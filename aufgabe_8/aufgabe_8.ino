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
// Define the LCD screen
LiquidCrystal lcd(R_S, E, DB4, DB5, DB6, DB7);
//LED & BUTTON Connection
#define BUTTON A0
#define REFERENCE_VOLTAGE 3.3

// If we defined other LEDs we had to do it here
const int lst[6] = { 2, 3, 4, 5, 6, 7 };
const String lst_color[6] = {"gruen", "gruen", "gelb ", "gelb ", "rot  ", "rot  "};
byte button_counter = 0;
String current_color;

//Timervariablen für Button-Press
float frequency; 
float starting_time;
float current_duration;
int duration;
bool button_state;
bool led_state = LOW;
bool current_state = HIGH;


void setup() {
  for (int i = 2; i < 8; i++){
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
  pinMode(BUTTON, INPUT);
  // LCD has 4 lines with 20 chars
  lcd.begin(NUM_CHAR, NUM_LINES);
}


void loop() {
  // Map the analog input TR1 with 10 bit to a defined frequency between 10 and 500 times per minute
  frequency = map(analogRead(A1), 0, 1023, 10, 500);
  // It has to be the some time on and off so divide by 2
  duration = 6000 /frequency / 2;
  
  // Read both digital and analog value of current Button
  //button_state = digitalRead(BUTTON);
  button_state = analogRead(BUTTON);

  // Switch LED Color with Button S1
  if (button_state <= 50 && button_state > 0){
    // Stop the current state
    digitalWrite(lst[button_counter], LOW);

    // Do the bouncing light
    // For readability I put the up and downbouncing in one loop (goes from 2 to 7 and backwards)
    for (int i = -5; i < 6; i++){
      digitalWrite(lst[7-abs(i)], HIGH);
      delay(duration);
      digitalWrite(lst[i], LOW);
    }
    // Reenter the previous state
    digitalWrite(lst[button_counter], HIGH);


    // Check, if we already pushed
    if (current_state == HIGH){
      starting_time = millis();
      // Stop old LED
      digitalWrite(lst[button_counter], LOW);
      // Choose new LED
      button_counter++;
      button_counter %= 6;
      led_state = true;
      digitalWrite(lst[button_counter], HIGH);
      current_color = lst_color[button_counter];
    }
  }
  else{
    current_state = LOW;
  }
  // Potentially switch off the current LED
  current_duration = millis()-starting_time;
  if (current_duration > duration){
    led_state = !led_state;
    digitalWrite(lst[button_counter], led_state);
    starting_time = millis();
  }

  // Print everything on LCD
  lcd.setCursor(0, 0);
  lcd.print("ANALOG 0: ");
  float button_value = analogRead(BUTTON);
  float voltage = button_value*REFERENCE_VOLTAGE/1023.00;
  lcd.print(voltage);
  lcd.print("V");

  lcd.setCursor(0,1);
  lcd.print("Button: ");

  if (button_value <= 50 && button_value >= 0){lcd.print("S1  ");}
  else if (button_value <= 1023 && button_value >= 1000){lcd.print("S-  ");}
  else if (button_value <= 250 && button_value >= 230){lcd.print("S2  ");}
  else if (button_value <= 500 && button_value >= 310){lcd.print("S3  ");}
  else if (button_value <= 700 && button_value >= 510){lcd.print("S4  ");}
  else if (button_value <= 900 && button_value >= 710){lcd.print("S5  ");}

  lcd.setCursor(0,2);
  lcd.print(duration);

  lcd.setCursor(0,3);
  lcd.print(current_color);

}
