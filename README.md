# Arducrypte
Web controler hosted on an ESP32 to control WS2812b leds using a web browser.

This project was made for an ESP32 using PlatformIO as compiler and programer and WebStorm for the web page developpment

This project aims to develop a fast and easy to use interface made for performance.

Do not forget to add `login.h` to the `include` folder with the following content:

```c++
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
