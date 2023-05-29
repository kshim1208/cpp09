#include "Date.hpp"

#include <string>
#include <sstream>

Date::Date(/* args*/){}

Date::~Date(){}

Date::Date(const Date& source)
{
	this->date = source.date;
	this->year = source.year;
	this->month = source.month;
	this->day = source.day;
}

Date& Date::operator=(const Date& source)
{
	this->date = source.date;
	this->year = source.year;
	this->month = source.month;
	this->day = source.day;
	return (*this);
}

void	Date::setDate(std::string &str)
{
	std::stringstream	tmp_stream;
	size_t	pos_f;
	size_t	pos_b;

	this->date = str;
	pos_f = this->date.find('-');
	pos_b = this->date.rfind('-');
	if (this->date.find('-', pos_f) != std::string::npos)
	{
		throw std::exception();
	}
	tmp_stream.clear();
	tmp_stream << this->date.substr(0, pos_f);
	if (tmp_stream.fail() == true || tmp_stream.eof() == false)
	{
		throw std::exception();
	}
	tmp_stream >> this->year;
	if (year < 0 || year > 9999)
	{
		throw std::exception();
	}

	// tmp month 체크
	tmp_stream.clear();
	tmp_stream << this->date.substr(pos_f + 1, pos_b);
	if (tmp_stream.fail() == true || tmp_stream.eof() == false)
	{
		throw std::exception();
	}
	tmp_stream >> this->month;
	if (this->month < 1 || this->month > 12)
	{
		throw std::exception();
	}

	// tmp day 체크
	tmp_stream.clear();
	tmp_stream << this->date.substr(pos_b + 1, this->date.size());
	if (tmp_stream.fail() == true || tmp_stream.eof() == false)
	{
		throw std::exception();
	}
	tmp_stream >> this->day;
	if ((this->month == 1 || this->month == 3 || this->month == 5 || this->month == 7
		|| this->month == 8 || this->month == 10 || this-> month == 12)
		&& (this->month < 1 || this->month > 31))
	{
		throw std::exception();
	}
	if ((this->month == 4 || this->month == 6
		|| this->month == 9 || this->month == 11)
		&& (this->month < 1 || this->month > 30))
	{
		throw std::exception();
	}
	if (this->month == 2)
	{
		if (this->year % 400 == 0)
		{
			if (this->day < 1 || this->day > 29)
			{
				throw std::exception();
			}
		}
		else if ((this->year % 100 != 0) && (this->year % 4 == 0))
		{
			if (this->day < 1 || this->day > 29)
			{
				throw std::exception();
			}
		}
		else
		{
			if (this->day < 1 || this->day > 28)
			{
				throw std::exception();
			}
		}
	}

}
