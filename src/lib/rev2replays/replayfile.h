#ifndef __REPLAYFILE_H__
#define __REPLAYFILE_H__

#include <stdint.h>

#define REPLAYFILE_LEN 0x2538D

enum replayfile_character
{
    SOL = 0,
    KY,
    MAY,
    MILLIA,
    ZATO,
    POTEMKIN,
    CHIPP,
    FAUST,
    AXL,
    VENOM,
    SLAYER,
    INO,
    BEDMAN,
    RAMLETHAL,
    SIN,
    ELPHELT,
    LEO,
    JOHNNY,
    JACKO,
    JAM,
    KUM,
    RAVEN,
    DIZZY,
    BAIKEN,
    ANSWER
};

struct replayfile_header {
    // Expected to be "REPL"
    char magic[4];

    // Maybe a timestamp?
    uint32_t unknown0;

    // So far has always been 0x7c53
    uint16_t unknown1;

    // Haven't investigated these yet
    uint16_t unknown2;
    uint16_t unknown3;
    uint16_t unknown4;

    uint8_t  rounds_to_win;
    uint8_t  round_time_gameseconds;

    // Needs investigation
    uint16_t unknown5;

    // Has always been zeroes as far as I can tell
    uint32_t unknown6[3];
};

struct replayfile_player {
    uint8_t character;
    uint8_t chroma;

    uint16_t unknown1;
    uint32_t unknown2[11];
};

struct replayfile_context {
    struct replayfile_header header;
    struct replayfile_player players[2];
};

const char* replayfile_character_to_str(enum replayfile_character character);
struct replayfile_context* replayfile_create(const char* path);
void replayfile_destroy(struct replayfile_context* context);

#endif // __REPLAYFILE_H__
