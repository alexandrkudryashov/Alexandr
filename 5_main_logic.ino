bool main_log (uint16_t* timeMassive, bool cur_state) {  // Основная фунция расчета состояния каналов суточных таймеров реального времени
  uint16_t j = 1440;
  uint8_t i = 0;
  uint8_t n = 0;
  for ( i = 1;  i < 21; i++) { //___________________________Ищем в массиве таймеров элемент соответсвующий текущему времени c значением не равным 1440 (означает неактивно, отображается "--:--")
    if ((timeMassive [i] == current_time) && (timeMassive [i] != 1440))  {
      j = timeMassive [i];
    }
  }
  if (j == 1440)return (cur_state); //_______________________Если не нашли оставляем состояние канала без изменений
  i = 0;
  for ( i = 1;  i < 21; i++) {
    if ((j == timeMassive [i]) && (timeMassive [i] != 1440))  {
      n = i;
    }
  }
  i = 0;
  if ((n % 2) == 0) { //____________________________________Четные таймеры выключают (LOW)
    return (LOW);
  }
  else return (HIGH); //____________________________________Нечетные таймеры включают (HIGH)
}

bool period_log (uint32_t* timeMassive, bool* state5, uint32_t* counter ) {  // Основная фунция расчета состояния каналов периодических таймеров
  uint32_t period_ms = 0;
  uint32_t duration_ms = 0;
  uint8_t j = 0;
  uint8_t i = 0;
  period_ms = (timeMassive [1]);
  duration_ms = (timeMassive [2]);

  if (millis() - *counter >= period_ms) { //_______________Отсчитывает время периода, включает реле, отсчитывает время длительности, выключает реле
    *state5 = HIGH;
    if ((millis() - *counter) >= (period_ms + duration_ms)) {
      *counter += period_ms;
      *state5 = (LOW);
    }
  }
}
