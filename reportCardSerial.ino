void reportCardSerial() {
  for ( uint8_t i = 0; i < __CARD_LENGTH; i++) {
    if (readCard[i] <16 )    {Serial.print(F("0"));}
    reverseUID ? Serial.print(rCard[i], HEX) : Serial.print(readCard[i], HEX);
  }
  }
