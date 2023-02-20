#include "camper_state.h"


//LIGHTS_PIN, GAS_PIN, WATER_PIN, WATER_BTN, LIGHTS_BTN, GAS_BTN
ControlPanel::ControlPanel(CamperState *_state): state(_state), water_pin(WATER_PIN), lights_pin(LIGHTS_PIN), gas_pin(GAS_PIN), water_btn(WATER_BTN), lights_btn(LIGHTS_BTN), gas_btn(GAS_BTN){};

void ControlPanel::update_LEDs(){
    digitalWrite(water_pin, state->water_on);
    digitalWrite(lights_pin, state->lights_on);
    digitalWrite(gas_pin, state->gas_on);
};

PanelButtons::PanelButtons(ControlPanel panel): lights(panel.lights_btn), gas(panel.gas_btn), water(panel.water_btn){
        lights.setDebounceTimeout(100);
        gas.setDebounceTimeout(100);
        water.setDebounceTimeout(100);
};

CamperState::CamperState():roof_fans_on(0), temperature_inside(0), temperature_outside(0), water_temp(0), grid_connected(0), gas_on(0), lights_on(0), water_on(0), engine_on(0), lte_signal(0), gps_signal(0){}


void CamperState::to_json(char *json_string){
  StaticJsonDocument<JSON_SIZE> json;
  json["gas_on"] = gas_on;
  json["water_on"] = water_on;
  json["lights_on"] = lights_on;
  json["water_temp"] = water_temp;

  json["roof_fans_on"] = 0;
  json["temperature_inside"] = 0.0;
  json["temperature_outside"] = 0.0;
  json["grid_connected"] = 0;
  json["engine_on"] = 0;
  json["lte_signal"] = 0;
  json["gps_signal"] = 0;

  char payload[JSON_SIZE*2];
  serializeJson(json, payload);
  strncpy(json_string, payload, JSON_SIZE);
}

void setup_leds(ControlPanel *panel){
    pinMode(panel->gas_pin, OUTPUT);
    pinMode(panel->water_pin, OUTPUT);
    pinMode(panel->lights_pin, OUTPUT);
}
