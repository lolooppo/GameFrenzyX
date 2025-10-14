from src.backend.payments.OnlinePayment import OnlinePayment
from src.backend.validators.payments import OnlinePaymentValidator as validator_module

def test_online_payment_success_with_valid_email():
    payment = OnlinePayment("user@gmail.com")
    assert payment.pay(50) is True

def test_online_payment_failure_with_invalid_email():
    payment = OnlinePayment("user@notgmail.com")
    assert payment.pay(50) is False

def test_online_payment_respects_validator(monkeypatch):
    payment = OnlinePayment("whatever")

    # Force validator False
    monkeypatch.setattr(
        validator_module.OnlinePaymentValidator,
        "validate",
        staticmethod(lambda p: False)
    )
    assert payment.pay(1) is False

    # Force validator True
    monkeypatch.setattr(
        validator_module.OnlinePaymentValidator,
        "validate",
        staticmethod(lambda p: True)
    )
    assert payment.pay(1) is True
