SRCS:=$(wildcard *.cc)
TARGETS:=$(SRCS:%.cc=%)
all:$(TARGETS)
%:%.cc
	g++ $< -g -o $@  -lpthread
clean:
	rm $(TARGETS)
