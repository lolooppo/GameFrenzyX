from src.backend.BackEnd import BackEnd
from src.frontend.FrontEnd import FrontEnd

if __name__ == '__main__':
    # Initialize backend with data file paths
    backend = BackEnd('./backend/database/users.txt', './backend/database/reservables.txt')
    # Create frontend with backend dependency
    frontend = FrontEnd(backend)
    # Start the application
    frontend.run()