from src.backend.managers.DatabaseManager import DatabaseManager
from src.backend.managers.ReservablesManager import ReservablesManager
from src.backend.managers.UsersManager import UsersManager
from src.backend.reservables.Reservable import Reservable
from src.backend.reservations.ReservationRequest import ReservationRequest

from src.backend.users.User import User




class BackEnd:
    """Coordinates all backend operations — manages users, reservables, and database persistence."""

    def __init__(self, users_file_path, reservables_file_path):
        # Files credits
        self.users_file_path = users_file_path
        self.reservables_file_path = reservables_file_path

        # System managers and database loading
        self.database_manager = DatabaseManager(users_file_path, reservables_file_path)
        self.users_manager = UsersManager(self.database_manager.load_users())
        self.reservables_manager = ReservablesManager(self.database_manager.load_reservables())

    def __del__(self):
        self.database_manager.upload_users()
        self.database_manager.upload_reservables()


    def login(self, username: str, password: str) -> bool:
        return self.users_manager.is_correct_login_credentials(username, password)

    def signup(self, username: str, password: str) -> bool:
        is_username_taken_before = self.users_manager.is_username_taken(username)
        if not is_username_taken_before:
            self.users_manager.add_user(username, password)
            return True
        return False

    def is_admin(self, username: str) -> bool:
        return self.users_manager.is_admin(username)

    def get_all_users(self) -> list[User]:
        return self.users_manager.get_all_users()

    def get_all_reservables(self) -> list[Reservable]:
        return self.reservables_manager.get_all_reservables()

    def add_reservable(self, type, reservable_name, param1, param2) -> bool:
        return self.reservables_manager.add_reservable(type, reservable_name, param1, param2)

    def reserve(self, user_name: str, reservation_request: ReservationRequest) -> bool:
        is_reserved = self.reservables_manager.reserve(reservation_request)
        if not is_reserved:
            return False
        self.users_manager.add_reservation(user_name, reservation_request)
        return True

    def get_all_reservations(self) -> list[ReservationRequest]:
        return self.users_manager.get_all_reservations()

    def get_user_reservations(self, user_name: str) -> list[ReservationRequest]:
        return self.users_manager.get_user_reservations(user_name)

    def cancel_user_reservation(self, user_name, reservation_request: ReservationRequest) :
        self.users_manager.cancel_user_reservation(user_name, reservation_request)
        self.reservables_manager.unreserve(reservation_request)

    def cancel_all_user_reservations(self):
        pass