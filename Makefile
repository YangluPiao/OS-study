SHELL := /bin/bash

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
	@g++ $^ -o $@

run: ${ID}.o 
	@echo "running..."
	@./$^

clean:
	@rm -rf *.o
