.PHONY: clean

headers:= $(wildcard *.h)
sources:= $(wildcard *.c)
target:= LL
cc:= gcc
std:= --ansi #--std=c99
shared:= --shared

link: clean objects
	@echo "linking..."
	$(cc) -o $(target) *.o
	@echo "done."

objects: $(sources)
	@echo "compiling source code..."
	$(cc) $(std) -c $(sources)
	@echo "ok."

shared: objects
	$(cc) $(shared) -c $(sources) 

clean:
	@echo "removing trash..."
	-rm *.o $(target)