#ifndef Date_HPP
# define Date_HPP

# include <string>

class Date
{
	private:
		std::string	date;
		int			year;
		int			month;
		int			day;
		
	public:
		Date(/* args*/);
		~Date();
		Date(const Date& source);
		Date& operator=(const Date& source);
		void	setDate(std::string &str);
};

#endif