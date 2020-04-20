/*  
  motor direction control
    by push buttons
    program checked by LED's blink
                */
//pin_declaration
int enable12 = 4;
int input1 = 5;
int input2 = 6;
int clockwise_pin = 7;
int counter_clockwise_pin = 8;
int LED = 12;

void setup()
{
  for(int i=4;i<=6;i++)pinMode(i ,OUTPUT);
  pinMode(LED ,OUTPUT);
  pinMode(clockwise_pin ,INPUT); //PULL_DOWN
  pinMode(counter_clockwise_pin ,INPUT);
  digitalWrite(enable12 ,HIGH);
  Serial.begin(9600);
  
  noInterrupts();
  //set timer1 interrupt at 2Hz
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 7811.5;// = (16*10^6) / (2*1024) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS12 and CS10 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  interrupts();
}

int condition = 0;
int i = 0;
int read_counter_clockwise_pin;
int read_clockwise_pin;

void loop()
{
  read_counter_clockwise_pin = PINB & 0x01;
  read_clockwise_pin = (PIND>>7) & 0x01;
  
  if( read_counter_clockwise_pin == 0x01 )
  {
    counter_clockwise();
  }
  if( read_clockwise_pin == 0x01 )
  {
    clockwise();
  }
}

bool toggle1 = 0;

//timer1 interrupt 2Hz
ISR(TIMER1_COMPA_vect)
{
  if (toggle1){
    PORTB |= 0b00010000;
    toggle1 = 0;
  }
  else{
    PORTB &= 0b11101111;
    toggle1 = 1;
  }
}

void counter_clockwise()
{
  analogWrite(input1 ,100);
  analogWrite(input2 ,0);
}

void clockwise()
{
  analogWrite(input1 ,0);
  analogWrite(input2 ,100);
}
