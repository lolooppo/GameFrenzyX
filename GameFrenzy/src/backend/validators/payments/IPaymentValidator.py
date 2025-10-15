from abc import ABC, abstractmethod


class IPaymentValidator(ABC):
    """
    Interface: To validate payment method and complete the payment process
    """
    @staticmethod
    @abstractmethod
    def validate(payment_method):
        pass