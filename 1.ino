void setup() {
  DDRD = 0b11111100;
  DDRB = 0b00000011;
}

void loop() {
  int d = 0b00000100;
  for(int i=0;i<6;i++){
    PORTD = d<<i;
    delay(300);
  }
  PORTD = 0b00000000;
  int b = 0b00000001;
  for(int i=0;i<2;i++){
    PORTB = B<<i;
    delay(300);
  }
  PORTB = 0b00000000;
}
