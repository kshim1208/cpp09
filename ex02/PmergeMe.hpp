#ifndef PmergeMe_HPP
# define PmergeMe_HPP

# include <vector>
# include <deque>

# include <exception>
# include <string>

# define BEFORE 0
# define AFTER 1
# define ONLY 2

template<template<typename, typename> class CONT> 
class PmergeMe
{
	typedef typename CONT<int, std::allocator<int> >::iterator	Piterator;

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

		void		parseInput(char **argv);
		void		pmergeIt();
		void		printCont(int mode);
		int			contSize() const ;
};

# include "PmergeMe.tpp"

#endif
