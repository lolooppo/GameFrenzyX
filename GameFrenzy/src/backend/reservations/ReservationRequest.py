from dataclasses import dataclass
from typing import Optional


@dataclass
class ReservationRequest:
    user_name: str
    date: str
    start_time: Optional[int] = None  # for football, etc.
    end_time: Optional[int] = None
    is_single: Optional[bool] = None  # for ping pong, etc.
    ticket_count: Optional[int] = None # for swimming pool, etc.