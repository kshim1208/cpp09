#include "RPN.hpp"

#include <string>
#include <sstream>
#include <cctype>

const char*	RPN::RPNExpressionError::what() const throw()
{
	return ("Error");
}

RPN::RPN(/* args*/){}

RPN::~RPN()
{
	// stack 제거
}

RPN::RPN(const RPN& source)
{
	this->exprs_ = source.exprs_;
}

RPN& RPN::operator=(const RPN& source)
{
	this->exprs_ = source.exprs_;
	return (*this);
}

void	RPN::isExpressions(char *str)
{
	std::stringstream	sstream(str);
	int			num = -1;
	char		aris_sym;

	// eof로 반복분 돌리면 안좋은 이유?
	while (sstream.eof() == false)
	{
		sstream >> num;
		// 문자 들어오면 fail은 무조건 뜨는데, 읽었던 걸 되돌릴 수는 없나?
		if (sstream.fail() == true && sstream.eof() == false)
		{
			sstream >> aris_sym;
			if (sstream.fail() == true || sstream.eof() == false)
			{
				throw RPN::RPNExpressionError();
			}
			this->calcExpressions(aris_sym);
			return ;
		}
		if (num > 9 || num < 0)
			throw RPN::RPNExpressionError();
		exprs_.push(num);
	}
	return ;
}


void	RPN::calcExpressions(char aris_sym)
{
	int	a;
	int	b;

	if (aris_sym == '+')
	{
		if (exprs_.size() == 0)
			throw RPN::RPNExpressionError();
		b = exprs_.top();
		exprs_.pop();
		if (exprs_.size() == 0)
			throw RPN::RPNExpressionError();
		a = exprs_.top();
		exprs_.pop();
		exprs_.push(a + b);
	}
	else if (aris_sym == '-')
	{
		if (exprs_.size() == 0)
			throw RPN::RPNExpressionError();
		b = exprs_.top();
		exprs_.pop();
		if (exprs_.size() == 0)
			throw RPN::RPNExpressionError();
		a = exprs_.top();
		exprs_.pop();
		exprs_.push(a - b);
	}
	else if (aris_sym == '*')
	{
		if (exprs_.size() == 0)
			throw RPN::RPNExpressionError();
		b = exprs_.top();
		exprs_.pop();
		if (exprs_.size() == 0)
			throw RPN::RPNExpressionError();
		a = exprs_.top();
		exprs_.pop();
		exprs_.push(a * b);
	}
	else if (aris_sym == '/')
	{
		if (exprs_.size() == 0)
			throw RPN::RPNExpressionError();
		b = exprs_.top();
		if (b == 0)
			throw RPN::RPNExpressionError();
		exprs_.pop();
		if (exprs_.size() == 0)
			throw RPN::RPNExpressionError();
		a = exprs_.top();
		exprs_.pop();
		exprs_.push(a / b);
	}
	else
	{
		throw RPN::RPNExpressionError();
	}
}

unsigned int	RPN::getExprsSize()
{
	return (exprs_.size());
}

int	RPN::getExprsTop()
{
	return (exprs_.top());
}
