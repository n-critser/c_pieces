
SUBPROJ = numnums noise_conv strbuild threads userio

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
