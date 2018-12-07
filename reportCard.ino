void reportCard() {
  for ( uint8_t i = 0; i < __CARD_LENGTH; i++) {
    if (readCard[i] <16 )    {Keyboard.print(F("0"));}
    invertUID ? Keyboard.print(rCard[i], HEX) : Keyboard.print(readCard[i], HEX);
  }
}
