#ifndef PMERGEME_TPP
# define PMERGEME_TPP

# include "PmergeMe.hpp"

# include <sstream>
# include <string>
# include <exception>

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
void	PmergeMe<CONT>::PmergeIt()
{
	// 호출할 때마다 새로운 컨테이너를 만들어줄까?
	// 아니면 element를 조작할까?
	// conatiner를 사용하여 정렬한다고 할 때, 어떤 접근이 더 나을까?
	// 아마도 iterator를 넘겨주면서 해당 iterator 간 값을 바꾸는게 나을 듯.

	// 일정 개수 단위까지 잘라냄
		// MergeSplit, MergeSplit
	// 일정 개수가 되면 삽입 정렬로 정렬함
		// MergeInsert
	// 합치는 과정에서 정렬함
		// MergeSort
}

// https://stackoverflow.com/questions/2152986/how-do-i-get-the-index-of-an-iterator-of-an-stdvector
// template화하여 공통적으로 사용하면서 작동 시간도 줄이고 싶다.
// 어쩌면 [index] 오버로딩이 더 연산량 많을 수도 있다. 적당히 알아보고 선택하기.
// +++ 어차피 std library 알고리즘을 따로 사용하지 않을 것을 권장하고 있음. 그냥 int index로 사용해보자.
template<template<typename, typename> class CONT> 
void	PmergeMe<CONT>::mergeSplit(int start, int end)
{

}

template<template<typename, typename> class CONT> 
void	PmergeMe<CONT>::mergeInsert(int start, int end)
{

}

template<template<typename, typename> class CONT> 
void	PmergeMe<CONT>::mergeSort(int start, int end)
{
	
}

#endif
