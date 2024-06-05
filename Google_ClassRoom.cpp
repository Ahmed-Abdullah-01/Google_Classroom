#include <iostream>  // Standard Input/Output stream, used for basic input and output operations.
#include <ctime>     // Time functions and types, used for working with dates and times.
#include <vector>    // Vector container, used for dynamic arrays.
#include <string>    // String operations, used for manipulating strings.
#include <iomanip>   // Input/output manipulators, used for formatting output.
#include <random>    // Random number generation facilities, used for generating random numbers.
#include <unistd.h>  // Unix standard header, provides access to POSIX operating system API.
#include <cstdlib>   // C Standard General Utilities Library, provides general utilities functions.
#include <regex>     // Regular expressions, used for pattern matching within strings.

using namespace std;
void mainMenu();

class TaskManager {
private:
    struct Task {
        string name;
        string deadline; // Store date and time as string
        string type;
    };

    vector<Task> tasks;
    int assignmentCount;
    int quizCount;
    int materialCount;
public:
    TaskManager() : assignmentCount(0), quizCount(0), materialCount(0) {}

    friend void addTask(TaskManager& manager);
    friend void editTask(TaskManager& manager);
    friend void extendDeadline(TaskManager& manager);
    friend void showAllTasks(TaskManager& manager);
    friend void displayMainMenu(TaskManager& manager);

    void taskManager();
};

bool isValidDate(string& date) {
    // Validate date format (YYYY-MM-DD)
    if (date.length() != 10) {
        return false;
    }

    // Validate year
    int year = stoi(date.substr(0, 4));
    if (year < 2024) {
        return false;
    }

    // Validate month
    int month = stoi(date.substr(5, 2));
    if (month < 1 || month > 12) {
        return false;
    }

    // Validate day
    int day = stoi(date.substr(8, 2));
    if (day < 1 || day > 31) {
        return false;
    }

    return true;
}

bool isValidTime(string& time) {
    // Validate time format (HH:MM)
    if (time.length() != 5) {
        return false;
    }

    // Validate hour
    int hour = stoi(time.substr(0, 2));
    if (hour < 0 || hour > 23) {
        return false;
    }

    // Validate minute
    int minute = stoi(time.substr(3, 2));
    if (minute < 0 || minute > 59) {
        return false;
    }

    return true;
}

void addTask(TaskManager& manager) {
    TaskManager::Task newTask;
    cout << "\t\tEnter task name: ";
    getline(cin >> ws, newTask.name);

    cout << "\t\tChoose task type:" << endl;
    cout << "\t\t1. Assignment" << endl;
    cout << "\t\t2. Quiz" << endl;
    cout << "\t\t3. Slides" << endl;
    cout << "\t\t\tEnter your choice: ";
    int typeChoice;
    cin >> typeChoice;
    cin.ignore(1000,'\n');
    if(typeChoice >= 1 && typeChoice<=3){
    switch (typeChoice) {
        case 1:
            newTask.type = "Assignment";
            ++manager.assignmentCount;
            break;
        case 2:
            newTask.type = "Quiz";
            ++manager.quizCount;
            break;
        case 3:
            newTask.type = "Slide";
            ++manager.materialCount;
            break;
        default:
            cerr << "\t\t\tInvalid choice. Setting task type to Assignment." << endl;
            newTask.type = "Assignment";
            ++manager.assignmentCount;
    }
}
    else
    {
            cout << "Invalid choice. Please try again.\n";
            cin.clear();
            cin.ignore(1000,'\n');
    }

    // Input deadline date
    string deadlineDate;
    do {
        cout << "\t\t\tEnter deadline date in YYYY-MM-DD format: ";
        cin >> deadlineDate;
    } while (!isValidDate(deadlineDate));

    // Input deadline time
    string deadlineTime;
    do {
        cout << "\t\t\tEnter deadline time in HH:MM format: ";
        cin >> deadlineTime;
    } while (!isValidTime(deadlineTime));

    // Combine date and time
    newTask.deadline = deadlineDate + " " + deadlineTime;

    // Validate deadline
    // Deadline should be a future date after May 5, 2024
    // and the time should not exceed 23 hours and 59 minutes
    // Assuming current date is May 5, 2024
    string currentDate = "2024-05-17";
    string currentTime = "00:00";

    if (newTask.deadline <= currentDate + " " + currentTime) {
        cout << "\t\t\tError: Deadline must be a future date and time after May 5, 2024." << endl;
        return;
    }

    manager.tasks.push_back(newTask);
    cout << "\t\t\tTask added successfully!" << endl;
}

