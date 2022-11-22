NAME		=	containers_test
SRCS		=	test/main.cpp \
				test/vector/vector_test.cpp \
				test/map/map_test.cpp \
				test/vector/vector_performance.cpp \
				test/test_utils.cpp \
				test/map/rbtree_test.cpp \

CXX			=	g++ 
CXXFLAGS	=	-Wall -Wextra -Werror -std=c++98 -g3 -Wno-c++0x-compat -fsanitize=address
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
