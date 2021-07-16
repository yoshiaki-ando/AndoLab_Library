OBJS_VECTOR_GAUSS_QUADRATURE = vector_gauss_quadrature.o
OBJS = $(OBJS_VECTOR_GAUSS_QUADRATURE)
OPTS = -O3 -Wall -fPIC
INC = -I.

all: libAndoLab.so

.PHONY: all clean

libAndoLab.so: $(OBJS)
	g++ -shared -o $@ $(OBJS)

%.o: %.cpp
	g++ -c $< $(OPTS) $(INC)


clean:
	rm -rf *.o libAndoLab.so