void editTask(TaskManager& manager) {
    if (manager.tasks.empty()) {
        cout << "\t\t\tNo tasks available to edit." << endl;
        return;
    }

    cout << "\t\t\tTasks:" << endl;
    for (size_t i = 0; i < manager.tasks.size(); ++i) {
        cout << i + 1 << ". " << manager.tasks[i].name << " - Type: " << manager.tasks[i].type << " - Deadline: " << manager.tasks[i].deadline << endl;
    }

    int choice;
    cout << "\t\t\tEnter the task number to edit: ";
    cin >> choice;
    cin.ignore(1000,'\n');

    if (choice >= 1 && choice <= manager.tasks.size()) {
        TaskManager::Task& selectedTask = manager.tasks[choice - 1];
        cout << "---------------------------------------------\n";
        cout << "|             Editing Task Menu             |\n";
        cout << "---------------------------------------------\n";
        cout << "| Editing Task: " << selectedTask.name<<"                    \n"; 
        cout << "| 1. Edit task name                         |\n";
        cout << "| 2. Edit deadline                          |\n";
        cout << "| 3. Edit task type                         |\n";
        cout << "|-------------------------------------------|\n";
        cout << "| Enter your choice:                        |\n";
        cout << "---------------------------------------------\n";
        int editChoice;
        cin >> editChoice;
        cin.ignore(1000,'\n');

        switch (editChoice) {
            case 1:
                cout << "\t\t\tEnter new task name: ";
                getline(cin >> ws, selectedTask.name);
                cout << "\t\t\tTask name updated successfully!" << endl;
                break;
            case 2: {
                // Input new deadline date
                string newDeadlineDate;
                do {
                    cout << "\t\t\tEnter new deadline date in YYYY-MM-DD format: ";
                    cin >> newDeadlineDate;
                } while (!isValidDate(newDeadlineDate));

                // Input new deadline time
                string newDeadlineTime;
                do {
                    cout << "\t\t\tEnter new deadline time in HH:MM format: ";
                    cin >> newDeadlineTime;
                } while (!isValidTime(newDeadlineTime));

                // Combine date and time
                selectedTask.deadline = newDeadlineDate + " " + newDeadlineTime;
                cout << "\t\t\tDeadline updated successfully!" << endl;
                break;
            }
            case 3:
                cout << "\t\tChoose task type:" << endl;
                cout << "\t\t1. Assignment" << endl;
                cout << "\t\t2. Quiz" << endl;
                cout << "\t\t3. Slides" << endl;
                cout << "\t\t\tEnter your choice: ";
                int typeChoice;
                cin >> typeChoice;
                cin.ignore(1000,'\n');
                switch (typeChoice) {
                    case 1:
                        selectedTask.type = "Assignment";
                        break;
                    case 2:
                        selectedTask.type = "Quiz";
                        break;
                    case 3:
                        selectedTask.type = "Slides";
                        break;
                    default:
                        cerr << "\t\t\tInvalid choice. Setting task type to Assignment." << endl;
                        selectedTask.type = "Assignment";
                }
                cout << "\t\t\tTask type updated successfully!" << endl;
                break;
            default:
                cout << "\t\t\tInvalid choice." << endl;
        }
    } else {
        cout << "\t\t\tInvalid task number." << endl;
    }
}

void extendDeadline(TaskManager& manager) {
    if (manager.tasks.empty()) {
        cout << "\t\tNo tasks available to extend deadline." << endl;
        cin.ignore(1000,'\n');        
        return;
    }

    cout << "\t\tTasks:" << endl;
    for (size_t i = 0; i < manager.tasks.size(); ++i) {
        cout << i + 1 << ". " << manager.tasks[i].name << " - Type: " << manager.tasks[i].type << " - Deadline: " << manager.tasks[i].deadline << endl;
    }

    int choice;
    cout << "\t\tEnter the task number to extend deadline: ";
    cin >> choice;
    cin.ignore(1000,'\n');

    if (choice >= 1 && choice <= manager.tasks.size()) {
        TaskManager::Task& selectedTask = manager.tasks[choice - 1];

        // Input new deadline date
        string newDeadlineDate;
        do {
            cout << "\t\tEnter new deadline date in YYYY-MM-DD format: ";
            cin >> newDeadlineDate;
        } while (!isValidDate(newDeadlineDate));

        // Input new deadline time
        string newDeadlineTime;
        do {
            cout << "\t\tEnter new deadline time in HH:MM format: ";
            cin >> newDeadlineTime;
        } while (!isValidTime(newDeadlineTime));

        // Combine date and time
        selectedTask.deadline = newDeadlineDate + " " + newDeadlineTime;
        cout << "\t\t\tDeadline extended successfully!" << endl;
    } else {
        cout << "\t\t\tInvalid task number." << endl;
    }
}

void showAllTasks(TaskManager& manager) {
    if (manager.tasks.empty()) {
        cout << "\t\t\tNo tasks available." << endl;
        cin.ignore(1000,'\n');
    } else {
        cout << "\t\t\tAll Tasks:" << endl;
        for (size_t i = 0; i < manager.tasks.size(); ++i) {
            cout << i + 1 << ". " << manager.tasks[i].name << " - Type: " << manager.tasks[i].type << " - Deadline: " << manager.tasks[i].deadline << endl;
        }
        cout << "\t\t\tTotal Assignments: " << manager.assignmentCount << endl;
        cout << "\t\t\tTotal Quizzes: " << manager.quizCount << endl;
        cout << "\t\t\tTotal Slides: " << manager.materialCount << endl;
    }
}

void displayMainMenu(TaskManager& manager) { 
    cout << "\t\t---------------------------------------------\n";
    cout << "\t\t|               Main Menu                   |\n";
    cout << "\t\t|-------------------------------------------|\n";
    cout << "\t\t| 1. Add Task                               |\n";
    cout << "\t\t| 2. Edit Task                              |\n";
    cout << "\t\t| 3. Extend Deadline                        |\n";
    cout << "\t\t| 4. Show All Tasks                         |\n";
    cout << "\t\t| 5. Exit                                   |\n";
}

void TaskManager::taskManager() {
    int choice;


    do {
    displayMainMenu(*this);
    cout << "\t\t|-------------------------------------------|\n";
    cout << "\t\t| Enter your choice:                        |\n";
    cout << "\t\t---------------------------------------------\n";
    cin >> choice;
    if(choice >=1 && choice <=5){

        switch (choice) {
            case 1:
                addTask(*this);
                break;
            case 2:
                editTask(*this);
                break;
            case 3:
                extendDeadline(*this);
                break;
            case 4:
                showAllTasks(*this);
                break;
            case 5:{
                cout << "\t\t\tExiting..." << endl;
                break;
            }
            default:
                cout << "\t\t\tInvalid choice." << endl;
        }
    }
            else
        {
            cout << "Invalid choice. Please try again.\n";
            cin.clear();
            cin.ignore(1000,'\n');
        }
    } while (choice != 5);

}
            //create class and joing class

