SHELL := /bin/bash

override C_FLAG := -O0 -g ${C_FLAG}

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

${ID}.o: ${ID}.c
	@echo "building..."
	@gcc $^ -o $@ ${C_FLAG}

run: ${ID}.o 
	@echo "running..."
	@./$^ ${ARG}

debug: check ${ID}.o
	@gdb --args ./${ID}.o
clean:
	@rm -rf *.o
