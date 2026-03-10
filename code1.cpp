#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Patient {
public:
    int id;
    string name;
    int bedNumber;
    bool ventilatorAssigned;
    bool doctorAssigned;
};

class ICU {
private:
    int totalBeds;
    int availableBeds;

    int totalVentilators;
    int availableVentilators;

    int totalDoctors;
    int availableDoctors;

    vector<bool> bedOccupied;
    vector<Patient> patients;

public:

    ICU(int beds, int ventilators, int doctors) {
        totalBeds = beds;
        availableBeds = beds;

        totalVentilators = ventilators;
        availableVentilators = ventilators;

        totalDoctors = doctors;
        availableDoctors = doctors;

        bedOccupied.resize(beds, false);
    }

    void admitPatient() {

        if (availableBeds == 0) {
            cout << "\nNo ICU beds available!\n";
            return;
        }

        Patient p;

        cout << "\nEnter Patient ID: ";
        cin >> p.id;

        cin.ignore();
        cout << "Enter Patient Name: ";
        getline(cin, p.name);

        for (int i = 0; i < totalBeds; i++) {

            if (!bedOccupied[i]) {
                bedOccupied[i] = true;
                p.bedNumber = i + 1;
                availableBeds--;
                break;
            }
        }

        char choice;

        cout << "Assign Ventilator? (y/n): ";
        cin >> choice;

        if ((choice == 'y' || choice == 'Y') && availableVentilators > 0) {
            p.ventilatorAssigned = true;
            availableVentilators--;
        }
        else {
            p.ventilatorAssigned = false;
        }

        if (availableDoctors > 0) {
            p.doctorAssigned = true;
            availableDoctors--;
        }
        else {
            p.doctorAssigned = false;
        }

        patients.push_back(p);

        cout << "\nPatient admitted to Bed " << p.bedNumber << endl;
    }

    void dischargePatient() {

        int id;
        cout << "\nEnter Patient ID to discharge: ";
        cin >> id;

        for (int i = 0; i < patients.size(); i++) {

            if (patients[i].id == id) {

                int bed = patients[i].bedNumber - 1;

                bedOccupied[bed] = false;
                availableBeds++;

                if (patients[i].ventilatorAssigned)
                    availableVentilators++;

                if (patients[i].doctorAssigned)
                    availableDoctors++;

                patients.erase(patients.begin() + i);

                cout << "Patient discharged successfully!\n";
                return;
            }
        }

        cout << "Patient not found!\n";
    }

    void showResources() {

        cout << "\n===== ICU Resource Status =====\n";

        cout << "Total Beds: " << totalBeds << endl;
        cout << "Available Beds: " << availableBeds << endl;

        cout << "Total Ventilators: " << totalVentilators << endl;
        cout << "Available Ventilators: " << availableVentilators << endl;

        cout << "Total Doctors: " << totalDoctors << endl;
        cout << "Available Doctors: " << availableDoctors << endl;
    }

    void showPatients() {

        if (patients.empty()) {
            cout << "\nNo patients admitted.\n";
            return;
        }

        cout << "\n===== ICU Patients =====\n";

        for (auto p : patients) {

            cout << "ID: " << p.id
                << " | Name: " << p.name
                << " | Bed: " << p.bedNumber
                << " | Ventilator: " << (p.ventilatorAssigned ? "Yes" : "No")
                << " | Doctor: " << (p.doctorAssigned ? "Assigned" : "Not Assigned")
                << endl;
        }
    }

    void usageReport() {

        cout << "\n===== ICU Usage Report =====\n";

        int usedBeds = totalBeds - availableBeds;
        int usedVentilators = totalVentilators - availableVentilators;
        int usedDoctors = totalDoctors - availableDoctors;

        cout << "Beds Used: " << usedBeds << "/" << totalBeds << endl;
        cout << "Ventilators Used: " << usedVentilators << "/" << totalVentilators << endl;
        cout << "Doctors Assigned: " << usedDoctors << "/" << totalDoctors << endl;

        cout << "Total Patients: " << patients.size() << endl;
    }
};

int main() {

    ICU icu(10, 5, 4);

    int choice;

    do {

        cout << "\n===== ICU Resource Monitoring System =====\n";
        cout << "1. Admit Patient\n";
        cout << "2. Discharge Patient\n";
        cout << "3. View ICU Resources\n";
        cout << "4. View Patients\n";
        cout << "5. Usage Report\n";
        cout << "6. Exit\n";

        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            icu.admitPatient();
            break;

        case 2:
            icu.dischargePatient();
            break;

        case 3:
            icu.showResources();
            break;

        case 4:
            icu.showPatients();
            break;

        case 5:
            icu.usageReport();
            break;

        case 6:
            cout << "Exiting program...\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }

    } while (choice != 6);

    return 0;
}