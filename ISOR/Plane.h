#pragma once
#include "stdafx.h"
#include "Train.h"

class Plane :
    public TransportInfo
{
private:
    std::string flightNumber;
    double fuelConsumptionPerKm;
public:
    Plane();
    Plane(const int ID, StationInfo const& departure, StationInfo const& destination, double fee,
        double fuelConsumptionPerKm, std::string_view flightNumber);

    // Inherited via TransportInfo
    TransportTypes getType() const override;
    void serialize(std::ofstream& out) const override;
    void deserialize(std::stringstream& ss) override;

    double calculateFuelConsumption(double distance) const override;
    double calculateEmissions(double distance) const override;
    TransportInfo* clone() const override;

    friend std::istream& operator>>(std::istream& in, Plane& other);
    friend std::ostream& operator<<(std::ostream& out, Plane const& other);
};

