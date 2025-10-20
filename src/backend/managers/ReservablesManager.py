from src.backend.reservables.Reservable import Reservable
from src.backend.reservables.CapacityReservable import CapacityReservable
from src.backend.reservables.PeriodReservable import PeriodReservable
from src.backend.reservables.MatchTypeReservable import MatchTypeReservable


class ReservablesManager:
    """
        Manage a collection of Reservable instances: list/add/reserve/unreserve.
        The manager works on an in-memory dict keyed by reservable name.
    """

    def __init__(self, reservables: dict[str, Reservable]):
        self.reservables = reservables

    def get_all_reservables(self) -> list[Reservable]:
        return list(self.reservables.copy().values())

    def add_reservable(self, type: int, reservable_name: str, param1, param2) -> bool:
        """
                Add a new reservable.
                - type: 1 => period, 2 => capacity, else => match
                - param1/param2: parameters required by each reservable constructor
                Returns True if added, False if name already exists.
        """

        if reservable_name in self.reservables:
            return False
        if type == 1:
            new_reservable = PeriodReservable('period', reservable_name, param1, param2)
        elif type == 2:
            new_reservable = CapacityReservable('capacity', reservable_name, param1, param2)
        else:
            new_reservable = MatchTypeReservable('match', reservable_name, param1, param2)
        self.reservables[reservable_name] = new_reservable
        return True


    def reserve(self, reservation_request) -> bool:
        """
                Find a matching available reservable (by type) and reserve it.
                Returns True on success, False if none available.
        """
        for reservable in self.reservables.values():
            if reservable.type == reservation_request.type and reservable.is_available_for_reservation(reservation_request):
                reservable.reserve(reservation_request)
                return True
        return False

    def unreserve(self, reservation_request) -> bool:
        """
                Unreserve the reservable that matches the reservation_request.reservable_name.
                Returns True on success, False if name not found.
        """
        for reservable in self.reservables.values():
            if reservable.name == reservation_request.reservable_name:
                reservable.unreserve(reservation_request)
                return True
        return False

    def reset_reservables(self, reservation_request):
        """Placeholder: reset logic for reservables (e.g., clear all bookings) — implement as needed."""
        pass