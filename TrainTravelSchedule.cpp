#include "TrainTravelSchedule.h"
#include <fstream>
#include <sstream>

// Prompts administrative user for travel schedule information
void TrainTravelSchedule::GetTravelInformation() {
	std::cout << "Enter the details of the travel route.\n";
	std::cout << "Train name: ";
	std::cin >> trainName;
	std::cout << "Boarding point: ";
	std::cin >> boardingPoint;
	std::cout << "Destination point: ";
	std::cin >> destinationPoint;
	std::cout << "Number of seats on train: ";
	std::cin >> totalSeats;
	availableSeats = totalSeats;
	std::cout << "Train fare in $: ";
	std::cin >> trainFare;
	std::cout << "Date of travel with month (1-12), day (1-31), and year (e.g. 2022): ";
	std::cin >> t.tm_mon >> t.tm_mday >> t.tm_year;
	std::cout << "Time of department with hour (0-23) and minute (0-59): ";
	std::cin >> t.tm_hour >> t.tm_min;
	std::cout << "Travel time (hours-minutes): ";
	std::cin >> durationHr >> durationMin;
}

// Adds seats that are available for reservation to a travel schedule
void TrainTravelSchedule::AddSeats(int numSeats) {
	availableSeats += numSeats;
}

// Returns the travel schedule ID for a travel schedule
int TrainTravelSchedule::GetID() const {
	return travelScheduleID;
}

// Returns the number of seats that are available for reservation for a travel schedule
int TrainTravelSchedule::GetAvailableSeats() const {
	return availableSeats;
}

// Sets the travel schedule ID for a travel schedule instance
void TrainTravelSchedule::SetTrainTravelID(int id) {
	travelScheduleID = id;
}

// Displays titles of travel schedule information
void TrainTravelSchedule::DisplayTravelInformationHeader() {
	const int smallSpacing = 10;
	const int largeSpacing = 20;
	const int largeSpacing2 = 25;
	const std::string smallSeparator = "----------";
	const std::string largeSeparator = "--------------------";
	const std::string largeSeparator2 = "-------------------------";

	std::cout << "|" << largeSeparator << "|" << largeSeparator2 << "|" << largeSeparator2
		      << "|" << largeSeparator2 << "|" << smallSeparator << "|" << smallSeparator
		      << "|" << smallSeparator << "|" << smallSeparator << "|" << smallSeparator << "|\n";

	std::cout << "|" << std::left << std::setw(largeSpacing) << "Travel Schedule ID" << "|" << std::left << std::setw(largeSpacing2) << "Train Name" << "|" << std::left << std::setw(largeSpacing2) << "Boarding Point"
		      << "|" << std::left << std::setw(largeSpacing2) << "Destination Point" << "|" << std::left << std::setw(smallSpacing) << "Available" << "|" << std::left << std::setw(smallSpacing) << "Train Fare"
		      << "|" << std::left << std::setw(smallSpacing) << "Travel" << "|" << std::left << std::setw(smallSpacing) << "Departure" << "|" << std::left << std::setw(smallSpacing) << "Duration" << "|\n";

	std::cout << "|" << std::left << std::setw(largeSpacing) << " " << "|" << std::left << std::setw(largeSpacing2) << " " << "|" << std::left << std::setw(largeSpacing2) << " "
	          << "|" << std::left << std::setw(largeSpacing2) << " " << "|" << std::left << std::setw(smallSpacing) << "Seats" << "|" << std::left << std::setw(smallSpacing) << " "
		      << "|" << std::left << std::setw(smallSpacing) << "Date" << "|" << std::left << std::setw(smallSpacing) << "Time" << "|" << std::left << std::setw(smallSpacing) << "of Travel" << "|\n";

	std::cout << "|" << largeSeparator << "|" << largeSeparator2 << "|" << largeSeparator2
	          << "|" << largeSeparator2 << "|" << smallSeparator << "|" << smallSeparator
		      << "|" << smallSeparator << "|" << smallSeparator << "|" << smallSeparator << "|\n";
}