class ClassBase {
public:
    virtual void editClass() = 0;
    virtual void joinClass() = 0;
    virtual void createClass() = 0;
    virtual void showAllClasses() = 0;
    virtual ~ClassBase() {}
};


class Class {
private:
    string className;
    string section;
    string subject;
    string room;
    string classCode;

public:
    // Constructors
    Class() {}

    Class(string className, string section, string subject, string room)
        : className(className), section(section), subject(subject), room(room) {
        generateClassCode();
    }

    // Generate a random 5-character class code
    void generateClassCode() {
        string characters = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz#'[]-=}{";
        int codeLength = 5;
        srand(time(0));
        string code;
        for (int i = 0; i < codeLength; ++i) {
            int randomIndex = rand() % characters.size();
            code += characters[randomIndex];
        }
        classCode = code;
    }

    // Getters
    string getClassName() const { return className; }
    string getSection() const { return section; }
    string getSubject() const { return subject; }
    string getRoom() const { return room; }
    string getClassCode() const { return classCode; }

    // Setters
    void setClassName(const string& newClassName) { className = newClassName; }
    void setSection(const string& newSection) { section = newSection; }
    void setSubject(const string& newSubject) { subject = newSubject; }
    void setRoom(const string& newRoom) { room = newRoom; }
};


class ClassManager : public ClassBase {
private:
    vector<Class> classes;

    vector<Class>::iterator findClassByCode(const string& classCode) {
        for (auto it = classes.begin(); it != classes.end(); ++it) {
            if (it->getClassCode() == classCode) {
                return it;
            }
        }
        return classes.end();
    }

public:
    // Function to edit a class
    void editClass() override {
        string classCode;
        cout << "\t\tEnter the class code of the class you want to edit: ";
        cin >> classCode;
        cin.ignore(1000, '\n');

        auto it = findClassByCode(classCode);
        if (it != classes.end()) {
            cout << "\t\t\t---------------------------------------------\n";
            cout << "\t\t\t|          Editing class: " << it->getClassName() << "          |\n";
            cout << "\t\t\t|-------------------------------------------|\n";
            cout << "\t\t\t| 1. Edit Class Name                        |\n";
            cout << "\t\t\t| 2. Edit Section                           |\n";
            cout << "\t\t\t| 3. Edit Subject                           |\n";
            cout << "\t\t\t| 4. Edit Room                              |\n";
            cout << "\t\t\t|-------------------------------------------|\n";
            cout << "\t\t\t| Enter your choice:                        |\n";
            cout << "\t\t\t---------------------------------------------\n";

            int choice;
            cin >> choice;
            cin.ignore(1000, '\n');
            if (choice >= 1 && choice <= 4) {
                switch (choice) {
                case 1: {
                    string newClassName;
                    cout << "\t\t\tEnter new class name: ";
                    getline(cin >> ws, newClassName);
                    it->setClassName(newClassName);
                    break;
                }
                case 2: {
                    string newSection;
                    cout << "\t\t\tEnter new section: ";
                    getline(cin >> ws, newSection);
                    it->setSection(newSection);
                    break;
                }
                case 3: {
                    string newSubject;
                    cout << "\t\t\tEnter new subject: ";
                    getline(cin >> ws, newSubject);
                    it->setSubject(newSubject);
                    break;
                }
                case 4: {
                    string newRoom;
                    cout << "\t\t\tEnter new room: ";
                    getline(cin >> ws, newRoom);
                    it->setRoom(newRoom);
                    break;
                }
                default:
                    cout << "\t\t\tInvalid choice." << endl;
                }
                // Generate new random class code
                it->generateClassCode();
                cout << "\t\t\tClass updated successfully!" << endl;
                cout << "\t\t\tNew class code: " << it->getClassCode() << endl;
            } else {
                cout << "Invalid choice. Please try again.\n";
                cin.clear();
                cin.ignore(1000, '\n');
            }
        } else {
            cout << "\t\t\tClass not found. Please double-check the class code." << endl;
        }
    }

    // Function to join a class
    void joinClass() override {
        cout << "\t\t\tEnter the class code to join: ";
        string inputCode;
        cin >> inputCode;

        auto it = findClassByCode(inputCode);
        if (it != classes.end()) {
            cout << "\t\t\tYou have successfully joined the class!" << endl;
            displayClassInfo(*it);
        } else {
            cout << "\t\t\tInvalid class code. Please double-check and try again." << endl;
        }
        int ab;
            while (true) {
            cout << "Enter any digit to continue: ";
            cin >> ab;
            if (ab >= 1 && ab <= 9)
                 break;
             else {
            cout << "Invalid choice. Please try again.\n";
            cin.clear();
            cin.ignore(1000, '\n');
    }
}

    }

    // Function to create a class
    void createClass() override {
        string className, section, subject, room;

        cout << "\t\t\tEnter class name: ";
        getline(cin >> ws, className);

        cout << "\t\t\tEnter section: ";
        getline(cin >> ws, section);

        cout << "\t\t\tEnter subject: ";
        getline(cin >> ws, subject);

        cout << "\t\t\tEnter room: ";
        getline(cin >> ws, room);

        Class newClass(className, section, subject, room);
        classes.push_back(newClass);

        cout << "\t\t\tClass created successfully!" << endl;
        cout << "\t\t\tYour class code is: " << newClass.getClassCode() << endl;
    }

