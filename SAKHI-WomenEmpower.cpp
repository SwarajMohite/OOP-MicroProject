// Creator : Mohite Swaraj Sanjay

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <string>

using namespace std;

// Node for account
struct Node {
    char name[20];
    int sakhi_id;
    long double phone_no;
    char pass[20];
    char appliedScheme[50]; // Stores the applied scheme
    Node* next;
};

// Base class for shared attributes
class Individual {
protected:
    string s_name, m_name, f_name, h_name, no_child, rgln, caste, dd, mm, yy;

public:
    void inputBasicDetails() {
        char choice;
        cout << "\t\t\t--> Enter Your Name: ";
        cin.ignore();
        getline(cin, s_name);
        cout << "\t\t\t--> Enter Mother Name: ";
        getline(cin, m_name);
        cout << "\t\t\t--> Enter Father Name: ";
        getline(cin, f_name);
        
        while (true) {
            cout << "\t\t\t--> Married or not? (y/n): ";
            cin >> choice;
            cin.ignore();

            if (choice == 'y' || choice == 'Y') {
                cout << "\t\t\t--> Enter Husband Name: ";
                getline(cin, h_name);
                cout << "\t\t\t--> How many children do you have?: ";
                getline(cin, no_child);
                break;
            } else if (choice == 'n' || choice == 'N') {
                break;
            } else {
                cout << "Invalid Choice! Please enter 'y' or 'n'.\n";
            }
        }

        cout << "\t\t\t--> Enter Religion: ";
        cin >> rgln;
        cout << "\t\t\t--> Enter Caste: ";
        cin >> caste;
        cout << "\t\t\t--> Enter Birth Date (DD/MM/YY): ";
        cin >> dd >> mm >> yy;
    }

    void displayPersonalInfo() {
        cout << "\nPersonal Information:\n";
        cout << "Name: " << s_name << "\nMother's Name: " << m_name
             << "\nFather's Name: " << f_name << "\nReligion: " << rgln
             << "\nCaste: " << caste << "\nBirth Date: " << dd << "/" << mm << "/" << yy << endl;
        if (!h_name.empty()) {
            cout << "Husband's Name: " << h_name << "\nNumber of Children: " << no_child << endl;
        }
    }
};

// Class for managing schemes
class SakhiScheme {
private:
    struct Scheme {
        char name[50];
        char description[100];
    };

    Scheme schemes[8]; // Adjust size based on number of schemes
    int schemeCount;

public:
    SakhiScheme() {
        schemeCount = 0;
        strcpy(schemes[schemeCount].name, "Mahila Udyam Nidhi");
        strcpy(schemes[schemeCount++].description, "Financial assistance for women entrepreneurs.");
        strcpy(schemes[schemeCount].name, "Beti Bachao Beti Padhao");
        strcpy(schemes[schemeCount++].description, "Empowerment of girls through education.");
        strcpy(schemes[schemeCount].name, "Women’s Self-Help Groups");
        strcpy(schemes[schemeCount++].description, "Support for women to start their own businesses.");
        strcpy(schemes[schemeCount].name, "Mahila Kisan Sashaktikaran Pariyojana");
        strcpy(schemes[schemeCount++].description, "Support for women farmers through training and resources.");
        strcpy(schemes[schemeCount].name, "Kanyadan Yojana");
        strcpy(schemes[schemeCount++].description, "Financial assistance for the marriage of daughters.");
        strcpy(schemes[schemeCount].name, "Shivshahir Babasaheb Purandare Yojana");
        strcpy(schemes[schemeCount++].description, "Support for women artisans and craftsmen.");
        strcpy(schemes[schemeCount].name, "Balika Samridhi Yojana");
        strcpy(schemes[schemeCount++].description, "Support for the education of the girl child.");
        strcpy(schemes[schemeCount].name, "Pradhan Mantri Awas Yojana");
        strcpy(schemes[schemeCount++].description, "Housing for all, focusing on women's empowerment in housing.");
    }

    void displaySchemes() {
        cout << "\nAvailable Schemes for Women:\n";
        for (int i = 0; i < schemeCount; i++) {
            cout << i + 1 << ". " << schemes[i].name << endl;
        }
    }

    const char* getScheme(int index) {
        return schemes[index].name;
    }

    const char* getDescription(int index) {
        return schemes[index].description;
    }

    int getSchemeCount() {
        return schemeCount;
    }

