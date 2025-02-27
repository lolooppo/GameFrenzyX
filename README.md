# GameFrenzyX
🎯 Playground Reservation System
📌 Description
The Playground Reservation System is a C++-based application that allows users to reserve sports facilities such as football fields, volleyball courts, tennis courts, swimming pools, ping pong tables, and billiards tables. The system supports user authentication, reservations management, and administrative control over available facilities.

## 🚀 Core Functionalities
👤 **User Management**
- Users can sign up with a username and password.
- Users can log in to access the system.
- Passwords must meet security criteria (length, special characters, etc.).

**🏟️ Facility Management**
- Supports multiple sports categories (Football, Volleyball, Tennis, Swimming, Ping Pong, Billiards).
- Each facility has availability status (open or under maintenance).
- Facilities have custom pricing (e.g., morning vs. night rates for football).
- Admins can add new facilities, update availability, and view all facilities.

**📅 Reservation System**
- Users can reserve a facility for a specific time slot.
- Prevents double booking by checking real-time availability.
- Users can view their reservations and cancel if needed.
- Different pricing models based on time slot or facility type.

**🔑 Admin Features**
- Admin login with predefined credentials.
- Admins can add new facilities, update availability, and view all reservations.
- Admins can clear all reservations when needed.

**📂 Database Management**
- Reads and writes data from text files (users.txt, reservables.txt, reservations.txt).
- Stores user accounts, facility details, and reservations history persistently.


# 🛠️ How It Works
1. User Sign-Up/Login → New users register; existing users log in.
2. Facility Selection → Users browse available facilities.
3. Reservation Process → Users select time slots and confirm booking.
4. Admin Management → Admins manage facilities and bookings.
5. Data Storage → System saves all changes to files for future use.
