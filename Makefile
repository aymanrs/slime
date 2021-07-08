.PHONY: clean mrproper
CXX = g++
CXXFLAGS = -c -I include -Wextra -Wall -std=c++14
LDFLAGS = -Llib -lsfml-graphics -lsfml-window -lsfml-system
EXEC = Slime

all: bin/$(EXEC)

bin/$(EXEC): bin/prog
	echo "#!/bin/bash\nexport LD_LIBRARY_PATH=lib\n./bin/prog" > bin/$(EXEC)
	chmod +x bin/$(EXEC)

bin/prog: bin/obj/main.o bin/obj/agent.o
	export LD_LIBRARY_PATH=lib
	$(CXX) bin/obj/main.o bin/obj/agent.o -o bin/prog $(LDFLAGS)

bin/obj/main.o: src/main.cpp
	$(CXX) src/main.cpp -o bin/obj/main.o $(CXXFLAGS)

bin/obj/agent.o: src/agent.cpp
	$(CXX) src/agent.cpp -o bin/obj/agent.o $(CXXFLAGS)

clean:
	rm -rf bin/obj/*

mrproper: clean
	rm -f bin/$(EXEC) bin/prog
