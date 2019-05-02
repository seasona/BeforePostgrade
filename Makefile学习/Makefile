CC=gcc
OBJ= sort.o max.o main.o

#VPATH和vpath解决的都是依赖的存在路径，只是让make找到目标路径
#VPATH=src/max src/sort src/main
vpath %.c src/max src/sort src/main
vpath %.h include

#命令中也要包括编译的路径，这是让gcc找到目标路径
CFLAGS=-I include

exec:$(OBJ)
	$(CC) -o $@ $(OBJ)

%.o:%.c 
	$(CC) -c $(CFLAGS) $< 

.PHONY:clean

clean:
	rm -rf exec $(OBJ)