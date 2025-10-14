import re
from src.backend.payments.EWalletPayment import EWalletPayment
from src.backend.validators.payments.IPaymentValidator import IPaymentValidator

EGYPT_PHONE_REGEX = r'^(?:\+20|0020|0)?1[0125]\d{8}$'

class EWalletPaymentValidator(IPaymentValidator):

    @staticmethod
    def validate(payment: EWalletPayment):
        is_valid_phone_number = bool(re.match(EGYPT_PHONE_REGEX, payment.phone_number))
        is_payment_done = True
        return is_valid_phone_number and is_payment_done