#include <iostream>
using namespace std;

int main () 
{
    const int MAX = 100;
    int choice, id[MAX], countEmp = 0, dayRate[MAX], daysW[MAX];
    double overTime[MAX], allowance[MAX], lateDeduc[MAX], loan[MAX], gross[MAX], net[MAX];
    string fullN[MAX], dept[MAX], position[MAX], EmpStatus[MAX];
    double sss[MAX], philhealth[MAX], pagibig[MAX], tax[MAX], totalDeduc[MAX];
  
do {    
    cout << "" << endl;
    cout << "======Automated Payroll System======" << endl;
    cout << "1. Add Employee" << endl;
    cout << "2. View Employees" << endl;
    cout << "3. Process Payroll" << endl;
    cout << "4. Search Employee" << endl;
    cout << "5. Sort by Name" << endl;
    cout << "6. Add Loan" << endl;
    cout << "7. Payroll Report" << endl;
    cout << "8. Exit" << endl;
    cout << "Choice: ";
    cin >> choice;
  
    if (choice == 1)
    {
      if (countEmp >= MAX)
      {
      cout << "Limit Reached!";
      continue;
      }
      cout << "\nEnter ID: ";
      cin >> id[countEmp];
      
      cin.ignore ();
      cout << "Full Name: ";
      getline(cin, fullN[countEmp]);
      cout << "Department: ";
      getline(cin, dept[countEmp]);
      cout << "Position: ";
      getline(cin, position[countEmp]);
      cout << "Employment Status: ";
      cin >> EmpStatus[countEmp];
      cout << "Daily Rate: ";
      cin >> dayRate[countEmp];
      cout << "Days Worked: ";
      cin >> daysW[countEmp];
      cout << "Overtime Hours: ";
      cin >> overTime[countEmp];
      cout << "Allowances: ";
      cin >> allowance[countEmp];
      cout << "Late Deductions: ";
      cin >> lateDeduc[countEmp];
      cout << "Loan: ";
      cin >> loan[countEmp];
      
      double otRate = (dayRate[countEmp] / 8) * 1.25;
        gross[countEmp] = (daysW[countEmp] * overTime[countEmp]) +
        (lateDeduc[countEmp] * otRate) +
        allowance[countEmp];
        
        sss[countEmp] = gross[countEmp] * 0.045;
        philhealth[countEmp] = gross[countEmp] * 0.02;
        pagibig[countEmp] = 100; 
        
        if (gross[countEmp] <= 20000)
          tax[countEmp] = 0;
          
          else if (gross[countEmp] <= 40000)
            tax[countEmp] = (gross[countEmp] - 20000) * 0.20;
            
          else
            tax[countEmp] = (gross[countEmp] - 40000) * 0.25 + 4000; 
            
        totalDeduc[countEmp] = sss[countEmp] + philhealth[countEmp] + pagibig[countEmp] + tax[countEmp] + lateDeduc[countEmp] + loan[countEmp];   
        
        net[countEmp] = gross[countEmp] - totalDeduc[countEmp];
        countEmp++;
        
        cout << "\nAdded Employee!" << endl;
    }
      else if (choice == 2) {
        
        if (countEmp == 0) {
          cout << "\nNot found!";
          continue;
        }
        for (int i = 0; i < countEmp; i++) {
          cout << "" << endl;         
          cout << "======View Employees======" << endl;
          cout << "ID: " << id[i];
          cout << "| Name: " << fullN[i];
          cout << "| Net Pay: " << net[i];
          cout << "\n";
        }
        }
    }
while (choice != 8);

return 0;
}
