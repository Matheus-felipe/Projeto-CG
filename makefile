rayTracer: main.cpp 
	g++ -std=c++11 -o $@ main.cpp Object.cpp Cena.cpp Light.cpp -O2 -larmadillo

clean:
$(RM) rayTracer