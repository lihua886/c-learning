SRCS:=$(wildcard *.cc)
OBJS:=$(patsubst %.cc,%.o,$(SRCS))
TARGETS:=main
all:$(TARGETS)
$(TARGETS):$(OBJS)
	g++ $^ -g -o $@ 
%.o:%.cc
	g++ -c -o $@ $<  
.PHONY:clean
clean:
	rm $(TARGETS) $(OBJS)
