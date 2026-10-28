CPP      = g++
# -MMD tells the compiler to generate dependency files (.d) tracking your .h files
# -MP prevents build crashes if a header file is deleted
CPPFLAGS = -Wall -Wextra -Wpedantic -Wconversion -Wdeprecated -fsanitize=undefined -MMD -MP -std=c++20
LDFLAGS  = -lfmt

# OBJFILES = memory.o main.o
MAIN_SRC = main.cpp
MAIN_OBJ = $(MAIN_SRC:.cpp=.o)
SRCS = memory.cpp mmu.cpp allocator.cpp paging.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET   = main

TEST_SRCS  = test_memory.cpp
TEST_OBJS  = $(TEST_SRCS:.cpp=.o)
TESTFLAGS  = -lgtest -fsanitize=undefined
TESTTARGET = test

DEPS = $(SRCS:.cpp=.d) $(MAIN_SRC:.cpp=.d) $(TEST_SRCS:.cpp=.d)


all: $(TARGET)

$(TARGET): $(OBJS) $(MAIN_OBJ)
	$(CPP) $(CPPFLAGS) -o $(TARGET) $(OBJS) $(MAIN_OBJ) $(LDFLAGS)

# Pattern rule to compile .cpp files to .o files
# $< is the first prerequisite and $@ is the target
# $^ is all the prereqs
%.o: %.cpp
	$(CPP) $(CPPFLAGS) -c $< -o $@

# Include the auto-generated header dependencies that -MMD tracks
-include $(DEPS)

format:
	clang-format --style=file -i *.cpp *.h

test: $(OBJS) $(TEST_OBJS)
	$(CPP) -o $(TESTTARGET) $(OBJS) $(TEST_OBJS) $(TESTFLAGS)

valgrind: main
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-origins=yes --track-fds=yes -s ./$(TARGET)

clean:
	rm -f $(OBJS) $(MAIN_OBJ) $(TEST_OBJS) $(DEPS) $(TARGET) $(TESTTARGET) *~

# PHONY lists targets that don't produce a file so that existing files don't cause a failure
.PHONY: all format valgrind clean
