#include "stdafx.h"
#include "TransportSchedule.h"

TransportTypes TransportSchedule::selectMeansOfTransport(bool allIsAllowed) const
{
	auto stopAt = E_AllTrans + (int)allIsAllowed;

	std::cout << "Select means of transport:\n";
	size_t i = 1;
	for (; i < E_AllTrans; ++i)
		std::cout << i << ") " << StaticData::vehiclesStringTypes.at((TransportTypes)i) << '\n';
	if (stopAt == E_AllTrans + 1) std::cout << i++ << ") All\n";
	std::cout << "Input: ";

	int input;
	validateInput(input, std::cin, [&stopAt](int val)
		{ return val >= 0 && val < stopAt; });
	if (input == 0)
		return TransportTypes::None;
	return (TransportTypes)input;
}

TransportInfo* TransportSchedule::createTransport(std::string_view type) const
{
	if (type == "Bus")
		return new Bus();
	else if (type == "Plane")
		return new Plane();
	else if (type == "Train")
		return new Train();

	throw std::runtime_error("Transport \'" + std::string(type) + "\' has not been found\n");
}

void TransportSchedule::addTransportUI()
{
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~\n"
		"Adding transport\n"
		"Type \'0\' to exit\n"
		"----------------------\n";
	
	auto transportType = selectMeansOfTransport(false);
	if (transportType == None)
		return;

	auto temp_transport = createTransport(StaticData::vehiclesStringTypes.at(transportType));
	validateInput(*temp_transport, std::cin);

	this->allTransports.emplace_back(temp_transport);
}

void TransportSchedule::removeTransportUI()
{
	if (this->allTransports.empty())
	{
		std::cout << "\nCannot remove any transport because there aren't any\n";
		return;
	}

	std::cout << "Removing transport\n";
	int ID;
	std::string choice;
	while (true)
	{
		std::cout <<
			"~~~~~~~~~~~~~~~~~~~~~~\n"
			"Enter ID of the transport you want to remove.\n"
			"Type \'0\' to exit\n"
			"----------------------\n"
			"Input: ";
		validateInput(ID, std::cin);
		if (ID == 0)
			return;

		auto chosenTransport = std::ranges::find_if(allTransports, [&ID](TransportInfo const* obj)
			{ return obj->getID() == ID; });

		if (chosenTransport != allTransports.end())
		{
			system("cls");
			std::cout << **chosenTransport <<
				"\nYou want to delete this transport?(yes/no): ";
			validateInput(choice, std::cin);
			if (choice == "yes" || choice == "y" || choice == "Yes" || choice == "YES")
			{
				std::cout << "The transport with ID " << ID << " was removed\n";
				this->allTransports.erase(chosenTransport);

				break;
			}
		}
		else
			std::cout << "There is no transport with that ID\n";
	}

	return;
}

std::vector<Route> TransportSchedule::findRouteCore(std::string_view from, std::string_view to, TransportTypes transportType) const
{
	std::vector<Route> validTransports;
	for (size_t i = 0; i < allTransports.size(); ++i)
	{
		const auto& transport1 = allTransports.at(i);
		if (transportType != TransportTypes::E_AllTrans && transport1.getType() != transportType)
			continue;

		if (transport1.getDeparture().name != from)
			continue;

		if (transport1.getDestination().name == to)
		{
			validTransports.emplace_back(Route({ &transport1 }));
			continue;
		}

		for (size_t j = i + 1; j < allTransports.size(); ++j)
		{
			const auto& transport2 = allTransports.at(j);
			if (transportType != TransportTypes::E_AllTrans && transport2.getType() != transportType)
				continue;

			if (transport1.getDestination().name != transport2.getDeparture().name)
				continue;

			if (transport2.getDestination().name == to)
			{
				validTransports.emplace_back(Route({ &transport1, &transport2 }));
				continue;
			}

			for (size_t k = j + 1; k < allTransports.size(); k++)
			{
				const auto& transport3 = allTransports.at(k);
				if (transportType != TransportTypes::E_AllTrans && transport3.getType() != transportType)
					continue;

				if (transport2.getDestination().name != transport3.getDeparture().name)
					continue;

				if (transport3.getDestination().name == to &&
					transport1.getDeparture().name != transport3.getDeparture().name)
				{
					validTransports.emplace_back(Route({ &transport1, &transport2, &transport3 }));
					break;
				}
			}
		}
	}
	std::ranges::sort(validTransports, std::less(), [](Route const& r) 
		{return r.totalTime;});

	return validTransports;
}

