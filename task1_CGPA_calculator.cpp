#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

// =========================
// Custom Exception Class
// =========================
class InputException
{
private:
    string message;

public:
    InputException(string msg)
    {
        message = msg;
    }

    string getMessage()
    {
        return message;
    }
};


// =========================
// Course Class
// =========================
class Course
{
private:
    string courseName;
    int creditHours;
    char grade;
    float gradePoint;

public:

    // Constructor
    Course()
    {
        courseName = "";
        creditHours = 0;
        grade = ' ';
        gradePoint = 0;
    }


    // Input Course Name
    void setCourseName()
    {
        cout << "Enter Course Name: ";
        cin >> courseName;

        if (courseName.empty())
        {
            throw InputException("Course name cannot be empty.");
        }
    }


    // Input Credit Hours
    void setCreditHours()
    {
        string input;

        cout << "Enter Credit Hours (1-6): ";
        cin >> input;

        // Check that every character is a digit
        for (int i = 0; i < input.length(); i++)
        {
            if (input[i] < '0' || input[i] > '9')
            {
                throw InputException("Credit hours must contain numbers only.");
            }
        }

        creditHours = stoi(input);

        if (creditHours < 1 || creditHours > 6)
        {
            throw InputException("Credit hours must be between 1 and 6.");
        }
    }


    // Input Grade
    void setGrade()
    {
        string input;

        cout << "Enter Grade (A, B, C, D, F): ";
        cin >> input;

        // Grade must contain exactly one character
        if (input.length() != 1)
        {
            throw InputException(
                "Grade must be one uppercase letter: A, B, C, D or F."
            );
        }

        grade = input[0];

        // Only uppercase grades are accepted
        if (grade != 'A' &&
            grade != 'B' &&
            grade != 'C' &&
            grade != 'D' &&
            grade != 'F')
        {
            throw InputException(
                "Invalid grade. Enter only uppercase A, B, C, D or F."
            );
        }

        calculateGradePoint();
    }


    // Calculate Grade Point
    void calculateGradePoint()
    {
        if (grade == 'A')
        {
            gradePoint = 4.0;
        }
        else if (grade == 'B')
        {
            gradePoint = 3.0;
        }
        else if (grade == 'C')
        {
            gradePoint = 2.0;
        }
        else if (grade == 'D')
        {
            gradePoint = 1.0;
        }
        else if (grade == 'F')
        {
            gradePoint = 0.0;
        }
    }


    // Input complete course information
    void inputCourse()
    {
        bool valid = false;

        while (!valid)
        {
            try
            {
                setCourseName();
                setCreditHours();
                setGrade();

                valid = true;
            }
            catch (InputException &e)
            {
                cout << "\nError: " << e.getMessage() << endl;
                cout << "Please enter the course information again.\n\n";
            }
        }
    }


    // Get Credit Hours
    int getCreditHours()
    {
        return creditHours;
    }


    // Get Grade Points
    float getGradePoints()
    {
        return gradePoint * creditHours;
    }


    // Display Course
    void displayCourse()
    {
        cout << left
             << setw(20) << courseName
             << setw(15) << creditHours
             << setw(10) << grade
             << setw(15) << fixed << setprecision(2)
             << gradePoint
             << endl;
    }
};


// =========================
// CGPA Calculator Class
// =========================
class CGPACalculator
{
private:
    Course courses[20];
    int numberOfCourses;
    float totalCredits;
    float totalGradePoints;

public:

    // Constructor
    CGPACalculator()
    {
        numberOfCourses = 0;
        totalCredits = 0;
        totalGradePoints = 0;
    }


    // Get number of courses
    void inputNumberOfCourses()
    {
        string input;
        bool valid = false;

        while (!valid)
        {
            try
            {
                cout << "Enter Number of Courses (1-20): ";
                cin >> input;

                // Check every character
                for (int i = 0; i < input.length(); i++)
                {
                    if (input[i] < '0' || input[i] > '9')
                    {
                        throw InputException(
                            "Number of courses must contain numbers only."
                        );
                    }
                }

                numberOfCourses = stoi(input);

                if (numberOfCourses < 1 ||
                    numberOfCourses > 20)
                {
                    throw InputException(
                        "Number of courses must be between 1 and 20."
                    );
                }

                valid = true;
            }
            catch (InputException &e)
            {
                cout << "\nError: "
                     << e.getMessage()
                     << "\nPlease try again.\n\n";
            }
        }
    }


    // Input all courses
    void inputCourses()
    {
        totalCredits = 0;
        totalGradePoints = 0;

        for (int i = 0; i < numberOfCourses; i++)
        {
            cout << "\n==============================\n";
            cout << "Course " << i + 1 << endl;
            cout << "==============================\n";

            courses[i].inputCourse();

            totalCredits += courses[i].getCreditHours();
            totalGradePoints += courses[i].getGradePoints();
        }
    }


    // Calculate Semester GPA
    float calculateGPA()
    {
        if (totalCredits == 0)
        {
            throw InputException(
                "Total credit hours cannot be zero."
            );
        }

        return totalGradePoints / totalCredits;
    }


