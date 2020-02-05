SHELL := /bin/bash

override CPP_FLAG := -O0 -g ${CPP_FLAG}

all: check run

check:
	@if [ "${ID}" = "" ]; then \
		echo "error: ID is not set" ;\
		exit -1; \
	fi

prepare: check
	@if [ ! -d "${ID}" ]; then\
		mkdir ${ID} ;\
		echo "ID=${ID}" > ${ID}/Makefile ;\
		echo "include ../Makefile" >> ${ID}/Makefile ;\
	fi

${ID}.o: ${ID}.cpp
	@echo "building..."
	@g++ $^ -o $@ ${CPP_FLAG}

run: ${ID}.o 
	@echo "running..."
	@./$^

debug: check ${ID}.o
	@gdb --args ./${ID}.o
clean:
	@rm -rf *.o
