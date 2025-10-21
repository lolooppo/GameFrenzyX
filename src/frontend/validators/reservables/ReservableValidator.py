import re

class ReservableValidator:
    def __init__(self):
        self.RES_NAME_REGEX = r'^[A-Za-z0-9]+$'

    def is_valid_reservable_name(self, reservable_name: str) -> bool:
        return bool(re.match(self.RES_NAME_REGEX, reservable_name))