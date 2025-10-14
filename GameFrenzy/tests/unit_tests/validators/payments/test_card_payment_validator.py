import pytest
from src.backend.payments.CardPayment import CardPayment
from src.backend.validators.payments.CardPaymentValidator import CardPaymentValidator

def test_card_validator_accepts_valid_card():
    payment = CardPayment("4242-4242-4242-4242", "123", "12/25")
    assert CardPaymentValidator.validate(payment) is True

def test_card_validator_rejects_bad_card_number():
    payment = CardPayment("4242-4242-4242", "123", "12/25")  # too short
    assert CardPaymentValidator.validate(payment) is False

def test_card_validator_rejects_bad_expiry():
    payment = CardPayment("4242-4242-4242-4242", "123", "13/25")  # invalid month
    assert CardPaymentValidator.validate(payment) is False

def test_card_validator_rejects_bad_cvc():
    payment = CardPayment("4242-4242-4242-4242", "12", "12/25")  # too short
    assert CardPaymentValidator.validate(payment) is False

def test_card_validator_rejects_old_expiry():
    payment = CardPayment("4242-4242-4242-4242", "12", "12/24")  # expired card
    assert CardPaymentValidator.validate(payment) is False