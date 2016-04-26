/* IR Remote Testing Application
 * Used to check the codes for different functions to be performed by the PanickRover
 * Also used to determine the nature of REPEAT codes
 */

#include <IRremote.h>

int RECV_PIN = 11;
int lastReceived = 0;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  // put your main code here, to run repeatedly:
  if(irrecv.decode(&results)){
    int thisTime = millis();
    int timeGap = thisTime - lastReceived;
    Serial.println(results.value, HEX);
    Serial.println(timeGap);

    lastReceived = thisTime;
    irrecv.resume(); //Receive the next value
  }

}
