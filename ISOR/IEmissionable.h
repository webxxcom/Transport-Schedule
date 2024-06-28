#pragma once
#include "stdafx.h"
#include "ISerializable.h"

class IEmissionable
{
protected:
    double emissionFactor;

public:
    IEmissionable() = delete;
    explicit IEmissionable(double emissionFactor) : emissionFactor(emissionFactor) { }

    virtual ~IEmissionable() = default;

    virtual double calculateFuelConsumption(double distance) const = 0;
    virtual double calculateEmissions(double distance) const = 0;
};
