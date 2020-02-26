#include<ThreeWire.h>
#include<RtcDS1302.h>

#define LED 10

ThreeWire myWire(4,5,2); //IO,SCLK,CE
RtcDS1302<ThreeWire>Rtc(myWire);
int previous_time;

void printDateTime(const RtcDateTime& dt){
  Serial.print(dt.Year(), DEC);
  Serial.print('/');
  Serial.print(dt.Month(), DEC);
  Serial.print('/');
  Serial.print(dt.Day(), DEC);
  Serial.print(' ');
  Serial.print(dt.Hour(), DEC);
  Serial.print('.');
  Serial.print(dt.Minute(), DEC);
  Serial.print('.');
  Serial.print(dt.Second(), DEC);
  Serial.println();

  Serial.print("Total Seconds since 1/1/2000 : ");
  Serial.print(dt.TotalSeconds());
  Serial.println();
}

void setup()
{
  Serial.begin(57600);
  Rtc.Begin();
  RtcDateTime setting_time(2020,2,2,2,0,0);
  // year, month, dayOfMonth, hour, minute, second
  printDateTime(setting_time);
  //Try to comment This line
  Rtc.SetDateTime(setting_time);

  pinMode(LED,OUTPUT);
  Serial.println("Start");

  RtcDateTime now = Rtc.GetDateTime();
  previous_time = now.TotalSeconds();
}


void loop()
{
    RtcDateTime now = Rtc.GetDateTime();
    printDateTime(now);
    //delay(500);
    int a = now.TotalSeconds() - previous_time ;
    if(a<120){
      if(now.TotalSeconds()%2){
        digitalWrite(LED,HIGH);
      }
      else{
        digitalWrite(LED,LOW);
      }
    }
   
    if(a = 120){
      digitalWrite(LED,LOW);
      Serial.println("Stop");
    }
}