    void apply(Individual& individual, Node* userNode) {
        displaySchemes();
        int choice;
        cout << "\nChoose a scheme (1-" << schemeCount << "): ";
        cin >> choice;

        if (choice < 1 || choice > schemeCount) {
            cout << "Invalid choice. Please try again.\n";
            return;
        }

        cout << "\nScheme Selected: " << schemes[choice - 1].name << endl;
        cout << "Details: " << schemes[choice - 1].description << endl;

        char apply;
        cout << "Do you want to apply for this scheme? (Y/N): ";
        cin >> apply;

        if (apply == 'Y' || apply == 'y') {
            individual.inputBasicDetails();
            strcpy(userNode->appliedScheme, schemes[choice - 1].name);
            cout << "\nApplication submitted for: " << schemes[choice - 1].name << endl;
        } else {
            cout << "You chose not to apply.\n";
        }
    }
};

// Sakhi class combining all functionalities
class Sakhi : public Individual {
private:
    Node* start;
    Node* temp;
    Node* current;
    Node* foundNode;
    SakhiScheme schemeManager;

public:
    Sakhi() : start(nullptr) {}

    void createAccount();
    Node* initializeAccount(int);
    int searchAccount(int);
    void login();
    void displayOptions(int);
    void signup();
    void showAppliedScheme(Node* userNode);
    void updatePersonalInfo(Node* userNode);

    int countDigits(int num) {
        int count = 0;
        while (num != 0) {
            num /= 10;
            count++;
        }
        return count;
    }
};

Node* Sakhi::initializeAccount(int mode) {
    char password[20];
    int id, exists;

    temp = new Node();
    strcpy(temp->appliedScheme, "");

    do {
        if (mode == 1) {
            cout << "\nEnter 4-digit ID: ";
            cin >> id;
        } else {
            do {
                cout << "\nEnter ID to create account: ";
                cin >> id;
                exists = searchAccount(id);
                if (exists) {
                    cout << "\nID already exists. Please enter a different ID.\n";
                }
            } while (exists);
        }

        if (countDigits(id) == 4) {
            temp->sakhi_id = id;
            break;
        } else {
            cout << "Invalid ID. It should contain 4 digits.\n";
        }
    } while (true);

    cout << "\nEnter username: ";
    cin >> temp->name;

    do {
        cout << "\nEnter password (minimum 6 characters): ";
        cin >> password;
        if (strlen(password) >= 6) {
            strcpy(temp->pass, password);
            break;
        } else {
            cout << "Invalid Password.\n";
        }
    } while (true);

    char hasPhone;
    cout << "Do you have a mobile number (Y/N)? ";
    cin >> hasPhone;
    if (hasPhone == 'Y' || hasPhone == 'y') {
        cout << "\nEnter your mobile number: ";
        cin >> temp->phone_no;
    }

    temp->next = nullptr;
    return temp;
}

int Sakhi::searchAccount(int id) {
    current = start;
    while (current != nullptr) {
        if (current->sakhi_id == id) {
            foundNode = current;
            return 1; // Found
        }
        current = current->next;
    }
    return 0; // Not found
}

void Sakhi::createAccount() {
    if (start == nullptr) {
        temp = initializeAccount(1);
        start = temp;
    } else {
        temp = initializeAccount(0);
        current = start;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = temp;
    }
    cout << "\n\033[1;33mAccount created successfully\033[0m\n\n";
}

void Sakhi::login() {
    char username[20];
    int id;
    char password[20];
    int retry;

    do {
        cout << "\t\t\t-->Enter your account ID: ";
        cin >> id;
        int found = searchAccount(id);
        if (found) {
            cout << "\t\t\t-->Enter your username: ";
            cin >> username;
            if (strcmp(username, foundNode->name) == 0) {
                cout << "\t\t\t-->Enter your password: ";
                cin >> password;
                if (strcmp(password, foundNode->pass) == 0) {
                    cout << "\n\033[1;32mLogin successful\033[0m\n"; // Using ANSI codes for color
                    displayOptions(id);
                    return;
                } else {
                    cout << "\033[1;31mInvalid password. Please try again.\033[0m\n";
                }
            } else {
                cout << "\033[1;31mInvalid username. Please try again.\033[0m\n";
            }
        } else {
            cout << "\033[1;31mInvalid ID. Please try again.\033[0m\n";
            break;
        }
        cout << "Press 1 to Retry: ";
        cin >> retry;
    } while (retry == 1);
}

