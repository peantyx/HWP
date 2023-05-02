#include <LiquidCrystal.h>

// LCD Connection
#define R_S 8
#define E   9
#define DB4 10
#define DB5 11
#define DB6 12
#define DB7 13

// LCD Defines
#define NUM_CHAR 20
#define NUM_LINES 4

//variables for serial communication
#define SERIAL_COMSPEED 9600
#define SERIAL_DELAY_MS 1000

// Define the LCD screen
LiquidCrystal lcd(R_S, E, DB4, DB5, DB6, DB7);

//LED & BUTTON Connection
#define LED_1 2
#define LED_2 3
#define LED_3 4
#define LED_4 5
#define LED_5 6
#define LED_6 7
#define BUTTON A0

// Global variables
#define REFERENCE_VOLTAGE 3.3

int lastState = LOW;
int currentState;
int pressed;

const int lst[6] = { 2, 3, 4, 5, 6, 7 };
const String lst_color[6] = {"gruen", "gruen", "gelb ", "gelb ", "rot  ", "rot  "};
int button_counter = 0;
String aktuelle_Farbe;

//Timervariablen für Button-Press
unsigned long startTime = 0;
unsigned long currentTime = 0;
int duration = 100;

//Timervariablen für Blinkfrequenz
unsigned long startTime2 = 0;
int LED_status = HIGH;



void setup() {
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(LED_4, OUTPUT);
  pinMode(LED_5, OUTPUT);
  pinMode(LED_6, OUTPUT);
  pinMode(BUTTON, INPUT);
  // LCD has 4 lines with 20 chars
  lcd.begin(NUM_CHAR, NUM_LINES);
}


void loop() {

  //hier ist das Map von dem Potientometerwerten auf die gewünschte Frequenz... Bin mir aber auch nicht ganz sicher
  byte duration2 = map(analogRead(A1), 0, 1023, 500, 10);
  // Read both digital and analog value of current Button
  currentState = digitalRead(BUTTON);
  int currentState2 = analogRead(BUTTON);

  // Switch LED Color with Button S1
  if (currentState != lastState){
    currentTime = millis();
  }
  if ((millis() - currentTime) > duration){
    if (currentState != pressed){
      pressed = currentState;
      if (pressed == LOW) {
        //Now we only switch colors, if S1 was pressed, specifically.
        if (currentState2 <= 50 && currentState2 >= 0){
          digitalWrite(lst[button_counter], LED_status);
          aktuelle_Farbe = lst_color[button_counter];
          for (int i = 0; i < 6; i++){
            if (i == button_counter){
            continue;
          }
          digitalWrite(lst[i], LOW);
        }
        button_counter++;
        button_counter %= 6;
        }
      }
    }
  }
  lastState = currentState;

  // Print everything on LCD
  lcd.setCursor(0, 0);
  lcd.print("ANALOG 0: ");
  float value = analogRead(BUTTON)*REFERENCE_VOLTAGE/1023.00;
  lcd.print(value);
  lcd.print("V");

  lcd.setCursor(0,1);
  lcd.print("Button: ");
  
  if (analogRead(BUTTON) <= 50 && analogRead(BUTTON) >= 0){
    lcd.print("S1");
    //Serial.println("Button: S1");
  }
  if (analogRead(BUTTON) <= 1023 && analogRead(BUTTON) >= 1000){
    lcd.print("S-");
  }
  if (analogRead(BUTTON) <= 250 && analogRead(BUTTON) >= 230){
    lcd.print("S2");
    //Serial.println("Button: S2");
  }
  if (analogRead(BUTTON) <= 500 && analogRead(BUTTON) >= 310){
    lcd.print("S3");
    //Serial.println("Button: S3");
  }
  if (analogRead(BUTTON) <= 700 && analogRead(BUTTON) >= 510){
    lcd.print("S4");
    //Serial.println("Button: S4");
  }
  if (analogRead(BUTTON) <= 900 && analogRead(BUTTON) >= 710){
    lcd.print("S5");
    //Serial.println("Button: S5");
  }

  //delay(SERIAL_DELAY_MS);
  // NOTE: If you update only parts of the screen, don't use lcd.clear.
  // Set the cursor to the line and column to be updated and override existing chars.
  delay(100);
  lcd.setCursor(0,2);
  lcd.print(aktuelle_Farbe);

  lcd.setCursor(0,3);
  lcd.print(duration2);
}
