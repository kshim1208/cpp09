#ifndef PmergeMe_HPP
# define PmergeMe_HPP

class PmergeMe
{
	private:
		/* data */
	public:
		PmergeMe(/* args*/);
		~PmergeMe();
		PmergeMe(const PmergeMe& source);
		PmergeMe& operator=(const PmergeMe& source);

		void	parseInput();
};

#endif