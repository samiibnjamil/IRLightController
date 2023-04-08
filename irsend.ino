#include <IRremote.h>

// IR LED pin
#define IR_LED_PIN 3

// IR transmitter object
IRsend irsend(IR_LED_PIN);

void setup() {
  // Start the serial communication
  Serial.begin(9600);
}

void loop() {
  // Define the IR signal code
  
uint32_t ir_code[] = {0x1FE48B7,0x1FEE01F,0x1FE906F};
  // Send the IR signal using the NEC protocol
  for(int i=0;i<3;i++){
     irsend.sendNEC(ir_code[i], 32);

    delay(50);
  }
 
  // Display the hex code on the serial monitor
  Serial.print("Sent IR signal: ");
//  Serial.println("1FE48B7", HEX);

  // Wait for 1 second before sending the next signal
  
}
