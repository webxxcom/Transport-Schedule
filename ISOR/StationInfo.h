#pragma once
#include "stdafx.h"
#include "Clocks.h"

struct StationInfo
{
	Coordinates coords;
	std::string name;
	Clocks time;
	int platform;

	//Constructors/Destructors
	StationInfo();

	StationInfo(std::string_view name, Clocks const& time, int platform);

	//Methods
	bool validateCoordinates(std::string const& str);

	//Input/output operators
	friend std::ostream& operator<<(std::ostream& out, StationInfo const& other);
	friend std::istream& operator>>(std::istream& in, StationInfo& other);
};
