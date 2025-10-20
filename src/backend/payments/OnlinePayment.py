from src.backend.payments.IPayment import IPayment


class OnlinePayment(IPayment):
    def __init__(self, email):
        self.email = email

    def pay(self, amount):
        return True