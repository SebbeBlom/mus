#include <CUnit/Basic.h>
#include <stdlib.h>

#include "../../src/analyzer.h"
#include "../../src/chord_map.h"

void test_Tritone(char *root, char *tritone) {
    HashMap *map = hash_map_create();
    populate_hash_map(map);

    int root_midi = note_to_midi(root);
    int tritone_midi = note_to_midi(tritone);

    int chord_root_position[] = {root_midi, tritone_midi};
    chord_t *chord = chord_analyzer(chord_root_position, 2, map);

    char expected[20];
    char extract_root[3];

    extract_note_name(root, extract_root);
    sprintf(expected, "%s tritone", extract_root);

    if (strcmp(chord->to_string, expected) != 0) {
        puts("");
        puts("");
        printf("Test failed: %s + %s\n", root, tritone);
        printf("Expected: '%s'\n", expected);
        printf("Got:      '%s'", chord->to_string);
        CU_FAIL("Chord analysis failed");
    }
}

void test_C_tritone(void) { test_Tritone("C3", "F#3"); }
void test_Cs_tritone(void) { test_Tritone("C#3", "G3"); }
void test_D_tritone(void) { test_Tritone("D3", "G#3"); }
void test_Ds_tritone(void) { test_Tritone("D#3", "A3"); }
void test_E_tritone(void) { test_Tritone("E3", "A#3"); }
void test_F_tritone(void) { test_Tritone("F3", "B3"); }
void test_Fs_tritone(void) { test_Tritone("F#3", "C4"); }
void test_G_tritone(void) { test_Tritone("G3", "C#4"); }
void test_Gs_tritone(void) { test_Tritone("G#3", "D4"); }
void test_A_tritone(void) { test_Tritone("A3", "D#4"); }
void test_As_tritone(void) { test_Tritone("A#3", "E4"); }
void test_B_tritone(void) { test_Tritone("B3", "F4"); }

int main() {
    CU_initialize_registry();

    CU_pSuite pSuite = CU_add_suite("Tritone Intervalls Test Suite", 0, 0);

    CU_add_test(pSuite, "C tritone", test_C_tritone);
    CU_add_test(pSuite, "C# tritone", test_Cs_tritone);
    CU_add_test(pSuite, "D tritone", test_D_tritone);
    CU_add_test(pSuite, "D# tritone", test_Ds_tritone);
    CU_add_test(pSuite, "E tritone", test_E_tritone);
    CU_add_test(pSuite, "F tritone", test_F_tritone);
    CU_add_test(pSuite, "F# tritone", test_Fs_tritone);
    CU_add_test(pSuite, "G tritone", test_G_tritone);
    CU_add_test(pSuite, "G# tritone", test_Gs_tritone);
    CU_add_test(pSuite, "A tritone", test_A_tritone);
    CU_add_test(pSuite, "A# tritone", test_As_tritone);
    CU_add_test(pSuite, "B tritone", test_B_tritone);

    CU_basic_run_tests();

    CU_cleanup_registry();

    return 0;
}
