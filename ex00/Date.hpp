#ifndef Date_HPP
# define Date_HPP

# include <string>
# include <iostream>

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

		bool	operator>(const Date& rhs) const;
		bool	operator<(const Date& rhs) const;
		bool	operator==(const Date& rhs) const;
		bool	operator!=(const Date& rhs) const;

		bool	setDate(std::string &str);
		const std::string&	getDate(void) const;
};

std::ostream& operator<<(std::ostream &output, const Date& rhs);

#endif