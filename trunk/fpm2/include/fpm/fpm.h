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

#ifndef FPM_FPM_H
#define FPM_FPM_H

/* ------------------------------------------------------------------------- */

/* Be sure we have the right types. Define one or both of FPM_MISSING_* defines
 * when your system does not have one or both of these headers.
 */

#ifndef FPM_MISSING_STDINT_H
#   include <stdint.h>
#else
#   ifndef FPM_MISSING_INTTYPES_H
#       include <inttypes.h>
#   else
typedef unsigned char        uint8_t;
typedef   signed char         int8_t;
typedef unsigned short      uint16_t;
typedef   signed short       int16_t;
typedef unsigned int    i   uint32_t;
typedef   signed int         int32_t;
typedef unsigned long long  uint64_t;
typedef   signed long long   int64_t;
#   endif
#endif

/* ------------------------------------------------------------------------- */

/* Attributes. By default, they are all off. Define HAVE_* to enable
 * one or all of them.
 */

#ifdef HAVE_ALWAYS_INLINE
#   define fpm_always_inline __attribute__((always_inline)) inline
#else
#   define fpm_always_inline inline
#endif

#ifdef HAVE_UNUSED
#   define fpm_unused __attribute__((unused))
#else
#   define fpm_unused
#endif

#define FPMFUNC static fpm_always_inline

/* ------------------------------------------------------------------------- */

/* TYPES */

/* Signed fixed point types */

typedef int16_t fp8p8_t;
typedef int32_t fp24p8_t;
typedef int32_t fp16p16_t;
typedef int32_t fp8p24_t;

/* Unsigned fixed point types */

typedef uint16_t ufp8p8_t;
typedef uint32_t ufp24p8_t;
typedef uint32_t ufp16p16_t;
typedef uint32_t ufp8p24_t;

/* ------------------------------------------------------------------------- */

/* CONVERSION */

/* int to fixed point */

FPMFUNC  fp8p8_t   itofp8p8   (int x) { return x << 8;  }
FPMFUNC  fp24p8_t  itofp24p8  (int x) { return x << 8;  }
FPMFUNC  fp16p16_t itofp16p16 (int x) { return x << 16; }
FPMFUNC  fp8p24_t  itofp8p24  (int x) { return x << 24; }
FPMFUNC ufp8p8_t   itoufp8p8  (int x) { return x << 8;  }
FPMFUNC ufp24p8_t  itoufp24p8 (int x) { return x << 8;  }
FPMFUNC ufp16p16_t itoufp16p16(int x) { return x << 16; }
FPMFUNC ufp8p24_t  itoufp8p24 (int x) { return x << 24; }

/* float to fixed point */

FPMFUNC  fp8p8_t   ftofp8p8   (float x) { return x * 256;      }
FPMFUNC  fp24p8_t  ftofp24p8  (float x) { return x * 256;      }
FPMFUNC  fp16p16_t ftofp16p16 (float x) { return x * 65536;    }
FPMFUNC  fp8p24_t  ftofp8p24  (float x) { return x * 16777216; }
FPMFUNC ufp8p8_t   ftoufp8p8  (float x) { return x * 256;      }
FPMFUNC ufp24p8_t  ftoufp24p8 (float x) { return x * 256;      }
FPMFUNC ufp16p16_t ftoufp16p16(float x) { return x * 65536;    }
FPMFUNC ufp8p24_t  ftoufp8p24 (float x) { return x * 16777216; }

/* double to fixed point */

FPMFUNC  fp8p8_t   dtofp8p8   (double x) { return x * 256;      }
FPMFUNC  fp24p8_t  dtofp24p8  (double x) { return x * 256;      }
FPMFUNC  fp16p16_t dtofp16p16 (double x) { return x * 65536;    }
FPMFUNC  fp8p24_t  dtofp8p24  (double x) { return x * 16777216; }
FPMFUNC ufp8p8_t   dtoufp8p8  (double x) { return x * 256;      }
FPMFUNC ufp24p8_t  dtoufp24p8 (double x) { return x * 256;      }
FPMFUNC ufp16p16_t dtoufp16p16(double x) { return x * 65536;    }
FPMFUNC ufp8p24_t  dtoufp8p24 (double x) { return x * 16777216; }

/* fixed point to int (truncated) */

