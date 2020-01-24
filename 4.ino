void setup()
{
  Serial.begin(9600);
  DDRD = 0b11111100;
  DDRB = 0b00000011;
  pinMode(A0,INPUT);
}

void loop()
{
  int w = analogRead(A0);
  int x = map(w,290,1024,50,1500);
  int a = 0b00000100;
  for(int i=0;i<6;i++){
   PORTD = a<<i;
   Serial.println(x);
   delay(x);
  }
  PORTD = 0b00000000;
  int b = 0b00000001;
  for(int i=0;i<2;i++){
   PORTB = b<<i;
   Serial.println(x);
   delay(x);
  }
  PORTB = 0b00000000;
}
