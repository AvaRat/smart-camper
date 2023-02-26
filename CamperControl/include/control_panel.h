#include <Arduino.h>
#include <RBD_Timer.h>
#include <RBD_Button.h>
#include "config.h"
#include "camper_state.h"



class ControlPanel{
    // pins connected to pushup buttons
    //RBD::Button main_switch;
    RBD::Button lights_button;
    RBD::Button gas_button;
    RBD::Button water_button;
    RBD::Button gas_heating_button;
    RBD::Button went_button;
    RBD::Button water_heating_button;
    //RBD::Button battery_heating_button;

    CamperState *state;
    
    public:
    // pins used to control 5V relays and signal (12V) LED
    int water_pin = 0;
    int lights_pin;
    int gas_pin;
    int went_pin;
    int gas_heating_pin;
    int water_heating_pin;
    int battery_heating_pin;

    bool enable;
    bool prev_enable;

    ControlPanel(CamperState *state);
    void setup();
    void update_relays();
    void handle_loop();
    void shutdown_all();
};
