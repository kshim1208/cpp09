#include "Date.hpp"

#include <string>
#include <sstream>
#include <tuple>

Date::Date(/* args*/)
{
	this->year_ = 0;
	this->month_ = 0;
	this->day_ = 0;
}

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

bool	Date::operator>(const Date& rhs) const
{
	if (this->year_ > rhs.year_)
		return (true);
	if (this->year_ < rhs.year_)
		return (false);
	if (this->month_ > rhs.month_)
		return (true);
	if (this->month_ < rhs.month_)
		return (false);
	return (this->day_ > rhs.day_);
}

bool	Date::operator<(const Date& rhs) const
{
	if (this->year_ < rhs.year_)
		return (true);
	if (this->year_ > rhs.year_)
		return (false);
	if (this->month_ < rhs.month_)
		return (true);
	if (this->month_ > rhs.month_)
		return (false);
	return (this->day_ < rhs.day_);
}

bool	Date::operator==(const Date& rhs) const
{
	return (this->year_ == rhs.year_ && this->month_ == rhs.month_ && this->day_ == rhs.day_);
}

bool	Date::setDate(std::string &str)
{
	std::stringstream	tmp_stream;
	size_t	pos_f;
	size_t	pos_b;

	this->date_ = str;
	pos_f = this->date_.find('-');
	pos_b = this->date_.find('-', pos_f + 1);
	if (this->date_.find('-', pos_b + 1) != std::string::npos)
	{
		return (false);
	}
	tmp_stream << this->date_.substr(0, pos_f);
	if (tmp_stream.fail() == true)
		return (false);
	tmp_stream >> this->year_;
	if (tmp_stream.eof() == false || this->year_ < 0 || this->year_ > 9999)
	{
		return (false);
	}

	// tmp month 체크
	tmp_stream.str("");
	tmp_stream.clear();
	tmp_stream << this->date_.substr(pos_f + 1, pos_b - pos_f - 1);
	if (tmp_stream.fail() == true)
	{
		return (false);
	}
	tmp_stream >> this->month_;
	if (tmp_stream.eof() == false || this->month_ < 1 || this->month_ > 12)
	{
		return (false);
	}

	// tmp day 체크
	tmp_stream.str("");
	tmp_stream.clear();
	tmp_stream << this->date_.substr(pos_b + 1, this->date_.size() - pos_b - 1);
	if (tmp_stream.fail() == true)
	{
		return (false);
	}
	tmp_stream >> this->day_;
	if (tmp_stream.eof() == false)
		return (false);
	if ((this->month_ == 1 || this->month_ == 3 || this->month_ == 5 || this->month_ == 7
		|| this->month_ == 8 || this->month_ == 10 || this->month_ == 12)
		&& (this->month_ < 1 || this->month_ > 31))
	{
		return (false);
	}
	if ((this->month_ == 4 || this->month_ == 6
		|| this->month_ == 9 || this->month_ == 11)
		&& (this->month_ < 1 || this->month_ > 30))
	{
		return (false);
	}
	if (this->month_ == 2)
	{
		if (this->year_ % 400 == 0)
		{
			if (this->day_ < 1 || this->day_ > 29)
			{
				return (false);
			}
		}
		else if ((this->year_ % 100 != 0) && (this->year_ % 4 == 0))
		{
			if (this->day_ < 1 || this->day_ > 29)
			{
				return (false);
			}
		}
		else
		{
			if (this->day_ < 1 || this->day_ > 28)
			{
				return (false);
			}
		}
	}
	return (true);
}

const std::string&	Date::getDate() const
{
	return (this->date_);
}

std::ostream& operator<<(std::ostream &output, const Date& rhs)
{
	output << rhs.getDate();
	return (output);
}
