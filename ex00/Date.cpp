#include "Date.hpp"

#include <string>
#include <sstream>

Date::Date(/* args*/){}

Date::~Date(){}

Date::Date(const Date& source)
{
	this->date_ = source.date_;
	this->year_ = source.year_;
	this->month_ = source.month_;
	this->day_ = source.day_;
}

Date& Date::operator=(const Date& source)
{
	this->date_ = source.date_;
	this->year_ = source.year_;
	this->month_ = source.month_;
	this->day_ = source.day_;
	return (*this);
}

void	Date::setDate(std::string &str)
{
	std::stringstream	tmp_stream;
	size_t	pos_f;
	size_t	pos_b;

	this->date_ = str;
	pos_f = this->date_.find('-');
	pos_b = this->date_.rfind('-');
	if (this->date_.find('-', pos_f) != std::string::npos)
	{
		throw std::exception();
	}
	tmp_stream.clear();
	tmp_stream << this->date_.substr(0, pos_f);
	if (tmp_stream.fail() == true || tmp_stream.eof() == false)
	{
		throw std::exception();
	}
	tmp_stream >> this->year_;
	if (this->year_ < 0 || this->year_ > 9999)
	{
		throw std::exception();
	}

	// tmp month 체크
	tmp_stream.clear();
	tmp_stream << this->date_.substr(pos_f + 1, pos_b);
	if (tmp_stream.fail() == true || tmp_stream.eof() == false)
	{
		throw std::exception();
	}
	tmp_stream >> this->month_;
	if (this->month_ < 1 || this->month_ > 12)
	{
		throw std::exception();
	}

	// tmp day 체크
	tmp_stream.clear();
	tmp_stream << this->date_.substr(pos_b + 1, this->date_.size());
	if (tmp_stream.fail() == true || tmp_stream.eof() == false)
	{
		throw std::exception();
	}
	tmp_stream >> this->day_;
	if ((this->month_ == 1 || this->month_ == 3 || this->month_ == 5 || this->month_ == 7
		|| this->month_ == 8 || this->month_ == 10 || this->month_ == 12)
		&& (this->month_ < 1 || this->month_ > 31))
	{
		throw std::exception();
	}
	if ((this->month_ == 4 || this->month_ == 6
		|| this->month_ == 9 || this->month_ == 11)
		&& (this->month_ < 1 || this->month_ > 30))
	{
		throw std::exception();
	}
	if (this->month_ == 2)
	{
		if (this->year_ % 400 == 0)
		{
			if (this->day_ < 1 || this->day_ > 29)
			{
				throw std::exception();
			}
		}
		else if ((this->year_ % 100 != 0) && (this->year_ % 4 == 0))
		{
			if (this->day_ < 1 || this->day_ > 29)
			{
				throw std::exception();
			}
		}
		else
		{
			if (this->day_ < 1 || this->day_ > 28)
			{
				throw std::exception();
			}
		}
	}

}
