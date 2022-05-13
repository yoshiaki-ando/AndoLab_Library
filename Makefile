OBJS_VECTOR_GAUSS_QUADRATURE = vector_gauss_quadrature.o gauss_quadrature.o
HEADERS = Command.h Vector3d.h gauss_quadrature.h memory_allocate.h physical_constants.h vector_gauss_quadrature.h
OBJS = $(OBJS_VECTOR_GAUSS_QUADRATURE) Command.o
OPTS = -O3 -Wall -fPIC
INC = -I.
INSTALL_TOP_DIR = $(HOME)

SUFFIX = _20

TARGET = libAndoLab$(SUFFIX).so

all: $(TARGET)

.PHONY: all clean install

$(TARGET): $(OBJS)
	g++ -shared -o $@ $(OBJS)

%.o: %.cpp
	g++ -c $< $(OPTS) $(INC)

gauss_quadrature.o: gauss_quadrature.h
vector_gauss_quadrature.o: vector_gauss_quadrature.h

clean:
	rm -rf *.o $(TARGET)

## Install
INSTALL_LIB_DIR = $(INSTALL_TOP_DIR)/lib
INSTALL_INC_DIR = $(INSTALL_TOP_DIR)/include
install: all
	@if [ ! -d $(INSTALL_LIB_DIR) ]; then \
		mkdir $(INSTALL_LIB_DIR); \
	fi
	cp $(TARGET) $(INSTALL_LIB_DIR)
	@if [ ! -d $(INSTALL_INC_DIR) ]; then \
		mkdir $(INSTALL_INC_DIR); \
	fi
	cp $(HEADERS) $(INSTALL_INC_DIR)

