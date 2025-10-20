from src.backend.BackEnd import BackEnd
from src.frontend.FrontEnd import FrontEnd

if __name__ == '__main__':
    backend = BackEnd('./backend/database/users.txt', './backend/database/reservables.txt')
    frontend = FrontEnd(backend)
    frontend.run()