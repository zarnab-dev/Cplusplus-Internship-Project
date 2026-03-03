#include "bankingsystem.h"
#include <iostream>
#include <iomanip>
#include <limits>

using namespace std;

bankingsystem::bankingsystem(int id) : account_id(id), balance(500.0) {}

void bankingsystem::deposit() {
    double amt;
    cout << "Enter deposit amount: ";
    if (!(cin >> amt) || amt <= 0) {
        cout << "[Error] Invalid numeric value entered." << endl;
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    balance += amt;
    history.push_back({"Deposit", amt}); // Logs to history
    cout << "[Success] Amount credited to your account." << endl;
}

void bankingsystem::withdraw() {
    double amt;
    cout << "Enter withdrawal amount: ";
    if (!(cin >> amt) || amt <= 0) {
        cout << "[Error] Invalid numeric value entered." << endl;
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    if (amt <= balance) {
        balance -= amt;
        history.push_back({"Withdrawal", amt}); // Logs to history
        cout << "[Success] Amount debited from your account." << endl;
    } else {
        cout << "[Error] Insufficient funds." << endl;
    }
}

void bankingsystem::transfer(vector<bankingsystem>& all_accounts) {
    int target;
    const double fee = 1.00;
    cout << "\n--- SECURE FUND TRANSFER ---" << endl;
    cout << "Enter Recipient ID (10000-99999): "; 
    if (!(cin >> target)) {
        cout << "[Error] Invalid character entered." << endl;
        cin.clear(); cin.ignore(1000, '\n'); return;
    }

    if (target < 10000 || target > 99999 || target == account_id) {
        cout << "[Error] Invalid ID. Must be 5 digits and not your own." << endl;
        return;
    }

    bankingsystem* rec = nullptr;
    for (auto& acc : all_accounts) {
        if (acc.get_id() == target) { rec = &acc; break; }
    }

    if (!rec) {
        all_accounts.push_back(bankingsystem(target));
        rec = &all_accounts.back();
    }

    double amt; cout << "Amount to transfer: ";
    if (!(cin >> amt)) { cin.clear(); cin.ignore(1000, '\n'); return; }

    if (amt > 0 && (amt + fee) <= balance) {
        balance -= (amt + fee);
        rec->balance += amt;
        history.push_back({"Transfer Out", amt});
        history.push_back({"Service Fee", fee});
        rec->history.push_back({"Transfer In", amt});
        cout << "[Success] Transfer successful." << endl;
    } else {
        cout << "[Error] Insufficient balance." << endl;
    }
}

void bankingsystem::showstatus() const {
    cout << "\n==========================================" << endl;
    cout << "         OFFICIAL BANK STATEMENT          " << endl;
    cout << "==========================================" << endl;
    cout << " ACCOUNT ID: " << account_id << endl;
    cout << " CURRENT BALANCE: $" << fixed << setprecision(2) << balance << endl;
    cout << "------------------------------------------" << endl;
    cout << left << setw(20) << "TRANSACTION TYPE" << " | " << "AMOUNT" << endl;
    cout << "------------------------------------------" << endl;
    
    if (history.empty()) {
        cout << " No transactions recorded yet." << endl;
    } else {
        for (const auto& t : history) {
            cout << left << setw(20) << t.type << " | $" << t.amount << endl;
        }
    }
    cout << "==========================================" << endl;
}