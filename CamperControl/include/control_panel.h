#include <Arduino.h>
#include <RBD_Timer.h>
#include <RBD_Button.h>
#include "config.h"
#include "camper_state.h"



class ControlPanel{
    // pins connected to pushup buttons
    RBD::Button lights_button;
    RBD::Button gas_button;
    RBD::Button water_button;
    CamperState *state;
    
    public:
    // pins used to control 5V relays and signal (12V) LED
    int water_pin;
    int lights_pin;
    int gas_pin;

    ControlPanel(CamperState *state);
    void setup();
    void update_LEDs();
    void handle_loop();
};
