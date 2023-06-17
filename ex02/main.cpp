
#include "PmergeMe.hpp"

#include <vector>
#include <deque>

#include <iostream>
#include <exception>
#include <sys/time.h>

int	main(int argc, char **argv)
{
	PmergeMe<std::vector>		merger_vec;
	PmergeMe<std::deque>		merger_deque;

	timeval			start;
	timeval			end;
	long			second;
	long			microsecond;
	double			passed;

	try
	{
		if (argc < 2)
			return (1);
		gettimeofday(&start, 0);
		merger_vec.parseInput(argv);
		merger_vec.printCont(BEFORE);
		merger_vec.pmergeIt();
		gettimeofday(&end, 0);

		second = end.tv_sec - start.tv_sec;
		microsecond = end.tv_usec - start.tv_usec;
		passed = second * 1000000.0 + microsecond;

		merger_vec.printCont(AFTER);

		std::cout << "Time to process a range of " << merger_vec.contSize() << " elements with std::vector : " << passed << "us" << std::endl;

		gettimeofday(&start, 0);
		merger_deque.parseInput(argv);
		merger_deque.printCont(BEFORE);
		merger_deque.pmergeIt();
		gettimeofday(&end, 0);

		second = end.tv_sec - start.tv_sec;
		microsecond = end.tv_usec - start.tv_usec;
		passed = second * 1000000.0 + microsecond;

		merger_deque.printCont(AFTER);

		std::cout << "Time to process a range of " << merger_deque.contSize() << " elements with std::deque : " << passed << "us" << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return (1);
	}
	return (0);
}
