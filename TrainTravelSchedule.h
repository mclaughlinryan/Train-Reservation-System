#include <iostream>

class TrainTravelSchedule {
	public:
		void GetTravelInformation();
		void AddSeats(int numSeats);
		int GetID() const;
		int GetAvailableSeats() const;
		void SetTrainTravelID(int id);
		static void DisplayTravelInformationHeader();
		void DisplayTravelInformation(int lastSchedule) const;
		void LoadScheduleInformation(std::string& scheduleInformation);
		void WriteScheduleInformation(std::ofstream& out);
	private:
		static constexpr int maxSize = 30;
		int travelScheduleID = 0;
		char trainName[maxSize];
		char boardingPoint[maxSize];
		char destinationPoint[maxSize];
		int totalSeats;
		int availableSeats;
		float trainFare;
		struct tm t = {};
		int durationHr;
		int durationMin;
};