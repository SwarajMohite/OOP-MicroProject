// Creator : Nalawade Sarthak Balu 

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <stdexcept>
#include <vector>
#include <ctime>

using namespace std;

// Base class for shared attributes
class Person {
protected:
    string s_name, m_name, f_name, c_name, cr_name, roll_no, rgln, dd, mm, yy;

public:
    void inputBasicDetails() {
        cout << "\t\t\t--> Enter Your Name : ";
        cin.ignore();
        getline(cin, s_name);
        cout << "\t\t\t--> Enter Mother Name : ";
        getline(cin, m_name);
        cout << "\t\t\t--> Enter Father Name : ";
        getline(cin, f_name);
        cout << "\t\t\t--> Enter College Name : ";
        getline(cin, c_name);
        cout << "\t\t\t--> Enter Course Name : ";
        getline(cin, cr_name);
        cout << "\t\t\t--> Enter Roll Number  : ";
        cin >> roll_no;
        cout << "\t\t\t--> Enter Regulation : ";
        cin >> rgln;
        cout << "\t\t\t--> Enter Birth Date (DD/MM/YY) : ";
        cin >> dd >> mm >> yy;
    }
};

// Interface for operations
class StudentOperations {
public:
    virtual void insert() = 0;
    virtual void display() = 0;
    virtual void deleted() = 0;
};

// Derived class for student-specific attributes and methods
class Student : public Person, public StudentOperations {
private:
    string grade, result;
    float per;
    int oop, dbms, dte, cn, pic, sum;

public:
    void menu();
    void insert() override;
    void display() override;
    void deleted() override;

    // User management
    void registerUser();
    void loginUser();
    bool authenticateUser();
};

// User registration function
void Student::registerUser() {
    string username, password;
    cout << "Register a new user\n";
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    ofstream outfile("users.txt", ios::app);
    if (!outfile.is_open()) {
        throw runtime_error("Error opening file for writing.");
    }
    outfile << username << " " << password << endl;
    outfile.close();
    cout << "Registration successful!\n";
}

// User login function
void Student::loginUser() {
    string username, password, fileUsername, filePassword;
    cout << "Login\n";
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    ifstream infile("users.txt");
    if (!infile.is_open()) {
        throw runtime_error("Error opening file for reading.");
    }
    bool loggedIn = false;
    while (infile >> fileUsername >> filePassword) {
        if (fileUsername == username && filePassword == password) {
            loggedIn = true;
            break;
        }
    }
    infile.close();
    if (loggedIn) {
        cout << "Login successful! Welcome, " << username << "!\n";
    } else {
        cout << "Invalid username or password.\n";
        loginUser();  // Reask for login
    }
}

// Authenticate user before accessing the system
bool Student::authenticateUser() {
    int choice;
    do {
        cout << endl;
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                loginUser();
                return true;  // Return true if login is successful
            case 3:
                cout << "Exiting...\n";
                return false;  // Return false if exiting
            default:
                cout << "You entered an invalid option.\n";
        }
    } while (choice != 3);
    return false;
}

// Menu function
void Student::menu() {
    if (!authenticateUser()) {
        return; // Exit if user chooses not to login
    }

    while (true) {
        system("cls");
        int choice;
        char x;
        cout << "\t\t\t\t-------------------------------------" << endl;
        cout << "\n\t\t\t\t |    GOVERNMENT POLYTECHNIC PUNE    | " << endl;
        cout << "\n\n\t\t\t\t-------------------------------------" << endl;
        cout << "\t\t\t\t |    STUDENT MANAGEMENT SYSTEM    | " << endl;
        cout << "\t\t\t\t-------------------------------------" << endl;
        cout << "\t\t\t\t 1. Enter New Record " << endl;
        cout << "\t\t\t\t 2. Display Record " << endl;
        cout << "\t\t\t\t 3. Delete Record " << endl;
        cout << "\t\t\t\t 4. Exit " << endl;
        cout << "\t\t\t\t-------------------------------------" << endl;
        cout << "\t\t\t\t  Choose Option : [ 1 / 2 / 3 / 4 ]" << endl;
        cout << "\t\t\t\t-------------------------------------" << endl;
        cout << " --> Please Enter Your Choice : "; cin >> choice;

        switch (choice) {
            case 1:
                do {
                    insert();
                    cout << "\n--> Add New Record (y/n)";
                    cin >> x;
                } while (x == 'Y' || x == 'y');
                break;

            case 2:
                display();
                break;

            case 3:
                deleted();
                break;

            case 4:
                exit(0);

            default:
                cout << "\n--> Invalid Choice..!! Please Try Again " << endl;
        }

        system("pause"); // Wait for user input before clearing the screen
    }
}

