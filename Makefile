rebuild: setup.py matrix.cpp
	rm -rf matrix.cpython-37m-darwin.so
	rm -rf build
	python3 setup.py build
	cp build/lib.macosx-10.14-x86_64-3.7/* .

run: main.py
	python3 main.py

testfile:
	g++ -std=c++11  -o test/test test/test.cpp && test/test