#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

class Student {
public:
    int roll;
    char name[50];
    float marks;

    void input() {
        cout << "Enter Roll No: ";
        cin >> roll;
        cin.ignore();
        cout << "Enter Name: ";
        cin.getline(name, 50);
        cout << "Enter Marks: ";
        cin >> marks;
    }

    void display() const {
        cout << "\nRoll No: " << roll;
        cout << "\nName   : " << name;
        cout << "\nMarks  : " << marks << "\n";
    }

    int getRoll() const {
        return roll;
    }
};

void addStudent() {
    ofstream outFile("students.dat", ios::binary | ios::app);
    Student s;
    s.input();
    outFile.write(reinterpret_cast<char*>(&s), sizeof(Student));
    outFile.close();
    cout << "\nStudent record added successfully.\n";
}

void displayAll() {
    ifstream inFile("students.dat", ios::binary);
    Student s;
    cout << "\n--- All Student Records ---\n";
    while (inFile.read(reinterpret_cast<char*>(&s), sizeof(Student))) {
        s.display();
        cout << "--------------------------\n";
    }
    inFile.close();
}

void searchStudent() {
    ifstream inFile("students.dat", ios::binary);
    Student s;
    int roll;
    bool found = false;
    cout << "Enter Roll No to search: ";
    cin >> roll;

    while (inFile.read(reinterpret_cast<char*>(&s), sizeof(Student))) {
        if (s.getRoll() == roll) {
            cout << "\nStudent Found:\n";
            s.display();
            found = true;
            break;
        }
    }

    inFile.close();
    if (!found)
        cout << "Student not found.\n";
}

void deleteStudent() {
    ifstream inFile("students.dat", ios::binary);
    ofstream outFile("temp.dat", ios::binary);
    Student s;
    int roll;
    bool found = false;
    cout << "Enter Roll No to delete: ";
    cin >> roll;

    while (inFile.read(reinterpret_cast<char*>(&s), sizeof(Student))) {
        if (s.getRoll() != roll) {
            outFile.write(reinterpret_cast<char*>(&s), sizeof(Student));
        } else {
            found = true;
        }
    }

    inFile.close();
    outFile.close();
    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
        cout << "Record deleted successfully.\n";
    else
        cout << "Student not found.\n";
}

void updateStudent() {
    fstream file("students.dat", ios::binary | ios::in | ios::out);
    Student s;
    int roll;
    bool found = false;
    cout << "Enter Roll No to update: ";
    cin >> roll;

    while (file.read(reinterpret_cast<char*>(&s), sizeof(Student))) {
        if (s.getRoll() == roll) {
            cout << "\nCurrent Data:\n";
            s.display();

            cout << "\nEnter New Data:\n";
            s.input();

            file.seekp(-static_cast<int>(sizeof(Student)), ios::cur);
            file.write(reinterpret_cast<char*>(&s), sizeof(Student));
            found = true;
            break;
        }
    }

    file.close();
    if (found)
        cout << "Record updated successfully.\n";
    else
        cout << "Student not found.\n";
}

int main() {
    int choice;
    do {
        cout << "\n===== Student Management System =====\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student\n";
        cout << "4. Delete Student\n";
        cout << "5. Update Student\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayAll(); break;
            case 3: searchStudent(); break;
            case 4: deleteStudent(); break;
            case 5: updateStudent(); break;
            case 6: cout << "Exiting program.\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 6);

    return 0;
}

