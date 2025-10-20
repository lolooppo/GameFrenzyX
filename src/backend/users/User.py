class User:
    def __init__(self, user_name, password):
        self.user_name = user_name
        self.password = password
        self.reservation_requests = []

    def __repr__(self):
        return f'{self.user_name},{self.password}'