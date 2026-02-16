/*
 * compass_frames.h
 *
 *  Created on: Jan 2, 2026
 *      Author: user
 */

#ifndef COMPASS_FRAMES_H
#define COMPASS_FRAMES_H

#include <stdint.h>

#define COMPASS_FRAME_COUNT 12
#define COMPASS_FRAME_WIDTH 132
#define COMPASS_FRAME_HEIGHT 64
#define COMPASS_FRAME_SIZE (COMPASS_FRAME_WIDTH * COMPASS_FRAME_HEIGHT / 8)

// Deklaracije svih frameova
extern const uint8_t compass_frame_0[];
extern const uint8_t compass_frame_30[];
extern const uint8_t compass_frame_60[];
extern const uint8_t compass_frame_90[];
extern const uint8_t compass_frame_120[];
extern const uint8_t compass_frame_150[];
extern const uint8_t compass_frame_180[];
extern const uint8_t compass_frame_210[];
extern const uint8_t compass_frame_240[];
extern const uint8_t compass_frame_270[];
extern const uint8_t compass_frame_300[];
extern const uint8_t compass_frame_330[];

// Lookup tablica
extern const uint8_t* compass_frames[COMPASS_FRAME_COUNT];

#endif

