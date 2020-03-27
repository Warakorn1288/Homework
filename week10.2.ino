#define INT_PIN 2

int timer1_counter;
bool previous_read;
int count = 0;

void setup(){
  pinMode(INT_PIN, INPUT_PULLUP);
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
  attachInterrupt(digitalPinToInterrupt(INT_PIN),
                  ISR_Callback, RISING);
}

void loop(){
  bool current_read = digitalRead(INT_PIN);
}

void ISR_Callback(){
  count++;
  Serial.println(count);
}
