from src.backend.payments.EWalletPayment import EWalletPayment
from src.backend.validators.payments.EWalletPaymentValidator import EWalletPaymentValidator


def test_ewallet_validator_accepts_valid_number():
    # Adjust expected valid format if your validator enforces a pattern.
    p = EWalletPayment("01158373074")
    assert EWalletPaymentValidator.validate(p) is True

def test_ewallet_validator_rejects_empty_number():
    p = EWalletPayment("")
    assert EWalletPaymentValidator.validate(p) is False

