#include "control_panel.h"

//LIGHTS_PIN, GAS_PIN, WATER_PIN, WATER_BTN, LIGHTS_BTN, GAS_BTN
ControlPanel::ControlPanel(CamperState *_state): state(_state), lights_button(LIGHTS_BTN), 
        gas_button(GAS_BTN), water_button(WATER_BTN), gas_heating_button(GAS_HEATING_BTN), went_button(WENT_BTN), 
        water_heating_button(WATER_HEATING_BTN), //battery_heating_button(BATTERY_HEATING_BTN),
        water_pin(RELAY_IN_1), lights_pin(RELAY_IN_3), gas_pin(RELAY_IN_2),
        went_pin(RELAY_IN_5), gas_heating_pin(RELAY_IN_4), water_heating_pin(RELAY_IN_6), battery_heating_pin(RELAY_IN_7),
        enable(0)
{

    //main_switch.setDebounceTimeout(DEBOUNCE_TIME);

    lights_button.setDebounceTimeout(DEBOUNCE_TIME);
    lights_button.invertReading();
    gas_button.setDebounceTimeout(DEBOUNCE_TIME);
    gas_button.invertReading();
    water_button.setDebounceTimeout(DEBOUNCE_TIME);
    water_button.invertReading();

    gas_heating_button.setDebounceTimeout(DEBOUNCE_TIME);
    water_heating_button.setDebounceTimeout(DEBOUNCE_TIME);
    went_button.setDebounceTimeout(DEBOUNCE_TIME);
    //battery_heating_button.setDebounceTimeout(DEBOUNCE_TIME);
};


void ControlPanel::update_relays(){
    digitalWrite(water_pin, !state->water_on);
    digitalWrite(lights_pin, !state->lights_on);
    digitalWrite(gas_pin, !state->gas_on);
    digitalWrite(went_pin, !state->roof_fans_on);
    digitalWrite(gas_heating_pin, !state->gas_heating_on);
    digitalWrite(water_heating_pin, !state->water_tank.heating_on);
    digitalWrite(battery_heating_pin, !state->main_battery.heating_on);
};

void ControlPanel::setup(){
    pinMode(MAIN_BTN, INPUT_PULLUP);
    pinMode(BATTERY_HEATING_BTN, OUTPUT);

    pinMode(gas_pin, OUTPUT);
    pinMode(water_pin, OUTPUT);
    pinMode(lights_pin, OUTPUT);
    pinMode(went_pin, OUTPUT);
    pinMode(gas_heating_pin, OUTPUT);
    pinMode(water_heating_pin, OUTPUT);
    pinMode(battery_heating_pin, OUTPUT);
}

void ControlPanel::shutdown_all(){
    state->all_off();
}

void ControlPanel::handle_loop(){
    if(digitalRead(MAIN_BTN) == 1){
        enable = 1;
        digitalWrite(BATTERY_HEATING_BTN, 1);

        if(water_button.onPressed()){
            state->water_on = !state->water_on;
        }
        if(gas_button.onPressed()){
            state->gas_on = !state->gas_on;
        }
        if(lights_button.onPressed()){
            state->lights_on = !state->lights_on;
        }
        if(gas_heating_button.onPressed()){
            state->gas_heating_on = !state->gas_heating_on;
        }
        if(went_button.onPressed()){
            state->roof_fans_on = !state->roof_fans_on;
        }
        if(water_heating_button.onPressed()){
            state->water_tank.heating_on = !state->water_tank.heating_on;
    }
/*    if(battery_heating_button.onPressed()){
        state->main_battery.heating_on = !state->lights_on;
    }
*/
    }
    else{
        digitalWrite(BATTERY_HEATING_BTN, 0);
        enable = 0;
        state->all_off();
    }
}
