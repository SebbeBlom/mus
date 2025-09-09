#include "chord_map.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool array_equals(int *arr1, int len1, int *arr2, int len2) {
    if (len1 != len2) {
        return false;
    }

    for (int i = 0; i < len1; i++) {
        if (arr1[i] != arr2[i]) {
            return false;
        }
    }

    return true;  
}

// Create a new hash map
HashMap *hash_map_create() {
    HashMap *map = (HashMap *)malloc(sizeof(HashMap));
    if (map) {
        for (int i = 0; i < TABLE_SIZE; i++) {
            map->buckets[i] = NULL;
        }
    }
    return map;
}

// Insert into hash map
void hash_map_insert(HashMap *map, int *relations, int length, chord_t *chord) {
    int key = hash_array(relations, length);
    int index = key % TABLE_SIZE;
    HashNode *current = map->buckets[index];

    while (current) {
        if (current->key == key &&
            array_equals(current->chord->relations,
                         current->chord->relations_length, relations, length)) {
            current->chord = chord;  
            return;
        }
        current = current->next;
    }

    HashNode *newNode = (HashNode *)malloc(sizeof(HashNode));
    newNode->key = key;
    newNode->chord = chord;
    newNode->next = map->buckets[index];
    map->buckets[index] = newNode;
}

// Lookup a chord
chord_t *hash_map_lookup(HashMap *map, int *relations, int length) {
    int key = hash_array(relations, length);
    int index = key % TABLE_SIZE;
    HashNode *current = map->buckets[index];
    while (current) {
        if (current->key == key &&
            array_equals(current->chord->relations,
                         current->chord->relations_length, relations, length)) {
            return current->chord;
        }
        current = current->next;
    }
    return NULL;
}

int hash_array(int *arr, int length) {
    int hash = 5381;
    for (int i = 0; i < length; i++) {
        hash = ((hash << 5) + hash) + arr[i];
    }
    return abs(hash);
}

chord_t *chord_create(int root_index, char *quality, int *relations,
                      int relations_length) {
    chord_t *chord = calloc(1, sizeof(chord_t));
    chord->root_index = root_index;
    chord->quality = strdup(quality); 
    chord->relations = malloc(relations_length * sizeof(int));
    memcpy(chord->relations, relations,
           relations_length * sizeof(int));
    chord->relations_length = relations_length;
    return chord;
}

void chord_destroy(chord_t *chord) {
    if (chord) {
        free(chord->quality);
        free(chord->relations);
        free(chord);
    }
}

void hash_map_destroy(HashMap *map) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        HashNode *current = map->buckets[i];
        while (current) {
            HashNode *temp = current;
            chord_destroy(current->chord);
            current = current->next;
            free(temp);
        }
    }
    free(map);
}

int extract_note_name(char *note, char *note_name) {
    int i = 0;

    while (note[i] && !(note[i] >= '0' && note[i] <= '9')) {
        note_name[i] = note[i];
        i++;
    }
    note_name[i] = '\0'; 

    return atoi(&note[i]);
}

int note_to_midi(char *note) {
    const char *notes[] = {
        "C", "C#", "D", "D#", "E", "F",
        "F#", "G", "G#", "A", "A#", "B"
    };

    char note_name[3] = {0};
    int octave = extract_note_name(note, note_name);

    int note_index = -1;
    for (int j = 0; j < 12; j++) {
        if (strcmp(note_name, notes[j]) == 0) {
            note_index = j;
            break;
        }
    }

    if (note_index == -1) {
        printf("Invalid note: %s\n", note);
        return -1;
    }

    return ((octave + 1) * 12) + note_index;
}


