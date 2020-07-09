OBJ = autoCrawler.out
OBJS_PATH = src/
OBJS += $(OBJS_PATH)main.o
OBJS += $(OBJS_PATH)spider.o
OBJS += $(OBJS_PATH)https.o
OBJS += $(OBJS_PATH)kalg.o

CC = g++
INCLUDE_PATH = ./include/

$(OBJ):$(OBJS)
	$(CC) $^ -o $@ -l curl

%.o:%.cpp
	$(CC) -I $(INCLUDE_PATH) -c $^ -o $@ 

.PHONY:

clean:
	rm $(OBJ)
disclean:
	rm $(OBJ) $(OBJS_PATH)*.o 
reset:
	make disclean
	make
proxy:
	../Download/proxy.sh	
go:
	make proxy
	./$(OBJ)
