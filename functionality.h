#include "validations.h"

#include <iostream>
#include <functional>
#include <iomanip>
#include <math.h>

#define FILE_NAME "users.txt"
#define LINE_DELIMITER ':'
#define INITIAL_BALANCE 0

void startMenu (std::vector<user> &users);

void mainMenu (std::vector<user> &users, int currentUserIdx);

std::vector<std::string> splitLine (const std::string &line, char delimiter);

bool readFile (std::vector<user> &users);

std::string askForUsername (const std::vector<user> &users);

std::string askForPassword ();

void addUser (const std::string &username, const std::string &password, std::vector<user> &users);

std::string askForPasswordConfirmation ();

void registerUser (std::vector<user> &users);

bool saveChangesToFile (const std::vector<user> &users);

void quit (const std::vector<user> &users);

int findUser (const std::string &username, const std::string &password, const std::vector<user> &users);

void login (std::vector<user> &users);

void cancelAccount (std::vector<user> &users, int currentUserIdx);

double askForAmountToDeposit ();

void deposit (std::vector<user> &users, int currentUserIdx);

void logout (std::vector<user> &users, int currentUserIdx);

int findUserByUsername (const std::vector<user> &users, const std::string &username);

int askForReceiver (const std::vector<user> &users, int currentUserIdx);

void transfer (std::vector<user> &users, int currentUserIdx);

void withdraw (std::vector<user> &users, int currentUserIdx);
