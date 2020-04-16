/*  
  motor position control  
  170 pulses per round
    required RMP-mode = 612
                */

#define count_pinB 3
#define enable12 4
#define input2 5
#define input1 6

void setup()
{
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
int speed = 1;
int angle = 0;
int want_angle = 90;

void loop()
{
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
  
  // for graph
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
