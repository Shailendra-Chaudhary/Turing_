#include <avr/sleep.h>
#include <avr/wdt.h>

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  
  // Set the Watchdog Timer to 8 seconds
  MCUSR &= ~(1 << WDRF); // Clear watchdog reset flag
  wdt_enable(WDTO_8S); // Enable watchdog timer with an 8-second interval
}

void loop() {
  // Perform necessary tasks here
  Serial.println("Device active.");
  delay(1000);

  // Enter Power-Down Sleep mode
  sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_cpu();

  // Watchdog Timer will wake up the device after 8 seconds
}