// Displays travel schedule information
void TrainTravelSchedule::DisplayTravelInformation(int lastSchedule) const {
	std::stringstream trainFareStringStream;
	trainFareStringStream << std::fixed << std::setprecision(2) << trainFare;
	std::string trainFareStringFloat = trainFareStringStream.str();
	const std::string trainFareString = "$" + trainFareStringFloat;
	const std::string travelMonthString = (std::to_string(t.tm_mon).size() == 1) ? "0" + std::to_string(t.tm_mon) : std::to_string(t.tm_mon);
	const std::string travelDayString = (std::to_string(t.tm_mday).size() == 1) ? "0" + std::to_string(t.tm_mday) : std::to_string(t.tm_mday);
	const std::string travelDateString = travelMonthString + "/" + travelDayString + "/" + std::to_string(t.tm_year);
	const std::string travelHrString = (std::to_string(t.tm_hour).size() == 1) ? "0" + std::to_string(t.tm_hour) : std::to_string(t.tm_hour);
	const std::string travelMinString = (std::to_string(t.tm_min).size() == 1) ? "0" + std::to_string(t.tm_min) : std::to_string(t.tm_min);
	const std::string travelTimeString = travelHrString + ":" + travelMinString;
	const std::string travelDurationString = std::to_string(durationHr) + "h" + " " + std::to_string(durationMin) + "m";
	const int smallSpacing = 10;
	const int largeSpacing = 20;
	const int largeSpacing2 = 25;
    const std::string smallSeparator = "----------";
	const std::string largeSeparator = "--------------------";
	const std::string largeSeparator2 = "-------------------------";

	std::cout << "|" << std::left << std::setw(largeSpacing) << travelScheduleID << "|" << std::left << std::setw(largeSpacing2) << trainName << "|" << std::left << std::setw(largeSpacing2) << boardingPoint
		      << "|" << std::left << std::setw(largeSpacing2) << destinationPoint << "|" << std::left << std::setw(smallSpacing) << availableSeats << "|" << std::left << std::setw(smallSpacing) << trainFareString
		      << "|" << std::left << std::setw(smallSpacing) << travelDateString << "|" << std::left << std::setw(smallSpacing) << travelTimeString << "|" << std::left << std::setw(smallSpacing) << travelDurationString << "|\n";

	if (lastSchedule == 1) {
		std::cout << "|" << largeSeparator << "|" << largeSeparator2 << "|" << largeSeparator2
	              << "|" << largeSeparator2 << "|" << smallSeparator << "|" << smallSeparator
		          << "|" << smallSeparator << "|" << smallSeparator << "|" << smallSeparator << "|\n\n";
	}
}

// Loads data for a travel schedule from a file and assigns it to a travel schedule instance
void TrainTravelSchedule::LoadScheduleInformation(std::string& scheduleInformation) {
	std::istringstream inputStringStream(scheduleInformation);
	std::string attribute;
	getline(inputStringStream, attribute, ',');
	(*this).travelScheduleID = std::stoi(attribute);
	getline(inputStringStream, attribute, ',');
	std::strcpy((*this).trainName, attribute.c_str());
	getline(inputStringStream, attribute, ',');
	std::strcpy((*this).boardingPoint, attribute.c_str());
	getline(inputStringStream, attribute, ',');
	std::strcpy((*this).destinationPoint, attribute.c_str());
	getline(inputStringStream, attribute, ',');
	(*this).availableSeats = std::stoi(attribute);
	getline(inputStringStream, attribute, ',');
	attribute.erase(std::remove(attribute.begin(), attribute.end(), '$'), attribute.end());
	(*this).trainFare = std::stof(attribute);
	getline(inputStringStream, attribute, ',');
    std::stringstream dateStringStream(attribute);
	getline(dateStringStream, attribute, '/');
	(*this).t.tm_mon = std::stoi(attribute);
	getline(dateStringStream, attribute, '/');
	(*this).t.tm_mday = std::stoi(attribute);
	getline(dateStringStream, attribute);
	(*this).t.tm_year = std::stoi(attribute);
	getline(inputStringStream, attribute, ',');
    std::stringstream timeStringStream(attribute);
	getline(timeStringStream, attribute, ':');
	(*this).t.tm_hour = std::stoi(attribute);
	getline(timeStringStream, attribute);
	(*this).t.tm_min = std::stoi(attribute);
	getline(inputStringStream, attribute);
	std::stringstream durationStringStream(attribute);
	getline(durationStringStream, attribute, 'h');
	(*this).durationHr = std::stoi(attribute);
	getline(durationStringStream, attribute, 'm');
	(*this).durationMin = std::stoi(attribute);
}

// Writes travel schedule data to a file
void TrainTravelSchedule::WriteScheduleInformation(std::ofstream& out) {
    std::stringstream trainFareStringStream;
	trainFareStringStream << std::fixed << std::setprecision(2) << (*this).trainFare;
	std::string trainFareStringFloat = trainFareStringStream.str();
	const std::string travelMonthString = (std::to_string((*this).t.tm_mon).size() == 1) ? "0" + std::to_string((*this).t.tm_mon) : std::to_string((*this).t.tm_mon);
	const std::string travelDayString = (std::to_string((*this).t.tm_mday).size() == 1) ? "0" + std::to_string((*this).t.tm_mday) : std::to_string((*this).t.tm_mday);
	const std::string travelDateString = travelMonthString + "/" + travelDayString + "/" + std::to_string((*this).t.tm_year);
	const std::string travelHrString = (std::to_string((*this).t.tm_hour).size() == 1) ? "0" + std::to_string((*this).t.tm_hour) : std::to_string((*this).t.tm_hour);
	const std::string travelMinString = (std::to_string((*this).t.tm_min).size() == 1) ? "0" + std::to_string((*this).t.tm_min) : std::to_string((*this).t.tm_min);
	const std::string travelTimeString = travelHrString + ":" + travelMinString;
	const std::string travelDurationString = (std::to_string((*this).durationHr)) + "h" + (std::to_string((*this).durationMin)) + "m";

	out << (*this).travelScheduleID << "," << (*this).trainName << "," << (*this).boardingPoint << ","
	    << (*this).destinationPoint << "," << (*this).availableSeats << "," << "$" << trainFareStringFloat << ","
	    << travelDateString << "," << travelTimeString << "," << travelDurationString << "\n";
}