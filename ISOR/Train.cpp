#include "stdafx.h"
#include "Train.h"

Train::Train(const int ID, StationInfo const& departure, StationInfo const& destination, double fee,
	double cars, double passengersPerCar)
	: TransportInfo(ID, departure, destination, fee),
	cars(cars), passengersPerCar(passengersPerCar)
{

}

TransportTypes Train::getType() const
{
	return E_Train;
}

void Train::serialize(std::ofstream& out) const
{
	out << static_cast<TransportInfo const&>(*this) << ','
		<< this->cars << ',' << this->passengersPerCar << '\n';
}

void Train::deserialize(std::stringstream& ss)
{
	ss >> static_cast<TransportInfo&>(*this);

	std::string item;
	std::getline(ss, item, ',');
	this->cars = std::stoi(item);

	std::getline(ss, item, ',');
	this->passengersPerCar = std::stoi(item);
}

double Train::calculateFuelConsumption(double distance) const
{
	return 0;
}

double Train::calculateEmissions(double distance) const
{
	return 0;
}

TransportInfo* Train::clone() const
{
	return new Train(*this);
}

std::istream& operator>>(std::istream& in, Train& other)
{
	in >> static_cast<TransportInfo&>(other);

	std::cout << "Enter the train's number of cars: ";
	validateInput(other.cars, in);

	std::cout << "Enter the train's number of passengers for each car: ";
	validateInput(other.passengersPerCar, in);

	return in;
}

std::ostream& operator<<(std::ostream& out, Train const& other)
{
	out << static_cast<TransportInfo const&>(other) 
		<< "\nCars: " << other.cars
		<< "\nPassengers per car: " << other.passengersPerCar <<
		"\n---------------------------------\n";

	return out;
}
