#ifndef PmergeMe_HPP
# define PmergeMe_HPP

#include <vector>
#include <list>

template<typename CONT, typename ELEM>
class PmergeMe
{
	private:
		CONT<ELEM>	cont_;
	public:
		PmergeMe(/* args*/);
		~PmergeMe();
		PmergeMe(const PmergeMe& source);
		PmergeMe& operator=(const PmergeMe& source);

		void	parseInput(char **argv);
};

# include "PmergeMe.tpp"

#endif
