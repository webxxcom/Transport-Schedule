#pragma once
#include "stdafx.h"
#include "PtrArray.cpp"

class Time
{
protected:
	time_t hours;
	time_t minutes;
	time_t seconds;

	time_t total_secs() const;
public:
	//Constructors
	Time();

	//Initialization constructors
	Time(time_t h, time_t m, time_t s);
	explicit Time(std::string_view str);

	// Getter methods
	time_t getHours() const;
	time_t getMinutes() const;
	time_t getSeconds() const;

	// Setter methods
	virtual bool setTime(time_t h, time_t m, time_t s);
	virtual bool parseString(std::string_view str);

	/* Operators */
	//Arithmetic with value
	Time operator+(time_t const value) const;

	Time operator-(time_t const value)const;

	Time operator+=(time_t const value);

	Time operator-=(time_t const value);

	//Arithmetic with object
	Time operator+(Time const& other) const;

	Time operator-(Time const& other) const;

	Time operator+=(Time const& other);

	Time operator-=(Time const& other);

	Time& operator=(Time const& other);

	std::strong_ordering operator<=>(Time const& other) const = default;

	//Input/output operators
	friend std::ostream& operator<<(std::ostream& out, Time const& other);
	friend std::istream& operator>>(std::istream& in, Time& other);

	friend std::ofstream& operator<<(std::ofstream& ofs, Time const& other);
	friend std::ifstream& operator>>(std::ifstream& ifs, Time& other);
};