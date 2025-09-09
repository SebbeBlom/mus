#define NOB_IMPLEMENTATION
#include "include/nob.h"

#define SRC_DIR "src/"
#define BIN_DIR "bin/"
#define OBJ_DIR "obj/"
int main(int argc, char **argv) {
    NOB_GO_REBUILD_URSELF(argc, argv);
    Nob_Cmd cmd = {0};

    if (!nob_mkdir_if_not_exists(BIN_DIR)) return 1;
    if (!nob_mkdir_if_not_exists(OBJ_DIR)) return 1;

    nob_cmd_append(&cmd, "cc", "-Wall", "-Wextra", "-c", SRC_DIR "chord_map.c",
                   "-o", OBJ_DIR "chord_map.o");
    if (!nob_cmd_run(&cmd)) return 1;

    nob_cmd_append(&cmd, "cc", "-Wall", "-Wextra", "-c", SRC_DIR "analyzer.c",
                   "-o", OBJ_DIR "analyzer.o");
    if (!nob_cmd_run(&cmd)) return 1;

    nob_cmd_append(&cmd, "cc", "-Wall", "-Wextra", SRC_DIR "mus.c",
                   OBJ_DIR "chord_map.o", OBJ_DIR "analyzer.o", "-o",
                   BIN_DIR "piano", "-lraylib", "-lm");
    if (!nob_cmd_run(&cmd)) return 1;

    
    return 0;
}