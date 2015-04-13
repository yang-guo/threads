ifeq ($(wildcard ./config.mk),)
$(error run ./configure first)
endif
include ./config.mk

TARGETS 	   := threads threadpool
OUTPUT 		   := threads.so
LIBFILES	   := pthread

OBJECTS = $(foreach TARGET,$(TARGETS),$(TARGET).o)
LIBS = $(foreach LIB,$(LIBFILES),-l$(LIB))

all: build

######################################
# DEFAULT COMPILATIONS
######################################
# default compilation commands
# Created depends as .d so that we have automated detection of changes in header files
%.o: %.cpp
	$(CXX) $(INCLUDES) $(CFLAGS) $(FLAGS) -c $< -o $@
	$(CXX) $(INCLUDES) $(CFLAGS) $(FLAGS) -MM $< > $*.d
	@cp -f $*.d $*.d.tmp
	@sed -e 's/.*://' -e 's/\\$$//' < $*.d.tmp | fmt -1 | \
	  sed -e 's/^ *//' -e 's/$$/:/' >> $*.d
	@rm -f $*.d.tmp
%.o: %.c
	$(CC) $(INCLUDES) $(CFLAGS) $(FLAGS) -c $< -o $@
	$(CC) $(INCLUDES) $(CFLAGS) $(FLAGS) -MM $< > $*.d
	@cp -f $*.d $*.d.tmp
	@sed -e 's/.*://' -e 's/\\$$//' < $*.d.tmp | fmt -1 | \
	  sed -e 's/^ *//' -e 's/$$/:/' >> $*.d
	@rm -f $*.d.tmp

-include $(OBJECTS:.o=.d)

build: $(OUTPUT)
$(OUTPUT) : $(OBJECTS)
	$(CC) $(INCLUDES) $(CFLAGS) $(FLAGS) $(OBJECTS) $(LIBS) -o $(OUTPUT)

clean:
	rm -f *.o *.so *.d

install: 
	mkdir -p ../$(KXARCH)
	cp $(OUTPUT) ../$(KXARCH)
