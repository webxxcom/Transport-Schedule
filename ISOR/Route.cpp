#include "stdafx.h"
#include "Route.h"

Route::Route(std::vector<const TransportInfo*> const& list)
{
	auto it = list.begin();
	for (size_t i = 0; it != list.end(); ++i, ++it)
	{
		this->transports.emplace_back(*it);
		const auto& departureTime = transports[i]->getDeparture().time;
		const auto& destinationTime = transports[i]->getDestination().time;

		// Calculate the travel time
		if (destinationTime > departureTime)
			this->totalTime += destinationTime - departureTime;
		else
			this->totalTime += Time(24, 00, 00) - departureTime + destinationTime;

		// Calculate the waiting time if it's not the first leg
		if (i > 0)
		{
			const auto& previousDestinationTime = transports[i - 1]->getDestination().time;
			if (departureTime < previousDestinationTime) 
				this->totalTime += Time(24, 0, 0) - previousDestinationTime + departureTime;
		}
		double temp_curr_distance = Coordinates::calcDistBetween(transports[i]->getDeparture().coords, transports[i]->getDestination().coords);
		this->totalFee += transports[i]->getFee();
		this->totalDistance += temp_curr_distance;
		this->carbonSavings += transports[i]->calculateEmissionSavings(temp_curr_distance);
	}
}

std::ostream& operator<<(std::ostream& out, Route const& other)
{
	std::cout << "Travel time: " << other.totalTime << "\n\n";
	for (auto& it : other.transports)
	{
		if (it->getType() == E_Train)
		{
			auto tr = dynamic_cast<const Train*>(it);
			std::cout << *tr;
		}
		else if (it->getType() == E_Plane)
		{
			auto tr = dynamic_cast<const Plane*>(it);
			std::cout << *tr;
		}
		
		//Do not need to cast to bus because it stores no extra information
		else
			std::cout << *it;
	}

	std::cout << "Total Fee: " << other.totalFee << "$\n"
		<< "Total distance: " << other.totalDistance << "km\n"
		<< "By this trip you will " << (other.carbonSavings > 0 ? "reduce" : "increase")
		<< " carbon emissions by " << std::abs(other.carbonSavings) << "kg\n";

	return out;
}