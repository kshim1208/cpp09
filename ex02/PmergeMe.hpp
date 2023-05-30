#ifndef PmergeMe_HPP
# define PmergeMe_HPP

#include <vector>
#include <list>

template< template <class ELEM, class Allocator > class T>
class PmergeMe
{
	private:
		T<int>	cont;
	public:
		PmergeMe(/* args*/);
		~PmergeMe();
		PmergeMe(const PmergeMe& source);
		PmergeMe& operator=(const PmergeMe& source);

		void	parseInput();
};

#endif