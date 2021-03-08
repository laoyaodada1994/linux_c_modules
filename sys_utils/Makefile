BUILD_DIR = build
BIN_DIR = output
DEST_EXE_NAME = main

all: clean build install
	@cd $(BUILD_DIR);  make -j4

clean:
	@rm $(BUILD_DIR) $(BIN_DIR)  -rf
build:
	@mkdir $(BUILD_DIR); cd $(BUILD_DIR); cmake ..

install:
	@cd $(BUILD_DIR); make install

run:
	@export LD_LIBRARY_PATH=$(PWD)/$(BIN_DIR)/lib/
	@$(BIN_DIR)/bin/$(DEST_EXE_NAME)

test:
	@cd $(BUILD_DIR); make test
