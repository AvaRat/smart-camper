#include <Arduino.h>
#include "config.h"

class CbeWaterSensor{
    public:
    //pins used
    int white;
    int bronze;
    int yellow;
    int green;
    double tank_level;

    CbeWaterSensor();
    void setup();
    void handle_loop();
};