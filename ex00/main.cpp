
#include "BitcoinExchange.hpp"

#include <iostream>

int main(int argc, char **argv)
{
	BitcoinExchange		market;
	std::fstream		data_strm;

	if (argc != 2)
		return (1);
	data_strm.open(argv[1]/*, 읽기 위한 옵션 추가 */);
	if (data_strm.is_open() == false)
	{
		std::cerr << "fail to open file." << "\n";
		return (1);
	}
	try
	{
		market.openMarket();
		market.calcInput(data_strm);
		data_strm.close();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return (1);
	}
	return (0);
}
