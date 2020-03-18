void setup()
{
  pinMode(12, OUTPUT);
  pinMode(3, INPUT);
  Serial.begin(9600);
}

int x;
int m=0;

void loop()
{
  x = digitalRead(3);
  Serial.println(m);
  delay(1000);
  if(x==0){
    m++;
    delay(1000);
  }
  
  if(m==0)blink(1);
  if(m==1)blink(2);
  if(m==2)blink(3);
  
  if(m>2)m=0;
}

void blink(int n){
  for(int i=0;i<n;i++)delay(1000);
  digitalWrite(12,HIGH);
  delay(300);
  digitalWrite(12,LOW);
}
