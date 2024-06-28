#pragma once
#include "stdafx.h"
#include "Route.h"

//Integrated system of routes
class TransportSchedule
{
private:
	PtrArray<TransportInfo> allTransports;
	std::string _fileName;

	//Helper methods
	TransportTypes selectMeansOfTransport(bool allIsAllowed) const;
	TransportInfo* createTransport(std::string_view type) const;

	//Methods
	std::vector<Route> findRouteCore(std::string_view from, std::string_view to, TransportTypes transportType = E_AllTrans) const;
	void findRouteUI() const;

	void print() const;

	bool adminCheckPassword() const;
	void adminMenuUI();

	void addTransportUI();

	void removeTransportUI();

	template<typename Function>
	void sortBy(Function foo) const;
	void sortUI() const;

	void loadDataUI();
	void loadDataCore(std::string const&);

	void saveDataCore() const;
	void saveDataUI();
public:
	explicit TransportSchedule(const char* fileName);

	void menu();
};

