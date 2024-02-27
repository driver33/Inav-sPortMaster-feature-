
//#include  <Arduino.h>
#include  <SoftwareSerial.h>

//HardwareSerial *serial;

const uint8_t pinCzujnik = 2; 
const uint8_t rxPin = 11;
const uint8_t txPin = 12;
const bool inversion = false;
unsigned long poprzedniCzas = 0;  // Zmienna do przechowywania poprzedniego czasu pomiaru
volatile int licznikImpulsow = 0;  // Licznik impulsów


uint8_t sPortHeader=0x7E;
uint8_t sPortSensorAsk=0xE4;

union sensorPacket {
    //! byte[8] presentation
    uint8_t byte[10] = {0x7E,0xE4,0x10,0x00,0x05,0x00,0x00,0x00,0x00,0x9A};
    struct {uint8_t Header; uint8_t Caller; uint8_t Responder; uint16_t sensorID; uint32_t sensorValue; uint8_t CRC;} sensorStructure;
    //! uint64 presentation
    uint64_t calosc;
};



SoftwareSerial mySerial(rxPin, txPin, inversion);
sensorPacket rpmPacket;




void setup()  {
  attachInterrupt(digitalPinToInterrupt(pinCzujnik), interruptService, RISING); 
    Serial.begin(57600);
    mySerial.begin(57600);
}

void loop() {
unsigned long aktualnyCzas = millis();

   if (Serial.available()>=2){
        sPortHeader = Serial.read();
        sPortSensorAsk = Serial.read();
       if (sPortSensorAsk == rpmPacket.sensorStructure.Caller) sendRPM();
      sPortHeader = 0;
      sPortSensorAsk =0;
      rpmPacket.byte[7]=0;
   }  

     if (mySerial.available()>=2){
        sPortHeader = mySerial.read();
        sPortSensorAsk = mySerial.read();
       if (sPortSensorAsk == rpmPacket.sensorStructure.Caller) sendSoftRPM();
      sPortHeader = 0;
      sPortSensorAsk =0;
      rpmPacket.byte[7]=0;
   }  

  if (aktualnyCzas - poprzedniCzas >=  1000) {
    float predkoscObrotowa = (licznikImpulsow  * 60.0);
    licznikImpulsow = 0;  
    setRPMValue(uint32_t(predkoscObrotowa));
    poprzedniCzas = millis(); 
    }

}

void setRPMValue (uint32_t rpmCalculated){
    rpmPacket.sensorStructure.sensorValue=rpmCalculated;
}


uint16_t CRCcheck (uint8_t *packet) {
    uint16_t crc = 0;
    for (int i=2; i<=8; i++) {
        crc += packet[i];
    }
     while (crc > 0xff) {
     crc = (crc & 0xFF ) + (crc >>8);
     } 
    
    return 0xFF-crc;
}


void sendRPM (){
        rpmPacket.sensorStructure.CRC=CRCcheck(rpmPacket.byte);
        for (int i=0; i<10; i++)  Serial.write(rpmPacket.byte[i]);
       }


void sendSoftRPM (){
        rpmPacket.sensorStructure.CRC=CRCcheck(rpmPacket.byte);
        for (int i=0; i<10; i++)  mySerial.write(rpmPacket.byte[i]);
       }


void interruptService()
{
  licznikImpulsow++;   // Zwiększenie liczby obrotów
}