    // Function to display all classes
    void showAllClasses() override {
        if (classes.empty()) {
            cout << "No classes available." << endl;
            return;
        }

        cout << "All Classes:" << endl;
        for (const auto& cls : classes) {
            cout << "Class Code: " << cls.getClassCode() << " - " << cls.getClassName() << endl;
        }
    }

    void displayClassInfo(const Class& cls) {
        cout << "\t\t\tClass Name: " << cls.getClassName() << endl;
        cout << "\t\t\tSection: " << cls.getSection() << endl;
        cout << "\t\t\tSubject: " << cls.getSubject() << endl;
        cout << "\t\t\tRoom: " << cls.getRoom() << endl;
    }
};


            //Calender Class
class Calendar {
private:
    string monthNames[12] = {"January", "February", "March", "April", "May", "June",
                             "July", "August", "September", "October", "November", "December"};
    int daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int month;
    int year;
    vector<bool> taskMarks;

public:
    //  ructor
    Calendar(int m, int y) : month(m), year(y), taskMarks(daysInMonth[m - 1], false) {}

    // Function to determine if a year is a leap year
    bool isLeapYear(int year) {
        if (year % 400 == 0) {
            return true;
        } else if (year % 100 == 0) {
            return false;
        } else if (year % 4 == 0) {
            return true;
        }
        return false;
    }

    // Function to print the calendar for a specific month and year
void printCalendar() {
    cout << setw(20) << left << "Month" << "Year" << endl;
    cout << setw(20) << left << month << year << "\n\n";
    cout << "Sun Mon Tue Wed Thu Fri Sat" << endl;

    int startingDay = 1; // Assuming the first day of the month is Sunday

    // Assuming month and year are already defined
    int daysInMonth = 30; // Assuming a month with 30 days

    cout<<"\n";

    // Print days of the month
    for (int i = 1; i <= daysInMonth; i++) {
        if (i == 1) {
            // Print blank spaces for days before the first day of the month
            for (int j = 0; j < startingDay; j++) {
                cout << setw(4) << left << " ";
            }
        }
        
        cout << setw(4) << left << i;
        
        if ((i + startingDay) % 7 == 0 || i == daysInMonth) {
            cout << endl; // Start a new line after every Saturday or the last day of the month
        }
        }
    int ab;
    while (true) {
        cout << "Enter any digit to continue: ";
        cin >> ab;
        if (ab >= 1 && ab <= 9)
            break;
        else {
            cout << "Invalid choice. Please try again.\n";
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }

}

private:
    // Function to calculate the starting day of the month (0 = Sunday, 6 = Saturday)
    int getStartingDay() {
        return (year + year / 4 - year / 100 + year / 400) % 7;
    }
};

void displayCalendar() {
    int month, year;

    // Input validation loop to ensure valid month (1-12)
    while (true) {
        cout << "\t\t\tEnter the month: ";
        if (cin >> month && month >= 1 && month <= 12) {
            break;
        }
        cout << "\t\t\tInvalid month. Please enter a value between 1 and 12." << endl;
        cin.clear(); // Clear the input stream after an error
        cin.ignore(10000, '\n'); // Discard characters up to newline
    }

    // Input validation loop to ensure valid year (2001-2050)
    while (true) {
        cout << "\t\t\tEnter the year: ";
        if (cin >> year && year >= 2001 && year <= 2050) {
            break;
        }
        cout << "\t\t\tInvalid year. Please enter a year between 2001 and 2050." << endl;
        cin.clear(); // Clear the input stream after an error
        cin.ignore(10000, '\n'); // Discard characters up to newline
    }

    // Create Calendar object
    Calendar calendar(month, year);
    calendar.printCalendar();
}

            // TASK CLASS

class Task {
protected:
    string name;
    string duedate;

public:
    Task(string name, string duedate) : name(name), duedate(duedate) {}

    virtual void displayDetails() = 0;
    virtual bool isDue() = 0;
};
// Class to represent user
class User {
private:
    string username;
    string password;

public:
    User(string username, string password) : username(username), password(password) {}

    // Getter methods
    string getUsername()   { return username; }
    string getPassword()   { return password; }
};

// Main class for the program
class Program {
private:
    vector<Task*> tasks;
    vector<User> users; // Vector to store users
    // Other necessary data members

public:
    // Method to get current date and time
    void getCurrentDateTime() {
        // Get current time
        time_t currentTime = time(nullptr);

        // Convert time to local time
        tm* localTime = localtime(&currentTime);

        // Display current date and time
        cout<<"\n\n\n";
        cout << "\t\t\tCurrent date and time: ";
        cout << localTime->tm_mday << "/" << localTime->tm_mon + 1 << "/" << localTime->tm_year + 1900 << " ";
        cout << localTime->tm_hour << ":" << localTime->tm_min << ":" << localTime->tm_sec << endl;
        cout<<"--------------------------------------------------------------------------------------------------------------------------------\n";
        sleep(4);
    }

