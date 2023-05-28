#include "BitcoinExchange.hpp"

#include <map>
#include <fstream>
#include <utility>
#include <string>
#include <sstream>

BitcoinExchange::BitcoinExchange(/* args*/){}

BitcoinExchange::~BitcoinExchange(){}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& source){}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& source){}

// stringstream, fail eof로 예외 처리해보기.

void	BitcoinExchange::openMarket(std::fstream& data_strm)
{
	std::string				tmp_str;
	std::stringstream		tmp_str_strm;
	size_t					pos;

	// 한 줄을 읽는다.
	std::getline(data_strm, tmp_str);
	pos = tmp_str.find(',');
	if (tmp_str.substr(0, pos) != "date")
	{
		
	}
	if (tmp_str.substr(pos, tmp_str.size()) != "exchange_rate")
	{

	}

	// 다음 줄을 읽는다 (자료 시작)
		// eof는 data를 본다. getline 실패하면 어디에 failbit 켜질까?

	while (!data_strm.eof())
	{
		if (data_strm.fail() == true)
		{
			return ;
		}
		std::getline(data_strm, tmp_str);
		tmp_str_strm.str(tmp_str);
		
		// 3개로 쪼개기

		this->database_.insert(std::make_pair(, ));
	}
	// 가장 앞 숫자열을 년도 단위가 되도록 읽어낸다.

	// 날짜 범위는 어떻게 잡을까? 제한이 있나? -> 데이터 베이스의 날짜가 int 범위를 초과하진 않음.

	// 날짜 parsing하고 나면 이에 해당하는 key 값을 float 읽기로 저장한다.

  
	return ;
}
