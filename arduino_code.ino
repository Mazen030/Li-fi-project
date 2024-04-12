#include <LiquidCrystal.h>
#include <LiquidCrystal.h>

#define LDR1pin 9
#define BuzzerPin 8
#define ButtonPin 2

#define onTimeThreshold500 10000
#define onTimeThreshold300 20000
#define buttonPressThreshold 5000

boolean lightOn = false;
boolean buttonPressed = false;

unsigned long startTime;
unsigned long onTime = 0;
unsigned long buttonPressTime = 0;

LiquidCrystal lcd(1, 10, 4, 5, 6, 7);

void buzzBuzzer() {
  digitalWrite(BuzzerPin, HIGH); // Turn on the buzzer
}

void setup() {
  lcd.begin(16, 2);
  pinMode(BuzzerPin, OUTPUT);
  pinMode(ButtonPin, INPUT_PULLUP);
}

void loop() {
  int ldr1Value = digitalRead(LDR1pin);
  int buttonState = digitalRead(ButtonPin);

  // Check if the button is pressed to stop the buzzer permanently
  if (buttonState == HIGH && !buttonPressed) {
    buttonPressTime = millis();
    digitalWrite(BuzzerPin, LOW); // Turn off the buzzer
    buttonPressed = true;
  }

  // Check if the 5-second threshold has passed since the button press
  if (buttonPressed) {
    delay(5000);
    buttonPressed = false;
    buzzBuzzer();
  }

  if (lightOn) {
    // If light state was on, check to see if it went off
    if (ldr1Value == HIGH) {
      onTime = millis() - startTime;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.setCursor(0, 1);

      lightOn = false;

      if (onTime >= 600) {
        lcd.clear();
        lcd.print("MAGNET");
      } else if (onTime >= 400) {
        lcd.clear();
        lcd.print("ULTRASONIC");
      } else if (onTime >= 200) {
        lcd.clear();
        lcd.print("FUME");
      }
            buzzBuzzer();

    }
  } else {
    // If light state was off, see if it has come on
    if (ldr1Value == LOW) {
      startTime = millis();
      lightOn = true;
            buzzBuzzer();

    }
  }

  
}
