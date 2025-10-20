from src.backend.reservables.Reservable import Reservable
from src.backend.reservations import ReservationRequest


class CapacityReservable(Reservable):
    def __init__(self, type, name, max_capacity, ticket_price):
        super().__init__(type, name)
        self.max_capacity = max_capacity
        self.current_capacity = 0
        self.ticket_price = ticket_price

    def is_available_for_reservation(self, req: ReservationRequest) -> bool:
        return self.status and (self.max_capacity > self.current_capacity+req.ticket_count)

    def reserve(self, req: ReservationRequest):
        self.current_capacity += req.ticket_count
        req.reservable_name = self.name
        # calculate the reservation fees
        req.total = req.ticket_count * self.ticket_price

    def unreserve(self, req: ReservationRequest):
        self.current_capacity -= req.ticket_count

    def reset(self):
        self.current_capacity = 0

    def __repr__(self):
        return f'{self.type},{self.name},{self.max_capacity},{self.ticket_price}'


