#pragma once
#include "stdafx.h"
#include "IEmissionable.h"

class Coordinates
{
private:
	double latitude;
	double longitude;

public:
	 Coordinates() : latitude(), longitude() { }
	 Coordinates(double lat, double lon) : latitude(lat), longitude(lon) { }

	 double getLatitude() const { return this->latitude; }
	 double getLongitude() const { return this->longitude; }

	///////////////		STATIC IMPLEMENTATION		/////////////////////////

	/* Calculations between two points */

	static constexpr double toRadians(double const degree) { return degree * std::numbers::pi / 180.; }

	//equirectangularApproximation
	static double calcDistBetween(Coordinates const& first, Coordinates const& second)
	{
		const double x = toRadians(second.longitude - first.longitude);
		const double y = toRadians(second.latitude - first.latitude);
		const double avgLat = toRadians((second.latitude + first.latitude) / 2.);
		return /* R = */6371. * std::sqrt(x * x * std::cos(avgLat) * std::cos(avgLat) + y * y);
	}

	/* The coordinates of cities */

	using json = nlohmann::json;

	inline static const char* json_name{ "Resources/coordinatesData.json" };
	inline static std::unordered_map<std::string, Coordinates> cityCoordinates;

	//Methods 
	static bool read_json_file()
	{
		std::ifstream ifs;
		try
		{
			ifs.open(json_name);
			ifs.exceptions(std::ofstream::failbit | std::ofstream::badbit);

			json jsonData;
			ifs >> jsonData;

			for (auto const& item : jsonData)
				cityCoordinates[item["cityName"]] = Coordinates(item["latitude"], item["longitude"]);
		}
		catch (std::exception const& ex)
		{
			if (!ifs.eof())
				std::cerr << ex.what() << '\n';

			return false;
		}
		return true;
	}

	static bool write_json_file()
	{
		std::ofstream ofs;
		try
		{
			ofs.open(json_name);

			json jsonData;
			for (auto const& [cityName, coords] : cityCoordinates)
			{
				json jsonItem;

				jsonItem["cityName"] = cityName;
				jsonItem["latitude"] = coords.getLatitude();
				jsonItem["longitude"] = coords.getLongitude();

				jsonData.push_back(jsonItem);
			}

			ofs << std::setw(4) << jsonData << std::endl;
			return true;
		}
		catch (std::exception const& ex)
		{
			std::cerr << ex.what() << '\n';
			return false;
		}
	}
};
