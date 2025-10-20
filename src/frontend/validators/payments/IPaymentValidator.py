from abc import ABC, abstractmethod


class IPaymentValidator(ABC):
    """
    Interface: To validate payment method
    """
    @abstractmethod
    def validate(self, payment_method):
        pass