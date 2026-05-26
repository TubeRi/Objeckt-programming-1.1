CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra

TARGET = programa

SRC = src/main.cpp \
      src/student.cpp \
      src/gen.cpp

all:
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

run:
	./$(TARGET)

clean:
	del /Q $(TARGET).exe 2>nul || rm -f $(TARGET)