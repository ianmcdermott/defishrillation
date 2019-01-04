
#define USE_ARDUINO_INTERRUPTS true    // Set-up low-level interrupts for most acurate BPM math.
#include <PulseSensorPlayground.h>     // Includes the PulseSensorPlayground Library.   

//  Variables
int PulseSensorPurplePin = 0;        // Pulse Sensor PURPLE WIRE connected to ANALOG PIN 0
int LED13 = 13;   //  The on-board Arduion LED


int Signal;                // holds the incoming raw data. Signal value can range from 0-1024
int Threshold = 550;            // Determine which Signal to "count as a beat", and which to ingore.

float offSet1 = 0;
float offSet2 = 50;
float offSet3 = 180;

PulseSensorPlayground pulseSensor;  // Creates an instance of the PulseSensorPlayground object called "pulseSensor"

// The SetUp Function:
void setup() {
  pinMode(6, OUTPUT);        // pin that will blink to your heartbeat!
  pulseSensor.blinkOnPulse(LED13);
  pinMode(LED13, OUTPUT);        // pin that will blink to your heartbeat!
  Serial.begin(9600);         // Set's up Serial Communication at certain speed.
  pulseSensor.analogInput(0);
  pulseSensor.setThreshold(Threshold);
  if (pulseSensor.begin()) {
    Serial.println("We created a pulseSensor Object !");  //This prints one time at Arduino power-up,  or on Arduino reset.
  }
}

// The Main Loop Function
void loop() {

  Signal = analogRead(PulseSensorPurplePin);  // Read the PulseSensor's value.
  // Assign this value to the "Signal" variable.

  Serial.println(Signal);                    // Send the Signal value to Serial Plotter.
  int myBPM = pulseSensor.getBeatsPerMinute();
  if (myBPM > 30) {
    if (Signal > Threshold) {
      analogWrite(5, int(random(800, 1000)));
      analogWrite(6, int(random(800, 1000)));
      analogWrite(9, int(random(800, 1000)));
      analogWrite(10, HIGH);
      digitalWrite(LED13, HIGH);



      //  if (pulseSensor.sawStartOfBeat()) {            // Constantly test to see if "a beat happened".
      //                      // Print the value inside of myBPM.
      //    digitalWrite(6, HIGH);
      //
      //     digitalWrite(LED13,HIGH);
    } else {
      analogWrite(5, 0);
      analogWrite(6, 0);
      analogWrite(9, 0);
      analogWrite(10, LOW);
      digitalWrite(LED13, LOW);               //  Else, the sigal must be below "550", so "turn-off" this LED.
    }
  } else {
    analogWrite(5, 0);
    analogWrite(6, 0);
    analogWrite(9, 0);
    analogWrite(10, LOW);
    digitalWrite(LED13, LOW);               //  Else, the sigal must be below "550", so "turn-off" this LED.
  }

  delay(5);


}
