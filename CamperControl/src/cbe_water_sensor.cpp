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
    int a1 = analogRead(bronze);
    int a2 = analogRead(yellow);
    int a3 = analogRead(green);
    char msg[256];
    sprintf(msg, " reads: a1(bronze): %d\n\ta2(yellow): %d\n\ta3(green): %d\n\n", a1, a2, a3);
    Serial.print(msg);
}