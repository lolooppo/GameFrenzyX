from src.backend.reservables.Reservable import Reservable
from src.backend.reservations import ReservationRequest


class CapacityReservable(Reservable):
    def __init__(self, name, category, status, max_capacity, ticket_price):
        super().__init__(name, category, status)
        self.type = 'capacity'
        self.max_capacity = max_capacity
        self.current_capacity = 0
        self.ticket_price = ticket_price

    def is_available_for_reservation(self, req: ReservationRequest) -> bool:
        return self.max_capacity > self.current_capacity+req.ticket_count

    def reserve(self, req: ReservationRequest):
        self.current_capacity += req.ticket_count

    def unreserve(self, req: ReservationRequest):
        self.current_capacity -= req.ticket_count

    def reset(self):
        self.current_capacity = 0


