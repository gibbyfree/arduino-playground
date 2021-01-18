#include <Arduino.h>
#include <stdlib.h> 

int INPUT_PIN = 2;
int RED_LED = 8;
int GREEN_LED = 7;
int DELAY_PUSH = 200;
int DELAY_FLICKER = 100;
int DELAY_PULSE = 150;
int DELAY_TWEEN = 50;
bool cleared = false;
int val;

void setup() {
  pinMode(INPUT_PIN, INPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  Serial.begin(9600);
}

void flicker(int LED_1, int LED_2) {
  for(int i = 0; i < 20; i++) { // 2 seconds
      digitalWrite(LED_1, HIGH);
      delay(DELAY_FLICKER);
      digitalWrite(LED_1, LOW);
      delay(DELAY_FLICKER);
      digitalWrite(LED_2, HIGH);
      delay(DELAY_FLICKER);
      digitalWrite(LED_2, LOW);
    }
}

void pulse(int LED) {
  for(int i = 0; i < 15; i++) { // 2 seconds
    digitalWrite(LED, HIGH);
    delay(DELAY_PULSE);
    digitalWrite(LED, LOW);
  }
}

void loop() {
  cleared = false;
  val = digitalRead(INPUT_PIN);
  
  delay(DELAY_PUSH);
  if(val == 1) {
    // Alternate lighting rapidly
    flicker(RED_LED, GREEN_LED);

    int result = rand() % 2;
    int chosenLED;

    if(result == 0) { // red
      chosenLED = RED_LED;
    }
    else if(result == 1) { // green
      chosenLED = GREEN_LED;
    }

    delay(DELAY_TWEEN);

    pulse(chosenLED);

    // Result remains illuminated until reset
    while(!cleared) {
      digitalWrite(chosenLED, HIGH);

      val = digitalRead(INPUT_PIN);

      if(val == 1) {
        digitalWrite(chosenLED, LOW);
        cleared = true;
      }
    }

  }
  else {
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
  }
}