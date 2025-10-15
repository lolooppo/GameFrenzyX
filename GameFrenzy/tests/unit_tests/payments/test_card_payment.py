from src.backend.payments.CardPayment import CardPayment
from src.backend.validators.payments import CardPaymentValidator as real_validator_module

def test_card_payment_success_with_real_validator():
    payment = CardPayment("4242-4242-4242-4242", "123", "12/25")
    assert payment.pay(100.0) is True

def test_card_payment_failure_with_real_validator():
    payment = CardPayment("badnumber", "123", "12/25")
    assert payment.pay(100.0) is False

def test_card_payment_respects_validator_result(monkeypatch):
    payment = CardPayment("anything", "any", "any")

    # Force the validator to return False
    monkeypatch.setattr(
        real_validator_module.CardPaymentValidator,
        "validate",
        staticmethod(lambda p: False)
    )
    assert payment.pay(10) is False

    # Force the validator to return True
    monkeypatch.setattr(
        real_validator_module.CardPaymentValidator,
        "validate",
        staticmethod(lambda p: True)
    )
    assert payment.pay(10) is True
