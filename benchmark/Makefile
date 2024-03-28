CC = gcc
CFLAGS = -lpthread -Wno-overflow -pthread

TARGET1 = cpubench
FILE1	= cpubench.c
TARGET2 = membench
FILE2	= membench.c

all:	$(TARGET1) $(TARGET2)

$(TARGET1): $(FILE1)
	$(CC) $(CFLAGS) -o $(TARGET1) $(FILE1)
	
$(TARGET2): $(FILE2)
	$(CC) $(CFLAGS) -o $(TARGET2) $(FILE2)


clean:
	rm $(TARGET1) $(TARGET2)
