CXX = g++
RM=rm -f

EXTRA_CCFLAGS   = -Wall -Wextra -Wcast-qual -Wfloat-equal -Wpedantic -Wpointer-arith -Wshadow
CXXFLAGS        = -std=c++11 $(EXTRA_CCFLAGS)
CXXOPTFLAGS		= -std=c++11 $(EXTRA_CCFLAGS) -O2

LDLIBS=-larmadillo
MAKELIBFLAGS=-dynamiclib

TARGET = test
SOURCE_FILES=src/filters.cpp src/windows.cpp src/helpers.cpp tests/tests.cpp
OBJECT_FILES=$(subst .cpp,.o,$(SOURCE_FILES))
# SOURCE_FILES += tests/tests.cpp
# OBJECT_FILES += tests/tests.o
# filters.o: src/filters.cpp src/filters.hpp
# 	g++ $(CPPFLAGS) -c src/filters.cpp

# test: TARGET = test
	


all: $(TARGET)

$(TARGET): $(OBJECT_FILES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECT_FILES) $(LDLIBS)
	./test

depend: .depend

.depend: $(SOURCE_FILES)
	$(RM) ./.depend
	$(CXX) $(CPPFLAGS) -MM $^>>./.depend;

clean:
	$(RM) $(OBJECT_FILES)

include .depend