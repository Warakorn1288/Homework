#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET   -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int sensorPin  = A0;
int sensorValue = 0;
String serialcom;
void setup() {
  pinMode(sensorPin, OUTPUT);
  pinMode(sensorValue, INPUT);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c); //initialize I2C addr 0x3c
  display.clearDisplay(); // clears the screen and buffer
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.display();
  Serial.begin(9600);
}
void loop() {
  sensorValue = analogRead(sensorPin);
  //Serial.print(" Send ");
  Serial.print(sensorValue);
  serialcom = Serial.readString();
  display.clearDisplay();
  display.setCursor(44, 28);
  display.println("Recieve: ");
  display.setCursor(44, 15);
  display.print(serialcom);
  display.display();
  delay(500);
}
