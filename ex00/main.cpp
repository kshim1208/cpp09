
#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
	BitcoinExchange		market;
	std::fstream		data_strm;

	if (argc != 2)
		return (1);
	data_strm.open(argv[1]/*, 읽기 위한 옵션 추가 */);
	if (data_strm.is_open() == false)
	{
		// exception throw할지 검토
		return (1);
	}
	market.openMarket();
	market.calcInput(data_strm);
	data_strm.close();
}
