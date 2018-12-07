/* CONTROLL COMMANDS
    help command
*/

void CMD_state() {
  Serial.println(F("\n\nThis is Mifare Classic card reader"));
  Serial.print(F("\t version "));
  Serial.println(__VERSION);
  Serial.println(F("=============================="));
  Serial.print(F("\tUIDs inverted:\t"));
  invertUID?Serial.println("Yes"):Serial.println("No");
  Serial.println(F("=============================="));
  ShowReaderDetails();
  Serial.println(F("=============================="));
  Serial.println(F("====    Last card read    ===="));
  Serial.println(F("=============================="));
  // Dump debug info about the card. PICC_HaltA() is automatically called.
  mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
  Serial.println(F("=============================="));
  Serial.println(F("Present the Card to see You"));
}
