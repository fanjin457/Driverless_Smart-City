const int led_pin_1 = 32;

void setup() {
  pinMode(led_pin_1, OUTPUT);
}

void loop() {
  digitalWrite(led_pin_1, LOW);
  delay(1000);
}
