/*********
  Rui Santos
  Complete instructions at https://RandomNerdTutorials.com/esp32-cam-projects-ebook/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files.
  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*********/
// https://randomnerdtutorials.com/esp32-esp8266-input-data-html-form/
// 

#include "WiFi.h"
#include "esp_timer.h"
#include "img_converters.h"
#include "Arduino.h"
#include "soc/soc.h"           // Disable brownour problems
#include "soc/rtc_cntl_reg.h"  // Disable brownour problems
#include "driver/rtc_io.h"
#include <ESPAsyncWebServer.h>
#include <StringArray.h>
#include <FS.h>

// LED pin
const int green_led_pin = 32;
const int red_led_pin = 33;

// Set your access point network credentials
const char* ssid = "wenhui";
const char* password = "wwh802613";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

const char* PARAM_INPUT_1 = "green_light";
const char* PARAM_INPUT_2 = "red_light";

void toggle_light(int color);

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>Mini-Car Controller</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    body { text-align:center; }
    .vert { margin-bottom: 10%; }
    .hori{ margin-bottom: 0%; }
  </style>
</head>
<body>
  <div align="center">
    <button type="button" name="green_light" id="green_light">Green Light</button>
    <button type="button" name="red_light" id="red_light">Red Light</button>
  </div>
  <script>
    var xhttp = new XMLHttpRequest();
    var green_light_botton = document.getElementById('green_light');
    var red_light_botton = document.getElementById('red_light');
    green_light_botton.onclick = function() {
      xhttp.open("POST", "/toggle_green_light");  //访问服务（开关灯）
      xhttp.send();
      console.log('toggle_green_light');
    }
    red_light_botton.onclick = function() {
      xhttp.open("POST", "/toggle_red_light");
      xhttp.send();
      console.log('toggle_red_light');
    }
  </script>
</body>
</html>)rawliteral";

void setup() {
  // Serial port for debugging purposes
  Serial.begin(115200);

  WiFi.mode(WIFI_AP); 
  if(!WiFi.softAPConfig(IPAddress(192, 168, 4, 1), IPAddress(192, 168, 4, 1), IPAddress(255, 255, 0, 0))){
      Serial.println("AP Config Failed");
  }
  WiFi.softAP(ssid, password);  //密码8位数以上

  IPAddress IP = WiFi.softAPIP();  //打印IP
  Serial.print("AP IP address: ");
  Serial.println(IP);

  // Turn-off the 'brownout detector'
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);

  // set led pinmode
  pinMode(green_led_pin, OUTPUT);
  pinMode(red_led_pin, OUTPUT);

  digitalWrite(green_led_pin, HIGH);
  digitalWrite(red_led_pin, HIGH);

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/html", index_html);
  });
  server.on("/toggle_green_light", HTTP_POST, [](AsyncWebServerRequest * request) {  //用户发送
    toggle_light(1);  
  });  
  server.on("/toggle_red_light", HTTP_POST, [](AsyncWebServerRequest * request) {
    toggle_light(2);
  });
  // Start server
  server.begin();
}

void loop() {
  delay(1);
}

void toggle_light(int color) {
  if (color == 1) {
    bool state = digitalRead(green_led_pin);
    digitalWrite(green_led_pin, !state);
  }
  else if (color == 2) {
    bool state = digitalRead(red_led_pin);
    digitalWrite(red_led_pin, !state);
  }
}
