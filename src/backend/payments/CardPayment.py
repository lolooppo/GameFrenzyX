from src.backend.payments.IPayment import IPayment


class CardPayment(IPayment):
    """Card payment strategy implementation"""
    
    def __init__(self, card_number, cvc, expiry_date):
        self.card_number = card_number
        self.cvc = cvc
        self.expiry_date = expiry_date

    def pay(self, amount):
        # In real implementation, would call payment gateway API
        return True