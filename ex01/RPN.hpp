#ifndef RPN_HPP
# define RPN_HPP

# include <stack>
# include <list>

typedef std::stack<int, std::list<int> > expressions;

class RPN
{
	private:
		expressions		exprs_;
	public:
		
		class RPNExpressionError : public std::exception
		{
			public:
				const char* what() const throw();
		};

		RPN(/* args*/);
		~RPN();
		RPN(const RPN& source);
		RPN& operator=(const RPN& source);
		void	isExpressions(char *str);
		void	calcExpressions(std::string& aris_sym);
		unsigned int	getExprsSize();
		int		getExprsTop();
};

#endif
