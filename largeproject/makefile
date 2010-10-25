lib_a		:= lib/a
lib_b		:= lib/b
lib_c		:= lib/c
libraries	:= $(lib_a) $(lib_b) $(lib_c)
large		:= large/

#.PHONY: all $(libraries) $(large) 
all: $(libraries) $(large)

$(large) $(libraries):
		$(MAKE) --directory=$@ $(TARGET)
		
$(large): $(libraries)
	
clean:
	cd $(lib_a) && make clean && cd ../../
	cd $(lib_b) && make clean && cd ../../
	cd $(lib_c) && make clean && cd ../../
	cd $(large) && make clean && cd ../../
	rm -rf build/*
	rm -rf bin/*