#ifndef PMERGEME_TPP
# define PMERGEME_TPP

# include "PmergeMe.hpp"

# include <algorithm>
# include <sstream>
# include <string>
# include <exception>
# include <iostream>
# include <utility>

template<template<typename, typename> class CONT> 
PmergeMe<CONT>::PmergeMe(/* args*/){}

template<template<typename, typename> class CONT> 
PmergeMe<CONT>::~PmergeMe(){}

template<template<typename, typename> class CONT> 
PmergeMe<CONT>::PmergeMe(const PmergeMe<CONT>& source)
{
	this->cont_.resize(source.cont_.size());
	std::copy(source.cont_.begin(), source.cont_.end(), this->cont_.begin());
}

template<template<typename, typename> class CONT> 
PmergeMe<CONT>& PmergeMe<CONT>::operator=(const PmergeMe<CONT>& source)
{
	this->cont_.resize(source.cont_.size());
	std::copy(source.cont_.begin(), source.cont_.end(), this->cont_.begin());
	return (*this);
}

template<template<typename, typename> class CONT> 
PmergeMe<CONT>::badInput::badInput(std::string& str)
{
	std::string	tmp = "Error: bad input => \'" + str + "\'";
	this->nowLine_ = new std::string(tmp);
}

template<template<typename, typename> class CONT> 
PmergeMe<CONT>::badInput::badInput(const std::string& str)
{
	std::string	tmp = "Error: bad input => \'" + str + "\'";
	this->nowLine_ = new std::string(tmp);
}

template<template<typename, typename> class CONT> 
PmergeMe<CONT>::badInput::~badInput() throw ()
{
	delete this->nowLine_;
}

template<template<typename, typename> class CONT> 
const char*	PmergeMe<CONT>::badInput::what() const throw ()
{
	return (this->nowLine_->c_str());
}

template<template<typename, typename> class CONT> 
void	PmergeMe<CONT>::parseInput(char **argv)
{
	std::stringstream	tmp_stream;
	std::string			tmp_str;
	int	iter = 1;
	int	tmp_int = 0;
	
	while (argv[iter] != 0)
	{
		tmp_stream.str("");
		tmp_stream.clear();
		tmp_stream << argv[iter];
		tmp_stream >> tmp_int;
		if (tmp_stream.eof() == false || tmp_stream.fail() == true)
		{
			throw PmergeMe<CONT>::badInput(argv[iter]);
		}
		tmp_stream << tmp_int;
		tmp_str = tmp_stream.str();
		if (tmp_int <= 0)
		{
			throw PmergeMe<CONT>::badInput(tmp_str);
		}
		this->cont_.push_back(tmp_int);
		iter++;
	}
}

template<template<typename, typename> class CONT> 
void	PmergeMe<CONT>::pmergeIt()
{
	int			pairNum = this->cont_.size() / 2;
	int			isOdd = this->cont_.size() % 2;

	// size가 2보다 작으면 그냥 종료
	if (this->cont_.size() < 2)
		return ;

	Piterator	base = this->cont_.begin();
	Piterator	pend = base + 1;
	Piterator	now;
	Piterator	tmp;

	// 반복문 구조상 임시 분리
	if (this->cont_[0] < this->cont_[1])
	{
		std::swap(this->cont_[0], this->cont_[1]);
	}

	// base 구간, pend 구간 설정
	for (int iter = 1; iter < pairNum; iter++)
	{
		if (this->cont_[iter * 2] < this->cont_[iter * 2 + 1])
		{
			std::swap(this->cont_[iter * 2], this->cont_[iter * 2 + 1]);
		}
	
		now = base + (iter * 2);
		tmp = pend;

		for (int swap_iter = 0; swap_iter < iter; swap_iter++)
		{
			std::iter_swap(tmp, now);
			tmp = tmp + 1;
		}
		pend = pend + 1;
	}

	// base 이진 정렬 및 pend 위치 동기화
	now = base + 1;
	for (int iter = 1; iter < pairNum; iter++)
	{
		int	distance;

		tmp = std::upper_bound(base, now, *now);
		if (tmp != now)
		{
			distance = std::distance(tmp, now);
			for (int swap_iter = 0; swap_iter < distance; swap_iter++)
			{
				std::iter_swap(tmp, now);
				std::iter_swap(tmp + pairNum, now + pairNum);
				tmp = tmp + 1;
			}
		}
		now = now + 1;
	}

	// pend를 base에 이진탐색하여 옮겨넣기
	bool	end = false;
	int		jacobsthalNumbers[] = {1, 3, 5, 11, 21, 43, 85, 171, 341, 683, 1365, 2731, 5461, 10923, 21845, 43691, 87381, 174763, 349525, 699051,
				1398101, 2796203, 5592405, 11184811, 22369621, 44739243, 89478485, 178956971, 357913941, 715827883, 1431655765};
	int		jacobIndex = 0;
	int		maxJacobIndex = 0;
	int		pendIter = 1;

	while (jacobsthalNumbers[maxJacobIndex] <= pairNum)
	{
		maxJacobIndex++;
	}

	while (end == false)
	{
		int distance;
		int jacobsIter = 1;

		if (pendIter != 1 && jacobsthalNumbers[jacobIndex] <= pairNum)
		{
			jacobIndex++;
			if (jacobsthalNumbers[jacobIndex] > pairNum)
			{
				jacobsIter = pairNum - jacobsthalNumbers[jacobIndex - 1];
				now = pend + pairNum - 1;
			}
			else
			{
				jacobsIter = jacobsthalNumbers[jacobIndex] - jacobsthalNumbers[jacobIndex - 1];
				now = pend + jacobsthalNumbers[jacobIndex] - 1;
			}
		}

		for (int iter = 0; iter < jacobsIter; iter++)
		{
			tmp = std::upper_bound(base, now, *now);
			if (tmp != now)
			{
				distance = std::distance(tmp, now);
				for (int swap_iter = 0; swap_iter < distance; swap_iter++)
				{
					std::iter_swap(tmp, now);
					tmp = tmp + 1;
				}
			}
			if (pendIter == pairNum)
			{
				end = true;
				break ;
			}
			pendIter++;
		}
	}

	// 홀수인 경우 1회 탐색 추가
	if (isOdd == true)
	{
		now = this->cont_.end() - 1;
		int distance;

		tmp = std::upper_bound(base, now, *now);
		if (tmp != now)
		{
			distance = std::distance(tmp, now);
			for (int swap_iter = 0; swap_iter < distance; swap_iter++)
			{
				std::iter_swap(tmp, now);
				tmp = tmp + 1;
			}
		}
	}

}

template<template<typename, typename> class CONT> 
void	PmergeMe<CONT>::printCont(int mode)
{
	size_t	contSize = this->cont_.size();

	if (mode == BEFORE)
	{
		std::cout << "Before: ";
	}
	else if (mode == AFTER)
	{
		std::cout << "After: ";
	}
	for (size_t iter = 0; iter < contSize; iter++)
	{
		std::cout << this->cont_[iter] << " ";
	}
	std::cout << std::endl;
}

template<template<typename, typename> class CONT> 
int	PmergeMe<CONT>::contSize() const
{
	return (this->cont_.size());
}


#endif