FPMFUNC int  fp8p8toi  ( fp8p8_t   x) { return x >> 8;  }
FPMFUNC int  fp24p8toi ( fp24p8_t  x) { return x >> 8;  }
FPMFUNC int  fp16p16toi( fp16p16_t x) { return x >> 16; }
FPMFUNC int  fp8p24toi ( fp8p24_t  x) { return x >> 24; }
FPMFUNC int ufp8p8toi  (ufp8p8_t   x) { return x >> 8;  }
FPMFUNC int ufp24p8toi (ufp24p8_t  x) { return x >> 8;  }
FPMFUNC int ufp16p16toi(ufp16p16_t x) { return x >> 16; }
FPMFUNC int ufp8p24toi (ufp8p24_t  x) { return x >> 24; }

/* fixed point to float */

FPMFUNC float  fp8p8tof  ( fp8p8_t   x) { return (float) x / 256.0;      }
FPMFUNC float  fp24p8tof ( fp24p8_t  x) { return (float) x / 256.0;      }
FPMFUNC float  fp16p16tof( fp16p16_t x) { return (float) x / 65536.0;    }
FPMFUNC float  fp8p24tof ( fp8p24_t  x) { return (float) x / 16777216.0; }
FPMFUNC float ufp8p8tof  (ufp8p8_t   x) { return (float) x / 256.0;      }
FPMFUNC float ufp24p8tof (ufp24p8_t  x) { return (float) x / 256.0;      }
FPMFUNC float ufp16p16tof(ufp16p16_t x) { return (float) x / 65536.0;    }
FPMFUNC float ufp8p24tof (ufp8p24_t  x) { return (float) x / 16777216.0; }

/* fixed point to double */

FPMFUNC double  fp8p8tod  ( fp8p8_t   x) { return (double) x / 256.0L;      }
FPMFUNC double  fp24p8tod ( fp24p8_t  x) { return (double) x / 256.0L;      }
FPMFUNC double  fp16p16tod( fp16p16_t x) { return (double) x / 65536.0L;    }
FPMFUNC double  fp8p24tod ( fp8p24_t  x) { return (double) x / 16777216.0L; }
FPMFUNC double ufp8p8tod  (ufp8p8_t   x) { return (double) x / 256.0L;      }
FPMFUNC double ufp24p8tod (ufp24p8_t  x) { return (double) x / 256.0L;      }
FPMFUNC double ufp16p16tod(ufp16p16_t x) { return (double) x / 65536.0L;    }
FPMFUNC double ufp8p24tod (ufp8p24_t  x) { return (double) x / 16777216.0L; }

/* fixed point to fixed point */

FPMFUNC fp8p8_t     fp8p8tofp8p8   ( fp8p8_t x) { return x;       }
FPMFUNC fp24p8_t    fp8p8tofp24p8  ( fp8p8_t x) { return x;       }
FPMFUNC fp16p16_t   fp8p8tofp16p16 ( fp8p8_t x) { return x << 8;  }
FPMFUNC fp8p24_t    fp8p8tofp8p24  ( fp8p8_t x) { return x << 16; }
FPMFUNC ufp8p8_t   ufp8p8toufp8p8  (ufp8p8_t x) { return x;       }
FPMFUNC ufp24p8_t  ufp8p8toufp24p8 (ufp8p8_t x) { return x;       }
FPMFUNC ufp16p16_t ufp8p8toufp16p16(ufp8p8_t x) { return x << 8;  }
FPMFUNC ufp8p24_t  ufp8p8toufp8p24 (ufp8p8_t x) { return x << 16; }

FPMFUNC fp8p8_t     fp24p8tofp8p8   ( fp24p8_t x) { return x;       }
FPMFUNC fp24p8_t    fp24p8tofp24p8  ( fp24p8_t x) { return x;       }
FPMFUNC fp16p16_t   fp24p8tofp16p16 ( fp24p8_t x) { return x << 8;  }
FPMFUNC fp8p24_t    fp24p8tofp8p24  ( fp24p8_t x) { return x << 16; }
FPMFUNC ufp8p8_t   ufp24p8toufp8p8  (ufp24p8_t x) { return x;       }
FPMFUNC ufp24p8_t  ufp24p8toufp24p8 (ufp24p8_t x) { return x;       }
FPMFUNC ufp16p16_t ufp24p8toufp16p16(ufp24p8_t x) { return x << 8;  }
FPMFUNC ufp8p24_t  ufp24p8toufp8p24 (ufp24p8_t x) { return x << 16; }

