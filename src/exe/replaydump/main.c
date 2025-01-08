#include <stdio.h>

#include <rev2replays/replayfile.h>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "usage: %s <replay_filepath>\n", argv[0]);
        return -1;
    }

    struct replayfile_context* context = replayfile_create(argv[1]);
    if (context == NULL)
    {
        fprintf(stderr, "failed to create context from path %s\n", argv[1]);
        return -1;
    }

    const char* magic = context->header.magic;
    fprintf(stdout, "MAGIC: %c%c%c%c\n", magic[0], magic[1], magic[2], magic[3]);
    fprintf(stdout, "Rounds to win: %d\n", context->header.rounds_to_win);
    fprintf(stdout, "Rounds time: %d\n", context->header.round_time_gameseconds);

    const uint32_t headerCRC = context->header.crc32;
    fprintf(stdout, "CRC32: 0x%08X\n", headerCRC);
    const uint32_t computedCRC = replayfile_compute_crc32(context);
    if (computedCRC != headerCRC)
    {
        fprintf(stdout, "Computed CRC mismatch: 0x%08X != 0x%08X\n", computedCRC, headerCRC);
    }

    const uint32_t filesize = context->header.filesize;
    fprintf(stdout, "File size: %d\n", filesize);

    struct replayfile_player* player1 = &context->players[0];
    const enum replayfile_character p1character = player1->character;
    fprintf(stdout, "Player 1 character: %s\n", replayfile_character_to_str(p1character));
    fprintf(stdout, "Player 1 color: %d\n", player1->chroma);

    struct replayfile_player* player2 = &context->players[1];
    const enum replayfile_character p2character = player2->character;
    fprintf(stdout, "Player 2 character: %s\n", replayfile_character_to_str(p2character));
    fprintf(stdout, "Player 2 color: %d\n", player2->chroma);

    return 0;
}
