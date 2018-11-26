from car import Car
from battery import Battery

class ElectricCar(Car):
    def __init__(self, make, model, year, battery_size):
        super().__init__(make, model, year)
        #self.battery_size = 70
        self.battery = Battery(battery_size)

    def describe_battery(self):
        #print("This car has a " + str(self.battery_size) + "-kWh battery.")
        self.battery.describe_battery()

    def fill_gas_tank(self, gas_tank):
        print("This car doesn't need a gas tank!")