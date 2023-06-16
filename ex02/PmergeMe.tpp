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
		if (std::find(this->cont_.begin(), this->cont_.end(), tmp_int) != this->cont_.end())
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
	int									pairNum = this->cont_.size() / 2;
	int									isOdd = this->cont_.size() % 2;

	// size가 2보다 작으면 그냥 종료

	for (int iter = 0; iter < pairNum; iter++)
	{
		if (this->cont_[iter * 2] < this->cont_[iter * 2 + 1])
		{
			std::swap(this->cont_[iter * 2], this->cont_[iter * 2 + 1]);
		}
	}

	// pair수만큼 옮기면서 이진정렬한다.

	Piterator	baseEnd;

	for (int iter = 0; iter < pairNum; iter++)
	{
		// this->cont_[iter * 2]
		// 이전 iter 값이랑 비교한다
		// iterator 저장을 위한 변수 필요
			// 자기 자신을 baseEnd로 지정하고 그 앞 노드를 정렬
	}

}

// template<template<typename, typename> class CONT> 
// void	PmergeMe<CONT>::mergeSplit(Piterator first, Piterator last)
// {
// 	Piterator	middle;
// }

// template<template<typename, typename> class CONT> 
// void	PmergeMe<CONT>::mergeInsert(Piterator first, Piterator last)
// {

// }

// template<template<typename, typename> class CONT> 
// void	PmergeMe<CONT>::mergeSort(Piterator first, Piterator last)
// {
	
// }

template<template<typename, typename> class CONT> 
void	PmergeMe<CONT>::printCont()
{
	size_t	contSize = this->cont_.size();

	for (size_t iter = 0; iter < contSize; iter++)
	{
		std::cout << this->cont_[iter] << " ";
	}
	std::cout << std::endl;
}

#endif
