#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unistd.h>
#include <sqlite3.h>

class User {
        std::string fUsername;
        std::string fPassword;
        std::string fSecurityCode;
    public:
        User();
        User(std::string, std::string, std::string);
        User(std::string, std::string);

        void SetUsername(std::string uname) { fUsername = uname; }
        std::string GetUsername() { return fUsername; }
        void SetPassword(std::string pword) { fPassword = pword; }
        std::string GetPassword() { return fPassword; }
        std::string ReturnPassword(std::string uname, std::string securityCode) {
            if (uname == fUsername && securityCode == fSecurityCode) {
                return fPassword;
            } else {
                std::cout << "There's an issue retrieving your password. Please try again." << std::endl;
                return "Error";
            };
        };
        void SetSecurityCode(std::string secCode) { fSecurityCode = secCode; }
        std::string GetSecurityCode() {return fSecurityCode; }
        std::string ReturnSecurityCode(std::string uname, std::string pword) {
            if (uname == fUsername && pword == fPassword) {
                return fSecurityCode;
            } else {
                std::cout << "There's an issue retrieving your security code. Please try again." << std::endl;
                return "Error";
            };
        };
};

User::User(std::string funame, std::string fpword, std::string fscode) {
    fUsername = funame;
    fPassword = fpword;
    fSecurityCode = fscode;
}

User::User(std::string funame, std::string fpword) {
    fUsername = funame;
    fPassword = fpword;
    fSecurityCode = "default";
}

///////////////////////////////////////////////////////////////////////////////
/// Prompt the user to put register with a new username, password, and security code
User NewUserPrompt() {
    std::string uname, pword, scode;
    std::cout << "Please enter your username: ";
    std::cin >> uname;
    std::cout << "Enter your password: ";
    std::cin >> pword;
    std::cout << "Enter your security code: ";
    std::cin >> scode;
    std::cout << "Thanks" << std::endl;
    std::cout << "" << std::endl;
    User newUser{uname, pword, scode};

    return newUser;
}

///////////////////////////////////////////////////////////////////////////////
/// 
User ExistingUserPrompt() {
    std::string uname, pword, scode;
    std::cout << "Please enter your username: ";
    std::cin >> uname;
    std::cout << "Enter your password: ";
    std::cin >> pword;

    User currentUser{uname, pword};
    return currentUser;
}

///////////////////////////////////////////////////////////////////////////////
/// 
int StartingPrompt() {
    int choice;
    std::cout << "Enter a number for your choice: " << std::endl;
    std::cout << "1 - Login" << std::endl;
    std::cout << "2 - Register new user" << std::endl;
    std::cout << "" << std::endl;
    std::cin >> choice;
    
    return choice;
}

///////////////////////////////////////////////////////////////////////////////
///
bool CheckExistingUser(std::vector<User> userList, User currentUser) {
    for (auto element : userList) {
        if (currentUser.GetUsername() == element.GetUsername()) {
            if (currentUser.GetPassword() == element.GetPassword()) {
                return true;
            }
        }
    }
    return false;
}

///////////////////////////////////////////////////////////////////////////////
///
int main() {
    std::vector<User> users;
    User John = {"John", "Password1", "Dog"};
    users.push_back(John);

    while (true) {
        int choice = StartingPrompt();
        if (choice == 1) {
            std::cout << "Login Below:" << std::endl;
            User tempUser = ExistingUserPrompt();
            if (CheckExistingUser(users, tempUser)) {
                std::cout << "Welcome " << tempUser.GetUsername() << std::endl;
                sleep(1);
            } else {
                std::cout << "There's an error with either your username or password. Please try again." << std::endl;
                sleep(1);
            }
        } else if (choice == 2) {
            users.push_back(NewUserPrompt());
            std::cout << "Welcome new user: " << users[users.size()-1].GetUsername() << std::endl;
        } else {
            std::cout << "You selected an invalid option" << std::endl;
        }
        std::cout << "" << std::endl;
    }

    return 0;
}
