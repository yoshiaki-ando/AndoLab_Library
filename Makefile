OBJS_VECTOR_GAUSS_QUADRATURE = vector_gauss_quadrature.o
OBJS = $(OBJS_VECTOR_GAUSS_QUADRATURE)
OPTS = -O3 -Wall -fPIC
INC = -I.
INSTALL_TOP_DIR = $(HOME)

all: libAndoLab.so

.PHONY: all clean install

libAndoLab.so: $(OBJS)
	g++ -shared -o $@ $(OBJS)

%.o: %.cpp
	g++ -c $< $(OPTS) $(INC)


clean:
	rm -rf *.o libAndoLab.so

## Install
INSTALL_LIB_DIR = $(INSTALL_TOP_DIR)/lib
INSTALL_INC_DIR = $(INSTALL_TOP_DIR)/include
install: all
	@if [ ! -d $(INSTALL_LIB_DIR) ]; then \
		mkdir $(INSTALL_LIB_DIR); \
	fi
	cp libAndoLab.so $(INSTALL_LIB_DIR)
	@if [ ! -d $(INSTALL_INC_DIR) ]; then \
		mkdir $(INSTALL_INC_DIR); \
	fi
	cp *.h $(INSTALL_INC_DIR)

