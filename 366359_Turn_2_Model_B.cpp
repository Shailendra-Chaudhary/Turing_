#include <Arduino.h>
#include <esp_sleep.h>

// Define the pin connected to the button
const int buttonPin = 32;

// Define the light sleep duration in microseconds (1 second = 1000000 microseconds)
const int lightSleepDuration = 1000000;  // 1 second

void setup() {
  // Initialize the serial communication
  Serial.begin(115200);
  
  // Configure the button pin as an input
  pinMode(buttonPin, INPUT);

  // Enable light sleep mode
  esp_sleep_enable_light_sleep_timer_wakeup(lightSleepDuration);
}

void loop() {
  // Check if the button is pressed
  if (digitalRead(buttonPin) == HIGH) {
    Serial.println("Button pressed, device active.");
    // Perform any necessary tasks here
    delay(1000);
  } 
  else {
    // Enter light sleep mode
    Serial.println("Entering light sleep...");
    esp_sleep_start();
  }
} 
