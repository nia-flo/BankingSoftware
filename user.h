#include <string>

struct user {
    std::string username;
    std::string password;
    double balance;

    user (std::string username, std::string password, double balance) {
        this->username = username;
        this->password = password;
        this->balance = balance;
    }
};