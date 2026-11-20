// Smart Energy Management System - OOP Mini Project (SDG 7)
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <memory>
#include <string>
#include <iomanip>
#include <cstdlib>
using namespace std;

// Abstract base class
class Appliance {
protected:
    string name;
    double watts, hours;
public:
    Appliance(string n, double w, double h) : name(n), watts(w), hours(h) {}
    virtual ~Appliance() {}
    virtual string type() const = 0;
    virtual string tip() const = 0;
    string getName() const { return name; }
    double getWatts() const { return watts; }
    double getHours() const { return hours; }
    double dailyKwh() const { return watts * hours / 1000; }
    double monthlyKwh() const { return dailyKwh() * 30; }
};

class Lighting : public Appliance {
public:
    Lighting(string n, double w, double h) : Appliance(n, w, h) {}
    string type() const override { return "Lighting"; }
    string tip() const override { return "Use LED bulbs and switch off lights in empty rooms."; }
};

class Cooling : public Appliance {
public:
    Cooling(string n, double w, double h) : Appliance(n, w, h) {}
    string type() const override { return "Cooling"; }
    string tip() const override { return "Set the AC to 24-26 C and clean the filters regularly."; }
};

class Kitchen : public Appliance {
public:
    Kitchen(string n, double w, double h) : Appliance(n, w, h) {}
    string type() const override { return "Kitchen"; }
    string tip() const override { return "Keep the fridge door closed and run full loads only."; }
};

class Electronics : public Appliance {
public:
    Electronics(string n, double w, double h) : Appliance(n, w, h) {}
    string type() const override { return "Electronics"; }
    string tip() const override { return "Unplug chargers and devices that are on standby."; }
};

typedef vector<unique_ptr<Appliance>> ApplianceList;

unique_ptr<Appliance> makeAppliance(int t, string n, double w, double h) {
    if (t == 1) return make_unique<Lighting>(n, w, h);
    if (t == 2) return make_unique<Cooling>(n, w, h);
    if (t == 3) return make_unique<Kitchen>(n, w, h);
    return make_unique<Electronics>(n, w, h);
}

// Reads a number between lo and hi, asks again if input is invalid
double readNumber(string msg, double lo, double hi) {
    double x;
    while (true) {
        cout << msg;
        if (cin >> x && x >= lo && x <= hi) {
            cin.ignore(1000, '\n');
            return x;
        }
        if (cin.eof()) exit(0);
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input, try again.\n";
    }
}

// Illustrative slab rates (Rs per unit)
double calculateBill(double units) {
    if (units <= 100) return units * 3;
    if (units <= 300) return 100 * 3 + (units - 100) * 5;
    return 100 * 3 + 200 * 5 + (units - 300) * 7.5;
}

void addAppliance(ApplianceList &list) {
    int type = (int)readNumber("Type (1 Lighting, 2 Cooling, 3 Kitchen, 4 Electronics): ", 1, 4);
    string name;
    while (name.empty()) {
        cout << "Appliance name: ";
        if (!getline(cin, name)) exit(0);
    }
    for (char &c : name)
        if (c == '|') c = ' ';
    double watts = readNumber("Power rating (watts): ", 1, 10000);
    double hours = readNumber("Usage per day (hours): ", 0, 24);
    list.push_back(makeAppliance(type, name, watts, hours));
    cout << "Appliance added.\n";
}

void viewAppliances(const ApplianceList &list) {
    if (list.empty()) {
        cout << "No appliances recorded yet.\n";
        return;
    }
    cout << left << setw(4) << "No." << setw(13) << "Category" << setw(20) << "Appliance"
         << right << setw(8) << "Watts" << setw(10) << "Hrs/day" << setw(12) << "kWh/month" << "\n";
    cout << string(67, '-') << "\n";
    for (size_t i = 0; i < list.size(); i++) {
        cout << left << setw(4) << i + 1 << setw(13) << list[i]->type() << setw(20) << list[i]->getName()
             << right << fixed << setw(8) << setprecision(0) << list[i]->getWatts()
             << setw(10) << setprecision(1) << list[i]->getHours()
             << setw(12) << setprecision(2) << list[i]->monthlyKwh() << "\n";
    }
}

void showSummary(const ApplianceList &list, double target) {
    if (list.empty()) {
        cout << "No appliances recorded yet.\n";
        return;
    }
    double daily = 0, monthly = 0;
    map<string, double> categoryTotal;
    set<string> shown;
    for (const auto &a : list) {
        daily += a->dailyKwh();
        monthly += a->monthlyKwh();
        categoryTotal[a->type()] += a->monthlyKwh();
    }
    cout << fixed << setprecision(2);
    cout << "Daily consumption   : " << daily << " kWh\n";
    cout << "Monthly consumption : " << monthly << " kWh\n";
    for (const auto &c : categoryTotal)
        cout << "  " << left << setw(13) << c.first << ": " << c.second << " kWh\n";
    cout << "Estimated bill      : Rs " << calculateBill(monthly) << " per month\n";
    if (target > 0) {
        cout << "Monthly target      : " << target << " kWh\n";
        if (monthly > target)
            cout << "Status: OVER target by " << monthly - target << " kWh.\n";
        else
            cout << "Status: within target.\n";
    } else {
        cout << "Monthly target      : not set (use option 4)\n";
    }
    cout << "\nEnergy-saving tips:\n";
    for (const auto &a : list) {
        if (shown.count(a->type()) == 0) {
            shown.insert(a->type());
            cout << "- " << a->tip() << "\n";  // polymorphic call
        }
    }
}

void saveRecords(const ApplianceList &list, double target) {
    ofstream out("energy_records.txt");
    out << "TARGET|" << target << "\n";
    for (const auto &a : list)
        out << a->type() << "|" << a->getName() << "|" << a->getWatts() << "|" << a->getHours() << "\n";
    cout << "Records saved. Goodbye!\n";
}

void loadRecords(ApplianceList &list, double &target) {
    ifstream in("energy_records.txt");
    if (!in) return;
    string line;
    while (getline(in, line)) {
        stringstream ss(line);
        string type, name, w, h;
        getline(ss, type, '|');
        if (type == "TARGET") {
            getline(ss, w);
            target = stod(w);
            continue;
        }
        getline(ss, name, '|');
        getline(ss, w, '|');
        getline(ss, h);
        int t = 4;
        if (type == "Lighting") t = 1;
        else if (type == "Cooling") t = 2;
        else if (type == "Kitchen") t = 3;
        list.push_back(makeAppliance(t, name, stod(w), stod(h)));
    }
    cout << list.size() << " saved appliance(s) loaded.\n";
}

int main() {
    ApplianceList appliances;
    double target = 0;
    loadRecords(appliances, target);

    int choice = 0;
    while (choice != 5) {
        cout << "\n=== SMART ENERGY MANAGEMENT SYSTEM ===\n"
             << "1 Add appliance\n"
             << "2 View all appliances\n"
             << "3 Energy summary and bill estimate\n"
             << "4 Set monthly energy target\n"
             << "5 Save and exit\n";
        choice = (int)readNumber("Choice: ", 1, 5);
        if (choice == 1) addAppliance(appliances);
        else if (choice == 2) viewAppliances(appliances);
        else if (choice == 3) showSummary(appliances, target);
        else if (choice == 4) target = readNumber("Monthly target (kWh): ", 0, 100000);
        else saveRecords(appliances, target);
    }
    return 0;
}
