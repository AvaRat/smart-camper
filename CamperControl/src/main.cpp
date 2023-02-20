#include <OneWire.h>
#include <DallasTemperature.h>
#include <Arduino.h>
#include "camper_state.h"
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
PanelButtons buttons(panel);
CbeWaterSensor cbe;

void setup()
{
  Serial.begin(9600);
  Serial.println();

  Serial.println("PINs SETUP");
  setup_leds(&panel);
  pinMode(AC_230_PIN, INPUT);

  sensors.begin();
  cbe.setup();
}

float water_temp = 0.0;
float room_temp = 0.0;
float outside_temp = 0.0;
float battery_temp = 0.0;
bool state_changed = 0;

void loop(){  
  unsigned long currentMillis = millis();
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
    state.water_temp = water_temp;
    state.temperature_inside = room_temp;
    state.temperature_outside = outside_temp;
    state.main_battery.temperature = battery_temp;
  
    int grid_connected = digitalRead(AC_230_PIN);
    state.grid_connected = grid_connected;
    Serial.print("Water temp: ");
    Serial.println(water_temp);
    Serial.print("room: ");
    Serial.println(room_temp);
    Serial.print("outside: ");
    Serial.println(outside_temp);
    Serial.print("battery temp: ");
    Serial.println(battery_temp);
    Serial.print("grid connected: ");
    Serial.println(grid_connected);

    cbe.handle_loop();
  }

  if(buttons.water.onPressed()){
    state.water_on = !state.water_on;
    //digitalWrite(panel.water_led, state.water_on);
    state_changed = 1;
  }
  if(buttons.gas.onPressed()){
    state.gas_on = !state.gas_on;
    //digitalWrite(panel.gas_led, state.gas_on);
    state_changed = 1;
  }
  if(buttons.lights.onPressed()){
    state.lights_on = !state.lights_on;
    //digitalWrite(panel.lights_led, state.lights_on);
    state_changed = 1;
  }
  if(state_changed) {
    Serial.print("lights: ");
    Serial.println(state.lights_on);
    Serial.print("gas: ");
    Serial.println(state.gas_on);
    Serial.print("water: ");
    Serial.println(state.water_on);
    //Serial.println(stateJson);
    //networkingHandler.send_state_update(&state);
  }
  state_changed=0;
  panel.update_LEDs();
}