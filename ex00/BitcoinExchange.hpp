#ifndef BitcoinExchange_HPP
# define BitcoinExchange_HPP

#include <map>

// key 관련 클래스를 nested class로 쓸까?
	// 아니면 key를 정수형으로 다룰까?
	// class 타입 key가 존재할 수 있을까?

class BitcoinExchange
{
	private:
		// std::multimap
		std::multimap<int, int>	database_;
	public:
		BitcoinExchange(/* args*/);
		~BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& source);
		BitcoinExchange& operator=(const BitcoinExchange& source);

		void openMarket(void);
};

#endif