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

BitcoinExchange::BitcoinExchange(const BitcoinExchange& source)
{
	this->database_ = source.database_;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& source)
{
	this->database_ = source.database_;
	return (*this);
}

const char*	BitcoinExchange::couldntOpenFile::what() const throw ()
{
	return ("Error: could not open file.");
}

const char*	BitcoinExchange::notPositiveValue::what() const throw ()
{
	return ("Error: not a positive number.");
}

const char*	BitcoinExchange::tooLargeNumber::what() const throw ()
{
	return ("Error: too large a number.");
}

BitcoinExchange::badInput::badInput(std::string& str)
{
	std::string	tmp = "Error: bad input => \'" + str + "\'";
	this->nowLine_ = new std::string(tmp);
}

BitcoinExchange::badInput::badInput(const std::string& str)
{
	std::string	tmp = "Error: bad input => \'" + str + "\'";
	this->nowLine_ = new std::string(tmp);
}

BitcoinExchange::badInput::~badInput() throw ()
{
	delete this->nowLine_;
};

const char*	BitcoinExchange::badInput::what() const throw ()
{
	return (this->nowLine_->c_str());
}


void	BitcoinExchange::openMarket(void)
{
	std::fstream			data_strm;
	std::string				tmp_str;
	size_t					pos;

	data_strm.open("data.csv");
	if (data_strm.is_open() == false)
	{
		throw BitcoinExchange::couldntOpenFile();
	}
	std::getline(data_strm, tmp_str);
	pos = tmp_str.find(',');
	if (pos == std::string::npos
		|| tmp_str.substr(0, pos) != "date"
		|| tmp_str.substr(pos + 1, tmp_str.size() - pos - 1) != "exchange_rate")
	{
		throw BitcoinExchange::badInput(tmp_str);
	}
	while (data_strm.eof() == false)
	{
		try
		{
			if (data_strm.fail() == true)
			{
				break ;
			}
			std::getline(data_strm, tmp_str);
			pos = tmp_str.find(',');
			if (pos == std::string::npos)
			{
				throw BitcoinExchange::badInput(tmp_str);
			}
			this->setDatabase(tmp_str, pos);
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << "\n";
		}
	}
	data_strm.close();
	return ;
}

void	BitcoinExchange::setDatabase(std::string& str, size_t pos)
{
	Date			tmp_date;
	std::string		tmp_str;
	std::stringstream tmp_stream;
	float			value;

	tmp_str = str.substr(0, pos);
	if (tmp_date.setDate(tmp_str) == false)
		throw BitcoinExchange::badInput(str);

	tmp_stream << str.substr(pos + 1, str.size() - pos - 1);
	tmp_stream >> value;
	if (tmp_stream.fail() == true || tmp_stream.eof() == false)
	{
		throw BitcoinExchange::badInput(str);
	}
	this->database_.insert(std::make_pair(tmp_date, value));
}

void	BitcoinExchange::calcInput(std::fstream& input)
{
	std::string			tmp_str;
	size_t				pos;

	std::getline(input, tmp_str);
	pos = tmp_str.find('|');
	if (pos == std::string::npos
		|| tmp_str.substr(0, pos - 1) != "date"
		|| tmp_str.substr(pos + 2, tmp_str.size() - pos - 2) != "value")
	{
		throw BitcoinExchange::badInput(tmp_str);
	}
	while (input.eof() == false)
	{
		try
		{
			if (input.fail() == true)
			{
				break ;
			}
			std::getline(input, tmp_str);
			pos = tmp_str.find('|');
			if (pos == std::string::npos)
			{
				throw BitcoinExchange::badInput(tmp_str);
			}
			this->checkInputLine(tmp_str, pos);
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
		
	}
}

void	BitcoinExchange::checkInputLine(std::string& str, size_t pos)
{
	Date					tmp_date;
	std::string				tmp_str;
	btcDatabase::iterator	iter;
	std::stringstream		tmp_stream;
	float					value;
	float					mult;

	tmp_str = str.substr(0, pos - 1);
	if (tmp_date.setDate(tmp_str) == false)
		throw BitcoinExchange::badInput(str);
	iter = this->database_.upper_bound(tmp_date);
	if (iter == this->database_.begin() && this->database_.begin()->first != tmp_date)
	{
		throw BitcoinExchange::badInput(tmp_date.getDate());
	}
	if (iter == this->database_.end() && this->database_.end()->first > tmp_date)
	{
		iter--;
	}
	else if (iter != this->database_.begin())
	{
		iter--;
	}
	tmp_stream << str.substr(pos + 2, str.size() - pos - 2);
	tmp_stream >> value;
	if (tmp_stream.fail() == true || tmp_stream.eof() == false)
	{
		throw BitcoinExchange::badInput(str);
	}
	if (value <= 0)
	{
		throw BitcoinExchange::notPositiveValue();
	}
	if (value >= 1000)
	{
		throw BitcoinExchange::tooLargeNumber();
	}
	mult = value * iter->second;
	std::cout << tmp_str << " => " << value << " = " << mult << std::endl;
}
