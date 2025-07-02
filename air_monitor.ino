// Air Quality Monitoring
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11
#define MQ135_PIN A0
#define BUZZER 3

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  pinMode(MQ135_PIN, INPUT);
  pinMode(BUZZER, OUTPUT);
  dht.begin();
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  int airQuality = analogRead(MQ135_PIN);
  
  Serial.print("Temp: "); Serial.print(temperature);
  Serial.print("C Hum: "); Serial.print(humidity);
  Serial.print("% AQ: "); Serial.println(airQuality);
  
  lcd.setCursor(0, 0);
  lcd.print("T:"); lcd.print(temperature); lcd.print("C H:"); lcd.print(humidity);
  
  lcd.setCursor(0, 1);
  lcd.print("Air Q: "); lcd.print(airQuality);
  
  if (airQuality > 300) { // Set threshold for air quality
    digitalWrite(BUZZER, HIGH);
    lcd.setCursor(10, 1);
    lcd.print("ALERT!");
  } else {
    digitalWrite(BUZZER, LOW);
  }

  delay(2000);
}