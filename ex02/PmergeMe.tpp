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

#endif
