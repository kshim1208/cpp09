NAME = PmergeMe
CXX = c++
CXXFLAGS = -Wall -Werror -Wextra -g
# CXXFLAGS = -Wall -Werror -Wextra -std=c++98 -g
RM = rm
RMFLAGS = -f

SRCS = main.cpp 
 
OBJS = $(SRCS:.cpp=.o)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

%.o	: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

all : $(NAME)

clean:
	$(RM) $(RMFLAGS) $(OBJS)

fclean: clean
	$(RM) $(RMFLAGS) $(NAME)

re:
	make fclean
	make all

.PHONY:all clean fclean re