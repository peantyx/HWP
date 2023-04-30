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
#define SERIAL_COMSPEED 9600
#define SERIAL_DELAY_MS 1000

// Define the LCD screen

void setup(){
  // LCD has 4 lines with 20 char
  Serial.begin(SERIAL_COMSPEED);
  Serial.println("Setup done!");
}

void loop(){
  
  float input_val = analogRead(INPUT_PIN);
  if (input_val <= 50 && input_val >= 0){
    Serial.println("Button: S1");
  }
  if (input_val <= 250 && input_val >= 230){
    Serial.println("Button: S2");
  }
  if (input_val <= 500 && input_val >= 310){
    Serial.println("Button: S3");
  }
  if (input_val <= 700 && input_val >= 510){
    Serial.println("Button: S4");
  }
  if (input_val <= 900 && input_val >= 710){
    Serial.println("Button: S5");
  }

  delay(SERIAL_DELAY_MS);
  // NOTE: If you update only parts of the screen, don't use lcd.clear.
  // Set the cursor to the line and column to be updated and override existing chars.
}
