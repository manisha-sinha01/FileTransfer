CC = gcc
CFLAGS = -g -Wall
SOURCE = main.c connections.c getFile.c sendFile.c notifications.c

TARGETS = ftp_custom
all : clean
		$(CC) $(CFLAGS) $(SOURCE) -o $(TARGETS)

clean :
		rm -f $(TARGETS)

install :
		cp $(TARGETS) /bin