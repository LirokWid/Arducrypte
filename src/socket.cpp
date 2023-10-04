#include "socket.h"


AsyncWebSocket ws("/ws");
AsyncWebServer server(SERVER_PORT);
JSONVar jsonValues;

String message;
WiFiClient wifi;


void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  AwsFrameInfo *info = (AwsFrameInfo*)arg;

  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT)
  {
    data[len] = 0;
    message = (char*)data;
    if (message.indexOf("BPM:") >= 0) 
    {
      Serial.println(message);
      ledData.bpm = message.substring(4).toInt();
    }

    if (message.indexOf("COLOR:") >= 0)
    {
      Serial.println(message);
      message = message.substring(6);
      long valeurHex = strtol(message.c_str() + 1, NULL, 16);
      ledData.color.r = ((valeurHex >> 16) & 0xFF);
      ledData.color.g = ((valeurHex >> 8) & 0xFF);
      ledData.color.b = (valeurHex & 0xFF);
    }
    if(message.indexOf("ANIMATION:") >= 0){
      Serial.println(message);
      ledData.animation = message.substring(10).toInt();
    }
    if(message.indexOf("BRIGHTNESS:") >= 0){
      Serial.println(message);
      ledData.brightness = message.substring(11).toInt();
      FastLED.setBrightness(ledData.brightness);
      FastLEDshowESP32();
    }
    if (strcmp((char*)data, "getValues") == 0) {
      notifyClients(getValues());
    }
  }
}
// Check if a message contains a specific keyword
bool messageContains(const char* keyword, const char* message) {
  return strstr(message, keyword) != NULL;
}

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
  switch (type) {
    case WS_EVT_CONNECT:
      Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
      break;
    case WS_EVT_DISCONNECT:
      Serial.printf("WebSocket client #%u disconnected\n", client->id());
      break;
    case WS_EVT_DATA:
      handleWebSocketMessage(arg, data, len);
      break;
    case WS_EVT_PONG:
      Serial.printf("WebSocket client #%u pong\n", client->id());
      break;
    case WS_EVT_ERROR:
      Serial.printf("WebSocket client #%u error\n", client->id());
      break;
  }
}

void initSocket() {
  ws.onEvent(onEvent);
  server.addHandler(&ws);
}

void notifyClients(String sliderValues) {
  ws.textAll(sliderValues);
}

//Get Slider Values
String getValues(){
  jsonValues["BPM"] = String(ledData.bpm);
  //TODO ameliorer l'envoi de la couleur
  //convert color to hex
  //Force 6 digits
  String hexColor = String(ledData.color.r, HEX);
  if (hexColor.length() < 2) {
    hexColor = "0" + hexColor;
  }
  hexColor += String(ledData.color.g, HEX);
  if (hexColor.length() < 4) {
    hexColor = "0" + hexColor;
  }
  hexColor += String(ledData.color.b, HEX);
  if (hexColor.length() < 6) {
    hexColor = "0" + hexColor;
  }

  jsonValues["COLOR"] = "#"+ hexColor;
  jsonValues["ANIMATION"] = String(ledData.animation);
  jsonValues["BRIGHTNESS"] = String(ledData.brightness);

  String jsonString = JSON.stringify(jsonValues);
  return jsonString;
}

//cleanup client connections
void cleanupClients(){
  ws.cleanupClients();
}
// Initialize SPIFFS
void initFS() {
  if (!SPIFFS.begin(true)) {
    Serial.println("An error has occurred while mounting SPIFFS");
  }
  else{
    Serial.println("SPIFFS mounted successfully");
  }
}
// Initialize WiFi
void setupWifi()
{
  // Set Hostname.
  String hostname(HOSTNAME);
  char hostnameChar[hostname.length() + 1];
  memset(hostnameChar, 0, hostname.length() + 1);

  for (uint8_t i = 0; i < hostname.length(); i++)
    hostnameChar[i] = hostname.charAt(i);

  WiFi.setHostname(hostnameChar);

  // Print hostname.
  Serial.println("Hostname: " + hostname);

  WiFi.persistent(false);
  WiFi.disconnect();
  WiFi.mode(WIFI_OFF);

  if (AP_MODE)
  {
    WiFi.mode(WIFI_AP);
    WiFi.softAP(hostnameChar, NULL);
    Serial.printf("Connect to Wi-Fi access point: %s\n", hostnameChar);
    Serial.print("soft AP IP: ");
    Serial.println(WiFi.softAPIP());
  }
  else
  {
    WiFi.mode(WIFI_STA);
    //Set local ip address to static at 192.169.1.100
    IPAddress local_IP(192, 168, 1, 100);
    IPAddress gateway(192, 168, 1, 1);
    IPAddress subnet(255, 255, 255, 0);
    if (!WiFi.config(local_IP, gateway, subnet))
    {
      Serial.println("STA Failed to configure");
    }
    Serial.printf("Connecting to %s\n", WIFI_SSID);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED)
    {
      delay(100);
      Serial.print(".");
    }
    Serial.println();
    Serial.print("Connected! IP address: ");
    Serial.println(WiFi.localIP());
  }
}


void initWebServer()
{
  initFS();
  setupWifi();
  initSocket();

    // Web Server Root URL
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", "text/html");
  });
  
  server.serveStatic("/", SPIFFS, "/");

  // Start server
  server.begin();
}
