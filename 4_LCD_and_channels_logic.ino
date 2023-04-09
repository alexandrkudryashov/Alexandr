
void start_screen() { //______________________________________Стартовый экран
  uint16_t timeCur;
  uint16_t timeLast = millis();
  if   ((timeLast - timeCur) > 100) {
    timeCur = timeLast;
    lcd.setCursor(2, 0);
    lcd.print (watch.gettime("H:i:s D")); //__________________Время на экране

    lcd.setCursor(12, 1);  //_________________________________Отображение текущего состояния каналов на главном экране
    if (Timer1[0] == 2) {
      lcd.print("A");
    } else {
      lcd.print(Timer1 [0]);
    }
    lcd.setCursor(13, 1);
    if (Timer2[0] == 2) {
      lcd.print("A");
    } else {
      lcd.print(Timer2 [0]);
    }
    lcd.setCursor(14, 1);
    if (Timer3[0] == 2) {
      lcd.print("A");
    } else {
      lcd.print(Timer3 [0]);
    }
    lcd.setCursor(15, 1);
    if (Timer4[0] == 2) {
      lcd.print("A");
    } else {
      lcd.print(Timer4 [0]);
    }
    lcd.setCursor(3, 1);
    if (Timer5[0] == 2) {
      lcd.print("A");
    } else {
      lcd.print(Timer5 [0]);
    }
    lcd.setCursor(4, 1);
    if (Timer6[0] == 2) {
      lcd.print("A");
    } else {
      lcd.print(Timer6 [0]);
    }
    lcd.setCursor(5, 1);
    if (Timer7[0] == 2) {
      lcd.print("A");
    } else {
      lcd.print(Timer7 [0]);
    }
    lcd.setCursor(6, 1);
    if (Timer8[0] == 2) {
      lcd.print("A");
    } else {
      lcd.print(Timer8 [0]);
    }
    lcd.setCursor(9, 1);
    lcd.print("DT_"); //___________________________________________Суточные таймеры (Daily timers)
    lcd.setCursor(0, 1);
    lcd.print("PT_");  //__________________________________________Периодические таймеры (Periodic timers)
  }
}


void first_channel (uint16_t* timeMassive, char* Channel_name) { //Экраны каналов суточных таймеров
  enc1.tick();
  butt2.tick(); //_________________________________________________Опрос кнопок 2 и 3
  butt3.tick();

  if (butt2.isClick()) {
    period_cur = millis();//_______________________________________Сброс таймера простоя, сохранение всех изменений, переключение состояния канала
    flag = 1;
    update_all ();
    timeMassive [0]++;
  }

  if (timeMassive [0] > 2) timeMassive [0] = 0;

  if (butt3.isClick()) { //________________________________________Сброс таймера простоя, сохранение всех изменений, переключение настраиваемого таймера (элемент массива)
    period_cur = millis();
    flag = 1;
    update_all ();
    time_num++;
  }
  if (time_num > 20) time_num = 1;

  lcd.setCursor(0, 0); //__________________________________________Индикация состояния канала (Название, состояние (вкл, выкл, авто)
  lcd.print(Channel_name);
  lcd.setCursor(9, 0);
  switch (timeMassive [0]) {
    case 0:
      lcd.print("Off ");
      break;
    case 1:
      lcd.print("On  ");
      break;
    case 2:
      lcd.print("Auto");
      break;
  }

  lcd.setCursor(0, 1);
  switch (time_num) { //___________________________________________Таймеры на каждый канал 10 на включение и 10 на выключение (элементы массива)
    case 1:   lcd.print("Timer1 on ");
      break;
    case 3:   lcd.print("Timer2 on ");
      break;
    case 5:   lcd.print("Timer3 on ");
      break;
    case 7:   lcd.print("Timer4 on ");
      break;
    case 9:   lcd.print("Timer5 on ");
      break;
    case 11:   lcd.print("Timer6 on ");
      break;
    case 13:   lcd.print("Timer7 on ");
      break;
    case 15:   lcd.print("Timer8 on ");
      break;
    case 17:   lcd.print("Timer9 on ");
      break;
    case 19:   lcd.print("Timer10on ");
      break;
    case 2:   lcd.print("Timer1 off");
      break;
    case 4:   lcd.print("Timer2 off");
      break;
    case 6:   lcd.print("Timer3 off");
      break;
    case 8:   lcd.print("Timer4 off");
      break;
    case 10:   lcd.print("Timer5 off");
      break;
    case 12:   lcd.print("Timer6 off");
      break;
    case 14:   lcd.print("Timer7 off");
      break;
    case 16:   lcd.print("Timer8 off");
      break;
    case 18:   lcd.print("Timer9 off");
      break;
    case 20:   lcd.print("Timer10off");
      break;
  }

  uint16_t hourt, mint;
  hourt = ((timeMassive [time_num]) / 60); //______________________Пересчет данных из массивов в часы и минуты
  mint = ((timeMassive [time_num]) % 60);

  if (hourt == 24) { //____________________________________________Отображение устанавливаемого времени на экране
    lcd.setCursor(14, 1);
    lcd.print("--");
    lcd.setCursor(11, 1);
    lcd.print("--");
    lcd.setCursor(13, 1);
    lcd.print(":");
  } else {

    if (hourt < 10) {
      lcd.setCursor(11, 1);
      lcd.print(0);
      lcd.setCursor(12, 1);
      lcd.print(hourt);
    } else {
      lcd.setCursor(11, 1);
      lcd.print(hourt);
    }
    if (mint < 10) {
      lcd.setCursor(14, 1);
      lcd.print(0);
      lcd.setCursor(15, 1);
      lcd.print(mint);
    } else {
      lcd.setCursor(14, 1);
      lcd.print(mint);
    }
    lcd.setCursor(13, 1);
    lcd.print(":");
  }
  //_______________________________________________________________________________Работа с энкодером
  if (enc1.isRight())timeMassive [time_num] += 60;   // _________________________если был поворот направо, увеличиваем на 60 минут (1 час)
  if (enc1.isLeft()) timeMassive [time_num] -= 60;   // _________________________если был поворот налево, уменьшаем на 60 минут (1 час)
  if (enc1.isRightH()) timeMassive [time_num] += 1;  //_________________________ если было удержание + поворот направо, увеличиваем на 5 минут
  if (enc1.isLeftH()) timeMassive [time_num] -= 1;   //__________________________если было удержание + поворот налево, уменьшаем на 5 минут
  if (enc1.isClick()) timeMassive [time_num] = 0;
  if (timeMassive [time_num] > 1440) timeMassive [time_num] = 1440;
}

