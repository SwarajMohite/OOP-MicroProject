// Creator : Mohite Swaraj Sanjay

#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <thread> // for sleep
#include <chrono>

using namespace std;

class User {
private:
    char username[20];
    char password[20];

public:
    User(const char* user, const char* pass) {
        strncpy(username, user, sizeof(username) - 1);
        username[sizeof(username) - 1] = '\0';
        strncpy(password, pass, sizeof(password) - 1);
        password[sizeof(password) - 1] = '\0';
    }

    const char* getUsername() const { return username; }
    const char* getPassword() const { return password; }
};

class UserManager {
private:
    vector<User> users;

public:
    void registerUser(const char* user, const char* pass) {
        users.emplace_back(user, pass);
        cout << "Successfully Created Account!" << endl;
    }

    bool loginUser(const char* user, const char* pass) {
        for (const auto& u : users) {
            if (strcmp(u.getUsername(), user) == 0 && strcmp(u.getPassword(), pass) == 0) {
                return true;  // Login successful
            }
        }
        return false;  // Login failed
    }
};

class Welcome {
private:
    char name[80], ph_no[15], email[40];
    UserManager userManager;

public:
    void login();
    void registration();
    void welcome_msg(const char* username) {
        cout << endl << "Hey! " << username << endl;
        cout << "Welcome again to Error Detection and Correction\n\n" << endl;
    }

    static int calculateParityBits(int dataBits);
};

void Welcome::registration() {
    cout << "Registration Page" << endl;
    cout << "Enter your name: ";
    cin.ignore();  // To clear the buffer
    cin.getline(name, sizeof(name));
    cout << "Enter your phone no: ";
    cin >> ph_no;
    cout << "Enter your valid email ID: ";
    cin >> email;

    char username[20], password[20];
    cout << "Enter a username: ";
    cin >> username;
    cout << "Enter a password: ";
    cin >> password;

    userManager.registerUser(username, password);
}

void Welcome::login() {
    cout << "Login Page" << endl;
    char log_username[20], log_password[20];
    cout << "Username: ";
    cin >> log_username;
    cout << "Password: ";
    cin >> log_password;

    char captcha[6];
    const char chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    srand(static_cast<unsigned int>(time(0)));

    for (int i = 0; i < 5; i++) {
        captcha[i] = chars[rand() % (sizeof(chars) - 1)];
    }
    captcha[5] = '\0';

    cout << "Captcha: " << captcha << endl;
    char user_input[6];
    cout << "Enter captcha: ";
    cin >> user_input;

    if (strcmp(captcha, user_input) != 0) {
        cout << "Incorrect Captcha!" << endl;
        return;
    }

    if (userManager.loginUser(log_username, log_password)) {
        cout << "Login Successfully!!!" << endl;
        welcome_msg(log_username);
    } else {
        cout << "Invalid username or password!" << endl;
    }
}

int Welcome::calculateParityBits(int dataBits) {
    int parityBits = 0;
    while (pow(2, parityBits) < (dataBits + parityBits + 1)) {
        parityBits++;
    }
    return parityBits;
}

vector<int> insertParityBits(vector<int>& data, int parityBits) {
    int totalBits = data.size() + parityBits;
    vector<int> hammingCode(totalBits, 0);
    int j = 0;
    for (int i = 1; i <= totalBits; i++) {
        if ((i & (i - 1)) != 0) {
            hammingCode[i - 1] = data[j++];
        }
    }
    return hammingCode;
}

void calculateParityBits(vector<int>& hammingCode, int parityBits) {
    int totalBits = hammingCode.size();
    for (int i = 0; i < parityBits; i++) {
        int parityPos = pow(2, i) - 1;
        int parity = 0;
        for (int j = parityPos; j < totalBits; j++) {
            if ((j + 1) & (parityPos + 1)) {
                parity ^= hammingCode[j];
            }
        }
        hammingCode[parityPos] = parity;
    }
}

