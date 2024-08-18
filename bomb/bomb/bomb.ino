#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Keypad.h>

// Display configuration
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Keypad configuration
const byte ROWS = 4;
const byte COLS = 3;
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte rowPins[ROWS] = {3, 8, 7, 5};
byte colPins[COLS] = {4, 2, 6};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// LED and Buzzer configuration
const int ledPin = LED_BUILTIN;
const int buzzerPin = 9;

// Timing variables
long startTime;
long remainingTime;
const int initialDelay = 1000; // Initial delay between beeps
const String correctCode = "7355608";
String enteredCode = "";
bool bombActive = false;
bool codeEntered = false;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
}

void displayText(const char* text) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print(text);
  display.display();
}

void displayCountdown(long secondsLeft) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Time Left: ");
  display.print(secondsLeft);
  display.print("s");
  display.display();
}

void beep() {
  tone(buzzerPin, 1000, 100); // Short beep
  delay(100);
  noTone(buzzerPin);
}

void handleBomb() {
  long currentTime = millis();
  long elapsedTime = currentTime - startTime;
  long secondsLeft = (45000 - elapsedTime) / 1000;

  if (elapsedTime <= 45000) { // until 45 seconds
    displayCountdown(secondsLeft);
    int delayTime = map(elapsedTime, 0, 45000, 1000, 50);
    tone(buzzerPin, 600);
    digitalWrite(ledPin, HIGH);
    delay(150);
    noTone(buzzerPin);
    digitalWrite(ledPin, LOW);
    delay(delayTime);
  } else {
    remainingTime = 0;
    for (int i = 0; i < 8; i++) {
      tone(buzzerPin, 1000);
      digitalWrite(ledPin, HIGH);
      delay(50);
      noTone(buzzerPin);
      digitalWrite(ledPin, LOW);
      delay(50);
    }
    displayText("Boom!");
    delay(2000); // Display "Boom!" for 2 seconds
    startTime = millis(); // reset time after "bomb explosion"
    codeEntered = false;
    bombActive = false;
    enteredCode = "";
    displayText("Enter Code:");
  }
}

void loop() {
  if (bombActive) {
    handleBomb();
  } else {
    char key = keypad.getKey();
    if (key) {
      beep();
      enteredCode += key;
      displayText(enteredCode.c_str());

      if (enteredCode.length() == correctCode.length()) {
        if (enteredCode == correctCode) {
          displayText("Bomb Activated!");
          delay(2000); // Display message for 2 seconds
          startTime = millis(); // Start bomb countdown
          bombActive = true;
          enteredCode = ""; // Clear code entry
        } else {
          displayText("Wrong Code!");
          for (int i = 0; i < 3; i++) {
            tone(buzzerPin, 1000, 100); // Rapid beep
            digitalWrite(ledPin, HIGH);
            delay(100);
            noTone(buzzerPin);
            digitalWrite(ledPin, LOW);
            delay(100);
          }
          delay(2000);
          enteredCode = ""; // Clear code entry after wrong attempt
          displayText("Enter Code:");
        }
      }
    }
  }
}
