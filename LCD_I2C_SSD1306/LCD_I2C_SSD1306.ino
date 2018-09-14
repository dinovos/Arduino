#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

void printWelcome(String message){
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(20,0);
  display.println(message);
  display.display();
}

void printWelcome2(String message){
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(20,20);
  display.println(message);
  display.display();

  for(int i=88; i<= 96; i = i+4){
    display.setCursor(i,20);
    display.print(".");
    display.display();
    delay(400);
  }  
}


void setup() {
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  
  display.clearDisplay();
  display.display();

  printWelcome("Welcome");
  printWelcome2("Sensor test");
  delay(1000);
  display.clearDisplay();
  display.display();

}

void loop() {

}
