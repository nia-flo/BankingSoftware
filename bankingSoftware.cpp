#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define FILE_NAME "users.txt"
#define LINE_DELIMITER ':'

bool openFile (std::fstream& file) {
    file.open (FILE_NAME, std::ios::in | std::ios::out);

    if (!file.is_open()) {
        return false;
    }

    return true;
}

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

void readFile (std::fstream& file, std::vector<std::string> &usernames, std::vector<std::string> &passwords, std::vector<double> &balances) {
    std::string line;

    while (std::getline(file, line)) {
        std::vector<std::string> parameters = splitLine(line, LINE_DELIMITER);

        usernames.push_back(parameters[0]);
        passwords.push_back(parameters[1]);
        balances.push_back(std::stod(parameters[2]));
    }
}


void mainMenu (std::fstream& file, std::vector<std::string> &usernames, std::vector<std::string> &passwords, std::vector<double> &balances) {
    while (true)
    {
        std::cout << "Choose one of the options (L, R or Q):\n";
        std::cout << "L - login\n";
        std::cout << "R - register\n";
        std::cout << "Q - quit\n";

        //choice is string although it must be only one letter, because the user could enter the whole word instead of the wanted letter
        std::string choice;
        
        std::cin >> choice;

        if (choice == "L") {
            //TODO: login
            return;
        } else if (choice == "R") {
            //TODO: register
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
    std::fstream usersFile;

    if (!openFile (usersFile)) {
        std::cout << "Error - database file could not be loaded.";

        return 0;
    }

    std::vector<std::string> usernames, passwords;
    std::vector<double> balances;

    readFile (usersFile, usernames, passwords, balances);

    mainMenu (usersFile, usernames, passwords, balances);

    usersFile.close();

    return 0;
}