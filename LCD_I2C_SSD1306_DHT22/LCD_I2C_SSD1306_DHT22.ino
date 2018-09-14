#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include<DHT.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

DHT dht(2, DHT22);

float hum;
float temp;

void printWelcome(String message) {
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(20, 0);
  display.println(message);
  display.display();
}

void printWelcome2(String message) {
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(20, 20);
  display.println(message);
  display.display();

  for (int i = 88; i <= 96; i = i + 4) {
    display.setCursor(i, 20);
    display.print(".");
    display.display();
    delay(400);
  }
}

void getValuesDHT22() {
  display.clearDisplay();
  display.setCursor(5, 0);
  display.println("T1: ");
  display.setCursor(65, 0);
  display.println("Hum: ");
    
  hum = dht.readHumidity();
  temp = dht.readTemperature();
  
  display.setCursor(25, 0);
  display.println(temp);

  display.setCursor(90, 0);
  display.println(hum);
  
  display.display();
  delay(300);
}

void setup() {
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  dht.begin();

  display.clearDisplay();
  display.display();

  printWelcome("Welcome");
  printWelcome2("Sensor test");
}

void loop() {
  getValuesDHT22();
}
