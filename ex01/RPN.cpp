#include "RPN.hpp"

#include <string>
#include <sstream>
#include <cctype>
#include <cstdlib>

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
	std::string			tmp;

	// eof로 반복분 돌리면 안좋은 이유?
	// ./RPN "0 2  -", ./RPN "0 2  - "의 동작 상 차이 한 번 보기
	while (sstream.eof() == false)
	{
		sstream >> tmp;
		if (tmp.size() != 1)
		{
			throw RPN::RPNExpressionError();
		}
		if (tmp.compare("+") == 0 || tmp.compare("-") == 0
			|| tmp.compare("*") == 0 || tmp.compare("/") == 0)
		{
			this->calcExpressions(tmp);
		}
		else if (tmp.front() >= '0' && tmp.front() <= '9')
		{
			exprs_.push(std::atoi(tmp.c_str()));
		}
		else
		{
			throw RPN::RPNExpressionError();
		}
	}
	return ;
}


void	RPN::calcExpressions(std::string& aris_sym)
{
	int	a;
	int	b;

	if (aris_sym.compare("+") == 0)
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
	else if (aris_sym.compare("-") == 0)
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
	else if (aris_sym.compare("*") == 0)
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
	else if (aris_sym.compare("/") == 0)
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
}

unsigned int	RPN::getExprsSize()
{
	return (exprs_.size());
}

int	RPN::getExprsTop()
{
	return (exprs_.top());
}
