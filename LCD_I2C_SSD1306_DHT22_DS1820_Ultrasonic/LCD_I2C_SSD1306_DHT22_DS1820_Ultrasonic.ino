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

long duration;
int distance;
const int Max = 200;
const int trigPin = 6;
const int echoPin = 7;

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

void getValueExternal() {
  sensor.requestTemperatures();
  temp1 = sensor.getTempCByIndex(0);
  display.setCursor(5,11);
  display.println("Ext T: ");
  display.setCursor(50,11);
  display.println(temp1);
}

void getValueUltrasonic(){
// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance= duration*0.034/2;
// Prints the distance on LCD

display.setCursor(5,22);
display.print("Dist (cm):");

display.setCursor(70,22);
if(distance < Max){
display.println(distance);
}else{
display.println("Max"); 
}

}

void setup() {
  Serial.begin(9600);
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  dht.begin();
  sensor.begin();

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  display.clearDisplay();
  display.display();

  printWelcome("Welcome");
  printWelcome2("Sensor test");
}

void loop() {
  display.clearDisplay();
  getValuesDHT22();
  getValueExternal();
  getValueUltrasonic();
  display.display();
}
