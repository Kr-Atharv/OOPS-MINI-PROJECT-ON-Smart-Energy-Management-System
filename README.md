# Smart Energy Management System

OOP Mini Project (C++17) | Group 3I5 | Subject: Object-Oriented Programming Using C++
**Mapped SDG:** SDG 7 - Affordable and Clean Energy

A console application that records household appliances, estimates daily/monthly
electricity consumption, bill and CO2 emissions, ranks the top energy consumers,
compares usage with a monthly target and gives category-wise saving tips.

## Team
Rohan Bhatt, Vedant Kodinya, Prateek Sharma

## Features
- Add appliances (Lighting, Cooling, Kitchen, Electronics)
- Daily and monthly consumption with category-wise totals
- Estimated bill using illustrative slab rates (edit `calculateBill()` for your tariff)
- User-defined monthly target and over/within target status
- Category-wise energy-saving tips
- Records saved to / loaded from `energy_records.txt`

## OOP concepts used
| Concept | Where |
|---|---|
| Abstraction | abstract `Appliance` class (pure virtual `type()`, `tip()`) |
| Inheritance | `Lighting`, `Cooling`, `Kitchen`, `Electronics` |
| Runtime polymorphism | `tip()` / `type()` called through `unique_ptr<Appliance>` |
| Encapsulation | protected data + public getters |
| STL / smart pointers | `vector<unique_ptr<Appliance>>`, `map`, `set` |
| File handling | `ifstream` / `ofstream` |
| Input validation | `readNumber()` keeps asking until the value is valid |

## Build and run
```
g++ -std=c++17 -Wall -Wextra -pedantic energy_management.cpp -o energy_tracker
./energy_tracker          # Windows: energy_tracker.exe
```
Or use `make` / `make run`.

## Project structure
```
energy_management.cpp   source code
Makefile                build helper
docs/                   project report (PDF)
README.md
```
