CC = g++
DEBFLAGS = -std=c++14 -g
RELFLAGS = -std=c++14 -s -O2
DEBOUT = lab1_ta_d.exe
RELOUT = lab1_ta.exe
SRC = main.cpp implicant.cpp logic.cpp imparr.cpp

debug:
	$(CC) $(DEBFLAGS) $(SRC) -o $(DEBOUT)

release:
	$(CC) $(RELFLAGS) $(SRC) -o $(RELOUT)
