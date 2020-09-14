/*
 * File:   Common.h
 * Author: fuminori.hakoishi
 *
 * Created on September 4, 2020, 4:27 PM
 */

#ifndef COMMON_H
#define COMMON_H

#include <stdbool.h>
#include <stdint.h>

#define ON true
#define OFF false

typedef enum {
    REST,
    DO,
    DO_SHARP,
    RE,
    RE_SHARP,
    MI,
    FA,
    FA_SHARP,
    SO,
    SO_SHARP,
    RA_,
    RA_SHARP,
    SI,
    DO2,
    RE2,
    MI2,
    FA2,
    SO2,
    RA2_,
    SI2,
    SCALE_NUM

} ScaleType;

#endif /* COMMON_H */
