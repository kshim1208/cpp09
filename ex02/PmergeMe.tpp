#ifndef PMERGEME_TPP
# define PMERGEME_TPP

# include "PmergeMe.hpp"

# include <sstream>

template<typename CONT, typename ELEM>
PmergeMe<CONT, ELEM>::PmergeMe(/* args*/){}

template<typename CONT, typename ELEM>
PmergeMe<CONT, ELEM>::~PmergeMe(){}

template<typename CONT, typename ELEM>
PmergeMe<CONT, ELEM>::PmergeMe(const PmergeMe<CONT, ELEM>& source){}

template<typename CONT, typename ELEM>
PmergeMe<CONT, ELEM>& PmergeMe<CONT, ELEM>::operator=(const PmergeMe<CONT, ELEM>& source){}

template<typename CONT, typename ELEM>
void	PmergeMe<CONT, ELEM>::parseInput(char **argv)
{
	std::stringstream	tmp_stream;
	int	iter = 0;
	int	tmp_int = 0;
	
	while (argv[iter] != 0)
	{
		tmp_stream.str("");
		tmp_stream.clear();
		tmp_stream << argv[iter];
		tmp_stream >> tmp_int;
		if (tmp_stream.eof() == false || tmp_stream.fail() == true)
		{
			// invalid str
		}
		if (tmp_int <= 0)
		{
			// invalid value
		}
		this->cont_.push_back(tmp_int);
		iter++;
	}
}

#endif
