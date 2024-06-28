#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <format>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <numbers>
#include <unordered_map>
#include <print>
#include <nlohmann/json.hpp>

enum TransportTypes
{
	None,
	E_Train,
	E_Bus,
	E_Plane,
	E_AllTrans,
	E_NumberOfTrans
};

//Global functions
static void clearBuffer(std::istream& in)
{
	in.clear();
	in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

template<typename Object, typename Function>
static void validateInput(Object& data, std::istream& in, Function foo, char const* text = "Incorrect input, try again: ")
{
	while (true)
	{
		in >> data;

		if (!foo(data) || in.fail())
		{
			clearBuffer(in);
			std::cout << text;
		}
		else break;
	}
}

template<typename Object>
static void validateInput(Object& data, std::istream& in, char const* text = "Incorrect input, try again: ")
{
	while (true)
	{
		in >> data;

		if (in.fail())
		{
			clearBuffer(in);
			std::cout << text;
		}
		else break;
	}
}