void add_two_note_chords(HashMap *map) {
    int m2[] = {1};
    chord_t *m2_chord = chord_create(0, strdup(" minor 2nd"), m2, 1);
    hash_map_insert(map, m2, 1, m2_chord);

    int M2[] = {2};
    chord_t *M2_chord = chord_create(0, strdup(" major 2nd"), M2, 1);
    hash_map_insert(map, M2, 1, M2_chord);

    int m3[] = {3};
    chord_t *m3_chord = chord_create(0, strdup(" minor 3rd"), m3, 1);
    hash_map_insert(map, m3, 1, m3_chord);

    int M3[] = {4};
    chord_t *M3_chord = chord_create(0, strdup(" major 3rd"), M3, 1);
    hash_map_insert(map, M3, 1, M3_chord);

    int P4[] = {5};
    chord_t *P4_chord = chord_create(0, strdup(" perfect 4th"), P4, 1);
    hash_map_insert(map, P4, 1, P4_chord);

    int Tritone[] = {6};
    chord_t *Tritone_chord = chord_create(0, strdup(" tritone"), Tritone, 1);
    hash_map_insert(map, Tritone, 1, Tritone_chord);

    int P5[] = {7};
    chord_t *P5_chord = chord_create(0, strdup(" perfect 5th"), P5, 1);
    hash_map_insert(map, P5, 1, P5_chord);

    int m6[] = {8};
    chord_t *m6_chord = chord_create(0, strdup(" minor 6th"), m6, 1);
    hash_map_insert(map, m6, 1, m6_chord);

    int M6[] = {9};
    chord_t *M6_chord = chord_create(0, strdup(" major 6th"), M6, 1);
    hash_map_insert(map, M6, 1, M6_chord);

    int m7[] = {10};
    chord_t *m7_chord = chord_create(0, strdup(" minor 7th"), m7, 1);
    hash_map_insert(map, m7, 1, m7_chord);

    int M7[] = {11};
    chord_t *M7_chord = chord_create(0, strdup(" major 7th"), M7, 1);
    hash_map_insert(map, M7, 1, M7_chord);

    int P8[] = {12};
    chord_t *P8_chord = chord_create(0, strdup(" octave"), P8, 1);
    hash_map_insert(map, P8, 1, P8_chord);
}

void add_three_note_chords(HashMap *map) {
    // major (M)
    int M_root[] = {4, 3};
    chord_t *M_root_chord = chord_create(0, strdup(""), M_root, 2);
    hash_map_insert(map, M_root, 2, M_root_chord);

    int M_1st[] = {3, 5};
    chord_t *M_1st_chord = chord_create(2, strdup(""), M_1st, 2);
    hash_map_insert(map, M_1st, 2, M_1st_chord);

    int M_2nd[] = {5, 4};
    chord_t *M_2nd_chord = chord_create(1, strdup(""), M_2nd, 2);
    hash_map_insert(map, M_2nd, 2, M_2nd_chord);

    // minor (m)
    int m_root[] = {3, 4};
    chord_t *m_root_chord = chord_create(0, strdup("m"), m_root, 2);
    hash_map_insert(map, m_root, 2, m_root_chord);

    int m_1st[] = {4, 5};
    chord_t *m_1st_chord = chord_create(2, strdup("m"), m_1st, 2);
    hash_map_insert(map, m_1st, 2, m_1st_chord);

    int m_2nd[] = {5, 3};
    chord_t *m_2nd_chord = chord_create(1, strdup("m"), m_2nd, 2);
    hash_map_insert(map, m_2nd, 2, m_2nd_chord);

    // Diminished (dim)
    int dim_root[] = {3, 3};
    chord_t *dim_root_chord = chord_create(0, strdup("dim"), dim_root, 2);
    hash_map_insert(map, dim_root, 2, dim_root_chord);

    int dim_1st[] = {3, 6};
    chord_t *dim_1st_chord = chord_create(2, strdup("dim"), dim_1st, 2);
    hash_map_insert(map, dim_1st, 2, dim_1st_chord);

    int dim_2nd[] = {6, 3};
    chord_t *dim_2nd_chord = chord_create(1, strdup("dim"), dim_2nd, 2);
    hash_map_insert(map, dim_2nd, 2, dim_2nd_chord);

    // Augmented (aug)
    int aug_root[] = {4, 4};
    chord_t *aug_root_chord = chord_create(0, strdup("aug"), aug_root, 2);
    hash_map_insert(map, aug_root, 2, aug_root_chord);

    // Suspended 4th (sus4)
    int sus4_root[] = {5, 2};
    chord_t *sus4_root_chord = chord_create(0, strdup("sus4"), sus4_root, 2);
    hash_map_insert(map, sus4_root, 2, sus4_root_chord);
}

