CXX = g++
RM=rm -f

EXTRA_CCFLAGS   = -Wall -Wextra -Wcast-qual -Wfloat-equal -Wpedantic -Wpointer-arith -Wshadow
CXXOPTFLAGS     = -O2
CXXFLAGS        = -std=c++11 $(EXTRA_CCFLAGS) $(CXXOPTFLAGS)

LDLIBS=-larmadillo
MAKELIBFLAGS=-current_version 0.1 -compatibility_version 0.1 -dynamiclib

TARGET = libadsp.dylib
TESTTARGET = dsptest
SOURCE_FILES=src/stft.cpp src/filters.cpp src/windows.cpp src/helpers.cpp
OBJECT_FILES=$(subst .cpp,.o,$(SOURCE_FILES))

TEST_SOURCE_FILES = $(SOURCE_FILES) tests/tests.cpp
TEST_OBJECT_FILES = $(subst .cpp,.o,$(TEST_SOURCE_FILES))

all: $(TARGET)

test: $(TESTTARGET)

$(TARGET): $(OBJECT_FILES)
	$(CXX) $(CXXFLAGS) $(MAKELIBFLAGS) -o $(TARGET) $(OBJECT_FILES) $(LDLIBS)

$(TESTTARGET): $(TEST_OBJECT_FILES)
	$(CXX) $(CXXFLAGS) -o $(TESTTARGET) $(TEST_OBJECT_FILES) $(LDLIBS)
	./dsptest

depend: .depend
testdepend: .testdepend

.depend: $(SOURCE_FILES)
	$(RM) ./.depend
	$(CXX) $(CXXFLAGS) -MM $^>>./.depend;

.testdepend: $(TEST_SOURCE_FILES)
	$(RM) ./.testdepend
	$(CXX) $(CXXFLAGS) -MM $^>>./.testdepend;

.PHONY: clean

clean:
	$(RM) $(OBJECT_FILES)
	$(RM) ./.depend

include .depend
include .testdepend