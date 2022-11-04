FLAGS=-ggdb3 -Werror -Wall -pedantic-errors -std=c++11


main: main.o Layer.o Player.o kbhit.o common.o Camera.o Color.o
	g++ $(FLAGS) $^ -o $@

main.o: main.cpp common.h Layer.h Player.h kbhit.h Camera.h
	g++ $(FLAGS) -c $<

Layer.o: Layer.cpp Layer.h common.h
	g++ $(FLAGS) -c $<

Player.o: Player.cpp Player.h Layer.h common.h
	g++ $(FLAGS) -c $<

kbhit.o: kbhit.cpp kbhit.h
	g++ $(FLAGS) -c $<

Camera.o: Camera.cpp Camera.h common.h Layer.h Player.h Color.h
	g++ $(FLAGS) -c $<

Color.o: Color.cpp Color.h
	g++ $(FLAGS) -c $<

common.o: common.cpp common.h
	g++ $(FLAGS) -c $<

clean:
	rm *.o

.PHONY:
	clean
