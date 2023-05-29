#include "BitcoinExchange.hpp"
#include "Date.hpp"

#include <map>
#include <fstream>
#include <utility>
#include <string>
#include <sstream>
#include <iostream>

BitcoinExchange::BitcoinExchange(/* args*/){}

BitcoinExchange::~BitcoinExchange(){}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& source){}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& source){}

void	BitcoinExchange::openMarket(std::fstream& data_strm)
{
	std::string				tmp_str;
	size_t					pos;

	std::getline(data_strm, tmp_str);
	pos = tmp_str.find(',');
	if (pos == std::string::npos)
	{
		// ,이 없어서 fail
	}
	if (tmp_str.substr(0, pos) != "date")
	{
		// fail
	}
	if (tmp_str.substr(pos + 1, tmp_str.size()) != "exchange_rate")
	{
		// fail
	}
	while (data_strm.eof() == false)
	{
		try
		{
			if (data_strm.fail() == true)
			{
				// fail
			}
			std::getline(data_strm, tmp_str);
			pos = tmp_str.find(',');
			if (pos == std::string::npos)
			{
				// ,이 없어서 fail
			}
			this->setDatabase(tmp_str, pos);
		}
		catch(const std::exception& e)
		{
		}
	}
  
	return ;
}

void	BitcoinExchange::setDatabase(std::string& str, size_t pos)
{
	Date			tmp_date;
	std::string		tmp_str;
	std::stringstream tmp_stream;
	float			value;

	tmp_str = str.substr(0, pos);
	tmp_date.setDate(tmp_str);

	tmp_stream << str.substr(pos + 1, tmp_str.size());
	tmp_stream >> value;
	if (tmp_stream.fail() == true || tmp_stream.eof() == false)
	{
		throw std::exception();
	}
	this->database_.insert(std::make_pair(tmp_date, value));
}