void TransportSchedule::findRouteUI() const
{
	std::cout << "Enter your initial location: ";
	std::string from;
	clearBuffer(std::cin);
	std::getline(std::cin, from);

	std::cout << "Enter where you're going to: ";
	std::string to;
	std::getline(std::cin, to);

	auto transportType = selectMeansOfTransport(true);
	if (transportType == None)
		return;

	std::vector<Route> routes = this->findRouteCore(from, to, transportType);
	if (!routes.empty())
	{
		std::print("You've got such options to get to {0} from {1}:\n", to, from);
		std::ranges::for_each(routes, [count = 0](Route const& it) mutable {
			std::cout << "------ROUTE #" << ++count << "------\n" << it << std::endl; });
	}
	else
		std::cout << "No routes were found for this direction, we're sincerely sorry\n";

	system("pause");
}

bool TransportSchedule::adminCheckPassword() const
{
	std::cout << "To get access to admin settings to must enter the password.\n"
		"Input: ";
	std::string password;
	int attempts = 3;
	for (size_t i = 0; i < attempts; i++)
	{
		validateInput(password, std::cin);
		clearBuffer(std::cin);
		if (password != "qwerty123")
			std::cout << "You have " << attempts - i - 1 << " attempts left.\n";
		else
			return true;
	}
	return false;
}

void TransportSchedule::adminMenuUI()
{
	if (!this->adminCheckPassword())
	{
		std::cout << "The password is incorrect.";
		system("pause");
		return;
	}
	system("cls");

	int input;
	bool exit = false;
	while (!exit)
	{
		std::cout <<
			"Admin settings\n"
			"~~~~~~~~~~~~~~~~~~\n"
			"1) Add transport\n"
			"2) Remove transport\n"
			"3) Sort data\n"
			"4) Load data\n"
			"5) See all transports\n"
			"6) Save\n"
			"7) Exit without saving\n"
			"Input: ";

		validateInput(input, std::cin, [](int val) {return val >= 1 && val <= 7; });
		system("cls");
		switch (input)
		{
		case 1:
			this->addTransportUI();
			break;

		case 2:
			this->removeTransportUI();
			break;

		case 3:
			this->sortUI();
			break;

		case 4:
			this->loadDataUI();
			break;

		case 5:
			this->print();
			break;

		case 6:
			this->saveDataUI();
			break;

		case 7:
			exit = true;
			break;
		}
		system("pause");
		system("cls");
	}
}

void TransportSchedule::print() const
{
	std::ranges::for_each(this->allTransports, [](auto const& it) {
		std::cout << *it << "\n-------------------------------\n"; });
	
	system("pause");
}

void TransportSchedule::loadDataUI()
{
	system("cls");

	std::cout <<
		"~~~~~~~~~~~~~~~~~~~~~~~~\n"
		"Loading data\n"
		"Write the file name\n"
		"Type \'0\' to exit\n"
		"Type \'1\' to save to current file\n"
		"------------------------\n"
		"Input: ";
	std::string temp;
	validateInput(temp, std::cin);
	if (temp == "0")
		return;
	if (temp == "1")
		temp = this->_fileName;

	this->allTransports.clear();
	this->loadDataCore(temp);
}

void TransportSchedule::loadDataCore(std::string const& _File_Name)
{
	std::ifstream ifs;
	try
	{
		ifs.open(_File_Name);
		if (!ifs.is_open())
			throw std::runtime_error("Can't open file" + _File_Name);
		ifs.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		std::string line, type;

		//Skip first line
		std::getline(ifs, line);
		while (std::getline(ifs, line))
		{
			std::stringstream ss(line);
			std::getline(ss, type, ',');

			TransportInfo* temp = createTransport(type);
			temp->deserialize(ss);
			this->allTransports.emplace_back(temp);
		}
	}
	catch (std::ifstream::failure const& ex)
	{
		if (!ifs.eof())
		{
			std::cerr << "Exception opening/reading/closing file\n";
			std::cerr << ex.what() << '\n';
			std::cerr << "Error code: " << ex.code() << '\n';
		}
		else
			std::cout << "The data was successfully loaded\n";
	}
	catch (std::exception const& ex)
	{
		std::cerr << "Exception: " << ex.what() << std::endl;
		system("pause");
	}
	ifs.close();
}

