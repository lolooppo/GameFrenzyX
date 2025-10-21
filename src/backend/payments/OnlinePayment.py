from src.backend.payments.IPayment import IPayment


class OnlinePayment(IPayment):
    """Online payment strategy implementation"""
    
    def __init__(self, email):
        self.email = email

    def pay(self, amount):
        # In real implementation, would call online payment API
        return True