
OS = $(shell uname)

# Program name
NAME = liblog42.a
# NAME = log42

# Source and object directories
SRCDIR = srcs
OBJDIR = objs

# Libraries directories
COMMONDIR = common

# Compiler and flags
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -Wshadow -MMD -MP -std=c++98
DEBUG_FLAGS = -g -fno-omit-frame-pointer -fstack-protector-all

INCLUDES = -I includes -I $(COMMONDIR)/includes

LIBS = -L $(COMMONDIR) -lcommon

# vpath to specify where to find the .cpp files
vpath %.cpp \
	$(SRCDIR) \

# Sources and object files
SRCES = BufferingFormatter.cpp FileHandler.cpp Filter.cpp Filterer.cpp Formatter.cpp Handler.cpp Logger.cpp Logging.cpp LogRecord.cpp Manager.cpp Node.cpp PercentStyle.cpp PlaceHolder.cpp RootLogger.cpp StreamHandler.cpp
#		main.cpp


OBJS_SRCES = $(addprefix $(OBJDIR)/, $(SRCES:.cpp=.o))

# Default rule: make all and compile the program
all: $(NAME)

debug: CXXFLAGS = $(DEBUG_FLAGS)

# Rebuild with debug flags
debug: re

# Sanitize
sanitize: DEBUG_FLAGS += -fsanitize=address 
sanitize: debug 

# Rule to compile with Leaks check
leaks:
ifeq ($(OS), Darwin)
	MallocStackLogging=YES leaks --outputGraph=log42.memgraph --fullContent --fullStackHistory --atExit -- ./$(NAME)
else ifeq ($(OS), Linux)
	valgrind --leak-check=full --track-origins=yes --log-file=log42.log --show-leak-kinds=all --trace-children=yes --track-fds=all ./$(NAME)
endif

# Compile each .cpp file to .o
$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Rule to compile the final executable
$(NAME): $(OBJS_SRCES) $(COMMONDIR)/libcommon.a
	ar -rcs $(NAME) $(OBJS_SRCES)
	# $(CXX) $(CXXFLAGS) $(OBJS_SRCES) $(LIBS) -o $(NAME)

# Rule to clean up object files
clean:
	@rm -rf $(OBJDIR)

# Rule to clean up object files and executable
fclean: clean
	@rm -f $(NAME)

# Rule to recompile everything
re: fclean all

.PHONY: all clean fclean re bonus debug sanitize
