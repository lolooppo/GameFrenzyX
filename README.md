# 🎮 GameFrenzy - Reservation Management System

A comprehensive reservation management system for sports facilities, built with clean architecture and modern design patterns.

## 🚀 Quick Start

```bash
# Run the application
python src/main.py
```

## ✨ Key Features

- **Multi-Type Reservations**: Support for period-based, capacity-based, and match-type reservations
- **Flexible Payment System**: Card, E-Wallet, and Online payment options
- **Role-Based Access**: Separate interfaces for users and administrators
- **Real-Time Availability**: Dynamic availability checking and reservation management
- **Data Persistence**: File-based data storage with automatic loading/saving

## 🏗️ System Architecture

### Core Components

- **Frontend**: Console-based UI with role-specific pages
- **Backend**: Business logic coordination and data management
- **Managers**: Specialized components for users, reservables, and database operations
- **Validators**: Input validation and data integrity checks

### Reservation Types

| Type | Description | Example |
|------|-------------|---------|
| **Period** | Time-slot based reservations | Football fields (hourly rates) |
| **Capacity** | Ticket-based reservations | Swimming pools (per person) |
| **Match Type** | Single/Double match reservations | Tennis courts (match-based pricing) |

## 🎯 Design Principles & Patterns

### Object-Oriented Design
- **Abstraction**: `Reservable` abstract class defining common interface
- **Inheritance**: Specialized reservable types extending base functionality
- **Polymorphism**: Runtime behavior based on reservable type
- **Encapsulation**: Private data with controlled access methods

### Design Patterns Implementation

| Pattern | Implementation | Purpose |
|---------|---------------|---------|
| **Strategy** | Payment system (`IPayment`) | Pluggable payment methods |
| **Abstract Factory** | `ReservablesManager` | Dynamic reservable creation |
| **Template Method** | `Reservable` hierarchy | Consistent reservation workflow |
| **Facade** | `BackEnd` class | Simplified system interface |
| **Repository** | `DatabaseManager` | Data persistence abstraction |

### SOLID Principles
- **Single Responsibility**: Each class has one clear purpose
- **Open/Closed**: Extensible through inheritance and interfaces
- **Liskov Substitution**: Reservable subclasses are interchangeable
- **Interface Segregation**: Focused interfaces (`IPayment`, `IPage`)
- **Dependency Inversion**: High-level modules depend on abstractions

## 📁 Project Structure

```
src/
├── backend/
│   ├── managers/          # Business logic managers
│   ├── payments/          # Payment strategy implementations
│   ├── reservables/       # Reservable type hierarchy
│   ├── reservations/      # Reservation data models
│   └── users/            # User management
├── frontend/
│   ├── pages/            # UI page implementations
│   └── validators/       # Input validation logic
└── main.py              # Application entry point
```

## 🔧 Technical Highlights

- **Type Safety**: Comprehensive Python type hints
- **Error Handling**: Graceful failure management
- **Modular Design**: Clean separation of concerns
- **Extensible Architecture**: Easy to add new reservation types
- **Validation Layer**: Comprehensive input validation

## 🎨 System Diagrams

- **Class Diagram**: Complete system architecture
- **Use Case Diagrams**: Detailed functionality flows
- **Component Diagrams**: System interaction patterns