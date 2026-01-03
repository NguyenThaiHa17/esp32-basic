#include<Arduino.h>

byte pin[]={5,18,19,3,1,23,22,21};
const byte count[10]={
   B01000000,
  B11111001,
  B00100100,
  B10110000,
  B00011001, // 4
  B10010010, // 5
  B00000010, // 6
  B11111000, // 7
  B00000000, // 8
  B10010000,
};
int index_count=0;
int action_mode=0;
const int button_up=26;
const int button_down=25;
int last_time=0;
void IRAM_ATTR count_index_up(){

  if((millis()-last_time)>200){
    if(index_count<9){
      index_count++;
      action_mode=1;
    }
last_time=millis();

  }
}
void IRAM_ATTR count_index_down(){
  if((millis()-last_time)>200){
    if(index_count>0){
      index_count--;
      action_mode=2;
    }
last_time=millis();
  }
}
void sevenSeg(byte Bit){
  for (int i=0;i<8;i++){
    digitalWrite(pin[i],bitRead(Bit,i));
  }
}
void setup(){
  for (int i=-0;i<8;i++){
    pinMode(pin[i],OUTPUT);

  }
  pinMode(button_up,INPUT_PULLUP);
  pinMode(button_down,INPUT_PULLUP);
attachInterrupt(digitalPinToInterrupt(button_up),count_index_up,RISING);
attachInterrupt(digitalPinToInterrupt(button_down),count_index_down,RISING);
}

void loop(){
  if(action_mode==1){
    for(int i=0;i<10;i++){
      sevenSeg(count[i]);
      delay(500);
    }
    action_mode=0;
  }
  else if( action_mode==2){
    for (int i=9;i>=0;i--){
      sevenSeg(count[i]);
      delay(500);
    }
    action_mode=0;
  }
}