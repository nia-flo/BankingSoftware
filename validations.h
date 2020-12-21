#include "user.h"

#include <fstream>
#include <string>
#include <vector>

#define MAX_OVERDRAFT -10000
#define POSSIBLE_PASSWORD_SYMBOLS "!@#$%^&*"
#define POSSIBLE_USERNAME_SYMBOLS "_-."
#define MIN_PASSWORD_LENGHT 5

bool isFileEmpty (std::fstream& file);

bool isDouble (const std::string &text);

bool isPossibleSymbol (char symbol, std::string possibleSymbols);

bool isUsernameValid (const std::string &username);

bool isUsernameTaken (const std::string &username, const std::vector<user> &users);

int isPasswordValid (const std::string &password);
