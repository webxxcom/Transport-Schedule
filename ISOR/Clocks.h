#pragma once
#include "stdafx.h"
#include "Time.h"

class Clocks :
    public Time
{
public:
    Clocks();

    Clocks(time_t h, time_t m, time_t s);

    explicit Clocks(std::string_view str);

    bool setTime(time_t h, time_t m, time_t s) override;
};

