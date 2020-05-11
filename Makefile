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
	
