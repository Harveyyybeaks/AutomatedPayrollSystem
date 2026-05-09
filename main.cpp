#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

const int MAX = 100;

int emp_id[MAX];
string emp_name[MAX], emp_department[MAX], emp_position[MAX], emp_status[MAX], emp_contact[MAX], emp_isMonthlyDaily1, emp_id1, rateInput;
double emp_rate[MAX];
bool emp_isMonthlyDaily[MAX];
int att_daysWorked[MAX];
double att_regularHours[MAX], att_overtimeHours[MAX];
int att_absences[MAX];
int att_lateMinutes[MAX];
double att_undertimeHours[MAX];
double allw_transport[MAX], allw_meal[MAX], allw_incentive[MAX], allw_others[MAX];
double ded_tax[MAX], ded_sss[MAX], ded_philhealth[MAX], ded_pagibig[MAX];
double ded_loans[MAX], ded_cashAdvance[MAX], ded_others[MAX];
double pay_gross[MAX], pay_totalDeduction[MAX], pay_totalAllowance[MAX], pay_net[MAX];

int empCount = 0;

double computeTax(double salary) {
    if (salary <= 20833) return 0;
    else if (salary <= 33333) return (salary - 20833) * 0.20;
    else return 2500 + (salary - 33333) * 0.25;
}
bool isValidText (string text) {
    return all_of(text.begin(), text.end(), [](char c) {return isalpha(c) || isspace(c);});
}
bool isPureNumber (string text) {
    return all_of(text.begin(), text.end(), ::isdigit);
}
void addEmployee() {
    if (empCount >= MAX) return;

    while (true) {
        cout << "\nEnter Employee ID: ";
        cin >> emp_id1;
        
       if (isPureNumber) {

           emp_id[empCount] = stoi(emp_id1);

           bool duplicate = false;

           for (int i = 0; i < empCount; i++) {
                if (emp_id[i] == emp_id[empCount]) {
                    duplicate = true;
                    break;
               }
           }
           if (duplicate) {
                cout << "Duplicate ID!\n";
           }
           else {
               break;
           }
       }
       else {
           cout << "Invalid Input! Please enter only numbers.\n";
       }
    }
    cin.ignore();
    
    while (true) {
        cout << "Full Name: ";
        getline(cin, emp_name[empCount]);
        
        if (isValidText && !emp_name[empCount].empty()) {
            break;
        }
        else {
            cout << "Invalid Input!\n";
        }
    }
    
    while (true) {
        cout << "Department: ";
        getline(cin, emp_department[empCount]);
        
        if (isValidText && !emp_department[empCount].empty()) {
            break;
        }
        else {
            cout << "Invalid Input!\n";
        }
    }
    while (true) {
        cout << "Position: ";
        getline(cin, emp_position[empCount]);
        
        if (isValidText && !emp_position[empCount].empty()) {
            break;
        }
        else {
            cout << "Invalid Input!\n";
        }
    }

    while (true) {
        cout << "Status: ";
        getline(cin, emp_status[empCount]);
        
        if (isValidText && !emp_status[empCount].empty()) {
            break;
        }
        else {
            cout << "Invalid Input!\n";
        }
    }

    cout << "Contact: ";
    getline(cin, emp_contact[empCount]);

    while (true) {
        cout << "Rate: ";
        cin >> rateInput;
        
        bool validRate = all_of(rateInput.begin(), rateInput.end(), [](char c) {return isdigit(c) || c == '.';});
        if (validRate) {
            emp_rate[empCount] = stod(rateInput);
            break;
        }
        else {
            cout << "Invalid Input!\n";
        }
    }

    while (true) {
        cout << "1-Monthly / 0-Daily: ";
        cin >> emp_isMonthlyDaily1; 
        
        if (emp_isMonthlyDaily1 == "1" || emp_isMonthlyDaily1 == "0") {
            break;
        }
        else {
            cout << "Invalid Input! Please enter only '1' for Monthly or '0' for Daily.\n";
        }
        }
    if (isPureNumber) {
        emp_isMonthlyDaily[empCount] = stoi(emp_isMonthlyDaily1);
    }
    
    empCount++;
    cout << "Employee added!\n";
}
void inputAttendance(int i) {
    cout << "\nDays Worked: "; cin >> att_daysWorked[i];
    cout << "Regular Hours: "; cin >> att_regularHours[i];
    cout << "Overtime Hours: "; cin >> att_overtimeHours[i];
    cout << "Absences: "; cin >> att_absences[i];
    cout << "Late Minutes: "; cin >> att_lateMinutes[i];
    cout << "Undertime Hours: "; cin >> att_undertimeHours[i];
}
void inputAllowance(int i) {
    cout << "\nTransport: "; cin >> allw_transport[i];
    cout << "Meal: "; cin >> allw_meal[i];
    cout << "Incentive: "; cin >> allw_incentive[i];
    cout << "Others: "; cin >> allw_others[i];
}
void computeDeductions(int i) {
    double basic = pay_gross[i];

    ded_sss[i] = basic * 0.045;
    ded_philhealth[i] = basic * 0.02;
    ded_pagibig[i] = 100;

    ded_tax[i] = computeTax(basic);

    cout << "Loans: "; cin >> ded_loans[i];
    cout << "Cash Advance: "; cin >> ded_cashAdvance[i];
    cout << "Other deductions: "; cin >> ded_others[i];

    if (ded_loans[i] < 0 || ded_cashAdvance[i] < 0) {
        cout << "Invalid deduction!\n";
        ded_loans[i] = ded_cashAdvance[i] = 0;
    }
}
void computePayroll(int i) {
    double basic;

    if (emp_isMonthlyDaily[i])
        basic = emp_rate[i];
    else
        basic = emp_rate[i] * att_daysWorked[i];

    double overtimePay = att_overtimeHours[i] * (emp_rate[i] / 8) * 1.25;

    double lateDeduction = (att_lateMinutes[i] / 60.0) * (emp_rate[i] / 8);
    double undertimeDeduction = att_undertimeHours[i] * (emp_rate[i] / 8);

    pay_gross[i] = basic + overtimePay;

    pay_totalAllowance[i] = allw_transport[i] + allw_meal[i] +
                            allw_incentive[i] + allw_others[i];

    computeDeductions(i);

    pay_totalDeduction[i] =
        ded_tax[i] + ded_sss[i] + ded_philhealth[i] +
        ded_pagibig[i] + ded_loans[i] + ded_cashAdvance[i] +
        ded_others[i] + lateDeduction + undertimeDeduction;

    pay_net[i] = pay_gross[i] + pay_totalAllowance[i] - pay_totalDeduction[i];
}
void payslip(int i) {
    cout << "\n===== PAYSLIP =====\n";
    cout << "Name: " << emp_name[i] << endl;
    cout << "Department: " << emp_department[i] << endl;
    cout << "Gross Pay: " << pay_gross[i] << endl;
    cout << "Allowances: " << pay_totalAllowance[i] << endl;
    cout << "Deductions: " << pay_totalDeduction[i] << endl;
    cout << "Net Pay: " << pay_net[i] << endl;
}
void searchEmployee() {
    int id;
    cout << "Enter ID: ";
    cin >> id;

    for (int i = 0; i < empCount; i++) {
        if (emp_id[i] == id) {
            cout << "Found: " << emp_name[i] << endl;
            payslip(i);
            return;
        }
    }
    cout << "Not found!\n";
}
void dashboard() {
    double totalGross = 0, totalDed = 0, totalNet = 0;

    for (int i = 0; i < empCount; i++) {
        totalGross += pay_gross[i];
        totalDed += pay_totalDeduction[i];
        totalNet += pay_net[i];
    }
    cout << "\n===== DASHBOARD =====\n";
    cout << "Total Employees: " << empCount << endl;
    cout << "Total Gross: " << totalGross << endl;
    cout << "Total Deduction: " << totalDed << endl;
    cout << "Total Net: " << totalNet << endl;
}
int main() {
    int choice;
    string input;

    do {
        cout << "\n=== AUTOMATED PAYROLL SYSTEM ===\n";
        cout << "1. Add Employee\n";
        cout << "2. Process Payroll\n";
        cout << "3. Search Employee\n";
        cout << "4. Dashboard\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        
        cin >> input; 
        bool isPureNumber = all_of(input.begin(), input.end(), ::isdigit);

        if (isPureNumber) {
            choice = stoi(input);
            }

        switch(choice) {
        case 1:
            addEmployee();
            break;
        case 2:
            for (int i = 0; i < empCount; i++) {
                cout << "\nProcessing: " << emp_name[i] << endl;
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
        case 0:
            cout << "Thank you for using our system!\n";  
            break;  
        default:
           cout << "Invalid Choice!" << endl;
        }
    } 
       while (choice != 0);
          
    return 0;
}