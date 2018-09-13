//pins Ultrasonic sensor
const int trigPin = 6;
const int echoPin = 7;

//Ultrasonic variables
long duration;
int distance;
const int Max = 200;

#include<Wire.h>
#include<LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F,20,4); //lcd address 0x3F

void Ultrasonic(){
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
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Udaljenost (cm):");
lcd.setCursor(0,1);
if(distance < Max){
lcd.print(distance);
delay(150);  
}else{
lcd.print("Max");
delay(150);  
}

}

void setup(){
  //setup ultrasonic variables
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  //setup lcd
  lcd.init();
  lcd.backlight();
  lcd.setCursor(2,0);
  lcd.print("Welcome");
  delay(1000);
}

void loop(){
  Ultrasonic();
}

