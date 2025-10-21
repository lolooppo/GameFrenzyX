from abc import abstractmethod, ABC
from src.backend.reservations.ReservationRequest import ReservationRequest


class Reservable(ABC):
    """Template Method pattern: Abstract base class for all reservable entities (e.g., courts, rooms, pools)."""

    def __init__(self, type, name, status = True):
        self.type = type
        self.name = name
        self.status = status  # Available/unavailable status

    @abstractmethod
    def is_available_for_reservation(self, req: ReservationRequest) -> bool:
        """Check if this reservable is available for reservation."""
        pass

    @abstractmethod
    def reserve(self, req: ReservationRequest):
        pass

    @abstractmethod
    def unreserve(self, req: ReservationRequest):
        pass

    @abstractmethod
    def reset(self):
        pass