void add_four_note_chords(HashMap *map) {
    // Major 7 (M7)
    int M7_root[] = {4, 3, 4};
    chord_t *M7_root_chord = chord_create(0, strdup("maj7"), M7_root, 3);
    hash_map_insert(map, M7_root, 3, M7_root_chord);

    int M7_1st[] = {3, 4, 1};
    chord_t *M7_1st_chord = chord_create(2, strdup("maj7"), M7_1st, 3);
    hash_map_insert(map, M7_1st, 3, M7_1st_chord);

    int M7_2nd[] = {4, 1, 4};
    chord_t *M7_2nd_chord = chord_create(1, strdup("maj7"), M7_2nd, 3);
    hash_map_insert(map, M7_2nd, 3, M7_2nd_chord);

    int M7_3rd[] = {1, 4, 3};
    chord_t *M7_3rd_chord = chord_create(3, strdup("maj7"), M7_3rd, 3);
    hash_map_insert(map, M7_3rd, 3, M7_3rd_chord);

    // Minor 7 (m7)
    int m7_root[] = {3, 4, 3};
    chord_t *m7_root_chord = chord_create(0, strdup("m7"), m7_root, 3);
    hash_map_insert(map, m7_root, 3, m7_root_chord);

    int m7_1st[] = {4, 3, 2};
    chord_t *m7_1st_chord = chord_create(2, strdup("m7"), m7_1st, 3);
    hash_map_insert(map, m7_1st, 3, m7_1st_chord);

    int m7_2nd[] = {3, 2, 4};
    chord_t *m7_2nd_chord = chord_create(1, strdup("m7"), m7_2nd, 3);
    hash_map_insert(map, m7_2nd, 3, m7_2nd_chord);

    int m7_3rd[] = {2, 4, 3};
    chord_t *m7_3rd_chord = chord_create(3, strdup("m7"), m7_3rd, 3);
    hash_map_insert(map, m7_3rd, 3, m7_3rd_chord);

    // Dominant 7 (7)
    int dom7_root[] = {4, 3, 3};
    chord_t *dom7_root_chord = chord_create(0, strdup("7"), dom7_root, 3);
    hash_map_insert(map, dom7_root, 3, dom7_root_chord);

    int dom7_1st[] = {3, 3, 2};
    chord_t *dom7_1st_chord = chord_create(3, strdup("7"), dom7_1st, 3);
    hash_map_insert(map, dom7_1st, 3, dom7_1st_chord);

    int dom7_2nd[] = {3, 2, 4};
    chord_t *dom7_2nd_chord = chord_create(2, strdup("7"), dom7_2nd, 3);
    hash_map_insert(map, dom7_2nd, 3, dom7_2nd_chord);

    int dom7_3rd[] = {2, 4, 3};
    chord_t *dom7_3rd_chord = chord_create(1, strdup("7"), dom7_3rd, 3);
    hash_map_insert(map, dom7_3rd, 3, dom7_3rd_chord);

    // Minor Major 7 (mM7)
    int mM7_root[] = {3, 4, 4};
    chord_t *mM7_root_chord =
        chord_create(0, strdup("mM7"), mM7_root, 3);
    hash_map_insert(map, mM7_root, 3, mM7_root_chord);

    int mM7_1st[] = {4, 4, 1};
    chord_t *mM7_1st_chord =
        chord_create(2, strdup("mM7"), mM7_1st, 3);
    hash_map_insert(map, mM7_1st, 3, mM7_1st_chord);

    int mM7_2nd[] = {4, 1, 3};
    chord_t *mM7_2nd_chord =
        chord_create(1, strdup("mM7"), mM7_2nd, 3);
    hash_map_insert(map, mM7_2nd, 3, mM7_2nd_chord);

    int mM7_3rd[] = {1, 3, 4};
    chord_t *mM7_3rd_chord =
        chord_create(3, strdup("mM7"), mM7_3rd, 3);
    hash_map_insert(map, mM7_3rd, 3, mM7_3rd_chord);

    // Diminished 7th (dim7)
    int dim7_root[] = {3, 3, 3};
    chord_t *dim7_root_chord = chord_create(0, strdup("dim7"), dim7_root, 3);
    hash_map_insert(map, dim7_root, 3, dim7_root_chord);

    int dim7_1st[] = {3, 3, 6};
    chord_t *dim7_1st_chord = chord_create(2, strdup("dim7"), dim7_1st, 3);
    hash_map_insert(map, dim7_1st, 3, dim7_1st_chord);

    int dim7_2nd[] = {3, 6, 3};
    chord_t *dim7_2nd_chord = chord_create(1, strdup("dim7"), dim7_2nd, 3);
    hash_map_insert(map, dim7_2nd, 3, dim7_2nd_chord);

    int dim7_3rd[] = {6, 3, 3};
    chord_t *dim7_3rd_chord = chord_create(3, strdup("dim7"), dim7_3rd, 3);
    hash_map_insert(map, dim7_3rd, 3, dim7_3rd_chord);

    // Augmented 7th (aug7)
    int aug7_root[] = {4, 4, 2};
    chord_t *aug7_root_chord = chord_create(0, strdup("aug7"), aug7_root, 3);
    hash_map_insert(map, aug7_root, 3, aug7_root_chord);

    int aug7_1st[] = {4, 2, 4};
    chord_t *aug7_1st_chord = chord_create(3, strdup("aug7"), aug7_1st, 3);
    hash_map_insert(map, aug7_1st, 3, aug7_1st_chord);

    int aug7_2nd[] = {2, 4, 4};
    chord_t *aug7_2nd_chord = chord_create(2, strdup("aug7"), aug7_2nd, 3);
    hash_map_insert(map, aug7_2nd, 3, aug7_2nd_chord);

    int aug7_3rd[] = {4, 4, 2};
    chord_t *aug7_3rd_chord = chord_create(1, strdup("aug7"), aug7_3rd, 3);
    hash_map_insert(map, aug7_3rd, 3, aug7_3rd_chord);

    // Dominant 7th Suspended 4th (dom7sus4)
    int dom7sus4_root[] = {5, 2, 3};
    chord_t *dom7sus4_root_chord =
        chord_create(0, strdup("7sus4"), dom7sus4_root, 3);
    hash_map_insert(map, dom7sus4_root, 3, dom7sus4_root_chord);

    // Add9 (add9)
    int add9_root[] = {4, 3, 5};
    chord_t *add9_root_chord = chord_create(0, strdup("add9"), add9_root, 3);
    hash_map_insert(map, add9_root, 3, add9_root_chord);

    int add9_1st[] = {3, 5, 4};
    chord_t *add9_1st_chord = chord_create(2, strdup("add9"), add9_1st, 3);
    hash_map_insert(map, add9_1st, 3, add9_1st_chord);

    int add9_2nd[] = {5, 4, 3};
    chord_t *add9_2nd_chord = chord_create(1, strdup("add9"), add9_2nd, 3);
    hash_map_insert(map, add9_2nd, 3, add9_2nd_chord);

    int add9_3rd[] = {4, 3, 5};
    chord_t *add9_3rd_chord = chord_create(3, strdup("add9"), add9_3rd, 3);
    hash_map_insert(map, add9_3rd, 3, add9_3rd_chord);

    // Minor 7♭5 (m7♭5) - Half-diminished
    int m7b5_root[] = {3, 3, 4};
    chord_t *m7b5_chord = chord_create(0, strdup("m7b5"), m7b5_root, 3);
    hash_map_insert(map, m7b5_root, 3, m7b5_chord);

    // Dominant 7♭5 (7♭5)
    int seven_b5_root[] = {4, 2, 6};
    chord_t *seven_b5_chord = chord_create(0, strdup("7b5"), seven_b5_root, 3);
    hash_map_insert(map, seven_b5_root, 3, seven_b5_chord);
}

