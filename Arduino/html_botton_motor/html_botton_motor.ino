/*********
  Rui Santos
  Complete instructions at https://RandomNerdTutorials.com/esp32-cam-projects-ebook/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files.
  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*********/
// https://randomnerdtutorials.com/esp32-esp8266-input-data-html-form/

#include "WiFi.h"
#include "esp_timer.h"
#include "Arduino.h"
#include "soc/soc.h"           // Disable brownour problems
#include "soc/rtc_cntl_reg.h"  // Disable brownour problems
#include "driver/rtc_io.h"
#include "driver/mcpwm.h"
#include <ESPAsyncWebServer.h>
#include <StringArray.h>
#include <FS.h>

esp_err_t esp_err;

// LED pin
const int green_led_pin = 32;
const int red_led_pin = 33;

// Set your access point network credentials
const char* ssid = "wenhui";
const char* password = "wwh802613";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);  //80：端口号

// motor parameters
int motor_duty_cycle = 60;

void toggle_light(int color);  //声明
void move_forward();
void move_backward();
void motor_stop();
void turn_left();
void turn_right();
void straight();

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html>
<head>
  <title>Mini-Car Controller</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
<style>  //CSS样式
  { font-family: sans-serif; background: #99FFCC; padding: 2rem; }
  body { max-width: 1200px; margin: 0 auto; background: #99CCFF; }
  nav { 
    background: rgb(60, 80, 100); 
    display: flex; 
    align-items: center; 
    padding: 0 1rem; 
    min-height: 5em;
  }
  nav h1 { 
      flex: auto; margin: 0; 
      color: #FFCCFF; 
      font: 1em lucida-grande;
      font-size: 40px;
      font-weight: 1500;
      margin-left: 0.5em;
  }
  .content { padding: 0 1rem 1rem; }
  .content > header { 
      /* border-bottom: 2px solid rgba(115, 133, 159, 0.5); */
      display: flex; align-items: flex-end; 
      /* background-color: #9fb2bb; */
  }
  .content > header h1 { 
      font: 1em lucida-grande;
      font-size: 24px;
      font-weight: 1000;
      color: #ff0000;
      flex: auto; 
      margin: 1rem 0 0.3rem 0; 
      margin-left: 0.3em;
  }
  .content p {
      margin: 5px;
      font-family: 'Courier New', Courier, monospace;
      font-size: 16px;
      font-weight: bold;
      line-height: 30px;
  }
  .content input[type=button] { 
      align-self: start; min-width: 8em; min-height: 2em; 
      font: 1em lucida-grande;
      font-size: 16px;
      font-weight: 1000;
      border: 0px;
      border-radius: 0.4em;
      background: rgba(115, 133, 159, 0.25);
  }
  .content input[type=button]:active {
      background: rgba(115, 133, 159, 0.507);
  }
</style>
</head>
<body>
  <nav>
    <h1>Mini car controller</h1>
  </nav>
  <section class="content">
    <header>
        <h1 align="center">Move</h1>
    </header>
    <p align="center">
      <input type="button" name="Green Light" value="Green Light" id="green_light">
      <input type="button" name="Red Light" value="Red Light" id="red_light">
    </p>
    <p align="center">
      <input type="button" name="Forward" value="Forward" id="forward">
      <input type="button" name="Stop" value="Stop" id="stop">
      <input type="button" name="Backward" value="Backward" id="backward">
    </p>
    <p align="center">
      <input type="button" name="Left" value="Left" id="left">
      <input type="button" name="Straight" value="Straight" id="straight">
      <input type="button" name="Right" value="Right" id="right">
    </p>
    <script>
      // XMLHttpRequest
      var xhttp = new XMLHttpRequest();  //脚本
      // button elements
      var green_light_button = document.getElementById('green_light');
      var red_light_button = document.getElementById('red_light');
      var forward_button = document.getElementById('forward');
      var backward_button = document.getElementById('backward');
      var stop_button = document.getElementById('stop');
      var left_button = document.getElementById('left');
      var right_button = document.getElementById('right');
      var straight_button = document.getElementById('straight');
      
      green_light_button.onclick = function() {
        xhttp.open("POST", "/toggle_green_light");
        xhttp.send();
        console.log('toggle green light');
      }
      red_light_button.onclick = function() {
        xhttp.open("POST", "/toggle_red_light");
        xhttp.send();
        console.log('toggle red light');
      }
      forward_button.onclick = function() {
        xhttp.open("POST", "/forward");
        xhttp.send();
        console.log('move forward');
      }
      backward_button.onclick = function() {
        xhttp.open("POST", "/backward");
        xhttp.send();
        console.log('move backward');
      }
      stop_button.onclick = function() {
        xhttp.open("POST", "/stop");
        xhttp.send();
        console.log('stop');
      }
      left_button.onclick = function() {
        xhttp.open("POST", "/left");
        xhttp.send();
        console.log('left');
      }
      right_button.onclick = function() {
        xhttp.open("POST", "/right");
        xhttp.send();
        console.log('right');
      }
      straight_button.onclick = function() {
        xhttp.open("POST", "/straight");
        xhttp.send();
        console.log('straight');
      }
    </script>
  </section>
</body>
</html>)rawliteral";

void setup() {
  // Serial port for debugging purposes
  Serial.begin(115200);

  WiFi.mode(WIFI_AP);
  if(!WiFi.softAPConfig(IPAddress(192, 168, 4, 1), IPAddress(192, 168, 4, 1), IPAddress(255, 255, 0, 0))){
      Serial.println("AP Config Failed");
  }
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  // Turn-off the 'brownout detector'
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);

  // set led pinmode
  pinMode(green_led_pin, OUTPUT);
  pinMode(red_led_pin, OUTPUT);

  digitalWrite(green_led_pin, HIGH);
  digitalWrite(red_led_pin, HIGH);

  // motor pwm config
  mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0A, 26);
  mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0B, 27);
  
  mcpwm_config_t motor_pwm_config;
  motor_pwm_config.frequency = 1000;
  motor_pwm_config.cmpr_a = 0;
  motor_pwm_config.cmpr_b = 0;
  motor_pwm_config.duty_mode = MCPWM_DUTY_MODE_0;
  motor_pwm_config.counter_mode = MCPWM_UP_COUNTER;
  
  esp_err = mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_0, &motor_pwm_config);
  if (esp_err == 0)
    Serial.println("Setting motor pwm success!");
  else {
    Serial.print("Setting motor pwm fail, error code: ");
    Serial.println(esp_err);
  }

  // servo pwm config
  mcpwm_gpio_init(MCPWM_UNIT_1, MCPWM1A, 13);
  
  mcpwm_config_t servo_pwm_config;
  servo_pwm_config.frequency = 50;
  servo_pwm_config.cmpr_a = 0;
  servo_pwm_config.duty_mode = MCPWM_DUTY_MODE_0;
  servo_pwm_config.counter_mode = MCPWM_UP_COUNTER;
  
  esp_err = mcpwm_init(MCPWM_UNIT_1, MCPWM_TIMER_1, &servo_pwm_config);
  if (esp_err == 0)
    Serial.println("Setting servo pwm success!");
  else {
    Serial.print("Setting servo pwm fail, error code: ");
    Serial.println(esp_err);
  }
  mcpwm_start(MCPWM_UNIT_1, MCPWM_TIMER_1);

  // Route for web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/html", index_html);
  });
  server.on("/toggle_green_light", HTTP_POST, [](AsyncWebServerRequest * request) {
    toggle_light(1);
  });
  server.on("/toggle_red_light", HTTP_POST, [](AsyncWebServerRequest * request) {
    toggle_light(2);
  });
  server.on("/forward", HTTP_POST, [](AsyncWebServerRequest * request) {
    move_forward();
  });
  server.on("/backward", HTTP_POST, [](AsyncWebServerRequest * request) {
    move_backward();
  });
  server.on("/stop", HTTP_POST, [](AsyncWebServerRequest * request) {
    motor_stop();
  });
  server.on("/left", HTTP_POST, [](AsyncWebServerRequest * request) {
    turn_left();
  });
  server.on("/right", HTTP_POST, [](AsyncWebServerRequest * request) {
    turn_right();
  });
  server.on("/straight", HTTP_POST, [](AsyncWebServerRequest * request) {
    straight();
  });
  // Start server
  server.begin();
}

