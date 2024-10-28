build:
	clang++ ./src/main.cpp -o fractal.out -lSDL2

run: build 
	./fractal.out

clean:
	rm ./fractal.out
