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

FPMFUNC double  fp8p8tod  ( fp8p8_t   x) { return (double) x / 256.0;      }
FPMFUNC double  fp24p8tod ( fp24p8_t  x) { return (double) x / 256.0;      }
FPMFUNC double  fp16p16tod( fp16p16_t x) { return (double) x / 65536.0;    }
FPMFUNC double  fp8p24tod ( fp8p24_t  x) { return (double) x / 16777216.0; }
FPMFUNC double ufp8p8tod  (ufp8p8_t   x) { return (double) x / 256.0;      }
FPMFUNC double ufp24p8tod (ufp24p8_t  x) { return (double) x / 256.0;      }
FPMFUNC double ufp16p16tod(ufp16p16_t x) { return (double) x / 65536.0;    }
FPMFUNC double ufp8p24tod (ufp8p24_t  x) { return (double) x / 16777216.0; }

/* fixed point to fixed point */

#define FPMA2B(a,b,c) FPMFUNC b##_t a##to##b(a##_t x) { return x c; } \
          FPMFUNC u##b##_t u##a##to##u##b(u##a##_t x) { return x c; }

FPMA2B(fp8p8  , fp8p8  ,     )      FPMA2B(fp8p8  , fp24p8 ,     )
FPMA2B(fp8p8  , fp16p16, <<8 )      FPMA2B(fp8p8  , fp8p24 , <<16)
FPMA2B(fp24p8 , fp8p8  ,     )      FPMA2B(fp24p8 , fp24p8 ,     )
FPMA2B(fp24p8 , fp16p16, <<8 )      FPMA2B(fp24p8 , fp8p24 , <<16)
FPMA2B(fp16p16, fp8p8  , >>8 )      FPMA2B(fp16p16, fp24p8 , >>8 )
FPMA2B(fp16p16, fp16p16,     )      FPMA2B(fp16p16, fp8p24 , <<8 )
FPMA2B(fp8p24 , fp8p8  , >>16)      FPMA2B(fp8p24 , fp24p8 , >>16)
FPMA2B(fp8p24 , fp16p16, >>8 )      FPMA2B(fp8p24 , fp8p24 ,     )

/* ------------------------------------------------------------------------- */

/* BASIC MATH */

#define FPMXY8p8    fp8p8_t    x, fp8p8_t    y
#define FPMXY24p8   fp24p8_t   x, fp24p8_t   y
#define FPMXY16p16  fp16p16_t  x, fp16p16_t  y
#define FPMXY8p24   fp8p24_t   x, fp8p24_t   y
#define FPMXYu8p8   ufp8p8_t   x, ufp8p8_t   y
#define FPMXYu24p8  ufp24p8_t  x, ufp24p8_t  y
#define FPMXYu16p16 ufp16p16_t x, ufp16p16_t y
#define FPMXYu8p24  ufp8p24_t  x, ufp8p24_t  y

/* multiplication (x*y) */

FPMFUNC fp8p8_t    mulfp8p8   (FPMXY8p8   ) { return ( int32_t) x * y >> 8;  }
FPMFUNC fp24p8_t   mulfp24p8  (FPMXY24p8  ) { return ( int64_t) x * y >> 8;  }
FPMFUNC fp16p16_t  mulfp16p16 (FPMXY16p16 ) { return ( int64_t) x * y >> 16; }
FPMFUNC fp8p24_t   mulfp8p24  (FPMXY8p24  ) { return ( int64_t) x * y >> 24; }
FPMFUNC ufp8p8_t   mulufp8p8  (FPMXYu8p8  ) { return (uint32_t) x * y >> 8;  }
FPMFUNC ufp24p8_t  mulufp24p8 (FPMXYu24p8 ) { return (uint64_t) x * y >> 8;  }
FPMFUNC ufp16p16_t mulufp16p16(FPMXYu16p16) { return (uint64_t) x * y >> 16; }
FPMFUNC ufp8p24_t  mulufp8p24 (FPMXYu8p24 ) { return (uint64_t) x * y >> 24; }

/* fast multiplication, less precision */

FPMFUNC fp8p8_t    fastmulfp8p8   (FPMXY8p8   ) { return (x>>4 ) * (y>>4 ); }
FPMFUNC fp24p8_t   fastmulfp24p8  (FPMXY24p8  ) { return (x>>4 ) * (y>>4 ); }
FPMFUNC fp16p16_t  fastmulfp16p16 (FPMXY16p16 ) { return (x>>8 ) * (y>>8 ); }
FPMFUNC fp8p24_t   fastmulfp8p24  (FPMXY8p24  ) { return (x>>12) * (y>>12); }
FPMFUNC ufp8p8_t   fastmulufp8p8  (FPMXYu8p8  ) { return (x>>4 ) * (y>>4 ); }
FPMFUNC ufp24p8_t  fastmulufp24p8 (FPMXYu24p8 ) { return (x>>4 ) * (y>>4 ); }
FPMFUNC ufp16p16_t fastmulufp16p16(FPMXYu16p16) { return (x>>8 ) * (y>>8 ); }
FPMFUNC ufp8p24_t  fastmulufp8p24 (FPMXYu8p24 ) { return (x>>12) * (y>>12); }

/* division (x/y) */

FPMFUNC fp8p8_t    divfp8p8   (FPMXY8p8   ) { return (( int32_t) x<<8 ) / y; }
FPMFUNC fp24p8_t   divfp24p8  (FPMXY24p8  ) { return (( int64_t) x<<8 ) / y; }
FPMFUNC fp16p16_t  divfp16p16 (FPMXY16p16 ) { return (( int64_t) x<<16) / y; }
FPMFUNC fp8p24_t   divfp8p24  (FPMXY8p24  ) { return (( int64_t) x<<24) / y; }
FPMFUNC ufp8p8_t   divufp8p8  (FPMXYu8p8  ) { return ((uint32_t) x<<8 ) / y; }
FPMFUNC ufp24p8_t  divufp24p8 (FPMXYu24p8 ) { return ((uint64_t) x<<8 ) / y; }
FPMFUNC ufp16p16_t divufp16p16(FPMXYu16p16) { return ((uint64_t) x<<16) / y; }
FPMFUNC ufp8p24_t  divufp8p24 (FPMXYu8p24 ) { return ((uint64_t) x<<24) / y; }

/* fast division, less precision, lower max x, perhaps not that useful */

FPMFUNC fp8p8_t    fastdivfp8p8   (FPMXY8p8   ) { return ((x<<4) / y) << 4;  }
FPMFUNC fp24p8_t   fastdivfp24p8  (FPMXY24p8  ) { return ((x<<8) / y);       }
FPMFUNC fp16p16_t  fastdivfp16p16 (FPMXY16p16 ) { return ((x<<8) / y) << 8;  }
FPMFUNC fp8p24_t   fastdivfp8p24  (FPMXY8p24  ) { return ((x<<4) / y) << 20; }
FPMFUNC ufp8p8_t   fastdivufp8p8  (FPMXYu8p8  ) { return ((x<<4) / y) << 4;  }
FPMFUNC ufp24p8_t  fastdivufp24p8 (FPMXYu24p8 ) { return ((x<<8) / y);       }
FPMFUNC ufp16p16_t fastdivufp16p16(FPMXYu16p16) { return ((x<<8) / y) << 8;  }
FPMFUNC ufp8p24_t  fastdivufp8p24 (FPMXYu8p24 ) { return ((x<<4) / y) << 20; }

/* ------------------------------------------------------------------------- */

/* ADVANCED MATH */

/* ------------------------------------------------------------------------- */

#endif
#endif