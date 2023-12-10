#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
using namespace std;

struct PasswordEntry {
    string website;
    string username;
    string password;
};

class PasswordManager {
private:
    vector<PasswordEntry> passwordDatabase;

public:
    void addPassword(const string& website, const string& username, const string& password) {
        PasswordEntry entry;
        entry.website = website;
        entry.username = username;
        entry.password = password;
        passwordDatabase.push_back(entry);
    }

    void viewPasswords() {
        if (passwordDatabase.empty()) {
            cout << "No passwords stored yet." << endl;
            return;
        }

        cout << "Stored Passwords:\n";
        for (const PasswordEntry& entry : passwordDatabase) {
            cout << "Website: " << entry.website << " | Username: " << entry.username << " | Password: " << entry.password << endl;
        }
    }

    void savePasswordsToFile(const string& filename) {
        ofstream file(filename);
        if (file.is_open()) {
            for (const PasswordEntry& entry : passwordDatabase) {
                file << entry.website << "," << entry.username << "," << entry.password << "\n";
            }
            file.close();
            cout << "Passwords saved to " << filename << endl;
        } else {
            cerr << "Error: Could not save passwords to file." << endl;
        }
    }

    void loadPasswordsFromFile(const string& filename) {
        passwordDatabase.clear(); // Clear existing passwords
        ifstream file(filename);
        if (file.is_open()) {
            PasswordEntry entry;
            string line;
            while (getline(file, line)) {
                size_t pos = line.find(",");
                if (pos != string::npos) {
                    entry.website = line.substr(0, pos);
                    line = line.substr(pos + 1);
                    pos = line.find(",");
                    if (pos != string::npos) {
                        entry.username = line.substr(0, pos);
                        entry.password = line.substr(pos + 1);
                        passwordDatabase.push_back(entry);
                    }
                }
            }
            file.close();
            cout << "Passwords loaded from " << filename << endl;
        } else {
            cerr << "Error: Could not load passwords from file." << endl;
        }
    }
};

int main() {
    PasswordManager passwordManager;
    string filename = "passwords.txt";

    while (true) {
        cout << "Password Manager Menu:\n";
        cout << "1. Add Password\n";
        cout << "2. View Passwords\n";
        cout << "3. Save Passwords to File\n";
        cout << "4. Load Passwords from File\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                string website, username, password;
                cout << "Enter Website: ";
                cin >> website;
                cout << "Enter Username: ";
                cin >> username;
                cout << "Enter Password: ";
                cin >> password;
                passwordManager.addPassword(website, username, password);
                break;
            }
            case 2:
                passwordManager.viewPasswords();
                break;
            case 3:
                passwordManager.savePasswordsToFile(filename);
                break;
            case 4:
                passwordManager.loadPasswordsFromFile(filename);
                break;
            case 5:
                cout << "Exiting the Password Manager." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }

    return 0;
}