#ifndef PmergeMe_HPP
# define PmergeMe_HPP

#include <vector>
#include <list>

#include <exception>

template<template<typename, typename> class CONT> 
class PmergeMe
{
	typedef	CONT<int>::iterator	Piterator;

	private:
		CONT<int, std::allocator<int> >	cont_;
	public:
		PmergeMe(/* args*/);
		~PmergeMe();
		PmergeMe(const PmergeMe& source);
		PmergeMe& operator=(const PmergeMe& source);

		class badInput : public std::exception
		{
			public:
				badInput(std::string& str);
				badInput(const std::string& str);
				~badInput() throw ();
				const char* what() const throw ();

			private:
				std::string*	nowLine_;
		};

		void	parseInput(char **argv);
		void	PmergeIt();
		void	mergeSplit(Piterator first, Piterator last);
		void	mergeInsert(Piterator first, Piterator last);
		void	mergeSort(Piterator first, Piterator last);

};

# include "PmergeMe.tpp"

#endif
