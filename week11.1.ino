#define LED 8

#define pinA 2
#define pinB 3

#define enableAB 7
#define inputA 5
#define inputB 6

#define ds 11
#define lch 10
#define clk 9

int timer1_counter;
int encoderDir;

void setup()
{
  for(int i=5;i<=11;i++)pinMode(i, OUTPUT);
  pinMode(pinA, INPUT_PULLUP);
  pinMode(pinB, INPUT_PULLUP);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(pinA),
                  ChannelA_callback, RISING);
  attachInterrupt(digitalPinToInterrupt(pinB),
                  ChannelB_callback, RISING);
}

int encoderCount = 0;

void loop()
{
  backward(250);
  int Hundredth = (encoderCount / 100) % 10;
  int Thousandth = (encoderCount / 1000) % 10;
  showNum(Thousandth, Hundredth);
  if(encoderCount<0)digitalWrite(LED, HIGH);
  else digitalWrite(LED, LOW);
}

void ChannelA_callback() 
{
  if (digitalRead(pinA)==1 && 
      digitalRead(pinB)==0) 
  {
    encoderCount++;
    encoderDir = 1;
    Serial.println( encoderCount );
  }
}

void ChannelB_callback() 
{
  if (digitalRead(pinA)==0 && 
      digitalRead(pinB)==1)
  {
    encoderCount--;
    encoderDir = 0;
    Serial.println( encoderCount );
  }
}

void forward(int speed)
{
  digitalWrite(enableAB ,HIGH);
  analogWrite(inputA ,speed);
  analogWrite(inputB ,0);
}

void backward(int speed)
{
  digitalWrite(enableAB ,HIGH);
  analogWrite(inputA ,0);
  analogWrite(inputB ,speed);
}

int map7seg[10]={
  0x7D,0x18,0x73,0x5B,0x1E,0x4F,0x6F,0x19,0x7F,0x5F
};

void spi_write_1(unsigned char cData, unsigned char dData){
  digitalWrite(lch,LOW);
  shiftOut(ds,clk,MSBFIRST,dData);
  shiftOut(ds,clk,MSBFIRST,cData);
  digitalWrite(lch,HIGH); 
}

void showNum(int num1, int num2){
  spi_write_1(map7seg[num1], map7seg[num2]);
}
