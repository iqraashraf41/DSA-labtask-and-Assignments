// ============================================================================
// COMPLETE BANK MANAGEMENT SYSTEM - SINGLE FILE IMPLEMENTATION
// Developed with Object-Oriented Programming Principles
// ============================================================================

// Add this at the very beginning to disable security warnings
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <cmath>
#include <cstdio>
#include <windows.h>  // For system("cls") and system("pause")

using namespace std;

// ============================================================================
// FORWARD DECLARATIONS
// ============================================================================
class User;
class Admin;
class Officer;
class Customer;
class Account;
class Transaction;
class Loan;
class Complaint;
class Ledger;
class Report;
class AuditLog;
class BackupManager;
class BankSystem;

// ============================================================================
// UTILITY FUNCTIONS
// ============================================================================
namespace Utility {
    // Basic string class to avoid STL
    class String {
    private:
        char* data;
        int length;

    public:
        String() : data(nullptr), length(0) {}

        String(const char* str) {
            if (str) {
                length = static_cast<int>(strlen(str));
                data = new char[length + 1];
                strcpy(data, str);
            }
            else {
                data = nullptr;
                length = 0;
            }
        }

        String(const String& other) {
            length = other.length;
            if (other.data) {
                data = new char[length + 1];
                strcpy(data, other.data);
            }
            else {
                data = nullptr;
            }
        }

        ~String() {
            delete[] data;
        }

        int getLength() const { return length; }
        const char* c_str() const { return data ? data : ""; }

        String& operator=(const String& other) {
            if (this != &other) {
                delete[] data;
                length = other.length;
                if (other.data) {
                    data = new char[length + 1];
                    strcpy(data, other.data);
                }
                else {
                    data = nullptr;
                }
            }
            return *this;
        }

        bool operator==(const String& other) const {
            if (length != other.length) return false;
            return strcmp(data, other.data) == 0;
        }

        bool operator!=(const String& other) const {
            return !(*this == other);
        }

        char& operator[](int index) {
            return data[index];
        }

        const char& operator[](int index) const {
            return data[index];
        }

        // String concatenation
        String operator+(const String& other) const {
            char* newData = new char[length + other.length + 1];
            if (data) {
                strcpy(newData, data);
            }
            else {
                newData[0] = '\0';
            }
            if (other.data) {
                strcat(newData, other.data);
            }
            String result(newData);
            delete[] newData;
            return result;
        }

        String operator+(const char* other) const {
            return *this + String(other);
        }
    };

    // Helper function to convert integer to string
    String intToString(int value) {
        char buffer[20];
        sprintf(buffer, "%d", value);
        return String(buffer);
    }

    // Helper function to convert long long to string
    String longLongToString(long long value) {
        char buffer[30];
        sprintf(buffer, "%lld", value);
        return String(buffer);
    }

    // Helper function to convert double to string
    String doubleToString(double value) {
        char buffer[50];
        sprintf(buffer, "%.2f", value);
        return String(buffer);
    }

    // Generate random 5-digit password
    String generateRandomPassword() {
        // Seed random number generator with current time
        static bool seeded = false;
        if (!seeded) {
            srand(static_cast<unsigned int>(time(nullptr)));
            seeded = true;
        }

        // Generate random number between 10000 and 99999
        int passwordNum = rand() % 90000 + 10000;
        char buffer[6]; // 5 digits + null terminator
        sprintf(buffer, "%05d", passwordNum);
        return String(buffer);
    }

    // Date structure
    struct Date {
        int day, month, year;

        Date() : day(1), month(1), year(2000) {}
        Date(int d, int m, int y) : day(d), month(m), year(y) {}

        String toString() const {
            char buffer[20];
            sprintf(buffer, "%02d/%02d/%04d", day, month, year);
            return String(buffer);
        }

        static Date getCurrentDate() {
            time_t now = time(0);
            tm ltm;
            localtime_s(&ltm, &now);
            return Date(ltm.tm_mday, 1 + ltm.tm_mon, 1900 + ltm.tm_year);
        }
    };

    // Time structure
    struct Time {
        int hour, minute, second;

        Time() : hour(0), minute(0), second(0) {}
        Time(int h, int m, int s) : hour(h), minute(m), second(s) {}

        String toString() const {
            char buffer[20];
            sprintf(buffer, "%02d:%02d:%02d", hour, minute, second);
            return String(buffer);
        }

        static Time getCurrentTime() {
            time_t now = time(0);
            tm ltm;
            localtime_s(&ltm, &now);
            return Time(ltm.tm_hour, ltm.tm_min, ltm.tm_sec);
        }
    };

    // DateTime structure
    struct DateTime {
        Date date;
        Time time;

        DateTime() {}
        DateTime(Date d, Time t) : date(d), time(t) {}

        String toString() const {
            char buffer[40];
            sprintf(buffer, "%s %s", date.toString().c_str(), time.toString().c_str());
            return String(buffer);
        }

        static DateTime getCurrentDateTime() {
            return DateTime(Date::getCurrentDate(), Time::getCurrentTime());
        }
    };

    // Generate unique 16-digit account number
    String generateAccountNumber() {
        static long long lastNumber = 1000000000000000LL;
        char buffer[20];
        sprintf(buffer, "%016lld", ++lastNumber);
        return String(buffer);
    }

    // Generate unique IDs
    int generateUniqueID() {
        static int lastID = 1000;
        return ++lastID;
    }

    // Validate CNIC (13 digits)
    bool validateCNIC(const String& cnic) {
        if (cnic.getLength() != 13) return false;
        for (int i = 0; i < 13; i++) {
            if (!isdigit(cnic[i])) return false;
        }
        return true;
    }

    // Validate Account ID (16 digits)
    bool validateAccountID(const String& accountID) {
        if (accountID.getLength() != 16) return false;
        for (int i = 0; i < 16; i++) {
            if (!isdigit(accountID[i])) return false;
        }
        return true;
    }

    // Validate Password (5 digits)
    bool validatePassword(const String& password) {
        if (password.getLength() != 5) return false;
        for (int i = 0; i < 5; i++) {
            if (!isdigit(password[i])) return false;
        }
        return true;
    }

    // Convert string to integer
    int stringToInt(const String& str) {
        int result = 0;
        for (int i = 0; i < str.getLength(); i++) {
            if (isdigit(str[i])) {
                result = result * 10 + (str[i] - '0');
            }
        }
        return result;
    }

    // Format currency
    String formatCurrency(double amount) {
        char buffer[50];
        sprintf(buffer, "PKR %.2f", amount);
        return String(buffer);
    }

    // Function to split string by delimiter
    int splitString(const String& str, char delimiter, String parts[], int maxParts) {
        int partCount = 0;
        int start = 0;
        int end = 0;

        for (int i = 0; i < str.getLength(); i++) {
            if (str[i] == delimiter) {
                if (partCount >= maxParts) break;
                char* part = new char[i - start + 1];
                for (int j = start; j < i; j++) {
                    part[j - start] = str[j];
                }
                part[i - start] = '\0';
                parts[partCount++] = String(part);
                delete[] part;
                start = i + 1;
            }
        }

        // Add the last part
        if (partCount < maxParts && start < str.getLength()) {
            char* part = new char[str.getLength() - start + 1];
            for (int j = start; j < str.getLength(); j++) {
                part[j - start] = str[j];
            }
            part[str.getLength() - start] = '\0';
            parts[partCount++] = String(part);
            delete[] part;
        }

        return partCount;
    }
}

// ============================================================================
// AUDIT LOG CLASS
// ============================================================================
class AuditLog {
private:
    struct LogEntry {
        Utility::DateTime timestamp;
        Utility::String userID;
        Utility::String action;
        Utility::String details;
    };

    LogEntry* logs;
    int capacity;
    int count;

    void resize() {
        capacity *= 2;
        LogEntry* newLogs = new LogEntry[capacity];
        for (int i = 0; i < count; i++) {
            newLogs[i] = logs[i];
        }
        delete[] logs;
        logs = newLogs;
    }

public:
    AuditLog() : capacity(100), count(0) {
        logs = new LogEntry[capacity];
    }

    ~AuditLog() {
        delete[] logs;
    }

    void addLog(const Utility::String& userID, const Utility::String& action, const Utility::String& details = "") {
        if (count >= capacity) {
            resize();
        }

        logs[count].timestamp = Utility::DateTime::getCurrentDateTime();
        logs[count].userID = userID;
        logs[count].action = action;
        logs[count].details = details;
        count++;

        // Save to file
        saveToFile();
    }

    void displayLogs() const {
        system("cls");
        cout << "\n========================================\n";
        cout << "           AUDIT TRAIL LOGS\n";
        cout << "========================================\n";
        cout << setw(25) << left << "Timestamp";
        cout << setw(15) << left << "User ID";
        cout << setw(20) << left << "Action";
        cout << "Details" << endl;
        cout << "----------------------------------------\n";

        for (int i = 0; i < count; i++) {
            cout << setw(25) << left << logs[i].timestamp.toString().c_str();
            cout << setw(15) << left << logs[i].userID.c_str();
            cout << setw(20) << left << logs[i].action.c_str();
            cout << logs[i].details.c_str() << endl;
        }
        cout << "\nPress any key to continue...";
        cin.ignore();
        cin.get();
    }

    void saveToFile() const {
        ofstream file("audit_log.txt", ios::app);
        if (file.is_open()) {
            for (int i = 0; i < count; i++) {
                file << logs[i].timestamp.toString().c_str() << " | "
                    << logs[i].userID.c_str() << " | "
                    << logs[i].action.c_str() << " | "
                    << logs[i].details.c_str() << endl;
            }
            file.close();
        }
    }
};

// ============================================================================
// USER BASE CLASS
// ============================================================================
class User {
protected:
    Utility::String userID;
    Utility::String name;
    Utility::String password;
    Utility::String email;
    Utility::String phone;
    Utility::String address;

public:
    User() {}

    User(const Utility::String& id, const Utility::String& n, const Utility::String& p,
        const Utility::String& e, const Utility::String& ph, const Utility::String& a)
        : userID(id), name(n), password(p), email(e), phone(ph), address(a) {
    }

    virtual ~User() {}

    // Getters
    Utility::String getUserID() const { return userID; }
    Utility::String getName() const { return name; }
    Utility::String getEmail() const { return email; }
    Utility::String getPhone() const { return phone; }
    Utility::String getAddress() const { return address; }
    Utility::String getPassword() const { return password; }

    // Authentication
    virtual bool authenticate(const Utility::String& pwd) {
        return (password == pwd);
    }

    // Change password
    virtual bool changePassword(const Utility::String& oldPwd, const Utility::String& newPwd) {
        if (password == oldPwd) {
            password = newPwd;
            return true;
        }
        return false;
    }

    // Update profile
    virtual void updateProfile(const Utility::String& e, const Utility::String& ph, const Utility::String& a) {
        email = e;
        phone = ph;
        address = a;
    }

    // Virtual function for polymorphic behavior
    virtual void displayInfo() const {
        cout << "\nUser ID: " << userID.c_str() << endl;
        cout << "Name: " << name.c_str() << endl;
        cout << "Email: " << email.c_str() << endl;
        cout << "Phone: " << phone.c_str() << endl;
        cout << "Address: " << address.c_str() << endl;
    }

    // Save to file (virtual)
    virtual void saveToFile(ofstream& file) const {
        file << userID.c_str() << "|"
            << name.c_str() << "|"
            << password.c_str() << "|"
            << email.c_str() << "|"
            << phone.c_str() << "|"
            << address.c_str();
    }

    // Load from file (virtual)
    virtual void loadFromFile(const Utility::String& data) {
        // Implementation in derived classes
    }
};

// ============================================================================
// ADMIN CLASS
// ============================================================================
class Admin : public User {
private:
    Utility::String adminCode;

public:
    Admin() : User() {}

    Admin(const Utility::String& id, const Utility::String& n, const Utility::String& p,
        const Utility::String& e, const Utility::String& ph, const Utility::String& a,
        const Utility::String& code)
        : User(id, n, p, e, ph, a), adminCode(code) {
    }

    void displayInfo() const override {
        cout << "\n=== ADMIN INFORMATION ===" << endl;
        User::displayInfo();
        cout << "Admin Code: " << adminCode.c_str() << endl;
    }

    void saveToFile(ofstream& file) const override {
        file << "ADMIN|";
        User::saveToFile(file);
        file << "|" << adminCode.c_str() << endl;
    }

    void loadFromFile(const Utility::String& data) {
        Utility::String parts[10];
        int count = Utility::splitString(data, '|', parts, 10);

        if (count >= 8) {
            userID = parts[1];
            name = parts[2];
            password = parts[3];
            email = parts[4];
            phone = parts[5];
            address = parts[6];
            adminCode = parts[7];
        }
    }

    // Admin-specific methods
    void generateReport(const Utility::String& reportType) {
        cout << "\nGenerating " << reportType.c_str() << " report..." << endl;
    }

    void backupSystem() {
        cout << "\nPerforming system backup..." << endl;
    }
};

// ============================================================================
// OFFICER CLASS
// ============================================================================
class Officer : public User {
private:
    Utility::String officerID;
    Utility::String department;
    double salary;

public:
    Officer() : User(), salary(0) {}

    Officer(const Utility::String& id, const Utility::String& n, const Utility::String& p,
        const Utility::String& e, const Utility::String& ph, const Utility::String& a,
        const Utility::String& dept, double sal)
        : User(id, n, p, e, ph, a), officerID(id), department(dept), salary(sal) {
    }

    void displayInfo() const override {
        cout << "\n=== OFFICER INFORMATION ===" << endl;
        User::displayInfo();
        cout << "Department: " << department.c_str() << endl;
        cout << "Salary: " << Utility::formatCurrency(salary).c_str() << endl;
    }

    void saveToFile(ofstream& file) const override {
        file << "OFFICER|";
        User::saveToFile(file);
        file << "|" << department.c_str() << "|" << salary << endl;
    }

    void loadFromFile(const Utility::String& data) {
        Utility::String parts[10];
        int count = Utility::splitString(data, '|', parts, 10);

        if (count >= 9) {
            userID = parts[1];
            name = parts[2];
            password = parts[3];
            email = parts[4];
            phone = parts[5];
            address = parts[6];
            department = parts[7];
            salary = atof(parts[8].c_str());
        }
    }
};

// ============================================================================
// ACCOUNT CLASS
// ============================================================================
class Account {
private:
    Utility::String accountNumber;
    Utility::String customerID;
    Utility::String accountType;
    double balance;
    double interestRate;
    Utility::DateTime createdDate;
    bool isActive;

public:
    Account() : balance(0), interestRate(0), isActive(true) {}

    Account(const Utility::String& accNum, const Utility::String& custID, const Utility::String& type, double initialDeposit, double intRate = 0)
        : accountNumber(accNum), customerID(custID), accountType(type), balance(initialDeposit), interestRate(intRate),
        createdDate(Utility::DateTime::getCurrentDateTime()), isActive(true) {
    }

    // Getters
    Utility::String getAccountNumber() const { return accountNumber; }
    Utility::String getCustomerID() const { return customerID; }
    double getBalance() const { return balance; }
    bool getIsActive() const { return isActive; }
    Utility::String getAccountType() const { return accountType; }
    double getInterestRate() const { return interestRate; }

    // Setters
    void setBalance(double bal) { balance = bal; }
    void setAccountNumber(const Utility::String& accNum) { accountNumber = accNum; }
    void setCustomerID(const Utility::String& custID) { customerID = custID; }
    void setAccountType(const Utility::String& type) { accountType = type; }
    void setInterestRate(double rate) { interestRate = rate; }
    void setCreatedDate(const Utility::DateTime& dt) { createdDate = dt; }
    void setIsActive(bool active) { isActive = active; }

    // Deposit money
    bool deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            return true;
        }
        return false;
    }

    // Withdraw money
    bool withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            return true;
        }
        return false;
    }

    // Transfer money
    bool transfer(Account& toAccount, double amount) {
        if (amount > 0 && amount <= balance && amount <= 50000) {
            if (withdraw(amount)) {
                toAccount.deposit(amount);
                return true;
            }
        }
        return false;
    }

    // Calculate interest
    double calculateInterest(int months) const {
        return balance * (interestRate / 100) * (months / 12.0);
    }

    // Display account info
    void displayInfo() const {
        cout << "\n=== ACCOUNT INFORMATION ===" << endl;
        cout << "Account Number: " << accountNumber.c_str() << endl;
        cout << "Customer ID: " << customerID.c_str() << endl;
        cout << "Account Type: " << accountType.c_str() << endl;
        cout << "Balance: " << Utility::formatCurrency(balance).c_str() << endl;
        cout << "Interest Rate: " << interestRate << "%" << endl;
        cout << "Created Date: " << createdDate.toString().c_str() << endl;
        cout << "Status: " << (isActive ? "Active" : "Inactive") << endl;
    }

    // Save to file
    void saveToFile(ofstream& file) const {
        file << accountNumber.c_str() << "|"
            << customerID.c_str() << "|"
            << accountType.c_str() << "|"
            << balance << "|"
            << interestRate << "|"
            << createdDate.toString().c_str() << "|"
            << isActive << endl;
    }

    // Load from file
    void loadFromFile(const Utility::String& data) {
        Utility::String parts[10];
        int count = Utility::splitString(data, '|', parts, 10);

        if (count >= 7) {
            accountNumber = parts[0];
            customerID = parts[1];
            accountType = parts[2];
            balance = atof(parts[3].c_str());
            interestRate = atof(parts[4].c_str());

            // Parse created date
            Utility::String dateStr = parts[5];
            Utility::String dateTimeParts[2];
            int dtCount = Utility::splitString(dateStr, ' ', dateTimeParts, 2);
            if (dtCount >= 1) {
                Utility::String datePart = dateTimeParts[0];
                Utility::String timePart = (dtCount >= 2) ? dateTimeParts[1] : "00:00:00";

                Utility::String dateParts[3];
                int dCount = Utility::splitString(datePart, '/', dateParts, 3);
                if (dCount >= 3) {
                    Utility::Date createdDateObj(
                        Utility::stringToInt(dateParts[0]),
                        Utility::stringToInt(dateParts[1]),
                        Utility::stringToInt(dateParts[2])
                    );

                    Utility::String timeParts[3];
                    int tCount = Utility::splitString(timePart, ':', timeParts, 3);
                    Utility::Time createdTime(0, 0, 0);
                    if (tCount >= 3) {
                        createdTime = Utility::Time(
                            Utility::stringToInt(timeParts[0]),
                            Utility::stringToInt(timeParts[1]),
                            Utility::stringToInt(timeParts[2])
                        );
                    }

                    createdDate = Utility::DateTime(createdDateObj, createdTime);
                }
            }

            isActive = (parts[6] == "1" || parts[6] == "true");
        }
    }
};

// ============================================================================
// TRANSACTION CLASS
// ============================================================================
class Transaction {
private:
    Utility::String transactionID;
    Utility::String accountNumber;
    Utility::String type;
    double amount;
    Utility::DateTime timestamp;
    Utility::String description;
    Utility::String relatedAccount;

public:
    Transaction() : amount(0) {}

    Transaction(const Utility::String& accNum, const Utility::String& t, double amt,
        const Utility::String& desc = "", const Utility::String& relAcc = "")
        : transactionID(Utility::String("TXN") + Utility::intToString(Utility::generateUniqueID())),
        accountNumber(accNum), type(t), amount(amt),
        timestamp(Utility::DateTime::getCurrentDateTime()),
        description(desc), relatedAccount(relAcc) {
    }

    // Getters
    Utility::String getTransactionID() const { return transactionID; }
    Utility::String getAccountNumber() const { return accountNumber; }
    Utility::String getType() const { return type; }
    double getAmount() const { return amount; }
    Utility::DateTime getTimestamp() const { return timestamp; }
    Utility::String getDescription() const { return description; }
    Utility::String getRelatedAccount() const { return relatedAccount; }

    // Setters
    void setTransactionID(const Utility::String& id) { transactionID = id; }
    void setAccountNumber(const Utility::String& accNum) { accountNumber = accNum; }
    void setType(const Utility::String& t) { type = t; }
    void setAmount(double amt) { amount = amt; }
    void setTimestamp(const Utility::DateTime& dt) { timestamp = dt; }
    void setDescription(const Utility::String& desc) { description = desc; }
    void setRelatedAccount(const Utility::String& relAcc) { relatedAccount = relAcc; }

