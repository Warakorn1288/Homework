#define pinA 2
#define pinB 3

int timer1_counter;
int countA = 0;
int countB = 0;
int diff = 10;

void setup(){
  pinMode(pinA, INPUT_PULLUP);
  pinMode(pinB, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.println("TestEncoder");
  
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  timer1_counter = 0;
  TCNT1 = timer1_counter;
  TCCR1B |= (1 << CS12);
  TIMSK1 |= (1 << TOIE1);
  interrupts();
  attachInterrupt(digitalPinToInterrupt(pinA),
                  ISR_CallbackA, RISING);
  attachInterrupt(digitalPinToInterrupt(pinB),
                  ISR_CallbackB, RISING);
}

void loop(){
  if(diff == 0)Serial.println("Counterclockwise");
  if(diff == 1)Serial.println("Clockwise");
}

void ISR_CallbackA(){
  countA++;
  diff = countA - countB;
}

void ISR_CallbackB(){
  countB++;
}