// Insert function
void Student::insert() {
    fstream file;

    system("cls");
    cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "\t\t\t\t\t\t | Add Student Details |" << endl;
    cout << "---------------------------------------------------------------------------------------------------------------------" << endl;

    inputBasicDetails(); // Get basic details from base class

    cout << "\t\t\t-----------------------------------------------" << endl;
    cout << "\t\t\t\t Enter Your Marks Subject Wise " << endl;
    cout << "\t\t\t-----------------------------------------------" << endl;
    cout << "\t\t\t--> OOP  : "; cin >> oop;
    cout << "\t\t\t--> DBMS : "; cin >> dbms;
    cout << "\t\t\t--> DTE  : "; cin >> dte;
    cout << "\t\t\t--> CN   : "; cin >> cn;
    cout << "\t\t\t--> PIC  : "; cin >> pic;

    // Calculate total marks, percentage and grade
    sum = oop + dbms + dte + cn + pic;
    per = sum / 5.0;
    if (per >= 80) {
        grade = "A";
        result = "PASS";
    } else if (per >= 60) {
        grade = "B";
        result = "PASS";
    } else if (per >= 35) {
        grade = "C";
        result = "PASS";
    } else {
        grade = "-";
        result = "FAIL";
    }

    // Creating a file STUDENTRESULT.TXT to store the records of students
    file.open("studentresult.txt", ios::out | ios::app);
    if (file.is_open()) {
        file << s_name << " " << f_name << " " << m_name << " " << c_name << " " << cr_name << " "
             << roll_no << " " << rgln << " " << dd << " " << mm << " " << yy << " "
             << oop << " " << dbms << " " << dte << " " << cn << " " << pic << " "
             << sum << " " << per << " " << grade << " " << result << "\n";
        file.close();
    } else {
        cout << "Error opening file for writing!" << endl;
    }
}

