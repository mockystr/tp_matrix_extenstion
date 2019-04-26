rebuild: setup.py matrix.cpp
	python3 setup.py build
	cp build/lib.macosx-10.14-x86_64-3.7/* .

test: main.py
	python3 main.py