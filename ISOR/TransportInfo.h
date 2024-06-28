#pragma once
#include "StationInfo.h"

class TransportInfo :
	public ISerializable<TransportTypes, std::ofstream, std::stringstream>,
	public IEmissionable {
protected:
	StationInfo departure;
	StationInfo destination;
	double fee;
	int id;

public:
	TransportInfo();

	TransportInfo(const int ID, StationInfo const& departure, StationInfo const& destination, double fee);

	~TransportInfo() override = default;

	// Getter methods
	StationInfo const& getDeparture() const;
	StationInfo const& getDestination() const;
	double getFee() const;
	int getID() const;

	//Pure virtual functions
	virtual TransportInfo* clone() const = 0;

	//Methods 
	virtual double calculateEmissionSavings(double distance) const;

	//Overriden methods
	std::string_view getTypeString() const final;

	//Operators overload
	TransportInfo& operator=(TransportInfo const& other);
	bool operator==(TransportInfo const& other) const;

	//Input/output operators
	friend std::ostream& operator<<(std::ostream& out, TransportInfo const& other);
	friend std::ofstream& operator<<(std::ofstream& ofs, TransportInfo const& other);
	friend std::istream& operator>>(std::istream& in, TransportInfo& other);
	friend std::stringstream& operator>>(std::stringstream& ifs, TransportInfo& other);
};