void Sakhi::showAppliedScheme(Node* userNode) {
    if (strlen(userNode->appliedScheme) > 0) {
        cout << "\033[1;32m\nYou have applied for the scheme: " << userNode->appliedScheme << "\033[0m\n";
    } else {
        cout << "\nYou have not applied for any scheme yet." << endl;
    }
}

void Sakhi::updatePersonalInfo(Node* userNode) {
    cout << "\n\t\t\t\tUpdate Personal Information:\n";
    cout << "\n\t\t\t\t1. Update Name\n\t\t\t\t2. Update Phone Number\n\t\t\t\t3. View Personal Info\n\t\t\t\t4. Back\n";
    int choice;
    cin >> choice;

    switch (choice) {
        case 1:
            cout << "\t\t\t-->Enter new name: ";
            cin.ignore();
            cin.getline(userNode->name, 20);
            cout << "\033[1;32mName updated successfully!\033[0m\n";
            break;
        case 2:
            cout << "\t\t\t-->Enter new phone number: ";
            cin >> userNode->phone_no;
            cout << "\033[1;32mPhone number updated successfully!\033[0m\n";
            break;
        case 3:
            displayPersonalInfo();
            break;
        case 4:
            return;
        default:
            cout << "\033[1;31mInvalid choice\n\033[0m";
    }
}

void Sakhi::displayOptions(int id) {
    int choice;
    do {
        cout << "\t\t\t\t----------------------------------------------------------\n";
        cout << "\n\t\t\t\t1. Scheme Details\n\t\t\t\t2. Apply for Scheme\n\t\t\t\t3. Show Applied Scheme\n\t\t\t\t4. Update Personal Info\n\t\t\t\t5. Exit\n";
        cout << "\n\t\t\t-->Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int schemeChoice;
                do {
                    schemeManager.displaySchemes();
                    
                    cout << "Choose a scheme to see details (1-" << schemeManager.getSchemeCount() << ", 0 to exit): " << endl;
                    cin >> schemeChoice;

                    if (schemeChoice > 0 && schemeChoice <= schemeManager.getSchemeCount()) {
                        cout << "\nScheme: " << schemeManager.getScheme(schemeChoice - 1) << endl << endl;
                        cout << "Details: " << schemeManager.getDescription(schemeChoice - 1) << endl <<endl << endl;
                    } else if (schemeChoice == 0) {
                        cout << "Exiting scheme details...\n";
                    } else {
                        cout << "Invalid choice. Please try again.\n";
                    }
                } while (schemeChoice != 0);
                break;
            }
            case 2:
                schemeManager.apply(*this, foundNode);
                break;
            case 3:
                showAppliedScheme(foundNode);
                break;
            case 4:
                updatePersonalInfo(foundNode); // Update personal info
                break;
            case 5:
                cout << "Exiting...\n";
                exit(0);
            default:
                cout << "\033[1;31mInvalid choice\n\033[0m";
        }
        cout << "Press any key to continue...\n";
        cin.ignore();
        cin.get(); // Wait for a key press
    } while (true);
}

void Sakhi::signup() {
    createAccount();
}

void displayBorder() {
    cout << "\n\t\t\t\t=========================================\n";
}

void displayWelcome() {
    displayBorder();
    cout << "\n\t\t\t\t\033[1;32mWelcome to the SAKHI Bot - Empowering Women\033[0m" << endl;
    displayBorder();
}

void displayMenu(Sakhi &S) {
    char choice;
    do {
        cout << "\t\t\t\t-------------------------------------" << endl;
        cout << "\n\t\t\t\t |    \033[1;32mSAKHI - EMPOWERING WOMEN\033[0m    | " << endl;
        cout << "\n\t\t\t\t-------------------------------------" << endl;
        cout << "\t\t\t\t 1. Sign Up " << endl;
        cout << "\t\t\t\t 2. Login " << endl;
        cout << "\t\t\t\t 3. Exit " << endl;
        cout << "\t\t\t\t-------------------------------------" << endl;
        cout << "\t\t\t\t  Choose Option : [ 1 / 2 / 3 ]" << endl;
        cout << "\t\t\t\t-------------------------------------" << endl;
        cout << " --> Please Enter Your Choice : ";
        cin >> choice;

        switch (choice) {
            case '1':
                S.signup();
                break;
            case '2':
                S.login();
                break;
            case '3':
                exit(0);
            default:
                cout << "\033[1;31mInvalid choice! Please try again.\033[0m\n";
                continue; // Go back to menu if invalid
        }

    } while (true);
}

int main() {
    displayWelcome();
    Sakhi S;
    displayMenu(S);
    return 0;
}
