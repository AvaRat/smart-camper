#include <OneWire.h>
#include <DallasTemperature.h>
#include <Arduino.h>
#include "camper_state.h"
#include "control_panel.h"
#include "config.h"
#include "cbe_water_sensor.h"

// GPIO where the DS18B20 is connected to 
float t = 0.0;
float h = 0.0; 

OneWire oneWire(ONE_WIRE_PIN);
DallasTemperature sensors(&oneWire);


// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;    // will store last time DHT was updated

// Updates DHT readings every 10 seconds
const long interval = 5000;  

CamperState state;
ControlPanel panel(&state);
CbeWaterSensor cbe;

void setup()
{
  Serial.begin(9600);
  Serial2.begin(9600);

  Serial.println("elo");
  Serial2.println("elo 2");

  //while(!Serial1.available()){}

  Serial.println("PINs SETUP");
  panel.setup();
  panel.update_LEDs();
  pinMode(AC_230_PIN, INPUT);

  sensors.begin();
  cbe.setup();
}

float water_temp = 0.0;
float room_temp = 0.0;
float outside_temp = 0.0;
float battery_temp = 0.0;

void loop(){  
  unsigned long currentMillis = millis();
  // read from port 1, send to port 0:




  // Every X number of seconds (interval = 10 seconds) 
  // it publishes a new MQTT message
  if (currentMillis - previousMillis >= interval) {
    // Save the last time a new reading was published
    previousMillis = currentMillis;
    
    sensors.requestTemperatures(); 
    water_temp = sensors.getTempCByIndex(0);
    room_temp = sensors.getTempCByIndex(1);
    outside_temp = sensors.getTempCByIndex(2);
    battery_temp = sensors.getTempCByIndex(3);

    state.water_temp = sensors.getTempCByIndex(0);
    state.temperature_inside = sensors.getTempCByIndex(1);
    state.temperature_outside = sensors.getTempCByIndex(2);
    state.main_battery.temperature = sensors.getTempCByIndex(3);
    state.grid_connected = digitalRead(AC_230_PIN);


    cbe.handle_loop();
    char msg[JSON_SIZE];
    state.to_json(msg);
    Serial.println(msg);
    if(Serial2.availableForWrite()){
      Serial2.write(msg);
      Serial.println("msg out");
      Serial2.flush();
    }
  }
  panel.handle_loop();
  //delay(50);
  panel.update_LEDs();
}