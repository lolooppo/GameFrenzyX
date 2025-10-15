from src.backend.reservables.Reservable import Reservable
from src.backend.reservations.ReservationRequest import ReservationRequest


class MatchTypeReservable(Reservable):
    def __init__(self, name, category, status, single_match_rate, multy_match_rate, is_available = True):
        super().__init__(name, category, status)
        self.type = "match"
        self.single_match_rate = single_match_rate
        self.multy_match_rate = multy_match_rate
        self.is_available = is_available

    def is_available_for_reservation(self, req: ReservationRequest) -> bool:
        return self.is_available

    def reserve(self, req: ReservationRequest):
        self.is_available = False

    def unreserve(self, req: ReservationRequest):
        self.is_available = True

    def reset(self):
        self.is_available = True