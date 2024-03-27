/*
 CIS22B
 01/30/23
 Assignment #2
 
 This program saves students' information at a school. The user will be
 prompted to enter the number of students, each student’s name, how many
 tests the student has taken, and the grade for each test. Once each
 student’s information has been entered, the program will display the
 number of students. Additionally, each student will have their name,
 list of test scores displayed.
*/

#include <iostream>
using namespace std;

//Function prototypes
int inputData(string*& names, double**& grades);
void displayData(string* names, double** grades, int numstudents);
void cleanHeap(string* names, double** grades, int numstudents);

// ===========================================================
//                        main function
//
// 1)Parameters: none
// 2)Returns: integer 0
// 3)Summary: Calls functions to obtain user input on number
//   of students,their names, number of tests, and test scores
// ===========================================================
int main() {
    
    string *names = nullptr;
    double **grades = nullptr;
    int numstudents = inputData(names, grades);
    displayData(names, grades, numstudents);
    cleanHeap(names, grades, numstudents);

    return 0;
}

// =================================================
//                    inputData
//
// 1)Parameters: a string pointer and a pointer to a
//          double pointer, both passed by reference
// 2)Returns: integer number of students
// 3)Summary: inputs the number of students, their
//          names, numer of tests, and grades
// =================================================
int inputData(string*& names, double**& grades)
{
    int numstudents = 0, tests = 0;
    
    //validate number of students, must be (+)
    while(numstudents <= 0)
    {
        cout << "How many students do you have in the system? ";
        cin >> numstudents;

        if (numstudents <= 0)
            cout << "\nPlease enter valid number of students\n" << endl;
    }
    
    //dynamically allocate array of student names
    //                   & array of pointers
    names = new string[numstudents];
    grades = new double*[numstudents];
    
    //request each student's info
    for (int i=0; i < numstudents; ++i)
    {
        cout << "\nEnter the student's name: ";
        getline(cin >> ws, *(names+i) );
        
        //validate number of tests, must be (+)
        while (tests <= 0)
        {
            cout << "\nEnter how many tests " << *(names+i) << " took: ";
            cin >> tests;

            if (tests <= 0)
                cout<<"\nPlease enter a positive number of tests taken"<<endl;
        }

        //save array of grades in ptr array
        //& save number of tests in 1st element
        *(grades+i) = new double[tests+1];
        **(grades+i) = tests;
        
        //validate grades, must be within (0-100)
        int j=1;
        while(j <= tests)
        {
            cout << "\nEnter grade #" << j << ": ";
            cin >> *(*(grades+i)+j);
            
            if (*(*(grades+i)+j) < 0 || *(*(grades+i)+j) > 100){
                cout << "\nPlease enter a grade between 0 and 100" << endl;
            }
            else
                ++j;
        }
    }
    return numstudents;
}

// =================================================================
//                           displayData
//
// 1)Parameters: a pointer to array of student names, a pointer to
//               array of test scores, and the number of students
// 2)Returns: none
// 3)Summary: display the number of students, and each student's
//            name and test scores
// =================================================================
void displayData(string* names, double** grades, int numstudents)
{
    cout <<"\n\nYou have "<<numstudents<<" students in the system."<<endl;
    
    //loop through each student
    for (int i=0; i < numstudents; ++i)
    {
        cout << "\nName of student #" << i+1 << ": " << *(names+i) << endl;
        cout << "\nGrades for student #" << i+1 << ": ";
        
        //loop through each grade
        for (int j=1; j <= **(grades+i); ++j){
            cout << *(*(grades+i)+j) << " ";
        }
        cout << endl;
    }
}

// ==================================================================
//                          cleanHeap
//
// 1)Parameters: a pointer to array of student names, a pointer to
//               array of test scores, and the number of students
// 2)Returns: none
// 3)Summary: delete dynamically-allocated elements
// ==================================================================
void cleanHeap(string* names, double** grades, int numstudents)
{
    delete[] names;
    for(int i=0; i< numstudents; i++){ //check/count
        delete[] grades[i];
    }
    delete[] grades;
    
    names = nullptr;
    grades = nullptr;
}

/* SAMPLE RUN OF CODE
 How many students do you have in the system? -1

 Please enter valid number of students

 How many students do you have in the system? 3

 Enter the student's name: John B. Doe

 Enter how many tests John B. Doe took: -2

 Please enter a positive number of tests taken

 Enter how many tests John B. Doe took: 3

 Enter grade #1: -95.5

 Please enter a grade between 0 and 100

 Enter grade #1: 95.5

 Enter grade #2: 101

 Please enter a grade between 0 and 100

 Enter grade #2: 84.3

 Enter grade #3: 80

 Enter the student's name: Anna Mull

 Enter how many tests Anna Mull took: 3

 Enter grade #1: 60

 Enter grade #2: 55.9

 Enter grade #3: 77.4

 Enter the student's name: Paige

 Enter how many tests Paige took: -1

 Please enter a positive number of tests taken

 Enter how many tests Paige took: 2

 Enter grade #1: 75.6

 Enter grade #2: -10.3

 Please enter a grade between 0 and 100

 Enter grade #2: 50.5


 You have 3 students in the system.

 Name of student #1: John B. Doe

 Grades for student #1: 95.5 84.3 80

 Name of student #2: Anna Mull

 Grades for student #2: 60 55.9 77.4

 Name of student #3: Paige

 Grades for student #3: 75.6 50.5
 Program ended with exit code: 0
 */
