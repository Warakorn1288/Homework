/*  
  motor speed control
    by serial input
  200 pulses per round
    require: RMP-mode = 730
    input: -100 to 100
    max speed = 255 rpm
                */

int count_pinA = 2;
int count_pinB = 3;
int enable12 = 4;
int input1 = 5;
int input2 = 6;

int count = 0;

int state = 0;
int first_count = 0;
int second_count = 0;
int real_speed = 0;

volatile int timer1_counter;

void InitiateInterruptTimer(int freq)
{
  //initialize timer1
  noInterrupts(); // disable all interrupts
  TCCR1A = 0;     // TCCRx - Timer/Counter Control Register
  TCCR1B = 0;
  
  // TCNTx - Timer/Counter Register
  // The actual timer value is stored here
  // TCNT1 Max is 65536
  timer1_counter = 62500/freq;
  TCNT1 = timer1_counter; // preload timer
  TCCR1B |= (1 << CS12);  // 256 prescaler
  TIMSK1 |= (1 << TOIE1); // Enable timer overflow interrupt
  interrupts(); // enable all interrupts
}

void setup()
{
  pinMode(count_pinA ,INPUT_PULLUP);
  pinMode(count_pinB ,INPUT_PULLUP);
  for(int i=4;i<=6;i++)pinMode(i ,OUTPUT);
  
  digitalWrite(enable12 ,HIGH);
  Serial.begin(9600);
  
  InitiateInterruptTimer(1000); // 1 Hz
  attachInterrupt(digitalPinToInterrupt(count_pinB),
                  add_count, RISING);
  attachInterrupt(digitalPinToInterrupt(count_pinA),
                  subtract_count, RISING);
}

int want_speed = 100;
int give_speed = 50;
int dir = 2;
int condition = 0;
String buff;

void loop()
{   
  set_speed( dir, give_speed, want_speed);
  
  if( Serial.available() > 0)
  {
    char inByte = Serial.read();
    
    if(condition == 1)
    {
      if(inByte == '-')
      {
        dir = 1;
      }
      else
      {
        dir = 0;
      }
      condition = 2;
    }
    
    if((inByte == 's') && (condition == 0))
    {
      buff = "";
      condition = 1;
    }
    
    if(('0'<=inByte) && ('9'>=inByte) && (condition == 2))
    {
      buff += inByte;
    }
    
    if(inByte == 'n')
    {
      want_speed = buff.toInt();
      want_speed = map( want_speed, 0, 100, 0, 255);
      want_speed = constrain( want_speed, 0, 255);
      condition = 0;
    }
  }
}

void set_speed( int Dir, int giveSpeed, int wantSpeed)
{
  if( Dir == 1 )counter_clockwise( giveSpeed );
  if( Dir == 0 )clockwise( giveSpeed );
  if( wantSpeed > give_speed ){
    give_speed += 1;
  }
  if( wantSpeed < give_speed ){
    give_speed -= 1;
  }
}

ISR (TIMER1_OVF_vect)
{
  TCNT1 = timer1_counter; // DO NOT EDIT
  if(state == 0){
    first_count = count;
  }
  if(state == 1){
    second_count = count;
  }
  state++;
  if(state>1){
    state=0;
  }
  
  Serial.print("current_rpm_speed = ");
  if( dir == 1 ){
    Serial.print("-");
  }
  Serial.println( abs(real_speed) );
  Serial.println(count);
}

void add_count() 
{
  if (digitalRead(count_pinA)==0 && 
      digitalRead(count_pinB)==1) 
  {
    count++;
    dir = 1;
    real_speed = ((second_count - first_count)*60)/200;
  }
}

void subtract_count() 
{
  if (digitalRead(count_pinA)==1 && 
      digitalRead(count_pinB)==0)
  {
    count--;
    dir = 0;
    real_speed = ((second_count - first_count)*60)/200;
  }
}

void counter_clockwise(int speed)
{
  analogWrite(input1 ,speed);
  analogWrite(input2 ,0);
}

void clockwise(int speed)
{
  analogWrite(input1 ,0);
  analogWrite(input2 ,speed);
}
