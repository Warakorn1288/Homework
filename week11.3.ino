/*  
  motor position control  
  170 pulses per round
    require: RMP-mode = 612
    
    300k ohm potentiometer 
    with 1846 ohm resistor 
    gives range from 1 to 360
                */

#define count_pinB 3
#define enable12 4
#define input2 5
#define input1 6
#define potentio_input A0

void setup()
{
  pinMode(A0, INPUT);
  pinMode(count_pinB, INPUT_PULLUP);
  pinMode(enable12, OUTPUT);
  pinMode(input2, OUTPUT);
  pinMode(input1, OUTPUT);
  Serial.begin(9600);
  
  attachInterrupt(digitalPinToInterrupt(count_pinB),
                  add_count, RISING);
  digitalWrite(enable12, HIGH);
}

int dir = 1;
long int count = 0;
int speed = 20;
int angle = 0;
int want_angle;
int add_angle;

void loop()
{
  want_angle = 5;
  add_angle = analogRead(A0);
  want_angle = add_angle;
  
  speed_control( dir , speed );
  if( count>170 || angle>360 ) count = 0;
  if( angle > want_angle ) dir=0;
  if( angle < want_angle ) dir=1;
}

void speed_control( int dir , int speed ){
  if( dir == 1 ) forward( speed );
  if( dir == 0 ) backward( speed );
}

void add_count() 
{
  if ( dir==1 ) count++;
  if ( dir==0 ) count--;
  angle = ( count *360 ) /170 ;
  
  // for graphing
  Serial.print( want_angle );
  Serial.print( "," );
  Serial.println( angle );
}

void forward(int speed)
{
  analogWrite(input1 ,speed);
  analogWrite(input2 ,0);
}

void backward(int speed)
{
  analogWrite(input1 ,0);
  analogWrite(input2 ,speed);
}
