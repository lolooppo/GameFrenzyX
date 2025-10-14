from src.backend.payments.IPayment import IPayment


class CardPayment(IPayment):
    def __init__(self, card_number, cvc, expiry_date):
        self.card_number = card_number
        self.cvc = cvc
        self.expiry_date = expiry_date

    def pay(self, amount):
        from src.backend.validators.payments.CardPaymentValidator import CardPaymentValidator
        return CardPaymentValidator.validate(self)