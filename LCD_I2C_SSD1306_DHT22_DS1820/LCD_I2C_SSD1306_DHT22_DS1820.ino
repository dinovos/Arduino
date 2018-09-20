#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include<DHT.h>
#include<OneWire.h>
#include<DallasTemperature.h>

#define ONEWIRE 3 //External temperature sensor PIN 3
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

DHT dht(2, DHT22);
OneWire ourWire(ONEWIRE);

DallasTemperature sensor(&ourWire);

float hum;
float temp;
float temp1;
const int button = 4;
int buttonState = 1;
int brojac = 0;
float minTempDHT = 1000;
float maxTempDHT = -1000;
float minTempDS = 1000;
float maxTempDS = -1000;

//pozdravna poruka
void printWelcome(String message) {
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(20, 0);
  display.println(message);
  display.display();
}

//pozdravna poruka2
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

//dohvaca podatke sa DHT22 za prikaz na pocetnom zaslonu
void getValuesDHT22() {
  display.setTextSize(1);
  display.setCursor(5, 0);
  display.println("T: ");

  display.setCursor(65, 0);
  display.println("Hum: ");

  hum = dht.readHumidity();
  temp = dht.readTemperature();

  display.setCursor(25, 0);
  display.println(temp);

  display.setCursor(95, 0);
  display.println(hum);

}

void getValuesOnlyDHT22() {
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.println("T: ");

  display.setCursor(0, 15);
  display.println("Hum: ");

  hum = dht.readHumidity();
  temp = dht.readTemperature();

  display.setCursor(25, 0);
  display.println(temp);

  display.setCursor(50, 15);
  display.println(hum);

}

//dohvaca podatke sa DS1820 za prikaz na pocetnom zaslonu
void getValueExternal() {
  display.setTextSize(1);
  sensor.requestTemperatures();
  temp1 = sensor.getTempCByIndex(0);
  display.setCursor(5, 15);
  display.println("Ext T: ");
  display.setCursor(50, 15);
  display.println(temp1);
}

void getValueExternalOnly() {
  display.setTextSize(2);
  sensor.requestTemperatures();
  temp1 = sensor.getTempCByIndex(0);
  display.setCursor(5, 0);
  display.println("Ext probe: ");
  display.setCursor(5, 15);
  display.println(temp1);
}

//prikaz min i max temp dohvacene sa DHT22
void getMinMaxDHT() {

  minTempDHT = min(minTempDHT, dht.readTemperature());
  maxTempDHT = max(maxTempDHT, dht.readTemperature());
  
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Min: ");
  display.setCursor(0, 15);
  display.println("Max: ");

  display.setCursor(35,0);
  display.println(minTempDHT);

  display.setCursor(35,15);
  display.println(maxTempDHT);

  display.setCursor(100, 15);
  display.println("DHT");
}


void getMinMaxDS() {

  sensor.requestTemperatures();
  minTempDS = min(minTempDS,sensor.getTempCByIndex(0));
  maxTempDS = max(maxTempDS,sensor.getTempCByIndex(0));
  
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Min: ");
  display.setCursor(0, 15);
  display.println("Max: ");

  display.setCursor(35,0);
  display.println(minTempDS);

  display.setCursor(35,15);
  display.println(maxTempDS);

  display.setCursor(100, 15);
  display.println("DS");
}


void setup() {

  pinMode(button, INPUT);

  Serial.begin(9600);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  dht.begin();
  sensor.begin();

  display.clearDisplay();
  display.display();

  printWelcome("Welcome");
  printWelcome2("Sensor test");
}

void loop() {

  //dohvati pritisak gumba
  buttonState = digitalRead(button);
  Serial.println(buttonState);

  if (buttonState == LOW) {
    delay(600);
    brojac++;
  }

  switch (brojac) {
    case 0:
      //prikaz podataka sa obje sonde
      display.clearDisplay();
      getValuesDHT22();
      getValueExternal();
      display.display();
      break;
    case 1:
      //prikaz podataka sa DHT22
      display.clearDisplay();
      getValuesOnlyDHT22();
      display.display();
      break;
    case 2:
      //prikaz podataka sa DS1820
      display.clearDisplay();
      getValueExternalOnly();
      display.display();
      break;
    case 3:
      //prikaz min i max temp sa DHT22
      display.clearDisplay();
      getMinMaxDHT();
      display.display();
      break;
    case 4:
      //prikaz min i max temp sa DS1820
      display.clearDisplay();
      getMinMaxDS();
      display.display();
      break;
    case 5:
      brojac = 0;
      break;
  }





}