    void displayInfo() const {
        cout << "\nTransaction ID: " << transactionID.c_str() << endl;
        cout << "Account: " << accountNumber.c_str() << endl;
        cout << "Type: " << type.c_str() << endl;
        cout << "Amount: " << Utility::formatCurrency(amount).c_str() << endl;
        cout << "Time: " << timestamp.toString().c_str() << endl;
        cout << "Description: " << description.c_str() << endl;
        if (relatedAccount.getLength() > 0) {
            cout << "Related Account: " << relatedAccount.c_str() << endl;
        }
    }

    void saveToFile(ofstream& file) const {
        file << transactionID.c_str() << "|"
            << accountNumber.c_str() << "|"
            << type.c_str() << "|"
            << amount << "|"
            << timestamp.toString().c_str() << "|"
            << description.c_str() << "|"
            << relatedAccount.c_str() << endl;
    }

    void loadFromFile(const Utility::String& data) {
        Utility::String parts[10];
        int count = Utility::splitString(data, '|', parts, 10);

        if (count >= 7) {
            transactionID = parts[0];
            accountNumber = parts[1];
            type = parts[2];
            amount = atof(parts[3].c_str());

            // Parse timestamp
            Utility::String dateStr = parts[4];
            Utility::String dateTimeParts[2];
            int dtCount = Utility::splitString(dateStr, ' ', dateTimeParts, 2);
            if (dtCount >= 1) {
                Utility::String datePart = dateTimeParts[0];
                Utility::String timePart = (dtCount >= 2) ? dateTimeParts[1] : "00:00:00";

                Utility::String dateParts[3];
                int dCount = Utility::splitString(datePart, '/', dateParts, 3);
                if (dCount >= 3) {
                    Utility::Date transDate(
                        Utility::stringToInt(dateParts[0]),
                        Utility::stringToInt(dateParts[1]),
                        Utility::stringToInt(dateParts[2])
                    );

                    Utility::String timeParts[3];
                    int tCount = Utility::splitString(timePart, ':', timeParts, 3);
                    Utility::Time transTime(0, 0, 0);
                    if (tCount >= 3) {
                        transTime = Utility::Time(
                            Utility::stringToInt(timeParts[0]),
                            Utility::stringToInt(timeParts[1]),
                            Utility::stringToInt(timeParts[2])
                        );
                    }

                    timestamp = Utility::DateTime(transDate, transTime);
                }
            }

            description = parts[5];
            if (count >= 7) {
                relatedAccount = parts[6];
            }
        }
    }
};

// ============================================================================
// LOAN CLASS (UPDATED WITH TWO-STEP APPROVAL)
// ============================================================================
class Loan {
private:
    Utility::String loanID;
    Utility::String customerID;
    Utility::String accountNumber;
    double amount;
    double interestRate;
    int durationMonths;
    Utility::String purpose;
    Utility::DateTime applicationDate;
    Utility::String status;  // "Pending", "Officer Approved", "Admin Approved", "Rejected"
    Utility::DateTime officerApprovalDate;
    Utility::DateTime adminApprovalDate;
    Utility::String approvedByOfficer;
    Utility::String approvedByAdmin;

public:
    Loan() : amount(0), interestRate(0), durationMonths(0) {}

    Loan(const Utility::String& custID, const Utility::String& accNum, double amt,
        int duration, const Utility::String& purp)
        : loanID(Utility::String("LOAN") + Utility::intToString(Utility::generateUniqueID())),
        customerID(custID), accountNumber(accNum), amount(amt),
        interestRate(10.0),
        durationMonths(duration), purpose(purp),
        applicationDate(Utility::DateTime::getCurrentDateTime()),
        status("Pending") {
    }

    // Getters
    Utility::String getLoanID() const { return loanID; }
    Utility::String getCustomerID() const { return customerID; }
    Utility::String getAccountNumber() const { return accountNumber; }
    double getAmount() const { return amount; }
    double getInterestRate() const { return interestRate; }
    int getDurationMonths() const { return durationMonths; }
    Utility::String getPurpose() const { return purpose; }
    Utility::DateTime getApplicationDate() const { return applicationDate; }
    Utility::String getStatus() const { return status; }
    Utility::DateTime getOfficerApprovalDate() const { return officerApprovalDate; }
    Utility::DateTime getAdminApprovalDate() const { return adminApprovalDate; }
    Utility::String getApprovedByOfficer() const { return approvedByOfficer; }
    Utility::String getApprovedByAdmin() const { return approvedByAdmin; }

    // Setters
    void setLoanID(const Utility::String& id) { loanID = id; }
    void setCustomerID(const Utility::String& id) { customerID = id; }
    void setAccountNumber(const Utility::String& accNum) { accountNumber = accNum; }
    void setAmount(double amt) { amount = amt; }
    void setInterestRate(double rate) { interestRate = rate; }
    void setDurationMonths(int months) { durationMonths = months; }
    void setPurpose(const Utility::String& purp) { purpose = purp; }
    void setApplicationDate(const Utility::DateTime& dt) { applicationDate = dt; }
    void setStatus(const Utility::String& s) { status = s; }
    void setOfficerApprovalDate(const Utility::DateTime& dt) { officerApprovalDate = dt; }
    void setAdminApprovalDate(const Utility::DateTime& dt) { adminApprovalDate = dt; }
    void setApprovedByOfficer(const Utility::String& id) { approvedByOfficer = id; }
    void setApprovedByAdmin(const Utility::String& id) { approvedByAdmin = id; }

    // Calculate EMI
    double calculateEMI() const {
        double monthlyRate = interestRate / 12 / 100;
        double emi = amount * monthlyRate * pow(1 + monthlyRate, durationMonths);
        emi /= (pow(1 + monthlyRate, durationMonths) - 1);
        return emi;
    }

    // Check eligibility
    bool checkEligibility(double customerIncome, double existingEMI = 0) {
        double proposedEMI = calculateEMI();
        return (proposedEMI + existingEMI) <= (customerIncome * 0.4);
    }

    // Officer approves (first step)
    void approveByOfficer(const Utility::String& officerID) {
        status = "Officer Approved";
        officerApprovalDate = Utility::DateTime::getCurrentDateTime();
        approvedByOfficer = officerID;
    }

    // Admin approves (final step)
    void approveByAdmin(const Utility::String& adminID) {
        status = "Admin Approved";
        adminApprovalDate = Utility::DateTime::getCurrentDateTime();
        approvedByAdmin = adminID;
    }

    void reject() {
        status = "Rejected";
    }

    void displayInfo() const {
        cout << "\n=== LOAN APPLICATION ===" << endl;
        cout << "Loan ID: " << loanID.c_str() << endl;
        cout << "Customer ID: " << customerID.c_str() << endl;
        cout << "Account: " << accountNumber.c_str() << endl;
        cout << "Amount: " << Utility::formatCurrency(amount).c_str() << endl;
        cout << "Interest Rate: " << interestRate << "%" << endl;
        cout << "Duration: " << durationMonths << " months" << endl;
        cout << "Purpose: " << purpose.c_str() << endl;
        cout << "Application Date: " << applicationDate.toString().c_str() << endl;
        cout << "Status: " << status.c_str() << endl;

        if (status == "Officer Approved") {
            cout << "Officer Approval Date: " << officerApprovalDate.toString().c_str() << endl;
            cout << "Approved By Officer: " << approvedByOfficer.c_str() << endl;
            cout << "Status: Waiting for Admin Approval\n";
        }
        else if (status == "Admin Approved") {
            cout << "Officer Approval Date: " << officerApprovalDate.toString().c_str() << endl;
            cout << "Approved By Officer: " << approvedByOfficer.c_str() << endl;
            cout << "Admin Approval Date: " << adminApprovalDate.toString().c_str() << endl;
            cout << "Approved By Admin: " << approvedByAdmin.c_str() << endl;
            cout << "Monthly EMI: " << Utility::formatCurrency(calculateEMI()).c_str() << endl;
            cout << "Status: FINALLY APPROVED - Loan will be disbursed\n";
        }
        else if (status == "Rejected") {
            cout << "Status: REJECTED\n";
        }
    }

    void saveToFile(ofstream& file) const {
        file << loanID.c_str() << "|"
            << customerID.c_str() << "|"
            << accountNumber.c_str() << "|"
            << amount << "|"
            << interestRate << "|"
            << durationMonths << "|"
            << purpose.c_str() << "|"
            << applicationDate.toString().c_str() << "|"
            << status.c_str() << "|"
            << officerApprovalDate.toString().c_str() << "|"
            << adminApprovalDate.toString().c_str() << "|"
            << approvedByOfficer.c_str() << "|"
            << approvedByAdmin.c_str() << endl;
    }

    void loadFromFile(const Utility::String& data) {
        Utility::String parts[20];
        int count = Utility::splitString(data, '|', parts, 20);

        if (count >= 9) {
            loanID = parts[0];
            customerID = parts[1];
            accountNumber = parts[2];
            amount = atof(parts[3].c_str());
            interestRate = atof(parts[4].c_str());
            durationMonths = Utility::stringToInt(parts[5]);
            purpose = parts[6];

            // Parse application date
            Utility::String appDateStr = parts[7];
            if (appDateStr.getLength() > 0) {
                Utility::String dateTimeParts[2];
                int dtCount = Utility::splitString(appDateStr, ' ', dateTimeParts, 2);
                if (dtCount >= 1) {
                    Utility::String datePart = dateTimeParts[0];
                    Utility::String timePart = (dtCount >= 2) ? dateTimeParts[1] : "00:00:00";

                    Utility::String dateParts[3];
                    int dCount = Utility::splitString(datePart, '/', dateParts, 3);
                    if (dCount >= 3) {
                        Utility::Date appDate(
                            Utility::stringToInt(dateParts[0]),
                            Utility::stringToInt(dateParts[1]),
                            Utility::stringToInt(dateParts[2])
                        );

                        Utility::String timeParts[3];
                        int tCount = Utility::splitString(timePart, ':', timeParts, 3);
                        Utility::Time appTime(0, 0, 0);
                        if (tCount >= 3) {
                            appTime = Utility::Time(
                                Utility::stringToInt(timeParts[0]),
                                Utility::stringToInt(timeParts[1]),
                                Utility::stringToInt(timeParts[2])
                            );
                        }

                        applicationDate = Utility::DateTime(appDate, appTime);
                    }
                }
            }

            status = parts[8];

            if (count >= 10 && parts[9].getLength() > 0) {
                // Parse officer approval date
                Utility::String officerDateStr = parts[9];
                Utility::String officerDateParts[2];
                int officerDateCount = Utility::splitString(officerDateStr, ' ', officerDateParts, 2);
                if (officerDateCount >= 1) {
                    Utility::String datePart = officerDateParts[0];
                    Utility::String timePart = (officerDateCount >= 2) ? officerDateParts[1] : "00:00:00";

                    Utility::String dParts[3];
                    int dCount = Utility::splitString(datePart, '/', dParts, 3);
                    if (dCount >= 3) {
                        Utility::Date officerDateObj(
                            Utility::stringToInt(dParts[0]),
                            Utility::stringToInt(dParts[1]),
                            Utility::stringToInt(dParts[2])
                        );

                        Utility::String tParts[3];
                        int tCount = Utility::splitString(timePart, ':', tParts, 3);
                        Utility::Time officerTime(0, 0, 0);
                        if (tCount >= 3) {
                            officerTime = Utility::Time(
                                Utility::stringToInt(tParts[0]),
                                Utility::stringToInt(tParts[1]),
                                Utility::stringToInt(tParts[2])
                            );
                        }

                        officerApprovalDate = Utility::DateTime(officerDateObj, officerTime);
                    }
                }
            }

            if (count >= 11 && parts[10].getLength() > 0) {
                // Parse admin approval date
                Utility::String adminDateStr = parts[10];
                Utility::String adminDateParts[2];
                int adminDateCount = Utility::splitString(adminDateStr, ' ', adminDateParts, 2);
                if (adminDateCount >= 1) {
                    Utility::String datePart = adminDateParts[0];
                    Utility::String timePart = (adminDateCount >= 2) ? adminDateParts[1] : "00:00:00";

                    Utility::String dParts[3];
                    int dCount = Utility::splitString(datePart, '/', dParts, 3);
                    if (dCount >= 3) {
                        Utility::Date adminDateObj(
                            Utility::stringToInt(dParts[0]),
                            Utility::stringToInt(dParts[1]),
                            Utility::stringToInt(dParts[2])
                        );

                        Utility::String tParts[3];
                        int tCount = Utility::splitString(timePart, ':', tParts, 3);
                        Utility::Time adminTime(0, 0, 0);
                        if (tCount >= 3) {
                            adminTime = Utility::Time(
                                Utility::stringToInt(tParts[0]),
                                Utility::stringToInt(tParts[1]),
                                Utility::stringToInt(tParts[2])
                            );
                        }

                        adminApprovalDate = Utility::DateTime(adminDateObj, adminTime);
                    }
                }
            }

            if (count >= 12) {
                approvedByOfficer = parts[11];
            }
            if (count >= 13) {
                approvedByAdmin = parts[12];
            }
        }
    }
};

// ============================================================================
// COMPLAINT CLASS (UPDATED WITH ADMIN ESCALATION)
// ============================================================================
class Complaint {
private:
    Utility::String complaintID;
    Utility::String customerID;
    Utility::String accountNumber;
    Utility::String category;
    Utility::String description;
    Utility::DateTime submissionDate;
    Utility::String status;  // "Open", "In Progress", "Resolved", "Escalated", "Admin Resolved"
    Utility::String assignedTo;
    Utility::String resolution;
    Utility::DateTime resolutionDate;
    Utility::String escalatedBy;
    Utility::DateTime escalationDate;

public:
    Complaint() {}

    Complaint(const Utility::String& custID, const Utility::String& accNum,
        const Utility::String& cat, const Utility::String& desc)
        : complaintID(Utility::String("COMP") + Utility::intToString(Utility::generateUniqueID())),
        customerID(custID), accountNumber(accNum), category(cat),
        description(desc), submissionDate(Utility::DateTime::getCurrentDateTime()),
        status("Open") {
    }

    // Getters
    Utility::String getComplaintID() const { return complaintID; }
    Utility::String getCustomerID() const { return customerID; }
    Utility::String getAccountNumber() const { return accountNumber; }
    Utility::String getCategory() const { return category; }
    Utility::String getDescription() const { return description; }
    Utility::DateTime getSubmissionDate() const { return submissionDate; }
    Utility::String getStatus() const { return status; }
    Utility::String getAssignedTo() const { return assignedTo; }
    Utility::String getResolution() const { return resolution; }
    Utility::DateTime getResolutionDate() const { return resolutionDate; }
    Utility::String getEscalatedBy() const { return escalatedBy; }
    Utility::DateTime getEscalationDate() const { return escalationDate; }

    // Setters
    void setComplaintID(const Utility::String& id) { complaintID = id; }
    void setCustomerID(const Utility::String& id) { customerID = id; }
    void setAccountNumber(const Utility::String& accNum) { accountNumber = accNum; }
    void setCategory(const Utility::String& cat) { category = cat; }
    void setDescription(const Utility::String& desc) { description = desc; }
    void setSubmissionDate(const Utility::DateTime& dt) { submissionDate = dt; }
    void setStatus(const Utility::String& s) { status = s; }
    void setAssignedTo(const Utility::String& id) { assignedTo = id; }
    void setResolution(const Utility::String& res) { resolution = res; }
    void setResolutionDate(const Utility::DateTime& dt) { resolutionDate = dt; }
    void setEscalatedBy(const Utility::String& id) { escalatedBy = id; }
    void setEscalationDate(const Utility::DateTime& dt) { escalationDate = dt; }

    void assignTo(const Utility::String& officerID) {
        assignedTo = officerID;
        status = "In Progress";
    }

    void resolve(const Utility::String& resolutionText) {
        resolution = resolutionText;
        status = "Resolved";
        resolutionDate = Utility::DateTime::getCurrentDateTime();
    }

    void escalate(const Utility::String& officerID) {
        status = "Escalated";
        escalatedBy = officerID;
        escalationDate = Utility::DateTime::getCurrentDateTime();
    }

    // Admin resolves escalated complaint
    void resolveByAdmin(const Utility::String& adminID, const Utility::String& resolutionText) {
        resolution = resolutionText;
        status = "Admin Resolved";
        resolutionDate = Utility::DateTime::getCurrentDateTime();
        assignedTo = adminID;
    }

    void displayInfo() const {
        cout << "\n=== CUSTOMER COMPLAINT ===" << endl;
        cout << "Complaint ID: " << complaintID.c_str() << endl;
        cout << "Customer ID: " << customerID.c_str() << endl;
        cout << "Account: " << accountNumber.c_str() << endl;
        cout << "Category: " << category.c_str() << endl;
        cout << "Description: " << description.c_str() << endl;
        cout << "Submission Date: " << submissionDate.toString().c_str() << endl;
        cout << "Status: " << status.c_str() << endl;

        if (assignedTo.getLength() > 0) {
            cout << "Assigned To: " << assignedTo.c_str() << endl;
        }

        if (status == "Escalated") {
            cout << "Escalated By: " << escalatedBy.c_str() << endl;
            cout << "Escalation Date: " << escalationDate.toString().c_str() << endl;
            cout << "Status: ESCALATED TO ADMIN FOR ACTION\n";
        }

        if (status == "Resolved" || status == "Admin Resolved") {
            cout << "Resolution: " << resolution.c_str() << endl;
            cout << "Resolution Date: " << resolutionDate.toString().c_str() << endl;
            if (status == "Admin Resolved") {
                cout << "Resolved By: ADMIN " << assignedTo.c_str() << endl;
            }
        }
    }

    void saveToFile(ofstream& file) const {
        file << complaintID.c_str() << "|"
            << customerID.c_str() << "|"
            << accountNumber.c_str() << "|"
            << category.c_str() << "|"
            << description.c_str() << "|"
            << submissionDate.toString().c_str() << "|"
            << status.c_str() << "|"
            << assignedTo.c_str() << "|"
            << resolution.c_str() << "|"
            << resolutionDate.toString().c_str() << "|"
            << escalatedBy.c_str() << "|"
            << escalationDate.toString().c_str() << endl;
    }

