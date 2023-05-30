#ifndef BitcoinExchange_HPP
# define BitcoinExchange_HPP

# include "Date.hpp"

# include <map>
# include <fstream>
# include <string>
# include <exception>

// key 관련 클래스를 nested class로 쓸까?
	// 아니면 key를 정수형으로 다룰까?
	// class 타입 key가 존재할 수 있을까?

typedef	std::map<Date, float> btcDatabase;

class BitcoinExchange
{
	private:
		btcDatabase	database_;
	public:
		BitcoinExchange(/* args*/);
		~BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& source);
		BitcoinExchange& operator=(const BitcoinExchange& source);

		class couldntOpenFile : public std::exception
		{
			public:
				const char* what() const throw ();
		};
		class notPositiveValue : public std::exception
		{
			public:
				const char* what() const throw ();
		};
		class tooLargeNumber : public std::exception
		{
			public:
				const char* what() const throw ();
		};
		class badInput : public std::exception
		{
			public:
				const char* what() const throw ();
		};


		void openMarket(void);
		void setDatabase(std::string& date, size_t pos);
		void calcInput(std::fstream& input);
		void checkInputLine(std::string& str, size_t pos);
};

#endif