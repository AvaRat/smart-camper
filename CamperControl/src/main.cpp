#include "SPI.h"
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

void SPI_setup(){
  // initialize the bus for a device on pin 4

  SPI.begin();
  //SPI.setClockDivider(SPI_CLOCK_DIV8); //divide the clock by 8
  
  Serial.println("Hello I'm SPI Mega_Master");
}


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
  SPI_setup();

  Serial.println("PINs SETUP");
  panel.setup();
  panel.update_relays();
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
    
     digitalWrite(SS, LOW); // enable Slave Select
     char str[32] = "elo elo 320";
    // send test string
    for(int i=0; i< sizeof(str); i++) {
      SPI.transfer( str [i] );
    }
    digitalWrite(SS, HIGH); // disable Slave Select
    delay(500);
  }
  panel.handle_loop();
  //delay(50);
  panel.update_relays();
}