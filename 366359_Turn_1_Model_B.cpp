#include <Arduino.h>
#include <esp_sleep.h>

// Define the pin connected to the button
const int buttonPin = 32;

// Define the pin connected to the LED
const int ledPin = 2;

// Define the time to sleep in seconds
const int sleepTime = 5;

void setup() {
  // Initialize the serial communication
  Serial.begin(115200);

  // Configure the button pin as an input
  pinMode(buttonPin, INPUT);

  // Configure the LED pin as an output
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Check if the button is pressed
  if (digitalRead(buttonPin) == HIGH) {
    // Turn on the LED
    digitalWrite(ledPin, HIGH);
    Serial.println("Button pressed, device active.");

    // Perform any necessary tasks here
    delay(1000);

    // Turn off the LED
    digitalWrite(ledPin, LOW);
    Serial.println("Device inactive, entering deep sleep.");
  }

  // Enter deep sleep mode
  esp_sleep_enable_timer_wakeup(sleepTime * 1000000);
  Serial.println("Entering deep sleep...");
  esp_deep_sleep_start();
}
