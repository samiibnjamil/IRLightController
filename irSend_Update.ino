#include <IRLibSendBase.h>
#include <IRLib_P01_NEC.h> // Include the NEC protocol for the new library

// IR LED pin
#define IR_LED_PIN 3
uint32_t red = 0x1FEE01F;
uint32_t toggle = 0x1FE48B7;
uint32_t blue = 0x1FE906F;
uint32_t green = 0x1FE10EF;
uint32_t yellow = 0x1FE50AF;
uint32_t bUp = 0x1FE58A7;
uint32_t bDown = 0x1FE7887;
uint32_t warm = 0x1FE20DF;
uint32_t white = 0x1FE609F ;
// Create an instance of the NEC transmitter
IRsendNEC irsend;

unsigned long previousTime = 0;
unsigned long interval = 500; // Time interval in milliseconds

bool isToggled = false; // Track the state of the LED

void setup() {
  // Start the serial communication
  Serial.begin(9600);
}

void loop() {
  //sweepColors();
  int bpm = 156; // Adjust the BPM value as per your requirement
  //strobeLight(bpm);
strobe(bpm);
}


void strobe(int input){
  // Define the IR signal codes
  uint32_t ir_code = toggle;

  // BPM value to use
  
  int bpm = input; // Adjust the BPM value as per your requirement

  // Calculate the time interval based on the current BPM
  interval = 60000 / bpm / 2; // Half of the interval time to toggle the LED

  unsigned long currentTime = millis();
  if (currentTime - previousTime >= interval) {
    previousTime = currentTime; // Update the previous time

    // Toggle the LED state
    isToggled = !isToggled;

    // Send the IR signal using the NEC protocol
    irsend.send(toggle); // Send the NEC signal

    // Display the hex code, BPM, and countdown on the serial monitor
    Serial.print("Sent IR signal: ");
    Serial.println(ir_code, HEX);
    Serial.print("BPM: ");
    Serial.println(bpm);
    unsigned long remainingTime = (interval * 2 - (currentTime - previousTime)) / 1000;
    Serial.print("Countdown: ");
    Serial.println(remainingTime);
  }

}
void sweepColors() {
  // Define color components for each color
  uint8_t red_component, green_component, blue_component;

  // Sweep through the range of colors between red and blue
  for (uint32_t color = red; color <= blue; color++) {
    // Extract color components
    red_component = (color >> 16) & 0xFF;
    green_component = (color >> 8) & 0xFF;
    blue_component = color & 0xFF;

    // Send the IR signal using the NEC protocol
     irsend.send(color);

    // Delay between sending each IR signal
    delay(200); // Adjust delay as needed
  }
}
