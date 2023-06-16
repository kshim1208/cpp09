
#include "PmergeMe.hpp"

#include <vector>
#include <list>

#include <iostream>
#include <exception>

int	main(int argc, char **argv)
{
	PmergeMe<std::vector>		merger_vec;
	PmergeMe<std::list>		merger_list;

	try
	{
		if (argc < 2)
			return (1);

		merger_vec.parseInput(argv);
		merger_vec.printCont();
		merger_list.parseInput(argv);
		// template으로 투입-정렬 합치기? 나누기?
		// input 각 container에 검사-투입
		merger_vec.pmergeIt();
		merger_vec.printCont();
		// input을 각 containter에서 정렬
		
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return (1);
	}
	return (0);
}
