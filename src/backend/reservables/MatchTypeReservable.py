from src.backend.reservables.Reservable import Reservable
from src.backend.reservations.ReservationRequest import ReservationRequest


class MatchTypeReservable(Reservable):
    """Match-type reservations (e.g., tennis courts) - single/double match pricing"""
    
    def __init__(self, type, name, single_match_rate, multy_match_rate, is_available = True):
        super().__init__(type, name)
        self.single_match_rate = single_match_rate
        self.multy_match_rate = multy_match_rate
        self.is_available = is_available  # Court availability

    def is_available_for_reservation(self, req: ReservationRequest) -> bool:
        return self.status and self.is_available

    def reserve(self, req: ReservationRequest):
        self.is_available = False  # Mark court as occupied
        req.reservable_name = self.name
        # Set price based on match type
        match_price = self.single_match_rate if req.is_single else self.multy_match_rate
        req.total = match_price

    def unreserve(self, req: ReservationRequest):
        self.is_available = True  # Mark court as available

    def reset(self):
        self.is_available = True

    def __repr__(self):
        return f'{self.type},{self.name},{self.single_match_rate},{self.multy_match_rate}'