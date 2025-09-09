CC     	= gcc
CFLAGS  = -Wall -Wextra -pedantic -g
LDFLAGS = -lm -g
CUNIT   = -lcunit
RAYLIB 	= -lraylib -lm 

SRC_DIR = src
BIN_DIR = bin
OBJ_DIR = obj
TEST_2_NOTE_DIR = test/2_note_chords
TEST_3_NOTE_DIR = test/3_note_chords
TEST_4_NOTE_DIR = test/4_note_chords
TEST_5_NOTE_DIR = test/5_note_chords
TEST_6_NOTE_DIR = test/6_note_chords
TEST_7_NOTE_DIR = test/7_note_chords
TEST_ANALYZER_DIR = test/analyzer_test


# Ensure necessary directories exist
$(OBJ_DIR) $(BIN_DIR):
	mkdir -p $@

# Object files for core components
OBJ_FILES = $(OBJ_DIR)/chord_map.o $(OBJ_DIR)/analyzer.o

# Compile object files
$(OBJ_DIR)/chord_map.o: $(SRC_DIR)/chord_map.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $^ -o $@

$(OBJ_DIR)/analyzer.o: $(SRC_DIR)/analyzer.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $^ -o $@

# Build the main executable
mus: $(SRC_DIR)/mus.c $(OBJ_FILES) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $(BIN_DIR)/piano $(RAYLIB)

m_test: test/3_note_chords/m_unit_test.c
	$(CC) $(CFLAGS) $(SRC_DIR)/analyzer.c $(SRC_DIR)/chord_map.c $^ $(CUNIT) -o $(BIN_DIR)/m_test

M_test: test/3_note_chords/M_unit_test.c
	$(CC) $(CFLAGS) $(SRC_DIR)/analyzer.c $(SRC_DIR)/chord_map.c $^ $(CUNIT) -o $(BIN_DIR)/M_test

sus4_test: test/3_note_chords/sus4_unit_test.c
	$(CC) $(CFLAGS) $(SRC_DIR)/analyzer.c $(SRC_DIR)/chord_map.c $^ $(CUNIT) -o $(BIN_DIR)/sus4_test	

aug_test: test/3_note_chords/aug_unit_test.c
	$(CC) $(CFLAGS) $(SRC_DIR)/analyzer.c $(SRC_DIR)/chord_map.c $^ $(CUNIT) -o $(BIN_DIR)/aug_test	

7_test: test/4_note_chords/7_unit_test.c
	$(CC) $(CFLAGS) $(SRC_DIR)/analyzer.c $(SRC_DIR)/chord_map.c $^ $(CUNIT) -o $(BIN_DIR)/7_test	

# Automatically compile unit tests
TESTS_2 = $(wildcard $(TEST_2_NOTE_DIR)/*.c)
TEST_BINARIES_2 = $(patsubst $(TEST_2_NOTE_DIR)/%.c, $(BIN_DIR)/%, $(TESTS_2))

TESTS_3 = $(wildcard $(TEST_3_NOTE_DIR)/*.c)
TEST_BINARIES_3 = $(patsubst $(TEST_3_NOTE_DIR)/%.c, $(BIN_DIR)/%, $(TESTS_3))

TESTS_4 = $(wildcard $(TEST_4_NOTE_DIR)/*.c)
TEST_BINARIES_4 = $(patsubst $(TEST_4_NOTE_DIR)/%.c, $(BIN_DIR)/%, $(TESTS_4))

TESTS_5 = $(wildcard $(TEST_5_NOTE_DIR)/*.c)
TEST_BINARIES_5 = $(patsubst $(TEST_5_NOTE_DIR)/%.c, $(BIN_DIR)/%, $(TESTS_5))

TESTS_6 = $(wildcard $(TEST_6_NOTE_DIR)/*.c)
TEST_BINARIES_6 = $(patsubst $(TEST_6_NOTE_DIR)/%.c, $(BIN_DIR)/%, $(TESTS_6))

TESTS_7 = $(wildcard $(TEST_7_NOTE_DIR)/*.c)
TEST_BINARIES_7 = $(patsubst $(TEST_7_NOTE_DIR)/%.c, $(BIN_DIR)/%, $(TESTS_7))

TESTS_ANALYZER = $(wildcard $(TEST_ANALYZER_DIR)/*.c)
TEST_BINARIES_ANALYZER = $(patsubst $(TEST_ANALYZER_DIR)/%.c, $(BIN_DIR)/%, $(TESTS_ANALYZER))

$(BIN_DIR)/%: $(TEST_2_NOTE_DIR)/%.c $(OBJ_FILES) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ $(CUNIT) -o $@

$(BIN_DIR)/%: $(TEST_3_NOTE_DIR)/%.c $(OBJ_FILES) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ $(CUNIT) -o $@	

$(BIN_DIR)/%: $(TEST_4_NOTE_DIR)/%.c $(OBJ_FILES) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ $(CUNIT) -o $@	

$(BIN_DIR)/%: $(TEST_5_NOTE_DIR)/%.c $(OBJ_FILES) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ $(CUNIT) -o $@	

$(BIN_DIR)/%: $(TEST_6_NOTE_DIR)/%.c $(OBJ_FILES) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ $(CUNIT) -o $@	

$(BIN_DIR)/%: $(TEST_7_NOTE_DIR)/%.c $(OBJ_FILES) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ $(CUNIT) -o $@	

$(BIN_DIR)/%: $(TEST_ANALYZER_DIR)/%.c $(OBJ_FILES) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ $(CUNIT) -o $@	

# Run all tests inside bin/
2_note_chord_tests: $(TEST_BINARIES_2)
	@for test in $(TEST_BINARIES_2); do \
		echo "Running $$test..."; \
		./$$test; \
	done

# Run all tests inside bin/
3_note_chord_tests: $(TEST_BINARIES_3)
	@for test in $(TEST_BINARIES_3); do \
		echo "Running $$test..."; \
		./$$test; \
	done

# Run all tests inside bin/
4_note_chord_tests: $(TEST_BINARIES_4)
	@for test in $(TEST_BINARIES_4); do \
		echo "Running $$test..."; \
		./$$test; \
	done

# Run all tests inside bin/
5_note_chord_tests: $(TEST_BINARIES_5)
	@for test in $(TEST_BINARIES_5); do \
		echo "Running $$test..."; \
		./$$test; \
	done

# Run all tests inside bin/
6_note_chord_tests: $(TEST_BINARIES_6)
	@for test in $(TEST_BINARIES_6); do \
		echo "Running $$test..."; \
		./$$test; \
	done

# Run all tests inside bin/
7_note_chord_tests: $(TEST_BINARIES_7)
	@for test in $(TEST_BINARIES_7); do \
		echo "Running $$test..."; \
		./$$test; \
	done

# Run all tests inside bin/
analyzer_tests: $(TEST_BINARIES_ANALYZER)
	@for test in $(TEST_BINARIES_ANALYZER); do \
		echo "Running $$test..."; \
		./$$test; \
	done

all: chord_map analyzer mus

# Clean up generated files
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
