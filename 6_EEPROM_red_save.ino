
void read_all () { //____________________________________Читаем данные из EEPROM
  eeprom_read_block((void*)&Timer1, 0, sizeof(Timer1));
  eeprom_read_block((void*)&Timer2, 44, sizeof(Timer2));
  eeprom_read_block((void*)&Timer3, 88, sizeof(Timer3));
  eeprom_read_block((void*)&Timer4, 132, sizeof(Timer4));
  eeprom_read_block((void*)&Timer5, 176, sizeof(Timer5));
  eeprom_read_block((void*)&Timer6, 190, sizeof(Timer6));
  eeprom_read_block((void*)&Timer7, 204, sizeof(Timer7));
  eeprom_read_block((void*)&Timer8, 216, sizeof(Timer8));
}

void update_all () { //_________________________________Обновляем данные в  EEPROM
  eeprom_update_block((void*)&Timer1, 0, sizeof(Timer1));
  eeprom_update_block((void*)&Timer2, 44, sizeof(Timer2));
  eeprom_update_block((void*)&Timer3, 88, sizeof(Timer3));
  eeprom_update_block((void*)&Timer4, 132, sizeof(Timer4));
  eeprom_update_block((void*)&Timer5, 176, sizeof(Timer5));
  eeprom_update_block((void*)&Timer6, 190, sizeof(Timer6));
  eeprom_update_block((void*)&Timer7, 204, sizeof(Timer7));
  eeprom_update_block((void*)&Timer8, 216, sizeof(Timer8));
}
