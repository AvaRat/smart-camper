#include "control_panel.h"

//LIGHTS_PIN, GAS_PIN, WATER_PIN, WATER_BTN, LIGHTS_BTN, GAS_BTN
ControlPanel::ControlPanel(CamperState *_state): state(_state), water_pin(WATER_PIN), lights_pin(LIGHTS_PIN), gas_pin(GAS_PIN), 
water_button(WATER_BTN), lights_button(LIGHTS_BTN), gas_button(GAS_BTN){
    lights_button.setDebounceTimeout(DEBOUNCE_TIME);
    lights_button.invertReading();
    gas_button.invertReading();
    water_button.invertReading();
    gas_button.setDebounceTimeout(DEBOUNCE_TIME);
    water_button.setDebounceTimeout(DEBOUNCE_TIME);
};

void ControlPanel::update_LEDs(){
    digitalWrite(water_pin, !state->water_on);
    digitalWrite(lights_pin, !state->lights_on);
    digitalWrite(gas_pin, !state->gas_on);
};


void ControlPanel::setup(){
    pinMode(gas_pin, OUTPUT);
    pinMode(water_pin, OUTPUT);
    pinMode(lights_pin, OUTPUT);
}

void ControlPanel::handle_loop(){
    if(water_button.onPressed()){
        state->water_on = !state->water_on;
    }
    if(gas_button.onPressed()){
        state->gas_on = !state->gas_on;
    }
    if(lights_button.onPressed()){
        state->lights_on = !state->lights_on;
    }
}
