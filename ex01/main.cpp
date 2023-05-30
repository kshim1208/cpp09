
#include "RPN.hpp"

#include <iostream>

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (1);

	RPN	calculator;

	try
	{
		calculator.isExpressions(argv[1]);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return (1);
	}
	// 스택 크기 1 아니어도 에러 throw?
	if (calculator.getExprsSize() == 1)
		std::cout << calculator.getExprsTop() << std::endl;
	else
		std::cerr << "Error" << std::endl;
	return (0);
}
