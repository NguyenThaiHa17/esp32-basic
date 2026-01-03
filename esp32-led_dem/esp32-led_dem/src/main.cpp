#include <Arduino.h>
byte pin[]={5,18,19,3,1,23,22,21}; // a b c d e f g dp

const byte count[10]={
  B01000000,
  B11111001,
  B01000100,
  B10110000,
  B00011001, // 4
  B10010010, // 5
  B00000010, // 6
  B11111000, // 7
  B00000000, // 8
  B10010000, 
};
void sevenSeg(byte Bit){
  for (int i=0;i<8;i++){
    digitalWrite(pin[i],bitRead(Bit,i));
  }
}
void setup(){
  pinMode(pin[0],OUTPUT);
   pinMode(pin[1],OUTPUT);
    pinMode(pin[2],OUTPUT);

     pinMode(pin[3],OUTPUT);
      pinMode(pin[4],OUTPUT);
       pinMode(pin[5],OUTPUT); 
       pinMode(pin[6],OUTPUT);
        pinMode(pin[7],OUTPUT);
}
void loop(){
  for (int i=0;i<10;i++){
    sevenSeg(count[i]);
    delay(1000);
    }
}