#include "camper_state.h"
#include "config.h"

MainBattery::MainBattery(): cell_voltages({3, 3, 3, 4}){
    temperature = 0;
    state_of_charge = 0;
    total_voltage = 12.5;
    charge_on = 0;
    discharge_on = 0;
    heating_on = 0;
}

Solar::Solar():voltage(12.6), current(0.9) {}

WaterTank::WaterTank(): temperature(10.3), level(0.0), heating_on(0) {}

CamperState::CamperState():
water_tank(), solar(), main_battery(),
roof_fans_on(0), temperature_inside(0), temperature_outside(0), water_temp(0), grid_connected(0), gas_on(0), lights_on(0), water_on(0), engine_on(0), lte_signal(0), gps_signal(0){}

void CamperState::all_off(){
    roof_fans_on = 0;
    gas_on = 0;
    lights_on = 0;
    water_on = 0;
    roof_fans_on = 0;
    gas_heating_on = 0;
    water_tank.heating_on = 0;
    main_battery.heating_on = 0;
}

void CamperState::to_json(char *json_string){
  StaticJsonDocument<JSON_SIZE> json;
  json["gas_on"] = gas_on;
  json["water_on"] = water_on;
  json["lights_on"] = lights_on;
  json["water_temp"] = water_temp;

  json["roof_fans_on"] = 0;
  json["temperature_inside"] = temperature_inside;
  json["temperature_outside"] = temperature_outside;
  json["grid_connected"] = grid_connected;
  json["engine_on"] = 0;
  json["lte_signal"] = 0;
  json["gps_signal"] = 0;

  char payload[JSON_SIZE*2];
  serializeJson(json, payload);
  strncpy(json_string, payload, JSON_SIZE);
}