    // Get Previous CGPA
    float inputPreviousCGPA()
    {
        string input;
        float previousCGPA;
        bool valid = false;

        while (!valid)
        {
            try
            {
                cout << "\nEnter Previous CGPA (0.00 - 4.00): ";
                cin >> input;

                // Check valid characters
                int decimalCount = 0;

                for (int i = 0; i < input.length(); i++)
                {
                    if (input[i] == '.')
                    {
                        decimalCount++;
                    }
                    else if (input[i] < '0' ||
                             input[i] > '9')
                    {
                        throw InputException(
                            "CGPA must contain numbers and one decimal point only."
                        );
                    }
                }

                if (decimalCount > 1)
                {
                    throw InputException(
                        "Invalid CGPA format."
                    );
                }

                previousCGPA = stof(input);

                if (previousCGPA < 0 ||
                    previousCGPA > 4)
                {
                    throw InputException(
                        "CGPA must be between 0.00 and 4.00."
                    );
                }

                valid = true;
            }
            catch (InputException &e)
            {
                cout << "Error: "
                     << e.getMessage()
                     << endl;
            }
        }

        return previousCGPA;
    }


    // Get Previous Credit Hours
    float inputPreviousCredits()
    {
        string input;
        float previousCredits;
        bool valid = false;

        while (!valid)
        {
            try
            {
                cout << "Enter Previous Completed Credit Hours: ";
                cin >> input;

                // Check numbers only
                for (int i = 0; i < input.length(); i++)
                {
                    if (input[i] < '0' ||
                        input[i] > '9')
                    {
                        throw InputException(
                            "Previous credit hours must contain numbers only."
                        );
                    }
                }

                previousCredits = stoi(input);

                if (previousCredits < 0)
                {
                    throw InputException(
                        "Previous credit hours cannot be negative."
                    );
                }

                valid = true;
            }
            catch (InputException &e)
            {
                cout << "Error: "
                     << e.getMessage()
                     << endl;
            }
        }

        return previousCredits;
    }


    // Calculate Overall CGPA
    float calculateCGPA(float previousCGPA,
                        float previousCredits)
    {
        float overallCGPA;

        if (previousCredits == 0)
        {
            // If this is the student's first semester
            overallCGPA = totalGradePoints / totalCredits;
        }
        else
        {
            overallCGPA =
                ((previousCGPA * previousCredits)
                 + totalGradePoints)
                /
                (previousCredits + totalCredits);
        }

        return overallCGPA;
    }


    // Display all courses
    void displayCourses()
    {
        cout << "\n\n====================================================\n";
        cout << "                 COURSE DETAILS\n";
        cout << "====================================================\n";

        cout << left
             << setw(20) << "Course Name"
             << setw(15) << "Credit Hours"
             << setw(10) << "Grade"
             << setw(15) << "Grade Point"
             << endl;

        cout << "----------------------------------------------------\n";

        for (int i = 0; i < numberOfCourses; i++)
        {
            courses[i].displayCourse();
        }

        cout << "====================================================\n";
    }


    // Display final result
    void displayResult(float semesterGPA,
                       float overallCGPA)
    {
        cout << "\n\n============================================\n";
        cout << "              FINAL RESULT\n";
        cout << "============================================\n";

        cout << fixed << setprecision(2);

        cout << "Total Credit Hours : "
             << totalCredits << endl;

        cout << "Total Grade Points : "
             << totalGradePoints << endl;

        cout << "Semester GPA       : "
             << semesterGPA << endl;

        cout << "Overall CGPA       : "
             << overallCGPA << endl;

        cout << "============================================\n";
    }


    // Complete calculation
    void calculateResult()
    {
        inputNumberOfCourses();

        inputCourses();

        float semesterGPA = calculateGPA();

        float previousCGPA = inputPreviousCGPA();

        float previousCredits = inputPreviousCredits();

        float overallCGPA =
            calculateCGPA(previousCGPA,
                          previousCredits);

        displayCourses();

        displayResult(semesterGPA,
                      overallCGPA);
    }
};


// =========================
// Main Function
// =========================
int main()
{
    int choice;
    bool running = true;

    while (running)
    {
        cout << "\n\n============================================\n";
        cout << "             CGPA CALCULATOR\n";
        cout << "============================================\n";
        cout << "1. Calculate GPA and CGPA\n";
        cout << "2. Exit\n";
        cout << "============================================\n";

        string input;

        try
        {
            cout << "Enter your choice: ";
            cin >> input;

            if (input.length() != 1 ||
                (input[0] != '1' && input[0] != '2'))
            {
                throw InputException(
                    "Please enter only 1 or 2."
                );
            }

            choice = input[0] - '0';

            if (choice == 1)
            {
                CGPACalculator calculator;

                calculator.calculateResult();
            }
            else if (choice == 2)
            {
                cout << "\nThank you for using CGPA Calculator!\n";
                running = false;
            }
        }
        catch (InputException &e)
        {
            cout << "\nError: "
                 << e.getMessage()
                 << endl;
        }
    }

    return 0;
}