    // Method to handle user sign in
void signIn() {
    // Loop until the correct password is entered
    while (true) {
        string username, password;

        cout << "\t\t\tEnter username: ";
        cin >> username;

        cout << "\t\t\tEnter password: ";
        cin >> password;

        // Check if the entered password matches the predefined value
        if (password == "fast9876" && username == "fastnuces@pwr.nu.edu.pk") {
            cout << "\t\t\tLogin successful!\n";
            ;
            break; // Exit the loop
        } else {
            cout << "\t\t\tInvalid Admin Credintials. Please try again.\n";
            cout << "\t\t\tPress 'Y' or 'y' to return to Sign-up or any other key to continue: ";
            char choice;
            cin >> choice;
            if (choice == 'Y' || choice == 'y') {
                signUp();
                break;
            }
        }
    }
}
    // Method to handle user sign up
bool isValidEmail(string& email) {
    // Regular expression to validate Gmail address
    regex pattern("^\\w+@gmail\\.com$");
    return regex_match(email, pattern);
}

void signUp() 
{
    string firstName, lastName, username, password, phoneNumber;
    bool onlinePurchasing = false;

    char wantsDetails;

    cout << "\t\t\tEnter first name: ";
    getline(cin>>ws,firstName);
    cout << "\t\t\tEnter last name: ";
    getline(cin>>ws,lastName);

    // Loop until a valid email address with "@gmail.com" is entered
    while (true) {
        cout << "\t\t\tEnter desired username: ";
        cin >> username;
        if (!isValidEmail(username)) {
            cout << "\t\t\tInvalid email address. Please enter a valid Gmail address.\n";
            continue;
        }
        break;  // Break out of the loop if a valid email is entered
    }

    // Password validation loop
    bool validPassword = false;
    while (!validPassword) {
        cout << "\t\t\tEnter password: ";
        cin >> password;

        // Check password length
        if (password.length() < 8) {
            cout << "\t\t\tPassword must be at least 8 characters long.\n";
            continue;
        }

        // Check for at least one uppercase letter, one lowercase letter, one number, and one symbol
        bool hasUppercase = false, hasLowercase = false, hasNumber = false, hasSymbol = false;
        for (char ch : password) {
            if (isupper(ch)) {
                hasUppercase = true;
            } else if (islower(ch)) {
                hasLowercase = true;
            } else if (isdigit(ch)) {
                hasNumber = true;
            } else if (!isalnum(ch)) {
                hasSymbol = true;
            }
        }

        // Check if all password requirements are met
        if (!hasUppercase || !hasLowercase || !hasNumber || !hasSymbol) {
            cout << "\t\t\tPassword must include at least :\nOne uppercase letter\nOne lowercase letter\nOne number\nOne symbol.\n";
        } else {
            validPassword = true;
        }
    }

    // Asking for phone number
    while (true) {
        cout << "\t\t\tEnter phone number : ";
        cin >> phoneNumber;
        if (phoneNumber.length() != 11 || phoneNumber.substr(0, 2) != "03") {
            cout << "\t\t\tInvalid phone number.\nPlease enter a valid 11-digit number starting with 03.\n";
            continue;
        }
        break;  // Break out of the loop if a valid phone number is entered
    }

    // Asking for online purchasing details
   // cout << "\t\t\tDo you want to provide online purchasing details? (y/n): ";
   // cin >> wantsDetails;
while(true)
{
     cout << "\t\t\tDo you want to provide online purchasing details? (y/n): ";
    cin >> wantsDetails;
    if(wantsDetails == 'y' || wantsDetails == 'Y'||wantsDetails == 'n' || wantsDetails == 'N')
    {
        break;
    }
else
{
    cout<<"invalid output"<<endl;

}

}



    if (wantsDetails == 'y' || wantsDetails == 'Y') {
        onlinePurchasing = true;

        // Input logic for online purchasing details
        string cardNumber, cardName, expiryDate, cvc;

        // Input for debit card number
        while (true) {
            cout << "\t\t\tEnter debit card number: ";
            cin >> cardNumber;
            if (cardNumber.length() != 16 || cardNumber[0] != '5') {
                cout << "\t\t\tInvalid card number.\nMaster-Card starts with 5 and is of 16 digits.\n";
                continue;
            }
            break;  // Break out of the loop if a valid card number is entered
        }

        // Input for card name
        cout << "\t\t\tEnter cardholder's name: ";
        getline(cin >> ws, cardName);

        // Input for expiry date
        while (true) {
            cout << "\t\t\tEnter expiry date (MM/YYYY): ";
            cin >> expiryDate;
            if (expiryDate.length() != 7 || expiryDate.substr(0, 2) > "12" || expiryDate.substr(0, 2) < "05" || expiryDate.substr(3, 4) > "2050") {
                cout << "\t\t\tPlease do not input year below 2024 and above 2050\nAlso Input month from above May-2024\n";
                continue;
            }
            break;  // Break out of the loop if a valid expiry date is entered
        }

        // Input for cvc
        while (true) {
            cout << "\t\t\tEnter CVC (3 digits): ";
            cin >> cvc;
            if (cvc.length() != 3 || !isdigit(cvc[0]) || !isdigit(cvc[1]) || !isdigit(cvc[2])) {
                cout << "\t\t\tInvalid CVC. Please enter a valid 3-digit number.\n";
                continue;
            }
            break;  // Break out of the loop if a valid CVC is entered
        }
    }

    // Add new user to the system or database
    cout << "\t\t\tSign up successful!\n";
    // Clear the screen or do other necessary actions
    
}
void Showdetail()
{
    int choice;
    system("CLS");    
                  cout << "   ___  _                        _    ___  _         _       _ _       _                 \n"
                 " / _ \\| |                      | |  / _ \\| |       | |     | | |     | |                \n"
                 "/ /_\\ \\ |__  _ __ ___   ___  __| | / /_\\ \\ |__   __| |_   _| | | __ _| |__              \n"
                 "|  _  | '_ \\| '_ ` _ \\ / _ \\/ _` | |  _  | '_ \\ / _` | | | | | |/ _` | '_ \\             \n"
                 "| | | | | | | | | | | |  __/ (_| | | | | | |_) | (_| | |_| | | | (_| | | | |            \n"
                 "\\_| |_/_| |_|_| |_| |_|\\___|\\__,_| \\_| |_/_.__/ \\__,_|\\__,_|_|_|\\__,_|_| |_|            \n"
                 "                                                                                        \n"
                 "                                                                                        \n"
                 "___  ___      _                                         _    ___  _                     \n"
                 "|  \\/  |     | |                                       | |  / _ \\| |                    \n"
                 "| .  . |_   _| |_   __ _ _ __ ___  _ __ ___   __ _  __| | / /_\\ \\ |__  ___  __ _ _ __   \n"
                 "| |\\/| | | | | '_ \\ / _` | '_ ` _ \\| '_ ` _ \\ / _` |/ _` | |  _  | '_ \\/ __|/ _` | '_ \\ \n"
                 "| |  | | |_| | | | | (_| | | | | | | | | | | | (_| | (_| | | | | | | | \\__ \\ (_| | | | |\n"
                 "\\_|  |_|\\__, |_| |_|\\__,_|_| |_| |_|_| |_| |_|\\__,_|\\__,_| \\_| |_|_| |_|___/\\__,_|_| |_|\n";
                 cout<<"\n";
                 cout << "______            _____ ______" << endl;
                 cout << "| ___ \\          / __  \\|  _  \\" << endl;
                 cout << "| |_/ / ___ ___  `' / /'| | | |" << endl;
                 cout << "| ___ \\/ __/ __|   / /  | | | |" << endl;
                 cout << "| |_/ / (__\\__ \\ ./ /___| |/ /" << endl;
                 cout << "\\____/ \\___|___/ \\_____/|___/" << endl;
                 cout << endl;

                 cout << " _____  ___________       _____ _____  _____  _____                       _____  ___________       _____ _____    ___  _____ " << endl;
                 cout << "/ __  \\|____ | ___ \\     |  _  |  ___|/ __  \\/ __  \\     ___    ___      / __  \\|____ | ___ \\     |  _  |  ___|  /   ||____ |" << endl;
                 cout << "`' / /'    / / |_/ /_____| |/' |___ \\ `' / /'`' / /'    ( _ )  ( _ )     `' / /'    / / |_/ /_____| |/' |___ \\  / /| |    / /" << endl;
                 cout << "  / /      \\ \\  __/______|  /| |   \\ \\  / /    / /      / _ \\/\\/ _ \\/\\     / /      \\ \\  __/______|  /| |   \\ \\/ /_| |    \\ \\" << endl;
                 cout << "./ /___.___/ / |         \\ |_/ /\\__/ /./ /___./ /___   | (_>  < (_>  <   ./ /___.___/ / |         \\ |_/ /\\__/ /\\___  |.___/ /" << endl;
                 cout << "\\_____/ ___/\\_|          \\___/\\____/ \\_____/ _____/    \\___/\\/\\___/\\/   \\_____/ ____/\\_|          \\___/\\____/     |_/ ____/ " << endl;
        sleep(3);
        system("CLS");
        
    while (true) {
    cout << "\t\t----------------------------------------\n";
    cout << "\t\t|             Menu                     |\n";
    cout << "\t\t|--------------------------------------|\n";
    cout << "\t\t| 1. Libraries Used                    |\n";
    cout << "\t\t| 2. Classes and Features              |\n";
    cout << "\t\t| 3. Other Details                     |\n";
    cout << "\t\t| 4. Why These Libraries               |\n";
    cout << "\t\t| 5. Exit                              |\n";
    cout << "\t\t----------------------------------------\n";
    cout << "\t\t\tEnter your choice (1-5): ";
        cin >> choice;
       if (choice == 1) {
            cout << "\nLibraries Used:\n";
            cout << "- iostream: For input and output operations.\n";
            cout << "- system("");: For accessing date and time functions.\n";
            cout << "- vector: To use the vector container class for dynamic arrays.\n";
            cout << "- string: For string operations.\n";
            cout << "- regex: For regular expression matching.\n";
            cout << "- iomanip: For setting output formatting options.\n";
            cout << "- random: For generating random numbers.\n";
        } else if (choice == 2) {
            while (true) {
                cout << "\nClasses and Features:\n";
                cout << "1. TaskManager Class\n";
                cout << "2. ClassBase, Class, ClassManager Classes\n";
                cout << "3. Calendar Class\n";
                cout << "4. Task Class\n";
                cout << "5. User Class\n";
                cout << "6. Program Class\n";
                cout << "7. Exit\n";
                cout << "Enter your choice (1-7): ";
                cin >> choice;

                if (choice == 1) {
                    cout << "\nTaskManager Class:\n";
                    cout << "Description: Manages tasks such as adding, editing, extending deadlines, and displaying all tasks.\n";
                    cout << "Inheritance/Composition/Aggregation: Does not involve inheritance, composition, or aggregation.\n";
                    cout << "Features:\n";
                    cout << "- Add tasks of different types (Assignment, Quiz, Material).\n";
                    cout << "- Edit existing tasks.\n";
                    cout << "- Extend deadlines for tasks.\n";
                    cout << "- Display all tasks along with their types and deadlines.\n\n";
                } else if (choice == 2) {
                    cout << "\nClassBase, Class, ClassManager Classes:\n";
                    cout << "Description: Handles operations related to classes like creating, editing, joining, and displaying classes.\n";
                    cout << "Inheritance/Composition/Aggregation:\n";
                    cout << "- ClassBase is an abstract class defining virtual methods for class operations. (Inheritance)\n";
                    cout << "- ClassManager inherits from ClassBase and provides implementations for the virtual methods. (Inheritance)\n";
                    cout << "Features:\n";
                    cout << "- Create a class with a name, section, subject, and room.\n";
                    cout << "- Edit class details like name, section, subject, and room.\n";
                    cout << "- Join a class using a class code.\n";
                    cout << "- Display all available classes.\n\n";
                } else if (choice == 3) {
                    cout << "\nCalendar Class:\n";
                    cout << "Description: Represents a calendar for a specific month and year and marks tasks on specific dates.\n";
                    cout << "Inheritance/Composition/Aggregation: Does not involve inheritance, composition, or aggregation.\n";
                    cout << "Features:\n";
                    cout << "- Print the calendar for a given month and year.\n";
                    cout << "- Mark tasks on specific dates.\n\n";
                } else if (choice == 4) {
                    cout << "\nTask Class:\n";
                    cout << "Description: Represents a task with a name and a due date.\n";
                    cout << "Inheritance/Composition/Aggregation: Does not involve inheritance, composition, or aggregation.\n";
                    cout << "Features:\n";
                    cout << "- Pure virtual methods for displaying task details and checking if the task is due.\n\n";
                } else if (choice == 5) {
                    cout << "\nUser Class:\n";
                    cout << "Description: Represents a user with a username and password.\n";
                    cout << "Inheritance/Composition/Aggregation: Does not involve inheritance, composition, or aggregation.\n";
                    cout << "Features:\n";
                    cout << "- Stores user credentials.\n\n";
                } else if (choice == 6) {
                    cout << "\nProgram Class:\n";
                    cout << "Description: Main class orchestrating the overall program flow, including sign-in, sign-up, and main menu.\n";
                    cout << "Inheritance/Composition/Aggregation: Does not involve inheritance, composition, or aggregation.\n";
                    cout << "Features:\n";
                    cout << "- Sign-in functionality with password validation.\n";
                    cout << "- Sign-up functionality with input validations.\n";
                    cout << "- Main menu navigation for accessing different program functionalities.\n";
                    cout << "- Displays current date and time.\n\n";
                } else if (choice == 7) {
                    
                    break; // Exit the submenu
                } else {
                    cout << "Invalid choice. Please enter a number between 1 and 7.\n";
                            cin.clear();
                            cin.ignore(1000,'\n');
                }
            }
        } else if (choice == 3) {
            cout << "\nOther Details:\n";
            cout << "Input Validation: The code includes input validation for various user inputs, ensuring data integrity.\n";
            cout << "Password Requirements: Passwords must be at least 8 characters long and contain at least one uppercase letter, one lowercase letter, one number, and one symbol.\n";
            cout << "Clearing Screen: The code includes platform-dependent screen clearing using macros ("").\n";
            cout << "Random Generation: Random class codes and random character generation are utilized for various functionalities.\n";
            cout << "Login Mechanism: Implements a basic login system with sign-in and sign-up options.\n\n";
        } else if (choice == 4) {
            cout << "\nWhy These Libraries?\n";
            cout << "- iostream: Standard for input/output operations.\n";
            cout << "- ctime: Essential for date and time operations.\n";
            cout << "- vector: Dynamic array and associative array for managing tasks and classes efficiently.\n";
            cout << "- string/regex: Handling string inputs and regular expression matching for email validation.\n";
            cout << "- random: Generating random class codes and random characters.\n\n";
        } else if (choice == 5) {
            break;
        } else {
            cout << "Invalid choice. Please enter a number between 1 and 5.\n";
            cin.clear();
            cin.ignore(1000,'\n');
        }
    }

}
    // Method to display the main menu
    void mainMenu() {


        ClassManager classManager;
        
        int choice;
        do{
        system("CLS");
    cout << "\n\n\n\t\t\t*****************************************************\n";
    cout << "\t\t\t*                                                   *\n";
    cout << "\t\t\t*                    Main Menu                      *\n";
    cout << "\t\t\t*                                                   *\n";
    cout << "\t\t\t*   1. To-Do List                                   *\n";
    cout << "\t\t\t*   2. Create Class or Edit Class                   *\n";
    cout << "\t\t\t*   3. Join Class                                   *\n";
    cout << "\t\t\t*   4. Calendar                                     *\n";
    cout << "\t\t\t*   5. Show-Details                                 *\n";
    cout << "\t\t\t*   6. Exit                                         *\n";
    cout << "\t\t\t*                                                   *\n";
    cout << "\t\t\t*****************************************************\n\n\n";
    cout << "\t\t\t\tEnter your choice: ";
        cin >> choice;
    cout<<"\t\t--------------------------------------------------------------------------------------------------------------------------------"<<endl;
        if(choice>= 1 && choice <=6 ){
        switch (choice) {
            case 1:
                {   
                TaskManager manager;
                manager.taskManager();
                }
                break;
            case 2:
            int a;
            do{    
            
            cout << "\t\t----------------------------------------\n";
            cout << "\t\t|           Enter your choice          |\n";
            cout << "\t\t|--------------------------------------|\n";
            cout << "\t\t| 1. Create Class                      |\n";
            cout << "\t\t| 2. Edit Class                        |\n";
            cout << "\t\t| 3. Display classes                   |\n";
            cout << "\t\t| 4. Exit                              |\n";
            cout << "\t\t----------------------------------------\n";
            cin >> a;
        if(a>= 1 && a<=4){
            switch (a) {
            case 1:
                classManager.createClass();
            break;
            case 2:
                classManager.editClass();
            break;
            case 3:
                classManager.showAllClasses();
            break;
            case 4:{
                break;
                cout << "Exiting...\n";
            }
            break;
            default:
            cout << "Invalid choice. Please try again.\n";
            break;
            }
            }
            else
                {
            cout << "Invalid choice. Please try again.\n";
            cin.clear();
            cin.ignore(1000,'\n');
                }
            }while(a!=4);
            break;

            case 3:
                classManager.joinClass();
                break;
            case 4:
                displayCalendar();
                break;
             case 5:
                Showdetail();
            break;               
            case 6:{
                break;
                cout << "Exiting...\n";
            }
            break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
        }
        else
        {
            cout << "Invalid choice. Please try again.\n";
            cin.clear();
            cin.ignore(1000,'\n');
        }
    }while(choice != 6);
}
    // Method to display login page
    int loginPage() {
        int choice , i = 0;
                    system("CLS");
                    sleep(2);
            cout<<"\n\n\n";
    cout<<"\t\t\t\t\t\t\t\t*____Google______Project_Object_Oriented_____Classroom_______*\n";
    cout<<"\t\t\t\t\t\t\t\t*____Google______Project_Object_Oriented_____Classroom_______*\n";
    cout<<"\t\t\t\t\t\t\t\t*____Google______Project_Object_Oriented_____Classroom_______*\n";
    cout<<"\t\t\t\t\t\t\t\t*____Google______Project_Object_Oriented_____Classroom_______*\n";
    cout<<"\t\t\t\t\t\t\t\t*____Google______Project_Object_Oriented_____Classroom_______*\n";
    cout<<"\t\t\t\t\t\t\t\t*____Google______Project_Object_Oriented_____Classroom_______*\n";
    cout<<"\t\t\t\t\t\t\t\t*____Google______Project        Oriented_____Classroom_______*\n";
    cout<<"\t\t\t\t\t\t\t\t*____Google______Project       _Oriented_____Classroom_______*\n";
    cout<<"\t\t\t\t\t\t\t\t*____Google______Project_     t_Oriented_____Classroom_______*\n";
    cout<<"\t\t\t\t\t\t\t\t*____Google______Project_Object_Oriented_____Classroom_______*\n";
    cout<<"\t\t\t\t\t\t\t\t*____Google______Project_Object_Oriented_____Classroom_______*\n";
    cout<<"\t\t\t\t\t\t\t\t*____Google______Project       _Oriented_____Classroom_______*\n";
    cout<<"\t\t\t\t\t\t\t\t*____Google______Proj             entied_____Classroom_______*\n";
    cout<<"\t\t\t\t\t\t\t\t*____Google______Pro                tied_____Classroom_______*\n";
    cout<<"\t\t\t\t\t\t\t\t*____Google______Project_Object_Oriented_____Classroom_______*\n";
    cout<<"\t\t\t\t\t\t\t\t*____Google______Project_Object_Oriented_____Classroom_______*\n";
    cout<<"\t\t\t\t\t\t\t\t*____Google______Project_Object_Oriented_____Classroom_______*\n";
    cout<<"\t\t\t\t\t\t\t\t*____Google______Project_Object_Oriented_____Classroom_______*\n";
    cout<<"\t\t\t\t\t\t\t\t*____Google______Project_Object_Oriented_____Classroom_______*\n";
cout<<"\t\t\t\t--------------------------------------------------------------------------------------------------------------------------------"<<endl;
cout << "\t\t\t\t  ________                   ____  .__               _________  .__                                                             " << endl;
cout << "\t\t\t\t /  _____/   ____    ____   / ___\\ |  |    ____      \\_   ___ \\ |  |  _____     ______  _____________   ____    ____    _____ " << endl;
cout << "\t\t\t\t/   \\  ___  /  _ \\  /  _ \\ / /_/  >|  |  _/ __ \\     /    \\  \\/ |  |  \\__  \\   /  ___/ /  ___/\\_  __ \\ /  _ \\  /  _ \\  /     \\" << endl;
cout << "\t\t\t\t\\    \\_\\  \\(  <_> )(  <_> )\\___  / |  |__\\  ___/     \\     \\____|  |__ / __ \\_ \\___ \\  \\___ \\  |  | \\/(  <_> )(  <_> )|  Y Y  \\" << endl;
cout << "\t\t\t\t \\______  / \\____/  \\____//_____/  |____/ \\___  >     \\______  /|____/(____  //____  > /____  > |__|    \\____/  \\____/ |__|_|  /" << endl;
cout << "\t\t\t\t        \\/                                    \\/             \\/            \\/      \\/       \\/                             \\/ " << endl;
cout<<"\t\t\t\t--------------------------------------------------------------------------------------------------------------------------------"<<endl;

             sleep(2);          
            system("CLS");

        while(i == 0){

    cout << "\n\n\n\t\t\t*****************************************************\n";
    cout << "\t\t\t*                                                   *\n";
    cout << "\t\t\t*                   Login Page                      *\n";
    cout << "\t\t\t*                                                   *\n";
    cout << "\t\t\t*   1. Sign In                                      *\n";
    cout << "\t\t\t*   2. Sign Up                                      *\n";
    cout << "\t\t\t*   3. Exit                                         *\n";
    cout << "\t\t\t*                                                   *\n";
    cout << "\t\t\t*****************************************************\n\n\n";
    cout << "\t\t\t\tEnter your choice: ";

            cin >> choice;
cout<<"\t\t--------------------------------------------------------------------------------------------------------------------------------"<<endl;
           if(choice >= 1 && choice <= 3 && !cin.fail()){
            switch (choice) {
                case 1:
                    signIn();
                    break;
                case 2:
                    signUp();
                    break;
                case 3:
                    cout << "Exiting login page...\n";
                    cout<<"\t\t--------------------------------------------------------------------------------------------------------------------------------"<<endl;
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n";
                    cout<<"\t\t--------------------------------------------------------------------------------------------------------------------------------"<<endl;
                    break;
            }
            i++;
        }
        else 
            cout<<"Invalid Choice...Try Again"; 
            cin.clear();
            cin.ignore(1000,'\n');
        }
        return choice;
    }
};

int main() {
    Program program;
    system("CLS");
    program.getCurrentDateTime();
    int a=program.loginPage();
    if(a!=3)
    {
        program.mainMenu();
    }
    
    return 0;
}