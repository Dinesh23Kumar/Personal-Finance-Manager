#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

class Transaction {
public:
    string type;
    string category;
    double amount;

    Transaction(string t, string c, double a) {
        type = t;
        category = c;
        amount = a;
    }
};

class FinanceManager {
private:
    vector<Transaction> transactions;
    double totalIncome = 0;
    double totalExpenses = 0;

public:
    void addIncome(double amount, string category) {
        transactions.push_back(Transaction("Income", category, amount));
        totalIncome += amount;
        cout << "Income added successfully.\n";
    }

    void addExpense(double amount, string category) {
        transactions.push_back(Transaction("Expense", category, amount));
        totalExpenses += amount;
        cout << "Expense added successfully.\n";
    }

    void showTransactions() {
        cout << "\nAll Transactions:\n";
        cout << "-------------------------------------------\n";
        cout << left << setw(10) << "Type" << setw(15) << "Category" << "Amount\n";
        cout << "-------------------------------------------\n";
        for (const auto &t : transactions) {
            cout << left << setw(10) << t.type << setw(15) << t.category << t.amount << "\n";
        }
        cout << "-------------------------------------------\n";
    }

    void showSummary() {
        double balance = totalIncome - totalExpenses;
        cout << "\nFinancial Summary:\n";
        cout << "------------------------\n";
        cout << "Total Income: " << totalIncome << "\n";
        cout << "Total Expenses: " << totalExpenses << "\n";
        cout << "Balance: " << balance << "\n";
        cout << "------------------------\n";
    }

    void saveToFile(const string& filename) {
        ofstream file(filename);
        if (file.is_open()) {
            for (const auto &t : transactions) {
                file << t.type << "," << t.category << "," << t.amount << "\n";
            }
            file.close();
            cout << "Transactions saved to file.\n";
        } else {
            cout << "Unable to open file.\n";
        }
    }

    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (file.is_open()) {
            transactions.clear();
            totalIncome = 0;
            totalExpenses = 0;

            string line, type, category;
            double amount;
            while (getline(file, line)) {
                size_t pos1 = line.find(',');
                size_t pos2 = line.rfind(',');

                type = line.substr(0, pos1);
                category = line.substr(pos1 + 1, pos2 - pos1 - 1);
                amount = stod(line.substr(pos2 + 1));

                transactions.push_back(Transaction(type, category, amount));
                if (type == "Income") {
                    totalIncome += amount;
                } else if (type == "Expense") {
                    totalExpenses += amount;
                }
            }
            file.close();
            cout << "Transactions loaded from file.\n";
        } else {
            cout << "Unable to open file.\n";
        }
    }
};

void displayMenu() {
    cout << "\n--- Personal Finance Manager ---\n";
    cout << "1. Add Income\n";
    cout << "2. Add Expense\n";
    cout << "3. Show All Transactions\n";
    cout << "4. Show Financial Summary\n";
    cout << "5. Save to File\n";
    cout << "6. Load from File\n";
    cout << "7. Exit\n";
    cout << "Choose an option: ";
}

int main() {
    FinanceManager manager;
    int choice;
    string category, filename;
    double amount;

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter income amount: ";
            cin >> amount;
            cout << "Enter income category: ";
            cin >> category;
            manager.addIncome(amount, category);
            break;

        case 2:
            cout << "Enter expense amount: ";
            cin >> amount;
            cout << "Enter expense category: ";
            cin >> category;
            manager.addExpense(amount, category);
            break;

        case 3:
            manager.showTransactions();
            break;

        case 4:
            manager.showSummary();
            break;

        case 5:
            cout << "Enter filename to save transactions: ";
            cin >> filename;
            manager.saveToFile(filename);
            break;

        case 6:
            cout << "Enter filename to load transactions: ";
            cin >> filename;
            manager.loadFromFile(filename);
            break;

        case 7:
            cout << "Exiting program.\n";
            break;

        default:
            cout << "Invalid option. Please try again.\n";
        }
    } while (choice != 7);

    return 0;
}
