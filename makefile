build :
	g++ -Wall ./src/*.cpp -lm -o output

run :
	./output

clean :
	rm output