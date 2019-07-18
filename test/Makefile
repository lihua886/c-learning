SRCS:=$(wildcard *.cc)
TARGETS:=$(SRCS:%.cc=%)
all:$(TARGETS)
%:%.cc
	g++ $< -g -o $@ 
clean:
	rm $(TARGETS)
