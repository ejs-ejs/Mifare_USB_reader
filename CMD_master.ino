void CMD_master() {

  Serial.println(F("Setting current card read as MASTER card\n"));

  
    for ( uint8_t i = 0; i < __CARD_LENGTH; i++) {
      validCard[i] = readCard[i];
    }
  Serial.print(F("MASTER card UID is: \t0x"));
  reportCardSerial();
  Serial.println(F("\nSory if you did not want to do this. You can just reset the reader to undo\n"));

}

