void setup() {
  DDRD = 0b11111100;
  DDRB = 0b00000011;
}

void loop() {
  int i = 0;
  int a = 0b00000100;
  while(i<6){
    PORTD = a;
    if(PINB==0b00000000){
      a = a<<1;
      i++;
      delay(300);
    }
  }
  PORTD = 0b00000000;
  int b = 0b00000001;
  while(i<8){
    PORTB = b;
    if(PINB==0b00000000){
      b = b<<1;
      i++;
      delay(300);
    }
  }
  PORTB = 0b00000000;
}
