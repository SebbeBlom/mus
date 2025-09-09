#define NOB_IMPLEMENTATION
#include "include/nob.h"

#define CC "gcc"
#define CFLAGS "-Wall", "-Wextra", "-pedantic", "-g"
#define LDFLAGS "-lm", "-g"
#define CUNIT "-lcunit"
#define RAYLIB "-lraylib", "-lm"

#define SRC_DIR "src"
#define BIN_DIR "bin"
#define OBJ_DIR "obj"
#define TEST_2_NOTE_DIR "test/2_note_chords"
#define TEST_3_NOTE_DIR "test/3_note_chords"
#define TEST_4_NOTE_DIR "test/4_note_chords"
#define TEST_5_NOTE_DIR "test/5_note_chords"
#define TEST_6_NOTE_DIR "test/6_note_chords"
#define TEST_7_NOTE_DIR "test/7_note_chords"
#define TEST_ANALYZER_DIR "test/analyzer_test"

bool build_object_file(const char *src_file, const char *obj_file) {
    if (nob_needs_rebuild1(obj_file, src_file)) {
        Nob_Cmd cmd = {0};
        nob_cmd_append(&cmd, CC, CFLAGS, "-c", src_file, "-o", obj_file);
        if (!nob_cmd_run(&cmd)) return false;
    }
    return true;
}

bool build_core_objects() {
    if (!nob_mkdir_if_not_exists(OBJ_DIR)) return false;

    if (!build_object_file(SRC_DIR "/chord_map.c", OBJ_DIR "/chord_map.o"))
        return false;
    if (!build_object_file(SRC_DIR "/analyzer.c", OBJ_DIR "/analyzer.o"))
        return false;

    return true;
}

bool build_main_executable() {
    if (!nob_mkdir_if_not_exists(BIN_DIR)) return false;

    const char *deps[] = {SRC_DIR "/mus.c", OBJ_DIR "/chord_map.o",
                          OBJ_DIR "/analyzer.o"};

    if (nob_needs_rebuild(BIN_DIR "/piano", deps, NOB_ARRAY_LEN(deps))) {
        Nob_Cmd cmd = {0};
        nob_cmd_append(&cmd, CC, CFLAGS);
        for (size_t i = 0; i < NOB_ARRAY_LEN(deps); ++i) {
            nob_cmd_append(&cmd, deps[i]);
        }
        nob_cmd_append(&cmd, "-o", BIN_DIR "/piano", RAYLIB);
        if (!nob_cmd_run(&cmd)) return false;
    }

    return true;
}

bool build_test_executable(const char *test_file, const char *output_name) {
    if (!nob_mkdir_if_not_exists(BIN_DIR)) return false;

    const char *deps[] = {test_file, OBJ_DIR "/chord_map.o",
                          OBJ_DIR "/analyzer.o"};

    const char *output_path = nob_temp_sprintf(BIN_DIR "/%s", output_name);

    if (nob_needs_rebuild(output_path, deps, NOB_ARRAY_LEN(deps))) {
        Nob_Cmd cmd = {0};
        nob_cmd_append(&cmd, CC, CFLAGS);
        for (size_t i = 0; i < NOB_ARRAY_LEN(deps); ++i) {
            nob_cmd_append(&cmd, deps[i]);
        }
        nob_cmd_append(&cmd, CUNIT, "-o", output_path);
        if (!nob_cmd_run(&cmd)) return false;
    }

    return true;
}

bool build_tests_in_directory(const char *test_dir) {
    Nob_File_Paths test_files = {0};
    if (!nob_read_entire_dir(test_dir, &test_files)) return false;

    bool result = true;
    for (size_t i = 0; i < test_files.count; ++i) {
        const char *file = test_files.items[i];
        if (!nob_sv_end_with(nob_sv_from_cstr(file), ".c")) continue;

        const char *test_path = nob_temp_sprintf("%s/%s", test_dir, file);
        const char *test_name = nob_temp_sprintf(
            "%.*s", (int)(strlen(file) - 2), file);  // Remove .c extension

        if (!build_test_executable(test_path, test_name)) {
            result = false;
            break;
        }
    }

    nob_da_free(test_files);
    return result;
}

bool run_tests_in_directory(const char *test_dir) {
    Nob_File_Paths test_files = {0};
    if (!nob_read_entire_dir(test_dir, &test_files)) return false;

    bool result = true;
    for (size_t i = 0; i < test_files.count; ++i) {
        const char *file = test_files.items[i];
        if (!nob_sv_end_with(nob_sv_from_cstr(file), ".c")) continue;

        const char *test_name =
            nob_temp_sprintf("%.*s", (int)(strlen(file) - 2), file);
        const char *test_binary = nob_temp_sprintf(BIN_DIR "/%s", test_name);

        nob_log(NOB_INFO, "Running %s...", test_binary);
        Nob_Cmd cmd = {0};
        nob_cmd_append(&cmd, test_binary);
        if (!nob_cmd_run(&cmd)) {
            result = false;
            break;
        }
    }

    nob_da_free(test_files);
    return result;
}

