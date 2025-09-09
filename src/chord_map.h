#ifndef CHORD_MAP_H
#define CHORD_MAP_H

#define TABLE_SIZE 113

typedef struct {
    int root_index;
    char *quality;
    int *relations;
    int relations_length;
    int *midi_notes;
    char *to_string;
} chord_t;

typedef struct HashNode {
    int key;
    chord_t *chord;
    struct HashNode *next;
} HashNode;

typedef struct {
    HashNode *buckets[TABLE_SIZE];
} HashMap;

HashMap *hash_map_create();

void hash_map_insert(HashMap *map, int *relations, int length, chord_t *chord);

int hash_array(int *arr, int length);

chord_t *hash_map_lookup(HashMap *map, int *relations, int length);

// Adds all chords to the hashmap
void populate_hash_map(HashMap *map);

int note_to_midi(char *note);

int extract_note_name(char *note, char *note_name);

chord_t *chord_create(int root_index, char *quality, int *relations,
                      int relations_length);

#endif  // CHORD_MAP_H
