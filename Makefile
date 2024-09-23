CXX = g++
CXXFLAGS = -std=c++11 

OBJECTS = main.o initial_values.o simulation.o

TMP_DIR = tmp

OBJECTS = $(TMP_DIR)/main.o $(TMP_DIR)/initial_values.o $(TMP_DIR)/simulation.o

TARGET = simulation.out

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

$(TMP_DIR)/main.o: src/main.cpp src/initial_values.hpp src/simulation.hpp | $(TMP_DIR)
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o $(TMP_DIR)/main.o

$(TMP_DIR)/initial_values.o: src/initial_values.cpp src/initial_values.hpp | $(TMP_DIR)
	$(CXX) $(CXXFLAGS) -c src/initial_values.cpp -o $(TMP_DIR)/initial_values.o

$(TMP_DIR)/simulation.o: src/simulation.cpp src/simulation.hpp | $(TMP_DIR)
	$(CXX) $(CXXFLAGS) -c src/simulation.cpp -o $(TMP_DIR)/simulation.o

$(TMP_DIR):
	mkdir -p $(TMP_DIR)

output/positions.csv: $(TARGET)
	./$(TARGET)

gif: output/positions.csv
	poetry install
	poetry run python3 create_gif.py

# クリーンアップルール
.PHONY: clean clear
clean:
	rm -f $(TMP_DIR)/*.o $(TARGET)

clear: clean
	rm -f output/positions.csv output/positions.gif

