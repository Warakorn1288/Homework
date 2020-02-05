int clk_pin = 6; //SHCP
int latch_pin = 4; //STCP
int data_pin = 5; //DS

int i=0;
int toggle=0;
int a=0;

uint8_t segment_no[10] = { 0x3F ,
                          0x06,                          
                          0x5B,
                          0x4F,
                          0x66,
                          0x6D,
                          0x7D,
                          0x07,
                          0x7F,
                          0x6F
                          };

void setLed(uint8_t _state){
digitalWrite(latch_pin,LOW);
 
for(int i = 0 ; i < 8 ; i++){
digitalWrite(data_pin,(_state >> (7-i)) & 0x01);
digitalWrite(clk_pin,HIGH); //
digitalWrite(clk_pin,LOW); //
}
digitalWrite(latch_pin,HIGH);
}

void setup()
{
DDRD = 0b01110000;//PD4-6
DDRB = 0b00000000;//pin8,9 pull up
}

void loop()
{
  if(digitalRead(8)==0){
    a++;
    delay(300);
    if(a>9){
      a=0;
    }
  }
  if(digitalRead(9)==0){
    a--;
    delay(300);
    if(a<0){
      a=9;
    }
  }
  setLed(segment_no[a]);
  Serial.println(a);
}
