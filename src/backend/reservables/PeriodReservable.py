from src.backend.reservables.Reservable import Reservable
from src.backend.reservations import ReservationRequest


class PeriodReservable(Reservable):
    def __init__(self, type, name, morning_hourly_rate, night_hourly_rate):
        super().__init__(type, name)
        self.periods = [0]*24
        self.morning_hourly_rate = morning_hourly_rate
        self.night_hourly_rate = night_hourly_rate

    def is_available_for_reservation(self, req: ReservationRequest) -> bool:
        if not self.status:
            return False

        start_time, end_time = req.start_time, req.end_time
        for i in range(start_time-1, end_time-1):
            if 1 == self.periods[i]:
                return False

        return True

    def reserve(self, req: ReservationRequest):
        start_time, end_time = req.start_time, req.end_time
        for i in range(start_time-1, end_time-1):
            self.periods[i] = 1
        req.reservable_name = self.name
        # calculate the reservation fees
        rate = self.morning_hourly_rate if 6 <= start_time <= 18 else self.night_hourly_rate
        req.total = rate * (end_time - start_time)

    def unreserve(self, req: ReservationRequest):
        start_time, end_time = req.start_time, req.end_time
        for i in range(start_time-1, end_time-1):
            self.periods[i] = 0

    def reset(self):
        self.periods = [0]*24

    def __repr__(self):
        return f'{self.type},{self.name},{self.morning_hourly_rate},{self.night_hourly_rate}'