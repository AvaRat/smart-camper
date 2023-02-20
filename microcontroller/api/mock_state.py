from models import *


class MockState:

    def __init__(self):
        water_tank = WaterTank(temperature=10, level=1)
        voltage = BatteryVoltages(cell_1=3.3, cell_2=3.1, cell_3=2.9, cell_4=3.5, total=13.8)
        battery = Battery(temperature=9.5, state_of_charge=0.7, voltages=voltage,
                        current=0, charging_on=True, discharging_on=True)
        solar = SolarPower(voltage=35.2, current=0.2)
        camper_state = CamperState(water_tank=water_tank, solar=solar,
                                main_battery=battery, roof_fans_on=False,
                                temperature_inside=15.1, temperature_outside=-9,
                                grid_connected=False, gas_enabled=False,
                                engine_on=False, lte_signal=False,
                                gps_signal=False)
        self.camper_state = camper_state



