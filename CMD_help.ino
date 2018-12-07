/* CONTROLL COMMANDS
    help command
*/

void CMD_help(void) {
Serial.println(F("\n\nThis is Mifare Classic card reader"));
  Serial.print(F("\t version "));
  Serial.println(__VERSION);
  Serial.println(F("\nREVERSE - reverse card's UID byte order for output (keyboard and serial)"));
  Serial.println(F("STATE - print the state of the device"));
  Serial.println(F("MASTER - set last card read as MASTER card\n"));
  Serial.println(F("ejs <eugenijus.januskevicius@vgtu.lt>, 2018"));
}
