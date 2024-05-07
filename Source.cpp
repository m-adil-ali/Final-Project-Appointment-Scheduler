#include <iostream>
#include <string>
#include <cctype>

using namespace std;

const int MAX_APPOINTMENTS = 100;

void date(int& day, int& month, int& year) {
    int currentYear = 2024;  
    int currentMonth = 1;
    int currentDay = 15;

    while (true) {
        cout << "Enter date (1-31): ";
        while (true)
        {
            cin >> day;
            if (cin.fail() || (day <= 0 || day > 31)) {
                cin.clear(); 
                cin.ignore(100, '\n'); 
                cout << "Invalid date. Please enter a date between 1 and 31.\n";
                continue;
            }
            else if (day >= 1 || day <= 31) {
                break;
            }
        }
        cout << "Enter month (1-12): ";
        while (true)
        {
            cin >> month;
            if (cin.fail() || (month <= 0 || month >= 13)) {
                cin.clear(); 
                cin.ignore(100 , '\n');
                cout << "Invalid month. Please enter a month between 1 and 12.\n";
                continue;
            }
            else if (month >= 1 || month <= 12) {
                break;
            }
        }

        cout << "Enter year (2024): ";
        while (true)
        {
            cin >> year;
            if (cin.fail() || (year < currentYear || year > 2025)) {
                cin.clear();
                cin.ignore(100, '\n');
                cout << "Invalid year. Please enter a year between " << currentYear << " and 2025.\n";
                continue;
            }
            else if (month >= 1 || month <= 12) {
                break;
            }
        }
        if (year == currentYear) {
            if (month < currentMonth) {
                cout << "Invalid date. Please enter a date in the current month or later.\n";
                continue;
            }
            else if (month == currentMonth && day < currentDay) {
                cout << "Invalid date. Please enter a date on or after today.\n";
                continue;
            }
        }
        // Check for month February as it can't have 30 days)
        if (month == 2 && day > 29) {
            cout << "Invalid date for February. Please enter a day between 1 and 29 (or 28 for non-leap years).\n";
            continue;
        }
        else if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
            cout << "invalid date. months 4, 6, 9, and 11 have only 30 days.\n";
            continue;
        }

        break;  
    }
}
void time(int& hour, int& minute, string& amPm) {
    while (true) {
        cout << "Enter hour (1-12): ";
        while (true)
        {
            cin >> hour;
            if (cin.fail() || (hour < 1 || hour > 12)) {
                cin.clear(); 
                cin.ignore(100, '\n'); 
                cout << "Invalid hour. Please enter an hour between 1 and 12.\n";
                continue;
            }
            else if (hour >= 1 || hour <= 12) {
                break;
            }
        }
        cout << "Enter minute (0-59): ";
        while (true)
        {
            cin >> minute;
            if (cin.fail() || (minute < 0 || minute > 59)) {
                cin.clear();
                cin.ignore(100, '\n');
                cout << "Invalid minute. Please enter a minute between 0 and 59.\n";
                continue;
            }
            else if (minute >= 1 || minute <= 59) {
                break;
            }
        }
        cout << "Enter AM or PM: ";
        while (true)
        {
            cin >> amPm;
            for (char& ch : amPm) {
                ch = toupper(ch);
            }
            if (cin.fail() || ((amPm != "AM") && (amPm != "PM"))) {
                cin.clear();
                cin.ignore(100, '\n');
                cout << "Invalid AM/PM. Please enter AM or PM.\n";
                continue;
            } 
            break;
        }
        break;
    }
}
class Appointment {

    int appDate;
    int appTime;
    int id = 1;
    string description;

protected:
    


public:
    int minute, hour, day, month, year;
    string amPm;

    void setToken(int id) {
        this->id = id;
        cout << "Token number# " << id << endl;
    }
    int getToken() const {
        return id;
    }
    void setAppDate() {
        date(day, month, year);
        // Combine the date components into a single integer (e.g., YYYYMMDD)
        appDate = year * 10000 + month * 100 + day;
    }
    int getAppDate() const {
        // Extract date components from appDate
        return appDate;
    }
    void setAppTime() {
        time(hour, minute, amPm);
        appTime = hour * 100 + minute;
    }
    int getAppTime() const {

        return appTime;
    }
    void setDescription() {

        cout << "Enter description: " << endl;
        cin.ignore();
        getline(cin, description);
    }
    string getDescription() const {
        return description;
    }
    void displayAppointment() {
        year = appDate / 10000;
        month = (appDate % 10000) / 100;
        day = appDate % 100;
        hour = appTime / 100;
        minute = appTime % 100;

        cout << "Token# " << id << endl;
        cout << "Appointment date MM/DD/YYYY: " << month << "/" << day << "/" << year << endl;
        cout << "Appointment time HH:MM AM/PM: " << hour << ":" << minute << " " << amPm << endl;
        cout << "Your description: " << description << endl << endl;
    }
};
bool isGreater(const Appointment& app1, const Appointment& app2) {
    if (app1.getAppDate() != app2.getAppDate()) {
        // Dates are different, compare directly
        return app1.getAppDate() > app2.getAppDate();
    }
    else if (app1.amPm == "PM" && app2.amPm == "AM") {
        return true;
    }
    else if (app1.amPm == "AM" && app2.amPm == "PM") {
        return false;
    }
    else if (app1.getAppTime() == app2.getAppTime()) {
        if (app1.amPm == "PM" && app2.amPm == "AM") {
            return true;
        }
        else if (app1.amPm == "AM" && app2.amPm == "PM") {
            return false;
        }
    }
    else
        return app1.getAppTime() > app2.getAppTime();
}
void swapAppointments(Appointment& app1, Appointment& app2) {
    Appointment temp = app1;
    app1 = app2;
    app2 = temp;
}

