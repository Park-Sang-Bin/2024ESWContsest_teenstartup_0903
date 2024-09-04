#include "HUSKYLENS.h"
#include <Servo.h>
#include <SoftwareSerial.h>

#define BT_RXD 3
#define BT_TXD 2

SoftwareSerial BTSerial(2,3);
HUSKYLENS huskylens;
Servo sv1;
Servo sv2;

int flag_1 = 0;
int flag_2 = 0;
int flag_3 = 0;

int y;

void setup() {
    Serial.begin(9600);
    BTSerial.begin(9600);
    Wire.begin();
    sv1.attach(8);
    sv2.attach(12);
    while (!huskylens.begin(Wire))
    {
        Serial.println(F("Begin failed! Check wiring and power supply."));
        delay(100);  
    }
    Serial.println(F("HUSKYLENS initialized successfully!"));
}

void loop() {
  if (BTSerial.available()) {
    y = BTSerial.read();
    Serial.println(y);
  }
    if (!huskylens.request()) {
        Serial.println(F("Fail to request data from HUSKYLENS, recheck the connection!"));
    } 
    else if (!huskylens.isLearned()) {
        Serial.println(F("Nothing learned, press learn button on HUSKYLENS to learn one!"));
    } 
    else if (!huskylens.available()) {
        sv1.write(0); 
        sv2.write(0);
        BTSerial.write ('b');
    } 
    else {
        while (huskylens.available()) {
          HUSKYLENSResult result = huskylens.read();
          if (result.command == COMMAND_RETURN_BLOCK) {
            if (y == 113 || flag_1 == 1) {
              flag_1 = 1;
              if ((result.ID) == 1) {
                sv1.write(90); 
                sv2.write(90);
                BTSerial.write('a');
              
              }
            }

            // case 'i':
            if (y == 119 || flag_2 == 1) {
              flag_2 = 1;
              if ((result.ID) == 2){
                sv1.write(90);   
                sv2.write(90);
                BTSerial.write ('c');
              }
            }

            // case 'y' :
            if (y == 101 || flag_3 == 1) {
              flag_3 = 1;
              if ((result.ID) == 3) {
                sv1.write(90);
                sv2.write(90);
                BTSerial.write ('d');
              }
            }
            if (y == 114) {
              sv1.write(0);
              sv2.write(0);
              flag_1 = 0;
            }
          }
            if (y == 115) {
              sv1.write(0);
              sv2.write(0);
              flag_2 = 0;
            }
            if (y == 116) {
              sv1.write(0);
              sv2.write(0);
              flag_3 = 0;
            }
          else break;
        }    
    }
}
