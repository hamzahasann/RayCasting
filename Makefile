all:
	g++ -c main.cpp -I /usr/include/SFML
	g++ main.o -o sfml-app -L/usr/lib -lsfml-graphics -lsfml-window -lsfml-system
	./sfml-app
	rm main.o
	