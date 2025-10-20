from src.backend.BackEnd import BackEnd
from src.frontend.pages.AdminPage import AdminPage
from src.frontend.pages.UserPage import UserPage
from src.frontend.utils import show_menu, input_valid
from src.frontend.validators.users.UserValidator import UserValidator


class FrontEnd:
    """
       Console-based UI coordinator for the reservation system.
       Handles login/signup flow and dispatches to admin/user pages.
    """

    def __init__(self, backend: BackEnd):
        self.backend = backend
        self.user_validator = UserValidator()
        self.current_user: str = ''

        # for admin, user pages
        self.admin_page_menu = ['List users', 'List reservables', 'List reservations', 'Add reservable', 'Cancel reservation', 'logout']
        self.user_page_menu = ['Reserve', 'Cancel Reservation', 'List my reservations', 'Logout']


    def run(self):
        while True:
            menu = ['Login', 'Signup', 'Exit']
            show_menu(menu)
            choice = input_valid('Enter choice: ',1, 3)
            if choice == 1:
                while True:
                    username = input('Username: ')
                    password = input('Password: ')
                    if self.backend.login(username, password):
                        self.current_user = username
                        print('\n\n\tLogin Successful\n')
                        break
                    print('\n\n\tSorry, invalid username or password\n')

            elif choice == 2:
                while True:
                    while True:
                        username = input('Username: ')
                        if self.user_validator.is_valid_username(username):
                            break
                        print('\n\n\tSorry, invalid username\n')

                    while True:
                        password = input('password(must contain uppercase,lowercase, digit, special character): ')
                        if self.user_validator.is_valid_password(password):
                            break
                        print('\n\n\tSorry, invalid password\n')

                    if self.backend.signup(username, password):
                        self.current_user = username
                        print('\n\n\tSignup Successful\n')
                        break
                    else:
                        print('\n\n\tSorry, this username is taken\n')

            else:
                print('\n\n\t\tThanks You\n\n')
                return

            if self.backend.is_admin(self.current_user):
                print('\n')
                print('\t************')
                print('\tAdmin | View')
                print('\t************')
                print('\n')
                admin_page = AdminPage(self.admin_page_menu, self.backend)
                admin_page.run()

            else:
                print('\n')
                print('\t***********')
                print('\tUser | View')
                print('\t***********')
                print('\n')
                user_page = UserPage(self.user_page_menu, self.backend, self.current_user)
                user_page.run()