int appointSearch(int tokenToSearch, int currentAppointmentIndex, const Appointment appointments[])
{
    for (int i = 0; i < currentAppointmentIndex; i++) {
        if (appointments[i].getToken() == tokenToSearch) {
            return i;
        }
    }
    return -1;
}
bool checkConflict(const Appointment& newAppointment, const Appointment existingAppointments[], int currentAppointmentIndex) {
    for (int i = 0; i < currentAppointmentIndex; i++) {
        if (newAppointment.getAppDate() == existingAppointments[i].getAppDate() &&
            newAppointment.getAppTime() == existingAppointments[i].getAppTime() &&
            newAppointment.amPm == existingAppointments[i].amPm) {
            cout << "Kindly change date or time! Another appointment exists at the same date and time.\n\n";
            return true;
        }
    }
    return false;
}
void menu()
{
    cout << "+----------------------+\n";
    cout << "\tMenu\n";
    cout << "+----------------------+\n";
    cout << "1) Add Appointment    ->\n";
    cout << "2) View Appointments  ->\n";
    cout << "3) Edit Appointment   ->\n";
    cout << "4) Delete Appointment ->\n";
    cout << "5) Sort Appointments  ->\n";
    cout << "6) Reminder           ->\n";
    cout << "7) Exit               ->\n";
    cout << "+----------------------+\n";
}

