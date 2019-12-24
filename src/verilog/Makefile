MODULES := counter

TYPE_FILES := counter_types.sv alu_types.sv

CC := verilator

% : %.sv $(TYPE_FILES) ../test/%_test.cpp
	$(CC) -Wall -cc $(TYPE_FILES) $@.sv -y . --prefix $@ --exe ../test/$@_test.cpp -CFLAGS "-std=c++11"
	make -C obj_dir -j8 -f $@.mk
	cd obj_dir && ./$@

all: $(MODULES)

clean:
	rm -rf obj_dir
