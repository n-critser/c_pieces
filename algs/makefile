
SUBPROJ = merge_sort insertion_sort matrix_mult max_subarray

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