int main() {
    Appointment appointments[MAX_APPOINTMENTS];
    int id = 1;
    int currentAppointmentIndex = 0;

    cout << "*--------------------------------------------------*\n";
    cout << "\tWelcome to the Appointment Manager\t" << endl;
    cout << "*--------------------------------------------------*\n\n";

    while (1) {
        int choose;
        while (true)
        {
            menu();
            cout << "choose an option-> ";
            cin >> choose;
            if (cin.fail() || (choose > 7 || choose <= 0)) {
                cin.clear(); 
                cin.ignore(100, '\n'); 
                cout << "\nInvalid input! Please enter a valid menu option (1-7).\n\n";
                continue;
            }
            else if (choose >= 1 || choose <= 7) {
                break;
            }
        }
        if (choose == 1) { // Add appointment
            if (currentAppointmentIndex < MAX_APPOINTMENTS) {
                Appointment newAppointment;
                cout << endl;
                newAppointment.setToken(id);
                newAppointment.setAppDate();
                newAppointment.setAppTime();

                // Check for conflicts
                if (!checkConflict(newAppointment, appointments, currentAppointmentIndex)) {
                    newAppointment.setDescription();
                    appointments[currentAppointmentIndex] = newAppointment;

                    cout << "\nAppointment with the token# " << id << " has been added successfully\n\n";
                    id++;
                    currentAppointmentIndex++;
                }
            }
            else {
                cout << "\nMaximum number of appointments reached.\n\n";
            }
        }
        else if (choose == 2) { // View appointments
            if (currentAppointmentIndex >= 1) {
                for (int i = 0; i < currentAppointmentIndex; i++) {
                    appointments[i].displayAppointment();
                }
            }
            else { cout << "Not enough appointments to view\n\n"; }
        }
        else if (choose == 3) { // Edit appointment
            if (currentAppointmentIndex >= 1) {
                int tokenToEdit;
                while (true)
                {
                    cout << "Enter the token number of the appointment that you want to edit: ";
                    cin >> tokenToEdit;
                    if (cin.fail() || (tokenToEdit > 100 || tokenToEdit <= 0)) {
                        cin.clear(); 
                        cin.ignore(100, '\n'); 
                        cout << "Invalid input! Please enter a valid token number to edit.\n";
                        continue;
                    }
                    else if (tokenToEdit >= 1 || tokenToEdit <= 100) {
                        break;
                    }
                }
                
                if (tokenToEdit >= 1 || tokenToEdit <= 100) {
                    int appointmentIndex = appointSearch(tokenToEdit, currentAppointmentIndex, appointments);
                    if (appointmentIndex != -1)
                    {   
                        while (true) { // Edit date
                            cout << "Do you want to edit the date? (y/n): ";
                            char editDateChoice;
                            cin >> editDateChoice;
                            char lowerdatechoice = tolower(editDateChoice);

                            if (cin.fail() || (lowerdatechoice != 'y' && lowerdatechoice != 'n')) {
                                cin.clear(); 
                                cin.ignore(100, '\n'); 
                                cout << "Invalid input! Please enter 'y' for yes or 'n' for no.\n";
                            }
                            else {
                                if (lowerdatechoice == 'y') {
                                    appointments[appointmentIndex].setAppDate();
                                }
                                break;
                            }
                        }
                        while (true) {// Edit time 
                            cout << "Do you want to edit the Time? (y/n): ";
                            char editTimeChoice;
                            cin >> editTimeChoice;
                            char lowerTimeChoice = tolower(editTimeChoice);

                            if (cin.fail() || (lowerTimeChoice != 'y' && lowerTimeChoice != 'n')) {
                                cin.clear(); 
                                cin.ignore(100, '\n');
                                cout << "Invalid input! Please enter 'y' for yes or 'n' for no.\n";
                            }
                            else {
                                if (lowerTimeChoice == 'y') {
                                    appointments[appointmentIndex].setAppTime();
                                }
                                break;
                            }
                        }
                        // Edit description
                        while (true) {
                            cout << "Do you want to edit the description? (y/n): ";
                            char editDescriptionChoice;
                            cin >> editDescriptionChoice;
                            char lowerDescChoice = tolower(editDescriptionChoice);

                            if (cin.fail() || (lowerDescChoice != 'y' && lowerDescChoice != 'n')) {
                                cin.clear(); 
                                cin.ignore(100, '\n'); 
                                cout << "Invalid input! Please enter 'y' for yes or 'n' for no.\n";
                            }
                            else {
                                if (lowerDescChoice == 'y') {
                                    appointments[appointmentIndex].setDescription();
                                }
                                break;
                            }
                        }
                        cout << "Appointment with token# " << tokenToEdit << " has been edited successfully.\n\n";
                    }
                    else
                    {
                        cout << "Appointment with token " << tokenToEdit << " not found.\n\n";
                    }
                }
            }
            else { cout << "Not enough appointments to edit\n\n"; }
        }
        else if (choose == 4) { // Delete Appointment
            if (currentAppointmentIndex >= 1) {
                int tokenToDelete;
                while (true)
                {
                    cout << "Enter the token number of the appointment that you want to delete: ";
                    cin >> tokenToDelete;
                    if (cin.fail() || (tokenToDelete > 100 || tokenToDelete <= 0)) {
                        cin.clear(); 
                        cin.ignore(100, '\n'); 
                        cout << "Invalid input! Please enter a valid token number to delete.\n";
                        continue;
                    }
                    else if (tokenToDelete >= 1 || tokenToDelete <= 100) {
                        break;
                    }
                }
                int appointmentIndex = appointSearch(tokenToDelete, currentAppointmentIndex, appointments);
                if (appointmentIndex != -1) {
                    // Shift elements to remove the appointment
                    for (int i = appointmentIndex; i < currentAppointmentIndex - 1; i++) {
                        appointments[i] = appointments[i + 1];
                    }
                    currentAppointmentIndex--;

                    cout << "Appointment with token# " << tokenToDelete << " has been deleted successfully\n\n";
                }
                else {
                    cout << "Appointment with token " << tokenToDelete << " not found.\n\n";
                }
            }
            else {
                cout << "Not enough appointments to delete\n\n";
            }
        }
        else if (choose == 5) { // Sort appointments
            if (currentAppointmentIndex >= 2) {
                int i, j;
                bool swapped = false;
                for (i = 0; i < currentAppointmentIndex; i++) {
                    for (j = 0; j < currentAppointmentIndex - i - 1; j++) {
                        if (isGreater(appointments[j], appointments[j + 1])) {
                            swapAppointments(appointments[j], appointments[j + 1]);
                            swapped = true;
                        }
                    }
                }
                if (!swapped) {
                    cout << "Appointments are already in sorted form\n\n";
                }
                else {
                    cout << "Appointments have been sorted successfully as per date and time\n\n";
                }
            }
            else {
                cout << "Not enough appointments to sort\n\n";
            }
        }
        else if (choose == 6) // Reminder
        {
            if (currentAppointmentIndex >= 1) {
                int i, j;
                bool swapped = false;
                for (i = 0; i < currentAppointmentIndex; i++) {
                    for (j = 0; j < currentAppointmentIndex - i - 1; j++) {
                        if (isGreater(appointments[j], appointments[j + 1])) {
                            swapAppointments(appointments[j], appointments[j + 1]);
                            swapped = true;
                        }
                    }
                    cout << "Reminder:" << endl;
                    appointments[i].displayAppointment();
                }
            }
            else { cout << "Not enough appointments to give reminder\n\n"; }
        }
        else if (choose == 7) { //Exit
            cout << endl;
            cout << "*-----------------------------------------------------*\n";
            cout << "\tThanks for visiting Appointment Manager\n";
            cout << "*-----------------------------------------------------*\n";
            return 0;
        }
    }
}
