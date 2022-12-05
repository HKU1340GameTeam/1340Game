FLAGS=-Werror -Wall -pedantic-errors -std=c++11


main: main.o Layer.o Player.o kbhit.o common.o Camera.o Color.o Animator.o Scene.o Talk.o Conversation.o AboveHeadComment.o ConvBox.o NPC.o UI.o
	g++ $(FLAGS) $^ -o $@

main.o: main.cpp common.h Layer.h Player.h kbhit.h Camera.h
	g++ $(FLAGS) -c $<

Layer.o: Layer.cpp Layer.h common.h
	g++ $(FLAGS) -c $<

Player.o: Player.cpp Player.h Layer.h common.h AboveHeadComment.h
	g++ $(FLAGS) -c $<

kbhit.o: kbhit.cpp kbhit.h
	g++ $(FLAGS) -c $<

Camera.o: Camera.cpp Camera.h common.h Layer.h Player.h Color.h
	g++ $(FLAGS) -c $<

Color.o: Color.cpp Color.h
	g++ $(FLAGS) -c $<

Animator.o: Animator.cpp Animator.h Layer.h common.h
	g++ $(FLAGS) -c $<

Conversation.o: Conversation.cpp Conversation.h Talk.h
	g++ $(FLAGS) -c $<

Talk.o: Talk.cpp Talk.h
	g++ $(FLAGS) -c $<

Scene.o: Scene.cpp Scene.h Layer.h Player.h Animator.h NPC.h
	g++ $(FLAGS) -c $<

AboveHeadComment.o: AboveHeadComment.cpp AboveHeadComment.h Layer.h
	g++ $(FLAGS) -c $<

ConvBox.o: ConvBox.cpp ConvBox.h Layer.h Camera.h Conversation.h
	g++ $(FLAGS) -c $<

NPC.o: NPC.cpp NPC.h Layer.h Conversation.h Player.h AboveHeadComment.h
	g++ $(FLAGS) -c $<

UI.o: UI.cpp UI.h
	g++ $(FLAGS) -c $<

common.o: common.cpp common.h
	g++ $(FLAGS) -c $<

clean:
	rm *.o

InstallDependencies:
	echo "Install Begins"
	echo "Install Ends"
PurgeDependencies:
	echo "Deletion Begins"
	echo "Deletion Ends"
.PHONY:
	clean InstallDependencies PurgeDependencies
