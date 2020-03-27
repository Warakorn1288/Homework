#define enable12 5
#define input1 3
#define input2 4

void setup()
{
  pinMode(enable12, OUTPUT);   
  pinMode(input1, OUTPUT);   
  pinMode(input2, OUTPUT); 
}

void rotateLeft(int speed){
  analogWrite(enable12, speed);
  digitalWrite(input1, HIGH);
  digitalWrite(input2, LOW);
} 

void rotateRight(int speed){
  analogWrite(enable12, speed);
  digitalWrite(input1, LOW);
  digitalWrite(input2, HIGH);
} 

void loop()
{
  
}
