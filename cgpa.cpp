// cgpa.cpp
#include "cgpa.h"
#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

void cgpa::calculate() {
    int n; cout << "\n--- CGPA (Decimal Enabled) ---\nCourses: ";
    if (!(cin >> n)) { cin.clear(); cin.ignore(1000, '\n'); return; }
    double pts = 0, crd = 0;
    for (int i = 0; i < n; i++) {
        double g, c;
        cout << "Course " << i+1 << " Grade (0.00): "; cin >> g;
        cout << "Course " << i+1 << " Credits: "; cin >> c;
        pts += (g * c); crd += c;
    }
    if (crd > 0) cout << fixed << setprecision(2) << "[Success] CGPA: " << (pts / crd) << endl;
}