# BankingSoftware
My course project for FMI Introduction to programming practicum

## Description
This is a console application, which simulates simple banking process. <br />
<br />
The user is a customer in the "bank". He can register new profile or log in if he already has one. Every user account can do deposits and withdraws to his own account and can transfer money to a different account.

## Usage
When the program starts, the user is in the _start menu_. He should choose one of the three options:
* _L_ - login <br />
If the user has an existing account and wants to log in it.

* _R_ - register <br />
If the user wants to create a new account.

* _Q_ - quit <br />
If the user wants to exit the program.

User account requirements:
* _username_ <br />
 The username could contain lowercase and uppercase latin letters as well as the symbols _-. <br />
 It must be at least 1 symbol long.

* _password_ <br />
The password could contain lowercase and uppercase latin letters, numbers and the symbols !@#$%^&* <br />
It must be at least 5 symbols long and must contain at least one lowercase latin letter, one uppercase latin letter and one symbol.

After successful login or register, the user is redirected to the _main menu_. He should choose one of the following options:
* _C_ - cancel account <br />
The user must enter his password to complete this operation. <br />
After cancellation the account is permanently deleted. This operation cannot be undone. <br />
After successful account cancellation the user is redirected to the _start menu_, otherwise he remains in his profile and is redirected back to the _main menu_.

* _D_ - deposit <br />
The user can deposit any positive amount of money to his own account. <br />
After this operation he is redirected back to the _main menu_.

* _L_ - logout <br />
The user is logged out of his account and is redirected to the _start menu_.

* _T_ - transfer <br />
If the user has reached his ovedraft limit (10 000 BGN), he could not do transfers until his balance increases.  <br />
The user is asked to enter a positive amount of money that he wants to transfer and the username of the receiver. The ovedraft limit is 10 000 BGN, if the amount exceeds it, the user is asked to enter a valid amount again. If there is no user with the receiver's username or the receiver is the current user, the user is asked to enter the username again. <br />
After successfull transfer, the amount of money is withdrawed from the current user's account and is added to the receiver's account. <br />
After this operation the user is redirected back to the _main menu_.

* _W_ - withdraw <br />
If the user has reached his ovedraft limit (10 000 BGN), he could not do any withdraws until his balance increases.  <br />
The user can withdraw any positive amount of money, which doesnt exceed his ovedraft limit (10 000 BGN), from his own account. <br />
After this operation the user is redirected back to the _main menu_.

## Start program
The program should be compilled with GCC compiler (version 9.2.0 or newer). <br />
_Build:_ 
```bash
g++ *cpp -o bankingSoftware.exe
```
<br />
_Run:_ Open bankingSoftware.exe <br />
 <br />
 
The file "users.txt" is the database of the program. It should be in the following format (otherwise the program will display error message): <br />
_username:hashed_password:balance_
