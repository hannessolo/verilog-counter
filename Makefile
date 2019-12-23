all:
	make clean && make verilog && make tests

verilog:
	cd src/verilog && verilator -Wall --cc microaddr.sv microaddr_counter.sv --prefix Microaddr --exe ../test/microaddr_counter_test.cpp -CFLAGS "-std=c++11"

tests:
	cd src/verilog/obj_dir && make -j8 -f Microaddr.mk Microaddr && ./Microaddr

clean:
	rm -rf src/verilog/obj_dir

copyTTF:
	cd tools && gcc vidorcvt.c -o vidorcvt
	(tools/vidorcvt < src/verilog/output_files/MKRVIDOR4000.ttf) > arduino/app.h
