from electric_car import ElectricCar

my_tesla = ElectricCar('tesla', 'model s', 2016, 100)
print(my_tesla.get_descriptive_name())
my_tesla.describe_battery()
my_tesla.fill_gas_tank(50)
#my_tesla.read_gas_tank()
