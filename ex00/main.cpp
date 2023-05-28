
#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
	BitcoinExchange		market;
	std::fstream		data_strm;

	if (argc != 2)
		return (1);
	// data.csv 파일을 연다.
	data_strm.open(argv[1]/*, 읽기 위한 옵션 추가 */);
	if (data_strm.is_open() == false)
	{
		// exception throw할지 검토
		return ;
	}
	market.openMarket(data_strm);
	// arg 2개
	// csv 파일을 열고 읽어서 데이터 베이스화
		// 데이터 베이스 만드는 멤버 함수 -> container 객체 반환? 아니면 내부 데이터 채우기? 어떤 방식이 더 나을지 생각
	// 인자 파일을 읽고, 이 파일을 데이터 베이스와 비교하며 평가
		// key-value 읽고, 비교하는 메커니즘 구현
		// 비트 코인 개수에 가격을 곱한 값을 연산하여 출력.

}
