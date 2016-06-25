CC = llvm-g++
CPP_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))
LD_FLAGS := 
CC_FLAGS := -Wall -std=c++11 -pedantic -O3 #(optimierung) # -g (for debugging)

TEST_OBJ := obj/Ion.o obj/IonSource.o obj/Device.o obj/Accelerator.o obj/DriftTube.o obj/QuadrupoleMagnet.o \
obj/Trafo.o obj/DipoleMagnet.o obj/Screen.o obj/ProfileGrid.o obj/Slit.o obj/HKick.o \
obj/Server.o 

MAIN_MAIN_OBJ := obj/main.o
TEST_MAIN_OBJ := obj/test.o

all: main
	@echo "done"

main: $(TEST_OBJ) $(MAIN_MAIN_OBJ)
	$(CC) $(LD_FLAGS) -o $@ $^
	
test: $(TEST_OBJ) $(TEST_MAIN_OBJ)
	$(CC) $(LD_FLAGS) -o $@ $^	

obj/%.o: src/%.cpp src/%.hpp
	$(CC) $(CC_FLAGS) -c -o $@ $<

clean:
	@rm -f obj/*.o *.exe main *.stackdump
	@echo project cleaned

