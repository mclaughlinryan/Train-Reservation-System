#include "TrainTravelSchedule.h"
#include "User.h"
#include <vector>

class Admin {
	public:
		Admin();
		void AddTravelSchedule();
		int AddUser();
		void AddAvailableSeats(int id, int numSeats);
		void UpdateTravelSchedule();
		void UpdateUser();
		void RemoveTravelSchedule();
		void RemoveUser();
		void RemoveUser(int index);
		int SearchSchedule(int id) const;
		int SearchUser(const std::string& username) const;
		TrainTravelSchedule& GetSchedule(int id);
		User& GetUser(int index);
		void DisplayTravelSchedules() const;
		void DisplayTravelSchedules(int id) const;
		void DisplayUserAccounts() const;
	private:
		void LoadScheduleData();
		void LoadUserData();
		void WriteScheduleData(int index);
		void WriteUserData(int index);
		void RemoveScheduleData(int id);
		void RemoveUserData(const std::string& username);
	private:
		std::vector<TrainTravelSchedule> schedules;
		std::vector<User> users;
		std::string trainInformationFile;
		std::string userInformationFile;
};