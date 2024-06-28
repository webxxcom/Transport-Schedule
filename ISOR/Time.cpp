#include "stdafx.h"
#include "Time.h"

//Private methods
time_t Time::total_secs() const
{
	return  this->hours * 3600 + this->minutes * 60 + this->seconds;
}

//Constructors
Time::Time()
{
	//Do not write this->setTime as it can confuse when Time is used as base class
	//That is, anyway when constructing Time's child class the Time::setTime will be called
	Time::setTime(0, 0, 0);
}

//Initialization constructor
Time::Time(time_t h, time_t m, time_t s)
{
	Time::setTime(h, m, s);
}

Time::Time(std::string_view str)
{
	Time::parseString(str);
}

// Getter methods
time_t Time::getHours() const
{
	return hours;
}

time_t Time::getMinutes() const
{
	return minutes;
}

time_t Time::getSeconds() const
{
	return seconds;
}

// Setter methods
bool Time::setTime(time_t h, time_t m, time_t s)
{
	this->hours = h;
	this->minutes = m;
	this->seconds = s;

	return true;
}

bool Time::parseString(std::string_view str)
{
	try
	{
		time_t hours, minutes, seconds;
		std::stringstream ss(str.data());

		char delimiter;
		ss >> hours >> delimiter >> minutes >> delimiter >> seconds;

		if (ss.fail() || !this->setTime(hours, minutes, seconds))
		{
			std::cerr << "Invalid parameters for time: " << str << '\n';
			return false;
		}
	}
	catch (std::exception const& e)
	{
		std::cerr << e.what() << '\n';
		return false;
	}
	return true;
}

//Operators overloading
Time Time::operator+(time_t const value) const
{
	Time tempTime;
	time_t total_secs = this->total_secs() + value;
	if (total_secs < 0)
		total_secs = 0;

	tempTime.setTime(total_secs / 3600, total_secs / 60 % 60, total_secs % 60);
	return tempTime;
}

Time Time::operator-(time_t const value)const
{
	return this->operator+(-value);
}

Time Time::operator+=(time_t const value)
{
	Time temp = this->operator+(value);
	this->setTime(temp.hours, temp.minutes, temp.seconds);

	return *this;
}

Time Time::operator-=(time_t const value)
{
	return this->operator+=(-value);
}

Time Time::operator+(Time const& other)const
{
	return this->operator+(other.total_secs());
}

Time Time::operator-(Time const& other)const
{
	return this->operator+(Time(-other.hours, -other.minutes, -other.seconds));
}

Time Time::operator+=(Time const& other)
{
	return this->operator+=(other.total_secs());
}

Time Time::operator-=(Time const& other)
{
	return this->operator-=(other.total_secs());
}

Time& Time::operator=(Time const& other)
{
	if (this != &other)
	{
		this->hours = other.hours;
		this->minutes = other.minutes;
		this->seconds = other.seconds;
	}

	return *this;
}

//Input/output operators
std::ostream& operator<<(std::ostream& out, Time const& other)
{
	//Format string that is zero-padded to two digits(':02') 
	out << std::format("{:02}:{:02}:{:02}", other.hours, other.minutes, other.seconds);
	return out;
}

std::ofstream& operator<<(std::ofstream& ofs, Time const& other)
{
	ofs << other.hours << ',' << other.minutes << ',' << other.seconds;

	return ofs;
}

std::istream& operator>>(std::istream& in, Time& other)
{
	std::string time_str;
	std::cout << "Enter time in format hh.mm.ss: ";
	validateInput(time_str, in);
	if (!other.parseString(time_str))
		in.setstate(std::ios::failbit);

	return in;
}

std::ifstream& operator>>(std::ifstream& ifs, Time& other)
{
	ifs >> other.hours >> other.minutes >> other.seconds;

	return ifs;
}