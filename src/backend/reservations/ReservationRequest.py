from dataclasses import dataclass
from typing import Optional

# Represents a user's reservation request with optional details based on reservable type.
@dataclass
class ReservationRequest:
    type: str
    start_time: Optional[int] = None  # for football, etc.
    end_time: Optional[int] = None
    is_single: Optional[bool] = None  # for ping pong, etc.
    ticket_count: Optional[int] = None # for swimming pool, etc.
    total: Optional[float] = None
    reservable_name: Optional[str] = None

    def __str__(self):
        details = [f"Name: {self.reservable_name}"]

        if self.start_time is not None and self.end_time is not None:
            details.append(f"Time: {self.start_time}:00 - {self.end_time}:00")

        if self.is_single is not None:
            details.append(f"Match Type: {'Single' if self.is_single else 'Double'}")

        if self.ticket_count is not None:
            details.append(f"Tickets: {self.ticket_count}")

        if self.total is not None:
            details.append(f"Total: {self.total:.2f}")

        return " | ".join(details)