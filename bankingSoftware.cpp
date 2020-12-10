#include "functionality.h"

int main () {
    std::vector<user> users;

    if (!readFile(users)) {
        std::cout << "Error: database file could not be loaded or it is not in the correct format.";

        return 0;
    }

    startMenu(users);

    return 0;
}