all:
	make clean && make verilog && make tests

verilog:
	verilator -Wall --cc microaddr.v microaddr_counter.v --prefix Microaddr --exe microaddr_counter_test.cpp -CFLAGS "-std=c++11"

tests:
	cd obj_dir && make -j8 -f Microaddr.mk Microaddr

clean:
	rm -rf obj_dir
