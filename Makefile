CC=g++
CCFLAGS=-Wall
PROGRAM_NAME=boost_server
OBJECT_FILES=*.o
SOURCE_FILES=*cpp Source_files/*.cpp
CLEAN= rm -f
LIBS=-lboost_filesystem -lboost_date_time -lboost_system -lboost_regex -lboost_serialization -lboost_thread -lpthread
$(PROGRAM_NAME): $(OBJECT_FILES)
	$(CC) $(CCFLAGS) $(LIBS) -o $@ $^

$(OBJECT_FILES) : $(SOURCE_FILES)
	$(CC) $(CCFLAGS) -c $^

clean:
	$(CLEAN) *.o $(PROGRAM_NAME)