// Display function
void Student::display() {
    system("cls");
    fstream file;
  
    file.open("studentresult.txt", ios::in);
    if (!file) {
        cout << "\n\t\t\t No Data Is Found ......";
        file.close();
    } else {
        while (file >> s_name >> f_name >> m_name >> c_name >> cr_name >> roll_no >> rgln >> dd >> mm >> yy >>
                      oop >> dbms >> dte >> cn >> pic >> sum >> per >> grade >> result) 
                      {                     
    cout << "\n\n\n---------------------------------------------------------------------------------------------------------------" << endl;                      
    cout << "\t\t\t\t       || GOVERNMENT POLYTECHNIC ,PUNE||" << endl;
    cout << "\t\t\t\t\t| Student Result ODD-2024 |" << endl;
    cout << "---------------------------------------------------------------------------------------------------------------------" << endl;

            cout << "\n\n\t CLASS  : " << cr_name << endl;
            cout << "\t COLLEGE  : " << c_name << endl;
            cout << "\n\n\t STUDENT'S NAME : " << s_name;
            cout << "\t\t\t\t\t ROLL NO : " << roll_no << endl;
            cout << "\n\t MOTHER'S NAME : " << m_name;
            cout << "\t\t\t\t\t DATE OF BIRTH : " << dd << "/" << mm << "/" << yy << endl;
            cout << "\t FATHER'S NAME : " << f_name << endl;
            cout << "\n\t REGULATION : " << rgln << endl;

            cout << "\n\t+-----------------------------------------------------------------------------------------+";
            cout << "\n\t|   Subject Name      |\t  Marks Obtained  |\tOut-Of   |  Percentage   |\tGrade    |";
            cout << "\n\t+----------------------------------------------------------------- -----------------------+";
            cout << "\n\t|\t OOP          |\t      " << oop << "           |\t" << 100 << "\t  |" << "\t\t |" << "\t\t |" << endl;
            cout << "\t| \t DBMS         |\t      " << dbms << "            |\t" << 100 << "\t  |" << "\t\t |" << "\t\t |" << endl;
            cout << "\t| \t DTE          |\t      " << dte << "            |\t" << 100 << "\t  |" << "\t" << per << "%\t |\t" << grade << "\t |" << endl;
            cout << "\t| \t CN           |\t      " << cn << "            |\t" << 100 << "\t  |" << "\t\t |" << "\t\t |" << endl;
            cout << "\t| \t PIC          |\t      " << pic << "            |\t" << 100 << "\t  |" << "\t\t |" << "\t\t |" << endl;
            cout << "\t+------------------------------------------------------------------- ---------------------+";
            cout << "\n\n\n\t\t\t\t  Total  -  " << sum << "\t\t\t  RESULT  -  " << result << endl;

            // Get current date and time
            time_t now = time(0);
            tm *ltm = localtime(&now);
             cout << "\n\n\n\n\n\t\t\t\t\t\t \t\t  Principal Signatures : " << endl;
             cout << "\t Dated : "
                 << 1900 + ltm->tm_year << "-"
                 << 1 + ltm->tm_mon << "-"
                 << ltm->tm_mday << " "
                 << ltm->tm_hour << ":"
                 << ltm->tm_min << ":"
                 << ltm->tm_sec << endl;
        }
         cout << "------------------------------------------------------------------------------------------------" << endl;

    }
    file.close();
    

}

// Delete function
void Student::deleted() {
    system("cls");
    fstream file, file1;
    string rollno;
    int found = 0;
    cout << "------------------------------------------------------------------------------------------" << endl;
    cout << "\t\t\t\t\t\t | Delete Student Record |" << endl;
    cout << "-----------------------------------------------------------------------------------  -----" << endl;

    file.open("studentresult.txt", ios::in);
    if (!file) {
        cout << "\n\t\t\t No Data Is Found ......";
        file.close();
    } else {
        cout << "\n\t\t\t--> Enter Roll No. Of Student Whose You Want To delete The Data : ";
        cin >> rollno;
        file1.open("temp.txt", ios::out | ios::app);

        while (file >> s_name >> f_name >> m_name >> c_name >> cr_name >> roll_no >> rgln >> dd >> mm >> yy >>
                      oop >> dbms >> dte >> cn >> pic >> sum >> per >> grade >> result) {
            if (rollno != roll_no) {
                file1 << s_name << " " << f_name << " " << m_name << " " << c_name << " " << cr_name << " "
                      << roll_no << " " << rgln << " " << dd << " " << mm << " " << yy << " "
                      << oop << " " << dbms << " " << dte << " " << cn << " " << pic << " "
                      << sum << " " << per << " " << grade << " " << result << "\n";
            } else {
                found++;
                cout << "\n\t\t\t Record Is Successfully Deleted.....";
            }
        }

        if (found == 0) {
            cout << "\n\t\t\t Student Roll Number Is Not found...!!! ";
        }

        file.close();
        file1.close();

        remove("studentresult.txt");
        rename("temp.txt", "studentresult.txt");
    }
}

// Main function
int main() {
    Student student;
    student.menu();
    return 0;
}