void second_channel (uint32_t* timeMassive, char* Channel_name) { //Экраны каналов периодических таймеров
  enc1.tick();
  butt2.tick(); //__________________________________________________Опрос кнопок 2 и 3
  butt3.tick();

  if (butt2.isClick()) {
    period_cur = millis();//_______________________________________ сброс таймера простоя, сохранение всех изменений, переключение состояния канала
    flag = 1;
    update_all ();
    timeMassive [0]++;
  }

  if (timeMassive [0] > 2) timeMassive [0] = 0;

  if (butt3.isClick()) { //________________________________________ сброс таймера простоя, сохранение всех изменений, переключение настройки периода/длительности (Period/Duration)
    period_cur = millis();
    flag = 1;
    update_all ();
    time_num++;
  }
  if (time_num > 2) time_num = 1;

  lcd.setCursor(0, 0); //__________________________________________Индикация состояния канала (Название, состояние (вкл, выкл, авто)
  lcd.print(Channel_name);
  lcd.setCursor(9, 0);
  switch (timeMassive [0]) {
    case 0:
      lcd.print("Off ");
      break;
    case 1:
      lcd.print("On  ");
      break;
    case 2:
      lcd.print("Auto");
      break;
  }
  lcd.setCursor(0, 1);
  switch (time_num) {
    case 1:   lcd.print("Period  ");
      break;
    case 2:   lcd.print("Length  ");
      break;
  }
  //______________________________________________________________________Отображение устанавливаемого времени на экране
  uint16_t hourt, mint, sect;
  hourt = ((timeMassive [time_num]) / 3600000); //______________________Пересчет данных из массивов в милисекундах в часы
  mint = (((timeMassive [time_num]) % 3600000) / 60000); //_____________Пересчет данных из массивов в милисекундах в минуты
  sect = ((((timeMassive [time_num]) % 3600000) % 60000) / 1000); //______Пересчет данных из массивов в милисекундах в секунды

  if (hourt < 10) {
    lcd.setCursor(8, 1);
    lcd.print(0);
    lcd.setCursor(9, 1);
    lcd.print(hourt);
  } else {
    lcd.setCursor(8, 1);
    lcd.print(hourt);
  }
  if (mint < 10) {
    lcd.setCursor(11, 1);
    lcd.print(0);
    lcd.setCursor(12, 1);
    lcd.print(mint);
  } else {
    lcd.setCursor(11, 1);
    lcd.print(mint);
  }
  if (sect < 10) {
    lcd.setCursor(14, 1);
    lcd.print(0);
    lcd.setCursor(15, 1);
    lcd.print(sect);
  } else {
    lcd.setCursor(14, 1);
    lcd.print(sect);
  }
  lcd.setCursor(10, 1);
  lcd.print(":");
  lcd.setCursor(13, 1);
  lcd.print(":");
  //______________________________________________________________________Работа с энкодером

  if (butt2.isHold()) {
    period_cur = millis();//____________________________________________ сброс таймера простоя, сохранение всех изменений, переключение состояния канала
    flag = 1;
    if (enc1.isRight())timeMassive [time_num] += 1000;     //____________если был поворот направо, увеличиваем на 1 секунду
    if (enc1.isLeft()) timeMassive [time_num] -= 1000;     //____________если был поворот налево, уменьшаем на 1 секунду
  } else {
    if (enc1.isRight())timeMassive [time_num] += 60000;     //____________если был поворот направо, увеличиваем на 1 минуту
    if (enc1.isLeft()) timeMassive [time_num] -= 60000;     //____________если был поворот налево, уменьшаем на 1 минуту
    if (enc1.isRightH()) timeMassive [time_num] += 3600000; //____________если было удержание + поворот направо, увеличиваем на 1 час
    if (enc1.isLeftH()) timeMassive [time_num] -= 3600000;
  }
  if (enc1.isClick()) timeMassive [time_num] = 0;
  if (timeMassive [time_num] > 356400000) timeMassive [time_num] = 356400000;
}
