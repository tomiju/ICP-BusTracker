all:
	cd src && \
	qmake && \
	make && \
	mv tracker icp

run:
	./src/icp

clean:
	rm -f src/*.o
	rm -f src/Makefile
	rm -f src/icp
	rm -f -r doc/*

pack:
	zip xjulin08_xkanto14 src/*.cpp src/*.h src/*.ui src/*.pro doc examples/map.json  README.txt Makefile Doxyfile

doxygen:
	doxygen Doxyfile