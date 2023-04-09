#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#include <Servo.h>
#define DHTPIN A0 // к какому пину будет подключен сигнальный выход датчика
#define DHTTYPE DHT11 // DHT 11
#define PIN_RELAY A2
//инициализация датчика
DHT dht(DHTPIN, DHTTYPE);
Servo servo;
byte degree[8] = // кодируем символ градуса
{
B00111,
B00101,
B00111,
B00000,
B00000,
B00000,
B00000,
};
LiquidCrystal_I2C lcd(0x27,16,2); // Задаем адрес и размерность дисплея
void setup()
{
  servo.attach(9);
lcd.init(); // Инициализация lcd
lcd.backlight(); // Включаем подсветку
lcd.createChar(1, degree); // Создаем символ под номером 1
Serial.begin(9600);
pinMode(PIN_RELAY,OUTPUT);
digitalWrite(PIN_RELAY,HIGH);
dht.begin();
}
void loop() {
// Добавляем паузы в несколько секунд между измерениями
delay(2000);
float h = dht.readHumidity();
float t = dht.readTemperature();
float f = dht.readTemperature(true);
  Serial.print("Humidity: ");
  Serial.println(h);
  Serial.print("Temperature: ");
  Serial.println(t);
  if (t > 30) servo.write(0);
  else servo.write(90);
 if (t > 30) digitalWrite(PIN_RELAY,LOW);
 else  digitalWrite(PIN_RELAY,HIGH);
  delay(1000); //ждем 2 секунды
lcd.setCursor(0, 0); // Устанавливаем курсор в начало 1 строки
lcd.print("VLAG->"); // Выводим текст
lcd.setCursor(7, 0); // Устанавливаем курсор на 7 символ
lcd.print(h, 1); // Выводим на экран значение влажности
lcd.setCursor(0, 1); // Устанавливаем курсор в начало 2 строки
lcd.print("TEMP->"); // Выводим текст, \1 - значок градуса
lcd.setCursor(7, 1); // Устанавливаем курсор на 7 символ
lcd.print(t,1); // Выводим значение температуры
}
