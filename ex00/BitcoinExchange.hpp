#ifndef BitcoinExchange_HPP
# define BitcoinExchange_HPP

# include "Date.hpp"

# include <map>
# include <fstream>
# include <string>
# include <exception>

typedef	std::map<Date, float> btcDatabase;

class BitcoinExchange
{
	private:
		btcDatabase	database_;
		std::string	nowline_;
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
				badInput(std::string& str);
				badInput(const std::string& str);
				~badInput() throw ();
				const char* what() const throw ();

			private:
				std::string*	nowLine_;
		};

		// class badInput : public std::exception
		// {
		// 	public:
		// 		badInput(std::string& str);
		// 		badInput(const std::string& str);
		// 		~badInput() throw ();
		// 		const char* what() const throw ();

		// 	private:
		// 		char*	nowLine_;
		// };


		void openMarket(void);
		void setDatabase(std::string& date, size_t pos);
		void calcInput(std::fstream& input);
		void checkInputLine(std::string& str, size_t pos);
		std::string& getnowLine();
};

#endif