OBJS	= Backpack.o Bridge.o CaptainsQuarters.o Corridor.o CrewMember.o CrewQuarters.o dansLibrary.o Engineering.o Game.o Harper.o Holly.o Lab.o Lester.o Lounge.o main.o Nate.o Penny.o Player.o Space.o
SOURCE	= Backpack.cpp Bridge.cpp CaptainsQuarters.cpp Corridor.cpp CrewMember.cpp CrewQuarters.cpp dansLibrary.cpp Engineering.cpp Game.cpp Harper.cpp Holly.cpp Lab.cpp Lester.cpp Lounge.cpp main.cpp Nate.cpp Penny.cpp Player.cpp Space.cpp
HEADER	= Backpack.hpp Bridge.hpp CaptainsQuarters.hpp colors.hpp Corridor.hpp CrewMember.hpp CrewQuarters.hpp dansLibrary.hpp Engineering.hpp Game.hpp Harper.hpp Holly.hpp Lab.hpp Lester.hpp Lounge.hpp Nate.hpp Penny.hpp Player.hpp Space.hpp
OUT	= donnarV
CC	 = g++
FLAGS	 = -g -c -Wall -std=c++11
LFLAGS	 = -std=c++11

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

Backpack.o: Backpack.cpp
	$(CC) $(FLAGS) Backpack.cpp 

Bridge.o: Bridge.cpp
	$(CC) $(FLAGS) Bridge.cpp 

CaptainsQuarters.o: CaptainsQuarters.cpp
	$(CC) $(FLAGS) CaptainsQuarters.cpp 

Corridor.o: Corridor.cpp
	$(CC) $(FLAGS) Corridor.cpp 

CrewMember.o: CrewMember.cpp
	$(CC) $(FLAGS) CrewMember.cpp 

CrewQuarters.o: CrewQuarters.cpp
	$(CC) $(FLAGS) CrewQuarters.cpp 

dansLibrary.o: dansLibrary.cpp
	$(CC) $(FLAGS) dansLibrary.cpp 

Engineering.o: Engineering.cpp
	$(CC) $(FLAGS) Engineering.cpp 

Game.o: Game.cpp
	$(CC) $(FLAGS) Game.cpp 

Harper.o: Harper.cpp
	$(CC) $(FLAGS) Harper.cpp 

Holly.o: Holly.cpp
	$(CC) $(FLAGS) Holly.cpp 

Lab.o: Lab.cpp
	$(CC) $(FLAGS) Lab.cpp 

Lester.o: Lester.cpp
	$(CC) $(FLAGS) Lester.cpp 

Lounge.o: Lounge.cpp
	$(CC) $(FLAGS) Lounge.cpp 

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp 

Nate.o: Nate.cpp
	$(CC) $(FLAGS) Nate.cpp 

Penny.o: Penny.cpp
	$(CC) $(FLAGS) Penny.cpp 

Player.o: Player.cpp
	$(CC) $(FLAGS) Player.cpp 

Space.o: Space.cpp
	$(CC) $(FLAGS) Space.cpp 


clean:
	rm -f $(OBJS) $(OUT)
