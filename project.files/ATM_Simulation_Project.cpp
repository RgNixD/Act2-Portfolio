#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <conio.h>
#include <windows.h>

using namespace std;

// Function to hide input for the PIN
string hideInput() {
    string pin;
    char c;
    while (true) {
        c = _getch();
        if (c == 13) { // Enter key
            cout << endl;
            break;
        } else if (c == 8) { // Backspace
            if (!pin.empty()) {
                cout << "\b \b";
                pin.pop_back();
            }
        } else {
            cout << "*";
            pin += c;
        }
    }
    return pin;
}

typedef struct account { // Account info about the user
    int accountNumber;
    std::string accountName;
    std::string birthday;
    std::string contactNumber;
    double initialDeposit;
    std::string pinCode;
} REC;

string reversePin(const string &pin) { // Function to reverse the PIN digits for encryption
    string reversedPin = pin;
    reverse(reversedPin.begin(), reversedPin.end());
    return reversedPin;
}

class ATM { // Functions that form the whole ATM
private:
    REC a;
    string STEAK_ = "E:\\pin_codes.txt"; // USB drive path of pin codes
    double balance = 0;
    bool isRegistered = false;

public:
    bool inputPredefinedAccount();
    void loadPinFromFile();
    void savePinToFile(const string& pin);
    void loadRegisteredPins();
    void registerAcc();
    int getAccNum();
    void balanceInquiry();
    void changePin();
    bool withdraw(double amount);
    bool deposit(double amount);
    bool verifyPin(string enteredPin);
    double getBalance();
    bool fundTransfer();
    void displayMainMenu();
    int main();
};

bool ATM::inputPredefinedAccount() { // Function of predefined account and PIN
    cout << "\n\t\t**************************************************************************************" << endl;
    cout << "\t\t*\t\t\t[ A C C O U N T ] *";
    cout << "\n\t\t**************************************************************************************" << endl;
    cout << "\n\t\t        Enter account number: ";
    cin >> a.accountNumber;
    cout << "\n\t\t        Enter the 6-digit PIN code: ";
    string pin = hideInput();
    cout << "\n\n";

    // Verify the predefined account and PIN
    if (a.accountNumber == 12345 && reversePin("123456") == pin) {
        isRegistered = true;
        return true;
    } else {
        cout << "\n\t\t\t\t[Account input is incorrect. Exiting.]" << endl;
        cout << "\n\t\t**************************************************************************************" << endl;
        return false;
    }
}

void ATM::loadPinFromFile() { // Function that detect if the card is inserted
    ifstream pinFile(STEAK_.c_str());
    if (pinFile.is_open()) {
        string pin;
        pinFile >> pin;
        pinFile.close();
        isRegistered = true;
    } else {
        cout << "Error: Card not inserted or card file not found." << endl;
    }
}

void ATM::savePinToFile(const string& pin) { // Function that saves pin codes
    ofstream pinFile(STEAK_ + "pin_codes", ios::app);
    if (pinFile.is_open()) {
        pinFile << pin << endl;
        pinFile.close();
    } else {
        cout << "Error: Could not save the PIN to the USB drive." << endl;
    }
}

void ATM::loadRegisteredPins() { // Function that reads the saved pin codes
    ifstream pinFile(STEAK_ + "pin_codes.txt");
    if (pinFile.is_open()) {
        string line;
        while (getline(pinFile, line)) {
            // You can process each registered PIN code here
            cout << "Registered PIN: " << line << endl;
        }
        pinFile.close();
    }
}

void ATM::registerAcc() { // Functions for processing registration
    if (isRegistered) {
    cout << "\n\t\t**************************************************************************************" << endl;
    cout << "\t\t*\t\t\t[ A C C O U N T    R E G I S T R A T I O N ]                    *";
    cout << "\n\t\t**************************************************************************************" << endl;
    do {
        cout << "\n\t\t        Enter your account number (5 digits):  ";
        cin >> a.accountNumber;
    } while (to_string(a.accountNumber).length() != 5); // Ensure exactly 5 digits

    cout << "\n\t\t        Name: ";
    cin.ignore();
    getline(cin, a.accountName);
    cout << "\t\t        Birthday (MM/DD/YY): ";
    cin.ignore();
    getline(cin, a.birthday);
    cout << "\t\t        Contact number: ";
    cin >> a.contactNumber;

    string pin, confirmPin;
    do {
        cout << "\n\t\t        Enter a 6-digits PIN code: ";
        pin = hideInput();
    } while (pin.length() != 6); // Ensure a 6-digit PIN

    do {
        cout << "\t\t        Enter the PIN code again to confirm: ";
        confirmPin = hideInput();
    } while (confirmPin != pin); // Confirm the PIN
    // Encrypt the PIN before storing it
    a.pinCode = reversePin(pin);

    do {
        cout << "\n\t\t        Enter initial deposit (minimum of Php.5000): ";
        cin >> a.initialDeposit;
    } while (a.initialDeposit < 5000); // Ensure a minimum deposit of Php. 5000

    balance = a.initialDeposit;
    isRegistered = true; // Confirmation to save account

    cout << "\n\t\t\t\t\t[ Account registered successfully! ]" << endl;
    cout << "\n\t\t**************************************************************************************" << endl;
    system("pause");
    } else {
        cout << "Card not found or PIN is not registered." << endl;
    }
}

