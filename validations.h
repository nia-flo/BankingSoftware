#include "user.h"

#include <fstream>
#include <string>
#include <vector>

#define MAX_OVERDRAFT -10000
#define POSSIBLE_PASSWORD_SYMBOLS "!@#$%^&*"
#define POSSIBLE_USERNAME_SYMBOLS "_-."
#define MIN_PASSWORD_LENGHT 5

bool isFileEmpty (std::fstream& file) {
    return file.peek() == std::ifstream::traits_type::eof();
}

bool isDouble (const std::string &text) {
    bool isDotUsed = false;

    for (int i = 0; i < text.size(); ++i) {
        if (text[i] == '.') {
            if (!isDotUsed && i != text.size() - 1) {
                isDotUsed = true;
            } else {
                return false;
            }
        }
        else if (text[i] == '-') {
            if (i != 0) {
                return false;
            }
        }
        else if (text[i] < '0' || text[i] > '9') {
            return false;
        }
    }

    return true;
}

bool isPossibleSymbol (char symbol, std::string possibleSymbols) {
    for (int i = 0; i < possibleSymbols.size(); ++i) {
        if (symbol == possibleSymbols[i]) {
            return true;
        }
    }

    return false;
}

bool isUsernameValid (const std::string &username) {
    for (int i = 0; i < username.size(); ++i) {
        if (!((username[i] >= 'a' && username[i] <= 'z') || (username[i] >= 'A' && username[i] <= 'Z') || isPossibleSymbol(username[i], POSSIBLE_USERNAME_SYMBOLS))) {
            return false;
        }
    }

    return true;
}

bool isUsernameTaken (const std::string &username, const std::vector<user> &users) {
    for (int i = 0; i < users.size(); ++i) {
        if (username == users[i].username) {
            return true;
        }
    }

    return false;
}

int isPasswordValid (const std::string &password) {
    if (password.size() < MIN_PASSWORD_LENGHT) {
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
        else if (isPossibleSymbol(password[i], POSSIBLE_PASSWORD_SYMBOLS)) {
            containsSymbol = true;
        }
        else if (password[i] < '0' || password[i] > '9') {
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
