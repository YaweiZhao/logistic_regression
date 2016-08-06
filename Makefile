EXE=logistic_regression
CXX=g++
SRC=$(wildcard *.cpp)
OBJ=$(SRC:.cpp=.o)
HEADERS=$(wildcard *.hpp)
CXXFLAGS=-std=c++11 \
         -O2 \
         -larmadillo

$(EXE): $(OBJ)
	$(CXX) $(OBJ) $(CXXFLAGS) -o $@
clean:
	@rm $(EXE) $(OBJ) .depend -f
