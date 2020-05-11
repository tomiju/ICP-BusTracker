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

pack:
	zip xjulin08_xkanto14 src/*.cpp src/*.h src/*.ui src/*.pro doc  README.txt Makefile examples/map.json

doxygen:
