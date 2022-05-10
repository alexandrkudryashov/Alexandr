#include <Servo.h>

#define coef 10 //(коэффициент соответствия 10 градусов на 1см)
#define dead_zone 2
#define max_value 10
#define servoPin 10

#define Trig 9
#define Echo 8
#define ledPin 13

Servo myservo;

void setup()
{
  pinMode(Trig, OUTPUT); //инициируем как выход
  pinMode(Echo, INPUT);  //инициируем как вход
  pinMode(ledPin, OUTPUT);
  myservo.attach(servoPin);
  myservo.write(0);
}

unsigned int impulseTime = 0;
unsigned int distance_sm = 0;

void loop()
{
  digitalWrite(Trig, HIGH); /* Подаем импульс на вход
   trig дальномера */
  delayMicroseconds(10);  // равный 10 микросекундам
  digitalWrite(Trig, LOW); // Отключаем
  impulseTime = pulseIn(Echo, HIGH); // Замеряем длину импульса
  distance_sm = impulseTime / 58; // Пересчитываем в сантиметры

  if (distance_sm >= dead_zone && distance_sm <= max_value)
  {
    myservo.write(coef * (distance_sm - dead_zone));
  }
  else if (distance_sm < dead_zone)// если дистанция менее 4 см, серва в положении ноль градусов
  {
    myservo.write(45);
  }
  else
  {
    myservo.write(90);
  }
  delay(1000); /* ждем 0.1 секунды,
   Следующий импульс может быть излучён, только после исчезновения эха от предыдущего. Это время называется периодом цикла (cycle period). Рекомендованный период между импульсами должен быть не менее 50 мс.
*/
}