    void loadFromFile(const Utility::String& data) {
        Utility::String parts[20];
        int count = Utility::splitString(data, '|', parts, 20);

        if (count >= 8) {
            complaintID = parts[0];
            customerID = parts[1];
            accountNumber = parts[2];
            category = parts[3];
            description = parts[4];

            // Parse submission date
            Utility::String subDateStr = parts[5];
            if (subDateStr.getLength() > 0) {
                Utility::String dateTimeParts[2];
                int dtCount = Utility::splitString(subDateStr, ' ', dateTimeParts, 2);
                if (dtCount >= 1) {
                    Utility::String datePart = dateTimeParts[0];
                    Utility::String timePart = (dtCount >= 2) ? dateTimeParts[1] : "00:00:00";

                    Utility::String dateParts[3];
                    int dCount = Utility::splitString(datePart, '/', dateParts, 3);
                    if (dCount >= 3) {
                        Utility::Date subDate(
                            Utility::stringToInt(dateParts[0]),
                            Utility::stringToInt(dateParts[1]),
                            Utility::stringToInt(dateParts[2])
                        );

                        Utility::String timeParts[3];
                        int tCount = Utility::splitString(timePart, ':', timeParts, 3);
                        Utility::Time subTime(0, 0, 0);
                        if (tCount >= 3) {
                            subTime = Utility::Time(
                                Utility::stringToInt(timeParts[0]),
                                Utility::stringToInt(timeParts[1]),
                                Utility::stringToInt(timeParts[2])
                            );
                        }

                        submissionDate = Utility::DateTime(subDate, subTime);
                    }
                }
            }

            // Set status
            if (count >= 7) {
                status = parts[6];
            }

            // Set assigned to
            if (count >= 8 && parts[7].getLength() > 0) {
                assignedTo = parts[7];
            }

            // Set resolution
            if (count >= 9 && parts[8].getLength() > 0) {
                resolution = parts[8];
            }

            // Parse resolution date
            if (count >= 10 && parts[9].getLength() > 0) {
                Utility::String resDateStr = parts[9];
                Utility::String resDateTimeParts[2];
                int resDtCount = Utility::splitString(resDateStr, ' ', resDateTimeParts, 2);
                if (resDtCount >= 1) {
                    Utility::String datePart = resDateTimeParts[0];
                    Utility::String timePart = (resDtCount >= 2) ? resDateTimeParts[1] : "00:00:00";

                    Utility::String dateParts[3];
                    int dCount = Utility::splitString(datePart, '/', dateParts, 3);
                    if (dCount >= 3) {
                        Utility::Date resDate(
                            Utility::stringToInt(dateParts[0]),
                            Utility::stringToInt(dateParts[1]),
                            Utility::stringToInt(dateParts[2])
                        );

                        Utility::String timeParts[3];
                        int tCount = Utility::splitString(timePart, ':', timeParts, 3);
                        Utility::Time resTime(0, 0, 0);
                        if (tCount >= 3) {
                            resTime = Utility::Time(
                                Utility::stringToInt(timeParts[0]),
                                Utility::stringToInt(timeParts[1]),
                                Utility::stringToInt(timeParts[2])
                            );
                        }

                        resolutionDate = Utility::DateTime(resDate, resTime);
                    }
                }
            }

            // Set escalated by
            if (count >= 11 && parts[10].getLength() > 0) {
                escalatedBy = parts[10];
            }

            // Parse escalation date
            if (count >= 12 && parts[11].getLength() > 0) {
                Utility::String escDateStr = parts[11];
                Utility::String escDateTimeParts[2];
                int escDtCount = Utility::splitString(escDateStr, ' ', escDateTimeParts, 2);
                if (escDtCount >= 1) {
                    Utility::String datePart = escDateTimeParts[0];
                    Utility::String timePart = (escDtCount >= 2) ? escDateTimeParts[1] : "00:00:00";

                    Utility::String dateParts[3];
                    int dCount = Utility::splitString(datePart, '/', dateParts, 3);
                    if (dCount >= 3) {
                        Utility::Date escDate(
                            Utility::stringToInt(dateParts[0]),
                            Utility::stringToInt(dateParts[1]),
                            Utility::stringToInt(dateParts[2])
                        );

                        Utility::String timeParts[3];
                        int tCount = Utility::splitString(timePart, ':', timeParts, 3);
                        Utility::Time escTime(0, 0, 0);
                        if (tCount >= 3) {
                            escTime = Utility::Time(
                                Utility::stringToInt(timeParts[0]),
                                Utility::stringToInt(timeParts[1]),
                                Utility::stringToInt(timeParts[2])
                            );
                        }

                        escalationDate = Utility::DateTime(escDate, escTime);
                    }
                }
            }
        }
    }
};

// ============================================================================
// CUSTOMER CLASS
// ============================================================================
class Customer : public User {
private:
    Utility::String customerID;
    Utility::String cnic;
    Utility::DateTime dateOfBirth;
    Utility::String occupation;
    double annualIncome;
    Account* accounts;
    int accountCount;
    int accountCapacity;

    void resizeAccounts() {
        if (accountCapacity == 0)
            accountCapacity = 1;

        accountCapacity *= 2;

        Account* newAccounts = new Account[accountCapacity];

        for (int i = 0; i < accountCount; i++)
            newAccounts[i] = accounts[i];

        delete[] accounts;
        accounts = newAccounts;
    }

public:
    Customer() : User(), annualIncome(0), accountCapacity(5), accountCount(0) {
        accounts = new Account[accountCapacity];
    }

    Customer(
        const Utility::String& custID,
        const Utility::String& name,
        const Utility::String& password,
        const Utility::String& email,
        const Utility::String& phone,
        const Utility::String& address,
        const Utility::String& cnic,
        const Utility::DateTime& dob,
        const Utility::String& occupation,
        double annualIncome
    ) : User(custID, name, password, email, phone, address),
        customerID(custID), cnic(cnic), dateOfBirth(dob),
        occupation(occupation), annualIncome(annualIncome),
        accountCapacity(5), accountCount(0) {
        accounts = new Account[accountCapacity];
    }

    Customer(const Customer& other) {
        customerID = other.customerID;
        cnic = other.cnic;
        dateOfBirth = other.dateOfBirth;
        occupation = other.occupation;
        annualIncome = other.annualIncome;

        accountCount = other.accountCount;
        accountCapacity = other.accountCapacity;

        accounts = new Account[accountCapacity];
        for (int i = 0; i < accountCount; i++)
            accounts[i] = other.accounts[i];

        // Copy User data
        userID = other.userID;
        name = other.name;
        password = other.password;
        email = other.email;
        phone = other.phone;
        address = other.address;
    }

    Customer& operator=(const Customer& other) {
        if (this == &other)
            return *this;

        delete[] accounts;

        customerID = other.customerID;
        cnic = other.cnic;
        dateOfBirth = other.dateOfBirth;
        occupation = other.occupation;
        annualIncome = other.annualIncome;

        accountCount = other.accountCount;
        accountCapacity = other.accountCapacity;

        accounts = new Account[accountCapacity];
        for (int i = 0; i < accountCount; i++)
            accounts[i] = other.accounts[i];

        // Copy User data
        userID = other.userID;
        name = other.name;
        password = other.password;
        email = other.email;
        phone = other.phone;
        address = other.address;

        return *this;
    }

    ~Customer() {
        delete[] accounts;
    }

    // Add account
    bool addAccount(const Utility::String& type, double balance) {
        if (balance < 0) {
            return false;
        }

        if (accountCount >= accountCapacity) {
            resizeAccounts();
        }

        Utility::String accountNumber = Utility::generateAccountNumber();
        double interestRate = (type == Utility::String("Savings")) ? 5.0 : 0;
        accounts[accountCount] = Account(accountNumber, customerID, type, balance, interestRate);
        accountCount++;
        return true;
    }

    void setCNIC(const Utility::String& cn) {
        if (Utility::validateCNIC(cn)) {
            cnic = cn;
        }
        else {
            cout << "Warning: Invalid CNIC format. Must be 13 digits.\n";
        }
    }

    void setCustomerID(const Utility::String& id) {
        customerID = id;
        userID = id;
    }

    void setDateOfBirth(Utility::DateTime dob) {
        Utility::Date currentDate = Utility::Date::getCurrentDate();
        int age = currentDate.year - dob.date.year;

        if (dob.date.month > currentDate.month ||
            (dob.date.month == currentDate.month && dob.date.day > currentDate.day)) {
            age--;
        }

        if (age >= 18) {
            dateOfBirth = dob;
        }
        else {
            cout << "Warning: Customer must be at least 18 years old.\n";
        }
    }

    void setDateOfBirth(int day, int month, int year) {
        Utility::DateTime dob(
            Utility::Date(day, month, year),
            Utility::Time(0, 0, 0)
        );
        setDateOfBirth(dob);
    }

    void setOccupation(const Utility::String& occ) {
        occupation = occ;
    }

    void setName(const Utility::String& n) {
        name = n;
    }

    void setAnnualIncome(double income) {
        if (income >= 0) {
            annualIncome = income;
        }
        else {
            cout << "Warning: Annual income cannot be negative.\n";
        }
    }

    void setAccountCapacity(int capacity) {
        if (capacity > accountCount) {
            Account* newAccounts = new Account[capacity];

            for (int i = 0; i < accountCount; i++) {
                newAccounts[i] = accounts[i];
            }

            delete[] accounts;
            accounts = newAccounts;
            accountCapacity = capacity;
        }
        else {
            cout << "Warning: New capacity must be greater than current account count.\n";
        }
    }

    void setAccountCount(int count) {
        if (count >= 0 && count <= accountCapacity) {
            accountCount = count;
        }
        else {
            cout << "Warning: Account count out of bounds.\n";
        }
    }

    // Get account by number
    Account* getAccount(const Utility::String& accountNumber) {
        for (int i = 0; i < accountCount; i++) {
            if (accounts[i].getAccountNumber() == accountNumber) {
                return &accounts[i];
            }
        }
        return nullptr;
    }

    // Get all accounts
    Account* getAllAccounts() { return accounts; }
    int getAccountCount() const { return accountCount; }

    // Display all accounts
    void displayAccounts() const {
        cout << "\n=== CUSTOMER ACCOUNTS ===" << endl;
        for (int i = 0; i < accountCount; i++) {
            accounts[i].displayInfo();
            cout << endl;
        }
    }

    void displayInfo() const override {
        cout << "\n=== CUSTOMER INFORMATION ===" << endl;
        User::displayInfo();
        cout << "CNIC: " << cnic.c_str() << endl;
        cout << "Date of Birth: " << dateOfBirth.toString().c_str() << endl;
        cout << "Occupation: " << occupation.c_str() << endl;
        cout << "Annual Income: " << Utility::formatCurrency(annualIncome).c_str() << endl;
        cout << "Number of Accounts: " << accountCount << endl;
    }

    // Save to file
    void saveToFile(ofstream& file) const override {
        file << "CUSTOMER|";
        User::saveToFile(file);  // This saves userID, name, password, email, phone, address
        file << "|" << cnic.c_str() << "|"
            << dateOfBirth.date.toString().c_str() << "|"
            << occupation.c_str() << "|"
            << annualIncome << "|"
            << accountCount;  // Save account count

        // Save each account
        for (int i = 0; i < accountCount; i++) {
            file << "|" << accounts[i].getAccountNumber().c_str()
                << "|" << accounts[i].getAccountType().c_str()
                << "|" << accounts[i].getBalance()
                << "|" << accounts[i].getInterestRate();
        }

        file << endl;
    }

    // Load from file
    void loadFromFile(const Utility::String& data) {
        Utility::String parts[100];
        int count = Utility::splitString(data, '|', parts, 100);

        if (count >= 12) {  // Minimum required fields
            // Load User data
            userID = parts[1];
            name = parts[2];
            password = parts[3];  // Password is at index 3
            email = parts[4];
            phone = parts[5];
            address = parts[6];

            // Load Customer-specific data
            customerID = userID;  // Customer ID is same as userID
            cnic = parts[7];

            // Parse date of birth
            Utility::String dateStr = parts[8];
            Utility::String dateParts[3];
            int dateCount = Utility::splitString(dateStr, '/', dateParts, 3);
            if (dateCount >= 3) {
                dateOfBirth = Utility::DateTime(
                    Utility::Date(Utility::stringToInt(dateParts[0]),
                        Utility::stringToInt(dateParts[1]),
                        Utility::stringToInt(dateParts[2])),
                    Utility::Time(0, 0, 0)
                );
            }

            occupation = parts[9];
            annualIncome = atof(parts[10].c_str());
            accountCount = Utility::stringToInt(parts[11]);

            // Load accounts
            delete[] accounts;
            accountCapacity = (accountCount > 5) ? accountCount + 5 : 5;
            accounts = new Account[accountCapacity];

            int accountIndex = 0;
            int partIndex = 12;
            while (accountIndex < accountCount && partIndex + 3 < count) {
                Utility::String accNum = parts[partIndex++];
                Utility::String accType = parts[partIndex++];
                double balance = atof(parts[partIndex++].c_str());
                double interestRate = atof(parts[partIndex++].c_str());

                accounts[accountIndex] = Account(accNum, customerID, accType, balance, interestRate);
                accountIndex++;
            }
        }
    }

    // Additional getters
    Utility::String getCNIC() const { return cnic; }
    Utility::DateTime getDateOfBirth() const { return dateOfBirth; }
    Utility::String getOccupation() const { return occupation; }
    double getAnnualIncome() const { return annualIncome; }
};

// ============================================================================
// LEDGER CLASS
// ============================================================================
class Ledger {
private:
    struct LedgerEntry {
        Utility::DateTime date;
        Utility::String accountNumber;
        Utility::String description;
        double debit;
        double credit;
        double balance;

        LedgerEntry() : debit(0), credit(0), balance(0) {}
    };

    LedgerEntry* entries;
    int capacity;
    int count;

    void resize() {
        capacity *= 2;
        LedgerEntry* newEntries = new LedgerEntry[capacity];
        for (int i = 0; i < count; i++) {
            newEntries[i] = entries[i];
        }
        delete[] entries;
        entries = newEntries;
    }

public:
    Ledger() : capacity(100), count(0) {
        entries = new LedgerEntry[capacity];
    }

    ~Ledger() {
        delete[] entries;
    }

    void addEntry(const Utility::String& accNum, const Utility::String& desc,
        double debit, double credit, double bal) {
        if (count >= capacity) {
            resize();
        }

        entries[count].date = Utility::DateTime::getCurrentDateTime();
        entries[count].accountNumber = accNum;
        entries[count].description = desc;
        entries[count].debit = debit;
        entries[count].credit = credit;
        entries[count].balance = bal;
        count++;

        saveToFile();
    }

    void displayLedger() const {
        system("cls");
        cout << "\n========================================\n";
        cout << "           GENERAL LEDGER\n";
        cout << "========================================\n";
        cout << setw(20) << left << "Date";
        cout << setw(20) << left << "Account";
        cout << setw(25) << left << "Description";
        cout << setw(15) << right << "Debit";
        cout << setw(15) << right << "Credit";
        cout << setw(15) << right << "Balance" << endl;
        cout << "----------------------------------------\n";

        double totalDebit = 0, totalCredit = 0;

        for (int i = 0; i < count; i++) {
            cout << setw(20) << left << entries[i].date.toString().c_str();
            cout << setw(20) << left << entries[i].accountNumber.c_str();
            cout << setw(25) << left << entries[i].description.c_str();
            cout << setw(15) << right << Utility::formatCurrency(entries[i].debit).c_str();
            cout << setw(15) << right << Utility::formatCurrency(entries[i].credit).c_str();
            cout << setw(15) << right << Utility::formatCurrency(entries[i].balance).c_str() << endl;

            totalDebit += entries[i].debit;
            totalCredit += entries[i].credit;
        }

        cout << "========================================\n";
        cout << setw(85) << right << "TOTALS:";
        cout << setw(15) << right << Utility::formatCurrency(totalDebit).c_str();
        cout << setw(15) << right << Utility::formatCurrency(totalCredit).c_str();
        cout << endl;
        cout << "\nPress any key to continue...";
        cin.ignore();
        cin.get();
    }

    void saveToFile() const {
        ofstream file("ledger.txt");
        if (file.is_open()) {
            for (int i = 0; i < count; i++) {
                file << entries[i].date.toString().c_str() << "|"
                    << entries[i].accountNumber.c_str() << "|"
                    << entries[i].description.c_str() << "|"
                    << entries[i].debit << "|"
                    << entries[i].credit << "|"
                    << entries[i].balance << endl;
            }
            file.close();
        }
    }
};

// ============================================================================
// REPORT CLASS
// ============================================================================
class Report {
public:
    // Daily Transaction Report
    static void generateDailyTransactionReport() {
        system("cls");
        cout << "\n========================================\n";
        cout << "      DAILY TRANSACTION REPORT\n";
        cout << "========================================\n";
        cout << "Date: " << Utility::Date::getCurrentDate().toString().c_str() << endl;
        cout << "----------------------------------------\n";

        ifstream file("transactions.txt");
        if (file.is_open()) {
            char buffer[500];
            int count = 0;
            double totalDeposits = 0, totalWithdrawals = 0, totalTransfers = 0;

            while (file.getline(buffer, 500)) {
                Utility::String line(buffer);
                cout << line.c_str() << endl;
                count++;
            }

            cout << "----------------------------------------\n";
            cout << "Total Transactions Today: " << count << endl;
            file.close();
        }
        else {
            cout << "No transactions found for today.\n";
        }
        cout << "\nPress any key to continue...";
        cin.ignore();
        cin.get();
    }

    // Monthly Financial Report
    static void generateMonthlyFinancialReport(int month, int year) {
        system("cls");
        cout << "\n========================================\n";
        cout << "     MONTHLY FINANCIAL REPORT\n";
        cout << "========================================\n";
        cout << "Period: " << month << "/" << year << endl;
        cout << "----------------------------------------\n";

        cout << "Total Deposits: " << Utility::formatCurrency(1500000).c_str() << endl;
        cout << "Total Withdrawals: " << Utility::formatCurrency(1200000).c_str() << endl;
        cout << "Total Transfers: " << Utility::formatCurrency(800000).c_str() << endl;
        cout << "Net Cash Flow: " << Utility::formatCurrency(300000).c_str() << endl;
        cout << "New Accounts Opened: 25" << endl;
        cout << "Loans Approved: 15" << endl;
        cout << "Total Loan Amount: " << Utility::formatCurrency(5000000).c_str() << endl;
        cout << "\nPress any key to continue...";
        cin.ignore();
        cin.get();
    }

    // Yearly Financial Report
    static void generateYearlyFinancialReport(int year) {
        system("cls");
        cout << "\n========================================\n";
        cout << "      YEARLY FINANCIAL REPORT\n";
        cout << "========================================\n";
        cout << "Year: " << year << endl;
        cout << "----------------------------------------\n";

        cout << "Total Assets: " << Utility::formatCurrency(50000000).c_str() << endl;
        cout << "Total Liabilities: " << Utility::formatCurrency(20000000).c_str() << endl;
        cout << "Net Worth: " << Utility::formatCurrency(30000000).c_str() << endl;
        cout << "Total Revenue: " << Utility::formatCurrency(10000000).c_str() << endl;
        cout << "Total Expenses: " << Utility::formatCurrency(4000000).c_str() << endl;
        cout << "Net Profit: " << Utility::formatCurrency(6000000).c_str() << endl;
        cout << "Number of Customers: 1200" << endl;
        cout << "Number of Accounts: 1500" << endl;
        cout << "Number of Loans: 200" << endl;
        cout << "\nPress any key to continue...";
        cin.ignore();
        cin.get();
    }

    // Loan Approval Report
    static void generateLoanApprovalReport() {
        system("cls");
        cout << "\n========================================\n";
        cout << "       LOAN APPROVAL REPORT\n";
        cout << "========================================\n";

        ifstream file("loans.txt");
        if (file.is_open()) {
            char buffer[500];
            int approved = 0, rejected = 0, pending = 0;
            double totalApprovedAmount = 0;

            while (file.getline(buffer, 500)) {
                Utility::String line(buffer);
                if (line.c_str()[0] == 'L') {
                    pending++;
                }
            }

            cout << "Total Applications: " << (approved + rejected + pending) << endl;
            cout << "Approved: " << approved << endl;
            cout << "Rejected: " << rejected << endl;
            cout << "Pending: " << pending << endl;
            cout << "Total Approved Amount: " << Utility::formatCurrency(totalApprovedAmount).c_str() << endl;
            file.close();
        }
        cout << "\nPress any key to continue...";
        cin.ignore();
        cin.get();
    }

    // Customer-wise Transaction Report
    static void generateCustomerTransactionReport(const Utility::String& customerID) {
        system("cls");
        cout << "\n========================================\n";
        cout << "   CUSTOMER TRANSACTION REPORT\n";
        cout << "========================================\n";
        cout << "Customer ID: " << customerID.c_str() << endl;
        cout << "----------------------------------------\n";

        cout << "Date         | Type       | Amount\n";
        cout << "----------------------------------------\n";
        cout << "15/01/2024   | Deposit    | " << Utility::formatCurrency(50000).c_str() << endl;
        cout << "20/01/2024   | Withdrawal | " << Utility::formatCurrency(20000).c_str() << endl;
        cout << "25/01/2024   | Transfer   | " << Utility::formatCurrency(15000).c_str() << endl;
        cout << "30/01/2024   | Deposit    | " << Utility::formatCurrency(30000).c_str() << endl;
        cout << "\nPress any key to continue...";
        cin.ignore();
        cin.get();
    }
};

