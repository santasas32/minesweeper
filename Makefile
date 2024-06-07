CFLAGS = -I ./CONTROLLER -I ./LOGIC -I ./workWithUser -I ./errorProc -g -c
CONTROLLER_DIR = ./CONTROLLER/
LOGIC_DIR = ./LOGIC/
workWithUser_DIR = ./workWithUser/
errorProc_DIR = ./errorProc/
object_deps = CONTROLLER.o workWithUser.o LOGIC.o errorProc.o

minesweeper.exe: $(object_deps)
	gcc -o minesweeper *.o
	del *.o

CONTROLLER.o: $(CONTROLLER_DIR)CONTROLLER.c
	gcc $(CFLAGS) $(CONTROLLER_DIR)CONTROLLER.c

workWithUser.o: $(workWithUser_DIR)workWithUser.c $(workWithUser_DIR)workWithUser.h
	gcc $(CFLAGS) $(workWithUser_DIR)workWithUser.c

LOGIC.o: $(LOGIC_DIR)LOGIC.c $(LOGIC_DIR)LOGIC.h
	gcc $(CFLAGS) $(LOGIC_DIR)LOGIC.c

errorProc.o: $(errorProc_DIR)errorProc.c $(errorProc_DIR)errorProc.h
	gcc $(CFLAGS) $(errorProc_DIR)errorProc.c

clean:
	del minesweeper.exe, *.o