FPMFUNC fp8p8_t     fp16p16tofp8p8   ( fp16p16_t x) { return x >> 8; }
FPMFUNC fp24p8_t    fp16p16tofp24p8  ( fp16p16_t x) { return x >> 8; }
FPMFUNC fp16p16_t   fp16p16tofp16p16 ( fp16p16_t x) { return x;      }
FPMFUNC fp8p24_t    fp16p16tofp8p24  ( fp16p16_t x) { return x << 8; }
FPMFUNC ufp8p8_t   ufp16p16toufp8p8  (ufp16p16_t x) { return x >> 8; }
FPMFUNC ufp24p8_t  ufp16p16toufp24p8 (ufp16p16_t x) { return x >> 8; }
FPMFUNC ufp16p16_t ufp16p16toufp16p16(ufp16p16_t x) { return x;      }
FPMFUNC ufp8p24_t  ufp16p16toufp8p24 (ufp16p16_t x) { return x << 8; }

FPMFUNC fp8p8_t     fp8p24tofp8p8   ( fp8p24_t x) { return x >> 16; }
FPMFUNC fp24p8_t    fp8p24tofp24p8  ( fp8p24_t x) { return x >> 16; }
FPMFUNC fp16p16_t   fp8p24tofp16p16 ( fp8p24_t x) { return x >> 8;  }
FPMFUNC fp8p24_t    fp8p24tofp8p24  ( fp8p24_t x) { return x;       }
FPMFUNC ufp8p8_t   ufp8p24toufp8p8  (ufp8p24_t x) { return x >> 16; }
FPMFUNC ufp24p8_t  ufp8p24toufp24p8 (ufp8p24_t x) { return x >> 16; }
FPMFUNC ufp16p16_t ufp8p24toufp16p16(ufp8p24_t x) { return x >> 8;  }
FPMFUNC ufp8p24_t  ufp8p24toufp8p24 (ufp8p24_t x) { return x;       }

/* ------------------------------------------------------------------------- */

/* BASIC MATH */

/* multiplication (x*y) */

FPMFUNC fp8p8_t    mulfp8p8   ( fp8p8_t   x,  fp8p8_t   y) { return ( int32_t) x * y >> 8;  }
FPMFUNC fp24p8_t   mulfp24p8  ( fp24p8_t  x,  fp24p8_t  y) { return ( int64_t) x * y >> 8;  }
FPMFUNC fp16p16_t  mulfp16p16 ( fp16p16_t x,  fp16p16_t y) { return ( int64_t) x * y >> 16; }
FPMFUNC fp8p24_t   mulfp8p24  ( fp8p24_t  x,  fp8p24_t  y) { return ( int64_t) x * y >> 24; }
FPMFUNC ufp8p8_t   mulufp8p8  (ufp8p8_t   x, ufp8p8_t   y) { return (uint32_t) x * y >> 8;  }
FPMFUNC ufp24p8_t  mulufp24p8 (ufp24p8_t  x, ufp24p8_t  y) { return (uint64_t) x * y >> 8;  }
FPMFUNC ufp16p16_t mulufp16p16(ufp16p16_t x, ufp16p16_t y) { return (uint64_t) x * y >> 16; }
FPMFUNC ufp8p24_t  mulufp8p24 (ufp8p24_t  x, ufp8p24_t  y) { return (uint64_t) x * y >> 24; }

/* division (x/y) */

FPMFUNC fp8p8_t    divfp8p8   ( fp8p8_t   x,  fp8p8_t   y) { return (( int32_t) x << 8 ) / y; }
FPMFUNC fp24p8_t   divfp24p8  ( fp24p8_t  x,  fp24p8_t  y) { return (( int64_t) x << 8 ) / y; }
FPMFUNC fp16p16_t  divfp16p16 ( fp16p16_t x,  fp16p16_t y) { return (( int64_t) x << 16) / y; }
FPMFUNC fp8p24_t   divfp8p24  ( fp8p24_t  x,  fp8p24_t  y) { return (( int64_t) x << 24) / y; }
FPMFUNC ufp8p8_t   divufp8p8  (ufp8p8_t   x, ufp8p8_t   y) { return ((uint32_t) x << 8 ) / y; }
FPMFUNC ufp24p8_t  divufp24p8 (ufp24p8_t  x, ufp24p8_t  y) { return ((uint64_t) x << 8 ) / y; }
FPMFUNC ufp16p16_t divufp16p16(ufp16p16_t x, ufp16p16_t y) { return ((uint64_t) x << 16) / y; }
FPMFUNC ufp8p24_t  divufp8p24 (ufp8p24_t  x, ufp8p24_t  y) { return ((uint64_t) x << 24) / y; }

/* ------------------------------------------------------------------------- */

/* ADVANCED MATH */

/* ------------------------------------------------------------------------- */

#endif