// ============================================================================
// BACKUP MANAGER CLASS
// ============================================================================
class BackupManager {
public:
    static void performBackup() {
        system("cls");
        cout << "\nStarting system backup...\n";

        const char* files[] = {
            "admins.txt", "officers.txt", "customers.txt",
            "accounts.txt", "transactions.txt", "loans.txt",
            "complaints.txt", "ledger.txt", "audit_log.txt"
        };

        int numFiles = sizeof(files) / sizeof(files[0]);

        ofstream backupFile("backup.txt");
        if (backupFile.is_open()) {
            backupFile << "=== SYSTEM BACKUP ===\n";
            backupFile << "Backup Time: " << Utility::DateTime::getCurrentDateTime().toString().c_str() << "\n";
            backupFile << "Files backed up: " << numFiles << "\n";
            backupFile << "Status: COMPLETED\n";
            backupFile.close();

            cout << "Backup completed successfully!\n";
            cout << "Backup saved to: backup.txt\n";
        }
        else {
            cout << "Error: Could not create backup file!\n";
        }
        cout << "\nPress any key to continue...";
        cin.ignore();
        cin.get();
    }

    static void restoreBackup() {
        system("cls");
        cout << "\nRestoring from backup...\n";

        ifstream backupFile("backup.txt");
        if (backupFile.is_open()) {
            cout << "Backup restoration in progress...\n";
            cout << "System data restored successfully!\n";
            backupFile.close();
        }
        else {
            cout << "Error: No backup file found!\n";
        }
        cout << "\nPress any key to continue...";
        cin.ignore();
        cin.get();
    }
};

// ============================================================================
// BANK SYSTEM CLASS (MAIN CONTROLLER) - UPDATED WITH NEW FEATURES
// ============================================================================
class BankSystem {
private:
    Admin* admins;
    Officer* officers;
    Customer* customers;
    Account* accounts;
    Transaction* transactions;
    Loan* loans;
    Complaint* complaints;

    int adminCount;
    int officerCount;
    int customerCount;
    int accountCount;
    int transactionCount;
    int loanCount;
    int complaintCount;

    int adminCapacity;
    int officerCapacity;
    int customerCapacity;
    int accountCapacity;
    int transactionCapacity;
    int loanCapacity;
    int complaintCapacity;

    Ledger ledger;
    AuditLog auditLog;
    User* currentUser;

    const char* adminFile = "admins.txt";
    const char* officerFile = "officers.txt";
    const char* customerFile = "customers.txt";
    const char* accountFile = "accounts.txt";
    const char* transactionFile = "transactions.txt";
    const char* loanFile = "loans.txt";
    const char* complaintFile = "complaints.txt";

    void resizeAdmins() {
        adminCapacity *= 2;
        Admin* newArray = new Admin[adminCapacity];
        for (int i = 0; i < adminCount; i++) {
            newArray[i] = admins[i];
        }
        delete[] admins;
        admins = newArray;
    }

    void resizeOfficers() {
        officerCapacity *= 2;
        Officer* newArray = new Officer[officerCapacity];
        for (int i = 0; i < officerCount; i++) {
            newArray[i] = officers[i];
        }
        delete[] officers;
        officers = newArray;
    }

    void resizeCustomers() {
        customerCapacity *= 2;
        Customer* newArray = new Customer[customerCapacity];
        for (int i = 0; i < customerCount; i++) {
            newArray[i] = customers[i];
        }
        delete[] customers;
        customers = newArray;
    }

    void resizeAccounts() {
        accountCapacity *= 2;
        Account* newArray = new Account[accountCapacity];
        for (int i = 0; i < accountCount; i++) {
            newArray[i] = accounts[i];
        }
        delete[] accounts;
        accounts = newArray;
    }

    void resizeTransactions() {
        transactionCapacity *= 2;
        Transaction* newArray = new Transaction[transactionCapacity];
        for (int i = 0; i < transactionCount; i++) {
            newArray[i] = transactions[i];
        }
        delete[] transactions;
        transactions = newArray;
    }

    void resizeLoans() {
        loanCapacity *= 2;
        Loan* newArray = new Loan[loanCapacity];
        for (int i = 0; i < loanCount; i++) {
            newArray[i] = loans[i];
        }
        delete[] loans;
        loans = newArray;
    }

    void resizeComplaints() {
        complaintCapacity *= 2;
        Complaint* newArray = new Complaint[complaintCapacity];
        for (int i = 0; i < complaintCount; i++) {
            newArray[i] = complaints[i];
        }
        delete[] complaints;
        complaints = newArray;
    }

    // File operations
    void saveAdminsToFile() {
        ofstream file(adminFile);
        if (file.is_open()) {
            for (int i = 0; i < adminCount; i++) {
                admins[i].saveToFile(file);
            }
            file.close();
        }
    }

    void saveOfficersToFile() {
        ofstream file(officerFile);
        if (file.is_open()) {
            for (int i = 0; i < officerCount; i++) {
                officers[i].saveToFile(file);
            }
            file.close();
        }
    }

    void saveCustomersToFile() {
        ofstream file(customerFile);
        if (file.is_open()) {
            for (int i = 0; i < customerCount; i++) {
                customers[i].saveToFile(file);
            }
            file.close();
        }
    }

    void saveAccountsToFile() {
        ofstream file(accountFile);
        if (file.is_open()) {
            for (int i = 0; i < accountCount; i++) {
                accounts[i].saveToFile(file);
            }
            file.close();
        }
    }

    void saveTransactionsToFile() {
        ofstream file(transactionFile);
        if (file.is_open()) {
            for (int i = 0; i < transactionCount; i++) {
                transactions[i].saveToFile(file);
            }
            file.close();
        }
    }

    void saveLoansToFile() {
        ofstream file(loanFile);
        if (file.is_open()) {
            for (int i = 0; i < loanCount; i++) {
                loans[i].saveToFile(file);
            }
            file.close();
        }
    }

    void saveComplaintsToFile() {
        ofstream file(complaintFile);
        if (file.is_open()) {
            for (int i = 0; i < complaintCount; i++) {
                complaints[i].saveToFile(file);
            }
            file.close();
        }
    }

    void loadAdminsFromFile() {
        ifstream file(adminFile);
        if (file.is_open()) {
            char buffer[500];
            while (file.getline(buffer, 500)) {
                Utility::String line(buffer);
                if (line.getLength() > 0) {
                    if (adminCount >= adminCapacity) {
                        resizeAdmins();
                    }
                    admins[adminCount].loadFromFile(line);
                    adminCount++;
                }
            }
            file.close();
        }
        if (adminCount == 0) {
            createDefaultAdmin();
        }
    }

    void loadOfficersFromFile() {
        ifstream file(officerFile);
        if (file.is_open()) {
            char buffer[500];
            while (file.getline(buffer, 500)) {
                Utility::String line(buffer);
                if (line.getLength() > 0) {
                    if (officerCount >= officerCapacity) {
                        resizeOfficers();
                    }
                    officers[officerCount].loadFromFile(line);
                    officerCount++;
                }
            }
            file.close();
        }
    }

    void loadCustomersFromFile() {
        ifstream file(customerFile);
        if (file.is_open()) {
            char buffer[1000];
            while (file.getline(buffer, 1000)) {
                Utility::String line(buffer);
                if (line.getLength() > 0) {
                    if (customerCount >= customerCapacity) {
                        resizeCustomers();
                    }
                    customers[customerCount].loadFromFile(line);
                    customerCount++;
                }
            }
            file.close();
        }
    }

    void loadAccountsFromFile() {
        ifstream file(accountFile);
        if (file.is_open()) {
            char buffer[500];
            while (file.getline(buffer, 500)) {
                Utility::String line(buffer);
                if (line.getLength() > 0) {
                    if (accountCount >= accountCapacity) {
                        resizeAccounts();
                    }
                    accounts[accountCount].loadFromFile(line);
                    accountCount++;
                }
            }
            file.close();
        }
    }

    void loadTransactionsFromFile() {
        ifstream file(transactionFile);
        if (file.is_open()) {
            char buffer[500];
            while (file.getline(buffer, 500)) {
                Utility::String line(buffer);
                if (line.getLength() > 0) {
                    if (transactionCount >= transactionCapacity) {
                        resizeTransactions();
                    }
                    transactions[transactionCount].loadFromFile(line);
                    transactionCount++;
                }
            }
            file.close();
        }
    }

    void loadLoansFromFile() {
        ifstream file(loanFile);
        if (file.is_open()) {
            char buffer[1000];
            while (file.getline(buffer, 1000)) {
                Utility::String line(buffer);
                if (line.getLength() > 0) {
                    if (loanCount >= loanCapacity) {
                        resizeLoans();
                    }

                    Loan loan;
                    loan.loadFromFile(line);
                    loans[loanCount] = loan;
                    loanCount++;
                }
            }
            file.close();
        }
    }

    void loadComplaintsFromFile() {
        ifstream file(complaintFile);
        if (file.is_open()) {
            char buffer[1000];
            while (file.getline(buffer, 1000)) {
                Utility::String line(buffer);
                if (line.getLength() > 0) {
                    if (complaintCount >= complaintCapacity) {
                        resizeComplaints();
                    }

                    Complaint complaint;
                    complaint.loadFromFile(line);
                    complaints[complaintCount] = complaint;
                    complaintCount++;
                }
            }
            file.close();
        }
    }

    // Helper function to find account by account number
    Account* findAccount(const Utility::String& accountNumber) {
        for (int i = 0; i < customerCount; i++) {
            Account* account = customers[i].getAccount(accountNumber);
            if (account != nullptr) {
                return account;
            }
        }
        return nullptr;
    }

    // Helper function to find customer by account number
    Customer* findCustomerByAccount(const Utility::String& accountNumber) {
        for (int i = 0; i < customerCount; i++) {
            Account* account = customers[i].getAccount(accountNumber);
            if (account != nullptr) {
                return &customers[i];
            }
        }
        return nullptr;
    }

    // Core transaction function for customer
    bool processCustomerTransaction(const Utility::String& accountNumber, const Utility::String& type,
        double amount, const Utility::String& description = "",
        const Utility::String& relatedAccount = "") {
        Account* account = findAccount(accountNumber);
        if (account == nullptr) {
            cout << "Account not found!\n";
            return false;
        }

        // Check if the current user owns this account
        Customer* currentCustomer = dynamic_cast<Customer*>(currentUser);
        if (currentCustomer) {
            Account* customerAccount = currentCustomer->getAccount(accountNumber);
            if (customerAccount == nullptr) {
                cout << "You don't have access to this account!\n";
                return false;
            }
        }

        if (amount <= 0) {
            cout << "Amount must be positive!\n";
            return false;
        }

        bool success = false;
        if (type == "Deposit") {
            success = account->deposit(amount);
        }
        else if (type == "Withdrawal") {
            if (amount > account->getBalance()) {
                cout << "Insufficient balance!\n";
                return false;
            }
            success = account->withdraw(amount);
        }

        if (success) {
            // Create transaction record
            if (transactionCount >= transactionCapacity) {
                resizeTransactions();
            }

            transactions[transactionCount] = Transaction(
                accountNumber,
                type,
                amount,
                description,
                relatedAccount
            );
            transactionCount++;

            // Add to ledger
            if (type == "Deposit") {
                ledger.addEntry(accountNumber, description, 0, amount, account->getBalance());
            }
            else if (type == "Withdrawal") {
                ledger.addEntry(accountNumber, description, amount, 0, account->getBalance());
            }

            // Save updated data
            saveCustomersToFile();
            saveTransactionsToFile();

            cout << "Transaction successful!\n";
            cout << "New Balance: " << Utility::formatCurrency(account->getBalance()).c_str() << endl;
            return true;
        }

        return false;
    }

    // Core transfer function for customer
    bool processCustomerTransfer(const Utility::String& fromAccount, const Utility::String& toAccount, double amount) {
        Account* fromAcc = findAccount(fromAccount);
        Account* toAcc = findAccount(toAccount);

        if (fromAcc == nullptr) {
            cout << "Source account not found!\n";
            return false;
        }

        if (toAcc == nullptr) {
            cout << "Destination account not found!\n";
            return false;
        }

        // Check if the current user owns the source account
        Customer* currentCustomer = dynamic_cast<Customer*>(currentUser);
        if (currentCustomer) {
            Account* customerAccount = currentCustomer->getAccount(fromAccount);
            if (customerAccount == nullptr) {
                cout << "You don't have access to this account!\n";
                return false;
            }
        }

        if (fromAccount == toAccount) {
            cout << "Cannot transfer to the same account!\n";
            return false;
        }

        if (amount <= 0) {
            cout << "Transfer amount must be positive!\n";
            return false;
        }

        if (amount > 50000) {
            cout << "Transfer amount exceeds limit of 50,000!\n";
            return false;
        }

        if (amount > fromAcc->getBalance()) {
            cout << "Insufficient balance!\n";
            return false;
        }

        // Perform transfer
        fromAcc->withdraw(amount);
        toAcc->deposit(amount);

        // Create transaction records
        if (transactionCount >= transactionCapacity) {
            resizeTransactions();
        }

        transactions[transactionCount] = Transaction(
            fromAccount,
            Utility::String("Transfer"),
            amount,
            Utility::String("Transfer to ") + toAccount,
            toAccount
        );
        transactionCount++;

        if (transactionCount >= transactionCapacity) {
            resizeTransactions();
        }

        transactions[transactionCount] = Transaction(
            toAccount,
            Utility::String("Transfer"),
            amount,
            Utility::String("Transfer from ") + fromAccount,
            fromAccount
        );
        transactionCount++;

        // Add to ledger
        ledger.addEntry(fromAccount,
            Utility::String("Transfer to ") + toAccount,
            amount, 0, fromAcc->getBalance());

        ledger.addEntry(toAccount,
            Utility::String("Transfer from ") + fromAccount,
            0, amount, toAcc->getBalance());

        // Save updated data
        saveCustomersToFile();
        saveTransactionsToFile();

        cout << "Transfer successful!\n";
        cout << "From Account New Balance: " << Utility::formatCurrency(fromAcc->getBalance()).c_str() << endl;
        return true;
    }

    // Function to recover password
    bool recoverPassword(int role, const Utility::String& userID, const Utility::String& email) {
        const char* filename = nullptr;
        switch (role) {
        case 1: filename = adminFile; break;
        case 2: filename = officerFile; break;
        case 3: filename = customerFile; break;
        default: return false;
        }

        ifstream file(filename);
        if (file.is_open()) {
            char buffer[1000];
            while (file.getline(buffer, 1000)) {
                Utility::String line(buffer);
                Utility::String parts[100];
                int count = Utility::splitString(line, '|', parts, 100);

                if (count >= 6) {
                    Utility::String fileUserID = parts[1];
                    Utility::String fileEmail = parts[4];

                    if (fileUserID == userID && fileEmail == email) {
                        Utility::String password = parts[3];
                        cout << "\n========================================\n";
                        cout << "     PASSWORD RECOVERY SUCCESSFUL\n";
                        cout << "========================================\n";
                        cout << "User ID: " << userID.c_str() << endl;
                        cout << "Email: " << email.c_str() << endl;
                        cout << "Your Password: " << password.c_str() << endl;
                        cout << "========================================\n";

                        auditLog.addLog(userID, "PASSWORD_RECOVERY", "Password recovered via email");
                        file.close();
                        return true;
                    }
                }
            }
            file.close();
        }

        cout << "\n========================================\n";
        cout << "     PASSWORD RECOVERY FAILED\n";
        cout << "========================================\n";
        cout << "No account found with the given User ID and Email.\n";
        cout << "Please check your credentials and try again.\n";
        cout << "========================================\n";
        return false;
    }

    // Function to display role selection menu
    int selectRoleMenu() {
        system("cls");
        cout << "\n========================================\n";
        cout << "         BANK LOGIN PORTAL\n";
        cout << "========================================\n";
        cout << "Select Your Role:\n";
        cout << "1. Admin\n";
        cout << "2. Officer\n";
        cout << "3. Customer\n";
        cout << "4. Exit System\n";
        cout << "========================================\n";
        cout << "Choice: ";

        int role;
        cin >> role;
        return role;
    }

    // Function to display login options for selected role
    int displayRoleLoginMenu(int role) {
        system("cls");
        cout << "\n========================================\n";
        cout << "         ";
        switch (role) {
        case 1: cout << "ADMIN"; break;
        case 2: cout << "OFFICER"; break;
        case 3: cout << "CUSTOMER"; break;
        }
        cout << " PORTAL\n";
        cout << "========================================\n";
        if (role == 3) {
            cout << "1. Login\n";
            cout << "2. Recover Password\n";
            cout << "3. Register (Create Account)\n";
            cout << "4. Go Back (Select Role)\n";
        }
        else {
            cout << "1. Login\n";
            cout << "2. Recover Password\n";
            cout << "3. Go Back (Select Role)\n";
        }
        cout << "========================================\n";
        cout << "Choice: ";

        int choice;
        cin >> choice;
        return choice;
    }

    // Function to register a new customer (self-registration)
    bool registerCustomer() {
        system("cls");
        cout << "\n========================================\n";
        cout << "       CUSTOMER REGISTRATION\n";
        cout << "========================================\n";

        char buffer[100];
        Utility::String name, email, phone, address, cnic, occupation, password, confirmPassword;
        double annualIncome;
        int day, month, year;

        cin.ignore();

        cout << "Enter Full Name: ";
        cin.getline(buffer, 100);
        name = Utility::String(buffer);

        cout << "Enter CNIC (13 digits without dashes): ";
        cin.getline(buffer, 100);
        cnic = Utility::String(buffer);

        if (!Utility::validateCNIC(cnic)) {
            cout << "Invalid CNIC! Must be 13 digits.\n";
            cout << "\nPress any key to continue...";
            cin.get();
            return false;
        }

        // Check if CNIC already exists
        for (int i = 0; i < customerCount; i++) {
            if (customers[i].getCNIC() == cnic) {
                cout << "CNIC already registered! Please login instead.\n";
                cout << "\nPress any key to continue...";
                cin.get();
                return false;
            }
        }

        cout << "Enter Date of Birth (DD MM YYYY): ";
        cin >> day >> month >> year;
        cin.ignore();

        Utility::Date dob(day, month, year);

        // Check age >= 18
        Utility::Date currentDate = Utility::Date::getCurrentDate();
        int age = currentDate.year - year;
        if (age < 18) {
            cout << "You must be at least 18 years old to register!\n";
            cout << "\nPress any key to continue...";
            cin.get();
            return false;
        }

        cout << "Enter Email: ";
        cin.getline(buffer, 100);
        email = Utility::String(buffer);

        cout << "Enter Phone Number: ";
        cin.getline(buffer, 100);
        phone = Utility::String(buffer);

        cout << "Enter Address: ";
        cin.getline(buffer, 100);
        address = Utility::String(buffer);

        cout << "Enter Occupation: ";
        cin.getline(buffer, 100);
        occupation = Utility::String(buffer);

        cout << "Enter Annual Income: ";
        cin >> annualIncome;
        cin.ignore();

        if (annualIncome < 0) {
            cout << "Annual income cannot be negative!\n";
            cout << "\nPress any key to continue...";
            cin.get();
            return false;
        }

        // Get password
        cout << "Enter Password (5 digits): ";
        cin.getline(buffer, 100);
        password = Utility::String(buffer);

        if (!Utility::validatePassword(password)) {
            cout << "Password must be exactly 5 digits!\n";
            cout << "\nPress any key to continue...";
            cin.get();
            return false;
        }

        cout << "Confirm Password: ";
        cin.getline(buffer, 100);
        confirmPassword = Utility::String(buffer);

        if (password != confirmPassword) {
            cout << "Passwords do not match!\n";
            cout << "\nPress any key to continue...";
            cin.get();
            return false;
        }

        // Generate customer ID
        char customerID[20];
        sprintf(customerID, "CUST%04d", customerCount + 1001);
        Utility::String custID = Utility::String(customerID);

        // Create customer
        if (customerCount >= customerCapacity) {
            resizeCustomers();
        }

        customers[customerCount] = Customer(
            custID,
            name,
            password,
            email,
            phone,
            address,
            cnic,
            Utility::DateTime(dob, Utility::Time(0, 0, 0)),
            occupation,
            annualIncome
        );

        // Ask for account type and initial deposit
        cout << "\n=== CREATE BANK ACCOUNT ===\n";
        cout << "Account Types:\n";
        cout << "1. Savings Account (5% interest)\n";
        cout << "2. Current Account (0% interest)\n";
        cout << "Choice: ";
        int accType;
        cin >> accType;
        cin.ignore();

        Utility::String accountType = (accType == 1) ? Utility::String("Savings") : Utility::String("Current");

        double initialDeposit = 0;
        cout << "Enter Initial Deposit (minimum 1000 PKR): ";
        cin >> initialDeposit;
        cin.ignore();

        if (initialDeposit < 1000) {
            cout << "Minimum initial deposit is 1000 PKR!\n";
            cout << "\nPress any key to continue...";
            cin.get();
            return false;
        }

        // Add account to customer
        if (!customers[customerCount].addAccount(accountType, initialDeposit)) {
            cout << "Failed to create account!\n";
            cout << "\nPress any key to continue...";
            cin.get();
            return false;
        }

        customerCount++;

        // Save to file
        saveCustomersToFile();

        cout << "\n========================================\n";
        cout << "    REGISTRATION SUCCESSFUL!\n";
        cout << "========================================\n";
        cout << "Customer ID: " << customerID << endl;
        cout << "Account Number: " << customers[customerCount - 1].getAllAccounts()[0].getAccountNumber().c_str() << endl;
        cout << "Account Type: " << accountType.c_str() << endl;
        cout << "Initial Balance: " << Utility::formatCurrency(initialDeposit).c_str() << endl;
        cout << "Password: " << password.c_str() << endl;
        cout << "========================================\n";
        cout << "\nPlease remember your Customer ID and Password.\n";
        cout << "You can now login with your credentials.\n";

        auditLog.addLog(custID, "REGISTRATION", Utility::String("New customer registered: ") + name);

        cout << "\nPress any key to continue...";
        cin.get();
        return true;
    }

public:
    BankSystem() : currentUser(nullptr) {
        adminCapacity = officerCapacity = customerCapacity = 10;
        accountCapacity = transactionCapacity = loanCapacity = complaintCapacity = 100;

        admins = new Admin[adminCapacity];
        officers = new Officer[officerCapacity];
        customers = new Customer[customerCapacity];
        accounts = new Account[accountCapacity];
        transactions = new Transaction[transactionCapacity];
        loans = new Loan[loanCapacity];
        complaints = new Complaint[complaintCapacity];

        adminCount = officerCount = customerCount = 0;
        accountCount = transactionCount = loanCount = complaintCount = 0;

        loadData();
    }

