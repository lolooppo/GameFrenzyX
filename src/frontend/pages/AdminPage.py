from src.backend import BackEnd
from src.frontend.pages.IPage import IPage
from src.frontend.utils import input_valid, show_menu
from src.frontend.validators.reservables.ReservableValidator import ReservableValidator


class AdminPage(IPage):
    def __init__(self, menu: list, backend: BackEnd):
        self.menu = menu
        self.backend = backend
        self.reservable_validator = ReservableValidator()

    def run(self):
        while True:
            show_menu(self.menu)
            choice = input_valid('Enter choice: ', 1, self.menu)

            if choice == 1:
                print('\n All Users Data\n')
                for user in self.backend.get_all_users():
                    print(f'\t{user}')
            elif choice == 2:
                print('\n All Reservables Data\n')
                for reservable in self.backend.get_all_reservables():
                    print(f'\t{reservable}')
            elif choice == 3:
                for reservation in self.backend.get_all_reservations():
                    print(f'\t{reservation}')
            elif choice == 4:
                while True:
                    reservable_name = input('Enter reservable name: ')
                    if not self.reservable_validator.is_valid_reservable_name(reservable_name):
                        print('\n\tSorry, Invalid reservable name.\n')
                        continue

                    reservable_type = input_valid('Enter reservable type(1. period, 2. capacity, 3. match type): ', 1, 3)
                    if reservable_type == 1:
                        param1 = float(input('Enter morning hourly rate: '))
                        param2 = float(input('Enter night hourly rate: '))

                    elif reservable_type == 2:
                        param1 = int(input('Enter max capacity: '))
                        param2 = float(input('Enter ticket rate: '))
                    else:
                        param1 = float(input('Enter single match rate: '))
                        param2 = float(input('Enter multy match rate: '))

                    if not self.backend.add_reservable(3, reservable_name, param1, param2):
                        print('Sorry, this reservable is already exist.')
                        continue

                    print('\n\tReservable added successfully.\n')
                    break
            elif choice == 5:
                pass
            else:
                return