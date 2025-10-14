import re
from datetime import datetime

from src.backend.payments.CardPayment import CardPayment
from src.backend.validators.payments.IPaymentValidator import IPaymentValidator

CARD_NUMBER_REGEX = r"^(?:\d{4}[- ]?){3}\d{4}$"
EXPIRY_DATE_REGEX = r"^(0[1-9]|1[0-2])/(?:\d{2}|\d{4})$"
CVC_REGEX = r"^\d{3,4}$"


class CardPaymentValidator(IPaymentValidator):

    @staticmethod
    def validate(payment: CardPayment):
        is_valid_card_number = bool(re.match(CARD_NUMBER_REGEX, payment.card_number))
        is_valid_card_cvc = bool(re.match(CVC_REGEX, payment.cvc))
        is_valid_card_expiry_date = bool(re.match(EXPIRY_DATE_REGEX, payment.expiry_date))
        is_payment_done = True
        return is_valid_card_number and is_valid_card_expiry_date and is_valid_card_cvc and is_payment_done