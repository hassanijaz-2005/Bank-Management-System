#include <iostream>
using namespace std;

// Global variable to track total money in the bank
double totalBankBalance = 0;

// Base class for bank accounts
class BankAccount {
protected:
    int accountNumber;
    string accountHolder;
    double balance;
    int pinCode;

public:
    BankAccount* next;

    BankAccount() : accountNumber(0), accountHolder(""), balance(0.0), pinCode(0), next(0) {}

    void create(int accNo, const string& name, double initialDeposit, int pin) {
        this->accountNumber = accNo;
        this->accountHolder = name;
        this->balance = initialDeposit;
        this->pinCode = pin;
        totalBankBalance += initialDeposit;
    }

    int getAccountNumber() const {
        return accountNumber;
    }

    bool verifyPIN(int pin) const {
        return this->pinCode == pin;
    }

    void showDetails() const {
        cout << "\n=== Account Details ===\n";
        cout << "Account Number : " << accountNumber << endl;
        cout << "Account Holder : " << accountHolder << endl;
        cout << "Balance        : $" << balance << endl;
    }

    void deposit(double amount) {
        if (amount <= 0) {
            cout << "Invalid deposit amount.\n";
            return;
        }
        this->balance += amount;
        totalBankBalance += amount;
        cout << "Deposit successful.\n";
        cout << "Total Bank Balance: $" << totalBankBalance << endl;
    }

    void withdraw(double amount) {
        if (amount <= 0 || amount > this->balance) {
            cout << "Invalid or insufficient amount.\n";
            return;
        }
        this->balance -= amount;
        totalBankBalance -= amount;
        cout << "Withdrawal successful.\n";
        cout << "Total Bank Balance: $" << totalBankBalance << endl;
    }

    virtual ~BankAccount() {}
};

int main() {
    BankAccount* head = 0;
    int option;

    do {
        cout << "\n====== Bank Menu ======\n";
        cout << "1. Create New Account\n";
        cout << "2. Search Account\n";
        cout << "3. Deposit Money\n";
        cout << "4. Withdraw Money\n";
        cout << "5. Exit\n";
        cout << "Choose an option: ";
        cin >> option;

        switch (option) {
            case 1: {
                int accNo, pin;
                string name;
                double deposit;

                cout << "Enter Account Number: ";
                cin >> accNo;
                cin.ignore();
                cout << "Enter Account Holder Name: ";
                getline(cin, name);
                cout << "Enter Initial Deposit: ";
                cin >> deposit;
                cout << "Set 4-digit PIN: ";
                cin >> pin;

                BankAccount* newAccount = new BankAccount();
                newAccount->create(accNo, name, deposit, pin);
                newAccount->next = head;
                head = newAccount;

                cout << "Account created successfully.\n";
                cout << "Total Bank Balance: $" << totalBankBalance << endl;
                break;
            }

            case 2: {
                int accNo;
                cout << "Enter Account Number to view: ";
                cin >> accNo;

                BankAccount* current = head;
                bool found = false;

                while (current != 0) {
                    if (current->getAccountNumber() == accNo) {
                        current->showDetails();
                        found = true;
                        break;
                    }
                    current = current->next;
                }

                if (!found) {
                    cout << "Account not found.\n";
                }
                break;
            }

            case 3: {
                int accNo, pin;
                double amount;
                cout << "Enter Account Number: ";
                cin >> accNo;

                BankAccount* current = head;
                bool found = false;

                while (current != 0) {
                    if (current->getAccountNumber() == accNo) {
                        cout << "Enter 4-digit PIN: ";
                        cin >> pin;

                        if (current->verifyPIN(pin)) {
                            cout << "Enter amount to deposit: ";
                            cin >> amount;
                            current->deposit(amount);
                        } else {
                            cout << "Incorrect PIN.\n";
                        }
                        found = true;
                        break;
                    }
                    current = current->next;
                }

                if (!found) {
                    cout << "Account not found.\n";
                }
                break;
            }

            case 4: {
                int accNo, pin;
                double amount;
                cout << "Enter Account Number: ";
                cin >> accNo;

                BankAccount* current = head;
                bool found = false;

                while (current != 0) {
                    if (current->getAccountNumber() == accNo) {
                        cout << "Enter 4-digit PIN: ";
                        cin >> pin;

                        if (current->verifyPIN(pin)) {
                            cout << "Enter amount to withdraw: ";
                            cin >> amount;
                            current->withdraw(amount);
                        } else {
                            cout << "Incorrect PIN.\n";
                        }
                        found = true;
                        break;
                    }
                    current = current->next;
                }

                if (!found) {
                    cout << "Account not found.\n";
                }
                break;
            }

            case 5:
                cout << "Exiting program. Total balance in the bank: $" << totalBankBalance << "\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (option != 5);

    while (head != 0) {
        BankAccount* temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}