bool clean() {
    nob_log(NOB_INFO, "Cleaning up...");

    // Remove directories recursively
    if (nob_file_exists(OBJ_DIR)) {
        Nob_Cmd cmd = {0};
        nob_cmd_append(&cmd, "rm", "-rf", OBJ_DIR);
        if (!nob_cmd_run(&cmd)) return false;
    }

    if (nob_file_exists(BIN_DIR)) {
        Nob_Cmd cmd = {0};
        nob_cmd_append(&cmd, "rm", "-rf", BIN_DIR);
        if (!nob_cmd_run(&cmd)) return false;
    }

    return true;
}

void usage(const char *program) {
    nob_log(NOB_INFO, "Usage: %s [SUBCOMMAND]", program);
    nob_log(NOB_INFO, "  SUBCOMMANDS:");
    nob_log(NOB_INFO, "    mus                    - Build main executable");
    nob_log(NOB_INFO,
            "    2_note_chord_tests     - Build and run 2-note chord tests");
    nob_log(NOB_INFO,
            "    3_note_chord_tests     - Build and run 3-note chord tests");
    nob_log(NOB_INFO,
            "    4_note_chord_tests     - Build and run 4-note chord tests");
    nob_log(NOB_INFO,
            "    5_note_chord_tests     - Build and run 5-note chord tests");
    nob_log(NOB_INFO,
            "    6_note_chord_tests     - Build and run 6-note chord tests");
    nob_log(NOB_INFO,
            "    7_note_chord_tests     - Build and run 7-note chord tests");
    nob_log(NOB_INFO,
            "    analyzer_tests         - Build and run analyzer tests");
    nob_log(NOB_INFO, "    all                    - Build everything");
    nob_log(NOB_INFO, "    clean                  - Clean build artifacts");
}

int main(int argc, char **argv) {
    NOB_GO_REBUILD_URSELF(argc, argv);

    const char *program = nob_shift(argv, argc);

    if (argc == 0) {
        usage(program);
        return 1;
    }

    const char *subcommand = nob_shift(argv, argc);

    // Build core objects first for most commands
    if (strcmp(subcommand, "clean") != 0) {
        if (!build_core_objects()) return 1;
    }

    if (strcmp(subcommand, "mus") == 0) {
        if (!build_main_executable()) return 1;
    } else if (strcmp(subcommand, "2_note_chord_tests") == 0) {
        if (!build_tests_in_directory(TEST_2_NOTE_DIR)) return 1;
        if (!run_tests_in_directory(TEST_2_NOTE_DIR)) return 1;
    } else if (strcmp(subcommand, "3_note_chord_tests") == 0) {
        if (!build_tests_in_directory(TEST_3_NOTE_DIR)) return 1;
        if (!run_tests_in_directory(TEST_3_NOTE_DIR)) return 1;
    } else if (strcmp(subcommand, "4_note_chord_tests") == 0) {
        if (!build_tests_in_directory(TEST_4_NOTE_DIR)) return 1;
        if (!run_tests_in_directory(TEST_4_NOTE_DIR)) return 1;
    } else if (strcmp(subcommand, "5_note_chord_tests") == 0) {
        if (!build_tests_in_directory(TEST_5_NOTE_DIR)) return 1;
        if (!run_tests_in_directory(TEST_5_NOTE_DIR)) return 1;
    } else if (strcmp(subcommand, "6_note_chord_tests") == 0) {
        if (!build_tests_in_directory(TEST_6_NOTE_DIR)) return 1;
        if (!run_tests_in_directory(TEST_6_NOTE_DIR)) return 1;
    } else if (strcmp(subcommand, "7_note_chord_tests") == 0) {
        if (!build_tests_in_directory(TEST_7_NOTE_DIR)) return 1;
        if (!run_tests_in_directory(TEST_7_NOTE_DIR)) return 1;
    } else if (strcmp(subcommand, "analyzer_tests") == 0) {
        if (!build_tests_in_directory(TEST_ANALYZER_DIR)) return 1;
        if (!run_tests_in_directory(TEST_ANALYZER_DIR)) return 1;
    } else if (strcmp(subcommand, "all") == 0) {
        if (!build_main_executable()) return 1;
        if (!build_tests_in_directory(TEST_2_NOTE_DIR)) return 1;
        if (!build_tests_in_directory(TEST_3_NOTE_DIR)) return 1;
        if (!build_tests_in_directory(TEST_4_NOTE_DIR)) return 1;
        if (!build_tests_in_directory(TEST_5_NOTE_DIR)) return 1;
        if (!build_tests_in_directory(TEST_6_NOTE_DIR)) return 1;
        if (!build_tests_in_directory(TEST_7_NOTE_DIR)) return 1;
        if (!build_tests_in_directory(TEST_ANALYZER_DIR)) return 1;
        nob_log(NOB_INFO, "Build completed successfully!");
    } else if (strcmp(subcommand, "clean") == 0) {
        if (!clean()) return 1;
    } else {
        nob_log(NOB_ERROR, "Unknown subcommand: %s", subcommand);
        usage(program);
        return 1;
    }

    return 0;
}