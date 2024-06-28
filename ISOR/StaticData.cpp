#pragma once
#include "stdafx.h"
#include "Coordinates.cpp"

namespace StaticData
{
	static const std::unordered_map<TransportTypes, std::string_view> vehiclesStringTypes =
	{
		{E_Train, "Train"},
		{E_Bus, "Bus"},
		{E_Plane, "Plane"}
	};
}