#include "cbe_water_sensor.h"


CbeWaterSensor::CbeWaterSensor(): white(CBE_WHITE_PIN), yellow(CBE_YELLOW_PIN), bronze(CBE_BRONZE_PIN), green(CBE_GREEN_PIN) {}

void CbeWaterSensor::setup(){
    pinMode(white, OUTPUT);
    digitalWrite(white, HIGH);
    pinMode(bronze, INPUT);
    pinMode(green, INPUT);
    pinMode(yellow, INPUT);
}

void CbeWaterSensor::handle_loop(){
    int bronze_read = analogRead(bronze);
    int yellow_read = analogRead(yellow);
    int green_read = analogRead(green);

    if((yellow_read > CBE_THRESHOLD) & (green_read > CBE_THRESHOLD )& (bronze_read > CBE_THRESHOLD)){
        tank_level = 1.0;
    }
    else if((green_read > CBE_THRESHOLD) & (bronze_read > CBE_THRESHOLD)){
        tank_level = 0.66;
    }
    else if(bronze_read > CBE_THRESHOLD){
        tank_level = 0.33;
    }
    else{
        tank_level = 0.0;
    }
    char msg[256];
    sprintf(msg, " reads: a1(bronze): %d\n\ta2(yellow): %d\n\ta3(green): %d\n\n", bronze_read, yellow_read, green_read);
    Serial.println(msg);
    Serial.println(tank_level);
}