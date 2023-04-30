// Include LCD functions:
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

// Global variables
#define INPUT_PIN A0
#define REFERENCE_VOLTAGE 3.3

// Define the LCD screen
LiquidCrystal lcd(R_S, E, DB4, DB5, DB6, DB7);

void setup(){
  // LCD has 4 lines with 20 chars
  lcd.begin(NUM_CHAR, NUM_LINES);
}

void loop(){
  
  lcd.setCursor(0, 0);
  lcd.print("ANALOG 0: ");
  int input_val = analogRead(INPUT_PIN);
  float voltage = input_val*REFERENCE_VOLTAGE/1023.00;
  lcd.print(voltage);
  lcd.print("V");

  delay(100);

  lcd.setCursor(0,1);
  lcd.print("Button: ");
  // If we ask the input_val every time again, it might be possible change at a false time
  // Also we save computing time, when just asking for the input_val one time
  if (input_val <= 50 && input_val >= 0){lcd.print("S1");}
  if (input_val <= 1023 && input_val >= 1000){lcd.print("S-");}
  if (input_val <= 250 && input_val >= 230){lcd.print("S2");}
  if (input_val <= 500 && input_val >= 310){lcd.print("S3");}
  if (input_val <= 700 && input_val >= 510){lcd.print("S4");}
  if (input_val <= 900 && input_val >= 710){lcd.print("S5");}

  delay(100);
  // NOTE: If you update only parts of the screen, don't use lcd.clear.
  // Set the cursor to the line and column to be updated and override existing chars.
}
