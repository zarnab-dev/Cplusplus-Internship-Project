#include "authsystem.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <limits>
#include <vector>
#include <string>

using namespace std;

// Helper to check if username is already in file
bool authsystem::userexists(const string& username) {
    ifstream file("users.txt");
    if (!file) return false;
    string u, p; int id;
    while (file >> u >> p >> id) {
        if (u == username) return true;
    }
    return false;
}

int authsystem::registeruser() {
    string u, p;
    cout << "\n==========================================" << endl;
    cout << "          USER REGISTRATION               " << endl;
    cout << "==========================================" << endl;
    cout << "Enter Username: "; cin >> u;
    
    if (userexists(u)) {
        cout << "[Error] Username already taken." << endl;
        return 0;
    }
    
    cout << "Enter Password: "; cin >> p;

    srand(time(0));
    int assigned_id = rand() % 90000 + 10000;

    ofstream file("users.txt", ios::app);
    file << u << " " << p << " " << assigned_id << endl;
    file.close();
    
    cout << "\n------------------------------------------" << endl;
    cout << " SUCCESSFUL! ACCOUNT CREATED.            " << endl;
    cout << " YOUR GRANTED ID IS: " << assigned_id << endl;
    cout << "------------------------------------------" << endl;
    return assigned_id;
}

int authsystem::loginuser() {
    string u, p, fu, fp; int fid;
    cout << "\n--- Login Security ---" << endl;
    cout << "Username: "; cin >> u;
    cout << "Password: "; cin >> p;

    ifstream file("users.txt");
    if (file.is_open()) {
        while (file >> fu >> fp >> fid) {
            if (u == fu && p == fp) {
                file.close();
                return fid; 
            }
        }
        file.close();
    }

    cout << "\n[Error] Invalid credentials entered." << endl;
    cout << "1. Forgot password? Want to recover?" << endl;
    cout << "2. Try again to enter the right credentials" << endl;
    cout << "\nPlease select the prefer choice: ";
    
    int fail_choice;
    if (!(cin >> fail_choice)) {
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return -1; 
    }

    if (fail_choice == 1) return -2; 
    return -1; 
}

void authsystem::forgotpassword() {
    string input_u;
    int input_id;
    cout << "\n--- ACCOUNT RECOVERY ---" << endl;
    cout << "Enter Registered Username: "; cin >> input_u;
    cout << "Enter your 5-digit Account ID: "; 
    
    if (!(cin >> input_id)) {
        cout << "[Error] Invalid character entered." << endl;
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    ifstream file("users.txt");
    string fu, fp; int fid;
    bool found = false;
    while (file >> fu >> fp >> fid) {
        if (fu == input_u && fid == input_id) {
            cout << "\n------------------------------------------" << endl;
            cout << " RECOVERY SUCCESSFUL!" << endl;
            cout << " YOUR PASSWORD IS: " << fp << endl;
            cout << "------------------------------------------" << endl;
            found = true; break;
        }
    }
    file.close();
    if (!found) cout << "[Error] Recovery failed. Data mismatch." << endl;
}

void authsystem::changepassword() {
    string input_u, old_p, new_p;
    int input_id;
    cout << "\n--- SECURE PASSWORD CHANGE ---" << endl;
    cout << "Enter Username: "; cin >> input_u;
    cout << "Enter Current Password: "; cin >> old_p;
    cout << "Enter 5-digit Account ID: "; 
    
    if (!(cin >> input_id)) {
        cout << "[Error] Invalid character entered." << endl;
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    ifstream file("users.txt");
    if (!file) { cout << "[Error] Database file not found." << endl; return; }

    vector<string> lines;
    string fu, fp; int fid;
    bool found = false;

    while (file >> fu >> fp >> fid) {
        if (fu == input_u && fp == old_p && fid == input_id) {
            cout << "Enter New Password: "; cin >> new_p;
            // Reconstruct the line with the new password
            lines.push_back(fu + " " + new_p + " " + to_string(fid));
            found = true;
        } else {
            lines.push_back(fu + " " + fp + " " + to_string(fid));
        }
    }
    file.close();

    if (found) {
        ofstream outfile("users.txt");
        for (const auto& line : lines) {
            outfile << line << endl;
        }
        outfile.close();
        cout << "\n[Success] Password updated successfully!" << endl;
    } else {
        cout << "\n[Error] Verification failed. Details do not match." << endl;
    }
}