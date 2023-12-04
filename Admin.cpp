#include "Admin.h"
#include <fstream>
#include <unistd.h>

// Constructor for Admin class that loads train schedule and user data into class objects from their respective files
Admin::Admin() {
    char cwd[PATH_MAX];
	getcwd(cwd, sizeof(cwd));
	std::string cwdString(cwd);
	trainInformationFile = cwdString + "/trainInformation.txt";
	userInformationFile = cwdString + "/userInformation.txt";
	LoadScheduleData();
	LoadUserData();
}

// Adds a new travel schedule from user input
void Admin::AddTravelSchedule() {
	int id;
	int index;
	
	if (schedules.size() > 0) {
        id = schedules[schedules.size() - 1].GetID() + 1;
	} else {
		id = 0;
	}

	TrainTravelSchedule newSchedule;
	newSchedule.SetTrainTravelID(id);
	newSchedule.GetTravelInformation();
	schedules.push_back(newSchedule);
	index = schedules.size() - 1;
	WriteScheduleData(index);
	DisplayTravelSchedules();
}

// Adds a new user to the system
int Admin::AddUser() {
	char username[30];
	char password[30];
	bool usernameInUse = false;
	int index;
	std::cout << "Enter your username: ";
	std::cin >> username;

	if (SearchUser(username) != -1) {
		std::cout << "That username is already taken.\n\n";
		return -1;
	}

	User newUser;
	newUser.SetUsername(username);
	std::cout << "Enter your password: ";
	std::cin >> password;
	std::cout << std::endl;
	newUser.SetPassword(password);
	users.push_back(newUser);
	index = users.size() - 1;
	WriteUserData(index);

	return index;
}

// Adds available seats to a travel schedule
void Admin::AddAvailableSeats(int id, int numSeats) {
	int index = SearchSchedule(id);
	schedules[index].AddSeats(numSeats);
}

// Writes updated travel schedule data to a file when any travel schedule data has been changed
void Admin::UpdateTravelSchedule() {
	WriteScheduleData(-1);
}

// Writes updated user account data to a file when any user account data has been changed
void Admin::UpdateUser() {
	WriteUserData(-1);
}

// Removes a travel schedule from the system
void Admin::RemoveTravelSchedule() {
    int id;
	int index;

	if (schedules.size() > 0) {
		DisplayTravelSchedules();
		std::cout << "Enter the ID of the travel schedule you would like to remove.\n";
		std::cin >> id;
		index = SearchSchedule(id);

		if (index == -1) {
			std::cout << "There is no travel schedule with that ID in the system.\n\n";

			return;
		} else {
			for (int i = 0; i < users.size(); i++) {
				if (users[i].GetTravelScheduleID() == id) {
					users[i].SetTravelScheduleID(-1);
					users[i].SetNumberOfSeats(0);
				}
			}

			UpdateUser();
			schedules.erase(schedules.begin() + index);
			RemoveScheduleData(id);
			std::cout << "The travel schedule has been removed from the system.\n";

			if (schedules.size() > 0) {
				DisplayTravelSchedules();
			}
		}
	} else {
		std::cout << "There are no travel schedules in the system.\n\n";
	}
}

// Removes a user account from the system after prompting for a user account to remove
void Admin::RemoveUser() {
	std::string username;
	int index;
	int travelScheduleID;
	int travelScheduleIndex;
	int numSeats;

	if (users.size() > 0) {
		std::cout << "Enter the username of the user account you woud like to remove.\n";
		std::cin >> username;
		index = SearchUser(username);

		if (index == -1) {
			std::cout << "That username does not exist in the system.\n\n";

			return;
		} else {
			travelScheduleID = users[index].GetTravelScheduleID();

			if (travelScheduleID != -1) {
				travelScheduleIndex = SearchSchedule(travelScheduleID);
			    numSeats = users[index].GetNumberOfSeats();
				schedules[travelScheduleIndex].AddSeats(numSeats);
				UpdateTravelSchedule();
			}

			users.erase(users.begin() + index);
			RemoveUserData(username);
			std::cout << "User account " + username + " has been removed from the system.\n\n";
		}
	} else {
		std::cout << "There are no user accounts in the system.\n\n";
	}
}

// Removes a user account from the system given the user account index as an input argument
void Admin::RemoveUser(int index) {
	std::string username = users[index].GetUsername();
	users.erase(users.begin() + index);
    RemoveUserData(username);
}

// Returns the index of a travel schedule given the travel schedule ID as an input argument
int Admin::SearchSchedule(int id) const {
	for (int i = 0; i < schedules.size(); i++) {
		if (schedules[i].GetID() == id) {
			return i;
		}
	}

	return -1;
}

// Returns a user account index given the account username as an input argument
int Admin::SearchUser(const std::string& username) const {
	for (int i = 0; i < users.size(); i++) {
		if (std::strcmp(users[i].GetUsername(), username.c_str()) == 0) {
			return i;
		}
	}

	return -1;
}

// Returns a travel schedule object given the travel schedule ID as an input argument
TrainTravelSchedule& Admin::GetSchedule(int id) {
	int index = SearchSchedule(id);

	return schedules[index];
}

// Returns a user account object given the user account index as an input argument
User& Admin::GetUser(int index) {
	return users[index];
}

// Displays all travel schedules in the system
void Admin::DisplayTravelSchedules() const {
    if (schedules.size() > 0)
	{
		std::cout << "\nThe travel schedules are:\n";
		TrainTravelSchedule::DisplayTravelInformationHeader();

		for (int i = 0; i < schedules.size(); i++) {
			if (i == (schedules.size() - 1)) {
				schedules[i].DisplayTravelInformation(1);
			} else {
				schedules[i].DisplayTravelInformation(0);
			}
		}
	} else {
		std::cout << "There is no travel schedule information to display.\n\n";
	}
}