int ATM::getAccNum() { // Saves the account number of user
    return a.accountNumber;
}

void ATM::balanceInquiry() { // Function to check account balance
    system("cls");
    cout << "\n\t\t**************************************************************************************" << endl;
    cout << "\t\t*\t\t\t\t[ B A L A N C E ]                                    *";
    cout << "\n\t\t**************************************************************************************" << endl;
    cout << "\n\t\t        Account Balance: Php. " << balance << endl;
    cout << "\n\t\t**************************************************************************************" << endl;
    getch();
}

void ATM::changePin() { // Function to change the pin of user
    string newPin, confirmNewPin;
    system("cls");
    cout << "\n\t\t**************************************************************************************" << endl;
    cout << "\t\t*\t\t\t\t[ C H A N G E P I N ]                                    *";
    cout << "\n\t\t**************************************************************************************" << endl;
    cout << "\n\t\tEnter your current PIN: ";
    string currentPin;
    currentPin = hideInput();

    if (verifyPin(currentPin)) { // Verify the current PIN
        do {
            cout << "\n\t\tEnter a new 6-digit PIN code: ";
            newPin = hideInput();
        } while (newPin.length() != 6); // Ensure a 6-digit PIN

        do {
            cout << "\t\tEnter the new PIN code again to confirm: ";
            confirmNewPin = hideInput();
        } while (confirmNewPin != newPin); // Confirm the new PIN
        // Encrypt the new PIN before storing it
        a.pinCode = reversePin(newPin);

        cout << "\n\t\t[PIN changed successfully!]" << endl;
        cout << "\n\t\t**************************************************************************************" << endl;
    }
    getch();
}

bool ATM::withdraw(double amount) { // Function to withdraw current balance
    string enteredPin;
    cout << "\t\t        Enter your PIN: ";
    enteredPin = hideInput();

    if (verifyPin(enteredPin)) { // Verify the PIN
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "\n\t\t\t\t\t        [Withdrawal successful.]" << endl;
            cout << "\n\t\t        New balance: Php. " << balance << endl;
            cout << "\n\t\t**************************************************************************************" << endl;
            return true;
        } else {
            cout << "\n\t\t        [Withdrawal failed. Insufficient funds or invalid amount.]" << endl;
            cout << "\n\t\t**************************************************************************************" << endl;
        }
    }
    getch();
    return false;
}

bool ATM::deposit(double amount) { // Function that deposits current balance
    string enteredPin;
    cout << "\t\t        Enter your PIN: ";
    enteredPin = hideInput();

    if (verifyPin(enteredPin)) { // Verify the PIN
        if (amount > 0) {
            balance += amount;
            cout << "\n\t\t\t\t\t        [Deposit successful.]" << endl;
            cout << "\n\t\t        New balance: Php. " << balance << endl;
            cout << "\n\t\t**************************************************************************************" << endl;
            return true;
        } else {
            cout << "\n\t\t        [Deposit failed. Invalid amount.]" << endl;
            cout << "\n\t\t**************************************************************************************" << endl;
        }
    }
    getch();
    return false;
}

bool ATM::verifyPin(string enteredPin) { // Decrypt the stored PIN before comparison
    string decryptedPin = reversePin(a.pinCode);

    if (enteredPin == decryptedPin) {
        return true;
    } else {
        cout << "\n\n\n\t\t**************************************************************************************" << endl;
        cout << "\t\t\t\t\t[PIN verification failed. Please try again.]" << endl;
        cout << "\t\t**************************************************************************************" << endl;
        return false;
    }
}

double ATM::getBalance() { // Function to save balance
    return balance;
}