void loop() {
  delay(1);
}

// some functions
void toggle_light(int color) {
  if (color == 1) {
    Serial.println("--- toggle left light...");
    bool state = digitalRead(green_led_pin);
    digitalWrite(green_led_pin, !state);
  }
  else if (color == 2) {
    Serial.println("--- toggle right light...");
    bool state = digitalRead(red_led_pin);
    digitalWrite(red_led_pin, !state);
  }
}

void move_forward() {
  Serial.println("--- move forward...");
  mcpwm_stop(MCPWM_UNIT_0, MCPWM_TIMER_0);
  mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, motor_duty_cycle);
  mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_B, 0);
  mcpwm_start(MCPWM_UNIT_0, MCPWM_TIMER_0);
}
void move_backward() {
  Serial.println("--- move backward...");
  mcpwm_stop(MCPWM_UNIT_0, MCPWM_TIMER_0);
  mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, 0);
  mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_B, motor_duty_cycle);
  mcpwm_start(MCPWM_UNIT_0, MCPWM_TIMER_0);
}
void motor_stop() {
  Serial.println("--- motor stop...");
  mcpwm_stop(MCPWM_UNIT_0, MCPWM_TIMER_0);
  mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, 100);
  mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_B, 100);
  mcpwm_start(MCPWM_UNIT_0, MCPWM_TIMER_0);
}
void turn_left() {
  mcpwm_set_duty(MCPWM_UNIT_1, MCPWM_TIMER_1, MCPWM_OPR_A, 5);
}
void turn_right() {
  mcpwm_set_duty(MCPWM_UNIT_1, MCPWM_TIMER_1, MCPWM_OPR_A, 10);
}
void straight() {
  mcpwm_set_duty(MCPWM_UNIT_1, MCPWM_TIMER_1, MCPWM_OPR_A, 7.5);
}
