#ifndef RPN_HPP
# define RPN_HPP

# include <stack>
# include <deque>

typedef std::stack<int, std::deque<int> > expressions;

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
		void	calcExpressions(char aris_sym);
		unsigned int	getExprsSize();
		int		getExprsTop();
};

#endif
