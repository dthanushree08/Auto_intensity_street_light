// Auto Intensity Street Light with LCD

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int ldrPin = A0;
int ledPin = 9;

int lightValue;
int brightness;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Street Light");
  lcd.setCursor(0, 1);
  lcd.print("Auto Intensity");
  delay(1500);
  lcd.clear();
}

void loop() {
  lightValue = analogRead(ldrPin);          // 0 (dark) to 1023 (bright)

  // Invert and scale: darker surroundings = brighter LED
  brightness = map(lightValue, 0, 1023, 255, 0);
  brightness = constrain(brightness, 0, 255);

  analogWrite(ledPin, brightness);           // PWM output, dims the LED smoothly

  Serial.print("Light: ");
  Serial.print(lightValue);
  Serial.print("  LED Brightness: ");
  Serial.println(brightness);

  // LCD line 1: raw light reading
  lcd.setCursor(0, 0);
  lcd.print("Light: ");
  lcd.print(lightValue);
  lcd.print("    ");

  // LCD line 2: status + brightness
  lcd.setCursor(0, 1);
  if (lightValue > 700) {
    lcd.print("DAY  Lvl:");
    lcd.print(brightness);
    lcd.print("  ");
  }
  else if (lightValue > 300) {
    lcd.print("DUSK Lvl:");
    lcd.print(brightness);
    lcd.print("  ");
  }
  else {
    lcd.print("NIGHT Lvl:");
    lcd.print(brightness);
    lcd.print(" ");
  }

  delay(300);
}
