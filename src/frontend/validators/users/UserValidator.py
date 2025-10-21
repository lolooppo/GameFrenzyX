import re

class UserValidator:
    def __init__(self):
        self.USER_NAME_REGEX = r'^[A-Za-z_]{4,8}$'
        self.PASSWORD_REGEX = r'^(?=.*[a-z])(?=.*[A-Z])(?=.*\d)(?=.*[@$!%*?&])[A-Za-z\d@$!%*?&]{8,12}$'

    def is_valid_username(self, user_name:str) -> bool:
        return bool(re.match(self.USER_NAME_REGEX, user_name))

    def is_valid_password(self, password:str) -> bool:
        return bool(re.match(self.PASSWORD_REGEX, password))