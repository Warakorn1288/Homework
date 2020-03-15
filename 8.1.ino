float brightness = 0;
String buff;
int state;
int pin;
void setup(){
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  Serial.begin(9600);
}

void loop(){
  if (Serial.available() > 0)
  {
    char inByte = Serial.read(); //L1B80
   
    if(inByte == 'L')
    {
      state = 0;
    }
 
 
  if(('0'<= inByte) && (inByte <= '9') && (state == 0))
    {
       if(inByte == '1'){
         pin = 5;
       }
       if(inByte == '2'){
         pin = 6;
       }
    }
         
    if(inByte == 'B'){
      buff = ' ';
      state = 1;
    }
             
    if(('0'<= inByte) && (inByte <= '9') && (state == 1))
     {
         buff += inByte;
     }
         
       if(inByte == 'A')
       {
         brightness = buff.toInt();
         Serial.println(brightness);
         analogWrite(pin,brightness*2.54);
       }
     }
 }
