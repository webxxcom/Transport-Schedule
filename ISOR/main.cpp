#include "stdafx.h"
#include "TransportSchedule.h"

int main()
{
	TransportSchedule obj("Resources/transport.csv");
	obj.menu();
	//Coordinates::write_json_file(StaticData::cityCoordinates);
}
