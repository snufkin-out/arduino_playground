#include <Keypad.h>

// Define the size of the keypad
const byte ROWS = 4; // four rows
const byte COLS = 3; // three columns

// Define the keymap for the keypad
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

// Define the pins for the rows and columns

// weird code because i use a weird keypad off amazon (NON STANDARD MATRIX SOMEHOW)
//https://www.amazon.de/-/en/HALJIA-Keyboard-Membrane-Compatible-Arduino/dp/B08BBXH6NM/ref=sr_1_1?crid=23QWWW2Z7G58E&dib=eyJ2IjoiMSJ9.i6xM5Fcf3EQpW4z8nNSI3kcj459vaP0JcqblpRyu5VZt5DTuGAyFWuMc1PgWA5LrifezBZ2stRFlYYHuV4VKk-AAWTJyW9idmKxIIFSxmJU.L2KVokDyO-iPlQYSRrIjTEmS8TrUxOzXOc_aBRRlmLE&dib_tag=se&keywords=HALJIA+4x3+Matrix+Array+12&qid=1723286694&sprefix=haljia+4x3+matrix+array+12%2Caps%2C110&sr=8-1
byte rowPins[ROWS] = {3, 8, 7, 5};  // Row1 -> Pin 3, Row2 -> Pin 8, Row3 -> Pin 7, Row4 -> Pin 5
byte colPins[COLS] = {4, 2, 6};     // Column1 -> Pin 4, Column2 -> Pin 2, Column3 -> Pin 6

// Create a Keypad object
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600); // Initialize serial communication at 9600 baud
}

void loop() {
  char key = keypad.getKey(); // Get the key that is pressed

  if (key) { // If a key is pressed
    Serial.print("Key pressed: ");
    Serial.println(key); // Print the key value to the serial monitor
  }
}
