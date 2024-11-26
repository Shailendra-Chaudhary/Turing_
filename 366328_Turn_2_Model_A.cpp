// Libraries required for interfacing with the MAX30100 sensor
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_MAX30100.h>

// Initialize the sensor
Adafruit_MAX30100 pulseSensor;

void setup() {
  Serial.begin(9600);

  // Initialize the sensor
  if (!pulseSensor.begin()) {
    Serial.println("Failed to initialize MAX30100 sensor!");
    while (1);
  }

  Serial.println("MAX30100 sensor initialized.");
}

void loop() {
  // Read the IR LED value which corresponds to the pulse
  uint32_t ir_value = pulseSensor.readIR();

  // Calculate the heart rate based on the IR LED value
  int heartRate = pulseSensor.readPulse();

  // Output the heart rate to the serial monitor
  Serial.print("Heart Rate: ");
  Serial.print(heartRate);
  Serial.println(" BPM");

  // Delay for a second before reading again
  delay(1000);
}
