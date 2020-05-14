all:
	cd src && \
	qmake && \
	make && \
	mv tracker icp

run:
	./src/icp

clean:
	rm src/*.o
	rm src/Makefile
	rm src/icp
	rm doc/*

pack:
	zip xjulin08_xkanto14 src/*.cpp src/*.h src/*.ui src/*.pro doc examples/map.json  README.txt Makefile Doxyfile

doxygen:
	doxygen Doxyfile