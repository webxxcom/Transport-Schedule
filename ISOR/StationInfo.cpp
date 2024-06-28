#include "stdafx.h"
#include "StationInfo.h"

//Constructors
StationInfo::StationInfo()
	: name(), time(), platform(0)
{

}

StationInfo::StationInfo(std::string_view name, Clocks const& time, int platform)
	: name(name), time(time), platform(platform)
{
	validateCoordinates(this->name);
}

bool StationInfo::validateCoordinates(std::string const& str)
{
	const auto& it = Coordinates::cityCoordinates.find(str);
	if (it != Coordinates::cityCoordinates.end())
		this->coords = Coordinates(it->second);
	else
		return false;
	return true;
}

//Input/output oprators
std::ostream& operator<<(std::ostream& out, StationInfo const& other)
{
	out << "Train to " << other.name << " departures at " << other.time << " at platform " << other.platform;

	return out;
}

std::istream& operator>>(std::istream& in, StationInfo& other)
{
	std::string name;
	Clocks time;
	int platform;
	std::cout << "Enter station name: ";
	clearBuffer(in);
	std::getline(in, name);

	validateInput(time, in, "");

	std::cout << "Enter the platform: ";
	validateInput(platform, in);

	if (!other.validateCoordinates(name))
	{
		std::cout << "The coordinates of the given city was not found\n" << "Please provide them.\n";
		double latitude, longitude;

		std::cout << "Latitude: ";
		validateInput(latitude, in);

		std::cout << "longitude: ";
		validateInput(longitude, in);

		Coordinates::cityCoordinates.try_emplace(name, latitude, longitude);
	}

	other = StationInfo(name, time, platform);
	return in;
}