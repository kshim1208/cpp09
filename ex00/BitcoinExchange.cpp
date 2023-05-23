#include "BitcoinExchange.hpp"

#include <map>
#include <fstream>

BitcoinExchange::BitcoinExchange(/* args*/){}

BitcoinExchange::~BitcoinExchange(){}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& source){}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& source){}

void	BitcoinExchange::openMarket(void)
{
	std::fstream	data;

	data.open("data.csv", /* 읽기 위한 옵션 추가 */);
	if (data.is_open() == false)
	{
		return ;
	}
	// data.csv 파일을 연다.
	// 한 줄을 읽는다.
	// 가장 앞 숫자열을 년도 단위가 되도록 읽어낸다.
	// 날짜 범위는 어떻게 잡을까? 제한이 있나? -> 데이터 베이스의 날짜가 int 범위를 초과하진 않음.
	// 날짜 parsing하고 나면 이에 해당하는 key 값을 float 읽기로 저장한다.
}