void TransportSchedule::sortUI() const
{
	system("cls");
	std::cout <<
		"~~~~~~~~~~~~~~~~~~~~~~~~\n"
		"Sorting data\n"
		"Select by which parameter sort the list\n"
		"Type \'0\' to exit\n"
		"------------------------\n"
		"1) ID\n" <<
		"2) Departure\n" <<
		"3) Destination\n" <<
		"4) Departure time\n" <<
		"5) Destination time\n" <<
		"6) Fee\n" <<
		"7) Means of transport\n" <<
		"Input: ";

	int choice;
	validateInput(choice, std::cin, [](char ch) {return ch >= 0 || ch <= 7; });
	switch (choice)
	{
	case 0:
		return;
	case 1:
		this->sortBy([](TransportInfo const* obj) {return obj->getID(); });
		break;
	case 2:
		this->sortBy([](TransportInfo const* obj) {return obj->getDeparture().name; });
		break;
	case 3:
		this->sortBy([](TransportInfo const* obj) {return obj->getDestination().name; });
		break;
	case 4:
		this->sortBy([](TransportInfo const* obj) {return obj->getDeparture().time; });
		break;
	case 5:
		this->sortBy([](TransportInfo const* obj) {return obj->getDestination().time; });
		break;
	case 6:
		this->sortBy([](TransportInfo const* obj) {return obj->getFee(); });
		break;
	case 7:
		this->sortBy([](TransportInfo const* obj) {return obj->getTypeString(); });
		break;
	}
	std::cout << "The list was successfully sorted\n";
}

template<typename Function>
void TransportSchedule::sortBy(Function foo) const
{
	std::ranges::sort(allTransports, std::less(), foo);
}

void TransportSchedule::saveDataUI() 
{
	std::cout <<
		"~~~~~~~~~~~~~~~~~~~~~~\n"
		"Saving data\n"
		"Write the file to save data to\n"
		"Type \'0\' to exit\n"
		"----------------------\n"
		"Input: ";

	std::string input;
	validateInput(input, std::cin);
	if (input == "0")
		return;

	this->_fileName = input;
	this->saveDataCore();
}

void TransportSchedule::saveDataCore() const
{
	try
	{
		std::ofstream ofs(this->_fileName);
		ofs.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		ofs << "TypeOfTransport,ID,Departure,Time,Platform,Destination,Time,Platform,Fee,AdditionalInformation\n";
		for (const auto& it : this->allTransports)
			it->serialize(ofs);

		std::cout << "The data was successfully saved\n";
		ofs.close();
	}
	catch (std::ofstream::failure& ex)
	{
		std::cerr << ex.what() << '\n' << ex.code() << '\n';
	}
}

TransportSchedule::TransportSchedule(const char* fileName) 
	: _fileName(fileName)
{
	Coordinates::read_json_file();
	this->loadDataCore(this->_fileName);
}

void TransportSchedule::menu()
{
	int input;
	bool exit = false;
	while (!exit)
	{
		system("cls");
		std::cout << "Hello to the ISOR app.\n"
			"~~~~~~~~~~~~~~~~~~~~~~~~~\n"
			"1) Find route\n"
			"2) See all transports\n"
			"3) Admin settings\n"
			"4) Exit\n"
			"Input: ";

		validateInput(input, std::cin, [](int val) {return val >= 1 && val <= 4; });
		system("cls");
		switch (input)
		{
		case 1:
			this->findRouteUI();
			break;

		case 2:
			this->print();
			break;

		case 3:
			this->adminMenuUI();
			break;

		case 4:
			exit = true;
			break;

		default:
			continue;
		}

	}
}
