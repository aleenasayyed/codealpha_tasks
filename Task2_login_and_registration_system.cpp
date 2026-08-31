#include <iostream>
#include <fstream>
#include <string>
#include <functional>
#include <cctype>

using namespace std;


// ==========================================
// Custom Exception Class
// ==========================================

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


// ==========================================
// User Class
// ==========================================

class User
{
private:
    string username;
    string password;

public:

    User()
    {
        username = "";
        password = "";
    }

    User(string u, string p)
    {
        username = u;
        password = p;
    }

    void setUsername(string u)
    {
        username = u;
    }

    void setPassword(string p)
    {
        password = p;
    }

    string getUsername()
    {
        return username;
    }

    string getPassword()
    {
        return password;
    }
};


// ==========================================
// Login System Class
// ==========================================

class LoginSystem
{
private:
    string fileName;

public:

    LoginSystem()
    {
        fileName = "users.txt";
    }


    // ======================================
    // Validate Username
    // ======================================

    void validateUsername(string username)
    {
        if (username.empty())
        {
            throw InputException("Username cannot be empty.");
        }

        if (username.length() < 3)
        {
            throw InputException(
                "Username must contain at least 3 characters."
            );
        }

        if (username.length() > 20)
        {
            throw InputException(
                "Username cannot contain more than 20 characters."
            );
        }

        for (int i = 0; i < username.length(); i++)
        {
            char ch = username[i];

            if (!isalnum(ch) && ch != '_')
            {
                throw InputException(
                    "Username can contain only letters, numbers and underscore."
                );
            }
        }
    }


    // ======================================
    // Validate Password
    // ======================================

    void validatePassword(string password)
    {
        if (password.empty())
        {
            throw InputException("Password cannot be empty.");
        }

        if (password.length() < 6)
        {
            throw InputException(
                "Password must contain at least 6 characters."
            );
        }

        if (password.length() > 30)
        {
            throw InputException(
                "Password cannot contain more than 30 characters."
            );
        }

        for (int i = 0; i < password.length(); i++)
        {
            if (isspace(password[i]))
            {
                throw InputException(
                    "Password cannot contain spaces."
                );
            }
        }
    }


    // ======================================
    // Hash Password
    // ======================================

    string hashPassword(string password)
    {
        hash<string> hashFunction;

        size_t hashedValue = hashFunction(password);

        return to_string(hashedValue);
    }


    // ======================================
    // Check Username
    // ======================================

    bool usernameExists(string username)
    {
        ifstream file(fileName);

        if (!file)
        {
            return false;
        }

        string storedUsername;
        string storedPassword;

        while (file >> storedUsername >> storedPassword)
        {
            if (storedUsername == username)
            {
                file.close();
                return true;
            }
        }

        file.close();

        return false;
    }


    // ======================================
    // Registration
    // ======================================

    void registerUser()
    {
        string username;
        string password;
        string confirmPassword;

        cout << "\n========================================\n";
        cout << "             REGISTRATION\n";
        cout << "========================================\n";

        try
        {
            cout << "Enter Username: ";
            getline(cin, username);

            validateUsername(username);

            // Check duplicate username
            if (usernameExists(username))
            {
                throw InputException(
                    "Username already exists. Please choose another username."
                );
            }

            cout << "Enter Password: ";
            getline(cin, password);

            validatePassword(password);

            cout << "Confirm Password: ";
            getline(cin, confirmPassword);

            if (password != confirmPassword)
            {
                throw InputException(
                    "Passwords do not match."
                );
            }

            // Create User object
            User newUser(username, password);

            // Open file
            ofstream file(fileName, ios::app);

            if (!file)
            {
                throw InputException(
                    "Unable to open user file."
                );
            }

            // Store username and hashed password
            file << newUser.getUsername()
                 << " "
                 << hashPassword(newUser.getPassword())
                 << endl;

            file.close();

            cout << "\nRegistration Successful!\n";
            cout << "Your account has been created successfully.\n";
        }
        catch (InputException &e)
        {
            cout << "\nRegistration Error: "
                 << e.getMessage()
                 << endl;
        }
    }


    // ======================================
    // Login
    // ======================================

    void loginUser()
    {
        bool loginSuccessful = false;

        while (!loginSuccessful)
        {
            string username;
            string password;

            cout << "\n========================================\n";
            cout << "                 LOGIN\n";
            cout << "========================================\n";

            try
            {
                cout << "Enter Username: ";
                getline(cin, username);

                if (username.empty())
                {
                    throw InputException(
                        "Username cannot be empty."
                    );
                }

                cout << "Enter Password: ";
                getline(cin, password);

                if (password.empty())
                {
                    throw InputException(
                        "Password cannot be empty."
                    );
                }

                ifstream file(fileName);

                if (!file)
                {
                    throw InputException(
                        "No registered users found. Please register first."
                    );
                }

                string storedUsername;
                string storedPassword;

                string enteredPasswordHash =
                    hashPassword(password);

                bool usernameFound = false;

                while (file >> storedUsername >> storedPassword)
                {
                    if (storedUsername == username)
                    {
                        usernameFound = true;

                        if (storedPassword == enteredPasswordHash)
                        {
                            loginSuccessful = true;
                        }

                        break;
                    }
                }

                file.close();

                if (loginSuccessful)
                {
                    cout << "\n========================================\n";
                    cout << "          LOGIN SUCCESSFUL!\n";
                    cout << "========================================\n";

                    cout << "Welcome, "
                         << username
                         << "!\n";
                }
                else
                {
                    if (!usernameFound)
                    {
                        throw InputException(
                            "Username not found. Please try again."
                        );
                    }
                    else
                    {
                        throw InputException(
                            "Incorrect password. Please try again."
                        );
                    }
                }
            }
            catch (InputException &e)
            {
                cout << "\nLogin Error: "
                     << e.getMessage()
                     << endl;

                cout << "Please enter your login details again.\n";
            }
        }
    }


    // ======================================
    // Menu
    // ======================================

    void displayMenu()
    {
        cout << "\n\n========================================\n";
        cout << "      LOGIN & REGISTRATION SYSTEM\n";
        cout << "========================================\n";
        cout << "1. Login\n";
        cout << "2. Register\n";
        cout << "3. Exit\n";
        cout << "========================================\n";
    }


    // ======================================
    // Run System
    // ======================================

    void run()
    {
        string choice;
        bool running = true;

        while (running)
        {
            displayMenu();

            try
            {
                cout << "Enter your choice: ";
                getline(cin, choice);

                if (choice == "1")
                {
                    loginUser();
                }
                else if (choice == "2")
                {
                    registerUser();
                }
                else if (choice == "3")
                {
                    cout << "\nThank you for using the system!\n";
                    running = false;
                }
                else
                {
                    throw InputException(
                        "Invalid choice. Please enter 1, 2 or 3."
                    );
                }
            }
            catch (InputException &e)
            {
                cout << "\nError: "
                     << e.getMessage()
                     << endl;
            }
        }
    }
};


// ==========================================
// Main Function
// ==========================================

int main()
{
    LoginSystem system;

    system.run();

    return 0;
}
