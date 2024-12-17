# Legacy Insurance System

## Overview
This project simulates a legacy surety bond insurance system, designed to demonstrate common patterns and practices found in legacy software. It's implemented in C++ using practices that were common in older systems, such as global variables, direct memory manipulation, and text-based interfaces.

## Purpose
The main purpose of this project is to serve as an example of legacy code that can be used for:
- Learning about legacy system structures
- Practice with refactoring techniques
- Understanding older programming patterns
- Testing migration strategies
- Training and educational purposes

## System Features
- Policyholder Management
- Contract Management
- Endorsement Management
- Reporting System

## Technical Characteristics
- Written in C++
- Console-based interface
- In-memory data storage
- Uses C-style strings
- Global variables
- Direct memory manipulation
- Simple validation rules
- No database integration

## Business Rules

### Policyholder Rules
- Each policyholder must have a valid document number (CNPJ) with 14 digits
- Policyholder information includes name, address, and contact details
- Policyholder status can be active or inactive

### Contract Rules
- Minimum contract value: $1,000.00
- Maximum contract value: $10,000,000.00
- Contract must have at least one coverage
- End date must be after start date
- Start date cannot be in the past
- Contract is linked to a single policyholder
- Premium is calculated based on selected coverages
- Each coverage has its own premium rate

### Endorsement Rules
- Can only be applied to active contracts
- Three types available:
  - Increase (I): Adds value to contract
  - Decrease (D): Reduces contract value
  - Cancel (C): Terminates the contract
- Cannot reduce contract value below minimum allowed
- Cannot increase contract value above maximum allowed
- Endorsement must include a description
- Each endorsement is timestamped

### Coverage Rules
- Two default coverages available:
  - Performance Bond (2% premium rate)
  - Bid Bond (1.5% premium rate)
- Each coverage has a maximum value limit
- Multiple coverages can be applied to a single contract

## Setup and Requirements
1. Windows environment
2. MinGW with MSYS2
3. G++ compiler
4. Visual Studio Code (recommended)

## Building the Project
1. Clone the repository
2. Open terminal in project directory
3. Compile using g++:
```bash
g++ -o insurance_system main.cpp menu.cpp database.cpp business.cpp
```

## Running the System
1. Execute the compiled program:
```bash
./insurance_system
```
2. Use the menu system to navigate through options:
   - 1: Policyholder Management
   - 2: Contract Management
   - 3: Endorsement Management
   - 4: Reports
   - 0: Exit

## Project Structure
```
surety-bond-system/
│
├── src/
│   ├── main.cpp          # Program entry point
│   ├── globals.h         # Global variables and structures
│   ├── database.h/cpp    # Data manipulation functions
│   ├── business.h/cpp    # Business rules implementation
│   └── menu.h/cpp        # User interface functions
│
└── README.md
```

## Important Notes
- All data is stored in memory and will be lost when the program closes
- This is a simulation of a legacy system and doesn't include modern programming practices intentionally
- The system uses simplified validation rules for demonstration purposes

## Limitations
- No persistent storage
- No user authentication
- Limited error handling
- No logging system
- No configuration files
- No automated tests

## Usage Example
1. First, create a policyholder
2. Then create a contract for that policyholder
3. Add endorsements if needed
4. Generate reports to view system status

## Contributing
This is an educational project meant to demonstrate legacy system characteristics. Feel free to fork and modify for your own learning purposes.