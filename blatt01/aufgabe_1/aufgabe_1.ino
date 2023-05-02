#define LED_PIN 3
#define duration 1000

unsigned long startTime = 0;
bool LED_status = false;

void setup() {
 pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // LED-Blinken mit delay() (Aufgabe_1i)
  /*
  digitalWrite(LED_PIN, HIGH);
  delay(1000);
  digitalWrite(LED_PIN, LOW);
  delay(1000);
  */
  // LED-Blinken mit millis() (Aufgabe_1ii)
  /*Der Vorteil von millis() ist, dass der Arduino
  im Gegensatz zu delay() für die angebebene Zeit 
  nicht blockiert wird. Wir berechnen anhand der
  aktuellen Systemzeit, wann unsere Funktion ausgeführt
  werden soll. Man könnte also theoretisch 
  noch "gleichzeitig" eine andere Funktion ausführen.
  In diesem Fall ist das zwar nicht nötig, weil wir
  nur eine LED blinken lassen, aber in späteren
  Anwendungen könnte das wichtig sein.*/
  
  unsigned long currentTime = millis();
  
  if (currentTime - startTime > duration){
    startTime = currentTime;
    if (LED_status == false){
      digitalWrite(LED_PIN, true);
      LED_status = true;
    }
    else {
      digitalWrite(LED_PIN, false);
      LED_status = false;
    }
  }
}
