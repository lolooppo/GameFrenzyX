import re
from src.backend.payments.OnlinePayment import OnlinePayment
from src.frontend.validators.payments.IPaymentValidator import IPaymentValidator


class OnlinePaymentValidator(IPaymentValidator):

    def __init__(self):
        self.GMAIL_REGEX = r"^[a-zA-Z0-9._%+-]+@gmail\.com$"

    def validate(self, payment: OnlinePayment):
        is_valid_email = bool(re.match(self.GMAIL_REGEX, payment.email))

        return is_valid_email
