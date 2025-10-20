import re

from src.backend.payments.CardPayment import CardPayment
from src.frontend.validators.payments.IPaymentValidator import IPaymentValidator


class CardPaymentValidator(IPaymentValidator):
    def __init__(self):
        self.CARD_NUMBER_REGEX = r"^(?:\d{4}[- ]?){3}\d{4}$"
        self.EXPIRY_DATE_REGEX = r"^(0[1-9]|1[0-2])/(?:\d{2}|\d{4})$"
        self.CVC_REGEX = r"^\d{3,4}$"

    def validate(self, payment: CardPayment):
        is_valid_card_number = bool(re.match(self.CARD_NUMBER_REGEX, payment.card_number))
        is_valid_card_cvc = bool(re.match(self.CVC_REGEX, payment.cvc))
        is_valid_card_expiry_date = bool(re.match(self.EXPIRY_DATE_REGEX, payment.expiry_date))
        return is_valid_card_number and is_valid_card_expiry_date and is_valid_card_cvc