#ifndef USER_H
#define USER_H
#include <iostream>

class User {
	public:
		void MakeReservation(class Admin& admin, int index);
		void CancelReservation(class Admin& admin, int index);
		void DeleteAccount(class Admin& admin);
		const char* const GetUsername() const;
		const char* const GetPassword() const;
		int GetTravelScheduleID() const;
		int GetNumberOfSeats() const;
		void SetUsername(const char* const inputUsername);
		void SetPassword(const char* const inputPassword);
		void SetTravelScheduleID(int inputTravelScheduleID);
		void SetNumberOfSeats(int inputNumberOfSeats);
		void DisplayReservation(class Admin& admin);
		void DisplayAccountInformation(const class Admin& admin) const;
		static void DisplayUserAccountInformationHeader();
		void DisplayUserAccountInformation(int lastUserAccount) const;
		void LoadUserInformation(std::string& userInformation);
		void WriteUserInformation(std::ofstream& out);
	private:
		constexpr static int maxSize = 30;
		char username[maxSize];
		char password[maxSize];
		int travelScheduleID = -1;
		int numSeats = 0;
};

#endif