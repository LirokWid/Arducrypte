# Arducrypte
Web page for controling WS2812b leds

This project was made for an ESP32 using PlatformIO as compiler and programer and WebStorm for the web page developpment


Do not forget to add `login.h` to the `include` folder with the following content:
```c
#ifndef LOGIN_H
#define LOGIN_H

//For AP mode
#define HOSTNAME "hostname"
#define AP_PASSWORD "ap-password"

//For STA mode
#define WIFI_SSID  "ssid"
#define WIFI_PASSWORD "password"
#endif
```