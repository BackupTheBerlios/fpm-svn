/* -------------------------------------------------------------------------
 *
 * Fixed Point Math Library
 *
 * Copyright (C) 2005, 2006, 2008 by Ivo van Poorten
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301 USA
 *
 * ------------------------------------------------------------------------- */

#ifndef FPM_INTERNAL
#error "This header file should NOT be included directly!"
#else

#ifndef FPM_FPMCODE_H
#define FPM_FPMCODE_H

/* ------------------------------------------------------------------------- */

/* Internal types */

typedef union {
    float    f;
    uint32_t u32;
    uint16_t u16[2];
    uint8_t  u8[4];
} fpm_funion_t;

typedef union {
    double   d;
    uint64_t u64;
    uint32_t u32[2];
    uint16_t u16[4];
    uint8_t  u8[8];
} fpm_dunion_t;

/* ------------------------------------------------------------------------- */

#include <fpm/fpmconversion.h>
#include <fpm/fpmbasic.h>
#include <fpm/fpmsqrt.h>

/* ------------------------------------------------------------------------- */

#endif
#endif
