all:
	make clean
	make verilog

.PHONY: verilog
verilog:
	make -C src/verilog

.PHONY: clean
clean:
	rm -rf src/verilog/obj_dir
	rm -f tools/vidorcvt

.PHONY: copyTTF
copyTTF:
	cd tools && gcc vidorcvt.c -o vidorcvt
	(tools/vidorcvt < src/verilog/output_files/MKRVIDOR4000.ttf) > arduino/app.h
