#include "LiquidCrystal_I2C.h"

#define BUT_PIN 2

LiquidCrystal_I2C lcd(0x27, 20, 4);

int last_but_state = HIGH;
int randInt = 0;

void setup() {
  pinMode(BUT_PIN, INPUT_PULLUP);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Rand digit: ");
  lcd.setCursor(0, 1);
  lcd.print("Time: ");
  lcd.setCursor(0, 2);
  lcd.print("Fibon digit: ");
  randomSeed(analogRead(A0));
  Serial.begin(9600);
  Serial.println("запуск");

}

void loop() {
  but_action();

}

void but_action() {
  int but_state = digitalRead(BUT_PIN);
  if (but_state == LOW && but_state != last_but_state) {
    Serial.println(1);
    randInt = random(5, 31);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Rand digit: ");
    lcd.print(randInt);
    uint32_t first_time = micros();
    uint32_t fibDigit = fibonacci(randInt);
    long time = micros() - first_time;
    lcd.setCursor(0, 1);
    lcd.print("Time: ");
    lcd.print(time / 1000000.0, 5);
    lcd.setCursor(0, 2);
    lcd.print("Fibon digit: ");
    lcd.print(fibDigit);
    last_but_state = but_state;
  }
  last_but_state = but_state;
}

uint32_t fibonacci(int n) {
  if (n <= 1) {
    return n;
  }
  return fibonacci(n - 1) + fibonacci(n - 2);
}

