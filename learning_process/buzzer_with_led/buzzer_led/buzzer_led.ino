const int ledPin =  LED_BUILTIN; // == 13
const int buzzerPin = 9;

long startTime;
long remainingTime;
int initialDelay = 1000; // Initial delay between beeps

void setup(){
    // DEBUG
    Serial.begin(9600);

    setupLED();
    setupBuzzer();
    startTime = millis(); // initialize start time
}

void setupLED(){
    pinMode(ledPin, OUTPUT);
}

void setupBuzzer(){
    pinMode(buzzerPin, OUTPUT);
}

void bomb() {
    long currentTime = millis();
    long elapsedTime = currentTime - startTime;

    if (elapsedTime <= 45000) { // until 45 seconds
      remainingTime = 45 - (elapsedTime / 1000); // Calculate the remaining time in seconds
      int delayTime = map(elapsedTime, 0, 45000, 1000, 50);  // Maps the elapsed time to a delay range of 1000ms to 100ms
      tone(buzzerPin, 600);
      digitalWrite(ledPin, HIGH);
      delay(150);
      noTone(buzzerPin);
      digitalWrite(ledPin, LOW);
      delay(delayTime);
    } else {
        remainingTime = 0; // timer finished

        // beep 8 times after 45 seconds to simulate "explosion"
        for (int i = 0; i < 8; i++) {
            tone(buzzerPin, 1000);
            digitalWrite(ledPin, HIGH);
            delay(50);
            noTone(buzzerPin);
            digitalWrite(ledPin, LOW);
            delay(50);
        }

        delay(6000);
        startTime = millis(); // reset time after "bomb explosion"
    }
}

void loop(){
    bomb();
}