 
SUBPROJ = numnums noise_conv strbuild threads userio algs grepish file_to_buf memcpy_test

all:
	for i in $(SUBPROJ) ;\
	do \
	cd $$i ;\
	make all ;\
	cd ../ ;\
	done\


clean:
	for i in $(SUBPROJ) ;\
	do \
	cd $$i ;\
	make clean ;\
	cd ../ ;\
	done\
