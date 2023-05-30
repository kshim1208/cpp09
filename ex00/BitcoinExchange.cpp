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

BitcoinExchange::badInput::badInput(std::string& str): nowLine_(str){};

const char*	BitcoinExchange::badInput::what() const throw ()
{
	std::string appending = "Error: bad input => " + this->nowLine_;
	return ("Error: bad input => ");
}

void	BitcoinExchange::openMarket(void)
{
	std::fstream			data_strm;
	std::string				tmp_str;
	size_t					pos;

	data_strm.open("data.csv"/*, 읽기 위한 옵션 추가 */);
	if (data_strm.is_open() == false)
	{
		// exception throw할지 검토
		return ;
	}
	std::getline(data_strm, tmp_str);
	pos = tmp_str.find(',');
	if (pos == std::string::npos)
	{
		// ,이 없어서 fail
	}
	// 여기서 stream 쓰면 data 앞 뒤로 띄어쓰기 걸러낼 수 있을 것 같음
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

	// 밑에 두 값 입력 방식은 둘 다 내부적으로 pair를 사용한다.
		// pair, pair에서 사용하는 compare 규칙 설명
	this->database_.insert(std::make_pair(tmp_date, value));
	// this->database_[tmp_date] = value;
	// printf("%s,%f\n", tmp_str.c_str(), value);
}

void	BitcoinExchange::calcInput(std::fstream& input)
{
	std::string			tmp_str;
	size_t				pos;
	// input 한 줄 넘기기
	std::getline(input, tmp_str);
	pos = tmp_str.find('|');
	if (pos == std::string::npos)
	{
		// ,이 없어서 fail
	}
	if (tmp_str.substr(0, pos - 1) != "date")
	{
		// fail
	}
	if (tmp_str.substr(pos + 2, tmp_str.size() - pos - 2) != "value")
	{
		// fail
	}
	while (input.eof() == false)
	{
		try
		{
			if (input.fail() == true)
			{
				// fail
			}
			std::getline(input, tmp_str);
			this->nowline_ = tmp_str;
			pos = tmp_str.find('|');
			if (pos == std::string::npos)
			{
				// ,이 없어서 fail
			}
			this->checkInputLine(tmp_str, pos);
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what();
			std::cerr << '\n';
		}
		
	}
	// input 한 줄 읽기
		// 정상
			// this->database_ 순회해서 맞는 날짜 선택한 뒤 곱 연산하는 함수
		// 비정상 (try-catch)
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
	tmp_date.setDate(tmp_str);
	if (tmp_date.setDate(tmp_str) == false)
		throw BitcoinExchange::badInput(str);
	iter = this->database_.upper_bound(tmp_date);
	if (iter == this->database_.end())
	{
		throw std::exception();
	}
	if (iter != this->database_.begin())
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

std::string& BitcoinExchange::getnowLine()
{
	return (this->nowline_);
}
