class Dog():

    def __init__(self, name, age):
        self.name = name
        self.age = age
    
    def sit(self):
        print(self.name.title() + " is now sitting.")

    def roll_over(self):
        print(self.name.title() + " rolled over!")


yahoo = Dog("yahoo", 8)
print("My dog's name is " + yahoo.name.title() + ".")
print("My dog is " + str(yahoo.age) + " years old.")
yahoo.sit()
yahoo.roll_over()
