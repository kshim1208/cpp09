
#include "PmergeMe.hpp"

#include <vector>
#include <list>

int	main(int argc, char **argv)
{
	PmergeMe<std::vector, int>		merger_vec;
	PmergeMe<std::list, int>		merger_list;

	if (argc < 2)
		return (1);

	merger_vec.parseInput(argv);
	merger_list.parseInput(argv);
	// template으로 투입-정렬 합치기? 나누기?
	// input 각 container에 검사-투입
	// input을 각 containter에서 정렬

}