bool ATM::fundTransfer() { // Function to transfer current balance
    string enteredPin;
    cout << "\n\t\t**************************************************************************************" << endl;
    cout << "\t\t*\t\t\t\t[ T R A N S F E R]                                  *";
    cout << "\n\t\t**************************************************************************************" << endl;
    cout << "\n\t\t        Enter your PIN: ";
    enteredPin = hideInput();

    if (verifyPin(enteredPin)) { // Verify the PIN
        if (!isRegistered) {
            cout << "\n\t\t        [Account not registered. Fund Transfer is not available. Please register first.]" << endl;
            cout << "\n\t\t**************************************************************************************" << endl;
            getch();
            return false;
        }

        double transferAmount;
        cout << "\n\t\t        Enter the amount to transfer: ";
        cin >> transferAmount;

        if (transferAmount <= 0 || transferAmount > balance) {
            cout << "\n\t\t       [Invalid transfer amount or insufficient balance.]" << endl;
            cout << "\n\t\t**************************************************************************************" << endl;
            getch();
            return false;
        }

        balance -= transferAmount;
        cout << "\n\t\t\t\t\t        [Fund Transfer Successful!]" << endl;
        cout << "\n\t\t        New balance: Php. " << balance << endl;
        cout << "\n\t\t**************************************************************************************" << endl;
        getch();
        return true;
    }
    getch();
    return false;
}

void ATM::displayMainMenu() { // Interface of ATM menu
    int choice;
    do {
        system("cls");
        cout << "\n\t\t**************************************************************************************" << endl;
        cout << "\t\t*\t\t\t\t[ A T M     M E N U ]                                *";
        cout << "\n\t\t**************************************************************************************" << endl;
        cout << "\t\t*\t1. Register Account                                                          *" << endl;
        cout << "\n\t\t*\t2. Balance Inquiry                                                           *" << endl;
        cout << "\n\t\t*\t3. Change PIN                                                                *" << endl;
        cout << "\n\t\t*\t4. Withdraw                                                                  *" << endl;
        cout << "\n\t\t*\t5. Deposit                                                                   *" << endl;
        cout << "\n\t\t*\t6. Fund Transfer                                                             *" << endl;
        cout << "\n\t\t*\t7. Exit                                                                      *" << endl;
        cout << "\t\t**************************************************************************************" << endl;
        cout << "\n\t\tEnter your choice(1-7 only): ";
        cin >> choice;

        switch (choice) {
            case 1:
                system("cls");
                registerAcc();
                break;
            case 2:
                balanceInquiry();
                break;
            case 3:
                changePin();
                break;
            case 4:
                double withdrawAmount;
                system("cls");
                cout << "\n\t\t**************************************************************************************" << endl;
                cout << "\t\t*\t\t\t\t[ W I T H D R A W ]                                  *";
                cout << "\n\t\t**************************************************************************************" << endl;
                cout << "\n\t\t        Enter the amount to withdraw: ";
                cin >> withdrawAmount;
                withdraw(withdrawAmount);
                getch();
                break;
            case 5:
                double depositAmount;
                system("cls");
                cout << "\n\t\t**************************************************************************************" << endl;
                cout << "\t\t*\t\t\t\t[ D E P O S I T ]                                  *";
                cout << "\n\t\t**************************************************************************************" << endl;
                cout << "\n\t\t        Enter the amount to deposit: ";
                cin >> depositAmount;
                deposit(depositAmount);
                getch();
                break;
            case 6:
                system("cls");
                fundTransfer();
                break;
            case 7:
                cout << "\n\t\t\t\t\t        [Exiting the ATM application. Thank you, come again.]" << endl;
                break;
            default:
                cout << "\n\t\t\t\t\t        [Invalid choice. Please try again.]" << endl;
        }
    } while (choice != 7);
}

int ATM::main() { // The first interface function before the the main menu
    cout << "Insert your flash drive (ATM card) into the USB port." << endl;
    cout << "Press any key to continue...";
    getch();
    loadPinFromFile();

    if (!isRegistered) {
        cout << "Card not found or PIN is not registered. Exiting the ATM application." << endl;
        return 1;
    }

    if (!inputPredefinedAccount()) {
        cout << "Exiting the ATM application. Thank you, come again." << endl;
        return 1;
    }

    displayMainMenu();

    return 0;
}

int main() { // Calls all the ATM functions of the program
    ATM atm1;
    atm1.loadPinFromFile();
    atm1.main();
    return 0;
}
