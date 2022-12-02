NAME		=	containers_test
SRCS		=	test/main.cpp \
				test/vector/vector_test.cpp \
				test/vector/vector_performance.cpp \
				test/test_utils.cpp \
				test/map/map_test.cpp \
				test/map/map_performance.cpp \
				test/set/set_test.cpp \
				test/set/set_performance.cpp \
				test/stack/stack_test.cpp \
				test/stack/stack_performance.cpp

UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
CXX	= clang++
CXXFLAGS	= -Wall -Wextra -Werror -std=c++98
else ifeq ($(UNAME), Linux)
CXX	= g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -Wno-c++0x-compat #-g3 -fsanitize=address
else
	@echo "unsupported OS"
	exit 1
endif

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
