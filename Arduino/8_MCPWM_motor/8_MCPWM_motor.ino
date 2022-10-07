// https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/mcpwm.html#operate
// https://electronics.stackexchange.com/questions/360390/what-is-the-difference-between-mcpwm-and-ledc-pwm
// https://github.com/espressif/esp-idf/blob/master/examples/peripherals/mcpwm/mcpwm_servo_control/main/mcpwm_servo_control_example_main.c

#include "driver/mcpwm.h"

esp_err_t esp_err;

void setup() {
  Serial.begin(115200);

  mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0A, 26);  // A,B两个通道
  mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0B, 27);
  
  mcpwm_config_t motor_pwm_config = {
    .frequency = 1000,
    .cmpr_a = 0,  // 初始占空比，不设也行
    .cmpr_b = 0,
    .duty_mode = MCPWM_DUTY_MODE_0,
    .counter_mode = MCPWM_UP_COUNTER,
  };
  esp_err = mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_0, &motor_pwm_config);
  Serial.println(esp_err);
}

void loop() {

  // PWM
  mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, 80);  // 占空比60可填0-100
  mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_B, 0);
  mcpwm_start(MCPWM_UNIT_0, MCPWM_TIMER_0);
  delay(5000);  // 转5s
  mcpwm_stop(MCPWM_UNIT_0, MCPWM_TIMER_0);
  mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, 0);
  mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_B, 80);
  mcpwm_start(MCPWM_UNIT_0, MCPWM_TIMER_0);
  delay(5000);
  mcpwm_stop(MCPWM_UNIT_0, MCPWM_TIMER_0);
}
