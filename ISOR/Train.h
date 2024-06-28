#pragma once
#include "stdafx.h"
#include "TransportInfo.h"

class Train :
    public TransportInfo
{
private:
    double cars;
    double passengersPerCar;

public:
    Train() = default;
    Train(const int ID, StationInfo const& departure, StationInfo const& destination, double fee,
        double passengersPerCar, double cars);

    // Inherited via TransportInfo
    TransportTypes getType() const override;
    void serialize(std::ofstream& out) const override;
    void deserialize(std::stringstream& ss) override;

    double calculateFuelConsumption(double distance) const override;
    double calculateEmissions(double distance) const override;
    TransportInfo* clone() const override;

    friend std::istream& operator>>(std::istream& in, Train& other);
    friend std::ostream& operator<<(std::ostream& out, Train const& other);
};

