/* 
  Sketch generated by the Arduino IoT Cloud Thing "Untitled 2"
  https://create.arduino.cc/cloud/things/00cfa2d0-a8ef-442a-8ec3-8f715cab254f 

  Arduino IoT Cloud Variables description

  The following variables are automatically generated and updated when changes are made to the Thing

  float acmeDistance;

  Variables which are marked as READ/WRITE in the Cloud Thing will also have functions
  which are called when their values are changed from the Dashboard.
  These functions are generated with the Thing and added at the end of this sketch.
*/

#include "thingProperties.h"

// Pin definitions
#define TRIG_PIN 2        // HC-SR04 Trig pin
#define ECHO_PIN 3        // HC-SR04 Echo pin

void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);

  // Set trig pin as output and echo pin as input
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500); 

  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
 */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  ArduinoCloud.update();

  // Measure distance using HC-SR04
  long duration;

  // Send a 10us pulse to trigger pin
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Read the echo pin to get duration of pulse
  duration = pulseIn(ECHO_PIN, HIGH);

  // Calculate distance in cm
  acmeDistance = (duration * 0.0343) / 2;

  // Print distance to serial monitor
  Serial.print("Distance: ");
  Serial.print(acmeDistance);
  Serial.println(" cm");

  // Wait before repeating measurements
  delay(2000);
}



/*
  Since AcmeDistance is READ_WRITE variable, onAcmeDistanceChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onAcmeDistanceChange()  {
  // Add your code here to act upon AcmeDistance change
}
