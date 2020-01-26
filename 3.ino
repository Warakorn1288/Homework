void setup()
{
  DDRD = 0b11111100;
  DDRB = 0b00000011;
}
int a=0,b=0,c=0;
void loop()
{
  int L = 0b00001000; //pin10
  int R = 0b00000100; //pin11
  while((a<6) && (a>=0) && (c==0)){ //start at PD left
    PINB = PINB & 0b00001100;
    PORTD = 0b00000100<<a;
    if((PINB == L) && (a>0)){a--;delay(200);}
    if((PINB == L) && (a==0)){a=6;c=1;delay(200);PORTD=0;}
    if((PINB == R) && (a!=5)){a++;delay(200);PORTD=0;}
    if((PINB == R) && (a==5)){a=6;c=0;delay(200);PORTD=0;}
  }
  while((a>=6) && (b<2) && (c==0)){ //start at PB left
    PINB = PINB & 0b00001100;
    PORTB = 0b00000001<<b;
    if((PINB == L) && (b>0)){b--;delay(200);}
    if((PINB == L) && (b==0)){a=0;c=2;delay(200);PORTB=0;}
    if((PINB == R) && (b!=1)){b++;delay(200);PORTB=0;}
    if((PINB == R) && (b==1)){a=0;b=0;c=0;delay(200);PORTB=0;}
  }
  while((a>=6) && (b<2) && (c==1)){ //start at PB right
    PINB = PINB & 0b00001100;
    PORTB = 0b00000010>>b;
    if((PINB == R) && (b>0)){b--;delay(200);}
    if((PINB == R) && (b==0)){a=0;c=0;delay(200);PORTB=0;}
    if((PINB == L) && (b!=1)){b++;delay(200);PORTB=0;}
    if((PINB == L) && (b==1)){a=0;b=0;c=2;delay(200);PORTB=0;}
  }
  while((a<6) && (a>=0) && (c==2)){ //start at PD right
    PINB = PINB & 0b00001100;
    PORTD = 0b10000000>>a;
    if((PINB == R) && (a>0)){a--;delay(200);}
    if((PINB == R) && (a==0)){a=6;c=0;delay(200);PORTD=0;}
    if((PINB == L) && (a!=5)){a++;delay(200);PORTD=0;}
    if((PINB == L) && (a==5)){a=6;c=1;delay(200);PORTD=0;}
  }
}
