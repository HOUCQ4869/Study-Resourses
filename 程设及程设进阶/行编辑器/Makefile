OBJ     = src/minied.o src/line.o src/editor.o
CC      = gcc
SYSTEM ?= WIN

ifeq ($(SYSTEM), WIN)
	BIN     := .\src\minied.exe
else ifeq ($(SYSTEM), MAC)
	BIN     := ./src/minied 
endif

$(BIN): $(OBJ)
	$(CC) -o $(BIN) $(OBJ)

run: $(BIN)
	$(BIN)

$(OBJ): %.o: %.c 
	$(CC) -c $< -o $@ -std=c11

.PHONY: clean run
