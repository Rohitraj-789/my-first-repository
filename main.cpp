#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
using namespace std;

struct Student {
    int rollNo;
    string name;
    string course;
    float marks;
};

const string FILE_NAME = "students.txt";

vector<Student> loadStudents() {
    vector<Student> students;
    ifstream file(FILE_NAME);
    Student s;
    while (file >> s.rollNo) {
        file.ignore(numeric_limits<streamsize>::max(), '|');
        getline(file, s.name, '|');
        getline(file, s.course, '|');
        file >> s.marks;
        file.ignore(numeric_limits<streamsize>::max(), '\n');
        students.push_back(s);
    }
    return students;
}

void saveStudents(const vector<Student>& students) {
    ofstream file(FILE_NAME);
    for (const Student& s : students) {
        file << s.rollNo << '|' << s.name << '|'
             << s.course << '|' << s.marks << '\n';
    }
}

int findStudent(const vector<Student>& students, int rollNo) {
    for (int i = 0; i < static_cast<int>(students.size()); ++i) {
        if (students[i].rollNo == rollNo) return i;
    }
    return -1;
}

void addStudent(vector<Student>& students) {
    Student s;
    cout << "Enter roll number: ";
    if (!(cin >> s.rollNo)) {
        cout << "Invalid roll number.\n";
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    if (findStudent(students, s.rollNo) != -1) {
        cout << "A student with this roll number already exists.\n";
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter student name: ";
    getline(cin, s.name);
    cout << "Enter course: ";
    getline(cin, s.course);
    cout << "Enter marks: ";
    if (!(cin >> s.marks) || s.marks < 0 || s.marks > 100) {
        cout << "Invalid marks. Enter a value from 0 to 100.\n";
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    students.push_back(s);
    saveStudents(students);
    cout << "Student added successfully.\n";
}

void displayStudents(const vector<Student>& students) {
    if (students.empty()) {
        cout << "No student records found.\n";
        return;
    }
    cout << "\nRoll No\\tName\\t\\tCourse\\t\\tMarks\n";
    cout << "--------------------------------------------------\n";
    for (const Student& s : students) {
        cout << s.rollNo << "\\t" << s.name << "\\t\\t"
             << s.course << "\\t\\t" << s.marks << '\n';
    }
}

void searchStudent(const vector<Student>& students) {
    int rollNo;
    cout << "Enter roll number to search: ";
    if (!(cin >> rollNo)) {
        cout << "Invalid roll number.\n";
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    int index = findStudent(students, rollNo);
    if (index == -1) {
        cout << "Student not found.\n";
        return;
    }
    const Student& s = students[index];
    cout << "Roll No: " << s.rollNo << "\nName: " << s.name
         << "\nCourse: " << s.course << "\nMarks: " << s.marks << '\n';
}

void updateStudent(vector<Student>& students) {
    int rollNo;
    cout << "Enter roll number to update: ";
    if (!(cin >> rollNo)) {
        cout << "Invalid roll number.\n";
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    int index = findStudent(students, rollNo);
    if (index == -1) {
        cout << "Student not found.\n";
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter new name: ";
    getline(cin, students[index].name);
    cout << "Enter new course: ";
    getline(cin, students[index].course);
    cout << "Enter new marks (0-100): ";
    if (!(cin >> students[index].marks) ||
        students[index].marks < 0 || students[index].marks > 100) {
        cout << "Invalid marks. Update cancelled.\n";
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    saveStudents(students);
    cout << "Student record updated.\n";
}

void deleteStudent(vector<Student>& students) {
    int rollNo;
    cout << "Enter roll number to delete: ";
    if (!(cin >> rollNo)) {
        cout << "Invalid roll number.\n";
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    int index = findStudent(students, rollNo);
    if (index == -1) {
        cout << "Student not found.\n";
        return;
    }
    students.erase(students.begin() + index);
    saveStudents(students);
    cout << "Student record deleted.\n";
}

int main() {
    vector<Student> students = loadStudents();
    int choice;

    do {
        cout << "\n===== STUDENT MANAGEMENT SYSTEM =====\n"
             << "1. Add Student\n"
             << "2. Display All Students\n"
             << "3. Search Student\n"
             << "4. Update Student\n"
             << "5. Delete Student\n"
             << "0. Exit\n"
             << "Enter your choice: ";

        if (!(cin >> choice)) {
            cout << "Please enter a valid menu number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1: addStudent(students); break;
            case 2: displayStudents(students); break;
            case 3: searchStudent(students); break;
            case 4: updateStudent(students); break;
            case 5: deleteStudent(students); break;
            case 0: cout << "Exiting program. Goodbye!\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}
