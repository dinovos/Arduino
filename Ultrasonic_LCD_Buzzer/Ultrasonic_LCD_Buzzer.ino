//pins Ultrasonic sensor
const int trigPin = 6;
const int echoPin = 7;

//Ultrasonic variables
long duration;
int distance;
const int Max = 200;

//Buzzer pin
const int buzzer = 8;

#include<Wire.h>
#include<LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 20, 4); //LCD address 0x3F

void Ultrasonic() {
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
  distance = duration * 0.034 / 2;
  // Prints the distance on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Udaljenost (cm):");
  lcd.setCursor(0, 1);
  if (distance < Max) {
    //Buzzer(distance);     //Buzzer function call
    lcd.print(distance);
  } else {
    lcd.print("Max");
  }
}

void Buzzer(int distance) {
  if (distance > 100) {
    noTone(buzzer);
  }
  if (distance > 50) {
    tone(buzzer, 500);
    delay(200);
    noTone(buzzer);
    delay(200);
  }
  if (distance > 30) {
    tone(buzzer, 500);
    delay(150);
    noTone(buzzer);
    delay(150);
  }
  if (distance > 20) {
    tone(buzzer, 500);
    delay(100);
    noTone(buzzer);
    delay(100);
  }
  if (distance > 10) {
    tone(buzzer, 500);
    delay(50);
    noTone(buzzer);
    delay(50);
  }
  if (distance > 5) {
    tone(buzzer, 500);
  }
}


void setup() {
  //setup buzzer oun
  pinMode(buzzer, OUTPUT);
  //setup ultrasonic variables
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  //setup lcd
  lcd.init();
  lcd.backlight();
  lcd.setCursor(2, 0);
  lcd.print("Welcome");
  delay(1000);
}

void loop() {
  Ultrasonic();
}

