import re
from src.backend.payments.OnlinePayment import OnlinePayment
from src.backend.validators.payments.IPaymentValidator import IPaymentValidator

GMAIL_REGEX = r"^[a-zA-Z0-9._%+-]+@gmail\.com$"

class OnlinePaymentValidator(IPaymentValidator):

    @staticmethod
    def validate(payment: OnlinePayment):
        is_valid_email = bool(re.match(GMAIL_REGEX, payment.email))
        is_payment_done = True
        return is_valid_email and is_payment_done