void add_five_note_chords(HashMap *map) {
    // Dominant 7♭9 (7♭9)
    int seven_b9_root[] = {4, 3, 3, 2};
    chord_t *seven_b9_chord = chord_create(0, strdup("7b9"), seven_b9_root, 4);
    hash_map_insert(map, seven_b9_root, 4, seven_b9_chord);

    // Dominant 7♯9 (7♯9)
    int seven_sharp9_root[] = {4, 3, 3, 4};
    chord_t *seven_sharp9_chord =
        chord_create(0, strdup("7#9"), seven_sharp9_root, 4);
    hash_map_insert(map, seven_sharp9_root, 4, seven_sharp9_chord);

    // Dominant 9 (9)
    int nine_root[] = {4, 3, 3, 4};
    chord_t *nine_chord = chord_create(0, strdup("9"), nine_root, 4);
    hash_map_insert(map, nine_root, 4, nine_chord);

    // Minor 9 (m9)
    int m9_root[] = {3, 4, 3, 4};
    // printf("m9: %d\n", m9);
    chord_t *m9_chord = chord_create(0, strdup("m9"), m9_root, 4);
    hash_map_insert(map, m9_root, 4, m9_chord);

    // Major 9 (M9)
    int M9_root[] = {4, 3, 4, 4};
    chord_t *M9_chord = chord_create(0, strdup("maj9"), M9_root, 4);
    hash_map_insert(map, M9_root, 4, M9_chord);

    // Augmented 9 (aug9)
    int aug9_root[] = {4, 4, 3, 4};
    chord_t *aug9_chord = chord_create(0, strdup("aug9"), aug9_root, 4);
    hash_map_insert(map, aug9_root, 4, aug9_chord);

    // Suspended 9 (9sus4)
    int nine_sus4_root[] = {5, 2, 3, 4};
    chord_t *nine_sus4_chord =
        chord_create(0, strdup("9sus4"), nine_sus4_root, 4);
    hash_map_insert(map, nine_sus4_root, 4, nine_sus4_chord);

    // 9 Flat 5 (9♭5)
    int nine_b5_root[] = {4, 2, 4, 4};
    chord_t *nine_b5_chord = chord_create(0, strdup("9b5"), nine_b5_root, 4);
    hash_map_insert(map, nine_b5_root, 4, nine_b5_chord);

    // 6/9 Chord (69)
    int six_nine_root[] = {4, 3, 2, 5};
    chord_t *six_nine_chord = chord_create(0, strdup("6/9"), six_nine_root, 4);
    hash_map_insert(map, six_nine_root, 4, six_nine_chord);

    // Minor 6/9 (m69)
    int minor_six_nine_root[] = {3, 4, 2, 5};
    chord_t *minor_six_nine_chord =
        chord_create(0, strdup("m6/9"), minor_six_nine_root, 4);
    hash_map_insert(map, minor_six_nine_root, 4, minor_six_nine_chord);
}

