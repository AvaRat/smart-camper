from pydantic import BaseModel


class WaterTank(BaseModel):
    temperature: float
    level: float


class BatteryVoltages(BaseModel):
    cell_1: float
    cell_2: float
    cell_3: float
    cell_4: float
    total: float


class Battery(BaseModel):
    temperature: float
    state_of_charge: float
    voltages: BatteryVoltages
    current: float
    charging_on: bool
    discharging_on: bool


class SolarPower(BaseModel):
    voltage: float
    current: float


class CamperState(BaseModel):
    water_tank: WaterTank
    solar: SolarPower
    main_battery: Battery
    roof_fans_on: bool
    temperature_inside: float
    temperature_outside: float
    grid_connected: bool
    gas_enabled: bool
    engine_on: bool
    lte_signal: bool
    gps_signal: bool
