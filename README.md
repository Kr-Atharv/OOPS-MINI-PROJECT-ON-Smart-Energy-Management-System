# Smart Energy Management System

**OOP Mini Project (C++17)**
**Mapped SDG:** SDG 7 – Affordable and Clean Energy

A C++ console application that records household appliances, estimates daily and monthly electricity consumption and bill, compares usage with a monthly target and gives category-wise energy-saving tips.

## Project Details

| | |
|---|---|
| **Group Number** | 3I4 and 3I6 |
| **Course / Semester** | BTECH / 3rd |
| **Subject** | Object-Oriented Programming Using C++ |

## Team Members

| Name | Enrollment Number |
|---|---|
| Pragya Chhajer | 06614803125 |
| Kumar Atharv | 08214803125 |
| Krishna Bhardwaj | 12014803125 |

## Features
- Add appliances (Lighting, Cooling, Kitchen, Electronics)
- Daily and monthly consumption with category-wise totals
- Estimated bill using illustrative slab rates (edit `calculateBill()` for your tariff)
- User-defined monthly target with over/within target status
- Category-wise energy-saving tips
- Records saved to and loaded from `energy_records.txt`

## OOP Concepts Used

| Concept | Where |
|---|---|
| Abstraction | abstract `Appliance` class (pure virtual `type()`, `tip()`) |
| Inheritance | `Lighting`, `Cooling`, `Kitchen`, `Electronics` |
| Runtime polymorphism | `tip()` / `type()` called through `unique_ptr<Appliance>` |
| Encapsulation | protected data + public getters |
| STL / smart pointers | `vector<unique_ptr<Appliance>>`, `map`, `set` |
| File handling | `ifstream` / `ofstream` |
| Input validation | `readNumber()` keeps asking until the value is valid |

## Build and Run

```
g++ -std=c++17 -Wall -Wextra -pedantic energy_management.cpp -o energy_tracker
./energy_tracker          # Windows: energy_tracker.exe
```

Or use `make` and `make run`.

## Sample Output

```
=== SMART ENERGY MANAGEMENT SYSTEM ===
1 Add appliance
2 View all appliances
3 Energy summary and bill estimate
4 Set monthly energy target
5 Save and exit

Daily consumption   : 12.98 kWh
Monthly consumption : 389.37 kWh
  Cooling      : 270.00 kWh
  Electronics  : 9.75 kWh
  Kitchen      : 108.00 kWh
  Lighting     : 1.62 kWh
Estimated bill      : Rs 1970.28 per month
Monthly target      : 350.00 kWh
Status: OVER target by 39.37 kWh.
```

## Project Structure

```
energy_management.cpp   source code
Makefile                build helper
docs/                   project report (PDF and Word)
README.md
```

## Future Scope
- Date-wise, weekly and monthly consumption reports
- Edit or remove appliances and use real tariffs for different states
- CO₂ emission estimate and top energy-consuming appliances
- Solar-panel generation estimates
- Multiple user profiles and database storage
- Graphical interface or mobile app with charts and reminders
