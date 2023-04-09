
void setup() {
  pinMode(5, OUTPUT); //____________Пины управления реле (5 - 8 периодические таймеры, 9 - 12 суточные таймеры)
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);

  lcd.init();
  lcd.backlight();
  watch.begin();
  enc1.setFastTimeout(10);

  if (!digitalRead(SW)) { //________Сброс настроек при включении с зажатым энкодером (Все таймеры и каналы выключены)
    update_all ();
    lcd.setCursor(0, 0);
    lcd.print(F(" Reset settings"));
    lcd.setCursor(7, 1);
    lcd.print(F("OK"));
  }
  while (!digitalRead(SW));
  lcd.clear();

  read_all (); //___________________Читаем настройки из памяти
  attachInterrupt(0, isr, CHANGE);//Прерывания на пинах энкодера
  attachInterrupt(1, isr, CHANGE);
  enc1.setType(TYPE2); //___________Тип энкодера


  /* установка времени, раскомментировать при первой прошивке, потом закомментировать и прошить еще раз,
    последняя цифра день недели (0 - sun, 1 - mon и т.д.) устанавливается вручную, остальные подтягиваются из системного времени */
  watch.settime(i[0], i[1], i[2], i[3], i[4], i[5], 0);

  watch.gettime(); //______________________________________Получаем текущее время и прокручиваем его ровно на сутки вперед, чтобы все каналы соответсвовали текущему состоянию
  current_time = (((watch.Hours) * 60) + (watch.minutes));
  for (int i = 0; i <= 1439; i++) {
    if (current_time > 1439) current_time = 0;
    state1 = main_log(Timer1, state1);
    state2 = main_log(Timer2, state2);
    state3 = main_log(Timer3, state3);
    state4 = main_log(Timer4, state4);
    current_time++;
  }
}

void isr() {   // Энкодер отработка в прерывании
  enc1.tick();
}
