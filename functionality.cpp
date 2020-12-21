#include "functionality.h"

std::vector<std::string> splitLine (const std::string &line, char delimiter) {
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

bool readFile (std::vector<user> &users) {
    std::fstream file;

    file.open(FILE_NAME, std::ios::in | std::ios::out | std::ios::app);

    if (!file.is_open()) {
        return false;
    }
    
    std::string line;

    while (!isFileEmpty(file) && std::getline(file, line)) {
        std::vector<std::string> parameters = splitLine(line, LINE_DELIMITER);

        if (parameters.size() != 3) {
            return false;
        }

        try {
            if (!isDouble(parameters[2])) {
                throw "Not a double";
            }

            double balance = std::stod(parameters[2]);

            balance = trunc (balance * 100) / 100;

            user current(parameters[0], parameters[1], balance);
            
            users.push_back(current);
        }
        catch (...) {
            return false;
        }
    }

    file.close();

    return true;
}

std::string askForUsername (const std::vector<user> &users) {
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

std::string askForPassword () {
    std::string password;

    std::cout << "Please enter your password: ";
    std::cin >> password;
        
    std::cout << '\n';

    int isValid = isPasswordValid(password);

    switch (isValid){
        case 1: {
            return password;
        }
        case -1: {
            std::cout << "The password must contain at least 5 characters\n";
            break;
        }
        case -2: {
            std::cout << "The password could contain only latin letters, number and the symbols " << POSSIBLE_PASSWORD_SYMBOLS << '\n';
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

void addUser (const std::string &username, const std::string &password, std::vector<user> &users) {
    user newUser(username, password, INITIAL_BALANCE);

    users.push_back(newUser);
}

std::string askForPasswordConfirmation () {
    std::cout << "Please confirm your password: ";

    std::string password;
    std::cin >> password;

    std::cout << '\n';

    return password;
}

void registerUser (std::vector<user> &users) {
    std::string username, password, passwordConfirmation;

    username = askForUsername(users);
    password = askForPassword();
    passwordConfirmation = askForPasswordConfirmation();

    if (password != passwordConfirmation) {
        std::cout << "Unsuccessfull registration - passwords do not match.\n\n";
        startMenu(users);

        return;
    }

    size_t generatedHash = std::hash<std::string>{}(password);
    std::string passwordHash = std::to_string(generatedHash);

    addUser (username, passwordHash, users);

    std::cout << "User registered successfully.\n\n";

    mainMenu(users, users.size() - 1);
}

bool saveChangesToFile (const std::vector<user> &users) {
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

void quit (const std::vector<user> &users) {
    saveChangesToFile(users);
}

int findUser (const std::string &username, const std::string &password, const std::vector<user> &users) {
    for (int i = 0; i < users.size(); ++i) {
        if (users[i].username == username && users[i].password == password) {
            return i;
        }
    }

    return -1;
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

void cancelAccount (std::vector<user> &users, int currentUserIdx) {
    std::string password;

    std::cout << "Please enter your password: ";
    std::cin >> password;

    size_t generatedHash = std::hash<std::string>{}(password);
    std::string passwordHash = std::to_string(generatedHash);

    std::cout << "\n";

    if (passwordHash != users[currentUserIdx].password) {
        std::cout << "Incorrect password! \n\n";
        mainMenu (users, currentUserIdx);
        return;
    }

    users.erase(users.begin() + currentUserIdx);

    std::cout << "Account cancelled successfully.\n\n";

    startMenu(users);
}

double askForAmountToDeposit () {
    double amount; 

    std::cout << "Please enter the amount BGN that you want to deposit: ";
    std::cin >> amount;

    std::cout << "\n";

    while (amount <= 0) {
        std::cout << "The amount is not possible to be 0 or less BGN, please enter a positive amount BGN that you want to deposit: ";
        std::cin >> amount;

        std::cout << "\n";
    }

    amount = trunc (amount * 100) / 100;

    return amount;
}

void deposit (std::vector<user> &users, int currentUserIdx) {
    double amount = askForAmountToDeposit();
    
    users[currentUserIdx].balance += amount;

    std::cout << "Successfully added " << amount << " BGN to to your accont.\n\n";

    mainMenu(users, currentUserIdx);
}

void logout (std::vector<user> &users, int currentUserIdx) {
    std::cout << "You logged out successfully.\n\n";

    startMenu(users);
}

double askForAmountToWithdraw (double maxAmount) {
    double amount; 

    std::cout << "Please enter the amount BGN: ";
    std::cin >> amount;

    std::cout << "\n";

    amount = trunc (amount * 100) / 100;

    while (amount <= 0 || amount > maxAmount) {
        std::cout << "This amount is not possible to be withdrawed from your account.\n";
        std::cout << "Please enter an amount between 0 and " << maxAmount << " BGN: ";

        std::cin >> amount;

        std::cout << '\n';

        amount = trunc (amount * 100) / 100;
    }

    return amount;
}

int findUserByUsername (const std::vector<user> &users, const std::string &username) {
    for (int i = 0; i < users.size(); ++i) {
        if (users[i].username == username) {
            return i;
        }
    }
    
    return -1;
}

int askForReceiver (const std::vector<user> &users, int currentUserIdx) {
    std::string receiverUsername;
    int receiverIdx;

    while (true) {
        std::cout << "Please enter the username of the user whom you want to transfer the money: ";
        std::cin >> receiverUsername;

        std::cout << '\n';

        if (receiverUsername == users[currentUserIdx].username) {
            std::cout << "You could not transfer money to yourself.\n\n";

            continue;
        }

        receiverIdx = findUserByUsername(users, receiverUsername);

        if (receiverIdx != -1) {
            return receiverIdx;
        }

        std::cout << "User with this username does not exist.\n\n";
    }

    return receiverIdx;
}

void transfer (std::vector<user> &users, int currentUserIdx) {
    if (users[currentUserIdx].balance == MAX_OVERDRAFT) {
        std::cout << "You have reached the ovedraft limit of your account - " << MAX_OVERDRAFT << " BGN. You cannot do transfers untill your balance increases.\n\n";
        mainMenu(users, currentUserIdx);
        return;
    }

    if (users.size() == 1)
    {
        std::cout << "You are the only user. There is noone to transfer money to.\n\n";
        mainMenu(users, currentUserIdx);
        return;
    }

    double amount = askForAmountToWithdraw(users[currentUserIdx].balance - MAX_OVERDRAFT);

    int receiverIdx = askForReceiver(users, currentUserIdx);

    users[currentUserIdx].balance -= amount;
    users[receiverIdx].balance += amount;

    std::cout << "You transfered " << amount << " BGN to " << users[receiverIdx].username << " successfully.\n\n";

    mainMenu(users, currentUserIdx);
}

void withdraw (std::vector<user> &users, int currentUserIdx) {
    if (users[currentUserIdx].balance == MAX_OVERDRAFT) {
        std::cout << "You have reached the ovedraft limit of your account - " << MAX_OVERDRAFT << " BGN. You cannot do withdraws untill your balance increases.\n\n";
        mainMenu(users, currentUserIdx);
        return;
    }

    double amount = askForAmountToWithdraw(users[currentUserIdx].balance - MAX_OVERDRAFT);

    users[currentUserIdx].balance -= amount;

    std::cout << "You withdrawed " << amount << " BGN successfully.\n\n";

    mainMenu(users, currentUserIdx);
}

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
        } 
        else if (choice == "R") {
            registerUser(users);

            return;
        } 
        else if (choice == "Q") {
            quit(users);
            
            return;
        } 
        else {
            std::cout << "Incorrect input. Please try again.\n\n";
        }
    }
    
}

void mainMenu (std::vector<user> &users, int currentUserIdx) {
    std::cout << "You have " << users[currentUserIdx].balance << " BGN. ";

    while (true)
    {
        std::cout << "Choose one of the following options:\n";
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
            cancelAccount(users, currentUserIdx);

            return;
        } 
        else if (choice == "D") {
            deposit(users, currentUserIdx);

            return;
        } 
        else if (choice == "L") {
            logout(users, currentUserIdx);

            return;
        } 
        else if (choice == "T") {
            transfer(users, currentUserIdx);

            return;
        } 
        else if (choice == "W") {
            withdraw(users, currentUserIdx);

            return;
        } 
        else {
            std::cout << "Incorrect input. Please try again.\n";
        }
    }
}
