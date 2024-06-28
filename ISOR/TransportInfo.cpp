#include "stdafx.h"
#include "TransportInfo.h"

//Public constructors
TransportInfo::TransportInfo()
	: IEmissionable(0), departure(), destination(), fee(0), id(0)
{

}

TransportInfo::TransportInfo(const int ID, StationInfo const& departure, StationInfo const& destination,
	double fee)
	: IEmissionable(0), id(ID), departure(departure), destination(destination), fee(fee)
{

}

//Getters
StationInfo const& TransportInfo::getDeparture() const
{
	return this->departure;
}

StationInfo const& TransportInfo::getDestination() const
{
	return this->destination;
}

int TransportInfo::getID() const
{
	return this->id;
}

double TransportInfo::getFee() const
{
	return this->fee;
}

std::string_view TransportInfo::getTypeString() const
{
	return StaticData::vehiclesStringTypes.at(this->getType());
}

//Methods
double TransportInfo::calculateEmissionSavings(double distance) const
{
	double carEmissions = distance / 36. * 10 * 10; //36 - fuel efficiency
	//10 - Natural gas emissions for km, 20 - average transport's number of people

	double transEmissions = this->calculateEmissions(distance);
	return carEmissions - transEmissions;
}

//Operators overload
TransportInfo& TransportInfo::operator=(TransportInfo const& other)
{
	this->departure = other.departure;
	this->destination = other.destination;
	this->fee = other.fee;
	this->id = other.id;

	return *this;
}

bool TransportInfo::operator==(TransportInfo const& other) const
{
	if (typeid(*this) != typeid(other))
		return false;

	return this->id == other.id;
}

//Input/output operators
std::ostream& operator<<(std::ostream& out, TransportInfo const& other)
{
	out << other.getTypeString() << '(' << other.id << "), " << other.fee << '$' <<
		"\nDeparture:" <<
		"\n\tFrom : " << other.departure.name <<
		"\n\tAt: " << other.departure.time <<
		"\n\tPlatform: " << other.departure.platform <<
		"\nDestination:" <<
		"\n\tTo : " << other.destination.name <<
		"\n\tAt: " << other.destination.time <<
		"\n\tPlatform: " << other.destination.platform <<
		"\nDistance: " << Coordinates::calcDistBetween(other.departure.coords, other.destination.coords) << "km.\n";
	
	return out;
}

std::ofstream& operator<<(std::ofstream& ofs, TransportInfo const& other)
{
	ofs << other.getTypeString() << ',' << other.id << ','
		<< other.departure.name << ',' << other.departure.time << ',' << other.departure.platform << ','
		<< other.destination.name << ',' << other.destination.time << ',' << other.destination.platform << ','
		<< other.fee;

	return ofs;
}

std::istream& operator>>(std::istream& in, TransportInfo& other)
{
	auto tmp = other.clone();

	std::cout << "Enter transport ID: ";
	validateInput(tmp->id, in, "Incorrect input. Re-enter ID: ");

	std::cout << "Departure:\n";
	in >> tmp->departure;

	std::cout << "Destination:\n";
	in >> tmp->destination;

	std::cout << "Fee: ";
	validateInput(tmp->fee, in, "Incorrect input. Re-enter fee: ");

	other = *tmp;
	return in;
}

std::stringstream& operator>>(std::stringstream& ss, TransportInfo& other)
{
	std::string item;
	auto tmp = other.clone();

	std::getline(ss, item, ',');
	tmp->id = std::stoi(item);

	std::getline(ss, item, ',');
	tmp->departure.name = item;
	if (!tmp->departure.validateCoordinates(item))
	{
		std::cerr << item + "'s coordinates wasn't found.\n";
		system("pause");
	}

	std::getline(ss, item, ',');
	tmp->departure.time.parseString(item);

	std::getline(ss, item, ',');
	tmp->departure.platform = std::stoi(item);

	std::getline(ss, item, ',');
	tmp->destination.name = item;
	if (!tmp->destination.validateCoordinates(item))
	{
		std::cerr << item + "'s coordinates wasn't found.\n";
		system("pause");
	}

	std::getline(ss, item, ',');
	tmp->destination.time.parseString(item);

	std::getline(ss, item, ',');
	tmp->destination.platform = std::stoi(item);

	std::getline(ss, item, ',');
	tmp->fee = std::stod(item);

	other = *tmp;
	return ss;
}
