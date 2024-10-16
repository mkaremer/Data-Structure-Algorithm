class Car:
    def __init__(self, make, model, year) -> None:
        self.make = make
        self.model = model
        self.year = year
    
    def display_info(self):
        print(f"This car is a {self.year} {self.make}")