void add_six_note_chords(HashMap *map) {
    // Altered Dominant (7alt) - Includes ♭9, ♯9, ♯5, ♭5 variations
    int seven_alt_root[] = {4, 3, 3, 4, 6};
    chord_t *seven_alt_chord =
        chord_create(0, strdup("7alt"), seven_alt_root, 5);
    hash_map_insert(map, seven_alt_root, 5, seven_alt_chord);

    // Minor 11 (m11)
    int m11_root[] = {3, 4, 3, 4, 5};
    chord_t *m11_chord = chord_create(0, strdup("m11"), m11_root, 5);
    hash_map_insert(map, m11_root, 5, m11_chord);
}

void add_seven_note_chords(HashMap *map) {
    // Dominant 13 (13)
    int thirteen_root[] = {4, 3, 3, 4, 5, 4};
    chord_t *thirteen_chord = chord_create(0, strdup("13"), thirteen_root, 6);
    hash_map_insert(map, thirteen_root, 6, thirteen_chord);

    // Minor 13 (m13)
    int m13_root[] = {3, 4, 3, 4, 5, 4};
    chord_t *m13_chord = chord_create(0, strdup("m13"), m13_root, 6);
    hash_map_insert(map, m13_root, 6, m13_chord);

    // Major 13 (M13)
    int M13_root[] = {4, 3, 4, 4, 5, 4};
    chord_t *M13_chord = chord_create(0, strdup("maj13"), M13_root, 6);
    hash_map_insert(map, M13_root, 6, M13_chord);
}

void populate_hash_map(HashMap *map) {
    add_two_note_chords(map);
    add_three_note_chords(map);
    add_four_note_chords(map);
    add_five_note_chords(map);
    add_six_note_chords(map);
    add_seven_note_chords(map);
}