int detectError(vector<int>& hammingCode, int parityBits) {
    int totalBits = hammingCode.size();
    int errorPosition = 0;
    for (int i = 0; i < parityBits; i++) {
        int parityPos = pow(2, i) - 1;
        int parity = 0;
        for (int j = parityPos; j < totalBits; j++) {
            if ((j + 1) & (parityPos + 1)) {
                parity ^= hammingCode[j];
            }
        }
        if (parity != 0) {
            errorPosition += parityPos + 1;
        }
    }
    return errorPosition;
}

void printHammingCode(const vector<int>& hammingCode) {
    for (int i : hammingCode) {
        cout << i << "  ";
    }
    cout << endl;
}

void introduceRandomErrors(vector<int>& hammingCode, int errorCount) {
    srand(static_cast<unsigned int>(time(0)));
    for (int i = 0; i < errorCount; i++) {
        int pos = rand() % hammingCode.size();
        hammingCode[pos] ^= 1;  // Introduce error by flipping the bit
    }
}

int main() {
    Welcome user;
    int choice;

    cout << "Error Detection and Correction" << endl;

    do {
        cout << "Welcome" << endl;
        cout << "1. Login" << endl;
        cout << "2. Register" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: user.login(); break;
            case 2: user.registration(); break;
            case 3: cout << "Exiting the program. Goodbye!" << endl; return 0;
            default: cout << "Invalid Option! Please try again." << endl; break;
        }

        int dataBits;
        cout << "Enter the number of data bits: ";
        cin >> dataBits;

        vector<int> data(dataBits);
        cout << "Enter the data bits separated by space: ";
        for (int i = 0; i < dataBits; i++) {
            cin >> data[i];
        }

        int parityBits = user.calculateParityBits(dataBits);
        cout << "Number of Parity bits needed: " << parityBits << endl;

        vector<int> hammingCode = insertParityBits(data, parityBits);
        calculateParityBits(hammingCode, parityBits);

        cout << "Hamming code with parity bits: ";
        printHammingCode(hammingCode);

        int errorPosition = detectError(hammingCode, parityBits);
        if (errorPosition == 0) {
            cout << "No errors detected in the Hamming code." << endl;
        } else {
            cout << "Error detected at position: " << errorPosition << endl;
            hammingCode[errorPosition - 1] ^= 1;  // Correct the error
            cout << "Corrected Hamming Code: ";
            printHammingCode(hammingCode);
        }

        int option;
        cout << "Introduce random errors or receiver's data? (1 for random errors, 2 for receiver's data, 0 to exit): ";
        cin >> option;

        if (option == 1) {
            int errorCount;
            cout << "Enter the number of random errors to introduce: ";
            cin >> errorCount;
            introduceRandomErrors(hammingCode, errorCount);
            cout << "Hamming code after introducing random errors: ";
            printHammingCode(hammingCode);

            errorPosition = detectError(hammingCode, parityBits);
            if (errorPosition == 0) {
                cout << "No errors detected in the Hamming code." << endl;
            } else {
                cout << "Error detected at position: " << errorPosition << endl;
                hammingCode[errorPosition - 1] ^= 1;  // Correct the error
                cout << "Corrected Hamming Code: ";
                printHammingCode(hammingCode);
            }
        } else if (option == 2) {
            vector<int> receivedHammingCode(hammingCode.size());
            cout << "Enter the received Hamming Code: ";
            for (int i = 0; i < receivedHammingCode.size(); i++) {
                cin >> receivedHammingCode[i];
            }

            errorPosition = detectError(receivedHammingCode, parityBits);
            if (errorPosition == 0) {
                cout << "No errors detected in the Hamming code." << endl;
            } else {
                cout << "Error detected at position: " << errorPosition << endl;
                receivedHammingCode[errorPosition - 1] ^= 1;  // Correct the error
                cout << "Corrected Hamming Code: ";
                printHammingCode(receivedHammingCode);
            }
        } else if (option == 0) {
            cout << "Exiting the program. Goodbye!" << endl;
            break;
        }

    } while (true);

    return 0;
}
