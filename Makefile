CC = clang

CFLAGS = -x c++ -c -std=c++14 -pedantic -Wall
LFLAGS = -lstdc++

SOURCES = biblio.cc
OBJECTS = $(SOURCES:.cc=.o)
EXECUTABLE = biblio


all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
		$(CC) $(LFLAGS) $(OBJECTS) -o $@

.cpp.o:
		$(CC) $(CFLAGS) $< -o $@

clean:
		rm -f $(EXECUTABLE) $(OBJECTS)

# TARGET = cpp11_test
#$(TARGET): $(TARGET).cpp
#		$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).cpp $(LFLAGS)

