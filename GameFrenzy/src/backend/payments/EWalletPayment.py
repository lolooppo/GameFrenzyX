from src.backend.payments.IPayment import IPayment


class EWalletPayment(IPayment):
    def __init__(self, phone_number):
        self.phone_number = phone_number

    def pay(self, amount):
        from src.backend.validators.payments.EWalletPaymentValidator import EWalletPaymentValidator
        return EWalletPaymentValidator.validate(self)