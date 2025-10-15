from src.backend.reservables import Reservable
from src.backend.reservations import ReservationRequest


class PricingService:

    @staticmethod
    def total(venue: Reservable, req: ReservationRequest) -> float :
        if 'period' == venue.type:
            rate = venue.morning_hourly_rate if 6<= req.start_date <= 18 else venue.night_hourly_rate
            return rate * (req.end_date - req.start_date)
        elif 'capacity' == venue.type:
            return req.ticket_count * venue.ticket_price

        match_price = venue.single_match_rate if req.is_single else venue.multy_match_rate
        return match_price