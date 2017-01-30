rayTracer: main.cpp 
	g++ -std=c++11 -o $@ main.cpp cena.cpp light.cpp object.cpp -o rayTracer -larmadillo -g

clean:
	$(RM) rayTracer
