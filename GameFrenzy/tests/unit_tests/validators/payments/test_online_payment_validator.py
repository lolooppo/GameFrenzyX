from src.backend.payments.OnlinePayment import OnlinePayment
from src.backend.validators.payments.OnlinePaymentValidator import OnlinePaymentValidator


def test_online_validator_accepts_gmail():
    p = OnlinePayment("user.name@gmail.com")
    assert OnlinePaymentValidator.validate(p) is True

def test_online_validator_rejects_non_gmail():
    p = OnlinePayment("user@example.com")
    assert OnlinePaymentValidator.validate(p) is False

def test_online_validator_rejects_malformed_email():
    p = OnlinePayment("not-an-email")
    assert OnlinePaymentValidator.validate(p) is False
