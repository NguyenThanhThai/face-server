BOOST  := /usr/include/boost
THRIFT := /usr/local/include/thrift  

CC=g++
#debug flags
#DEBUG=-o0 -g
DEBUG=
CFLAGS=$(DEBUG) -c -Wall 
LDFLAGS=$(DEBUG)

SRC=src/main/cpp
GEN_THRIFT=build/gen-cpp
INC=-I$(BOOST) -I$(THRIFT)
INC_SRCS=-I$(SRC) -I$(GEN_THRIFT)
LIBS=-lc -lz -lboost_thread -lboost_program_options -lthrift -lthriftnb -levent -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_objdetect



EXE=face-server
OUT=build

THRIFT_SRC=src/main/thrift/service.thrift
OBJECTS:= service_types.o service_constants.o FaceService.o FaceServiceImpl.o server.o 

#$(patsubst %,$(ODIR)/%,$(_OBJS))
OBJS := $(patsubst %,$(OUT)/%,$(OBJECTS))


all: init thrift link update-pfs-client clear-tmps

init:
	mkdir -p $(OUT)
   
link: $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(OUT)/$(EXE) $(INC) $(INC_SRCS) $(LIBS)

#compile sources
#$(CC) -c $(INC) -o $@ $< $(CFLAGS)
$(OUT)/%.o: $(GEN_THRIFT)/%.cpp
	$(CC) $(INC) $(INC_SRCS) -o $@ $< $(CFLAGS)
	

$(OUT)/%.o: $(SRC)/%.cpp			
	$(CC) $(INC) $(INC_SRCS) -o $@ $< $(CFLAGS)

clear-tmps:
	#rm -fr *.o
	#rm -fr *~		
				
clean: 
	rm -fr build

thrift:
	thrift -o $(OUT) --gen js:node $(THRIFT_SRC)
	thrift -o $(OUT) --gen cpp $(THRIFT_SRC)
	thrift -o $(OUT) --gen py $(THRIFT_SRC)

update-pfs-client:
	cp $(OUT)/gen-nodejs/*.js src/pfs-client/lib/
	
.PHONY:    		
	echo "phony"