// Displays a travel schedule given the travel schedule ID as an input argument
void Admin::DisplayTravelSchedules(int id) const {
	int idResult = SearchSchedule(id);
	TrainTravelSchedule::DisplayTravelInformationHeader();
	schedules[idResult].DisplayTravelInformation(1);
}

// Displays all user accounts in the system
void Admin::DisplayUserAccounts() const {
    if (users.size() > 0) {
		std::cout << "\nUser accounts:\n";
		User::DisplayUserAccountInformationHeader();

		for (int i = 0; i < users.size(); i++) {
			if (i == (users.size() - 1)) {
				users[i].DisplayUserAccountInformation(1);
			} else {
				users[i].DisplayUserAccountInformation(0);
			}
		}
	} else {
		std::cout << "There are no user accounts in the system.\n\n";
	}
}

// Loads travel schedule data from file into travel schedule instances
void Admin::LoadScheduleData() {
    std::ifstream in(trainInformationFile);

	if (in.get() != -1) {
		in.seekg(0);
		std::string line;
		getline(in, line);

		while (in.peek() != EOF) {
			getline(in, line);
			TrainTravelSchedule trainTravelSchedule;
			trainTravelSchedule.LoadScheduleInformation(line);
			schedules.push_back(trainTravelSchedule);
		}
	}

	in.close();
}

// Loads user account data from file into user account instances
void Admin::LoadUserData() {
	std::ifstream in(userInformationFile);

	if (in.get() != -1) {
		in.seekg(0);
		std::string line;
		getline(in, line);

		while (in.peek() != EOF) {
			getline(in, line);
			User user;
			user.LoadUserInformation(line);
			users.push_back(user);
		}
	}

	in.close();
}

// Writes all travel schedule data to a file or appends the data of an added travel schedule to a file
void Admin::WriteScheduleData(int index) {
	std::ifstream in(trainInformationFile);
	std::ofstream out;
	std::string travelInformationHeader = "Travel Schedule ID,Train Name,Boarding Point,Destination Point,Available Seats,Train Fare,Travel Date,Travel Time,Duration of Travel";
	int writeTravelInformationHeader = 1;

    if (in.get() != -1) {
		in.seekg(0);
		std::string line;
		
		if (in.peek() != EOF) {
			getline(in, line);

			if (line == travelInformationHeader) {
				writeTravelInformationHeader = 0;
			}
		}
	}

	in.close();

    if (index == -1) {
		out.open(trainInformationFile);
		out << travelInformationHeader << "\n";
		
		for (int i = 0; i < schedules.size(); i++) {
			schedules[i].WriteScheduleInformation(out);
		}
	}
	else if (writeTravelInformationHeader == 1) {
		out.open(trainInformationFile);
		out << travelInformationHeader << "\n";
		schedules[index].WriteScheduleInformation(out);
	} else {
		out.open(trainInformationFile, std::ios::app);
		schedules[index].WriteScheduleInformation(out);
	}

	out.close();
}

// Writes all user account data to a file or appends the data of an added user account to a file
void Admin::WriteUserData(int index) {
	std::ifstream in(userInformationFile);
	std::ofstream out;
	std::string userInformationHeader = "Username,Password,Travel Schedule ID,Number of Seats";
	int writeUserInformationHeader = 1;

	if (in.get() != -1) {
		in.seekg(0);
		std::string line;

		if (in.peek() != EOF) {
			getline(in, line);

			if (line == userInformationHeader) {
				writeUserInformationHeader = 0;
			}
		}
	}

	in.close();

    if (index == -1) {
		out.open(userInformationFile);
		out << userInformationHeader << "\n";

		for (int i = 0; i < users.size(); i++) {
			users[i].WriteUserInformation(out);
		}
	}
	else if (writeUserInformationHeader == 1) {
		out.open(userInformationFile);
		out << userInformationHeader << "\n";
		users[index].WriteUserInformation(out);
	} else {
		out.open(userInformationFile, std::ios::app);
		users[index].WriteUserInformation(out);
	}

	out.close();
}

// Removes the data of a deleted travel schedule from a file by writing all travel schedule data to the file except for the deleted travel schedule data
void Admin::RemoveScheduleData(int id) {
	std::vector<std::string> scheduleInformation;
    std::ifstream in(trainInformationFile);
	std::ofstream out;

	if (in.get() != -1) {
		in.seekg(0);
		std::string line;

		while (in.peek() != EOF) {
			getline(in, line);
			
			if (int(line[0] - '0') != id) {
				scheduleInformation.push_back(line);
			}
		}
	}

	in.close();
	out.open(trainInformationFile);

	for (int i = 0; i < scheduleInformation.size(); i++) {
		out << scheduleInformation[i] << "\n";
	}

	out.close();
}

// Removes the data of a deleted user account from a file by writing all user account data to the file except for the deleted user account data
void Admin::RemoveUserData(const std::string& username) {
    std::vector<std::string> userInformation;
	std::ifstream in(userInformationFile);
	std::ofstream out;
	int usernameLength = username.size();

	if (in.get() != -1) {
		in.seekg(0);
		std::string line;

		while (in.peek() != EOF) {
			getline(in, line);

			if (line.substr(0, usernameLength) != username) {
				userInformation.push_back(line);
			}
		}
	}

	in.close();
	out.open(userInformationFile);

	for (int i = 0; i < userInformation.size(); i++) {
		out << userInformation[i] << "\n";
	}

	out.close();
}