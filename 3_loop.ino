void loop() {
  watch.gettime(); //_________________________________________Получаем текущее время
  current_time = (((watch.Hours) * 60) + (watch.minutes));  //Переводим текущее время в минуты

  if (((millis() -  period_cur) > period_wait) && (flag)) { //Отключение подсветки, переход на стартовый экран, сохранение всех изменений после истечения периода бездействия
    update_all ();
    lcd.clear();
    lcd.noBacklight();
    flag = 0;
    number_channel = 0;
  }

  butt1.tick(); //____________________________________________Опрос кнопоки 1

  if (butt1.isClick()) {  //__________________________________Выбор текущего канала для настройки (По порядку, циклически)
    period_cur = millis();
    lcd.clear();
    lcd.backlight();
    flag = 1;
    number_channel++;
    time_num = 1;
    update_all ();
    if (number_channel > 8)number_channel = 0;
  };

  if  (butt1.isHolded()) { //________________________________Меню настройки времени (Включается по удержанию кнопки 1)
    period_cur = millis();
    lcd.clear();
    lcd.backlight();
    flag = 1;
    number_channel = 9;
  }

  switch (number_channel) {  //_______________________________Отображение текущего канала на экране
    case 0: start_screen();
      break;
    case 1: first_channel(Timer1, "1 SVET"); //______________В кавычках название канала для отображения на экране можно указать любое (Длинной не более 8 символов вместе с пробелами)
      break;
    case 2: first_channel(Timer2, "2 VENT"); //________________Каналы 1 - 4 суточные таймеры привязанные к реальному времени (после перезагрузки продолжают работать в том же режиме)
      break;
    case 3: first_channel(Timer3, "3 POMP1");
      break;
    case 4: first_channel(Timer4, "4 POMP2");
      break;
    case 5: second_channel(Timer5, "5 Period"); //____________В кавычках название канала для отображения на экране можно указать любое (Длинной не более 8 символов вместе с пробелами)
      break;
    case 6: second_channel(Timer6, "6 Period"); //____________Каналы 5 - 8 периодические таймеры НЕ привязанные к реальному времени (после перезагрузки начинают все с начала)
      break;
    case 7: second_channel(Timer7, "7 Period");
      break;
    case 8: second_channel(Timer8, "8 Period");
      break;
    case 9: set_time (); //___________________________________Экран установки (коррекции) времени
      break;
  }

  state1 = main_log(Timer1, state1);  //______________________Обработка каналов управления суточных таймеров реального времени (каналы 1 - 4)
  switch (Timer1 [0]) {
    case 0:  digitalWrite(9, 0);
      break;
    case 1:  digitalWrite(9, 1);
      break;
    case 2:   digitalWrite(9, state1);
      break;
  }
  state2 = main_log(Timer2, state2);
  switch (Timer2 [0]) {
    case 0:  digitalWrite(10, 0);
      break;
    case 1:  digitalWrite(10, 1);
      break;
    case 2:   digitalWrite(10, state2);
      break;
  }
  state3 = main_log(Timer3, state3);
  switch (Timer3 [0]) {
    case 0:  digitalWrite(11, 0);
      break;
    case 1:  digitalWrite(11, 1);
      break;
    case 2:   digitalWrite(11, state3);
      break;
  }
  state4 = main_log(Timer4, state4);
  switch (Timer4 [0]) {
    case 0:  digitalWrite(12, 0);
      break;
    case 1:  digitalWrite(12, 1);
      break;
    case 2:   digitalWrite(12, state4);
      break;
  }
  
  period_log(Timer5, &state5, &counter1);   //________________Обработка каналов управления периодических таймеров (каналы 5 - 6)
  switch (Timer5 [0]) {
    case 0:  digitalWrite(5, 0);
      break;
    case 1:  digitalWrite(5, 1);
      break;
    case 2:   digitalWrite(5, state5);
      break;
  }
  period_log(Timer6, &state6, &counter2);
  switch (Timer6 [0]) {
    case 0:  digitalWrite(6, 0);
      break;
    case 1:  digitalWrite(6, 1);
      break;
    case 2:   digitalWrite(6, state6);
      break;
  }
  period_log(Timer7, &state7, &counter3);
  switch (Timer7 [0]) {
    case 0:  digitalWrite(7, 0);
      break;
    case 1:  digitalWrite(7, 1);
      break;
    case 2:   digitalWrite(7, state7);
      break;
  }
  period_log(Timer8, &state8, &counter4);
  switch (Timer8 [0]) {
    case 0:  digitalWrite(8, 0);
      break;
    case 1:  digitalWrite(8, 1);
      break;
    case 2:   digitalWrite(8, state8);
      break;
  }
}
