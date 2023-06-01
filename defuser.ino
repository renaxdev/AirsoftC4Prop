#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

#define OLED_RESET  -1
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int buzzer = 9;
int red = 8;
int green = 10;
int defuser = 4;
void setup() {

  pinMode(buzzer, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(defuser, OUTPUT);
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)){
    Serial.println(F("SSD1306 allocation failed..."));
    for(;;); //if allocation fails, stop the execution
  }

  display.clearDisplay();
  display.setTextSize(1.5);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(30,13);
  display.println(F("Defuser Kit"));
  display.display();
  delay(1000);
  display.clearDisplay();
  display.setTextSize(1.5);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(30,13);
  display.println(F("Please connect!"));
  display.display();
  delay(3000);
  

}

void loop() {
  display.clearDisplay();
  display.setTextSize(1.5);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(5,5);
  display.println(F("Defusing..."));
  display.display();
  delay(2000);
  beep();
  digitalWrite(red, HIGH);
  clearDisplay("5");
  delay(1000);
  beep();
  digitalWrite(red, LOW);
  digitalWrite(green, HIGH);
  clearDisplay("4");
  delay(1000);
  digitalWrite(red, HIGH);
  digitalWrite(green, LOW);
  clearDisplay("3");
  beep();
  delay(1000);
  digitalWrite(red, LOW);
  digitalWrite(green, HIGH);
  clearDisplay("2");
  beep();
  delay(1000);
  digitalWrite(red, HIGH);
  digitalWrite(green, LOW);
  clearDisplay("1");
  beep();
  delay(1000);
  display.clearDisplay();
  digitalWrite(buzzer, HIGH);
  digitalWrite(defuser, HIGH);
  digitalWrite(red, HIGH);
  digitalWrite(green, HIGH);
  display.setCursor(30,13);
  display.print(F("Defused!"));
  display.display();
  delay(3000);
  digitalWrite(buzzer, LOW);
  while(1){}
  
}

void beep(){
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW);
  delay(200);
}

void clearDisplay(String i){
  display.clearDisplay();
  display.setTextSize(1.5);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(5,5);
  display.println(F("Defusing..."));
  display.setCursor(50,15);
  display.print(i);
  display.display();
}
