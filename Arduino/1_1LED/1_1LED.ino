const int led_pin_1 = 32;
const int led_pin_2 = 33;
void setup() {
  pinMode(led_pin_1, OUTPUT);
  pinMode(led_pin_2, OUTPUT);
}

void loop() {
  digitalWrite(led_pin_1, LOW);
  delay(750);
  digitalWrite(led_pin_1, HIGH);
  delay(750);
  digitalWrite(led_pin_2, LOW);
  delay(1000);
}
