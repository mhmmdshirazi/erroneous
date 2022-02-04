BUILD := build
INC := Inc
SRC := Src

TARGET := Connecterra
SRCFILES := $(shell find $(SRC) -type f -name "*.cpp" )
OBJ := $(patsubst %, $(BUILD)/%, $(notdir $(SRCFILES:.cpp=.o)))
CFLAGS := -Wall -I$(INC)
CC:= g++ -std=c++11

$(BUILD)/$(TARGET) : $(OBJ)
	$(CC) -o $(TARGET) $(OBJ)

$(BUILD)/%.o : $(SRC)/%.cpp
	@mkdir -p $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -rf build