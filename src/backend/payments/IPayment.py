from abc import ABC, abstractmethod

class IPayment(ABC):
    """Strategy pattern: Abstract interface for payment operations."""

    @abstractmethod
    def pay(self, amount):
        """The appropriate APIs to be called in real world usage"""
        pass