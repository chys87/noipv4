.PHONY: all
all: libnoipv4.so

CXX := g++
CXXFLAGS := -O2 -Wall -Wextra -fPIC -fno-exceptions

# --as-needed tells linker to drop libstdc++.so dependency
libnoipv4.so: main.o
	$(CXX) -Wl,--as-needed -shared $(CXXFLAGS) -o $@ $< -ldl

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f *.so *.o
