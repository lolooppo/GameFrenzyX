from src.backend.reservables.Reservable import Reservable
from src.backend.reservables.CapacityReservable import CapacityReservable
from src.backend.reservables.MatchTypeReservable import MatchTypeReservable
from src.backend.reservables.PeriodReservable import PeriodReservable
from src.backend.users.User import User


class DatabaseManager:
    """
    Repository pattern: Handles loading and saving users and reservables data from/to files.
    Acts as a lightweight persistence layer for the system.
    """

    def __init__(self, users_file_path, reservables_file_path):
        self.users_file_path = users_file_path
        self.reservables_file_path = reservables_file_path

        self.users_dict = {}
        self.reservables_dict = {}

    def load_users(self) -> dict[str, User]:
        """Load users from file and create User objects"""
        users_lines = []
        with open(self.users_file_path, 'r') as users_file:
            users_lines = [line.strip() for line in users_file.readlines()]
        for line in users_lines:
            user_name, password = line.split(',')
            self.users_dict[user_name] = User(user_name, password)

        return self.users_dict


    def load_reservables(self) -> dict[str, Reservable]:
        """Load reservables from file and create appropriate Reservable objects"""

        with open(self.reservables_file_path, 'r') as reservables_file:
            reservables_lines = [line.strip() for line in reservables_file.readlines()]
            for line in reservables_lines:
                type = line.strip().split(',')[0]
                # Create appropriate reservable type based on file data
                if 'period' == type:
                    type, name, morning_hourly_rate, night_hourly_rate = line.split(',')
                    self.reservables_dict[name] = PeriodReservable(type, name, float(morning_hourly_rate), float(night_hourly_rate))
                elif 'match' == type:
                    type, name, single_match_rate, multy_match_rate = line.split(',')
                    self.reservables_dict[name] = MatchTypeReservable(type, name, float(single_match_rate), float(multy_match_rate))
                else:
                    type, name, max_capacity, ticket_price = line.split(',')
                    self.reservables_dict[name] = CapacityReservable(type, name, int(max_capacity), float(ticket_price))

            return self.reservables_dict


    def upload_users(self) -> None:
        """Save users data to file"""
        with open(self.users_file_path, 'w') as users_file:
            for user in self.users_dict.values():
                users_file.write(f"{user}\n")

    def upload_reservables(self) -> None:
        """Save reservables data to file"""
        with open(self.reservables_file_path, 'w') as reservables_file:
            for reservable in self.reservables_dict.values():
                reservables_file.write(f"{reservable}\n")