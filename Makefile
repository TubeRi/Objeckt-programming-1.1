CXX = g++
CXXFLAGS = -std=c++17 -O3 -Wall -Wextra

SRC = src/main.cpp src/student.cpp src/gen.cpp

TARGET = programa

all:
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

run:
	./$(TARGET)

clean:
	rm -f $(TARGET)

	## Paleidimas naudojant Makefile

```bash
make
./programa