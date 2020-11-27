#include "user.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <functional>

#define FILE_NAME "users.txt"
#define LINE_DELIMITER ':'
#define INITIAL_BALANCE 0

std::vector<std::string> splitLine(std::string line, char delimiter) {
    std::vector<std::string> result;

    for (int i = 0; i < line.size(); ++i) {
        std::string current = "";

        for (; i < line.size() && line[i] != delimiter; ++i) {
            current += line[i];
        }

        result.push_back(current);
    }

    return result;
}

bool isFileEmpty (std::fstream& file) {
    return file.peek() == std::ifstream::traits_type::eof();
}

bool readFile (std::vector<std::string> &usernames, std::vector<std::string> &passwords, std::vector<double> &balances) {
    std::fstream file;

    file.open (FILE_NAME, std::ios::in | std::ios::out | std::ios::app);

    if (!file.is_open()) {
        return false;
    }
    
    std::string line;

    while (!isFileEmpty(file) && std::getline(file, line)) {
        std::vector<std::string> parameters = splitLine(line, LINE_DELIMITER);

        usernames.push_back(parameters[0]);
        passwords.push_back(parameters[1]);
        balances.push_back(std::stod(parameters[2]));
    }

    file.close();

    return true;
}

bool isUsernameValid(std::string username) {
    for (int i = 0; i < username.size(); ++i) {
        if (!((username[i] >= 'a' && username[i] <= 'z') || (username[i] >= 'A' && username[i] <= 'Z') || username[i] == '_' || username[i] == '_' || username[i] == '.')) {
            return false;
        }
    }

    return true;
}

bool isUsernameTaken (std::string username, std::vector<std::string> &usernames) {
    for (int i = 0; i < usernames.size(); ++i) {
        if (username == usernames[i]) {
            return true;
        }
    }

    return false;
}

std::string askForUsername (std::vector<std::string> &usernames) {
    std::string username;

    std::cout << "Please enter your username: ";
    std::cin >> username;
        
    std::cout << '\n';

    if (!isUsernameValid(username)) {
        std::cout << "Username is not valid - it must contain only latin letters and/or the symbols _-.\n\n";
        
        return askForUsername(usernames);
    }

    if (isUsernameTaken(username, usernames)) {
        std::cout << "This username is already taken!\n\n";
            
        return askForUsername(usernames);
    }

    return username;
}

//returns:
//1 if the password is valid
//-1 if the password's lenght is less than 5 characters
//-2 is the password contains characters that are not allowed
//-3 if the password doesnt contain a lowercase letter
//-4 if the password doesnt contain an uppercase letter
//-5 if the password doesnt contain a symbol
int isPasswordValid (std::string password) {
    if (password.size() < 5) {
        return -1;
    }

    bool containsLowercaseLetter = false, containsUppercaseLetter = false, containsSymbol = false;

    for (int i = 0; i < password.size(); ++i) {
        if (password[i] >= 'a' && password[i] <= 'z') {
            containsLowercaseLetter = true;
        }
        else if (password[i] >= 'A' && password[i] <= 'Z') {
            containsUppercaseLetter = true;
        }
        else if (password[i] == '!' || password[i] == '@' || password[i] == '#' || password[i] == '$' || password[i] == '%' || password[i] == '^' || password[i] == '&' || password[i] == '*') {
            containsSymbol = true;
        }
        else {
            return -2;
        }
    }

    if (!containsLowercaseLetter) {
        return -3;
    }

    if (!containsUppercaseLetter) {
        return -4;
    }

    if (!containsSymbol) {
        return -5;
    }

    return 1;
}

std::string askForPassword () {
    std::string password;

    std::cout << "Please enter your password: ";
    std::cin >> password;
        
    std::cout << '\n';

    int isValid = isPasswordValid(password);

    if (isValid == 1) {
        return password;
    }

    switch (isValid){
        case -1: {
            std::cout << "The password must contain at least 5 characters\n";
            break;
        }
        case -2: {
            std::cout << "The password could contain only latin letters, number and the symbols !@#$%^&*\n";
            break;
        }
        case -3: {
            std::cout << "The password must contain a lowercase letter\n";
            break;
        }
        case -4: {
            std::cout << "The password must contain an uppercase letter\n";
            break;
        }
        case -5: {
            std::cout << "The password must contain at least one of the symbols !@#$%^&*\n";
            break;
        }
    }

    std::cout << '\n';

    return askForPassword();
}

void addUserToDB (std::string username, std::string password, std::vector<std::string> &usernames, std::vector<std::string> &passwords, std::vector<double> &balances) {
    usernames.push_back(username);
    passwords.push_back(password);
    balances.push_back(INITIAL_BALANCE);
}


void registerUser (std::vector<std::string> &usernames, std::vector<std::string> &passwords, std::vector<double> &balances) {
    std::string username, password;

    username = askForUsername(usernames);

    std::cout << '\n';

    password = askForPassword();

    size_t generatedHash = std::hash<std::string>{}(password);

    std::string passwordHash = std::to_string(generatedHash);

    addUserToDB (username, passwordHash, usernames, passwords, balances);

    //TODO: redirect to main menu
}

void startMenu (std::vector<std::string> &usernames, std::vector<std::string> &passwords, std::vector<double> &balances) {
    while (true)
    {
        std::cout << "Choose one of the options (L, R or Q):\n";
        std::cout << "L - login\n";
        std::cout << "R - register\n";
        std::cout << "Q - quit\n";

        //choice is string although it must be only one letter, because the user could enter the whole word instead of the wanted letter
        std::string choice;

        std::cin >> choice;

        std::cout << '\n';

        if (choice == "L") {
            //TODO: login
            return;
        } else if (choice == "R") {
            registerUser(usernames, passwords, balances);

            return;
        } else if (choice == "Q") {
            //TODO: quit
            return;
        } else {
            std::cout << "Incorrect input. Please try again.\n";
        }
    }
    
}

int main () {
    std::vector<std::string> usernames, passwords;
    std::vector<double> balances;

    if (!readFile (usernames, passwords, balances)) {
        std::cout << "Error - database file could not be loaded.";

        return 0;
    }

    startMenu (usernames, passwords, balances);

    return 0;
}