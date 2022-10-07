#include "driver/mcpwm.h"

esp_err_t esp_err;

void setup() {
  Serial.begin(115200);
  // servo pwm config
  mcpwm_gpio_init(MCPWM_UNIT_1, MCPWM1A, 15);
//  mcpwm_config_t servo_pwm_config = {
//    .frequency = 50,  
//    .cmpr_a = 0,  
//    .duty_mode = MCPWM_DUTY_MODE_0,
//    .counter_mode = MCPWM_UP_COUNTER,
//  };
  mcpwm_config_t servo_pwm_config;
  servo_pwm_config.frequency = 50;  // 频率只能50Hz 20ms
  servo_pwm_config.cmpr_a = 0;
  servo_pwm_config.duty_mode = MCPWM_DUTY_MODE_0;
  servo_pwm_config.counter_mode = MCPWM_UP_COUNTER;
    
  esp_err = mcpwm_init(MCPWM_UNIT_1, MCPWM_TIMER_1, &servo_pwm_config);
  if (esp_err == 0)
    Serial.println("Setting motor pwm success!");
  else {
    Serial.print("Setting motor pwm fail, error code: ");
    Serial.println(esp_err);
  }
  mcpwm_start(MCPWM_UNIT_1, MCPWM_TIMER_1);
}

void loop() {
  mcpwm_set_duty(MCPWM_UNIT_1, MCPWM_TIMER_1, MCPWM_OPR_A, 7.5);  // 占空比2.5-12.5 0.5-2.5ms
  delay(1000);
  mcpwm_set_duty(MCPWM_UNIT_1, MCPWM_TIMER_1, MCPWM_OPR_A, 2.5);
  delay(1000);
  mcpwm_set_duty(MCPWM_UNIT_1, MCPWM_TIMER_1, MCPWM_OPR_A, 7.5);
  delay(1000);
  mcpwm_set_duty(MCPWM_UNIT_1, MCPWM_TIMER_1, MCPWM_OPR_A, 12.5);
  delay(1000);
}
