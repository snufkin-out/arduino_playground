#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// screen dimensions
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

// an instance of the SSD1306 display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup(){
  // initialize the display with the I2C address 0x3C
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // stop execution if the display fails to initialize
  }

  display.clearDisplay();        // clear the display
  display.setTextSize(1);        // set text size to 1
  display.setTextColor(SSD1306_WHITE); // set text color to white
}

void displayText(const char* text) {
  display.clearDisplay();        // clear the display
  display.setCursor(0, 0);       // set the cursor to the top-left corner
  display.print(text);           // print the text
  display.display();             // display the text on the screen
}

void loop(){
  displayText("Hello, World!");   
  delay(2000);                   
}
