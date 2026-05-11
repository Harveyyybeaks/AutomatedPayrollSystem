#include <iostream>
#include <string>
#include <algorithm>
#include <ctime>
using namespace std;

const int MAX = 100;

int emp_id[MAX];
string emp_name[MAX], emp_department[MAX], emp_position[MAX], emp_status[MAX], emp_contact[MAX], emp_isMonthlyDaily1, emp_id1, rateInput, input;
string att_timeIn[MAX], att_timeOut[MAX], payroll_date[MAX];
double emp_rate[MAX];
bool emp_isMonthlyDaily[MAX];
int att_daysWorked[MAX];
double att_regularHours[MAX], att_overtimeHours[MAX];
int att_absences[MAX];
int att_lateMinutes[MAX];
double allw_transport[MAX], allw_meal[MAX], allw_incentive[MAX], allw_others[MAX];
double ded_loans[MAX], ded_tax[MAX], ded_sss[MAX], ded_philhealth[MAX], ded_pagibig[MAX];
double ded_cashAdvance[MAX], ded_others[MAX];
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
bool isValidNumber (string text) {
    return all_of(text.begin(), text.end(), ::isdigit);
}
bool isValidDecimal(string text) {
    bool hasDecimal = false;
    for (char c : text) {
        if (c == '.') {
            if (hasDecimal)
                return false;
            hasDecimal = true;
        }
        else if (!isdigit(c)) {
            return false;
        }
    }
    return !text.empty();
}
void addEmployee() {
    cin.ignore();
    if (empCount >= MAX) return;
    while (true) {
        cout << "\nEnter ID: ";
        getline(cin, emp_id1);
        
       if (emp_id1.empty()) {
          cout << "ID cannot be empty!\n";
          continue;
       }
       if (isValidNumber(emp_id1)) {
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
    
    while (true) {
        cout << "Full Name: ";
        getline(cin, emp_name[empCount]);
        
        if (emp_name[empCount].empty()) {
            cout << "Full name cannot be empty!\n";
        }
        else if (isValidText(emp_name[empCount]) && !emp_name[empCount].empty()) {
            break;
        }
        else {
            cout << "Invalid Input!\n";
            }
    }
    
    while (true) {
        cout << "Department: ";
        getline(cin, emp_department[empCount]);
        
        if (emp_department[empCount].empty()) {
            cout << "Department cannot be empty!\n";
        }
        else if (isValidText(emp_department[empCount]) && !emp_department[empCount].empty()) {
            break;
        }    
        else {
            cout << "Invalid Input!\n";
        }    
    }
    
    while (true) {
        cout << "Position: ";
        getline(cin, emp_position[empCount]);
        
        if (emp_position[empCount].empty()) {
            cout << "Position cannot be empty!\n";
        }
        else if (isValidText(emp_position[empCount]) && !emp_position[empCount].empty()) {
            break;
        }
        else {
            cout << "Invalid Input!\n";
        }
    }
    
    while (true) {
        cout << "Status: ";
        getline(cin, emp_status[empCount]);
        
        if (emp_status[empCount].empty()) {
            cout << "Status cannot be empty!\n";
        }
        else if (isValidText(emp_status[empCount]) && !emp_status[empCount].empty()) {
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
        getline(cin, rateInput);
        
        if (rateInput.empty()) {
            cout << "Rate cannot be empty!\n";
        }
        else {
        bool isValidRate = all_of(rateInput.begin(), rateInput.end(), [](char c) {return isdigit(c) || c == '.';});
        if (isValidRate) {
            emp_rate[empCount] = stod(rateInput);
            break;
        }
        else {
            cout << "Invalid Input!\n";
        }
        }
    }
    
    while (true) {
        cout << "1-Monthly / 0-Daily: ";
        getline(cin, emp_isMonthlyDaily1); 
        
        if (emp_isMonthlyDaily1.empty()) {
            cout << "Monthly/Daily cannot be empty!\n";
            continue;
        }
        else {
        bool isPureNumber = all_of(emp_isMonthlyDaily1.begin(), emp_isMonthlyDaily1.end(), ::isdigit);
        if (emp_isMonthlyDaily1 == "1" || emp_isMonthlyDaily1 == "0") {
            break;
        }
        else {
            cout << "Invalid Input! Please enter only '1' for Monthly or '0' for Daily.\n";
        }
        }
        }
    if (isValidNumber) {
        emp_isMonthlyDaily[empCount] = stoi(emp_isMonthlyDaily1);
    }
    
    empCount++;
    cout << "Employee added!\n";
}
void inputAttendance(int i) {
    cin.ignore();
    while (true) {
    string input;
        cout << "\nDays Worked: "; 
        getline(cin, input);
        
        if (input.empty()) {
            cout << "Days worked cannot be empty!\n";
        }
        else if (!isValidNumber(input)) {
            cout << "Invalid Input! Please enter only numbers\n";
        }
        else {
            att_daysWorked[i] = stoi(input);
            break;
        }
    }
    
    while (true) {
    string input1;
        cout << "Regular Hours: "; 
        getline(cin, input1);
        
        if (input1.empty()) {
            cout << "Regular hours cannot be empty!\n";
        }
        else if (!isValidDecimal(input1)) {
            cout << "Invalid Input! Please enter only numbers.\n";
        }
        else {
            att_regularHours[i] = stod(input1);
            break;
        }
    }
    
    while (true) {
    string input2;
        cout << "Overtime Hours: "; 
        getline(cin, input2);
        
        if (input2.empty()) {
            cout << "Overtime hours cannot be empty!\n";
        }
        else if (!isValidDecimal(input2)) {
            cout << "Invalid Input! Please enter only numbers.\n";
        }
        else {
            att_overtimeHours[i] = stod(input2);
            break;
        }
    }
    
    while (true) {
    string input3;
        cout << "Absences: ";
        getline(cin, input3);
        
        if (input3.empty()) {
            cout << "Absences cannot be empty!\n";
        }
        else if (!isValidNumber(input3)) {
            cout << "Invalid Input! Please enter only numbers.\n";
        }
        else {
            att_absences[i] = stoi(input3);
            break;
        }
    }
    
    while (true) {
    string input4;
       cout << "Late Minutes: "; 
       getline(cin, input4);
       
       if (input4.empty()) {
           cout << "Late minutes cannot be empty!\n";
       }
       else if (!isValidNumber(input4)) {
           cout << "Invalid Input! Please enter only numbers.\n";
       }
       else {
           att_lateMinutes[i] = stoi(input4);
           break;
       }
    }
    
    time_t now = time(0);
    att_timeIn[i] = ctime(&now);
    att_timeIn[i].erase(remove(att_timeIn[i].begin(), att_timeIn[i].end(), '\n'), att_timeIn[i].end());
        cout << "Time In Recorded: " << att_timeIn[i] << endl;
}    
void inputAllowance(int i) {
    while (true) {
    string input6;
        cout << "\nTransport: "; 
        getline(cin, input6);
        
        if (input6.empty()) {
            cout << "Transport hours cannot be empty!\n";
        }
        else if (!isValidDecimal(input6)) {
            cout << "Invalid Input! Please enter only numbers.\n";
        }
        else {
            allw_transport[i] = stod(input6);
            break;
        }
    }
    
    while (true) {
    string input7;
        cout << "Meal: ";
        getline(cin, input7);
        
        if (input7.empty()) {
            cout << "Meal cannot be empty!\n";
        }
        else if (!isValidDecimal(input7)) {
            cout << "Invalid Input! Please enter only numbers.\n";
        }
        else {
            allw_meal[i] = stod(input7);
            break;
        }
        
    }
    
    while (true) {
    string input8;
        cout << "Incentive: "; 
        getline(cin, input8);
        
        if (input8.empty()) {
            cout << "Incentive cannot be empty!\n";
        }
        else if (!isValidDecimal(input8)) {
            cout << "Invalid Input! Please enter only numbers.\n";
        }
        else {
            allw_incentive[i] = stod(input8);
            break;
        }
    }
    
    while (true) {
    string input9;
        cout << "Others: "; 
        getline(cin, input9);
        
        if (input9.empty()) {
            cout << "Others cannot be empty!\n";
        }
        else if (!isValidDecimal(input9)) {
            cout << "Invalid Input! Please enter only numbers.\n";
        }
        else {
            allw_others[i] = stod(input9);
            break;
        }
    }
}
void computeDeductions(int i) {
    double basic = pay_gross[i];

    ded_sss[i] = basic * 0.045;
    ded_philhealth[i] = basic * 0.02;
    ded_pagibig[i] = 100;

    ded_tax[i] = computeTax(basic);

    while (true) {
    string input10;
        cout << "Loans: "; 
        getline(cin, input10);
        
        if (input10.empty()) {
            cout << "Loans cannot be empty!\n";
        }
        else if (!isValidDecimal(input10)) {
            cout << "Invalid Input! Please enter only numbers.\n";
        }
        else {
            ded_loans[i] = stod(input10);
            break;
        }
    }
    
    while (true) {
    string input11;
        cout << "Cash Advance: "; 
        getline(cin, input11);
        
        if (input11.empty()) {
            cout << "Cash advance cannot be empty!\n";
        }
        else if (!isValidDecimal(input11)) {
            cout << "Invalid Input! Please enter only numbers.\n";
        }
        else {
            ded_cashAdvance[i] = stod(input11);
            break;
        }
    }
    
    while (true) {
    string input12;
        cout << "Other deductions: "; 
        getline(cin, input12);
        
        if (input12.empty()) {
            cout << "Other deductions cannot be empty!\n";
        }
        else if (!isValidDecimal(input12)) {
            cout << "Invalid Input! Please enter only numbers.\n";
        }
        else {
            ded_others[i] = stod(input12);
            break;
        }
    }

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

    pay_gross[i] = basic + overtimePay;

    pay_totalAllowance[i] = allw_transport[i] + allw_meal[i] +
                            allw_incentive[i] + allw_others[i];

    computeDeductions(i);

    pay_totalDeduction[i] =
        ded_tax[i] + ded_sss[i] + ded_philhealth[i] +
        ded_pagibig[i] + ded_loans[i] + ded_cashAdvance[i] +
        ded_others[i] + lateDeduction;

    pay_net[i] = pay_gross[i] + pay_totalAllowance[i] - pay_totalDeduction[i];
}
void payslip(int i) {
    cout << "\n===== PAYSLIP =====\n";
    cout << "Name: " << emp_name[i] << endl;
    cout << "Department: " << emp_department[i] << endl;
    
    cout << "\n--- Deductions ---\n";
    cout << "SSS: " << ded_sss[i] << endl;
    cout << "PhilHealth: " << ded_philhealth[i] << endl;
    cout << "Pag-ibig: " << ded_pagibig[i] << endl;
    cout << "Tax: " << ded_tax[i] << endl;
    
    cout << "\nGross Pay: " << pay_gross[i] << endl;
    cout << "Allowances: " << pay_totalAllowance[i] << endl;
    cout << "Total Deductions: " << pay_totalDeduction[i] << endl;
    cout << "Net Pay: " << pay_net[i] << endl;
}
void searchEmployee() {
    int id;
    cout << "Enter Employee ID: ";
    cin >> id;

    bool found = false;
    for (int i = 0; i < empCount; i++) {
        if (emp_id[i] == id) {
            cout << "Found: " << emp_name[i] << endl;
            payslip(i);
            found = true;
            return;
        }
    }
    if (!found) {
        cout << "Not found!\n";
    }
}
void viewEmployees (int i) {
    cout << "ID: " << emp_id[i] << endl;
    cout << "Full Name: " << emp_name[i] << endl;
    cout << "Department: " << emp_department[i] << endl;
    
    cout << "Time In: ";
    if (att_timeIn[i].empty()) cout << "NOT SET";
    else cout << att_timeIn[i];
    cout << endl;
    
    cout << "Time Out: ";
    if (att_timeOut[i].empty()) cout << "NOT SET";
    else cout << att_timeOut[i];
    cout << endl;
    
    cout << "Payroll Date: ";
    if (payroll_date[i].empty()) cout << "NOT SET";
    else cout << payroll_date[i];
    cout << endl;
}
void setTimeOutAndPayrollDate(int i) {
    time_t now = time(0);

    att_timeOut[i] = ctime(&now);
    att_timeOut[i].erase(remove(att_timeOut[i].begin(), att_timeOut[i].end(), '\n'), att_timeOut[i].end());
    payroll_date[i] = att_timeOut[i];
}
int main() {
    int choice;
    string input;

    do {
        cout << "\n=== AUTOMATED PAYROLL SYSTEM ===\n";
        cout << "1. Add Employee\n";
        cout << "2. Process Payroll\n";
        cout << "3. Search Employee\n";
        cout << "4. View Employees\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        
        cin.ignore();
        getline (cin, input);
        if (input.empty()) {
            cout << "Input cannot be empty!\n";
            continue;
        }    
        bool isPureNumber = all_of (input.begin(), input.end(), ::isdigit);
        if (isPureNumber) {
            choice = stoi (input);
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
                setTimeOutAndPayrollDate(i);
                payslip(i);
            }
            break;
        case 3:
            searchEmployee();
            break;
        case 4:
            cout << "\n==== Employees ====\n";
            for (int i = 0; i < empCount; i++) {
            viewEmployees(i);
            }
            break;
        case 0:
            cout << "\nThank you for using our system!\n";  
            break;  
        default:
           cout << "Invalid Choice!" << endl;
        }
    } 
       while (choice != 0);
          
    return 0;
}