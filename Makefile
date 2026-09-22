CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Werror -Iinclude

TARGET = build/server

SRC = src

OBJ = build/main.o build/Request.o build/Router.o build/Server.o build/Response.o

all: $(TARGET)

$(TARGET): build $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

# Теперь имя цели (build/main.o) совпадает с тем, куда сохраняется результат (-o build/main.o)
build/main.o : main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o build/main.o

build/Request.o : $(SRC)/Request.cpp
	$(CXX) $(CXXFLAGS) -c $(SRC)/Request.cpp -o build/Request.o

build/Response.o : $(SRC)/Response.cpp
	$(CXX) $(CXXFLAGS) -c $(SRC)/Response.cpp -o build/Response.o

build/Router.o : $(SRC)/Router.cpp
	$(CXX) $(CXXFLAGS) -c $(SRC)/Router.cpp -o build/Router.o

build/Server.o : $(SRC)/Server.cpp
	$(CXX) $(CXXFLAGS) -c $(SRC)/Server.cpp -o build/Server.o
     
build:
	mkdir -p build

start:
	./$(TARGET)

clean:
	rm -rf build