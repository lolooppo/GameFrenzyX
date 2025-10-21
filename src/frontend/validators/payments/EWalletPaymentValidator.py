import re
from src.backend.payments.EWalletPayment import EWalletPayment
from src.frontend.validators.payments.IPaymentValidator import IPaymentValidator


class EWalletPaymentValidator(IPaymentValidator):
    def __init__(self):
        self.EGYPT_PHONE_REGEX = r'^(?:\+20|0020|0)?1[0125]\d{8}$'


    def validate(self, payment: EWalletPayment):
        is_valid_phone_number = bool(re.match(self.EGYPT_PHONE_REGEX, payment.phone_number))

        return is_valid_phone_number