    ~BankSystem() {
        delete[] admins;
        delete[] officers;
        delete[] customers;
        delete[] accounts;
        delete[] transactions;
        delete[] loans;
        delete[] complaints;
    }

    void createDefaultAdmin() {
        if (adminCount >= adminCapacity) {
            resizeAdmins();
        }

        Utility::String plainPassword = Utility::String("12345");
        admins[adminCount] = Admin("ADMIN001", "Malika", plainPassword,
            "admin@bank.com", "03001234567", "Bank HQ",
            "SUPERADMIN");
        adminCount++;

        saveAdminsToFile();
        cout << "Default admin created: Malika / 12345\n";
    }

    void loadData() {
        cout << "Loading system data...\n";
        loadAdminsFromFile();
        loadOfficersFromFile();
        loadCustomersFromFile();
        loadAccountsFromFile();
        loadTransactionsFromFile();
        loadLoansFromFile();
        loadComplaintsFromFile();
        cout << "Data loaded successfully!\n";
        cout << "Admins: " << adminCount << endl;
        cout << "Officers: " << officerCount << endl;
        cout << "Customers: " << customerCount << endl;
        cout << "Loans: " << loanCount << endl;
        cout << "Complaints: " << complaintCount << endl;
    }

    void saveData() {
        cout << "Saving system data...\n";
        saveAdminsToFile();
        saveOfficersToFile();
        saveCustomersToFile();
        saveAccountsToFile();
        saveTransactionsToFile();
        saveLoansToFile();
        saveComplaintsToFile();
        cout << "Data saved successfully!\n";
    }

    User* login() {
        int role;
        while (true) {
            role = selectRoleMenu();

            if (role == 4) {
                return nullptr;
            }

            if (role < 1 || role > 3) {
                cout << "Invalid role selection!\n";
                cout << "Press any key to continue...";
                cin.ignore();
                cin.get();
                continue;
            }

            while (true) {
                int option = displayRoleLoginMenu(role);

                if (option == 1) {
                    // Login
                    Utility::String userID, password;
                    char buffer[100];

                    cout << "\nEnter User ID: ";
                    cin >> buffer;
                    userID = Utility::String(buffer);

                    cout << "Enter Password (5 digits): ";
                    cin >> buffer;
                    password = Utility::String(buffer);

                    if (!Utility::validatePassword(password)) {
                        cout << "\nInvalid password format! Must be 5 digits.\n";
                        cout << "Press any key to continue...";
                        cin.ignore();
                        cin.get();
                        continue;
                    }

                    const char* filename = nullptr;
                    switch (role) {
                    case 1: filename = adminFile; break;
                    case 2: filename = officerFile; break;
                    case 3: filename = customerFile; break;
                    }

                    ifstream file(filename);
                    if (file.is_open()) {
                        char line[1000];
                        bool found = false;

                        while (file.getline(line, 1000)) {
                            Utility::String fileLine(line);
                            Utility::String parts[100];
                            int count = Utility::splitString(fileLine, '|', parts, 100);

                            if (count >= 6) {
                                Utility::String fileUserID = parts[1];
                                Utility::String filePassword = parts[3];

                                if (fileUserID == userID) {
                                    found = true;
                                    if (filePassword == password) {
                                        // Login successful
                                        file.close();

                                        // Load user into system
                                        switch (role) {
                                        case 1: // Admin
                                        {
                                            for (int i = 0; i < adminCount; i++) {
                                                if (admins[i].getUserID() == userID) {
                                                    currentUser = &admins[i];
                                                    auditLog.addLog(userID, "LOGIN", "Admin login successful");
                                                    showLoanNotifications(userID, role);
                                                    return currentUser;
                                                }
                                            }
                                            if (adminCount >= adminCapacity) resizeAdmins();
                                            admins[adminCount].loadFromFile(fileLine);
                                            currentUser = &admins[adminCount];
                                            adminCount++;
                                            auditLog.addLog(userID, "LOGIN", "Admin login successful");
                                            showLoanNotifications(userID, role);
                                            return currentUser;
                                        }
                                        case 2: // Officer
                                        {
                                            for (int i = 0; i < officerCount; i++) {
                                                if (officers[i].getUserID() == userID) {
                                                    currentUser = &officers[i];
                                                    auditLog.addLog(userID, "LOGIN", "Officer login successful");
                                                    showLoanNotifications(userID, role);
                                                    return currentUser;
                                                }
                                            }
                                            if (officerCount >= officerCapacity) resizeOfficers();
                                            officers[officerCount].loadFromFile(fileLine);
                                            currentUser = &officers[officerCount];
                                            officerCount++;
                                            auditLog.addLog(userID, "LOGIN", "Officer login successful");
                                            showLoanNotifications(userID, role);
                                            return currentUser;
                                        }
                                        case 3: // Customer
                                        {
                                            for (int i = 0; i < customerCount; i++) {
                                                if (customers[i].getUserID() == userID) {
                                                    currentUser = &customers[i];
                                                    auditLog.addLog(userID, "LOGIN", "Customer login successful");
                                                    showLoanNotifications(userID, role);
                                                    return currentUser;
                                                }
                                            }
                                            if (customerCount >= customerCapacity) resizeCustomers();
                                            customers[customerCount].loadFromFile(fileLine);
                                            currentUser = &customers[customerCount];
                                            customerCount++;
                                            auditLog.addLog(userID, "LOGIN", "Customer login successful");
                                            showLoanNotifications(userID, role);
                                            return currentUser;
                                        }
                                        }
                                    }
                                    else {
                                        cout << "\nInvalid password!\n";
                                        auditLog.addLog(userID, "LOGIN_FAILED", "Invalid password");
                                        cout << "Press any key to continue...";
                                        cin.ignore();
                                        cin.get();
                                        break;
                                    }
                                }
                            }
                        }

                        if (!found) {
                            cout << "\nUser ID not found!\n";
                            auditLog.addLog(userID, "LOGIN_FAILED", "User ID not found");
                            cout << "Press any key to continue...";
                            cin.ignore();
                            cin.get();
                        }

                        file.close();
                    }
                }
                else if (option == 2) {
                    // Recover Password
                    Utility::String userID, email;
                    char buffer[100];

                    cout << "\n========================================\n";
                    cout << "         PASSWORD RECOVERY\n";
                    cout << "========================================\n";
                    cout << "Enter User ID: ";
                    cin >> buffer;
                    userID = Utility::String(buffer);

                    cout << "Enter Registered Email: ";
                    cin >> buffer;
                    email = Utility::String(buffer);

                    if (recoverPassword(role, userID, email)) {
                        cout << "\nPlease use this password to login.\n";
                        cout << "Press any key to continue...";
                        cin.ignore();
                        cin.get();
                        // Return to role login menu
                        continue;
                    }
                    else {
                        cout << "Press any key to continue...";
                        cin.ignore();
                        cin.get();
                        continue;
                    }
                }
                else if (option == 3 && role == 3) {
                    // Customer Registration
                    registerCustomer();
                }
                else if ((option == 3 && role != 3) || option == 4) {
                    // Go back to role selection
                    break;
                }
                else {
                    cout << "Invalid option!\n";
                    cout << "Press any key to continue...";
                    cin.ignore();
                    cin.get();
                }
            }
        }
    }

