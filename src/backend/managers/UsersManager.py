from src.backend.reservations.ReservationRequest import ReservationRequest
from src.backend.users.User import User


class UsersManager:
    """Manage users and their reservation requests (in-memory)."""

    def __init__(self, users: dict):
        self.users = users
        self.admin_username = 'lolooppo'  # Hardcoded admin user

    def is_correct_login_credentials(self, username: str, password: str) -> bool:
        return username in self.users and self.users[username].password == password

    def is_username_taken(self, username: str) -> bool:
        return username in self.users

    def add_user(self, username: str, password: str):
        self.users[username] = User(username, password)

    def is_admin(self, username: str) -> bool:
        return username == self.admin_username

    def get_all_users(self) -> list[User]:
        return list(self.users.copy().values())

    def add_reservation(self, user_name: str, reservation_request: ReservationRequest):
        self.users[user_name].reservation_requests.append(reservation_request)

    def cancel_user_reservation(self, user_name: str, reservation_request: ReservationRequest):
        user = self.users[user_name]
        user.reservation_requests.remove(reservation_request)

    def get_user_reservations(self, user_name: str) -> list[ReservationRequest]:
        return self.users[user_name].reservation_requests

    def get_all_reservations(self) -> list[ReservationRequest]:
        # Collect all reservations from all users
        reservations = []
        for user in self.users:
            reservations.append(user.reservation_requests)
        return reservations