CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic

energy_tracker: energy_management.cpp
	$(CXX) $(CXXFLAGS) energy_management.cpp -o energy_tracker

run: energy_tracker
	./energy_tracker

clean:
	rm -f energy_tracker energy_records.txt
