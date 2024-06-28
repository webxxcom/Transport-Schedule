#include "stdafx.h"
#include "Bus.h"

Bus::Bus()
    : TransportInfo(), fuelEfficiency()
{
    emissionFactor = 8.7;
}

Bus::Bus(int ID, StationInfo const& departure, StationInfo const& destination, double fee,
    double fuelEfficiency)
    : TransportInfo(ID, departure, destination, fee),
    fuelEfficiency(fuelEfficiency)
{
    emissionFactor = 8.7;
}

TransportTypes Bus::getType() const
{
    return TransportTypes::E_Bus;
}

void Bus::serialize(std::ofstream& ofs) const
{
    ofs << static_cast<const TransportInfo&>(*this)
        << ',' << this->fuelEfficiency << '\n';
}

void Bus::deserialize(std::stringstream& ss)
{
    ss >> static_cast<TransportInfo&>(*this);

    std::string item;
    std::getline(ss, item, ',');
    this->fuelEfficiency = std::stod(item);
}

double Bus::calculateFuelConsumption(double distance) const
{
    // Fuel consumption logic specific to a bus
    return distance / fuelEfficiency;
}

double Bus::calculateEmissions(double distance) const
{
    // Emission calculation specific to a bus
    return calculateFuelConsumption(distance) * emissionFactor; // kg CO2 per liter of diesel
}

TransportInfo* Bus::clone() const
{
    return new Bus(*this);
}

std::istream& operator>>(std::istream& in, Bus& other)
{
    in >> static_cast<TransportInfo&>(other);
    
    std::cout << "Enter the bus' fuel efficiency: ";
    validateInput(other.fuelEfficiency, in);

    return in;
}

