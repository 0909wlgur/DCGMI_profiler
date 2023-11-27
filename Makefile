
all:
	gcc -I /usr/local/cuda/targets/x86_64-linux/include \
	-o profiler profiler.c \
	-ldl -ldcgm -lncurses -lpthread -lnvidia-ml

clean:
	rm -f frontend