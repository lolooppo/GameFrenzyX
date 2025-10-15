from abc import abstractmethod, ABC
from src.backend.reservations.ReservationRequest import ReservationRequest


class Reservable(ABC):
    def __init__(self, name, category, status = True):
        self.name = name
        self.category = category
        self.status = status

    @abstractmethod
    def is_available_for_reservation(self, req: ReservationRequest) -> bool:
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