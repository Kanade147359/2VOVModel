CXX       := g++
CXXFLAGS  := -std=c++17 -Iinclude -O2
SRCS      := src/Vec2.cpp src/Model.cpp src/main.cpp
OBJS      := $(SRCS:.cpp=.o)
TARGET    := ov2d
PYTHON    := uv run
GIF       := animation.gif
CSV       := positions.csv
PY_SCRIPT := make_gif.py

.PHONY: all clean

$(GIF): $(CSV) $(PY_SCRIPT)
	uv run $(PY_SCRIPT)

$(CSV): $(TARGET)
	./$(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) $(GIF) $(CSV)