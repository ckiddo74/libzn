all:
	@echo "make [install_python] [install_cpp]"

install_python: zn.py
	pip install .

install_cpp: build/libzn.so zn.hpp
	cp build/libzn.so /usr/local/lib
	ldconfig /usr/local/lib
	cp zn.hpp /usr/local/include

build/libzn.so: build/zn.o
	gcc -shared -o build/libzn.so build/zn.o

build/zn.o: zn.cpp zn.hpp
	mkdir -p build
	g++ -c zn.cpp -fPIC -o build/zn.o -I. -std=c++11 -O2 `pkg-config opencv --cflags`

clean:
	rm -rf build/







