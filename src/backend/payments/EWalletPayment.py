from src.backend.payments.IPayment import IPayment


class EWalletPayment(IPayment):
    """E-Wallet payment strategy implementation"""
    
    def __init__(self, phone_number):
        self.phone_number = phone_number

    def pay(self, amount):
        # In real implementation, would call e-wallet API
        return True