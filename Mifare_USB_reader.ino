/*
   This is Mifare UID reader, based on RFID-RC522 reader module, Arduino Leonardo/ Pro Micro and SPI, MFRC522 and SerialComand Libraries
   The reader can be found on eBay for around 5 dollars. Search for "mf-rc522" on ebay.com.

   The device is exposed as USB HID keyboard device (no drivers should be required) and standart serial port
   One connected, use predefined commands to configure the device. All changes are temporary right now, so you 
   can reset the device in the case of misfortune
   
   The predefined commands are: ?, STATE, INVERT, MASTER

   The library file MFRC522.h has a wealth of useful info. Please read it.
   The functions are documented in MFRC522.cpp.

   Pin layout should be as follows:
   Signal     Pin                   Pin
              Arduino Leonardo      MFRC522 board
   ----------------------------------------------------------------------------
   Reset      9                     RST
   SPI SS     10                    SDA
   SPI MOSI   ICSP_4                MOSI
   SPI MISO   ICSP_1                MISO
   SPI SCK    ICSP_3                SCK

   LED        4

*/

#define __VERSION "0.1a"
#define __CARD_LENGTH 4
#include <SPI.h>
#include <MFRC522.h>

#include <Keyboard.h> // USB HID keyboard; Leonardo / Pro Mini / DUE 

// command inteface
#include <SerialCommand.h>

#define LED 4

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance.

SerialCommand sCmd;     // The SerialCommand object


byte readCard[__CARD_LENGTH];   // Stores scanned ID read from RFID Module
byte rCard[__CARD_LENGTH];   // reversed card ID

byte invertUID = 1;

byte validCard[] = {0xE5, 0x4B, 0xA9, 0x65};
//

long tDelay = 500; // delay time between scans
long tNow = 0;
long tPrev = 0;
byte ledState = 0;
byte kbdReport = 0;


void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(115200); // Initialize serial communications with the PC
  SPI.begin();      // Init SPI bus
  mfrc522.PCD_Init(); // Init MFRC522 card
  Keyboard.begin(); // start HID/USB keyboard emulation
  // delay(2000); //for Leonardo


  // Setup callbacks for SerialCommand commands
  sCmd.addCommand("STATE",   CMD_state);         // print state to serial port
  sCmd.addCommand("INVERT",   CMD_invert);         // invert card's UID
  sCmd.addCommand("MASTER",   CMD_master);         // treat last card read as master card
  sCmd.addCommand("?", CMD_help);        // help un use
  sCmd.setDefaultHandler(CMD_help);      // Handler for command that isn't matched
}

void loop() {
  // read serial port
  sCmd.readSerial();

  // Look for new cards
  long tNow = millis();

  if ((tNow - tPrev) >= tDelay) {
    tPrev = tNow;
    digitalWrite(LED, ledState);
    if ( ! mfrc522.PICC_IsNewCardPresent()) {
      return;
    } else if ( ! mfrc522.PICC_ReadCardSerial()) { // Select one of the cards
      return;
    } else {
      for ( uint8_t i = 0; i < __CARD_LENGTH; i++) {
        readCard[i] = mfrc522.uid.uidByte[i];
        rCard[__CARD_LENGTH - 1 - i] = mfrc522.uid.uidByte[i];
      }
      kbdReport = 1;

      mfrc522.PICC_HaltA(); // Stop reading

      if (kbdReport) {
        reportCard();
        kbdReport = 0;
      }

      if ( checkUID(readCard, validCard) ) {
        ledState = 1;
        digitalWrite(LED, ledState);
        ledState = 0;
        reportCardSerial();
        Serial.println(F(":\tWelcome, Master"));
      } else {
        reportCardSerial();
        Serial.println(F(":\t === Go away, Stranger ==="));
      }
    }
  }
}

