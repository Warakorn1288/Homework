int clk_pin = 6; //SHCP
int latch_pin = 4; //STCP
int data_pin = 5; //DS

int data;
int i=0;
int toggle=0;

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
}

void loop()
{
  data= 0b00000111;
  setLed(data);
}
