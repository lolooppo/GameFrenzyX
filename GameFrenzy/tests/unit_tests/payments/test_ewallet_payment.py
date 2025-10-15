from src.backend.payments.EWalletPayment import EWalletPayment
from src.backend.validators.payments import EWalletPaymentValidator as validator_module

def test_ewallet_payment_success_with_valid_wallet():
    payment = EWalletPayment("01141195797")
    assert payment.pay(20) is True

def test_ewallet_payment_failure_with_invalid_wallet():
    payment = EWalletPayment("lolooppo")
    assert payment.pay(20) is False

def test_ewallet_payment_respects_validator(monkeypatch):
    payment = EWalletPayment("012411aB97z")

    monkeypatch.setattr(
        validator_module.EWalletPaymentValidator,
        "validate",
        staticmethod(lambda p: False)
    )
    assert payment.pay(5) is False

    monkeypatch.setattr(
        validator_module.EWalletPaymentValidator,
        "validate",
        staticmethod(lambda p: True)
    )
    assert payment.pay(5) is True
