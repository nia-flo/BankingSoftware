#include "user.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <functional>
#include <iomanip>

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

bool readFile (std::vector<user> &users) {
    std::fstream file;

    file.open (FILE_NAME, std::ios::in | std::ios::out | std::ios::app);

    if (!file.is_open()) {
        return false;
    }
    
    std::string line;

    while (!isFileEmpty(file) && std::getline(file, line)) {
        std::vector<std::string> parameters = splitLine(line, LINE_DELIMITER);

        user current(parameters[0], parameters[1], std::stod(parameters[2]));

        users.push_back(current);
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

bool isUsernameTaken (std::string username, std::vector<user> &users) {
    for (int i = 0; i < users.size(); ++i) {
        if (username == users[i].username) {
            return true;
        }
    }

    return false;
}

std::string askForUsername (std::vector<user> &users) {
    std::string username;

    std::cout << "Please enter your username: ";
    std::cin >> username;
        
    std::cout << '\n';

    if (!isUsernameValid(username)) {
        std::cout << "Username is not valid - it must contain only latin letters and/or the symbols _-.\n\n";
        
        return askForUsername(users);
    }

    if (isUsernameTaken(username, users)) {
        std::cout << "This username is already taken!\n\n";
            
        return askForUsername(users);
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

void addUser (std::string username, std::string password, std::vector<user> &users) {
    user newUser(username, password, INITIAL_BALANCE);

    users.push_back(newUser);
}

void mainMenu (std::vector<user> users, int currentUserIdx) {
    std::cout << "You have " << users[currentUserIdx].balance << " BGN. Choose one of the following options:\n";

    while (true)
    {
        std::cout << "Choose one of the options (C, D, L, T, W):\n";
        std::cout << "C - cancel account\n";
        std::cout << "D - deposit\n";
        std::cout << "L - logout\n";
        std::cout << "T - transfer\n";
        std::cout << "W - withdraw\n";

        //choice is string although it must be only one letter, because the user could enter the whole word instead of the wanted letter
        std::string choice;

        std::cin >> choice;

        std::cout << '\n';

        if (choice == "C") {
            //TODO: cancel account
            return;
        } else if (choice == "D") {
            //TODO: deposit
            return;
        } else if (choice == "L") {
            //TODO: logout
            return;
        } else if (choice == "T") {
            //TODO: transfer
            return;
        } else if (choice == "W") {
            //TODO: withdraw
            return;
        } else {
            std::cout << "Incorrect input. Please try again.\n";
        }
    }
}

void registerUser (std::vector<user> &users) {
    std::string username, password;

    username = askForUsername(users);

    std::cout << '\n';

    password = askForPassword();

    size_t generatedHash = std::hash<std::string>{}(password);

    std::string passwordHash = std::to_string(generatedHash);

    addUser (username, passwordHash, users);

    mainMenu(users, users.size() - 1);
}

bool saveChangesToFile (std::vector<user> &users) {
    std::fstream file;

    file.open (FILE_NAME, std::ios::out | std::ios::trunc);

    if (!file.is_open()) {
        return false;
    }
    
    for (int i = 0; i < users.size(); ++i) {
        file << users[i].username << ':' << users[i].password << ':' << users[i].balance << '\n';
    }

    file.close();

    return true;
}

void quit (std::vector<user> &users) {
    saveChangesToFile(users);
}

//returns:
//-1 if user with these username and password does not exist
//otherwise - the index of the user
int findUser (std::string username, std::string password, std::vector<user> &users) {
    for (int i = 0; i < users.size(); ++i) {
        if (users[i].username == username && users[i].password == password) {
            return i;
        }
    }

    return -1;
}

void login (std::vector<user> &users);

void startMenu (std::vector<user> &users) {
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
            login(users);

            return;
        } else if (choice == "R") {
            registerUser(users);

            return;
        } else if (choice == "Q") {
            quit(users);
            
            return;
        } else {
            std::cout << "Incorrect input. Please try again.\n";
        }
    }
    
}

int main () {
    std::vector<user> users;

    if (!readFile (users)) {
        std::cout << "Error - database file could not be loaded.";

        return 0;
    }

    startMenu (users);

    return 0;
}

void login (std::vector<user> &users) {
    std::string username, password;

    std::cout << "Please enter your username: ";
    std::cin >> username;

    std::cout << '\n';

    std::cout << "Please enter your password: ";
    std::cin >> password;

    std::cout << '\n';

    size_t generatedHash = std::hash<std::string>{}(password);

    std::string passwordHash = std::to_string(generatedHash);

    int userIdx = findUser (username, passwordHash, users);

    if (userIdx == -1) {
        std::cout << "Incorrect username or password.\n\n";
        startMenu(users);
        return;
    }

    mainMenu(users, userIdx);
}