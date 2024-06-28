#pragma once
#include "stdafx.h"
#include "Bus.h"

struct Route
{
	std::vector<const TransportInfo*> transports;
	Time totalTime;
	double totalFee = 0;
	double totalDistance = 0;
	double carbonSavings = 0;

	Route(std::vector<const TransportInfo*> const& list);

	friend std::ostream& operator<<(std::ostream& out, Route const& other);
};