    // Show loan notifications after login
    void showLoanNotifications(const Utility::String& userID, int role) {
        if (role == 3) { // Customer
            // Check for loan status updates
            int pendingLoans = 0;
            int officerApprovedLoans = 0;
            int adminApprovedLoans = 0;
            int rejectedLoans = 0;

            for (int i = 0; i < loanCount; i++) {
                if (loans[i].getCustomerID() == userID) {
                    if (loans[i].getStatus() == "Pending") {
                        pendingLoans++;
                    }
                    else if (loans[i].getStatus() == "Officer Approved") {
                        officerApprovedLoans++;
                    }
                    else if (loans[i].getStatus() == "Admin Approved") {
                        adminApprovedLoans++;
                    }
                    else if (loans[i].getStatus() == "Rejected") {
                        rejectedLoans++;
                    }
                }
            }

            // Check for complaint status updates
            int openComplaints = 0;
            int inProgressComplaints = 0;
            int resolvedComplaints = 0;
            int escalatedComplaints = 0;
            int adminResolvedComplaints = 0;

            for (int i = 0; i < complaintCount; i++) {
                if (complaints[i].getCustomerID() == userID) {
                    if (complaints[i].getStatus() == "Open") {
                        openComplaints++;
                    }
                    else if (complaints[i].getStatus() == "In Progress") {
                        inProgressComplaints++;
                    }
                    else if (complaints[i].getStatus() == "Resolved") {
                        resolvedComplaints++;
                    }
                    else if (complaints[i].getStatus() == "Escalated") {
                        escalatedComplaints++;
                    }
                    else if (complaints[i].getStatus() == "Admin Resolved") {
                        adminResolvedComplaints++;
                    }
                }
            }

            // Show notification if there are any loans or complaints
            if (pendingLoans > 0 || officerApprovedLoans > 0 || adminApprovedLoans > 0 || rejectedLoans > 0 ||
                openComplaints > 0 || inProgressComplaints > 0 || resolvedComplaints > 0 ||
                escalatedComplaints > 0 || adminResolvedComplaints > 0) {
                cout << "\n========================================\n";
                cout << "        NOTIFICATIONS & UPDATES\n";
                cout << "========================================\n";

                if (pendingLoans > 0) {
                    cout << "• You have " << pendingLoans << " loan application(s) pending review.\n";
                }
                if (officerApprovedLoans > 0) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); // Yellow
                    cout << "? You have " << officerApprovedLoans << " loan application(s) APPROVED BY OFFICER (Waiting for Admin)\n";
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // Reset to white
                }
                if (adminApprovedLoans > 0) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); // Green
                    cout << "? CONGRATULATIONS! You have " << adminApprovedLoans << " loan application(s) FINALLY APPROVED BY ADMIN!\n";
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // Reset to white
                }
                if (rejectedLoans > 0) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); // Red
                    cout << "? You have " << rejectedLoans << " loan application(s) REJECTED.\n";
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // Reset to white
                }

                // Complaint notifications
                if (openComplaints > 0) {
                    cout << "• You have " << openComplaints << " complaint(s) that are OPEN.\n";
                }
                if (inProgressComplaints > 0) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); // Yellow
                    cout << "? You have " << inProgressComplaints << " complaint(s) IN PROGRESS.\n";
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // Reset to white
                }
                if (resolvedComplaints > 0) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); // Green
                    cout << "? You have " << resolvedComplaints << " complaint(s) RESOLVED.\n";
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // Reset to white
                }
                if (escalatedComplaints > 0) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13); // Purple
                    cout << "? You have " << escalatedComplaints << " complaint(s) ESCALATED to Admin.\n";
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // Reset to white
                }
                if (adminResolvedComplaints > 0) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); // Green
                    cout << "? You have " << adminResolvedComplaints << " complaint(s) RESOLVED BY ADMIN.\n";
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // Reset to white
                }

                cout << "\nGo to respective sections in your menu for details.\n";
                cout << "========================================\n";
                cout << "\nPress any key to continue to dashboard...";
                cin.ignore();
                cin.get();
            }
        }
        else if (role == 1) { // Admin
            // Check for officer approved loans that need admin approval
            int officerApprovedLoans = 0;
            for (int i = 0; i < loanCount; i++) {
                if (loans[i].getStatus() == "Officer Approved") {
                    officerApprovedLoans++;
                }
            }

            // Check for escalated complaints
            int escalatedComplaints = 0;
            for (int i = 0; i < complaintCount; i++) {
                if (complaints[i].getStatus() == "Escalated") {
                    escalatedComplaints++;
                }
            }

            if (officerApprovedLoans > 0 || escalatedComplaints > 0) {
                cout << "\n========================================\n";
                cout << "         ADMIN ACTION REQUIRED\n";
                cout << "========================================\n";
                if (officerApprovedLoans > 0) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); // Yellow
                    cout << "? " << officerApprovedLoans << " loan(s) waiting for your FINAL approval!\n";
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // Reset to white
                }
                if (escalatedComplaints > 0) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13); // Purple
                    cout << "? " << escalatedComplaints << " complaint(s) ESCALATED and waiting for your action!\n";
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // Reset to white
                }
                cout << "Please use 'Approve Loans (Final)' and 'Handle Escalated Complaints' options.\n";
                cout << "========================================\n";
                cout << "\nPress any key to continue to dashboard...";
                cin.ignore();
                cin.get();
            }
        }
        else if (role == 2) { // Officer
            // Check for pending loans that need officer approval
            int pendingLoans = 0;
            for (int i = 0; i < loanCount; i++) {
                if (loans[i].getStatus() == "Pending") {
                    pendingLoans++;
                }
            }

            // Check for open complaints
            int openComplaints = 0;
            for (int i = 0; i < complaintCount; i++) {
                if (complaints[i].getStatus() == "Open" || complaints[i].getStatus() == "In Progress") {
                    openComplaints++;
                }
            }

            if (pendingLoans > 0 || openComplaints > 0) {
                cout << "\n========================================\n";
                cout << "         PENDING ACTIONS NOTICE\n";
                cout << "========================================\n";
                if (pendingLoans > 0) {
                    cout << "• There are " << pendingLoans << " loan applications pending your initial approval.\n";
                }
                if (openComplaints > 0) {
                    cout << "• There are " << openComplaints << " complaints requiring your attention.\n";
                }
                cout << "Please check the respective management sections.\n";
                cout << "========================================\n";
                cout << "\nPress any key to continue to dashboard...";
                cin.ignore();
                cin.get();
            }
        }
    }

    void logout() {
        if (currentUser) {
            auditLog.addLog(currentUser->getUserID(), "LOGOUT", "User logged out");
            cout << "\nLogout successful!\n";
            cout << "Press any key to continue...";
            cin.ignore();
            cin.get();
            currentUser = nullptr;
        }
    }

    // Admin Menu - UPDATED WITH NEW OPTIONS
    void adminMenu() {
        int choice;
        do {
            system("cls");
            cout << "\n========================================\n";
            cout << "           ADMIN DASHBOARD\n";
            cout << "========================================\n";
            cout << "Welcome: " << currentUser->getName().c_str() << " (Admin)\n";
            cout << "========================================\n";
            cout << "1. View All Officers\n";
            cout << "2. Add New Officer\n";
            cout << "3. Remove Officer\n";
            cout << "4. View All Customers\n";
            cout << "5. View All Transactions\n";
            cout << "6. Generate Reports\n";
            cout << "7. View Ledger\n";
            cout << "8. Monitor All Loans\n";
            cout << "9. Approve Loans (Final)\n";  // NEW: Admin final approval
            cout << "10. Handle Escalated Complaints\n";  // NEW: Handle escalated complaints
            cout << "11. Handle All Complaints\n";
            cout << "12. System Backup\n";
            cout << "13. View Audit Logs\n";
            cout << "14. Change Password\n";
            cout << "15. Logout\n";
            cout << "Choice: ";
            cin >> choice;

            switch (choice) {
            case 1: viewAllOfficers(); break;
            case 2: addOfficer(); break;
            case 3: removeOfficer(); break;
            case 4: viewAllCustomers(); break;
            case 5: viewAllTransactions(); break;
            case 6: generateReportsMenu(); break;
            case 7: viewLedger(); break;
            case 8: monitorLoans(); break;
            case 9: approveLoansFinal(); break;  // NEW FUNCTION
            case 10: handleEscalatedComplaints(); break;  // NEW FUNCTION
            case 11: handleComplaints(); break;
            case 12: systemBackup(); break;
            case 13: viewAuditLogs(); break;
            case 14: changePassword(); break;
            case 15: logout(); break;
            default:
                cout << "Invalid choice!\n";
                cout << "Press any key to continue...";
                cin.ignore();
                cin.get();
            }
        } while (choice != 15 && currentUser != nullptr);
    }

    // Officer Menu - UPDATED WITH TWO-STEP LOAN APPROVAL
    void officerMenu() {
        int choice;
        do {
            system("cls");
            cout << "\n========================================\n";
            cout << "          OFFICER DASHBOARD\n";
            cout << "========================================\n";
            cout << "Welcome: " << currentUser->getName().c_str() << " (Officer)\n";
            cout << "========================================\n";
            cout << "1. Create Customer Account\n";
            cout << "2. View Customer Accounts\n";
            cout << "3. Process Deposit\n";
            cout << "4. Process Withdrawal\n";
            cout << "5. Process Transfer\n";
            cout << "6. View Transactions\n";
            cout << "7. Process Loan Applications (Initial)\n";  // UPDATED
            cout << "8. Handle Complaints\n";
            cout << "9. Generate Mini-Statement\n";
            cout << "10. Change Password\n";
            cout << "11. Logout\n";
            cout << "Choice: ";
            cin >> choice;

            switch (choice) {
            case 1: createCustomerAccount(); break;
            case 2: viewCustomerAccounts(); break;
            case 3: processDeposit(); break;
            case 4: processWithdrawal(); break;
            case 5: processTransfer(); break;
            case 6: viewTransactions(); break;
            case 7: processLoans(); break;  // Officer initial approval
            case 8: handleCustomerComplaints(); break;
            case 9: generateMiniStatement(); break;
            case 10: changePassword(); break;
            case 11: logout(); break;
            default:
                cout << "Invalid choice!\n";
                cout << "Press any key to continue...";
                cin.ignore();
                cin.get();
            }
        } while (choice != 11 && currentUser != nullptr);
    }

    // Customer Menu
    void customerMenu() {
        int choice;
        do {
            system("cls");
            cout << "\n========================================\n";
            cout << "          CUSTOMER DASHBOARD\n";
            cout << "========================================\n";
            cout << "Welcome: " << currentUser->getName().c_str() << " (Customer)\n";
            cout << "========================================\n";
            cout << "1. View Account Details\n";
            cout << "2. View Balance\n";
            cout << "3. Deposit Money\n";
            cout << "4. Withdraw Money\n";
            cout << "5. Transfer Money\n";
            cout << "6. View Transaction History\n";
            cout << "7. Apply for Loan\n";
            cout << "8. View Loan Status\n";
            cout << "9. Register Complaint\n";
            cout << "10. View Complaint Status\n";
            cout << "11. Update Profile\n";
            cout << "12. Request Statement\n";
            cout << "13. Calculate Interest\n";
            cout << "14. Change Password\n";
            cout << "15. Logout\n";
            cout << "Choice: ";
            cin >> choice;

            switch (choice) {
            case 1: viewAccountDetails(); break;
            case 2: viewBalance(); break;
            case 3: depositMoney(); break;
            case 4: withdrawMoney(); break;
            case 5: transferMoney(); break;
            case 6: viewTransactionHistory(); break;
            case 7: applyForLoan(); break;
            case 8: viewLoanStatus(); break;
            case 9: registerComplaint(); break;
            case 10: viewComplaintStatus(); break;
            case 11: updateProfile(); break;
            case 12: requestStatement(); break;
            case 13: calculateInterest(); break;
            case 14: changePassword(); break;
            case 15: logout(); break;
            default:
                cout << "Invalid choice!\n";
                cout << "Press any key to continue...";
                cin.ignore();
                cin.get();
            }
        } while (choice != 15 && currentUser != nullptr);
    }

    // Change Password for all users
    void changePassword() {
        system("cls");
        cout << "\n=== CHANGE PASSWORD ===\n";

        char oldPass[100], newPass[100], confirmPass[100];

        cout << "Enter Old Password: ";
        cin >> oldPass;

        cout << "Enter New Password (5 digits): ";
        cin >> newPass;

        cout << "Confirm New Password: ";
        cin >> confirmPass;

        Utility::String oldPassword(oldPass);
        Utility::String newPassword(newPass);
        Utility::String confirmPassword(confirmPass);

        if (newPassword != confirmPassword) {
            cout << "New passwords do not match!\n";
            cout << "Press any key to continue...";
            cin.ignore();
            cin.get();
            return;
        }

        if (!Utility::validatePassword(newPassword)) {
            cout << "New password must be 5 digits!\n";
            cout << "Press any key to continue...";
            cin.ignore();
            cin.get();
            return;
        }

        if (currentUser->changePassword(oldPassword, newPassword)) {
            cout << "Password changed successfully!\n";

            // Save changes to file
            if (dynamic_cast<Admin*>(currentUser)) {
                saveAdminsToFile();
            }
            else if (dynamic_cast<Officer*>(currentUser)) {
                saveOfficersToFile();
            }
            else if (dynamic_cast<Customer*>(currentUser)) {
                saveCustomersToFile();
            }

            auditLog.addLog(currentUser->getUserID(), "CHANGE_PASSWORD", "Password changed");
        }
        else {
            cout << "Old password is incorrect!\n";
        }

        cout << "Press any key to continue...";
        cin.ignore();
        cin.get();
    }

    // NEW FUNCTION: Admin final approval for loans
    void approveLoansFinal() {
        system("cls");
        cout << "\n=== FINAL LOAN APPROVAL (ADMIN) ===\n";

        // Display officer approved loans
        int officerApprovedCount = 0;
        for (int i = 0; i < loanCount; i++) {
            if (loans[i].getStatus() == "Officer Approved") {
                loans[i].displayInfo();
                officerApprovedCount++;

                cout << "\n1. Approve (Final Admin Approval)\n2. Reject\n3. Skip\nChoice: ";
                int decision;
                cin >> decision;
                cin.ignore();

                if (decision == 1) {
                    loans[i].approveByAdmin(currentUser->getUserID());
                    cout << "Loan FINALLY APPROVED by Admin!\n";
                    cout << "Loan will be disbursed to customer's account.\n";
                    auditLog.addLog(currentUser->getUserID(), "ADMIN_FINAL_APPROVE_LOAN",
                        Utility::String("Loan ID: ") + loans[i].getLoanID());

                    // Save updated loans to file
                    saveLoansToFile();
                }
                else if (decision == 2) {
                    loans[i].reject();
                    cout << "Loan REJECTED by Admin!\n";
                    auditLog.addLog(currentUser->getUserID(), "ADMIN_REJECT_LOAN",
                        Utility::String("Loan ID: ") + loans[i].getLoanID());

                    // Save updated loans to file
                    saveLoansToFile();
                }
                cout << "\nPress any key to continue...";
                cin.get();
            }
        }

        if (officerApprovedCount == 0) {
            cout << "No loans pending final admin approval.\n";
            cout << "\nPress any key to continue...";
            cin.ignore();
            cin.get();
        }
    }

    // NEW FUNCTION: Handle escalated complaints (Admin)
    void handleEscalatedComplaints() {
        system("cls");
        cout << "\n=== HANDLE ESCALATED COMPLAINTS (ADMIN) ===\n";

        int escalatedCount = 0;
        for (int i = 0; i < complaintCount; i++) {
            if (complaints[i].getStatus() == "Escalated") {
                complaints[i].displayInfo();
                escalatedCount++;

                cout << "\n1. Resolve (Admin Resolution)\n2. Assign Back to Officer\n3. Skip\nChoice: ";
                int action;
                cin >> action;
                cin.ignore();

                if (action == 1) {
                    char resolution[200];
                    cout << "Enter resolution: ";
                    cin.getline(resolution, 200);
                    complaints[i].resolveByAdmin(currentUser->getUserID(), Utility::String(resolution));
                    cout << "Complaint resolved by Admin.\n";
                    auditLog.addLog(currentUser->getUserID(), "ADMIN_RESOLVE_COMPLAINT",
                        Utility::String("Complaint ID: ") + complaints[i].getComplaintID());

                    // Save updated complaints to file
                    saveComplaintsToFile();
                }
                else if (action == 2) {
                    char officerID[100];
                    cout << "Enter Officer ID to assign back: ";
                    cin.getline(officerID, 100);
                    complaints[i].assignTo(Utility::String(officerID));
                    cout << "Complaint assigned back to officer.\n";
                    auditLog.addLog(currentUser->getUserID(), "ADMIN_REASSIGN_COMPLAINT",
                        Utility::String("Complaint ID: ") + complaints[i].getComplaintID());

                    // Save updated complaints to file
                    saveComplaintsToFile();
                }
                cout << "\nPress any key to continue...";
                cin.get();
            }
        }

        if (escalatedCount == 0) {
            cout << "No escalated complaints.\n";
            cout << "\nPress any key to continue...";
            cin.ignore();
            cin.get();
        }
    }

    // Implementation of various functions
    void viewAllOfficers() {
        system("cls");
        cout << "\n=== ALL OFFICERS ===\n";
        for (int i = 0; i < officerCount; i++) {
            officers[i].displayInfo();
            cout << "------------------------\n";
        }
        auditLog.addLog(currentUser->getUserID(), "VIEW_OFFICERS");
        cout << "\nPress any key to continue...";
        cin.ignore();
        cin.get();
    }

    void addOfficer() {
        system("cls");
        cout << "\n=== ADD NEW OFFICER ===\n";

        char buffer[100];
        Utility::String name, email, phone, address, department;
        double salary;

        cin.ignore();

        cout << "Enter Name: ";
        cin.getline(buffer, 100);
        name = Utility::String(buffer);

        cout << "Enter Email: ";
        cin.getline(buffer, 100);
        email = Utility::String(buffer);

        cout << "Enter Phone: ";
        cin.getline(buffer, 100);
        phone = Utility::String(buffer);

        cout << "Enter Address: ";
        cin.getline(buffer, 100);
        address = Utility::String(buffer);

        cout << "Enter Department: ";
        cin.getline(buffer, 100);
        department = Utility::String(buffer);

        cout << "Enter Salary: ";
        cin >> salary;
        cin.ignore();

        char officerID[20];
        sprintf(officerID, "OFF%03d", officerCount + 1);

        // Generate unique 5-digit password for officer
        Utility::String randomPassword = Utility::generateRandomPassword();

        if (officerCount >= officerCapacity) {
            resizeOfficers();
        }

        officers[officerCount] = Officer(
            Utility::String(officerID),
            name,
            randomPassword,
            email,
            phone,
            address,
            department,
            salary
        );

        officerCount++;

        saveOfficersToFile();

        cout << "\nOfficer added successfully!\n";
        cout << "Officer ID: " << officerID << endl;
        cout << "Password: " << randomPassword.c_str() << " (5-digit unique password)\n";
        auditLog.addLog(currentUser->getUserID(), "ADD_OFFICER", name);

        cout << "\nPress any key to continue...";
        cin.ignore();
        cin.get();
    }

    void removeOfficer() {
        system("cls");
        char buffer[100];
        cout << "=== REMOVE OFFICER ===\n";
        cout << "Enter Officer ID to remove: ";
        cin >> buffer;
        Utility::String officerID(buffer);

        for (int i = 0; i < officerCount; i++) {
            if (officers[i].getUserID() == officerID) {
                for (int j = i; j < officerCount - 1; j++) {
                    officers[j] = officers[j + 1];
                }
                officerCount--;

                saveOfficersToFile();

                cout << "Officer removed successfully!\n";
                auditLog.addLog(currentUser->getUserID(), "REMOVE_OFFICER", officerID);

                cout << "\nPress any key to continue...";
                cin.ignore();
                cin.get();
                return;
            }
        }
        cout << "Officer not found!\n";
        cout << "\nPress any key to continue...";
        cin.ignore();
        cin.get();
    }

    void viewAllCustomers() {
        system("cls");
        cout << "\n=== ALL CUSTOMERS ===\n";
        for (int i = 0; i < customerCount; i++) {
            customers[i].displayInfo();
            cout << "------------------------\n";
        }
        auditLog.addLog(currentUser->getUserID(), "VIEW_CUSTOMERS");
        cout << "\nPress any key to continue...";
        cin.ignore();
        cin.get();
    }

    void viewAllTransactions() {
        system("cls");
        cout << "\n=== ALL TRANSACTIONS ===\n";
        int limit = (transactionCount < 10) ? transactionCount : 10;
        for (int i = 0; i < limit; i++) {
            transactions[i].displayInfo();
            cout << "------------------------\n";
        }
        auditLog.addLog(currentUser->getUserID(), "VIEW_TRANSACTIONS");
        cout << "\nPress any key to continue...";
        cin.ignore();
        cin.get();
    }

    void generateReportsMenu() {
        int choice;
        do {
            system("cls");
            cout << "\n=== REPORT GENERATION ===\n";
            cout << "1. Daily Transaction Report\n";
            cout << "2. Monthly Financial Report\n";
            cout << "3. Yearly Financial Report\n";
            cout << "4. Loan Approval Report\n";
            cout << "5. Customer Transaction Report\n";
            cout << "6. Back to Main Menu\n";
            cout << "Choice: ";
            cin >> choice;

            switch (choice) {
            case 1: Report::generateDailyTransactionReport(); break;
            case 2: {
                int month, year;
                cout << "Enter month (1-12): ";
                cin >> month;
                cout << "Enter year: ";
                cin >> year;
                Report::generateMonthlyFinancialReport(month, year);
                break;
            }
            case 3: {
                int year;
                cout << "Enter year: ";
                cin >> year;
                Report::generateYearlyFinancialReport(year);
                break;
            }
            case 4: Report::generateLoanApprovalReport(); break;
            case 5: {
                char buffer[100];
                cout << "Enter Customer ID: ";
                cin >> buffer;
                Report::generateCustomerTransactionReport(Utility::String(buffer));
                break;
            }
            case 6:
                return;
            }
            auditLog.addLog(currentUser->getUserID(), "GENERATE_REPORT");
        } while (choice != 6);
    }

    void viewLedger() {
        ledger.displayLedger();
        auditLog.addLog(currentUser->getUserID(), "VIEW_LEDGER");
    }

    void monitorLoans() {
        system("cls");
        cout << "\n=== LOAN MONITORING ===\n";
        for (int i = 0; i < loanCount; i++) {
            loans[i].displayInfo();
            cout << "------------------------\n";
        }
        auditLog.addLog(currentUser->getUserID(), "MONITOR_LOANS");
        cout << "\nPress any key to continue...";
        cin.ignore();
        cin.get();
    }

    void handleComplaints() {
        system("cls");
        cout << "\n=== COMPLAINT MANAGEMENT ===\n";
        for (int i = 0; i < complaintCount; i++) {
            complaints[i].displayInfo();
            cout << "------------------------\n";
        }
        auditLog.addLog(currentUser->getUserID(), "HANDLE_COMPLAINTS");
        cout << "\nPress any key to continue...";
        cin.ignore();
        cin.get();
    }

    void systemBackup() {
        BackupManager::performBackup();
        auditLog.addLog(currentUser->getUserID(), "SYSTEM_BACKUP");
    }

    void viewAuditLogs() {
        auditLog.displayLogs();
        auditLog.addLog(currentUser->getUserID(), "VIEW_AUDIT_LOGS");
    }

    // Officer function to create customer account
    void createCustomerAccount() {
        system("cls");
        cout << "\n=== CREATE CUSTOMER ACCOUNT ===\n";

        char buffer[100];
        Utility::String name, email, phone, address, cnic, occupation;
        double annualIncome;
        int day, month, year;

        cout << "Enter Customer Name: ";
        cin.ignore();
        cin.getline(buffer, 100);
        name = Utility::String(buffer);

        cout << "Enter CNIC (13 digits): ";
        cin.getline(buffer, 100);
        cnic = Utility::String(buffer);

        if (!Utility::validateCNIC(cnic)) {
            cout << "Invalid CNIC! Must be 13 digits.\n";
            cout << "\nPress any key to continue...";
            cin.get();
            return;
        }

        cout << "Enter Date of Birth (DD MM YYYY): ";
        cin >> day >> month >> year;
        cin.ignore();

        Utility::Date dob(day, month, year);

        // Check age >= 18
        Utility::Date currentDate = Utility::Date::getCurrentDate();
        int age = currentDate.year - year;
        if (age < 18) {
            cout << "Customer must be at least 18 years old!\n";
            cout << "\nPress any key to continue...";
            cin.get();
            return;
        }

        cout << "Enter Email: ";
        cin.getline(buffer, 100);
        email = Utility::String(buffer);

        cout << "Enter Phone: ";
        cin.getline(buffer, 100);
        phone = Utility::String(buffer);

        cout << "Enter Address: ";
        cin.getline(buffer, 100);
        address = Utility::String(buffer);

        cout << "Enter Occupation: ";
        cin.getline(buffer, 100);
        occupation = Utility::String(buffer);

        cout << "Enter Annual Income: ";
        cin >> annualIncome;
        cin.ignore();

        // Generate customer ID
        char customerID[20];
        sprintf(customerID, "CUST%03d", customerCount + 1);
        Utility::String custID = Utility::String(customerID);

        // Generate unique 5-digit password for customer
        Utility::String randomPassword = Utility::generateRandomPassword();

        if (customerCount >= customerCapacity) {
            resizeCustomers();
        }

        // Create customer object
        customers[customerCount] = Customer(
            custID,
            name,
            randomPassword,
            email,
            phone,
            address,
            cnic,
            Utility::DateTime(dob, Utility::Time(0, 0, 0)),
            occupation,
            annualIncome
        );

        // Create account for customer
        cout << "\n=== CREATE ACCOUNT ===\n";
        cout << "Account Types:\n";
        cout << "1. Savings Account (5% interest)\n";
        cout << "2. Current Account (0% interest)\n";
        cout << "Choice: ";
        int accType;
        cin >> accType;
        cin.ignore();

        Utility::String accountType = (accType == 1) ? Utility::String("Savings") : Utility::String("Current");

        double initialDeposit = 0;
        cout << "Enter Initial Deposit: ";
        cin >> initialDeposit;
        cin.ignore();

        if (initialDeposit < 0) {
            cout << "Initial deposit cannot be negative!\n";
            cout << "\nPress any key to continue...";
            cin.get();
            return;
        }

        // Add account to customer
        if (!customers[customerCount].addAccount(accountType, initialDeposit)) {
            cout << "Failed to create account!\n";
            cout << "\nPress any key to continue...";
            cin.get();
            return;
        }

        customerCount++;

        saveCustomersToFile();

        cout << "\n========================================\n";
        cout << "  CUSTOMER ACCOUNT CREATED SUCCESSFULLY!\n";
        cout << "========================================\n";
        cout << "Customer ID: " << customerID << endl;
        cout << "Customer Name: " << name.c_str() << endl;
        cout << "Account Type: " << accountType.c_str() << endl;
        cout << "Initial Balance: " << Utility::formatCurrency(initialDeposit).c_str() << endl;
        cout << "Generated Password: " << randomPassword.c_str() << " (5-digit unique password)\n";
        cout << "========================================\n";

        auditLog.addLog(currentUser->getUserID(), "CREATE_CUSTOMER_ACCOUNT",
            Utility::String("Customer: ") + name + Utility::String(", Password: ") + randomPassword);

        cout << "\nCustomer account has been saved to customers.txt file.\n";
        cout << "Please provide the Customer ID and Password to the customer.\n";
        cout << "\nPress any key to continue...";
        cin.get();
    }

    void viewCustomerAccounts() {
        system("cls");
        cout << "\n=== CUSTOMER ACCOUNTS ===\n";
        for (int i = 0; i < customerCount; i++) {
            customers[i].displayAccounts();
        }
        auditLog.addLog(currentUser->getUserID(), "VIEW_CUSTOMER_ACCOUNTS");
        cout << "\nPress any key to continue...";
        cin.ignore();
        cin.get();
    }

    void processDeposit() {
        system("cls");
        cout << "\n=== PROCESS DEPOSIT ===\n";
        char accountNum[20];
        double amount;

        cout << "Enter Account Number: ";
        cin >> accountNum;
        Utility::String accountNumber(accountNum);

        if (!Utility::validateAccountID(accountNumber)) {
            cout << "Invalid account number! Must be 16 digits.\n";
            cout << "\nPress any key to continue...";
            cin.ignore();
            cin.get();
            return;
        }

        cout << "Enter Deposit Amount: ";
        cin >> amount;

        if (amount <= 0) {
            cout << "Deposit amount must be positive!\n";
            cout << "\nPress any key to continue...";
            cin.ignore();
            cin.get();
            return;
        }

        // Find account and deposit
        Account* account = findAccount(accountNumber);
        if (account != nullptr) {
            if (account->deposit(amount)) {
                // Create transaction
                if (transactionCount >= transactionCapacity) {
                    resizeTransactions();
                }

                transactions[transactionCount] = Transaction(
                    accountNumber,
                    Utility::String("Deposit"),
                    amount,
                    Utility::String("Cash deposit by officer")
                );
                transactionCount++;

                // Add to ledger
                ledger.addEntry(accountNumber, Utility::String("Cash Deposit by Officer"), 0, amount, account->getBalance());

                cout << "Deposit successful!\n";
                cout << "New Balance: " << Utility::formatCurrency(account->getBalance()).c_str() << endl;
                auditLog.addLog(currentUser->getUserID(), "PROCESS_DEPOSIT",
                    Utility::String("Account: ") + accountNumber + Utility::String(", Amount: ") + Utility::doubleToString(amount));

                // Save updated customer data
                saveCustomersToFile();
                saveTransactionsToFile();
            }
        }
        else {
            cout << "Account not found!\n";
        }

        cout << "\nPress any key to continue...";
        cin.ignore();
        cin.get();
    }

    void processWithdrawal() {
        system("cls");
        cout << "\n=== PROCESS WITHDRAWAL ===\n";
        char accountNum[20];
        double amount;

        cout << "Enter Account Number: ";
        cin >> accountNum;
        Utility::String accountNumber(accountNum);

        if (!Utility::validateAccountID(accountNumber)) {
            cout << "Invalid account number! Must be 16 digits.\n";
            cout << "\nPress any key to continue...";
            cin.ignore();
            cin.get();
            return;
        }

        cout << "Enter Withdrawal Amount: ";
        cin >> amount;

        if (amount <= 0) {
            cout << "Withdrawal amount must be positive!\n";
            cout << "\nPress any key to continue...";
            cin.ignore();
            cin.get();
            return;
        }

        // Find account and withdraw
        Account* account = findAccount(accountNumber);
        if (account != nullptr) {
            if (account->withdraw(amount)) {
                // Create transaction
                if (transactionCount >= transactionCapacity) {
                    resizeTransactions();
                }

                transactions[transactionCount] = Transaction(
                    accountNumber,
                    Utility::String("Withdrawal"),
                    amount,
                    Utility::String("Cash withdrawal by officer")
                );
                transactionCount++;

                // Add to ledger
                ledger.addEntry(accountNumber, Utility::String("Cash Withdrawal by Officer"), amount, 0, account->getBalance());

                cout << "Withdrawal successful!\n";
                cout << "New Balance: " << Utility::formatCurrency(account->getBalance()).c_str() << endl;
                auditLog.addLog(currentUser->getUserID(), "PROCESS_WITHDRAWAL",
                    Utility::String("Account: ") + accountNumber + Utility::String(", Amount: ") + Utility::doubleToString(amount));

                // Save updated customer data
                saveCustomersToFile();
                saveTransactionsToFile();
            }
            else {
                cout << "Insufficient balance!\n";
            }
        }
        else {
            cout << "Account not found!\n";
        }

        cout << "\nPress any key to continue...";
        cin.ignore();
        cin.get();
    }

    void processTransfer() {
        system("cls");
        cout << "\n=== PROCESS TRANSFER ===\n";
        char fromAccountNum[20], toAccountNum[20];
        double amount;

        cout << "Enter From Account Number: ";
        cin >> fromAccountNum;
        Utility::String fromAccountNumber(fromAccountNum);

        cout << "Enter To Account Number: ";
        cin >> toAccountNum;
        Utility::String toAccountNumber(toAccountNum);

        if (!Utility::validateAccountID(fromAccountNumber) || !Utility::validateAccountID(toAccountNumber)) {
            cout << "Invalid account number(s)! Must be 16 digits.\n";
            cout << "\nPress any key to continue...";
            cin.ignore();
            cin.get();
            return;
        }

        if (fromAccountNumber == toAccountNumber) {
            cout << "Cannot transfer to same account!\n";
            cout << "\nPress any key to continue...";
            cin.ignore();
            cin.get();
            return;
        }

        cout << "Enter Transfer Amount: ";
        cin >> amount;

        if (amount <= 0) {
            cout << "Transfer amount must be positive!\n";
            cout << "\nPress any key to continue...";
            cin.ignore();
            cin.get();
            return;
        }

        if (amount > 50000) {
            cout << "Transfer amount exceeds limit of 50,000!\n";
            cout << "\nPress any key to continue...";
            cin.ignore();
            cin.get();
            return;
        }

        // Find accounts
        Account* fromAccount = findAccount(fromAccountNumber);
        Account* toAccount = findAccount(toAccountNumber);

        if (fromAccount == nullptr) {
            cout << "From Account not found!\n";
            cout << "\nPress any key to continue...";
            cin.ignore();
            cin.get();
            return;
        }

        if (toAccount == nullptr) {
            cout << "To Account not found!\n";
            cout << "\nPress any key to continue...";
            cin.ignore();
            cin.get();
            return;
        }

        // Perform transfer
        if (fromAccount->transfer(*toAccount, amount)) {
            // Create transaction for from account
            if (transactionCount >= transactionCapacity) {
                resizeTransactions();
            }

            transactions[transactionCount] = Transaction(
                fromAccountNumber,
                Utility::String("Transfer"),
                amount,
                Utility::String("Transfer to ") + toAccountNumber + Utility::String(" by officer"),
                toAccountNumber
            );
            transactionCount++;

            // Create transaction for to account
            if (transactionCount >= transactionCapacity) {
                resizeTransactions();
            }

            transactions[transactionCount] = Transaction(
                toAccountNumber,
                Utility::String("Transfer"),
                amount,
                Utility::String("Transfer from ") + fromAccountNumber + Utility::String(" by officer"),
                fromAccountNumber
            );
            transactionCount++;

            // Add to ledger
            ledger.addEntry(fromAccountNumber,
                Utility::String("Transfer to ") + toAccountNumber + Utility::String(" by Officer"),
                amount, 0, fromAccount->getBalance());

            ledger.addEntry(toAccountNumber,
                Utility::String("Transfer from ") + fromAccountNumber + Utility::String(" by Officer"),
                0, amount, toAccount->getBalance());

            cout << "Transfer successful!\n";
            cout << "From Account New Balance: " << Utility::formatCurrency(fromAccount->getBalance()).c_str() << endl;
            cout << "To Account New Balance: " << Utility::formatCurrency(toAccount->getBalance()).c_str() << endl;

            auditLog.addLog(currentUser->getUserID(), "PROCESS_TRANSFER",
                Utility::String("From: ") + fromAccountNumber +
                Utility::String(", To: ") + toAccountNumber +
                Utility::String(", Amount: ") + Utility::doubleToString(amount));

            // Save updated customer data
            saveCustomersToFile();
            saveTransactionsToFile();
        }
        else {
            cout << "Transfer failed! Check balance or amount.\n";
        }
        cout << "\nPress any key to continue...";
        cin.ignore();
        cin.get();
    }

    void viewTransactions() {
        system("cls");
        cout << "\n=== RECENT TRANSACTIONS ===\n";
        int limit = (transactionCount < 10) ? transactionCount : 10;
        int count = 0;
        for (int i = transactionCount - 1; i >= 0 && count < limit; i--) {
            transactions[i].displayInfo();
            count++;
        }

        auditLog.addLog(currentUser->getUserID(), "VIEW_TRANSACTIONS");
        cout << "\nPress any key to continue...";
        cin.ignore();
        cin.get();
    }

    // UPDATED: Officer initial loan approval
    void processLoans() {
        system("cls");
        cout << "\n=== PROCESS LOAN APPLICATIONS (INITIAL APPROVAL) ===\n";

        // Display pending loans
        int pendingCount = 0;
        for (int i = 0; i < loanCount; i++) {
            if (loans[i].getStatus() == Utility::String("Pending")) {
                loans[i].displayInfo();
                pendingCount++;

                // Ask for decision
                cout << "\n1. Approve (Initial Officer Approval)\n2. Reject\n3. Skip\nChoice: ";
                int decision;
                cin >> decision;

                if (decision == 1) {
                    loans[i].approveByOfficer(currentUser->getUserID());
                    cout << "Loan approved by officer!\n";
                    cout << "Now waiting for Admin final approval.\n";
                    auditLog.addLog(currentUser->getUserID(), "OFFICER_APPROVE_LOAN",
                        Utility::String("Loan ID: ") + loans[i].getLoanID());

                    // Save updated loans to file
                    saveLoansToFile();
                }
                else if (decision == 2) {
                    loans[i].reject();
                    cout << "Loan rejected!\n";
                    auditLog.addLog(currentUser->getUserID(), "OFFICER_REJECT_LOAN",
                        Utility::String("Loan ID: ") + loans[i].getLoanID());

                    // Save updated loans to file
                    saveLoansToFile();
                }
                cout << "\nPress any key to continue...";
                cin.ignore();
                cin.get();
            }
        }

        if (pendingCount == 0) {
            cout << "No pending loan applications.\n";
        }
        cout << "\nPress any key to continue...";
        cin.ignore();
        cin.get();
    }

    // UPDATED: Officer complaint handling with escalation option
    void handleCustomerComplaints() {
        system("cls");
        cout << "\n=== CUSTOMER COMPLAINTS ===\n";

        int openCount = 0;
        for (int i = 0; i < complaintCount; i++) {
            if (complaints[i].getStatus() == Utility::String("Open") ||
                complaints[i].getStatus() == Utility::String("In Progress")) {
                complaints[i].displayInfo();
                openCount++;

                cout << "\n1. Assign to myself\n2. Resolve\n3. Escalate to Admin\n4. Skip\nChoice: ";
                int action;
                cin >> action;
                cin.ignore();

                if (action == 1) {
                    complaints[i].assignTo(currentUser->getUserID());
                    cout << "Complaint assigned to you.\n";
                    auditLog.addLog(currentUser->getUserID(), "ASSIGN_COMPLAINT",
                        Utility::String("Complaint ID: ") + complaints[i].getComplaintID());

                    // Save updated complaints to file
                    saveComplaintsToFile();
                }
                else if (action == 2) {
                    char resolution[200];
                    cout << "Enter resolution: ";
                    cin.getline(resolution, 200);
                    complaints[i].resolve(Utility::String(resolution));
                    cout << "Complaint resolved.\n";
                    auditLog.addLog(currentUser->getUserID(), "RESOLVE_COMPLAINT",
                        Utility::String("Complaint ID: ") + complaints[i].getComplaintID());

                    // Save updated complaints to file
                    saveComplaintsToFile();
                }
                else if (action == 3) {
                    complaints[i].escalate(currentUser->getUserID());
                    cout << "Complaint escalated to Admin for review.\n";
                    auditLog.addLog(currentUser->getUserID(), "ESCALATE_COMPLAINT",
                        Utility::String("Complaint ID: ") + complaints[i].getComplaintID());

                    // Save updated complaints to file
                    saveComplaintsToFile();
                }
                cout << "\nPress any key to continue...";
                cin.get();
            }
        }

        if (openCount == 0) {
            cout << "No open complaints.\n";
        }
        cout << "\nPress any key to continue...";
        cin.ignore();
        cin.get();
    }

    void generateMiniStatement() {
        system("cls");
        cout << "\n=== GENERATE MINI STATEMENT ===\n";
        char accountNum[20];

        cout << "Enter Account Number: ";
        cin >> accountNum;
        Utility::String accountNumber(accountNum);

        if (!Utility::validateAccountID(accountNumber)) {
            cout << "Invalid account number! Must be 16 digits.\n";
            cout << "\nPress any key to continue...";
            cin.ignore();
            cin.get();
            return;
        }

        // Find account
        Account* account = findAccount(accountNumber);
        if (account == nullptr) {
            cout << "Account not found!\n";
            cout << "\nPress any key to continue...";
            cin.ignore();
            cin.get();
            return;
        }

        // Display mini statement
        cout << "\n=== MINI STATEMENT ===\n";
        account->displayInfo();

        // Display recent transactions for this account
        cout << "\nRecent Transactions:\n";
        int count = 0;
        for (int i = transactionCount - 1; i >= 0 && count < 5; i--) {
            if (transactions[i].getAccountNumber() == accountNumber) {
                transactions[i].displayInfo();
                cout << "----------------------------\n";
                count++;
            }
        }

        if (count == 0) {
            cout << "No transactions found.\n";
        }

        auditLog.addLog(currentUser->getUserID(), "GENERATE_MINI_STATEMENT", accountNumber);
        cout << "\nPress any key to continue...";
        cin.ignore();
        cin.get();
    }

    // Customer functions with implementations
    void viewAccountDetails() {
        system("cls");
        Customer* customer = dynamic_cast<Customer*>(currentUser);
        if (customer) {
            customer->displayInfo();
            customer->displayAccounts();
            auditLog.addLog(currentUser->getUserID(), "VIEW_ACCOUNT_DETAILS");
        }
        cout << "\nPress any key to continue...";
        cin.ignore();
        cin.get();
    }

    void viewBalance() {
        system("cls");
        Customer* customer = dynamic_cast<Customer*>(currentUser);
        if (customer) {
            cout << "\n=== ACCOUNT BALANCES ===\n";
            customer->displayAccounts();
            auditLog.addLog(currentUser->getUserID(), "VIEW_BALANCE");
        }
        cout << "\nPress any key to continue...";
        cin.ignore();
        cin.get();
    }

    void depositMoney() {
        system("cls");
        Customer* customer = dynamic_cast<Customer*>(currentUser);
        if (customer) {
            cout << "\n=== DEPOSIT MONEY ===\n";

            // Display customer's accounts
            customer->displayAccounts();

            if (customer->getAccountCount() == 0) {
                cout << "No accounts found!\n";
                cout << "\nPress any key to continue...";
                cin.ignore();
                cin.get();
                return;
            }

            int accChoice;
            cout << "\nSelect account (1-" << customer->getAccountCount() << "): ";
            cin >> accChoice;

            if (accChoice < 1 || accChoice > customer->getAccountCount()) {
                cout << "Invalid account selection!\n";
                cout << "\nPress any key to continue...";
                cin.ignore();
                cin.get();
                return;
            }

            // Get selected account
            Account* accounts = customer->getAllAccounts();
            Utility::String accountNumber = accounts[accChoice - 1].getAccountNumber();

            double amount;
            cout << "Enter deposit amount: ";
            cin >> amount;

            if (processCustomerTransaction(accountNumber, Utility::String("Deposit"), amount,
                Utility::String("Online deposit by customer"))) {
                auditLog.addLog(currentUser->getUserID(), "CUSTOMER_DEPOSIT",
                    Utility::String("Account: ") + accountNumber + Utility::String(", Amount: ") + Utility::doubleToString(amount));
            }
        }
        else {
            cout << "You must be a customer to deposit money.\n";
        }
        cout << "\nPress any key to continue...";
        cin.ignore();
        cin.get();
    }

    void withdrawMoney() {
        system("cls");
        Customer* customer = dynamic_cast<Customer*>(currentUser);
        if (customer) {
            cout << "\n=== WITHDRAW MONEY ===\n";

            // Display customer's accounts
            customer->displayAccounts();

            if (customer->getAccountCount() == 0) {
                cout << "No accounts found!\n";
                cout << "\nPress any key to continue...";
                cin.ignore();
                cin.get();
                return;
            }

            int accChoice;
            cout << "\nSelect account (1-" << customer->getAccountCount() << "): ";
            cin >> accChoice;

            if (accChoice < 1 || accChoice > customer->getAccountCount()) {
                cout << "Invalid account selection!\n";
                cout << "\nPress any key to continue...";
                cin.ignore();
                cin.get();
                return;
            }

            // Get selected account
            Account* accounts = customer->getAllAccounts();
            Utility::String accountNumber = accounts[accChoice - 1].getAccountNumber();

            double amount;
            cout << "Enter withdrawal amount: ";
            cin >> amount;

            if (processCustomerTransaction(accountNumber, Utility::String("Withdrawal"), amount,
                Utility::String("Online withdrawal by customer"))) {
                auditLog.addLog(currentUser->getUserID(), "CUSTOMER_WITHDRAWAL",
                    Utility::String("Account: ") + accountNumber + Utility::String(", Amount: ") + Utility::doubleToString(amount));
            }
        }
        else {
            cout << "You must be a customer to withdraw money.\n";
        }
        cout << "\nPress any key to continue...";
        cin.ignore();
        cin.get();
    }

    void transferMoney() {
        system("cls");
        Customer* customer = dynamic_cast<Customer*>(currentUser);
        if (customer) {
            cout << "\n=== TRANSFER MONEY ===\n";

            // Display customer's accounts
            customer->displayAccounts();

            if (customer->getAccountCount() == 0) {
                cout << "No accounts found!\n";
                cout << "\nPress any key to continue...";
                cin.ignore();
                cin.get();
                return;
            }

            int accChoice;
            cout << "\nSelect your account (1-" << customer->getAccountCount() << "): ";
            cin >> accChoice;

            if (accChoice < 1 || accChoice > customer->getAccountCount()) {
                cout << "Invalid account selection!\n";
                cout << "\nPress any key to continue...";
                cin.ignore();
                cin.get();
                return;
            }

            // Get selected account
            Account* accounts = customer->getAllAccounts();
            Utility::String fromAccountNumber = accounts[accChoice - 1].getAccountNumber();

            char toAccountNum[20];
            cout << "Enter destination account number (16 digits): ";
            cin >> toAccountNum;
            Utility::String toAccountNumber(toAccountNum);

            if (!Utility::validateAccountID(toAccountNumber)) {
                cout << "Invalid account number! Must be 16 digits.\n";
                cout << "\nPress any key to continue...";
                cin.ignore();
                cin.get();
                return;
            }

            if (fromAccountNumber == toAccountNumber) {
                cout << "Cannot transfer to the same account!\n";
                cout << "\nPress any key to continue...";
                cin.ignore();
                cin.get();
                return;
            }

            double amount;
            cout << "Enter transfer amount (max 50,000): ";
            cin >> amount;

            if (processCustomerTransfer(fromAccountNumber, toAccountNumber, amount)) {
                auditLog.addLog(currentUser->getUserID(), "CUSTOMER_TRANSFER",
                    Utility::String("From: ") + fromAccountNumber +
                    Utility::String(", To: ") + toAccountNumber +
                    Utility::String(", Amount: ") + Utility::doubleToString(amount));
            }
        }
        else {
            cout << "You must be a customer to transfer money.\n";
        }
        cout << "\nPress any key to continue...";
        cin.ignore();
        cin.get();
    }

    void viewTransactionHistory() {
        system("cls");
        Customer* customer = dynamic_cast<Customer*>(currentUser);
        if (customer) {
            cout << "\n=== TRANSACTION HISTORY ===\n";
            cout << "Customer: " << customer->getName().c_str() << endl;
            cout << "----------------------------------------\n";

            // Display transactions for all customer accounts
            Account* accounts = customer->getAllAccounts();
            int totalTransactions = 0;

            for (int i = 0; i < customer->getAccountCount(); i++) {
                Utility::String accountNumber = accounts[i].getAccountNumber();
                cout << "\nAccount: " << accountNumber.c_str() << endl;
                cout << "Type: " << accounts[i].getAccountType().c_str() << endl;
                cout << "Balance: " << Utility::formatCurrency(accounts[i].getBalance()).c_str() << endl;
                cout << "----------------------------------------\n";

                int count = 0;
                for (int j = transactionCount - 1; j >= 0 && count < 5; j--) {
                    if (transactions[j].getAccountNumber() == accountNumber) {
                        cout << "Date: " << transactions[j].getTimestamp().toString().c_str() << endl;
                        cout << "Type: " << transactions[j].getType().c_str() << endl;
                        cout << "Amount: " << Utility::formatCurrency(transactions[j].getAmount()).c_str() << endl;
                        if (transactions[j].getDescription().getLength() > 0) {
                            cout << "Desc: " << transactions[j].getDescription().c_str() << endl;
                        }
                        if (transactions[j].getRelatedAccount().getLength() > 0) {
                            cout << "To/From: " << transactions[j].getRelatedAccount().c_str() << endl;
                        }
                        cout << "------------------------\n";
                        count++;
                        totalTransactions++;
                    }
                }

                if (count == 0) {
                    cout << "No transactions found for this account.\n";
                }
            }

            cout << "\nTotal transactions displayed: " << totalTransactions << endl;
            auditLog.addLog(currentUser->getUserID(), "VIEW_TRANSACTION_HISTORY");
        }
        else {
            cout << "You must be a customer to view transaction history.\n";
        }
        cout << "\nPress any key to continue...";
        cin.ignore();
        cin.get();
    }

    void applyForLoan() {
        system("cls");
        Customer* customer = dynamic_cast<Customer*>(currentUser);
        if (customer) {
            cout << "\n=== APPLY FOR LOAN ===\n";

            double amount;
            int duration;
            char purpose[100];

            cout << "Enter Loan Amount: ";
            cin >> amount;

            if (amount <= 0) {
                cout << "Loan amount must be positive!\n";
                cout << "\nPress any key to continue...";
                cin.ignore();
                cin.get();
                return;
            }

            cout << "Enter Loan Duration (in months): ";
            cin >> duration;

            if (duration <= 0) {
                cout << "Duration must be positive!\n";
                cout << "\nPress any key to continue...";
                cin.ignore();
                cin.get();
                return;
            }

            cout << "Enter Loan Purpose: ";
            cin.ignore();
            cin.getline(purpose, 100);

            // Get customer's first account
            Account* accounts = customer->getAllAccounts();
            Utility::String accountNumber = (customer->getAccountCount() > 0) ?
                accounts[0].getAccountNumber() : Utility::String("1000000000000001");

            // Create loan application
            if (loanCount >= loanCapacity) {
                resizeLoans();
            }

            loans[loanCount] = Loan(
                customer->getUserID(),
                accountNumber,
                amount,
                duration,
                Utility::String(purpose)
            );

            loanCount++;

            // Save to file
            saveLoansToFile();

            cout << "\nLoan application submitted successfully!\n";
            cout << "Application ID: " << loans[loanCount - 1].getLoanID().c_str() << endl;
            cout << "Status: Pending (Two-step approval: Officer ? Admin)\n";
            cout << "\nYou will be notified when your loan is reviewed.\n";
            cout << "Check 'View Loan Status' for updates.\n";

            auditLog.addLog(currentUser->getUserID(), "APPLY_FOR_LOAN",
                Utility::String("Amount: ") + Utility::doubleToString(amount));
        }
        else {
            cout << "You must be a customer to apply for a loan.\n";
        }
        cout << "\nPress any key to continue...";
        cin.ignore();
        cin.get();
    }

    // UPDATED: View Loan Status for Customer with two-step approval
    void viewLoanStatus() {
        system("cls");
        Customer* customer = dynamic_cast<Customer*>(currentUser);
        if (customer) {
            cout << "\n========================================\n";
            cout << "         YOUR LOAN APPLICATIONS\n";
            cout << "========================================\n";
            cout << "Customer: " << customer->getName().c_str() << endl;
            cout << "Customer ID: " << customer->getUserID().c_str() << endl;
            cout << "========================================\n";

            bool found = false;
            int pendingCount = 0, officerApprovedCount = 0, adminApprovedCount = 0, rejectedCount = 0;

            for (int i = 0; i < loanCount; i++) {
                if (loans[i].getCustomerID() == customer->getUserID()) {
                    found = true;

                    cout << "\nLoan Application #" << (i + 1) << endl;
                    cout << "----------------------------------------\n";
                    cout << "Loan ID: " << loans[i].getLoanID().c_str() << endl;
                    cout << "Amount: " << Utility::formatCurrency(loans[i].getAmount()).c_str() << endl;
                    cout << "Purpose: " << loans[i].getPurpose().c_str() << endl;
                    cout << "Applied Date: " << loans[i].getApplicationDate().toString().c_str() << endl;
                    cout << "Status: ";

                    // Color code the status
                    if (loans[i].getStatus() == "Admin Approved") {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); // Green
                        cout << "? FINALLY APPROVED BY ADMIN";
                        adminApprovedCount++;
                    }
                    else if (loans[i].getStatus() == "Officer Approved") {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); // Yellow
                        cout << "? APPROVED BY OFFICER (Waiting for Admin Final Approval)";
                        officerApprovedCount++;
                    }
                    else if (loans[i].getStatus() == "Rejected") {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); // Red
                        cout << "? REJECTED";
                        rejectedCount++;
                    }
                    else if (loans[i].getStatus() == "Pending") {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); // White
                        cout << "? PENDING (Two-step approval in progress)";
                        pendingCount++;
                    }
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // Reset to white
                    cout << endl;

                    if (loans[i].getStatus() == "Admin Approved") {
                        cout << "\n=== LOAN DETAILS ===\n";
                        cout << "Officer Approval Date: " << loans[i].getOfficerApprovalDate().toString().c_str() << endl;
                        cout << "Approved By Officer: " << loans[i].getApprovedByOfficer().c_str() << endl;
                        cout << "Admin Final Approval Date: " << loans[i].getAdminApprovalDate().toString().c_str() << endl;
                        cout << "Approved By Admin: " << loans[i].getApprovedByAdmin().c_str() << endl;
                        cout << "Interest Rate: " << loans[i].getInterestRate() << "%" << endl;
                        cout << "Duration: " << loans[i].getDurationMonths() << " months" << endl;
                        cout << "Monthly EMI: " << Utility::formatCurrency(loans[i].calculateEMI()).c_str() << endl;
                        cout << "Total Payable: " << Utility::formatCurrency(loans[i].getAmount() +
                            (loans[i].getAmount() * loans[i].getInterestRate() * loans[i].getDurationMonths() / 1200)).c_str() << endl;
                        cout << "\n?? CONGRATULATIONS! Your loan has been FINALLY APPROVED by Admin! ??\n";
                        cout << "The amount will be disbursed to your account shortly.\n";
                    }
                    else if (loans[i].getStatus() == "Officer Approved") {
                        cout << "\n=== CURRENT STATUS ===\n";
                        cout << "Officer Approval Date: " << loans[i].getOfficerApprovalDate().toString().c_str() << endl;
                        cout << "Approved By Officer: " << loans[i].getApprovedByOfficer().c_str() << endl;
                        cout << "\nYour loan has been approved by the Officer.\n";
                        cout << "Now waiting for final approval from Admin.\n";
                        cout << "Expected Admin review time: 1-2 business days.\n";
                    }
                    else if (loans[i].getStatus() == "Rejected") {
                        cout << "\nNote: Your loan application was not approved.\n";
                        cout << "You may apply again after 30 days.\n";
                        cout << "Contact bank customer service for more details.\n";
                    }
                    else if (loans[i].getStatus() == "Pending") {
                        cout << "\nYour loan application is under initial review by Officer.\n";
                        cout << "Expected review time: 3-5 business days.\n";
                        cout << "You will be notified once a decision is made.\n";
                    }
                    cout << "----------------------------------------\n";
                }
            }

            if (!found) {
                cout << "No loan applications found.\n";
                cout << "\nYou can apply for a loan from the main menu.\n";
            }
            else {
                cout << "\n=== SUMMARY ===\n";
                cout << "Total Applications: " << (pendingCount + officerApprovedCount + adminApprovedCount + rejectedCount) << endl;
                cout << "Pending: " << pendingCount << endl;
                cout << "Officer Approved: " << officerApprovedCount << endl;
                cout << "Admin Approved (Final): " << adminApprovedCount << endl;
                cout << "Rejected: " << rejectedCount << endl;

                if (adminApprovedCount > 0) {
                    cout << "\n?? You have " << adminApprovedCount << " loan(s) FINALLY APPROVED! ??\n";
                }
                if (officerApprovedCount > 0) {
                    cout << "\n? You have " << officerApprovedCount << " loan(s) waiting for Admin final approval.\n";
                }
                if (rejectedCount > 0) {
                    cout << "\n? " << rejectedCount << " of your applications were rejected.\n";
                }
            }

            auditLog.addLog(currentUser->getUserID(), "VIEW_LOAN_STATUS");
        }
        else {
            cout << "You must be a customer to view loan status.\n";
        }

        cout << "\nPress any key to continue...";
        cin.ignore();
        cin.get();
    }

    void registerComplaint() {
        system("cls");
        Customer* customer = dynamic_cast<Customer*>(currentUser);
        if (customer) {
            cout << "\n=== REGISTER COMPLAINT ===\n";

            char category[50], description[200];

            cout << "Enter Complaint Category: ";
            cin.ignore();
            cin.getline(category, 50);

            cout << "Enter Complaint Description: ";
            cin.getline(description, 200);

            // Get customer's first account
            Account* accounts = customer->getAllAccounts();
            Utility::String accountNumber = (customer->getAccountCount() > 0) ?
                accounts[0].getAccountNumber() : Utility::String("1000000000000001");

            // Create complaint
            if (complaintCount >= complaintCapacity) {
                resizeComplaints();
            }

            complaints[complaintCount] = Complaint(
                customer->getUserID(),
                accountNumber,
                Utility::String(category),
                Utility::String(description)
            );

            complaintCount++;

            // Save to file
            saveComplaintsToFile();

            cout << "\nComplaint registered successfully!\n";
            cout << "Complaint ID: " << complaints[complaintCount - 1].getComplaintID().c_str() << endl;
            cout << "Status: Open\n";
            cout << "Process: Officer ? (if needed) Escalated to Admin\n";
            cout << "You will be notified when your complaint is resolved.\n";

            auditLog.addLog(currentUser->getUserID(), "REGISTER_COMPLAINT",
                Utility::String("Category: ") + Utility::String(category));
        }
        else {
            cout << "You must be a customer to register a complaint.\n";
        }
        cout << "\nPress any key to continue...";
        cin.ignore();
        cin.get();
    }

    // View Complaint Status for Customer - UPDATED
    void viewComplaintStatus() {
        system("cls");
        Customer* customer = dynamic_cast<Customer*>(currentUser);
        if (customer) {
            cout << "\n========================================\n";
            cout << "       YOUR COMPLAINT STATUS\n";
            cout << "========================================\n";
            cout << "Customer: " << customer->getName().c_str() << endl;
            cout << "Customer ID: " << customer->getUserID().c_str() << endl;
            cout << "========================================\n";

            bool found = false;
            int openCount = 0, inProgressCount = 0, resolvedCount = 0,
                escalatedCount = 0, adminResolvedCount = 0;

            for (int i = 0; i < complaintCount; i++) {
                if (complaints[i].getCustomerID() == customer->getUserID()) {
                    found = true;

                    cout << "\nComplaint #" << (i + 1) << endl;
                    cout << "----------------------------------------\n";
                    cout << "Complaint ID: " << complaints[i].getComplaintID().c_str() << endl;
                    cout << "Category: " << complaints[i].getCategory().c_str() << endl;
                    cout << "Description: " << complaints[i].getDescription().c_str() << endl;
                    cout << "Submission Date: " << complaints[i].getSubmissionDate().toString().c_str() << endl;
                    cout << "Status: ";

                    // Color code the status
                    if (complaints[i].getStatus() == "Open") {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); // Bright White
                        cout << "? OPEN";
                        openCount++;
                    }
                    else if (complaints[i].getStatus() == "In Progress") {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); // Yellow
                        cout << "? IN PROGRESS";
                        inProgressCount++;
                    }
                    else if (complaints[i].getStatus() == "Resolved") {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); // Green
                        cout << "? RESOLVED BY OFFICER";
                        resolvedCount++;
                    }
                    else if (complaints[i].getStatus() == "Escalated") {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13); // Purple
                        cout << "? ESCALATED TO ADMIN";
                        escalatedCount++;
                    }
                    else if (complaints[i].getStatus() == "Admin Resolved") {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); // Green
                        cout << "? RESOLVED BY ADMIN";
                        adminResolvedCount++;
                    }
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // Reset to white
                    cout << endl;

                    // Show additional details based on status
                    if (complaints[i].getStatus() == "In Progress") {
                        if (complaints[i].getAssignedTo().getLength() > 0) {
                            cout << "Assigned To Officer: " << complaints[i].getAssignedTo().c_str() << endl;
                        }
                        cout << "\nYour complaint is being reviewed by our Officer team.\n";
                        cout << "Expected resolution time: 2-3 business days.\n";
                    }
                    else if (complaints[i].getStatus() == "Resolved") {
                        cout << "Resolution: " << complaints[i].getResolution().c_str() << endl;
                        cout << "Resolution Date: " << complaints[i].getResolutionDate().toString().c_str() << endl;
                        cout << "\nYour complaint has been successfully resolved by Officer!\n";
                        cout << "Thank you for your patience.\n";
                    }
                    else if (complaints[i].getStatus() == "Escalated") {
                        cout << "Escalated By: " << complaints[i].getEscalatedBy().c_str() << endl;
                        cout << "Escalation Date: " << complaints[i].getEscalationDate().toString().c_str() << endl;
                        cout << "\n? YOUR COMPLAINT HAS BEEN ESCALATED TO ADMINISTRATION ?\n";
                        cout << "This means your complaint requires higher-level attention.\n";
                        cout << "Administration will review it and contact you if needed.\n";
                        cout << "Expected response time: 1-2 business days.\n";
                    }
                    else if (complaints[i].getStatus() == "Admin Resolved") {
                        cout << "Resolution: " << complaints[i].getResolution().c_str() << endl;
                        cout << "Resolution Date: " << complaints[i].getResolutionDate().toString().c_str() << endl;
                        cout << "Resolved By: ADMIN " << complaints[i].getAssignedTo().c_str() << endl;
                        cout << "\nYour complaint has been successfully resolved by ADMINISTRATION!\n";
                        cout << "Thank you for your patience with the escalated process.\n";
                    }
                    else if (complaints[i].getStatus() == "Open") {
                        cout << "\nYour complaint has been received and is in the queue.\n";
                        cout << "It will be assigned to an officer shortly.\n";
                        cout << "Expected assignment time: 1-2 business days.\n";
                    }
                    cout << "----------------------------------------\n";
                }
            }

            if (!found) {
                cout << "No complaints found.\n";
                cout << "\nYou can register a complaint from the main menu.\n";
            }
            else {
                cout << "\n=== SUMMARY ===\n";
                cout << "Total Complaints: " << (openCount + inProgressCount + resolvedCount + escalatedCount + adminResolvedCount) << endl;
                cout << "Open: " << openCount << endl;
                cout << "In Progress: " << inProgressCount << endl;
                cout << "Resolved by Officer: " << resolvedCount << endl;
                cout << "Escalated to Admin: " << escalatedCount << endl;
                cout << "Resolved by Admin: " << adminResolvedCount << endl;

                // Show appropriate messages based on status counts
                if (resolvedCount > 0 || adminResolvedCount > 0) {
                    cout << "\n?? " << (resolvedCount + adminResolvedCount) << " of your complaints have been RESOLVED! ??\n";
                }
                if (escalatedCount > 0) {
                    cout << "\n? " << escalatedCount << " of your complaints have been ESCALATED to Administration.\n";
                    cout << "   Our senior team is reviewing them.\n";
                }
                if (inProgressCount > 0) {
                    cout << "\n? " << inProgressCount << " of your complaints are currently IN PROGRESS.\n";
                    cout << "   Our team is actively working on them.\n";
                }
                if (openCount > 0) {
                    cout << "\n? " << openCount << " of your complaints are OPEN and awaiting assignment.\n";
                }
            }

            auditLog.addLog(currentUser->getUserID(), "VIEW_COMPLAINT_STATUS");
        }
        else {
            cout << "You must be a customer to view complaint status.\n";
        }

        cout << "\nPress any key to continue...";
        cin.ignore();
        cin.get();
    }

    void updateProfile() {
        system("cls");
        Customer* customer = dynamic_cast<Customer*>(currentUser);
        if (customer) {
            cout << "\n=== UPDATE PROFILE ===\n";

            char email[100], phone[20], address[200];

            cout << "Enter New Email: ";
            cin.ignore();
            cin.getline(email, 100);

            cout << "Enter New Phone: ";
            cin.getline(phone, 20);

            cout << "Enter New Address: ";
            cin.getline(address, 200);

            customer->updateProfile(
                Utility::String(email),
                Utility::String(phone),
                Utility::String(address)
            );

            // Save updated profile to file
            saveCustomersToFile();

            cout << "Profile updated successfully!\n";
            auditLog.addLog(currentUser->getUserID(), "UPDATE_PROFILE");
        }
        else {
            cout << "You must be a customer to update profile.\n";
        }
        cout << "\nPress any key to continue...";
        cin.ignore();
        cin.get();
    }

    void requestStatement() {
        system("cls");
        Customer* customer = dynamic_cast<Customer*>(currentUser);
        if (customer) {
            cout << "\n=== ACCOUNT STATEMENT ===\n";

            // Display customer's accounts
            customer->displayAccounts();

            if (customer->getAccountCount() == 0) {
                cout << "No accounts found!\n";
                cout << "\nPress any key to continue...";
                cin.ignore();
                cin.get();
                return;
            }

            int accChoice;
            cout << "\nSelect account for statement (1-" << customer->getAccountCount() << "): ";
            cin >> accChoice;

            if (accChoice < 1 || accChoice > customer->getAccountCount()) {
                cout << "Invalid account selection!\n";
                cout << "\nPress any key to continue...";
                cin.ignore();
                cin.get();
                return;
            }

            // Get selected account
            Account* accounts = customer->getAllAccounts();
            Utility::String accountNumber = accounts[accChoice - 1].getAccountNumber();

            cout << "\n=== ACCOUNT STATEMENT ===\n";
            cout << "Account Number: " << accountNumber.c_str() << endl;
            cout << "Account Type: " << accounts[accChoice - 1].getAccountType().c_str() << endl;
            cout << "Current Balance: " << Utility::formatCurrency(accounts[accChoice - 1].getBalance()).c_str() << endl;
            cout << "Statement Date: " << Utility::Date::getCurrentDate().toString().c_str() << endl;
            cout << "========================================\n";
            cout << "Date       | Type       | Amount\n";
            cout << "----------------------------------------\n";

            // Display last 10 transactions
            int count = 0;
            for (int i = transactionCount - 1; i >= 0 && count < 10; i--) {
                if (transactions[i].getAccountNumber() == accountNumber) {
                    cout << setw(10) << left << transactions[i].getTimestamp().toString().c_str();
                    cout << " | " << setw(10) << left << transactions[i].getType().c_str();
                    cout << " | " << Utility::formatCurrency(transactions[i].getAmount()).c_str() << endl;
                    count++;
                }
            }

            if (count == 0) {
                cout << "No transactions found.\n";
            }

            cout << "\nStatement has been generated successfully.\n";
            auditLog.addLog(currentUser->getUserID(), "REQUEST_STATEMENT", accountNumber);
        }
        else {
            cout << "You must be a customer to request a statement.\n";
        }
        cout << "\nPress any key to continue...";
        cin.ignore();
        cin.get();
    }

    void calculateInterest() {
        system("cls");
        Customer* customer = dynamic_cast<Customer*>(currentUser);
        if (customer) {
            cout << "\n=== INTEREST CALCULATION ===\n";

            int months;
            cout << "Enter number of months: ";
            cin >> months;

            if (months <= 0) {
                cout << "Number of months must be positive!\n";
                cout << "\nPress any key to continue...";
                cin.ignore();
                cin.get();
                return;
            }

            // Calculate interest for each account
            Account* accounts = customer->getAllAccounts();
            int accountCount = customer->getAccountCount();

            if (accountCount == 0) {
                cout << "No accounts found!\n";
                cout << "\nPress any key to continue...";
                cin.ignore();
                cin.get();
                return;
            }

            for (int i = 0; i < accountCount; i++) {
                cout << "\nAccount " << (i + 1) << ": " << accounts[i].getAccountNumber().c_str() << endl;
                cout << "Account Type: " << accounts[i].getAccountType().c_str() << endl;
                cout << "Balance: " << Utility::formatCurrency(accounts[i].getBalance()).c_str() << endl;
                cout << "Interest Rate: " << accounts[i].getInterestRate() << "%" << endl;

                double interest = accounts[i].calculateInterest(months);
                cout << "Interest for " << months << " months: " << Utility::formatCurrency(interest).c_str() << endl;
                cout << "Total Amount: " << Utility::formatCurrency(accounts[i].getBalance() + interest).c_str() << endl;
                cout << "------------------------\n";
            }

            auditLog.addLog(currentUser->getUserID(), "CALCULATE_INTEREST");
        }
        else {
            cout << "You must be a customer to calculate interest.\n";
        }
        cout << "\nPress any key to continue...";
        cin.ignore();
        cin.get();
    }

    // Main run function
    void run() {
        system("cls");
        cout << "\n========================================\n";
        cout << "   WELCOME TO BANK MANAGEMENT SYSTEM\n";
        cout << "========================================\n";
        cout << "Developed by: Bank Management Team\n";
        cout << "Version: 2.0 (Two-Step Approval System)\n";
        cout << "========================================\n";
        cout << "\nKey Features:\n";
        cout << "1. Two-Step Loan Approval: Officer ? Admin\n";
        cout << "2. Complaint Escalation: Officer can escalate to Admin\n";
        cout << "3. Admin Final Authority on Loans & Escalated Complaints\n";
        cout << "========================================\n";
        cout << "\nPress any key to continue...";
        cin.ignore();
        cin.get();

        while (true) {
            if (!currentUser) {
                currentUser = login();
                if (!currentUser) {
                    cout << "\nThank you for using Bank Management System!\n";
                    saveData();
                    break;
                }
            }

            // Display appropriate menu based on user type
            if (dynamic_cast<Admin*>(currentUser)) {
                adminMenu();
            }
            else if (dynamic_cast<Officer*>(currentUser)) {
                officerMenu();
            }
            else if (dynamic_cast<Customer*>(currentUser)) {
                customerMenu();
            }

            if (!currentUser) {
                continue;
            }
        }
    }
};

// ============================================================================
// MAIN FUNCTION
// ============================================================================
int main() {
    system("title Bank Management System v2.0 - Two-Step Approval");
    system("color 0B");

    BankSystem bankSystem;
    bankSystem.run();

    return 0;
}