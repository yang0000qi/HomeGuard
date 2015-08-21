CXX =  $(shell which /usr/bin/clang++ 2>/dev/null || which g++)
CXXFLAGS = -I./include -I../include -std=c++11 -Wall -g

TARGET = HomeGuard
TEST_TARGET = testHomeGuard

SOURCES = $(wildcard ./src/*.cpp)
OBJECTS = $(patsubst %.cpp,%.o,$(SOURCES))

TEST_SOURCES = $(wildcard ./test/*.cpp) \
               $(filter-out ./src/main.cpp, $(SOURCES))

TEST_OBJECTS = $(patsubst %.cpp,%.o,$(TEST_SOURCES))

.PHONY:
	clean

all: $(TARGET)

run: all
	./$(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^

$(TEST_TARGET): $(TEST_OBJECTS)
	$(CXX) -o $@ $^

test: $(TEST_TARGET)
	./$(TEST_TARGET)

test-detail: $(TEST_TARGET)
	./$(TEST_TARGET) -s

clean:
	rm -rf $(OBJECTS) $(TEST_OBJECTS) $(TARGET) $(TEST_TARGET)
