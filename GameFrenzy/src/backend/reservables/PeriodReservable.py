from src.backend.reservables.Reservable import Reservable
from src.backend.reservations import ReservationRequest


class PeriodReservable(Reservable):
    def __init__(self, name, category, status, morning_hourly_rate, night_hourly_rate):
        super().__init__(name, category, status)
        self.type = 'period'
        self.periods = [0]*24
        self.morning_hourly_rate = morning_hourly_rate
        self.night_hourly_rate = night_hourly_rate

    def is_available_for_reservation(self, req: ReservationRequest) -> bool:
        start_time, end_time = req.start_time, req.end_time
        for i in range(start_time-1, end_time-1):
            if 1 == self.periods[i]:
                return False
        return True

    def reserve(self, req: ReservationRequest):
        start_time, end_time = req.start_time, req.end_time
        for i in range(start_time-1, end_time-1):
            self.periods[i] = 1

    def unreserve(self, req: ReservationRequest):
        start_time, end_time = req.start_time, req.end_time
        for i in range(start_time-1, end_time-1):
            self.periods[i] = 0

    def reset(self):
        self.periods = [0]*24