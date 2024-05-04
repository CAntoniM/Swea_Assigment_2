
EXE = Casino
CXX = g++

all: $(EXE)

%: %.cpp
	$(CXX) $< -o $@

clean:
	rm -rf $(EXE)
