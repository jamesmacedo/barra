CXX = g++
CXXFLAGS = -std=c++17 -Wall
LDFLAGS = -lX11 -lcairo

SRC_DIR = src
BUILD_DIR = build

SRCS = $(wildcard $(SRC_DIR)/*/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/*/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))
TARGET = $(BUILD_DIR)/layout_example

SRC = src/main.cpp

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(OBJS) $(SRC) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@


run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(BUILD_DIR)

