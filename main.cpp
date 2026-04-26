#include <iostream>
#include <string>
using namespace std;

const int MAX = 100;

struct Employee {
    int id;
    string name, department, position, status, contact;
    double rate;
    bool isMonthly;
};

struct Attendance {
    int daysWorked;
    double regularHours, overtimeHours;
    int absences;
    int lateMinutes;
    double undertimeHours;
};

struct Allowance {
    double transport, meal, incentive, others;
};

struct Deduction {
    double tax, sss, philhealth, pagibig, loans, cashAdvance, others;
};

struct Payroll {
    double gross, totalDeduction, totalAllowance, net;
};

Employee emp[MAX];
Attendance att[MAX];
Allowance allw[MAX];
Deduction ded[MAX];
Payroll pay[MAX];

int empCount = 0;

double computeTax(double salary) {
    if (salary <= 20833) return 0;
    else if (salary <= 33333) return (salary - 20833) * 0.20;
    else return 2500 + (salary - 33333) * 0.25;
}
void addEmployee() {
    if (empCount >= MAX) return;

    cout << "\nEnter Employee ID: ";
    cin >> emp[empCount].id;
    
    for (int i = 0; i < empCount; i++) {
        if (emp[i].id == emp[empCount].id) {
            cout << "Duplicate ID!\n";
            return;
        }
    }
    cin.ignore();
    cout << "Full Name: ";
    getline(cin, emp[empCount].name);

    cout << "Department: ";
    getline(cin, emp[empCount].department);

    cout << "Position: ";
    getline(cin, emp[empCount].position);

    cout << "Status (Active/Inactive): ";
    getline(cin, emp[empCount].status);

    cout << "Contact: ";
    getline(cin, emp[empCount].contact);

    cout << "Rate: ";
    cin >> emp[empCount].rate;

    cout << "1-Monthly / 0-Daily: ";
    cin >> emp[empCount].isMonthly;

    empCount++;
    cout << "Employee added!\n";
}
void inputAttendance(int i) {
    cout << "\nDays Worked: "; cin >> att[i].daysWorked;
    cout << "Regular Hours: "; cin >> att[i].regularHours;
    cout << "Overtime Hours: "; cin >> att[i].overtimeHours;
    cout << "Absences: "; cin >> att[i].absences;
    cout << "Late Minutes: "; cin >> att[i].lateMinutes;
    cout << "Undertime Hours: "; cin >> att[i].undertimeHours;
}
void inputAllowance(int i) {
    cout << "\nTransport: "; cin >> allw[i].transport;
    cout << "Meal: "; cin >> allw[i].meal;
    cout << "Incentive: "; cin >> allw[i].incentive;
    cout << "Others: "; cin >> allw[i].others;
}
void computeDeductions(int i) {
    double basic = pay[i].gross;

    ded[i].sss = basic * 0.045;
    ded[i].philhealth = basic * 0.02;
    ded[i].pagibig = 100;

    ded[i].tax = computeTax(basic);

    cout << "Loans: "; cin >> ded[i].loans;
    cout << "Cash Advance: "; cin >> ded[i].cashAdvance;
    cout << "Other deductions: "; cin >> ded[i].others;

    if (ded[i].loans < 0 || ded[i].cashAdvance < 0) {
        cout << "Invalid deduction!\n";
        ded[i].loans = ded[i].cashAdvance = 0;
    }
}
void computePayroll(int i) {
    double basic;

    if (emp[i].isMonthly)
        basic = emp[i].rate;
    else
        basic = emp[i].rate * att[i].daysWorked;

    double overtimePay = att[i].overtimeHours * (emp[i].rate / 8) * 1.25;

    double lateDeduction = (att[i].lateMinutes / 60.0) * (emp[i].rate / 8);
    double undertimeDeduction = att[i].undertimeHours * (emp[i].rate / 8);

    pay[i].gross = basic + overtimePay;

    pay[i].totalAllowance = allw[i].transport + allw[i].meal +
                            allw[i].incentive + allw[i].others;

    computeDeductions(i);

    pay[i].totalDeduction =
        ded[i].tax + ded[i].sss + ded[i].philhealth +
        ded[i].pagibig + ded[i].loans + ded[i].cashAdvance +
        ded[i].others + lateDeduction + undertimeDeduction;

    pay[i].net = pay[i].gross + pay[i].totalAllowance - pay[i].totalDeduction;
}
void payslip(int i) {
    cout << "\n===== PAYSLIP =====\n";
    cout << "Name: " << emp[i].name << endl;
    cout << "Department: " << emp[i].department << endl;
    cout << "Gross Pay: " << pay[i].gross << endl;
    cout << "Allowances: " << pay[i].totalAllowance << endl;
    cout << "Deductions: " << pay[i].totalDeduction << endl;
    cout << "Net Pay: " << pay[i].net << endl;
}
void searchEmployee() {
    int id;
    cout << "Enter ID: ";
    cin >> id;

    for (int i = 0; i < empCount; i++) {
        if (emp[i].id == id) {
            cout << "Found: " << emp[i].name << endl;
            payslip(i);
            return;
        }
    }
    cout << "Not found!\n";
}
void dashboard() {
    double totalGross = 0, totalDed = 0, totalNet = 0;

    for (int i = 0; i < empCount; i++) {
        totalGross += pay[i].gross;
        totalDed += pay[i].totalDeduction;
        totalNet += pay[i].net;
    }

    cout << "\n===== DASHBOARD =====\n";
    cout << "Total Employees: " << empCount << endl;
    cout << "Total Gross: " << totalGross << endl;
    cout << "Total Deduction: " << totalDed << endl;
    cout << "Total Net: " << totalNet << endl;
}
int main() {
    int choice;

    do {
        cout << "\n=== AUTOMATED PAYROLL SYSTEM ===\n";
        cout << "1. Add Employee\n";
        cout << "2. Process Payroll\n";
        cout << "3. Search Employee\n";
        cout << "4. Dashboard\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch(choice) {
        case 1:
            addEmployee();
            break;
        case 2:
            for (int i = 0; i < empCount; i++) {
                cout << "\nProcessing: " << emp[i].name << endl;
                inputAttendance(i);
                inputAllowance(i);
                computePayroll(i);
                payslip(i);
            }
            break;
        case 3:
            searchEmployee();
            break;
        case 4:
            dashboard();
            break;
        }
    } while(choice != 0);

    return 0;
}
            

