#include "User.h"
#include "Admin.h"
#include <fstream>
#include <sstream>

// Reserves seats for a travel schedule for a system user
void User::MakeReservation(Admin& admin, int index) {
	int scheduleID;
	int scheduleIndex;
	int reservationNumSeats;

	if (admin.SearchSchedule(travelScheduleID) == -1) {
		admin.DisplayTravelSchedules();
		std::cout << "Enter the ID of the train you would like to make a reservation for.\n";
        std::cin >> scheduleID;
		scheduleIndex = admin.SearchSchedule(scheduleID);

		if (scheduleIndex == -1) {
			std::cout << "Invalid ID.\n\n";
		} else {
			std::cout << "Enter the number of seats you would like to reserve.\n";
			std::cin >> reservationNumSeats;

			if (reservationNumSeats > admin.GetSchedule(scheduleID).GetAvailableSeats()) {
				if (reservationNumSeats == 1) {
					std::cout << "There are no seats available for that travel schedule at this time.\n\n";
				} else {
				    std::cout << "There are not " << reservationNumSeats << " seats available for that travel schedule at this time.\n\n";
				}
			} else {
				admin.GetUser(index).travelScheduleID = scheduleID;
				admin.GetUser(index).numSeats = reservationNumSeats;
				*this = admin.GetUser(index);
				admin.UpdateUser();
				admin.AddAvailableSeats(scheduleID, -reservationNumSeats);
				admin.UpdateTravelSchedule();

				if (reservationNumSeats == 1) {
					std::cout << "\nYou have booked " << reservationNumSeats << " seat for the following travel schedule:\n";
				} else {
					std::cout << "\nYou have booked " << reservationNumSeats << " seats for the following travel schedule:\n";
				}

				admin.DisplayTravelSchedules(scheduleID);
			}
		}
	} else {
		std::cout << "You already have a reservation. Please cancel it if you would like to make a new reservation.\n\n";
	}
}

// Cancels user travel schedule reservation
void User::CancelReservation(Admin& admin, int index) {
	int scheduleID = admin.GetUser(index).travelScheduleID;
	int reservationNumSeats = admin.GetUser(index).numSeats;
	char option;

	if (travelScheduleID != -1) {
		std::cout << "Are you sure you want to cancel your reservation? Type 'y' to confirm or 'n' to keep the reservation: ";
		std::cin >> option;

		if (option == 'y') {
			admin.AddAvailableSeats(scheduleID, reservationNumSeats);
			admin.UpdateTravelSchedule();
			admin.GetUser(index).travelScheduleID = -1;
			admin.GetUser(index).numSeats = 0;
			*this = admin.GetUser(index);
			admin.UpdateUser();
			std::cout << "Your reservation has been canceled.\n\n";
		} else if (option == 'n') {
			std::cout << "Your reservation is still in place.\n\n";
		} else {
			std::cout << "Invalid option.\n\n";
		}
	} else {
		std::cout << "You do not have a reservation to cancel.\n\n";
	}
}

// Removes user account from the system
void User::DeleteAccount(class Admin& admin) {
	int index;
	int numSeats;
	std::string accountName = username;
	char option;
	std::cout << "Are you sure you would like to delete your account? Type 'y' for yes or 'n' for no: ";
	std::cin >> option;

	if (option == 'y') {
        index = admin.SearchUser(accountName);
		
		if (travelScheduleID != -1) {
			numSeats = GetNumberOfSeats();
			admin.GetSchedule(travelScheduleID).AddSeats(numSeats);
			admin.UpdateTravelSchedule();
		}

		admin.RemoveUser(index);
		std::cout << "Your account has been removed from the system.\n\n";
	} else if (option != 'n') {
        std::cout << "Invalid option.\n\n";
	}
}

// Sets the username for user account
void User::SetUsername(const char* const inputUsername) {
    strcpy(username, inputUsername);
}

// Sets the password for user account
void User::SetPassword(const char* const inputPassword) {
    strcpy(password, inputPassword);
}

// Sets the travel schedule ID for user account
void User::SetTravelScheduleID(int inputTravelScheduleID) {
	travelScheduleID = inputTravelScheduleID;
}

