#include <iostream>
#include <vector>
#include <fstream>
#include <limits>
#include "authsystem.h"
#include "bankingsystem.h"
#include "cgpa.h"

using namespace std;

int main() {
    authsystem auth;
    cgpa calc;
    vector<bankingsystem> bank_db;

    // Load Database
    ifstream file("users.txt");
    if (file.is_open()) {
        string tu, tp; int tid;
        while (file >> tu >> tp >> tid) bank_db.push_back(bankingsystem(tid));
        file.close();
    }

    while (true) {
        cout << "\n==========================================" << endl;
        cout << "       WELCOME TO THE CORPORATE PORTAL    " << endl;
        cout << "==========================================" << endl;
        cout << "1. REGISTER\n2. LOGIN\n3. FORGOT PASSWORD (RECOVERY)\n4. CHANGE PASSWORD\n5. EXIT" << endl;
        cout << "\nPlease select the prefer choice: ";
        
        int choice;
        if (!(cin >> choice)) {
            cout << "\n[Error] Invalid character entered. Please select the prefer choice." << endl;
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); continue;
        }

        if (choice == 5) {
            cout<<"\n----------System Terminated!-----------\n";
        break;
        } // Exit shifted to 5

        if (choice == 1) {
            int nid = auth.registeruser();
            if (nid > 0) bank_db.push_back(bankingsystem(nid));
            continue;
        }

        if (choice == 3) { auth.forgotpassword(); continue; }
        
        if (choice == 4) { auth.changepassword(); continue; } // New Option

        if (choice == 2) {
            int attempts = 0;
            bool login_active = true;
            while (login_active) {
                int result = auth.loginuser();
                if (result >= 10000) {
                    login_active = false;
                    bankingsystem* user = nullptr;
                    for (auto& acc : bank_db) if (acc.get_id() == result) { user = &acc; break; }
                    if (!user) { bank_db.push_back(bankingsystem(result)); user = &bank_db.back(); }

                    int menu = 0;
                    while (menu != 5) {
                        cout << "\n--- DASHBOARD ID: " << user->get_id() << " ---" << endl;
                        cout << "1. BANKING\n2. TRANSFER\n3. HISTORY\n4. CGPA\n5. LOGOUT" << endl;
                        cout << "\nPlease select the prefer choice: ";
                        if (!(cin >> menu)) { cin.clear(); cin.ignore(1000, '\n'); continue; }

                        if (menu == 1) {
                            bool in_bank = true;
                            while(in_bank) {
                                cout << "\n--- BANKING OPERATIONS ---\n1. DEPOSIT\n2. WITHDRAW\n3. BACK\nChoice: ";
                                int bc; cin >> bc;
                                if (bc == 1) { user->deposit(); in_bank = false; }
                                else if (bc == 2) { user->withdraw(); in_bank = false; }
                                else if (bc == 3) in_bank = false;
                                else cout << "[Error] Invalid number entered. Please select the prefer choice." << endl;
                            }
                        }
                        else if (menu == 2) user->transfer(bank_db);
                        else if (menu == 3) user->showstatus();
                        else if (menu == 4) calc.calculate();
                    }
                } 
                else if (result == -2) { auth.forgotpassword(); login_active = false; } 
                else if (result == -1) {
                    attempts++;
                    if (attempts >= 3) {
                        cout << "\n[SECURITY ALERT] 3 failed attempts. LOCKED." << endl;
                        login_active = false; 
                    } else cout << "[Warning] " << (3 - attempts) << " attempt(s) left." << endl;
                }
            }
        } else if (choice < 1 || choice > 5) {
            cout << "\n[Error] Invalid number entered. Please select the prefer choice." << endl;
        }
    }
    return 0;
}