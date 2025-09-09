#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "analyzer.h"
#include "raylib.h"

// Constants
#define NUM_KEYS 88
#define WHITE_KEYS 52
#define BLACK_KEYS 36
#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 300
#define WHITE_KEY_WIDTH (SCREEN_WIDTH / WHITE_KEYS)
#define BLACK_KEY_WIDTH (WHITE_KEY_WIDTH * 0.6)
#define BLACK_KEY_HEIGHT (SCREEN_HEIGHT * 0.6)
#define MAX_NOTES 7

// Data Structures
typedef struct {
    Color color;  // White or Black
    int midiNote;
    bool isPressed;
} Key;

Key keys[NUM_KEYS];
int selectedNotes[NUM_KEYS];
int selectedCount = 0;
char chordText[50] = "Unknown chord";

// Determines if a MIDI note is a black key
bool IsBlackKey(int midiNote) {
    int posInOctave = (midiNote - 1) % 12;  // MIDI notes are 1-based
    return (posInOctave == 1 || posInOctave == 4 || posInOctave == 6 ||
            posInOctave == 9 || posInOctave == 11);
}

// Initialize the piano keys
void InitializeKeys() {
    for (int i = 0; i < NUM_KEYS; i++) {
        keys[i].midiNote = i + 21;
        keys[i].isPressed = false;

        if (IsBlackKey(i + 1)) {
            keys[i].color = BLACK;
        } else {
            keys[i].color = WHITE;
        }
    }
}

void DrawPiano() {
    // First, draw all white keys
    int whiteKeyIndex = 0;
    for (int i = 0; i < NUM_KEYS; i++) {
        if (ColorIsEqual(keys[i].color, WHITE)) {
            Color color = keys[i].isPressed ? RED : WHITE;
            int x = whiteKeyIndex * WHITE_KEY_WIDTH;
            DrawRectangle(x, 50, WHITE_KEY_WIDTH, SCREEN_HEIGHT - 50, color);
            DrawRectangleLines(x, 50, WHITE_KEY_WIDTH, SCREEN_HEIGHT - 50,
                               BLACK);
            whiteKeyIndex++;
        }
    }

    // Then, draw all black keys on top
    whiteKeyIndex = 0;
    for (int i = 0; i < NUM_KEYS; i++) {
        if (ColorIsEqual(keys[i].color, WHITE)) {
            whiteKeyIndex++;
        } else {
            // Black key: determine its X position between two white keys
            int x = whiteKeyIndex * WHITE_KEY_WIDTH - (BLACK_KEY_WIDTH / 2);
            Color color = keys[i].isPressed ? RED : BLACK;

            // Only draw if it's in range
            if (x >= 0 && x + BLACK_KEY_WIDTH <= SCREEN_WIDTH) {
                DrawRectangle(x, 50, BLACK_KEY_WIDTH, BLACK_KEY_HEIGHT, color);
                DrawRectangleLines(x, 50, BLACK_KEY_WIDTH, BLACK_KEY_HEIGHT,
                                   DARKGRAY);
            }
        }
    }
}

void CheckKeyClicks(HashMap *chord_map) {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        int mouseX = GetMouseX();
        int mouseY = GetMouseY();

        // First check black keys (they are on top visually)
        int whiteKeyIndex = 0;
        for (int i = 0; i < NUM_KEYS; i++) {
            if (ColorIsEqual(keys[i].color, WHITE)) {
                whiteKeyIndex++;
                continue;
            }

            // Calculate black key position
            int x = whiteKeyIndex * WHITE_KEY_WIDTH - (BLACK_KEY_WIDTH / 2);
            if (mouseX >= x && mouseX <= x + BLACK_KEY_WIDTH && mouseY >= 50 &&
                mouseY <= 50 + BLACK_KEY_HEIGHT) {
                keys[i].isPressed = !keys[i].isPressed;
                goto updateChord;
            }
        }

        // If no black key was clicked, check white keys
        whiteKeyIndex = 0;
        for (int i = 0; i < NUM_KEYS; i++) {
            if (ColorIsEqual(keys[i].color, WHITE)) {
                int x = whiteKeyIndex * WHITE_KEY_WIDTH;
                if (mouseX >= x && mouseX <= x + WHITE_KEY_WIDTH &&
                    mouseY >= 50 && mouseY <= SCREEN_HEIGHT) {
                    keys[i].isPressed = !keys[i].isPressed;
                    break;
                }
                whiteKeyIndex++;
            }
        }

    updateChord:
        // Update selected notes list
        selectedCount = 0;
        for (int i = 0; i < NUM_KEYS; i++) {
            if (keys[i].isPressed && selectedCount < MAX_NOTES) {
                selectedNotes[selectedCount++] = keys[i].midiNote;
            }
        }

        // Analyze chord
        if (selectedCount > 0) {
            chord_t *result =
                chord_analyzer(selectedNotes, selectedCount, chord_map);
            if (result) {
                strncpy(chordText, result->to_string, 49);
                chordText[49] = '\0';
            } else {
                strcpy(chordText, "Unknown chord");
            }
        } else if (selectedCount == 8) {
            sprintf(chordText, "%d", selectedNotes[0]);
        } else {
            strcpy(chordText, "Unknown chord");
        }
    }
}

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Piano Keyboard");
    SetTargetFPS(60);

    InitializeKeys();
    HashMap *chord_map = hash_map_create();
    populate_hash_map(chord_map);

    while (!WindowShouldClose()) {
        CheckKeyClicks(chord_map);

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawPiano();
        DrawText(chordText, SCREEN_WIDTH / 2 - MeasureText(chordText, 30) / 2,
                 10, 30, BLACK);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
