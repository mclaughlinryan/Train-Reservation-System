#include "Admin.h"

// Shows menu with options to edit or display system information as an administrative user
void AdminMode(Admin& admin) {
	char answer[30];
	std::cout << "Enter password: ";
	std::cin >> answer;
	char password[30] = "login";

	if (strcmp(answer, password) != 0) {
		std::cout << "Incorrect password.\n\n";

		return;
	}

	std::cout << std::endl;

	do {
		std::cout << "---------- Admin Menu ----------\n";
		std::cout << "1. Add New Travel Schedule\n";
		std::cout << "2. Remove Travel Schedule\n";
		std::cout << "3. Remove User Account\n";
		std::cout << "4. Display All Travel Schedules\n";
		std::cout << "5. Display All User Accounts\n";
		std::cout << "0. Return to Main Menu\n";
		std::cout << "Enter a menu option: ";
		int selection;
		std::cin >> selection;

		switch (selection) {
			case 1:
				admin.AddTravelSchedule();
				break;
			case 2:
				admin.RemoveTravelSchedule();
				break;
			case 3:
			    admin.RemoveUser();
				break;
			case 4:
				admin.DisplayTravelSchedules();
				break;
			case 5:
				admin.DisplayUserAccounts();
				break;
			case 0:
			    std::cout << std::endl;
				return;
			default:
				std::cout << "Enter 0-5 to select a menu option.\n\n";
		}
	} while (true);
}

// Shows menu with options to make or change a train reservation as a system user
void UserMode(Admin& admin) {
	int index;
	int menu = 0;
	User user;
	char option;
	std::cout << "Do you have an account? Type 'y' for yes or 'n' to sign up: ";
	std::cin >> option;

	if (option == 'y') {
		char username[30];
		char password[30];
		std::cout << "Enter your username: ";
		std::cin >> username;
		index = admin.SearchUser(username);

		if (index == -1) {
			std::cout << "That username does not exist in the system.\n\n";

			return;
		} else {
			std::cout << "Enter your password: ";
			std::cin >> password;
			user = admin.GetUser(index);

			if (strcmp(password, user.GetPassword()) != 0) {
				std::cout << "Incorrect password.\n\n";
			} else {
				menu = 1;
				std::cout << std::endl;
			}
		}
	} else if (option == 'n') {
		std::cout << "Account Sign Up:\n";
		index = admin.AddUser();

		if (index != -1) {
			user = admin.GetUser(index);
			menu = 1;
		}
	} else {
		std::cout << "Invalid option.\n\n";
	}

	if (menu == 1) {
		do {
			std::cout << "---------- User Menu ----------\n";
			std::cout << "1. Make Reservation\n";
			std::cout << "2. Cancel Reservation\n";
			std::cout << "3. Display Reservation\n";
			std::cout << "4. Display All Travel Schedules\n";
			std::cout << "5. Display Account Information\n";
			std::cout << "6. Delete Account\n";
			std::cout << "0. Return to Main Menu\n";
			std::cout << "Enter a menu option: ";
			int selection;
			std::cin >> selection;

			switch (selection) {
				case 1:
					user.MakeReservation(admin, index);
					break;
				case 2:
					user.CancelReservation(admin, index);
					break;
				case 3:
				    user.DisplayReservation(admin);
					break;
				case 4:
					admin.DisplayTravelSchedules();
					break;
				case 5:
					user.DisplayAccountInformation(admin);
					break;
				case 6:
					user.DeleteAccount(admin);
					return;
				case 0:
					std::cout << std::endl;
					return;
				default:
					std::cout << "Enter 0-6 to select a menu option.\n\n";
			}
		} while (true);
	}
}

int main() {
	Admin admin;
	std::cout << "---------- Welcome to the Train Reservation System ----------\n\n";

	do {
		std::cout << "---------- Main Menu ----------\n";
		std::cout << "1. Admin Mode\n";
		std::cout << "2. User Mode\n";
		std::cout << "0. Exit\n";
		std::cout << "Enter a menu option: ";
		int selection;
		std::cin >> selection;
		
		switch (selection) {
			case 1:
				AdminMode(admin);
				break;
			case 2:
				UserMode(admin);
				break;
			case 0:
				return 0;
			default:
				std::cout << "Enter 0-2 to select a menu option.\n\n";
		}
	} while (true);

	return 0;
}