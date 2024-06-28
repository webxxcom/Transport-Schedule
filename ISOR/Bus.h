#pragma once
#include "stdafx.h"
#include "Plane.h"

class Bus :
    public TransportInfo
{
private:
    double fuelEfficiency;

public:
    Bus();
    Bus(const int ID, StationInfo const& departure, StationInfo const& destination, double fee,
        double fuelEfficiency);

    TransportTypes getType() const override;
    void serialize(std::ofstream& out) const override;
    void deserialize(std::stringstream& ss) override;

    double calculateFuelConsumption(double distance) const override;
    double calculateEmissions(double distance) const override;
    TransportInfo* clone() const override;

    //Operators
    friend std::istream& operator>>(std::istream& in, Bus& other);
};

