from abc import ABC, abstractmethod

class IPayment(ABC):

    @abstractmethod
    def pay(self, amount):
        pass