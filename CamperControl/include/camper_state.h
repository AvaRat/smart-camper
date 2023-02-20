#ifndef CAMPER_STATE_H
#define CAMPER_STATE_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <RBD_Timer.h>
#include <RBD_Button.h>
#include "config.h"

class MainBattery{
    public:
    double temperature;
    double state_of_charge;
    double cell_voltages[4];
    double total_voltage;
    bool charge_on;
    bool discharge_on;
};

class Solar{
    public:
    double voltage;
    double current;
};

class WaterTank{
    public:
    double temperature;
    double level;
};


class CamperState{
    public:

    WaterTank water_tank;
    Solar solar;
    MainBattery main_battery;
    bool roof_fans_on;
    double temperature_inside;
    double temperature_outside;
    double water_temp;
    bool grid_connected;
    bool gas_on;
    bool lights_on;
    bool water_on;
    bool engine_on;
    bool lte_signal;
    bool gps_signal;
    
    CamperState();
    void update_state();
    void handle_message(char *message, char *topic, size_t len);
    void to_json(char *json_string);
};

class ControlPanel{
    public:
    CamperState *state;
    int water_pin;
    int water_btn;
    int lights_pin;
    int lights_btn;
    int gas_pin;
    int gas_btn;
    ControlPanel(CamperState *state);
    void update_LEDs();
};

class PanelButtons{
    public:
    RBD::Button lights;
    RBD::Button gas;
    RBD::Button water;
    PanelButtons(ControlPanel);
};
void setup_leds(ControlPanel *panel);



#endif