// Sets the number of seats for a travel schedule that are reserved by the user
void User::SetNumberOfSeats(int inputNumberOfSeats) {
	numSeats = inputNumberOfSeats;
}

// Returns the username for user account
const char * const User::GetUsername() const {
	return username;
}

// Returns the password for user account
const char * const User::GetPassword() const {
	return password;
}

// Returns the travel schedule ID for user account
int User::GetTravelScheduleID() const {
	return travelScheduleID;
}

// Returns the number of seats for a travel schedule that are reserved by the user
int User::GetNumberOfSeats() const {
	return numSeats;
}

// Displays user travel schedule reservation
void User::DisplayReservation(Admin& admin) {
	if (travelScheduleID != -1) {
		if (numSeats == 1) {
			std::cout << "\nYou have booked " << numSeats << " seat for the following travel schedule:\n";
		} else {
			std::cout << "\nYou have booked " << numSeats << " seats for the following travel schedule:\n";
		}
		
		admin.DisplayTravelSchedules(travelScheduleID);
	} else {
		std::cout << "You do not have a travel reservation.\n\n";
	}
}

// Displays account information for a user including their travel schedule reservation
void User::DisplayAccountInformation(const Admin& admin) const {
	std::cout << "Your user informaation is:\n";
	std::cout << "Username: " << username << "\n";
	std::cout << "Password: " << password << "\n";
	
	if (travelScheduleID == -1) {
		std::cout << "You do not have any travel reservations.\n\n";
	} else {
		if (numSeats == 1) {
			std::cout << "\nYou have booked " << numSeats << " seat for the following travel schedule:\n";
		} else {
			std::cout << "\nYou have booked " << numSeats << " seats for the following travel schedule:\n";
		}
		
		admin.DisplayTravelSchedules(travelScheduleID);
	}
}

// Displays titles of user account information
void User::DisplayUserAccountInformationHeader() {
	const int largeSpacing = 20;
	const std::string largeSeparator = "--------------------";

    std::cout << "|" << largeSeparator << "|" << largeSeparator << "|" << largeSeparator << "|" << largeSeparator << "|\n";
	std::cout << "|" << std::left << std::setw(largeSpacing) << "Username" << "|" << std::left << std::setw(largeSpacing) << "Password" << "|" << std::left << std::setw(largeSpacing) << "Travel Schedule ID" << "|" << std::left << std::setw(largeSpacing) << "Number of Seats" << "|\n";
	std::cout << "|" << largeSeparator << "|" << largeSeparator << "|" << largeSeparator << "|" << largeSeparator << "|\n";
}

// Displays user account information
void User::DisplayUserAccountInformation(int lastUserAccount) const {
	const int largeSpacing = 20;
	const std::string largeSeparator = "--------------------";

	std::cout << "|" << std::left << std::setw(largeSpacing) << username << "|" << std::left << std::setw(largeSpacing) << password << "|" << std::left << std::setw(largeSpacing) << travelScheduleID << "|" << std::left << std::setw(largeSpacing) << numSeats << "|\n";

	if (lastUserAccount == 1) {
		std::cout << "|" << largeSeparator << "|" << largeSeparator << "|" << largeSeparator << "|" << largeSeparator << "|\n\n";
	}
}

// Loads user account data from a file and assigns it to a user account instance
void User::LoadUserInformation(std::string& userInformation) {
    std::istringstream inputStringStream(userInformation);
	std::string attribute;
	getline(inputStringStream, attribute, ',');
	std::strcpy((*this).username, attribute.c_str());
	getline(inputStringStream, attribute, ',');
	std::strcpy((*this).password, attribute.c_str());
	getline(inputStringStream, attribute, ',');
	(*this).travelScheduleID = std::stoi(attribute);
	getline(inputStringStream, attribute, ',');
	(*this).numSeats = std::stoi(attribute);
}

// Writes user account data to a file
void User::WriteUserInformation(std::ofstream& out) {
	out << (*this).username << "," << (*this).password << "," << (*this).travelScheduleID << "," << (*this).numSeats << "\n";
}