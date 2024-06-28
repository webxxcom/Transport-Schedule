#include "stdafx.h"
#include "Clocks.h"

Clocks::Clocks()
	: Time()
{

}

Clocks::Clocks(time_t h, time_t m, time_t s)
{
	Clocks::setTime(h, m, s);
}

Clocks::Clocks(std::string_view str)
{
	Clocks::parseString(str);
}

bool Clocks::setTime(time_t h, time_t m, time_t s)
{
	if (h < 0 || h > 23 || m < 0 || m > 59 || s < 0 || s > 59)
	{
		h = m = s = 0;
		return false;
	}
	this->hours = h;
	this->minutes = m;
	this->seconds = s;

	return true;
}