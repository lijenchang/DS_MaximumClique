CC = g++ -O3 -lm -std=c++11

#SRCS = ../*.cpp
RO_SRCS = ./*.cpp

clique_find:
	$(CC) -o $@ $(RO_SRCS)


#RO: $(RO_SRCS)
#	$(CC) -c $(RO_SRCS)

.PHONY: clean

clean:
ifeq ($(OS),Windows_NT)
	del clique_find.exe *.o
else
	rm clique_find *.o
endif
