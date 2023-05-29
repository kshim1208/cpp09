#ifndef Date_HPP
# define Date_HPP

# include <string>

class Date
{
	private:
		std::string	date_;
		int			year_;
		int			month_;
		int			day_;
		
	public:
		Date(/* args*/);
		~Date();
		Date(const Date& source);
		Date& operator=(const Date& source);
		void	setDate(std::string &str);
};

#endif