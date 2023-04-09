void set_time () {
  enc1.tick();
  butt2.tick(); //__________________________________________________Опрос кнопок 2 и 3
  butt3.tick();

  if (butt2.isClick()) {
    period_cur = millis();//_______________________________________ Сброс таймера простоя
    flag = 1;
    h_set = (watch.Hours);//________________________________________Получение текущего времени (часов и минут)
    m_set = (watch.minutes);
  }

  if (butt3.isClick()) {
    period_cur = millis();//_______________________________________ Сброс таймера простоя
    flag = 1;
    watch.settime(-1, m_set, h_set); //_____________________________Установка текущего времени
  }

  if (enc1.isRight()) m_set++;  //__________________________________если был поворот направо, увеличиваем на 1 минуту
  if (enc1.isLeft()) m_set--;   //_________________________________ если был поворот налево, уменьшаем на 1 минуту
  if (enc1.isRightH()) h_set++; //__________________________________если было удержание + поворот направо, увеличиваем на 1 час
  if (enc1.isLeftH()) h_set--;  //_____________ . . .
  if (enc1.isClick()) {
    h_set = 0; //___________________________________________________если был клик сброс в ноль
    m_set = 0;
  }
  if (m_set > 59) m_set = 0;
  if (h_set > 23) h_set = 0;


  lcd.setCursor(2, 0);
  lcd.print (watch.gettime("H:i:s D")); //__________________________Время на экране (текущее)

  lcd.setCursor(0, 1); //___________________________________________Отображение настраиваемого времени
  lcd.print("Set time   ");

  if (h_set < 10) {
    lcd.setCursor(11, 1);
    lcd.print(0);
    lcd.setCursor(12, 1);
    lcd.print(h_set);
  } else {
    lcd.setCursor(11, 1);
    lcd.print(h_set);
  }
  if (m_set < 10) {
    lcd.setCursor(14, 1);
    lcd.print(0);
    lcd.setCursor(15, 1);
    lcd.print(m_set);
  } else {
    lcd.setCursor(14, 1);
    lcd.print(m_set);
  }
  lcd.setCursor(13, 1);
  lcd.print(":");
}
