/* 
  https://create.arduino.cc/cloud/things/e75efe13-eb5e-432a-86d3-0bf1cd34aaac 
  
Arduino IoT Cloud Variables description

  The following variables are automatically generated and updated when changes are made to the Thing

  float distance;
  CloudTemperatureSensor temperature;
  CloudRelativeHumidity humidity;
  bool present;

  Variables which are marked as READ/WRITE in the Cloud Thing will also have functions
  which are called when their values are changed from the Dashboard.
  These functions are generated with the Thing and added at the end of this sketch.
*/

#include "thingProperties.h"
#include <DHT.h>

// Pin definitions
#define DHTPIN 12         // DHT11 data pin
#define DHTTYPE DHT11     // DHT 11 sensor type
#define TRIG_PIN 2        // HC-SR04 Trig pin
#define ECHO_PIN 3        // HC-SR04 Echo pin

// Create DHT sensor object
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);

    // Initialize DHT sensor
  dht.begin();

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
  present = false;
  if (isnan(humidity) || isnan(temperature)) {
  Serial.println("Failed to read from DHT sensor!");
  }
  else {
  // Update cloud variables
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
  }
  // Measure temperature and humidity

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print("%  Temperature: ");
  Serial.print(temperature);
  Serial.println("C");

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
  distance = (duration * 0.0343) / 2;
  if (distance <65) {
    present = true;
  }

  // Print distance to serial monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Wait before repeating measurements
  delay(2000);
}

/*
  Since Temperature is READ_WRITE variable, onTemperatureChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onTemperatureChange()  {
  // Add your code here to act upon Temperature change
}

/*
  Since Humidity is READ_WRITE variable, onHumidityChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onHumidityChange()  {
  // Add your code here to act upon Humidity change
}



/*
  Since Distance is READ_WRITE variable, onDistanceChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onDistanceChange()  {
  // Add your code here to act upon Distance change
}

/*
  Since Present is READ_WRITE variable, onPresentChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onPresentChange()  {
  // Add your code here to act upon Present change
}
