NAME		=	test_containers
SRCS		=	test/main.cpp

CXX			=	g++ 
CXXFLAGS	=	-Wall -Wextra -Werror -std=c++98 -pedantic -g3 -Wno-c++0x-compat
RM			=	rm -f
OBJS		=	$(SRCS:.cpp=.o)

INC_DIR = includes/

all: 		$(NAME)

%.o: 		%.cpp
			$(CXX) $(CXXFLAGS) -I $(dir $(INC_DIR)) -c $< -o $@

$(NAME): 	$(OBJS) $(dir $(LIBFT_DIR))$(LIBFT)
			$(CXX) $(OBJS) $(CXXFLAGS) -o  $@

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re