#include "stdafx.h"
#include "Plane.h"

Plane::Plane()
	:TransportInfo(), fuelConsumptionPerKm(), flightNumber()
{
	emissionFactor = 12.2;
}

Plane::Plane(const int ID, StationInfo const& departure, StationInfo const& destination, double fee,
	double fuelConsumptionPerKm, std::string_view flightNumber)
	: TransportInfo(ID, departure, destination, fee),
	fuelConsumptionPerKm(fuelConsumptionPerKm), flightNumber(flightNumber)
{

}

TransportTypes Plane::getType() const
{
	return E_Plane;
}

void Plane::serialize(std::ofstream& out) const
{
	out << static_cast<TransportInfo const&>(*this) << ','
		<< this->fuelConsumptionPerKm << ',' << this->flightNumber << '\n';
}

void Plane::deserialize(std::stringstream& ss)
{
	ss >> static_cast<TransportInfo&>(*this);

	std::string item;
	std::getline(ss, item, ',');
	this->fuelConsumptionPerKm = std::stod(item);

	std::getline(ss, item, ',');
	this->flightNumber = item;
}

double Plane::calculateFuelConsumption(double distance) const
{
	return distance * this->fuelConsumptionPerKm;
}

double Plane::calculateEmissions(double distance) const
{
	return calculateFuelConsumption(distance) * this->emissionFactor 
		* 1.12;//As aircrafts emit more pollutions at higher altitudes
}

TransportInfo* Plane::clone() const
{
	return new Plane(*this);
}

std::istream& operator>>(std::istream& in, Plane& other)
{
	in >> static_cast<TransportInfo&>(other);

	std::cout << "Enter the plane's flight number: ";
	validateInput(other.flightNumber, in);

	std::cout << "Enter the plane's fuel consumption per kilometer: ";
	validateInput(other.fuelConsumptionPerKm, in);

	return in;
}

std::ostream& operator<<(std::ostream& out, Plane const& other)
{
	out << static_cast<TransportInfo const&>(other)
		<< "\nFlight number: " << other.flightNumber <<
		"\n---------------------------------\n";

	return out;
}
