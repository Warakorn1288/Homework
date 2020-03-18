#define ds 10
#define clk 11
#define lch 12

int timer1_counter;
int mode = 0;

int map7seg[10]={
  0x7D,0x18,0x73,0x5B,0x1E,0x4F,0x6F,0x19,0x7F,0x5F
};

void spi_write_1(unsigned char cData){
  digitalWrite(lch,LOW);
  shiftOut(ds,clk,MSBFIRST,cData);
  digitalWrite(lch,HIGH); 
}
    
void setup()
{
  pinMode(ds,OUTPUT);
  pinMode(clk,OUTPUT);
  pinMode(lch,OUTPUT);
  
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  timer1_counter = 0;
  TCNT1 = timer1_counter;
  TCCR1B |= (1 << CS12);
  TIMSK1 |= (1 << TOIE1);
  interrupts();
  Serial.begin(9600);
}

void loop()
{
  
}

ISR (TIMER1_OVF_vect){
  TCNT1 = timer1_counter;
  spi_write_1(map7seg[mode]);
  mode++;
  if(mode>9)mode=0;
}
