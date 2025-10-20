from src.backend import BackEnd
from src.backend.payments.CardPayment import CardPayment
from src.backend.payments.EWalletPayment import EWalletPayment
from src.backend.payments.OnlinePayment import OnlinePayment
from src.backend.reservations.ReservationRequest import ReservationRequest
from src.frontend.pages.IPage import IPage
from src.frontend.utils import input_valid, show_menu
from src.frontend.validators.payments.CardPaymentValidator import CardPaymentValidator
from src.frontend.validators.payments.EWalletPaymentValidator import EWalletPaymentValidator
from src.frontend.validators.payments.OnlinePaymentValidator import OnlinePaymentValidator


class UserPage(IPage):
    def __init__(self, menu: list, backend: BackEnd, user_name: str):
        self.menu = menu
        self.backend = backend
        self.current_user: str = user_name

    def run(self):
        while True:
            show_menu(self.menu)
            choice = input_valid('Enter choice: ', 1, len(self.menu))

            if choice == 1:
                type = input_valid('Enter reservation(1. period, 2. capacity, 3. match type) type: ', 1, 3)

                if type == 1:
                    start_time = input_valid('Enter start time: ', 1, 23)
                    end_time = input_valid('Enter end time: ', start_time+1, 24)
                    reservation_request = ReservationRequest('period', start_time, end_time)

                elif type == 2:
                    ticket_count = int(input('Enter ticket count: '))
                    reservation_request = ReservationRequest('capacity', ticket_count)

                else:
                    is_single = bool(input_valid('Enter match type(1. single, 0. multy): ', 0, 1))
                    reservation_request = ReservationRequest('match', is_single)

                if self.backend.reserve(self.current_user, reservation_request):
                    # payment process
                    payment_choice = input_valid('Enter payment choice(1. Card, 2. EWallet, 3. Online): ', 1, 3)
                    if payment_choice == 1:
                        while True:
                            card_number = input('Enter card number: ')
                            cvc         = input('Enter cvc number: ')
                            expiry_date = input('Enter expiry date: ')
                            card = CardPayment(card_number, cvc, expiry_date)
                            if not CardPaymentValidator().validate(card):
                                print('\n\n\tSorry, Invalid card\n\n')
                                continue
                            if card.pay(reservation_request.total):
                                print('\n\n\tPayment successful\n\n')
                            else:
                                print('\n\n\tPayment, failed\n\n')
                                self.backend.cancel_user_reservation(self.current_user, reservation_request)
                            break

                    elif payment_choice == 2:
                        while True:
                            phone_number = input('Enter phone number: ')
                            wallet = EWalletPayment(phone_number)
                            if not EWalletPaymentValidator().validate(wallet):
                                print('\n\n\tSorry, Invalid wallet\n\n')
                                continue
                            if wallet.pay(reservation_request.total):
                                print('\n\n\tPayment successful\n\n')
                            else:
                                print('\n\n\tPayment, failed\n\n')
                                self.backend.cancel_user_reservation(self.current_user, reservation_request)
                            break
                    else:
                        while True:
                            email = input('Enter account email: ')
                            online_account = OnlinePayment(email)
                            if not OnlinePaymentValidator().validate(online_account):
                                print('\n\n\tSorry, Invalid account email\n\n')
                                continue
                            if online_account.pay(reservation_request.total):
                                print('\n\n\tPayment successful\n\n')
                            else:
                                print('\n\n\tPayment, failed\n\n')
                                self.backend.cancel_user_reservation(self.current_user, reservation_request)
                            break
                else:
                    print('\n\n\tSorry, no venue available\n\n')

            elif choice == 2:
                print('\n\n\tAll My Reservations\n\n')
                show_menu(self.backend.get_user_reservations(self.current_user))
                reservation_number = input_valid(f'Enter reservation to cancel(1 - {len(self.backend.get_user_reservations(self.current_user))}): ', 1, len(self.backend.get_user_reservations(self.current_user)))
                reservation_to_be_cancelled = self.backend.get_user_reservations(self.current_user)[reservation_number-1]
                self.backend.cancel_user_reservation(self.current_user, reservation_to_be_cancelled)

            elif choice == 3:
                print('\n\n\tAll My Reservations\n\n')
                show_menu(self.backend.get_user_reservations(self.current_user))
                print('\n\n')

            else:
                return
