const int buttonPin = 5;
const int buzzerPin = 8;
const int redLedPin = 6;
const int greenLedPin = 7;

// Global variables
bool buttonPressed = false;
bool countdownStarted = false;
unsigned long buttonPressTime;
unsigned long countdownStartTime;

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const byte interruptPin = 4;
volatile bool interruptTriggered = false;
unsigned long interruptTime = 0;

void setup() {
  // Initialize pins
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP);
  
  // Attach interrupt to interruptPin
  attachInterrupt(digitalPinToInterrupt(interruptPin), interruptHandler, FALLING);
  
  // Initialize LCD display
  lcd.begin(16, 2);
  lcd.print("Airsoft Bomb");
  lcd.backlight();
}

void loop() {
  bool buttonPressed = digitalRead(buttonPin) == LOW;
  static bool countdownStarted = false;
  static unsigned long countdownStartTime = 0;
  
  // Check if button is pressed and not counting down
  if (buttonPressed && !countdownStarted) {
    lcd.clear();
    lcd.print("Countdown: 60s");
    digitalWrite(greenLedPin, HIGH); // Activate green LED
    tone(buzzerPin, 1000);
    delay(10000); // Wait for button to be held for 10 sec
    noTone(buzzerPin);
    digitalWrite(redLedPin, HIGH); // Activate red LED
    countdownStarted = true;
    countdownStartTime = millis();
  }
  
  // Check if counting down
  if (countdownStarted) {
    unsigned long elapsedTime = millis() - countdownStartTime;
    unsigned long remainingTime = 60000 - elapsedTime;
    if (remainingTime > 0) {
      int seconds = remainingTime / 1000;
      lcd.setCursor(0, 1);
      lcd.print("Time: ");
      lcd.print(seconds);
      lcd.print("s ");
      int buzzerFrequency = 1000 + (60 - seconds) * 50; // Calculate buzzer frequency
      tone(buzzerPin, buzzerFrequency); // Activate buzzer with calculated frequency
      delay(1000);
      noTone(buzzerPin);
    } else {
      lcd.clear();
      lcd.print("Boom!");
      digitalWrite(redLedPin, LOW); // Deactivate red LED
      digitalWrite(greenLedPin, LOW); // Deactivate green LED
      tone(buzzerPin, 2000);
      delay(2000);
      noTone(buzzerPin);
      countdownStarted = false;
    }
  }
  
  // Check if interrupt was triggered
  if (interruptTriggered) {
    // Wait for interrupt to end
    while (digitalRead(interruptPin) == LOW) {
      delay(10);
    }
    
    // Check if interrupt lasted for more than 10 sec
    if (millis() - interruptTime > 1000) {
      countdownStarted = false;
      noTone(buzzerPin);
      lcd.clear();
      lcd.print("Aborted");
      digitalWrite(redLedPin, LOW); // Deactivate red LED
      digitalWrite(greenLedPin, LOW); // Deactivate green LED
    }
    interruptTriggered = false;
  }
}

void interruptHandler() {
  interruptTime = millis();
  interruptTriggered = true;
}
