/*
  commonly-used routines
  Copyright (c) 2006-2015 Cheng Zhang

  This material is provided "as is", with absolutely no warranty expressed
  or implied. Any use is at your own risk.
  Permission to use or copy this software for any purpose is hereby granted
  without fee. Permission to modify the code and to distribute modified
  code is also granted without any restrictions.

  Usage:

  1.  This header file is designed for rapid programming.
      You can simply include this file and all functions will be available.
      But there might be many compiler warnings for unused functions.

  2.  You can include this file multiple times in a single file.

  3.  All functions are static by default. To export functions,
      e.g., to make it easier to debug, or to avoid warnings of unused functions,
      define ZCOM_XFUNCS before the first inclusion.

  4.  To hand-pick a specific set of modules, e.g.,
        #define ZCOM_PICK
        #define ZCOM_RNG
        #define ZCOM_ARGOPT
      before including this file.  In this way, other modules are skipped.

  5.  If the compiler supports keywords inline and restrict, write
        #define INLINE inline
        #define RESTRICT restrict
      before including this file. Otherwise the default values,
      according to the compiler, are used.

  6.  Define HAVEVAM if the compiler supports variable-argument macros.

  7.  The `util' module defines `real' as a double, to override it, write
        typedef float real;
        #define HAVEREAL 1
      before including this file (or equivalently define HAVE_REAL)
*/

/* ZCOM_PICK or ZCOM_NONE is used include only subset of modules
 * 1. to reduce the number of warnings for unused functions
 * 2. to reduce the compiling time
 * 3. to avoid potential name conflicts
 * By default, ZCOM_PICK is undefined, so everything is used. */
#ifdef ZCOM_NONE  /* equivalent to ZCOM_PICK */
#define ZCOM_PICK
#endif

#ifndef ZCOM_PICK
  #ifndef ZCOM_UTIL
  #define ZCOM_UTIL
  #endif
  #ifndef ZCOM_BITS
  #define ZCOM_BITS
  #endif
  #ifndef ZCOM_BLKMEM
  #define ZCOM_BLKMEM
  #endif
  #ifndef ZCOM_SS
  #define ZCOM_SS
  #endif
  #ifndef ZCOM_ENDN
  #define ZCOM_ENDN
  #endif
  #ifndef ZCOM_BIO
  #define ZCOM_BIO
  #endif
  #ifndef ZCOM_OSYS
  #define ZCOM_OSYS
  #endif
  #ifndef ZCOM_OPT
  #define ZCOM_OPT
  #endif
  #ifndef ZCOM_ARGOPT
  #define ZCOM_ARGOPT
  #endif
  #ifndef ZCOM_CFG
  #define ZCOM_CFG
  #endif
  #ifndef ZCOM_LOG
  #define ZCOM_LOG
  #endif
  #ifndef ZCOM_AV
  #define ZCOM_AV
  #endif
  #ifndef ZCOM_HIST
  #define ZCOM_HIST
  #endif
  #ifndef ZCOM_RNG
  #define ZCOM_RNG
  #endif
  #ifndef ZCOM_RC
  #define ZCOM_RC
  #endif
  #ifndef ZCOM_RV2
  #define ZCOM_RV2
  #endif
  #ifndef ZCOM_RV3
  #define ZCOM_RV3
  #endif
  #ifndef ZCOM_RVN
  #define ZCOM_RVN
  #endif
  #ifndef ZCOM_CHOLESKY
  #define ZCOM_CHOLESKY
  #endif
  #ifndef ZCOM_LU
  #define ZCOM_LU
  #endif
  #ifndef ZCOM_SVD
  #define ZCOM_SVD
  #endif
  #ifndef ZCOM_EIG
  #define ZCOM_EIG
  #endif
  #ifndef ZCOM_SPECFUNC
  #define ZCOM_SPECFUNC
  #endif
  #ifndef ZCOM_NUMTHR
  #define ZCOM_NUMTHR
  #endif
  #ifndef ZCOM_SAVGOL
  #define ZCOM_SAVGOL
  #endif
  #ifndef ZCOM_MDS
  #define ZCOM_MDS
  #endif
  #ifndef ZCOM_PDB
  #define ZCOM_PDB
  #endif
  #ifndef ZCOM_MD
  #define ZCOM_MD
  #endif
  #ifndef ZCOM_HMC
  #define ZCOM_HMC
  #endif
  #ifndef ZCOM_ISING2
  #define ZCOM_ISING2
  #endif
  #ifndef ZCOM_POTTS2
  #define ZCOM_POTTS2
  #endif
  #ifndef ZCOM_LJ
  #define ZCOM_LJ
  #endif
  #ifndef ZCOM_ABPRO
  #define ZCOM_ABPRO
  #endif
  #ifndef ZCOM_CAGO
  #define ZCOM_CAGO
  #endif
#endif

/* build dependencies */
#ifdef ZCOM_GLEZ
  #define ZCOM_RV3
#endif

#ifdef ZCOM_CAGO
  #define ZCOM_MD
  #define ZCOM_PDB
#endif

#ifdef ZCOM_ABPRO
  #define ZCOM_MD
#endif

#ifdef ZCOM_LJ
  #define ZCOM_MD
  #define ZCOM_HIST
  #define ZCOM_AV
#endif

#ifdef ZCOM_POTTS2
  #define ZCOM_RNG
#endif

#ifdef ZCOM_ISING2
  #define ZCOM_RNG
#endif

#ifdef ZCOM_HMC
  #define ZCOM_RNG
#endif

#ifdef ZCOM_MD
  #define ZCOM_RV3
  #define ZCOM_RV2
#endif

#ifdef ZCOM_PDB
  #define ZCOM_RV3
#endif

#ifdef ZCOM_MDS
  #define ZCOM_EIG
#endif

#ifdef ZCOM_SAVGOL
  #define ZCOM_SPECFUNC
  #define ZCOM_LU
#endif

#ifdef ZCOM_NUMTHR
  #define ZCOM_UTIL
#endif

#ifdef ZCOM_SPECFUNC
  #define ZCOM_UTIL
#endif

#ifdef ZCOM_EIG
  #define ZCOM_UTIL
#endif

#ifdef ZCOM_SVD
  #define ZCOM_UTIL
#endif

#ifdef ZCOM_LU
  #define ZCOM_UTIL
#endif

#ifdef ZCOM_CHOLESKY
  #define ZCOM_UTIL
#endif

#ifdef ZCOM_RVN
  #define ZCOM_RV3
  #define ZCOM_RV2
#endif

#ifdef ZCOM_RV3
  #define ZCOM_RNG
#endif

#ifdef ZCOM_RV2
  #define ZCOM_RNG
#endif

#ifdef ZCOM_RC
  #define ZCOM_UTIL
#endif

#ifdef ZCOM_RNG
  #define ZCOM_UTIL
#endif

#ifdef ZCOM_HIST
  #define ZCOM_UTIL
#endif

#ifdef ZCOM_AV
  #define ZCOM_UTIL
#endif

#ifdef ZCOM_LOG
  #define ZCOM_UTIL
#endif

#ifdef ZCOM_CFG
  #define ZCOM_OPT
#endif

#ifdef ZCOM_ARGOPT
  #define ZCOM_OPT
#endif

#ifdef ZCOM_OPT
  #define ZCOM_SS
  #define ZCOM_UTIL
#endif

#ifdef ZCOM_OSYS
  #define ZCOM_SS
  #define ZCOM_UTIL
#endif

#ifdef ZCOM_BIO
  #define ZCOM_ENDN
#endif

#ifdef ZCOM_BLKMEM
  #define ZCOM_UTIL
#endif

#ifdef ZCOM_BITS
  #define ZCOM_UTIL
#endif


/* manage storage class: static is the safer choice
   to avoid naming conflict.  Example:
   both m.c and n.c include this file,
   m.c --> m.o, n.c --> n.o, m.o+n.o --> a.out
   static is the only way to avoid naming conflict in this case.

   In case that this file is included multiple times,
   ZCOM_XFUNCS should be defined before the first inclusion,
   otherwise it won't be effective in deciding storage class. */
#ifndef STRCLS
  #ifndef ZCOM_XFUNCS
    #define STRCLS static
  #else
    #define STRCLS
  #endif
#endif

/* inline keyword */
#ifndef INLINE
  #if defined(__GNUC__) || defined(__xlC__)
    #define INLINE STRCLS __inline__
  #elif defined(__INTEL_COMPILER)
    #define INLINE STRCLS __inline
  #elif defined(_MSC_VER) || defined(__BORLANDC__)
    #define INLINE __inline STRCLS
  #elif defined(__STDC_VERSION__) && (STDC_VERSION__ >= 199901L)
    #define INLINE STRCLS inline
  #else
    #define INLINE STRCLS
  #endif
#endif

/* restrict keyword */
#ifndef RESTRICT
  #if (defined(__GNUC__) || defined(__INTEL_COMPILER) || defined(__xlC__) \
      || (defined(_MSC_VER) && _MSC_VER >= 1400))
    #define RESTRICT __restrict
  #elif defined(__STDC_VERSION__) && (STDC_VERSION__ >= 199901L)
    #define RESTRICT restrict
  #else
    #define RESTRICT
  #endif
#endif

/* macros with variable-length arguments */
#ifndef HAVEVAM
  #if (  (defined(__GNUC__) && (__GNUC__ >= 3))   \
      || (defined(__xlC__)  && (__xlC__ >= 0x0700)) \
      || (defined(_MSC_VER) && (_MSC_VER >= 1400)) )
    #define HAVEVAM 1
  #endif
#endif

#ifdef __INTEL_COMPILER
  #pragma warning push
  #pragma warning(disable:981) /* unspecified order of operands */
  #pragma warning(disable:177) /* unreferenced function */
  #pragma warning(disable:161) /* unrecognized #pragma, for omp */
#elif defined(__GNUC__) && (__GNUC__ >= 4 && __GNUC_MINOR__ >= 2)
  /* Note: intel compiler also defines __GNUC__ */
  #if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)
    /* diagonistic push and pop are added in GCC 4.6 */
    #pragma GCC diagnostic push
  #endif
  #pragma GCC diagnostic ignored "-Wunknown-pragmas"
  #pragma GCC diagnostic ignored "-Wvariadic-macros"
  #pragma GCC diagnostic ignored "-Wlong-long"
#endif

#ifdef _MSC_VER
  #pragma warning(push)
  #pragma warning(disable:4127) /* conditional expression constant */
  #pragma warning(disable:4505) /* unreferenced function */
  #pragma warning(disable:4514) /* unreferenced inline */
  #pragma warning(disable:4710) /* not inlined */
  /* suppress CRT safety warnings:
   * no need for "_s" versions of CRT functions
   * The macros below will not work if standard C library files
   * like <stdio.h> and <time.h> are included before zcom.h */
  #ifndef _CRT_SECURE_NO_DEPRECATE
  #define _CRT_SECURE_NO_DEPRECATE
  #endif
  #ifndef _CRT_SECURE_NO_WARNINGS
  #define _CRT_SECURE_NO_WARNINGS
  #endif
  #include <stdio.h>
#endif

#ifdef __BORLANDC__
  #pragma warning(push)
  #pragma warn -8027 /* not expanded inlined */
#endif

#ifdef _OPENMP
#include <omp.h>
#endif

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/* In addition to ZCOM_ABC, we have to define another macro ZCOM_ABC__
 * to allow multiple inclusions. */


#ifdef  ZCOM_UTIL
#ifndef ZCOM_UTIL__
#define ZCOM_UTIL__
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>
#include <limits.h>
#include <float.h>


/* define a real type */
#ifdef HAVE_REAL
  #ifndef HAVEREAL
  #define HAVEREAL HAVE_REAL
  #endif
#endif

#ifndef HAVEREAL
  #define HAVEREAL 1
  typedef double real;
#endif


/* define int16_t/int32_t/int64_t, etc. */
#if (  (defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)) \
     || defined(__GNUC__) || defined(__INTEL_COMPILER) )
  /* C99 compatible compilers support int64_t etc.
   * but GCC and other compilers has the header even in C89/C90 mode
   * So we need to include more compilers here, see the list on
   * http://sourceforge.net/p/predef/wiki/Compilers/ */
  #include <inttypes.h>
#elif (defined(_MSC_VER) \
      || (defined(__BORLANDC__) && (__BORLANDC__ >= 0x520)))
  /* tested for Visual C++ 6.0 and Borland C++ 5.5 */
  typedef __int8              int8_t;
  typedef __int16             int16_t;
  typedef __int32             int32_t;
  typedef __int64             int64_t;
  typedef unsigned __int8     uint8_t;
  typedef unsigned __int16    uint16_t;
  typedef unsigned __int32    uint32_t;
  typedef unsigned __int64    uint64_t;
#elif defined(__unix__)
  /* a unix compiler is likely to have inttypes.h  */
  #include <inttypes.h>
#else
  /* note the following is a guess, long long is not supported
   * until a later version of visual C++ */
  typedef char                int8_t;
  typedef short               int16_t;
  typedef int                 int32_t;
  typedef long long           int64_t;
  typedef unsigned char       uint8_t;
  typedef unsigned short      uint16_t;
  typedef unsigned            uint32_t;
  typedef unsigned long long  uint64_t;
#endif


/* constant 64-bit integer */
#if defined(_MSC_VER) || defined(__BORLANDC__)
  #define CI64(x) (x ## i64)
  #define CU64(x) (x ## ui64)
#else
  #define CI64(x) (x ## ll)
  #define CU64(x) (x ## ull)
#endif


/* printf() format strings for integers
 * the macros PRId32, PRIu64, etc are defined by C99
 * we write the macros below just in case they are not defined */
#if defined(_MSC_VER) || defined(__BORLANDC__)
  #ifndef PRId32
  #define PRId32 "I32d"
  #endif
  #ifndef SCNd32
  #define SCNd32 "I32d"
  #endif
  #ifndef PRIi32
  #define PRIi32 "I32i"
  #endif
  #ifndef SCNi32
  #define SCNi32 "I32i"
  #endif
  #ifndef PRIu32
  #define PRIu32 "I32u"
  #endif
  #ifndef SCNu32
  #define SCNu32 "I32u"
  #endif
  #ifndef PRIo32
  #define PRIo32 "I32o"
  #endif
  #ifndef SCNo32
  #define SCNo32 "I32o"
  #endif
  #ifndef PRIx32
  #define PRIx32 "I32x"
  #endif
  #ifndef SCNx32
  #define SCNx32 "I32x"
  #endif
  #ifndef PRId64
  #define PRId64 "I64d"
  #endif
  #ifndef SCNd64
  #define SCNd64 "I64d"
  #endif
  #ifndef PRIi64
  #define PRIi64 "I64i"
  #endif
  #ifndef SCNi64
  #define SCNi64 "I64i"
  #endif
  #ifndef PRIu64
  #define PRIu64 "I64u"
  #endif
  #ifndef SCNu64
  #define SCNu64 "I64u"
  #endif
  #ifndef PRIo64
  #define PRIo64 "I64o"
  #endif
  #ifndef SCNo64
  #define SCNo64 "I64o"
  #endif
  #ifndef PRIx64
  #define PRIx64 "I64x"
  #endif
  #ifndef SCNx64
  #define SCNx64 "I64x"
  #endif
#else
  #ifndef PRId32
  #define PRId32 "d"
  #endif
  #ifndef SCNd32
  #define SCNd32 "d"
  #endif
  #ifndef PRIi32
  #define PRIi32 "i"
  #endif
  #ifndef SCNi32
  #define SCNi32 "i"
  #endif
  #ifndef PRIu32
  #define PRIu32 "u"
  #endif
  #ifndef SCNu32
  #define SCNu32 "u"
  #endif
  #ifndef PRIo32
  #define PRIo32 "o"
  #endif
  #ifndef SCNo32
  #define SCNo32 "o"
  #endif
  #ifndef PRIx32
  #define PRIx32 "x"
  #endif
  #ifndef SCNx32
  #define SCNx32 "x"
  #endif
  #ifndef PRId64
  #define PRId64 "lld"
  #endif
  #ifndef SCNd64
  #define SCNd64 "lld"
  #endif
  #ifndef PRIi64
  #define PRIi64 "lli"
  #endif
  #ifndef SCNi64
  #define SCNi64 "lli"
  #endif
  #ifndef PRIu64
  #define PRIu64 "llu"
  #endif
  #ifndef SCNu64
  #define SCNu64 "llu"
  #endif
  #ifndef PRIo64
  #define PRIo64 "llo"
  #endif
  #ifndef SCNo64
  #define SCNo64 "llo"
  #endif
  #ifndef PRIx64
  #define PRIx64 "llx"
  #endif
  #ifndef SCNx64
  #define SCNx64 "llx"
  #endif
#endif


/* print an error message */
INLINE void perrmsg__(const char *file, int line, const char *why,
    const char *fmt, va_list args)
{
  fprintf(stderr, "error: ");
  vfprintf(stderr, fmt, args);
  if (fmt[strlen(fmt) - 1] != '\n')
    fprintf(stderr, "\n"); /* add a new line if needed */
  if (file != NULL) fprintf(stderr, "file: %s\n", file);
  if (line >= 0) fprintf(stderr, "line: %d\n", line);
  if (why != NULL && strcmp(why, "1") != 0)
    fprintf(stderr, "cond: %s\n", why);
}


#ifdef HAVEVAM

INLINE void perrmsg_(const char *file, int line, const char *why,
    int cond, const char *fmt, ...)
{
  if (cond) {
    va_list args;
    va_start(args, fmt);
    perrmsg__(file, line, why, fmt, args);
    va_end(args);
    exit(1);
  }
}

#define die_if(cond, fmt, ...) \
  perrmsg_(__FILE__, __LINE__, #cond, cond, fmt, ## __VA_ARGS__)
#define fatal(fmt, ...)  die_if(1, fmt, ## __VA_ARGS__)

#else /* !HAVEVAM */

#define PERRMSG__(c) {                        \
  if ((#c[0] == '1' && #c[1] == '\0') || c) { \
    va_list args;                             \
    va_start(args, fmt);                      \
    perrmsg__(NULL, -1, NULL, fmt, args);     \
    va_end(args);                             \
    exit(1);                                  \
  } }
INLINE void die_if(int cond, const char *fmt, ...) PERRMSG__(cond)
INLINE void fatal(const char *fmt, ...) PERRMSG__(1)
#undef PERRMSG__

#endif /* HAVEVAM */


#ifndef xnew
#define xnew(x, n) { \
  size_t num_ = (size_t) (n); \
  die_if (num_ <= 0, \
    "cannot allocate %d objects for %s\n", (int) num_, #x); \
  die_if ((x = calloc(num_, sizeof(*(x)))) == NULL, \
    "no memory for %s x %d\n", #x, (int) num_); }
#endif


#ifndef xrenew
#define xrenew(x, n) { \
  size_t num_ = (size_t) (n); \
  char *xrenewptr__; \
  die_if (num_ <= 0, \
    "cannot allocate %d objects for %s\n", (int) num_, #x); \
  die_if ((xrenewptr__ = realloc(x, (num_)*sizeof(*(x)))) == NULL, \
    "no memory for %s x %d\n", #x, (int) num_); \
  x = (void *) xrenewptr__; }
#endif


#define xfopen(fp, fn, fmt, err) \
  if ((fp = fopen(fn, fmt)) == NULL) { \
    fprintf(stderr, "cannot open file %s with mode [%s]\n", fn, fmt); \
    err; }


/* check if file `fn' exists */
INLINE int fexists(const char *fn)
{
  FILE *fp;
  if ((fp = fopen(fn, "r")) == NULL) return 0;
  else { fclose(fp); return 1; }
}


/* copy file */
INLINE int copyfile(const char *fninp, const char *fnout)
{
  FILE *fpinp, *fpout;
#ifndef COPYFILE_BUFSZ
#define COPYFILE_BUFSZ (64*1024)
#endif
  unsigned char buf[COPYFILE_BUFSZ];
  size_t sz, tot = 0;

  if ((fpinp = fopen(fninp, "rb")) == NULL) {
    fprintf(stderr, "copyfile: cannot read file %s\n", fninp);
    return -1;
  }
  if ((fpout = fopen(fnout, "wb")) == NULL) {
    fprintf(stderr, "copyfile: cannot write file %s\n", fnout);
    fclose(fpinp);
    return -2;
  }
  while ((sz = fread(buf, sizeof(buf[1]), COPYFILE_BUFSZ, fpinp)) != 0) {
    tot += sz;
    /* note: sz may differ from COPYFILE_BUFSZ */
    if (sz != fwrite(buf, sizeof(buf[1]), sz, fpout))
      fprintf(stderr, "copyfile: error writing %s, byte %.0f\n", fnout, 1.*tot);
    if ( feof(fpinp) ) break;
  }
  fclose(fpinp);
  fclose(fpout);
  return 0;
}


/* swap two variables */
#define xtpswap(tp, x, y) { tp dum_; dum_ = (x); (x) = (y); (y) = dum_; }

#define intswap(x, y) xtpswap(int, x, y)

#define dblswap(x, y) xtpswap(double, x, y)

#define realswap(x, y) xtpswap(real, x, y)


INLINE int intmax(int x, int y) { return x > y ? x : y; }
INLINE int intmin(int x, int y) { return x < y ? x : y; }


/* confine x within [xmin, xmax] */
INLINE int intconfine(int x, int xmin, int xmax)
  { return x < xmin ? xmin : x > xmax ? xmax : x; }


INLINE int intsqr(int x) { return x * x; }


/* get the pair index from 0 to n*(n - 1)/2 - 1 */
INLINE int getpairindex(int i, int j, int n)
{
  die_if (i < 0 || i >= n || j < 0 || j >= n || i == j,
      "bad index error i %d, j %d, n %d\n", i, j, n);
  if (i > j) { int i1 = i; i = j; j = i1; }
  return n*i - (i + 1)*(i + 2)/2 + j;
}

/* return individual indices for a given pair index */
INLINE int parsepairindex(int id, int n, int *i, int *j)
{
  int i1, n1;
  die_if (id < 0 || id >= n*(n - 1)/2, "index %d too large for n %d\n", id, n);
  for (i1 = n - 2; i1 >= 0; i1--) {
    if (id >= (n1 = i1*n - i1*(i1 + 1)/2)) {
      *i = i1;
      *j = id - n1 + i1 + 1;
      return 0;
    }
  }
  return 1;
}


INLINE double dblmax(double x, double y) { return x > y ? x : y; }
INLINE double dblmin(double x, double y) { return x < y ? x : y; }


/* confine x within [xmin, xmax] */
INLINE double dblconfine(double x, double xmin, double xmax)
{ return x < xmin ? xmin : x > xmax ? xmax : x; }


INLINE double dblsqr(double x) { return x * x; }


/* sqrt(x*x + y*y) */
INLINE double dblhypot(double x, double y)
{
  double t;
  x = fabs(x);
  y = fabs(y);
  if (x <= 0.) return y;
  else if (y <= 0.) return x;
  if (x < y) t = x, x = y, y = t;
  t = y/x;
  return x*sqrt(1 + t*t);
}


/* round x to a multiple dx  */
INLINE double dblround(double x, double dx)
{
  if (x*dx > 0) return dx * (int)(x/dx + (.5 - DBL_EPSILON));
  else return -dx * (int)(-x/dx + (.5 - DBL_EPSILON));
}


/* convert to double to integer */
INLINE int dbl2int(double x)
{
  return (int) ((x < 0) ? (x - .5) : (x + .5));
}


INLINE void dblcleararr(double *x, int n)
{
  int i; for (i = 0; i < n; i++) x[i] = 0.0;
}


#ifdef HAVEREAL
INLINE real realmax(real x, real y) { return x > y ? x : y; }
INLINE real realmin(real x, real y) { return x < y ? x : y; }
/* confine x within [xmin, xmax] */
INLINE real realconfine(real x, real xmin, real xmax)
{ return x < xmin ? xmin : x > xmax ? xmax : x; }
#endif


#ifndef LNADD_DEFINED
#define LNADD_DEFINED
#define LN_BIG 50.0

/* log(exp(a) + exp(b)) */
INLINE double lnadd(double a, double b)
{
  double c;
  if (a < b) { c = a; a = b; b = c; } /* ensure a >= b */
  return ((c = a - b) > LN_BIG) ? a : a + log(1 + exp(-c));
}

/* log(exp(a) - exp(b)), only works for a > b */
INLINE double lndif(double a, double b)
{
  double c;
  die_if (a < b, "lndif: %g < %g\n", a, b);
  return ((c = a - b) > LN_BIG) ? a : a + log(1 - exp(-c));
}

/* log(exp(a)+b) */
INLINE double lnaddn(double a, double b)
{
  return (a > LN_BIG) ? a : a + log(1 + b*exp(-a));
}

#undef LN_BIG
#endif  /* LNADD_DEFINED */


#define cisalnum(c)   isalnum((unsigned char)(c))
#define cisalpha(c)   isalpha((unsigned char)(c))
#define cisdigit(c)   isdigit((unsigned char)(c))
#define cisxdigit(c)  isxdigit((unsigned char)(c))
#define cisprint(c)   isprint((unsigned char)(c))
#define cisspace(c)   isspace((unsigned char)(c))
#define cislower(c)   islower((unsigned char)(c))
#define cisupper(c)   isupper((unsigned char)(c))
#define ctolower(c)   (char) tolower((unsigned char)(c))
#define ctoupper(c)   (char) toupper((unsigned char)(c))


/* string manipulation */
#define ZSTR_XSPACEL  0x0001
#define ZSTR_XSPACER  0x0002
#define ZSTR_XSPACE   (ZSTR_XSPACEL|ZSTR_XSPACER)
#define ZSTR_COPY     0x0004
#define ZSTR_CAT      0x0008
#define ZSTR_CASE     0x0100
#define ZSTR_UPPER_   0x0200
#define ZSTR_UPPER    (ZSTR_CASE|ZSTR_UPPER_)
#define ZSTR_LOWER    ZSTR_CASE


/* remove leading and trailing spaces */
#define strip(s)  stripx(s, ZSTR_XSPACE)
#define lstrip(s) stripx(s, ZSTR_XSPACEL)
#define rstrip(s) stripx(s, ZSTR_XSPACER)
INLINE char *stripx(char *s, unsigned flags)
{
  char *p;

  if (flags & ZSTR_XSPACEL) { /* remove leading spaces */
    for (p = s; cisspace(*p); p++) ;
    if (*p == '\0') *s = '\0';
    else memmove(s, p, strlen(p) + 1);
  }
  if (flags & ZSTR_XSPACER) /* remove trailing spaces */
    for (p = s + strlen(s) - 1; p >= s && cisspace(*p); p--)
      *p = '\0';
  return s;
}


/* in the follows, size_s means the buffer size of s, i.e., sizeof(s) for static strings */
/* copy the string and convert it to upper/lower case */
#define strcpy2u(s, t, size_s) strcnv(s, t, size_s - 1, ZSTR_COPY|ZSTR_UPPER)
#define strcpy2l(s, t, size_s) strcnv(s, t, size_s - 1, ZSTR_COPY|ZSTR_LOWER)
#define strcpy_sf(s, t, size_s) strcnv(s, t, size_s - 1, ZSTR_COPY)
#define substr(s, t, start, len) strcnv(s, t+start, len, ZSTR_COPY)
/* concatenate strings, the last parameter is the buffer size of s,
 * unlike strncat(), in which it's the number of characters from *t* to be copied.  */
#define strcat_sf(s, t, size_s) strcnv(s, t, size_s - 1, ZSTR_CAT)


/* safely copy/cat strings with case conversion
 * unlike strncpy(), s is always null-terminated on return: it copies at most
 * len non-blank characters, i.e., s[len] = '\0' for the longest output */
INLINE char *strcnv(char *s, const char *t, size_t len, unsigned flags)
{
  size_t i = 0, j;
  unsigned docase = flags & ZSTR_CASE, up = flags & ZSTR_UPPER_;

  if (len == 0 || s == NULL || t == NULL) return s;
  if (flags & ZSTR_CAT) while(s[i]) i++;
  for (j = 0; i < len; i++, j++) {
    if (docase && t[j]) {
      if (up) s[i] = (char) (unsigned char) toupper((unsigned char) t[j]);
      else    s[i] = (char) (unsigned char) tolower((unsigned char) t[j]);
    } else s[i] = t[j];
    if (t[j] == 0) break;
  }
  if (i == len) s[i] = '\0';
  if (flags & ZSTR_XSPACE) stripx(s, flags); /* call strip */
  return s;
}


/* compare strings without case */
#define strcmpnc(s, t) strncmpnc(s, t, INT_MAX)
INLINE int strncmpnc(const char *s, const char *t, int n)
{
  int i, cs, ct;

  if (s == NULL || t == NULL) return 0;
  for (i = 0; ; i++) {
    if (i >= n) return 0;
    cs = s[i];
    ct = t[i];
    if (cs == 0 || ct == 0) break;
    cs = toupper( (unsigned char) cs );
    ct = toupper( (unsigned char) ct );
    if (cs != ct) break;
  }
  return cs - ct;
}


#define strcmpfuzzy(s, t) strncmpfuzzy(s, t, INT_MAX)

/* comparison, ignoring cases, spaces and punctuations */
INLINE int strncmpfuzzy(const char *s, const char *t, int n)
{
  int is, it, i;
  const char cset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789()[]{}";

  for ( i = 0; i < n; s++, t++, i++ ) {
    while ( *s != '\0' && strchr(cset, *s) == NULL ) s++;
    while ( *t != '\0' && strchr(cset, *t) == NULL ) t++;
    is = tolower( (unsigned char) (*s) );
    it = tolower( (unsigned char) (*t) );
    if ( is != it ) return is - it;
    if ( *s == '\0' ) return 0;
  }
  return 0;
}


/* check if `s' starts with `t' */
#define strstartswith(s, t)       (strncmp(s, t, sizeof(t))       == 0)
#define strstartswithnc(s, t)     (strncmpnc(s, t, sizeof(t))     == 0)
#define strstartswithfuzzy(s, t)  (strncmpfuzzy(s, t, sizeof(t))  == 0)


/* join strings */
INLINE char *strjoin(char *s, int size,
    const char **arr, int n, const char *com)
{
  int i, li, lc, sz = 0;

  if ( com == NULL ) com = " ";
  lc = strlen(com);
  s[0] = '\0';
  for ( i = 0; i < n; i++ ) {
    li = strlen(arr[i]);
    if ( (sz += li) < size ) strcat(s, arr[i]);
    if ( i == n - 1 ) break;
    if ( (sz += lc) < size ) strcat(s, com);
  }
  return s;
}


#endif /* ZCOM_UTIL__ */
#endif /* ZCOM_UTIL */





#ifdef  ZCOM_BITS
#ifndef ZCOM_BITS__
#define ZCOM_BITS__


/* these masks can be generated from the helper python script mkmask.py */
STRCLS uint32_t bitsmask32_[33] = {0,
 0x00000001, 0x00000003, 0x00000007, 0x0000000f,
 0x0000001f, 0x0000003f, 0x0000007f, 0x000000ff,
 0x000001ff, 0x000003ff, 0x000007ff, 0x00000fff,
 0x00001fff, 0x00003fff, 0x00007fff, 0x0000ffff,
 0x0001ffff, 0x0003ffff, 0x0007ffff, 0x000fffff,
 0x001fffff, 0x003fffff, 0x007fffff, 0x00ffffff,
 0x01ffffff, 0x03ffffff, 0x07ffffff, 0x0fffffff,
 0x1fffffff, 0x3fffffff, 0x7fffffff, 0xffffffff};


STRCLS uint32_t invbitsmask32_[33] = {0xffffffff,
 0xfffffffe, 0xfffffffc, 0xfffffff8, 0xfffffff0,
 0xffffffe0, 0xffffffc0, 0xffffff80, 0xffffff00,
 0xfffffe00, 0xfffffc00, 0xfffff800, 0xfffff000,
 0xffffe000, 0xffffc000, 0xffff8000, 0xffff0000,
 0xfffe0000, 0xfffc0000, 0xfff80000, 0xfff00000,
 0xffe00000, 0xffc00000, 0xff800000, 0xff000000,
 0xfe000000, 0xfc000000, 0xf8000000, 0xf0000000,
 0xe0000000, 0xc0000000, 0x80000000,        0x0};


/* make the ith bit */
#define MKBIT32(n) (((uint32_t) 1u) << (uint32_t) (n))

/* make a mask with the lowest n bits being 1s, other bits being 0s */
#define MKBITSMASK32(n) bitsmask32_[n]

/* make a mask with the lowest n bits being 0s, other bits being 1s */
#define MKINVBITSMASK32(n) invbitsmask32_[n]


/* if the lowest two bits of x are zeros, and x has n nonzero bits,
 * then x, x+1, x+2, x+3 have respectivly n, n+1, n+1, n+2 nonzero bits */
#define BITB2_(n)        n,         n+1,         n+1,         n+2
#define BITB4_(n) BITB2_(n), BITB2_(n+1), BITB2_(n+1), BITB2_(n+2)
#define BITB6_(n) BITB4_(n), BITB4_(n+1), BITB4_(n+1), BITB4_(n+2)

/* how many bits in 0..255 */
STRCLS const unsigned char bits256_[256] = {
  BITB6_(0), BITB6_(1), BITB6_(1), BITB6_(2) };


/* count the number of 1 bits in x
 * http://graphics.stanford.edu/~seander/bithacks.html#CountBitsSetTable */
#define BITCOUNT8(x) bits256_[ ((unsigned char *)&(x))[0] ]

#define BITCOUNT16(x) ( BITCOUNT8(x) \
  + bits256_[ ((unsigned char *)&(x))[1] ] )

#define BITCOUNT24(x) ( BITCOUNT16(x) \
  + bits256_[ ((unsigned char *)&(x))[2] ] )

#define BITCOUNT32(x) ( BITCOUNT24(x) \
  + bits256_[ ((unsigned char *)&(x))[3] ] )

#define BITCOUNT40(x) ( BITCOUNT32(x) \
  + bits256_[ ((unsigned char *)&(x))[4] ] )

#define BITCOUNT48(x) ( BITCOUNT40(x) \
  + bits256_[ ((unsigned char *)&(x))[5] ] )

#define BITCOUNT56(x) ( BITCOUNT48(x) \
  + bits256_[ ((unsigned char *)&(x))[6] ] )

#define BITCOUNT64(x) ( BITCOUNT56(x) \
  + bits256_[ ((unsigned char *)&(x))[7] ] )

INLINE int bitcount32(uint32_t x) { return BITCOUNT32(x); }


/* invert the lowest n bits */
#define BITNINVL32(x, n) ((x) ^ MKBITSMASK32(n))

INLINE uint32_t bitninvl32(uint32_t x, int n)
{ return BITNINVL32(x, n); }

/* invert the highest n bits */
#define BITNINVH32(x, n) ((x) ^ MKINVBITSMASK32(32 - n))

INLINE uint32_t bitninvh32(uint32_t x, int n)
{ return BITNINVH32(x, n); }


#define BITR2_(n)        n,         n + 2*64,         n + 1*64,         n + 3*64
#define BITR4_(n) BITR2_(n), BITR2_(n + 2*16), BITR2_(n + 1*16), BITR2_(n + 3*16)
#define BITR6_(n) BITR4_(n), BITR4_(n + 2*4 ), BITR4_(n + 1*4 ), BITR4_(n + 3*4 )

STRCLS const unsigned char bitrev256_[256] = {
  BITR6_(0), BITR6_(2), BITR6_(1), BITR6_(3) };

/* reverse bits a = rev(b) */
#define BITREV32(a, b) { \
  ((unsigned char *)&(a))[0] = bitrev256_[ ((unsigned char *)&(b))[3] ]; \
  ((unsigned char *)&(a))[1] = bitrev256_[ ((unsigned char *)&(b))[2] ]; \
  ((unsigned char *)&(a))[2] = bitrev256_[ ((unsigned char *)&(b))[1] ]; \
  ((unsigned char *)&(a))[3] = bitrev256_[ ((unsigned char *)&(b))[0] ]; }

INLINE uint32_t bitrev32(uint32_t x)
{ uint32_t c; BITREV32(c, x) return c; }


STRCLS const int bruijn32_[32] =
  { 0, 1, 28, 2, 29, 14, 24, 3, 30, 22, 20, 15, 25, 17, 4, 8,
    31, 27, 13, 23, 21, 19, 16, 7, 26, 12, 18, 6, 11, 5, 10, 9};

#define BIT2ID32(b) bruijn32_[((b) * 0x077CB531) >> 27]


/* macro version of bitfirstlow(); */
#define BITFIRSTLOW32(id, x, b) { \
  (b) = (x) & (-(x)); \
  (id) = BIT2ID32(b); }

/* find the index of the lowest 1 bit
 * on return *b is the nonzero bit
 * http://graphics.stanford.edu/~seander/bithacks.html#ZerosOnRightMultLookup
 * ``Using de Bruijn Sequences to Index 1 in a Computer Word''
 * by Charles E. Leiserson, Harald Prokof, and Keith H. Randall.
 * http://supertech.csail.mit.edu/papers/debruijn.pdf */
INLINE int bitfirstlow32(uint32_t x, uint32_t *b)
{
  (*b) = x & (-x); /* such that only the lowest 1-bit survives */
  return BIT2ID32(*b);
}


/* find the least significant nonzero bit
 * http://en.wikipedia.org/wiki/Find_first_set#Tool_and_library_support
 * http://chessprogramming.wikispaces.com/BitScan */
#ifdef __INTEL_COMPILER

/* directly map to the intrinsic function
 * use it only when you are sure x != 0
 * the intrinsic for the most significant nonzero bit
 * is _bit_scan_reverse(x) */
#define BITFIRSTNZ32(x)  _bit_scan_forward(x)
#define BITFIRST32(id, x) id = (x) ? BITFIRSTNZ32(x) : 0;
#define bitfirst32(x) ((x) ? BITFIRSTNZ32(x) : 0)

#elif defined(__GNUC__) && !defined(__INTEL_COMPILER)

/* the intrinsic for the least significant nonzero bit
 * is __builtin_clz */
#define BITFIRSTNZ32(x)  __builtin_ctz(x)
#define BITFIRST32(id, x) id = (x) ? BITFIRSTNZ32(x) : 0;
#define bitfirst32(x)  ((x) ? BITFIRSTNZ32(x) : 0)

#else /* general */

#define BITFIRSTNZ32(x)   bitfirst32(x)
#define BITFIRST32(id, x) { uint32_t b32_; BITFIRSTLOW32(id, x, b32_) }

/* index of nonzero bit */
INLINE int bitfirst32(uint32_t x)
{
  uint32_t b;
  return bitfirstlow32(x, &b);
}

#endif /* defined(__INTEL_COMPILER/__GNUC__) */


STRCLS uint64_t bitsmask64_[65] = {0,
 CU64(0x0000000000000001), CU64(0x0000000000000003), CU64(0x0000000000000007), CU64(0x000000000000000f),
 CU64(0x000000000000001f), CU64(0x000000000000003f), CU64(0x000000000000007f), CU64(0x00000000000000ff),
 CU64(0x00000000000001ff), CU64(0x00000000000003ff), CU64(0x00000000000007ff), CU64(0x0000000000000fff),
 CU64(0x0000000000001fff), CU64(0x0000000000003fff), CU64(0x0000000000007fff), CU64(0x000000000000ffff),
 CU64(0x000000000001ffff), CU64(0x000000000003ffff), CU64(0x000000000007ffff), CU64(0x00000000000fffff),
 CU64(0x00000000001fffff), CU64(0x00000000003fffff), CU64(0x00000000007fffff), CU64(0x0000000000ffffff),
 CU64(0x0000000001ffffff), CU64(0x0000000003ffffff), CU64(0x0000000007ffffff), CU64(0x000000000fffffff),
 CU64(0x000000001fffffff), CU64(0x000000003fffffff), CU64(0x000000007fffffff), CU64(0x00000000ffffffff),
 CU64(0x00000001ffffffff), CU64(0x00000003ffffffff), CU64(0x00000007ffffffff), CU64(0x0000000fffffffff),
 CU64(0x0000001fffffffff), CU64(0x0000003fffffffff), CU64(0x0000007fffffffff), CU64(0x000000ffffffffff),
 CU64(0x000001ffffffffff), CU64(0x000003ffffffffff), CU64(0x000007ffffffffff), CU64(0x00000fffffffffff),
 CU64(0x00001fffffffffff), CU64(0x00003fffffffffff), CU64(0x00007fffffffffff), CU64(0x0000ffffffffffff),
 CU64(0x0001ffffffffffff), CU64(0x0003ffffffffffff), CU64(0x0007ffffffffffff), CU64(0x000fffffffffffff),
 CU64(0x001fffffffffffff), CU64(0x003fffffffffffff), CU64(0x007fffffffffffff), CU64(0x00ffffffffffffff),
 CU64(0x01ffffffffffffff), CU64(0x03ffffffffffffff), CU64(0x07ffffffffffffff), CU64(0x0fffffffffffffff),
 CU64(0x1fffffffffffffff), CU64(0x3fffffffffffffff), CU64(0x7fffffffffffffff), CU64(0xffffffffffffffff)};

STRCLS uint64_t invbitsmask64_[65] = {CU64(0xffffffffffffffff),
 CU64(0xfffffffffffffffe), CU64(0xfffffffffffffffc), CU64(0xfffffffffffffff8), CU64(0xfffffffffffffff0),
 CU64(0xffffffffffffffe0), CU64(0xffffffffffffffc0), CU64(0xffffffffffffff80), CU64(0xffffffffffffff00),
 CU64(0xfffffffffffffe00), CU64(0xfffffffffffffc00), CU64(0xfffffffffffff800), CU64(0xfffffffffffff000),
 CU64(0xffffffffffffe000), CU64(0xffffffffffffc000), CU64(0xffffffffffff8000), CU64(0xffffffffffff0000),
 CU64(0xfffffffffffe0000), CU64(0xfffffffffffc0000), CU64(0xfffffffffff80000), CU64(0xfffffffffff00000),
 CU64(0xffffffffffe00000), CU64(0xffffffffffc00000), CU64(0xffffffffff800000), CU64(0xffffffffff000000),
 CU64(0xfffffffffe000000), CU64(0xfffffffffc000000), CU64(0xfffffffff8000000), CU64(0xfffffffff0000000),
 CU64(0xffffffffe0000000), CU64(0xffffffffc0000000), CU64(0xffffffff80000000), CU64(0xffffffff00000000),
 CU64(0xfffffffe00000000), CU64(0xfffffffc00000000), CU64(0xfffffff800000000), CU64(0xfffffff000000000),
 CU64(0xffffffe000000000), CU64(0xffffffc000000000), CU64(0xffffff8000000000), CU64(0xffffff0000000000),
 CU64(0xfffffe0000000000), CU64(0xfffffc0000000000), CU64(0xfffff80000000000), CU64(0xfffff00000000000),
 CU64(0xffffe00000000000), CU64(0xffffc00000000000), CU64(0xffff800000000000), CU64(0xffff000000000000),
 CU64(0xfffe000000000000), CU64(0xfffc000000000000), CU64(0xfff8000000000000), CU64(0xfff0000000000000),
 CU64(0xffe0000000000000), CU64(0xffc0000000000000), CU64(0xff80000000000000), CU64(0xff00000000000000),
 CU64(0xfe00000000000000), CU64(0xfc00000000000000), CU64(0xf800000000000000), CU64(0xf000000000000000),
 CU64(0xe000000000000000), CU64(0xc000000000000000), CU64(0x8000000000000000), CU64(0x0000000000000000)};


/* make the ith bit */
#define MKBIT64(n) (((uint64_t) 1u) << (uint64_t) (n))

/* make a mask with the lowest n bits being 1s, other bits being 0s */
#define MKBITSMASK64(n) bitsmask64_[n]

/* make a mask with the lowest n bits being 0s, other bits being 1s */
#define MKINVBITSMASK64(n) invbitsmask64_[n]


INLINE int bitcount64(uint64_t x) { return BITCOUNT64(x); }


/* invert the lowest k bits */
#define BITNINVL64(x, n) ((x) ^ MKBITSMASK64(n))

INLINE uint64_t bitninvl64(uint64_t x, int n)
{ return BITNINVL64(x, n); }

/* invert the highest k bits */
#define BITNINVH64(x, n) ((x) ^ MKINVBITSMASK64(64 - n))

INLINE uint64_t bitninvh64(uint64_t x, int n)
{ return BITNINVH64(x, n); }


/* reverse bits a = rev(b) */
#define BITREV64(a, b) { \
  ((unsigned char *)&(a))[0] = bitrev256_[ ((unsigned char *)&(b))[7] ]; \
  ((unsigned char *)&(a))[1] = bitrev256_[ ((unsigned char *)&(b))[6] ]; \
  ((unsigned char *)&(a))[2] = bitrev256_[ ((unsigned char *)&(b))[5] ]; \
  ((unsigned char *)&(a))[3] = bitrev256_[ ((unsigned char *)&(b))[4] ]; \
  ((unsigned char *)&(a))[4] = bitrev256_[ ((unsigned char *)&(b))[3] ]; \
  ((unsigned char *)&(a))[5] = bitrev256_[ ((unsigned char *)&(b))[2] ]; \
  ((unsigned char *)&(a))[6] = bitrev256_[ ((unsigned char *)&(b))[1] ]; \
  ((unsigned char *)&(a))[7] = bitrev256_[ ((unsigned char *)&(b))[0] ]; }

INLINE uint64_t bitrev64(uint64_t x)
{ uint64_t c; BITREV64(c, x) return c; }


STRCLS const int bruijn64_[64] =
  {  0,  1,  2,  7,  3, 13,  8, 19,  4, 25, 14, 28,  9, 34, 20, 40,
     5, 17, 26, 38, 15, 46, 29, 48, 10, 31, 35, 54, 21, 50, 41, 57,
    63,  6, 12, 18, 24, 27, 33, 39, 16, 37, 45, 47, 30, 53, 49, 56,
    62, 11, 23, 32, 36, 44, 52, 55, 61, 22, 43, 51, 60, 42, 59, 58};

#define BIT2ID64(b) bruijn64_[((b) * CU64(0x218A392CD3D5DBF)) >> 58]


/* macro version of bitfirstlow(); */
#define BITFIRSTLOW64(id, x, b) { \
  (b) = (x) & (-(x)); \
  (id) = BIT2ID64(b); }

/* find the index of the lowest 1 bit
 * on return *b is the nonzero bit
 * http://graphics.stanford.edu/~seander/bithacks.html#ZerosOnRightMultLookup
 * ``Using de Bruijn Sequences to Index 1 in a Computer Word''
 * by Charles E. Leiserson, Harald Prokof, and Keith H. Randall.
 * http://supertech.csail.mit.edu/papers/debruijn.pdf */
INLINE int bitfirstlow64(uint64_t x, uint64_t *b)
{
  (*b) = x & (-x); /* such that only the lowest 1-bit survives */
  return BIT2ID64(*b);
}


#define BITFIRSTNZ64(x) bitfirst64(x)

#define BITFIRST64(id, x) { uint64_t b64_; BITFIRSTLOW64(id, x, b64_) }

/* index of nonzero bit */
INLINE int bitfirst64(uint64_t x)
{
  uint64_t b;
  return bitfirstlow64(x, &b);
}


#ifndef WORDBITS_
#define WORDBITS_ 32
#endif /* defined(WORDBITS_) */


/* one word operations */
#if WORDBITS_ == 64

  #ifndef BITS_WORD_T
  #define BITS_WORD_T uint64_t
  #endif
  #define MKBIT(n)                MKBIT64(n)
  #define MKBITSMASK(n)           MKBITSMASK64(n)
  #define MKINVBITSMASK(n)        MKINVBITSMASK64(n)
  #define BITCOUNT(x)             BITCOUNT64(x)
  #define bitcount(x)             bitcount64(x)
  #define BITNINVL(x, k)          BITNINVL64(x, k)
  #define bitninvl(x, k)          bitninvl64(x, k)
  #define BITNINVH(x, k)          BITNINVH64(x, k)
  #define bitninvh(x, k)          bitninvh64(x, k)
  #define BITREV(x)               BITREV64(x)
  #define bitrev(x)               bitrev64(x)
  #define BIT2ID(b)               BIT2ID64(b)
  #define BITFIRSTLOW(id, x, b)   BITFIRSTLOW64(id, x, b)
  #define bitfirstlow(x, b)       bitfirstlow64(x, b)
  #define BITFIRSTNZ(x)           BITFIRSTNZ64(x)
  #define BITFIRST(id, x)         BITFIRST64(id, x)
  #define bitfirst(x)             bitfirst64(x)

#elif WORDBITS_ == 32

  #ifndef BITS_WORD_T
  #define BITS_WORD_T uint32_t
  #endif
  #define MKBIT(n)                MKBIT32(n)
  #define MKBITSMASK(n)           MKBITSMASK32(n)
  #define MKINVBITSMASK(n)        MKINVBITSMASK32(n)
  #define BITCOUNT(x)             BITCOUNT32(x)
  #define bitcount(x)             bitcount32(x)
  #define BITNINVL(x, k)          BITNINVL32(x, k)
  #define bitninvl(x, k)          bitninvl32(x, k)
  #define BITNINVH(x, k)          BITNINVH32(x, k)
  #define bitninvh(x, k)          bitninvh32(x, k)
  #define BITREV(x)               BITREV32(x)
  #define bitrev(x)               bitrev32(x)
  #define BIT2ID(b)               BIT2ID32(b)
  #define BITFIRSTLOW(id, x, b)   BITFIRSTLOW32(id, x, b)
  #define bitfirstlow(x, b)       bitfirstlow32(x, b)
  #define BITFIRSTNZ(x)           BITFIRSTNZ32(x)
  #define BITFIRST(id, x)         BITFIRST32(id, x)
  #define bitfirst(x)             bitfirst32(x)

#else

  #error bad WORDBITS_ definition

#endif /* WORDBITS_ == 32 */


/* multiple-word bit-set operations */

#if WORDBITS_ == 32
  #define BITS_GETNW(n)      (((n) + 31) >> 5)
  #define BITS_GETNQ(n)      ((n) >> 5)            /* n / 32 */
  #define BITS_GETNR(n)      ((n) & 0x1f)          /* n % 32 */
#elif WORDBITS_ == 64
  #define BITS_GETNW(n)      (((n) + 63) >> 6)
  #define BITS_GETNQ(n)      ((n) >> 6)            /* n / 64 */
  #define BITS_GETNR(n)      ((n) & 0x3f)          /* n % 64 */
#else
  /* get the number of words to represent n elements */
  #define BITS_GETNW(n)      (((n) + WORDBITS_ - 1) / WORDBITS_)
  #define BITS_GETNQ(n)      ((n) / WORDBITS_)
  #define BITS_GETNR(n)      ((n) % WORDBITS_)
#endif
#define BITS_GETNB(n)      MKBIT( BITS_GETNR(n) )


#define BITS_CPY(a, b, nw) { int iw_; \
  for (iw_ = 0; iw_ < nw; iw_++) \
    a[iw_] = b[iw_]; }

#define BITS_CLEAR(bs, nw) { int iw_; \
  for (iw_ = 0; iw_ < nw; iw_++) (bs)[iw_] = 0; }

#define BITS_MKBIT(i, bi, iq) { iq = BITS_GETNQ(i), bi = MKBIT(DG_IR(i)); }
/* construct the set `bs' with a single vertex */
#define BITS_ONEBIT(bs, nw, bi, iq) { BITS_CLEAR(bs, nw); bs[iq] = bi; }

/* make a mask for the lowest k elements, clear higher bits up to nw */
#define BITS_MKBITSMASK(bs, k, nw) { int iw_; \
  int kq_ = BITS_GETNQ(k), kr_ = BITS_GETNR(k); \
  for (iw_ = 0; iw_ < kq_; iw_++) \
    (bs)[iw_] = MKINVBITSMASK(0); \
  if (kr_ != 0) (bs)[kq_++] = MKBITSMASK(kr_); \
  for (iw_ = kq_; iw_ < nw; iw_++) \
    (bs)[iw_] = 0; }

INLINE BITS_WORD_T *bits_mkbitsmask(BITS_WORD_T *bs, int k, int nw)
{ BITS_MKBITSMASK(bs, k, nw) return bs; }

/* a similar set of macros BITS_MKINVSET() are defined later
 * after we have defined BITS_REMOVE() */


#define BITS_NONZERO(nz, bs, nw) { int iw_; \
  for (nz = 0, iw_ = 0; iw_ < nw; iw_++) \
    if ( (bs)[iw_] ) nz = 1; }

INLINE int bits_nonzero(BITS_WORD_T *bs, int nw)
{  int nz; BITS_NONZERO(nz, bs, nw) return nz; }

#define bits_iszero(bs, nw) ( !bits_nonzero(bs, nw) )

#define BITS_NOTEQUAL(ne, a, b, nw) { int iw_; \
  for (ne = 0, iw_ = 0; iw_ < nw; iw_++) \
    if ( (a)[iw_] != (b)[iw_] ) ne = 1; }

INLINE int bits_notequal(BITS_WORD_T *a, BITS_WORD_T *b, int nw)
{ int ne; BITS_NOTEQUAL(ne, a, b, nw) return ne; }

#define bits_equal(a, b, nw) ( !bits_notequal(a, b, nw) )

#define BITS_COUNT(cnt, bs, nw) { int iw_; \
  for (cnt = 0, iw_ = 0; iw_ < nw; iw_++) \
    cnt += bitcount( (bs)[iw_] ); }

INLINE int bits_count(BITS_WORD_T *bs, int nw) \
{ int cnt; BITS_COUNT(cnt, bs, nw) return cnt; }

/* invert the lowest n bits of b, keep the rest */
#define BITS_NINV(a, b, n, nw) { int iw_; \
  for (iw_ = 0; iw_ < nw - 1; iw_++) \
    (a)[iw_] = ~(b)[iw_]; \
  (a)[iw_] = BITNINVL((b)[iw_], n - iw_ * WORDBITS_); }


/* save the bit of `bs' corresponding to the first element to `b'
 * `bs' is a set, `b' is a word, `bq' is the word offset */
#define BITS_FIRSTBIT(bs, nw, b, bq) { \
  BITS_WORD_T w_; \
  (b) = 0; \
  for (bq = 0; bq < nw; bq++) { \
    if ((w_ = (bs)[bq]) != 0) { \
      (b) = w_ & (-w_); \
      break; \
    } } }

/* save the index of the first element to `id'
 * and the bit corresponding to `id' is `b'
 * `bs' is a set, `b' is a word, `bq' is the word offset */
#define BITS_FIRSTLOW(id, bs, nw, b, bq) { \
  BITS_WORD_T w_; \
  b = 0; id = 0; \
  for (bq = 0; bq < nw; bq++) { \
    if ((w_ = (bs)[bq]) != 0) { \
      BITFIRSTLOW(id, w_, b); \
      id += bq * WORDBITS_; \
      break; \
    } } }

/* return the index of the first element in the set */
INLINE int bits_first(BITS_WORD_T *bs, int nw)
{
  BITS_WORD_T b;
  int id, bq;
  BITS_FIRSTLOW(id, bs, nw, b, bq);
  return id;
}

/* assuming `bs' contains a single bit, return the index */
INLINE int bits_bit2id(BITS_WORD_T *bs, int nw)
{
  BITS_WORD_T b;
  int bq;

  for (bq = 0; bq < nw; bq++)
    if ((b = bs[bq]) != 0)
      return bq * WORDBITS_ * BIT2ID(b);
  return 0;
}


/* bitwise/set operations */
/* a ^= b */
#define BITS_XOR(a, b, nw) { int iw_; \
  for (iw_ = 0; iw_ < nw; iw_++) (a)[iw_] ^= (b)[iw_]; }

#define BITS_XOR1(a, b, iq)     (a)[iq] ^= b;

/* a = b ^ c */
#define BITS_XOR2(a, b, c, nw) { int iw_; \
  for (iw_ = 0; iw_ < nw; iw_++) \
    (a)[iw_] = (b)[iw_] ^ (c)[iw_]; }

INLINE BITS_WORD_T *bits_xor2(BITS_WORD_T *a, BITS_WORD_T *b, BITS_WORD_T *c, int nw)
{ BITS_XOR2(a, b, c, nw); return a; }

/* a |= b */
#define BITS_OR(a, b, nw) { int iw_; \
  for (iw_ = 0; iw_ < nw; iw_++) (a)[iw_] |= (b)[iw_]; }

#define BITS_OR1(a, b, iq)      (a)[iq] |= b;

/* a = b | c */
#define BITS_OR2(a, b, c, nw) { int iw_; \
  for (iw_ = 0; iw_ < nw; iw_++) \
    (a)[iw_] = (b)[iw_] | (c)[iw_]; }

INLINE BITS_WORD_T *bits_or2(BITS_WORD_T *a, BITS_WORD_T *b, BITS_WORD_T *c, int nw)
{ BITS_OR2(a, b, c, nw); return a; }

/* a &= b */
#define BITS_AND(a, b, nw) { int iw_; \
  for (iw_ = 0; iw_ < nw; iw_++) \
    (a)[iw_] &= (b)[iw_]; }

#define BITS_AND1(a, b, iq)     (a)[iq] &= b;

/* a = b & c */
#define BITS_AND2(a, b, c, nw) { int iw_; \
  for (iw_ = 0; iw_ < nw; iw_++) \
    (a)[iw_] = (b)[iw_] & (c)[iw_]; }

INLINE BITS_WORD_T *bits_and2(BITS_WORD_T *a, BITS_WORD_T *b, BITS_WORD_T *c, int nw)
{ BITS_AND2(a, b, c, nw); return a; }

/* a &= ~b or a -= b */
#define BITS_MINUS(a, b, nw) { int iw_; \
  for (iw_ = 0; iw_ < nw; iw_++) \
    (a)[iw_] &= ~(b)[iw_]; }

#define BITS_MINUS1(a, b, iq)  (a)[iq] &= ~(b);

/* a = b & ~c or a = b - c */
#define BITS_MINUS2(a, b, c, nw) { int iw_; \
  for (iw_ = 0; iw_ < nw; iw_++) \
    (a)[iw_] = (b)[iw_] & ~(c)[iw_]; }

/* a = b & ~c or a = b - c */
INLINE BITS_WORD_T *bits_minus2(BITS_WORD_T *a, BITS_WORD_T *b, BITS_WORD_T *c, int nw)
{ BITS_MINUS2(a, b, c, nw) return a; }


/* add element `i' into the set `bs' */
#define BITS_ADD(bs, i)         BITS_OR1(bs, BITS_GETNB(i), BITS_GETNQ(i))

/* remove element `i' from the set `bs' */
#define BITS_REMOVE(bs, i)      BITS_MINUS1(bs, BITS_GETNB(i), BITS_GETNQ(i))

/* flip the state of element `i' in the set `bs' */
#define BITS_FLIP(bs, i)        BITS_XOR1(bs, BITS_GETNB(i), BITS_GETNQ(i))

/* test if the set `bs' has element `i' */
#define BITS_HAS(bs, i)         (int) (((bs)[BITS_GETNQ(i)] >> BITS_GETNR(i)) & 0x1)

/* test if the set `bs' has bit `bi' at offset `iq' */
#define BITS_HASBIT(bs, bi, iq) (((bs)[iq] & (bi)) != 0)

/* right shift one bit */
#define BITS_RSHIFT1(a, b, nw) { int iw_; \
  for (iw_ = 0; iw_ < nw - 1; iw_++) { \
    a[iw_] = (b[iw_] >> 1) | (b[iw_ + 1] << (WORDBITS_ - 1)); \
  } a[iw_] = b[iw_] >> 1; }

/* left shift one bit */
#define BITS_LSHIFT1(a, b, nw) { int iw_; \
  for (iw_ = nw - 1; iw_ > 0; iw_--) { \
    a[iw_] = (b[iw_] << 1) | ( b[iw_ - 1] >> (WORDBITS_ - 1) ); \
  } a[0] = b[0] << 1; }


/* make a set of lowest k - 1 bits, without the ith element */
#define BITS_MKINVSET(bs, k, nw, i)  \
  BITS_MKBITSMASK(bs, k, nw) BITS_REMOVE(bs, i)

INLINE BITS_WORD_T *bits_mkinvset(BITS_WORD_T *bs, int n, int nw, int i)
{ BITS_MKINVSET(bs, n, nw, i) return bs; }

/* make a set of the lowest k - 2 bits, without the ith and jth elements */
#define BITS_MKINVSET2(bs, k, nw, i, j)  \
  BITS_MKBITSMASK(bs, k, nw) BITS_REMOVE(bs, i) BITS_REMOVE(bs, j)

INLINE BITS_WORD_T *bits_mkinvset2(BITS_WORD_T *bs, int n, int nw, int i, int j)
{ BITS_MKINVSET2(bs, n, nw, i, j) return bs; }


#define bits_print(bs, n, name) bits_fprint(bs, n, stdout, name)

/* print a set as star or blank pattern */
INLINE void bits_fprint(BITS_WORD_T *bs, int n, FILE *fp, const char *name)
{
  int i;

  if (name != NULL) fprintf(fp, "%-8s: [", name);
  for (i = 0; i < n; i++)
    fprintf(fp, "%c", BITS_HAS(bs, i) ? '*' : ' ');
  fprintf(fp, "]\n");
}


#define bits_printn(bs, n, name) bits_fprintn(bs, n, stdout, name)

/* print a set as numbers */
INLINE void bits_fprintn(BITS_WORD_T *bs, int n, FILE *fp, const char *name)
{
  int i;

  if (name != NULL) fprintf(fp, "%-8s:", name);
  for (i = 0; i < n; i++)
    if ( BITS_HAS(bs, i) )
      fprintf(fp, " %d", i);
  fprintf(fp, "\n");
}


#endif /* ZCOM_BITS__ */
#endif /* ZCOM_BITS */





#ifdef  ZCOM_BLKMEM
#ifndef ZCOM_BLKMEM__
#define ZCOM_BLKMEM__


/* block memory allocator */

typedef struct tagblkmemlls_t {
  char *ptr; /* allocated memory */
  size_t n; /* number of item used */
  struct tagblkmemlls_t *next;
} blkmemlls_t;

typedef struct {
  size_t objsz; /* memory for a single object */
  size_t blksz; /* number of objects to allocate each time */
  blkmemlls_t *ls, *last;
  int err; /* we are out of memory */
} blkmem_t;


INLINE blkmem_t *blkmem_open(size_t objsz, size_t blksz)
{
  blkmem_t *bm;

  if ((bm = calloc(1, sizeof(*bm))) == NULL) {
    fprintf(stderr, "blkmem: no memory for blkmem_t\n");
    return NULL;
  }
  bm->objsz = objsz;
  bm->blksz = blksz;
  bm->ls = NULL;
  bm->last = NULL; /* for quick look up */
  bm->err = 0;
  return bm;
}


INLINE void blkmem_close(blkmem_t *bm)
{
  blkmemlls_t *ls, *ls1;

  for (ls = bm->ls; ls; ls = ls1) {
    ls1 = ls->next;
    free(ls->ptr);
    free(ls);
  }
  free(bm);
}


/* allocate an empty list */
INLINE blkmemlls_t *blkmem_newlls(size_t objsz, size_t blksz, int *err)
{
  blkmemlls_t *ls;

  if (*err) return NULL;
  if ((ls = calloc(1, sizeof(*ls))) == NULL) {
    fprintf(stderr, "blkmem: no memory for the first list\n");
    *err = 1;
    return NULL;
  }
  ls->n = 0;
  ls->next = NULL;
  if ((ls->ptr = calloc(blksz, objsz)) == NULL) {
    fprintf(stderr, "blkmem: no memory for list objects %u x %u\n",
        (unsigned) blksz, (unsigned) objsz);
    *err = 1;
    return NULL;
  }
  return ls;
}


#define blkmem_new1(bm) blkmem_newlow(bm, 1, 1)
#define blkmem_new(bm, k) blkmem_newlow(bm, k, 1)

/* allocate k new objects of size bm->objsz
 * if `fromlast' is true, we do not search for holes in previous lists
 * otherwise we search from the beginning of the list, which is much slower */
INLINE void *blkmem_newlow(blkmem_t *bm, size_t k, int fromlast)
{
  blkmemlls_t *ls;
  size_t blksz = bm->blksz, objsz = bm->objsz, n;

  if (k == 0) {
    return NULL;
  } else if (k >= blksz) {
    fprintf(stderr, "blkmem: size %u > %u\n", (unsigned) k, (unsigned) blksz);
    return NULL;
  }

  if (bm->ls == NULL) { /* initial empty list */
    if ((ls = blkmem_newlls(objsz, blksz, &bm->err)) == NULL)
      return NULL;
    bm->ls = bm->last = ls;
  } else {
    if (fromlast) /* search from the last item */
      ls = bm->last;
    else /* search from the beginning */
      ls = bm->ls;
    /* loop to the end of the list
     * or stop if there are enough spaces left */
    while (1) {
      if (ls->n + k <= blksz) { /* find a hole */
        break;
      } else if (ls->next == NULL) { /* end of the list, extend it */
        if ((ls->next = blkmem_newlls(blksz, objsz, &bm->err)) == NULL)
          return NULL;
        ls = ls->next;
        bm->last = ls;
        break;
      } else { /* check the next list */
        ls = ls->next;
      }
    }
  }
  /* we still have memory */
  n = ls->n;
  ls->n = n + k;
  return (void *) (ls->ptr + n * objsz);
}


#define blkmem_print(bm, name) blkmem_fprint(bm, name, stdout)

/* print usage */
INLINE void blkmem_fprint(const blkmem_t *bm, const char *name, FILE *fp)
{
  blkmemlls_t *ls = bm->ls;

  fprintf(fp, "(blkmem)%s: %u (objsz) x %u (blksz): ",
      name ? name : "", (unsigned) bm->objsz, (unsigned) bm->blksz);
  for (; ls; ls = ls->next)
    fprintf(fp, "%u ", (unsigned) ls->n);
  fprintf(fp, "\n");
}


#endif /* ZCOM_BLKMEM__ */
#endif /* ZCOM_BLKMEM */





#ifdef  ZCOM_SS
#ifndef ZCOM_SS__
#define ZCOM_SS__
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>

/* operation code */
enum { SSCAT = 1, SSDELETE = 2, SSSHRINK = 3, SSSINGLE = 0x1000 };

#ifndef SSMINSIZ /* to override the block size, define it before inclusion */
#define SSMINSIZ 256 /* at least sizeof(int), but change this value to 1 for debugging */
#endif
#ifndef SSHASHBITS
#define SSHASHBITS 8
#endif
#define SSHASHSIZ   (1 << SSHASHBITS)
#define SSOVERALLOC 1
#define sscalcsize_(n) (((n)/SSMINSIZ + 1) * SSMINSIZ) /* size for n nonblank characters */

struct ssheader {
  size_t size;
  size_t hashval;
  struct ssheader *next;
} ssbase_[SSHASHSIZ] = {{ 0u, 0u, NULL }};


/* we use the string address instead of that of the pointer
 * to struct ssheader to compute the Hash value,
 * because the former is more frequently used in e.g. looking-up
 * */
INLINE size_t sshashval_(const char *p)
{
  size_t val = (size_t) p * 1664525u + 1013904223u;
  return (val >> (sizeof(size_t)*8 - SSHASHBITS)) & ((1<<SSHASHBITS) - 1);
}


/* return the *previous* header to the one that associates with s
 * first locate the list from the Hash value, then enumerate the linked list.
 * */
INLINE struct ssheader *sslistfind_(const char *s)
{
  struct ssheader *hp, *head;

  if (s == NULL) return NULL;
  head = ssbase_ + sshashval_(s);
  if (head->next == NULL) return NULL; /* uninitialized head node */
  for (hp = head; hp->next != head; hp = hp->next)
    if ((char *)(hp->next + 1) == s) /* match the string address */
      return hp;
  return NULL;
}


/* simply add the entry h at the begining of the list
 * we do not accept a pre-calculated hash value,
 * since realloc might have changed it
 * */
INLINE struct ssheader *sslistadd_(struct ssheader *h)
{
  struct ssheader *head;

  head = ssbase_ + sshashval_( (char *)(h + 1) );
  if (head->next == NULL) /* initialize the base */
    head->next = head;
  h->next = head->next;
  head->next = h;
  return head;
}


/* remove hp->next */
INLINE void sslistremove_(struct ssheader *hp, int f)
{
  struct ssheader *h = hp->next;

  hp->next = h->next;
  if (f) free(h);
}


/* (re)allocate memory for (*php)->next, update list, return the new string
 * n is the number of nonempty characters, obtained e.g. from strlen().
 * create a new header if *php is NULL, in this case, the first character
 * of the string is '\0'
 * */
INLINE char *ssresize_(struct ssheader **php, size_t n, unsigned flags)
{
  struct ssheader *h = NULL, *hn, *hp;
  size_t size;

  if (php == NULL) {
    fprintf(stderr, "ssresize_: php is NULL, n = %u", (unsigned) n);
    return NULL;
  }

  /* we use the following if to assign hp and h, so the order is crucial */
  if ((hp = *php) == NULL || (h = hp->next)->size < n + 1 || !(flags & SSOVERALLOC)) {
    size = sscalcsize_(n);
    if (h == NULL || size != h->size) {
      /* remove h from the list  */
      if (hp != NULL) sslistremove_(hp, 0);
      if ((hn = calloc(sizeof(*h) + size, 1)) == NULL) {
        fprintf(stderr, "ssresize_: no memory for %u\n", (unsigned) size);
        return NULL;
      }
      if (h != NULL) {
        memcpy(hn, h, sizeof(*hn) + (size > h->size ? h->size : size));
        free(h);
      }
      h = hn;

      *php = hp = sslistadd_(h);
      hp->next->size = size;
    }
  }
  return (char *)(hp->next + 1);
}


INLINE void ssmanage_low_(struct ssheader *hp, unsigned opt)
{
  if (opt == SSDELETE)
    sslistremove_(hp, 1);
  else if (opt == SSSHRINK)
    ssresize_(&hp, strlen((char *)(hp->next + 1)), 0);
}


#define ssdel(s)       ssmanage((s), SSDELETE|SSSINGLE)
#define ssdelete(s)    { ssdel(s); (s)=NULL; }
#define ssshrink(s)    ssmanage((s), SSSHRINK|SSSINGLE)
#define ssdelall()     ssmanage(NULL, SSDELETE)
#define ssshrinkall()  ssmanage(NULL, SSHRINK)

/* delete a string, shrink memory, etc ... */
INLINE int ssmanage(char *s, unsigned flags)
{
  struct ssheader *hp, *head;
  unsigned opt = flags & 0xFF;

  if (flags & SSSINGLE) { /* working on a single string */
    if (s == NULL || (hp = sslistfind_(s)) == NULL) {
      if (s) fprintf(stderr, "ssmanage: unknown address %p (%s)\n",  s, s);
      return -1;
    }
    ssmanage_low_(hp, opt);
  } else {
    size_t i;
    for (i = 0; i < SSHASHSIZ; i++)
      for (hp = head = ssbase_ + i; hp->next && hp->next != head; hp = hp->next)
        /* we must not operate on h itself, which renders the iterator h invalid */
        ssmanage_low_(hp, opt);
  }
  return 0;
}


#define ssnew(n)       sscpycatx(NULL, NULL, (n),    0)
#define ssdup(t)       sscpycatx(NULL, (t),   0,     0)
#define sscpy(s, t)    sscpycatx(&(s), (t),   0,     0)
#define sscat(s, t)    sscpycatx(&(s), (t),   0, SSCAT)

/* copy/cat t to *ps
 *
 * If (flags & SSCAT) == 0:
 * copy t to *ps, if ps is not NULL, and return the result
 * if ps or *ps is NULL, we return a string created from t
 *   *ps is set to the same value if ps is not NULL
 * otherwise, we update the record that corresponds to *ps
 *
 * minsize: to request a minimal size for the resulting buffer
 *
 * If flags & SSCAT:
 * append t after *ps. Equivalent to cpy if ps or *ps is NULL.
 * */
INLINE char *sscpycatx(char **ps, const char *t, size_t minsize, unsigned flags)
{
  struct ssheader *hp = NULL;
  size_t size = 0u, sizes = 0u;
  char *s = NULL, *p;

  /* both ps and *ps can be NULL, in which cases we leave hp as NULL */
  if (ps != NULL && (s = *ps) != NULL && (hp = sslistfind_(s)) == NULL) {
    fprintf(stderr, "sscpycatx: unknown address %p (%s)\n", s, s);
    return NULL;
  }
  if (t != NULL)
    while (t[size]) /* compute the length of t */
      size++;
  if (flags & SSCAT) {
    if (s != NULL)  /* s is also NULL, if ps itself is NULL */
      while (s[sizes]) /* compute the length of s */
        sizes++;
    size += sizes;
  }  /* sizes is always 0 in case of copying */
  if (size < minsize)
    size = minsize;
  if ((s = ssresize_(&hp, size, SSOVERALLOC)) == NULL) { /* change size */
    return NULL;
  }
  if (t != NULL)
    for (p = s + sizes; (*p++ = *t++) != '\0'; ) /* copy/cat the string */
      ;
  if (ps != NULL)
    *ps = s;
  return s;
}


#define ssfgets(s, pn, fp)    ssfgetx(&(s), (pn), '\n', (fp))
#define ssfgetall(s, pn, fp)  ssfgetx(&(s), (pn), EOF, (fp))

/* get a string *ps from file fp
 * *ps can be NULL, in which case memory is allocated
 * *pn is number of characters read (including '\n', but not the terminal null)
 * delim is the '\n' for reading a singe line
 * */
INLINE char *ssfgetx(char **ps, size_t *pn, int delim, FILE *fp)
{
  size_t n, max;
  int c;
  char *s;
  struct ssheader *hp;

  if (ps == NULL || fp == NULL)
    return NULL;
  if ((s = *ps) == NULL) /* allocate an initial buffer if *ps is NULL */
    if ((s = sscpycatx(ps, NULL, 0, 0u)) == NULL)
      return NULL;
  if ((hp = sslistfind_(s)) == NULL) {
    fprintf(stderr, "ssfgetx: unknown address %p (%s)\n", s, s);
    return NULL;
  }
  max = hp->next->size-1;
  for (n = 0; (c = fgetc(fp)) != EOF; ) {
    if (n + 1 > max) { /* request space for n+1 nonblank characters */
      if ((*ps = s = ssresize_(&hp, n + 1, SSOVERALLOC)) == NULL)
        return NULL;
      max = hp->next->size - 1;
    }
    s[n++] = (char)(unsigned char) c;
    if (c == delim)
      break;
  }
  s[n] = '\0';
  if (pn != NULL)
    *pn = n;
  return (n > 0) ? s : NULL;
}


/* parse `s' into a string array
 * delimiters are removed */
INLINE char **ssparse(char *s, int *pn, const char *delim)
{
  const int capsz = 16;
  int cap, n;
  char **sarr, **sarr1, *p, *q;
  char delim0[8] = "\n\r"; /* default deliminators: new lines */

  if (pn) *pn = 0;
  if (delim == NULL) delim = delim0;

  cap = capsz;
  if ((sarr = calloc(cap, sizeof(sarr[0]))) == NULL) {
    fprintf(stderr, "no memory for sarr\n");
    return NULL;
  }
  for (n = 0, p = s; ; ) { /* n is # of lines */
    for (q = p; *q != '\0'; q++)
      if (strchr(delim, *q))
        break;
    if (q != p) { /* skip an empty line */
      sarr[n++] = p;
      if (n >= cap) { /* expand the array */
        cap += capsz;
        if ((sarr1 = realloc(sarr, cap * sizeof(sarr[0]))) == NULL) {
          fprintf(stderr, "no memory for sarr, %d\n", cap);
          return NULL;
        }
        sarr = sarr1;
      }
    }
    if (*q == '\0') break; /* we are done */
    *q = '\0';
    /* search for the next starting point */
    for (p = q + 1; *p && strchr(delim, *p); p++)
      ;
    if (*p == '\0') break;
  }

  if (pn) *pn = n;
  return sarr;
}

/* free the string array, sarr[0] created by ssnew() and sarr created by malloc() */
#define ssarrfree(sarr) { ssdel(sarr[0]); free(sarr); }

#endif /* ZCOM_SS__ */
#endif /* ZCOM_SS */





#ifdef  ZCOM_ENDN
#ifndef ZCOM_ENDN__
#define ZCOM_ENDN__
/* endianness handling */
#include <stdio.h>
#include <string.h>


/* return the system endian, 1: big endian, 0: little endian */
INLINE int endn_system(void)
{
  unsigned feff = 0xFEFF; /* assume unsigned is at least 16-bit */
  unsigned char *p;

  p  = (unsigned char *) &feff;
  return (*p == 0xFF) ? 0 : 1;
}


/* change endianness in-place for n items of size in ptr */
INLINE void endn_flip(void *ptr, size_t size, size_t n)
{
  unsigned char *p = (unsigned char *) ptr, ch;
  size_t i, r, half = size/2;

  for (; n > 0; n--, p += size) {
    /* reverse bytes for each object */
    for (i = 0; i < half; i++) {
      r = size - i - 1;
      ch   = p[i];
      p[i] = p[r];
      p[r] = ch;
    }
  }
}

/* write data in ptr to file with a specific endian 'endn'
 * `ptr' is not const, because it needs to change its endian */
INLINE size_t endn_fwrite(void *ptr, size_t size, size_t n, FILE *fp, int endn)
{
  static int endsys = -1;

  /* initial determine the machine's endianess */
#ifdef _OPENMP
#pragma omp critical
#endif
  {
    if (endsys < 0) endsys = endn_system();
  }
  if (endn == endsys) return fwrite(ptr, size, n, fp);

  endn_flip(ptr, size, n);
  n = fwrite(ptr, size, n, fp);
  endn_flip(ptr, size, n);
  return n;
}


/* read an object test object *src, compared with *ref
 * return 0 if they are identical without endian change
 * return 1 if changing the endianness of *src matches *ref
 * otherwise return -1 */
INLINE int endn_rmatch(void *src, const void *ref, size_t size, FILE *fp)
{
  if (1 != fread(src, size, 1, fp))
    return -1;
  if (memcmp(src, ref,  size) == 0)
    return 0;
  /* alter the endianness, and test again */
  endn_flip(src, size, 1);
  return (memcmp(src, ref, size) == 0) ? 1 : -1;
}


/* special case of endn_rmatchi for integer, convenient because
 * iref could be e.g. sizeof(int), which has no address */
INLINE int endn_rmatchi(int *src, int iref, FILE *fp)
{
  return endn_rmatch(src, &iref, sizeof(int), fp);
}


/* read data from file to ptr with endianness changed if 'flip' is 1
 * flip can be initialized by calling endn_rmatch() for a test object */
INLINE size_t endn_fread(void *ptr, size_t size, size_t n, FILE *fp, int flip)
{
  n = fread(ptr, size, n, fp);
  if (flip) endn_flip(ptr, size, n);
  return n;
}

#endif /* ZCOM_ENDN__ */
#endif /* ZCOM_ENDN */





#ifdef  ZCOM_BIO
#ifndef ZCOM_BIO__
#define ZCOM_BIO__

#include <stdio.h>

/*
 * Helper macros for reading binary files with endianness
 * support.  However, sizeof(int) must remain the same
 * between system and file.
 *
 * To use these macros in a function:
 * 1. define the following variables in your function
 *   FILE *fp;
 *   int endn, err;
 *   (no need for to define `endn' or `err' in writing a file)
 *
 * 2. define a label ERR for error exit
 *
 * 3. in reading a file, use BIO_INITENDIAN to determine
 *    the correct endianness
 * */

#ifndef BIO_ENDNDEF
#define BIO_ENDNDEF 1  /* big endian */
#endif

/* string for printing file name and line number */
#define BIO_FLFMT_ "file: %s, line: %d"

/* check type */
#define BIO_CHECKTP_(x, tp)                                           \
  if (sizeof(x) != sizeof(tp)) {                                      \
    fprintf(stderr, "%s is not %s\n", #x, #tp);                       \
    goto ERR;                                                         \
  }

/* initialize file endian state to variable 'endn'
 * endn = 1: a conversion is needed from file's endianness to system's
 * endn = 0: otherwise
 * read an int variable x,
 * determine endian by comparing the value of x with ref
 * quit if neither endian makes x == ref */
#define BIO_INIT_ENDIAN(x, ref) {                                     \
  BIO_CHECKTP_(x, int)                                                \
  if ((endn = endn_rmatchi(&(x), ref, fp)) < 0) {                     \
    fprintf(stderr, "%s 0x%X cannot match %s 0x%X\n",                 \
      #x, (unsigned) x, #ref, (unsigned) ref);                        \
    goto ERR;                                                         \
  } }

/* read an array of size n, set err, fix endian */
#define BIO_RATOM_(arr, n)                                                      \
  if ((n) > 0 && endn_fread(arr, sizeof(*(arr)), n, fp, endn) != (size_t) n) {  \
    fprintf(stderr, "error while reading %s, size %u, "                         \
        BIO_FLFMT_ "\n", #arr, (unsigned) n, __FILE__, __LINE__);               \
    err = 1;                                                                    \
  } else { err = 0; }

/* read an array, set error */
#define BIO_RNA_(arr, n, tp) BIO_CHECKTP_(*(arr), tp) BIO_RATOM_(arr, n)
/* read a single variable x of type tp, set err if error occurs */
#define BIO_R1A_(x, tp) BIO_RNA_(&(x), 1, tp)

/* goto ERR if error occurs during reading */
#define BIO_RNB_(arr, n, tp) { BIO_RNA_(arr, n, tp); if (err) goto ERR; }
#define BIO_R1B_(x, tp) { BIO_R1A_(x, tp); if (err) goto ERR; }

/* most common: int and double cases */
#define BIO_RI_ERR(x)     BIO_R1A_(x, int)
#define BIO_RI(x)         BIO_R1B_(x, int)
#define BIO_RIARR(x, n)   BIO_RNB_(x, n, int)

#define BIO_RD_ERR(x)     BIO_R1A_(x, double)
#define BIO_RD(x)         BIO_R1B_(x, double)
#define BIO_RDARR(x, n)   BIO_RNB_(x, n, double)

/* match a temporary int x with the reference var */
#define BIO_MI(x, var)                                                \
  if ((x) != (var)) {                                                 \
    fprintf(stderr, "%s mismatch, expect: %d, read: %d "              \
        BIO_FLFMT_ "\n", #var, (int) var, x, __FILE__, __LINE__);     \
    goto ERR; }

/* match a temporary double x with the reference var */
#define BIO_MD(x, var, eps)                                           \
  if (fabs((x) - (var)) > eps) {                                      \
    fprintf(stderr, "%s mismatch, expect: %g, read: %g "              \
        BIO_FLFMT_ "\n", #var, var, x, __FILE__, __LINE__);           \
    goto ERR; }

/* read an int to x, match it with xref */
#define BIO_RMI(x, xref)       BIO_RI(x); BIO_MI(x, xref)
/* read a double to x, match it with xref */
#define BIO_RMD(x, xref, eps)  BIO_RD(x); BIO_MD(x, xref, eps)

/* write an array of size n with endian being BIO_ENDNDEF
 * we do not set err, directly goto ERR */
#define BIO_WATOM_(arr, n)                                            \
  if ((n) > 0 &&  (size_t) (n) !=                                     \
      endn_fwrite(arr, sizeof(*(arr)), n, fp, BIO_ENDNDEF) ) {        \
    fprintf(stderr, "error while reading %s, size %u, "               \
        BIO_FLFMT_ "\n", #arr, (unsigned) n, __FILE__, __LINE__);     \
    goto ERR;                                                         \
  }

/* write an array, go to ERR if error occurs */
#define BIO_WNB_(arr, n, tp) BIO_CHECKTP_(*(arr), tp) BIO_WATOM_(arr, n)
/* write a single variable, go to ERR if error occurs */
#define BIO_W1B_(x, tp) BIO_WNB_(&(x), 1, tp)

#define BIO_WI(x)           BIO_W1B_(x, int)
#define BIO_WIARR(x, n)     BIO_WNB_(x, n, int)
#define BIO_WD(x)           BIO_W1B_(x, double)
#define BIO_WDARR(x, n)     BIO_WNB_(x, n, double)

#endif /* ZCOM_BIO__ */
#endif /* ZCOM_BIO */





#ifdef  ZCOM_OSYS
#ifndef ZCOM_OSYS__
#define ZCOM_OSYS__

#define OSYS_VERBOSE 0x1

/* run command and capture the output
 * `cmd' is the command to run
 * `*nc' returns the number of characters read */
INLINE char *sysrun(const char *cmd, size_t *nc, unsigned flags)
{
  FILE *fp;
  char fntmp[] = "h1Qi7G0c.TmP"; /* output file */
  char *ncmd, *output = NULL;
  int i;

  if (nc) *nc = 0;

  /* construct the command */
  ncmd = ssdup(cmd);
  sscat(ncmd, " > ");
  sscat(ncmd, fntmp);

  /* run it */
  if ((i = system(ncmd)) != 0)
    if (flags & OSYS_VERBOSE)
      fprintf(stderr, "command \"%s\" failed\n", ncmd);
  ssdel(ncmd);
  if (i != 0) goto EXIT; /* output should be NULL in this case */

  xfopen(fp, fntmp, "r", goto EXIT);
  ssfgetall(output, nc, fp);
  fclose(fp);
EXIT:
  remove(fntmp);
  return output;
}


/* Get a list of file names satisfying a pattern
 * `pat' is the file name pattern, such as '*.c'
 * `*n' returns the number of matches
 * `lscmd' is the list command
 * the output is a file list (string array), to free it:
 *    ssdel(fnls[0]); free(fnls); */
INLINE char **fnglob(const char *pat, int *pn, const char *lscmd, unsigned flags)
{
  size_t nc = 0;
  char *cmd, *output;

  if (pn) *pn = 0;

  /* construct a command first */
  cmd = ssnew(256);
  if (lscmd == NULL) /* assuming Linux */
    lscmd = "ls --color=never ";
  sscpy(cmd, lscmd);
  sscat(cmd, pat);

  /* run the command and get the output */
  output = sysrun(cmd, &nc, flags);
  ssdel(cmd);
  if (output == NULL || nc == 0) return NULL;

  /* parse the output into file names
   * don't ssdel(output), for it's used in the output */
  return ssparse(output, pn, NULL);
}


#endif /* ZCOM_OSYS__ */
#endif /* ZCOM_OSYS */





#ifdef  ZCOM_OPT
#ifndef ZCOM_OPT__
#define ZCOM_OPT__


enum { OPT_ARGUMENT, OPT_OPTION, OPT_CFG, OPT_COUNT };


/* option either from arguments or configuration */
typedef struct {
  int isopt; /* one of OPT_xxx values */
  char ch; /* single letter option flag */
  const char *sflag; /* long string flag */
  const char *key; /* key, for cfg files as in `key = val' */

  const char *val; /* raw string from command line */
  const char *desc; /* description */
  const char *fmt; /* sscanf format */
  const char *pfmt; /* printf format, NULL: to guess */
  void *ptr; /* address to the target variable */
  int initval; /* initial value, for a switch option */
  const char **sarr; /* array of string values, for a list option */
  int scnt; /* length of the array, for a list option */
  unsigned flags;
} opt_t;


/* support __float128 for GCC
 * Intel compiler defines __GNUC__, but it does not have __float128 */
#if defined(__GNUC__) && !defined(__INTEL_COMPILER) \
  && ( (__GNUC__ == 4 && __GNUC_MINOR__ >= 6) || __GNUC__ > 4 )
  #define HAVEFLOAT128 1
  #include <quadmath.h>
  /* ignore warnings for "%Qf"
   * assume `diagnostic push' is available in this case */
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wformat"
  #pragma GCC diagnostic ignored "-Wformat-extra-args"
  #pragma GCC diagnostic ignored "-Wlong-long"
#else
  #define HAVEFLOAT128 0
#endif


/* return the index of string from a predefined array
 * using fuzzy string comparison */
INLINE int opt_select(const char *s, const char **sarr, int n)
{
  int i;
  char ls[1024];

  for ( i = 0; i < n; i++ )
    if ( strcmpfuzzy(sarr[i], s) == 0 )
      return i;
  if ( isdigit(s[0]) ) {
    i = atoi(s);
    if ( i >= 0 && i < n ) return i;
  }
  strjoin(ls, sizeof ls, sarr, n, ", ");
  fprintf(stderr, "Error: cannot select %s from the array of %d items: %s\n",
      s, n, ls);
  exit(1);
  return 0;
}


#define OPT_MUST     0x0001  /* a mandatory argument or option */
#define OPT_SWITCH   0x0002  /* an option is a switch */
#define OPT_SET      0x0004  /* an argument/option is set */

/* translate string value in `o->val' into
 * actual ones through sscanf(), etc */
INLINE int opt_getval(opt_t *o)
{
  const char *fmt = o->fmt;

  /* for a string argument, it can be obtained from NULL or "%s"
   * NULL: string memory from command-line
   * "%s":  string memory from sscpy()
   * if the string is read-only, like a output file name,
   * but the string is to be changed, use "%s" */
  if (fmt == NULL || fmt[0] == '\0') { /* raw string assignment */
    *((const char **) o->ptr) = o->val;
  } else if (strcmp(fmt, "%s") == 0) { /* copy the string */
    sscpy( *((char **) o->ptr), o->val);
  } else if (strcmpnc(fmt, "%list") == 0
          || strcmpnc(fmt, "%enum") == 0) {
    *((int *) o->ptr) = opt_select(o->val, o->sarr, o->scnt);
  } else if (strcmp(fmt, "%b") == 0) { /* switch */
    /* switch the default value */
    if (o->flags & OPT_SET) return !o->initval;
    else return o->initval;
  } else if (strcmp(fmt, "%+") == 0) { /* incremental, like -vv */
    *((int *) o->ptr) += 1;
  } else if (strcmp(fmt, "%-") == 0) { /* decremental, like -vv */
    *((int *) o->ptr) -= 1;
#if HAVEFLOAT128
  } else if (strcmp(fmt, "%Qf") == 0) {
#if defined(QUAD) || defined(F128)
    *((__float128 *) o->ptr) = strtoflt128(o->val, NULL);
#else /* intrinsic hook, requires no -lquadmath if unnecessary */
    sscanf(o->val, "%Qf", (__float128 *) o->ptr);
#endif /* defined(QUAD) || defined(F128) */
#endif
  } else { /* call sscanf */
    if (strcmp(fmt, "%r") == 0) /* real */
      fmt = (sizeof(real) == sizeof(float)) ? "%f" : "%lf";
    if (1 != sscanf(o->val, fmt, o->ptr)) {
      fprintf(stderr, "Error: unable to convert a value for [%s] as fmt [%s], raw string: [%s]\n",
          o->desc, fmt, o->val);
      return 1;
    }
  }
  return 0;
}


/* register an option
 *
 * for a configure entry, set `key' and leave `sflag' = NULL
 * for a command-line option, set `sflag' and leave `key' = NULL
 * `fmt' is the sscanf() format string
 * `*ptr' is the target variable
 * `fmt' can "%b" for a switch (like an command-line option "-v")
 * `fmt' can have a prefix `!' to mean a mandatory option
 * both NULL and "%s" of `fmt' mean string values, the type of
 *  `ptr' should be `char **', the difference is that `*ptr'
 *  is directly assigned to `o->val' during opt_getval() in the
 *  former case, but extra memory is allocated to copy `o->val'
 *  in the latter case */
#define opt_set(o, sflag, key, fmt, ptr, desc) \
  opt_setx(o, sflag, key, fmt, ptr, desc, NULL, 0)

INLINE void opt_setx(opt_t *o, const char *sflag, const char *key,
    const char *fmt, void *ptr, const char *desc,
    const char **sarr, int scnt)
{
  o->ch = '\0';
  if (key) { /* cfg file `key = val', not a command-line argument */
    o->isopt = OPT_CFG;
  } else if (sflag) { /* option */
    o->isopt = OPT_OPTION;
    o->ch = (char) ( sflag[2] ? '\0' : sflag[1] ); /* no ch for a long flag */
  } else { /* argument */
    o->isopt = OPT_ARGUMENT;
  }
  o->sflag = sflag;
  o->key = key;
  o->flags = 0;
  die_if (ptr == NULL, "null pass to opt with %s: %s\n", sflag, desc);
  o->ptr = ptr;
  if (fmt == NULL) fmt = "";
  if (fmt[0] == '!') {
    fmt++;
    o->flags |= OPT_MUST;
  }
  die_if (fmt[0] != '\0' && fmt[0] != '%',
      "unknown format (missing `%%') flag `%s\', fmt `%s', description: %s\n",
      sflag, fmt, desc);
  if (strcmp(fmt, "%b") == 0) {
    o->flags |= OPT_SWITCH;
    o->initval = *((int *) ptr); /* save the initial value */
  }
  o->fmt = fmt;
  o->pfmt = NULL;
  o->desc = desc;
  o->sarr = sarr;
  o->scnt = scnt;
}


/* print the value of o->ptr */
#define opt_printptr(o) opt_fprintptr(stderr, o)
INLINE void opt_fprintptr(FILE *fp, opt_t *o)
{
  const char *fmt;

  for (fmt = o->fmt; *fmt && *fmt != '%'; fmt++) ;

#define ELIF_PF_(fm, fmp, type) \
  else if (strcmp(fmt, fm) == 0) \
  { fprintf(fp, (o->pfmt ? o->pfmt : fmp), *(type *)o->ptr); }

  if (fmt == NULL || *fmt == '\0' || strcmp(fmt, "%s") == 0) {
    fprintf(fp, "%s", (*(char **) o->ptr) ? (*(char **) o->ptr) : "NULL");
  } else if (strcmp(fmt, "%b") == 0) {
    fprintf(fp, "%s", (*(int *)o->ptr) ? "true" : "false");
  } else if (strcmpfuzzy(fmt, "%list") == 0
          || strcmpfuzzy(fmt, "%enum") == 0) {
    int ival = *((int *) o->ptr);
    fprintf(fp, "%d (%s)", ival, o->sarr[ival]);
  }
  ELIF_PF_("%+", "%d", int)
  ELIF_PF_("%-", "%d", int)
  ELIF_PF_("%d", "%d", int)
  ELIF_PF_("%u", "%u", unsigned)
  ELIF_PF_("%x", "0x%x", unsigned)
  ELIF_PF_("%ld", "%ld", long)
  ELIF_PF_("%lo", "%lo", long)
  ELIF_PF_("%lu", "%lu", unsigned long)
  ELIF_PF_("%lx", "0x%lx", unsigned long)
#if 1  /* C99 or GCC extension */
  ELIF_PF_("%lld", "%lld", long long)
  ELIF_PF_("%llo", "%llo", long long)
  ELIF_PF_("%llu", "%llu", unsigned long long)
  ELIF_PF_("%llx", "0x%llx", unsigned long long)
#endif
  ELIF_PF_("%f", "%g", float)
  ELIF_PF_("%lf", "%g", double)
  ELIF_PF_("%Lf", "%Lg", long double)
#if HAVEFLOAT128
#if defined(QUAD) || defined(F128)
  else if (strcmp(fmt, "%Qf") == 0) {
    char buf[256];
    quadmath_snprintf(buf, sizeof buf,
        (o->pfmt ? o->pfmt : "%Qg"), *(__float128 *)o->ptr);
    fprintf(fp, "%s", buf);
  }
#else /* intrinsic hook, requires no -lquadmath if unnecessary */
  ELIF_PF_("%Qf", "%Qg", __float128)
#endif /* defined(QUAD) || defined(F128) */
#endif /* HAVEFLOAT128 */
  ELIF_PF_("%r", "%g", real)
  else {
    fprintf(fp, "unknown %s-->%%d: %d", fmt, *(int *) o->ptr);
  }

#undef ELIF_PF_
}


/* search an option list, return an option whose variable address is p */
INLINE opt_t *opt_find(opt_t *ls, int n, const void *p)
{
  int i;

  for (i = 0; i < n; i++) if (ls[i].ptr == p) return ls + i;
  return NULL;
}


/* search an option list to see if an option is explicitly set */
INLINE int opt_isset(opt_t *ls, int n, const void *p, const char *var)
{
  opt_t *o = opt_find(ls, n, p);
  die_if (!o, "cannot find var %s, ptr %p\n", var, p);
  return o->flags & OPT_SET ? 1 : 0;
}


#if HAVEFLOAT128
  #pragma GCC diagnostic pop
#endif


#endif /* ZCOM_OPT__ */
#endif /* ZCOM_OPT */





#ifdef  ZCOM_ARGOPT
#ifndef ZCOM_ARGOPT__
#define ZCOM_ARGOPT__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


typedef struct {
  int nopt;
  opt_t *opts;
  const char *prog;
  const char *desc;
  const char *author;
  const struct tm *tm; /* compilation time */
  int version;
  unsigned flags;
  int dum_[4]; /* space holder */
} argopt_t;

#define ARGOPT_MUST     OPT_MUST    /* mandatory argument or option, format starts with ! */
#define ARGOPT_SWITCH   OPT_SWITCH  /* format "%b" */
#define ARGOPT_SET      OPT_SET
#define ARGOPT_LONGOPT  0x0010  /* always assume long format, e.g., -maxh */


#define argopt_getopt(ao, p) opt_find(ao->opts, ao->nopt, p)
#define argopt_getarg argopt_getopt

/* test if argument/option is explicitly set */
#define argopt_isset(ao, var) opt_isset(ao->opts, ao->nopt, &var, #var)


/* initialize the argument structure */
INLINE argopt_t *argopt_open(unsigned flags)
{
  argopt_t *ao;
  time_t tmcmpl;

  xnew(ao, 1);
  ao->flags = flags;
  ao->nopt = 0;
  ao->opts = NULL;
  tmcmpl = time(NULL);
  ao->tm = localtime( &tmcmpl );
  memset(ao->dum_, '\0', sizeof(ao->dum_));
  return ao;
}


INLINE void argopt_close(argopt_t *ao)
{
  if (ao->opts) free(ao->opts);
  free(ao);
}


/* print version and die */
INLINE void argopt_version(argopt_t *ao)
{
  fprintf(stderr, "%s: %s, version %d\n",
      ao->prog, ao->desc ? ao->desc : "", ao->version);
  if (ao->author && ao->tm)
    fprintf(stderr, "Copyright (c) %s %d\n", ao->author, ao->tm->tm_year + 1900);
  argopt_close(ao);
  exit(1);
}


/* print help message and die */
INLINE void argopt_help(argopt_t *ao)
{
  int i, len, maxlen;
  opt_t *o;
  const char *sysopt[2] = {"print help message", "print version"}, *desc;
  char ls[1024];

  fprintf(stderr, "%s, version %d",
      ao->desc ? ao->desc : ao->prog, ao->version);
  if (ao->author && ao->tm)
    fprintf(stderr, ", Copyright (c) %s %d", ao->author, ao->tm->tm_year + 1900);
  fprintf(stderr, "\nUSAGE\n  %s {OPTIONS}", ao->prog);
  for (i = 0; i < ao->nopt; i++) {
    const char *bra = "", *ket = "";
    o = ao->opts + i;
    if (o->isopt) continue;
    if (o->flags & OPT_MUST) {
      if (strchr(o->desc, ' '))
        bra = "[", ket = "]";
    } else
      bra = "{", ket = "}";
    fprintf(stderr, " %s%s%s", bra, o->desc, ket);
  }
  fprintf(stderr, "\n");

  fprintf(stderr, "OPTIONS:\n") ;
  for (maxlen = 0, i = 0; i < ao->nopt; i++) { /* compute the longest option */
    if (!ao->opts[i].isopt) continue;
    len = strlen(ao->opts[i].sflag);
    if (len > maxlen) maxlen = len;
  }
  for (i = 0; i < ao->nopt; i++) {
    o = ao->opts + i;
    if (!o->isopt) continue;
    desc = o->desc;
    if (strcmp(desc, "$HELP") == 0)
      desc = sysopt[0];
    else if (strcmp(desc, "$VERSION") == 0)
      desc = sysopt[1];
    fprintf(stderr, "  %-*s : %s%s%s%s%s", maxlen, o->sflag,
        ((o->flags & OPT_MUST) ? "[MUST] " : ""),
        (!(o->flags & OPT_SWITCH) ? "followed by " : ""), desc,
        (o->sarr != NULL ? ", options: " : ""),
        (o->sarr != NULL ? strjoin(ls, sizeof ls, o->sarr, o->scnt, ", ") : ""));
    if (o->ptr && o->ptr != ao->dum_) { /* print default values */
      fprintf(stderr, ", default: ");
      opt_fprintptr(stderr, o);
    }
    fprintf(stderr, "\n");
  }
  argopt_close(ao);
  exit(1);
}


#define argopt_regarg(ao, fmt, ptr, desc) argopt_add(ao, NULL, fmt, ptr, desc)
#define argopt_regopt argopt_add
#define argopt_reghelp argopt_addhelp
#define argopt_regversion argopt_addversion
#define argopt_addhelp(ao, sflag) argopt_add(ao, sflag, "%b", ao->dum_, "$HELP")
#define argopt_addversion(ao, sflag) argopt_add(ao, sflag, "%b", ao->dum_, "$VERSION")
#define argopt_add(ao, sflag, fmt, ptr, desc) \
  argopt_addx(ao, sflag, fmt, ptr, desc, NULL, 0)

/* register an argument or option
 * sflag: string flag, or NULL for an argument
 * fmt: sscanf() format string, "%b" for a switch, "%r" for real
 * return the index */
INLINE int argopt_addx(argopt_t *ao, const char *sflag,
    const char *fmt, void *ptr, const char *desc,
    const char **sarr, int scnt)
{
  opt_t *o;
  int n;

  n = ao->nopt++;
  xrenew(ao->opts, ao->nopt);
  o = ao->opts + n;
  opt_setx(o, sflag, NULL, fmt, ptr, desc, sarr, scnt);
  return n;
}


/* main parser of arguments */
INLINE void argopt_parse(argopt_t *ao, int argc, char **argv)
{
  int i, j, k, ch, acnt = 0;
  opt_t *ol = ao->opts;

  ao->prog = argv[0];
  for (i = 1; i < argc; i++) {
    if (argv[i][0] != '-') { /* it's an argument */
      while (ol[acnt].isopt && acnt < ao->nopt) acnt++;
      if (acnt >= ao->nopt) argopt_help(ao);
      ol[acnt].val = argv[i];
      ol[acnt].flags |= OPT_SET;
      if (0 != opt_getval(ol + acnt))
        argopt_help(ao);
      ++acnt;
      continue;
    }

    /* it's an option, loop for abbreviated form "-abc" == "-a -b -c" */
    for (j = 1; (ch = argv[i][j]) != '\0'; j++) {
      int islong = (j == 1 && argv[i][1] == '-') | (ao->flags & ARGOPT_LONGOPT);

      if (islong) { /* match against long options */
        for (k = 0; k < ao->nopt; k++) {
          int lenf;
          if (ol[k].sflag == NULL) continue;
          lenf = strlen(ol[k].sflag);
          if (ol[k].isopt &&
              strncmp(argv[i], ol[k].sflag, lenf) == 0 &&
              ( (ol[k].flags & OPT_SWITCH)
              || strchr("= ", argv[i][lenf]) ) ) /* followed by a space or "=" */
            break;
        }
      } else { /* match against short options */
        for (k = 0; k < ao->nopt; k++)
          if (ol[k].isopt && ch == ol[k].ch)
            break;
      }
      if (k >= ao->nopt) {
        fprintf(stderr, "cannot handle option [%s]\n", argv[i]);
        argopt_help(ao);
      }

      if (ol[k].desc[0] == '$') { /* system commands */
        if (strcmp(ol[k].desc, "$HELP") == 0)
          argopt_help(ao);
        else if (strcmp(ol[k].desc, "$VERSION") == 0)
          argopt_version(ao);
      }

      if (ol[k].flags & OPT_SWITCH) { /* handle switches "%b" */
        ol[k].flags |= OPT_SET;
        /* switch the default value, note this flag may be passed
         * several times, so we don't want to flip around */
        *((int *) ol[k].ptr) = !ol[k].initval;
        if (islong) break; /* go to the next argument argv[i+1] */
      } else if (strcmp(ol[k].fmt, "%+") == 0
              || strcmp(ol[k].fmt, "%-") == 0) {
        if (0 != opt_getval(ol + k)) argopt_help(ao);
      } else { /* look for the argument for this option */
        int hasv = 0;
        if (islong) { /* e.g., --version=11 */
          j = strlen(ol[k].sflag);
          if (argv[i][j] == '=') {
            ol[k].val = argv[i] + j + 1;
            hasv = 1;
          }
        } else { /* e.g., -n8 */
          if (argv[i][++j]) {
            ol[k].val = argv[i] + j;
            hasv = 1;
          }
        }

        if (!hasv) { /* --version 11 or -n 8 */
          if (++i >= argc) {
            fprintf(stderr, "%s(%s) requires an argument!\n", ol[k].sflag, argv[i - 1]);
            argopt_help(ao);
          }
          ol[k].val = argv[i];
        }
        ol[k].flags |= OPT_SET;
        if (0 != opt_getval(ol + k)) argopt_help(ao);
        break; /* go to the next argument argv[i+1] */
      }
    } /* end of short option loop */
  }
  /* check if we have all mandatory arguments and options */
  for (i = 0; i < ao->nopt; i++) {
    if ((ol[i].flags & OPT_MUST) && !(ol[i].flags & OPT_SET)) {
      fprintf(stderr, "Error: missing %s %s: %s\n\n",
          ol[i].isopt ? "option" : "argument", ol[i].sflag, ol[i].desc);
      argopt_help(ao);
    }
  }
}


/* dump the current values */
INLINE void argopt_dump(const argopt_t *ao)
{
  int i, len = 2;
  opt_t *ol = ao->opts;

  /* get the width of the widest option */
  for (i = 0; i < ao->nopt; i++)
    if (ol[i].sflag)
      len = intmax(len, strlen(ol[i].sflag));

  /* print values of all options */
  for (i = 0; i < ao->nopt; i++) {
    const char *sflag = ol[i].sflag;
    char buf[1024];

    if (sflag == NULL) sflag = "arg";
    fprintf(stderr, "%*s: ", len + 1, sflag);
    opt_fprintptr(stderr, ol + i);
    fprintf(stderr, ",  %s", ol[i].desc);
    if (ol[i].sarr != NULL)
      fprintf(stderr, ", options: %s",
          strjoin(buf, sizeof buf, ol[i].sarr, ol[i].scnt, ", "));
    fprintf(stderr, "\n");
  }
}


#endif /* ZCOM_ARGOPT__ */
#endif /* ZCOM_ARGOPT */





#ifdef  ZCOM_CFG
#ifndef ZCOM_CFG__
#define ZCOM_CFG__


/* a line in the cfg file: `key = val'
 * `key' and `val' point to spaces allocated in cfg->buf
 * and no additional memory are allocated */
typedef struct {
  char *key, *val;
  int used;
} cfgln_t;

/* the entire cfg file */
typedef struct {
  char *buf;      /* string buffer for the entire file */
  int nln;        /* number of input lines */
  cfgln_t *lns;   /* parsed lines */
  int nopt;       /* number of user-requested options */
  opt_t *opts;    /* user-requested options, such that
                     cfg works like command-line options */
} cfg_t;

typedef cfg_t cfgdata_t; /* old alias */


#define cfg_set(cfg, var) opt_isset(cfg->opts, cfg->nopt, &var, #var)


/* Read the value of a given variable from the current configuration file,
 * the name of variable is given by `key',
 * If the key is matched, its value is saved to `*var' through sscanf,
 *   otherwise, the content in *var is not modified.
 * If the function succeeds, it returns 0.
 * In case fmt is "%s", (*var) is a string, or a pointer to char.
 *   The space for (*var) will be managed through sscpy. */
INLINE int cfg_get(cfg_t *cfg, void *var, const char *key, const char *fmt)
{
  int i;

  for (i = 0; i < cfg->nln; i++) {
    cfgln_t *cln = cfg->lns + i;
    if (cln->key != NULL && strcmp(cln->key, key) == 0) {
      if (strcmp(fmt, "%s") == 0) { /* string */
        sscpy( *((char **) var), cln->val); /* make a copy and return */
        return 0;
      } else /* use sscanf for other cases, like int, float,... */
        return EOF == sscanf(cln->val, fmt, var) ? 2 : 0;
    }
  }
  return 1; /* no match */
}


/* load the whole configuration file into memory, parse it to entries */
INLINE cfg_t *cfg_open(const char *fn)
{
  cfg_t *cfg;
  cfgln_t *cln;
  FILE *fp;
  size_t i, j, n, size = 0;
  char *p, *q;

  xfopen(fp, fn, "r", return NULL);
  xnew(cfg, 1);
  if (ssfgetall(cfg->buf, &size, fp) == NULL) {
    fprintf(stderr, "error reading file %s\n", fn);
    return NULL;
  }
  sscat(cfg->buf, "\n"); /* in case the file is not ended by a new line, we add one */
  fclose(fp);

  /* count the number of lines (before allocating the key-table) */
  for (p = cfg->buf, i = 0, n = 0; i < size; i++) {
    if (p[i] == '\n' || p[i] == '\r') {
      if (i > 0 && p[i - 1] == '\\') {
        /* splice multiple lines: replace CR/LF with spaces
           the parser should be insensitive to the extra spaces */
        p[i - 1] = p[i] = ' ';
      } else { /* mark the end the current line */
        p[i] = '\0';
        n++;
      }

      /* replace successive CR/LF by spaces for efficiency
         the size of the key-table == the number of non-blank lines */
      for (j = i + 1; j < size && cisspace(p[j]); j++) p[j] = ' ';
    }
  }

  xnew(cfg->lns, n);

  /* load lines into the key-table */
  for (p = cfg->buf, j = 0, i = 0; i < size; i++) {
    if (cfg->buf[i] == '\0') {
      cfg->lns[j++].key = p;
      if (j >= n) break;
      p = cfg->buf + i + 1;
    }
  }
  n = j;

  /* parse each line to a key/value pair */
  for (j = 0; j < n; j++) {
    cln = cfg->lns + j;
    p = cln->key;
    strip(p); /* remove leading and trailing spaces */

    /* skip a blank or comment line */
    if (p[0] == '\0' || strchr("#;", p[0]) != NULL) {
      cln->key = NULL;
      continue;
    }

    /* remove trailing spaces and ';' */
    for ( q = p + strlen(p) - 1;
          q >= p && (cisspace(*q) || *q == ';'); q--)
      *q = '\0';

    /* skip a line without '=' */
    if ((q = strchr(p, '=')) == NULL) {
      cln->key = NULL;
      continue;
    }
    *q = '\0';
    cln->val = q + 1;
    strip(cln->key);
    strip(cln->val);
  }
  cfg->nln = (int) n;
  cfg->nopt = 0;
  xnew(cfg->opts, 1); /* s.t. we call `xrenew' the next time */
  return cfg;
}


INLINE void cfg_close(cfg_t *cfg)
{
  ssdelete(cfg->buf);
  free(cfg->lns);
  free(cfg->opts);
  memset(cfg, 0, sizeof(*cfg));
  free(cfg);
}


/* register an option request, return the index */
INLINE int cfg_add(cfg_t *cfg, const char *key, const char *fmt,
            void *ptr, const char *desc)
{
  /* if fmt == NULL, the memory space of (*ptr) will be invalid
   * after cfg_close(), "%s" is much safer */
  if (fmt == NULL) fmt = "%s";
  xrenew(cfg->opts, cfg->nopt + 1);
  opt_set(cfg->opts + cfg->nopt, NULL, key, fmt, ptr, desc);
  return cfg->nopt++;
}


#define CFG_UNUSED   0x0001
#define CFG_NOTSET   0x0002
#define CFG_CHECKUSE 0x0100
#define CFG_VERBOSE  0x1000
#define cfg_parse(cfg, flags) cfg_match(cfg, flags)

/* match requested options with entries in cfg file
 * returns 0 if successful
 * if mandatory variables are not set, the return `ret' contains CFG_NOTSET
 * if `flags' has OPT_CHECKUSE, the return `ret' has CFG_UNUSED if
 * there are unused variables */
INLINE int cfg_match(cfg_t *cfg, unsigned flags)
{
  int i, j, ret = 0, verbose = flags & CFG_VERBOSE, must;
  opt_t *o;
  cfgln_t *cln;

  for (i = 0; i < cfg->nopt; i++) {
    o = cfg->opts + i;
    for (j = 0; j < cfg->nln; j++) {
      cln = cfg->lns + j;
      if (cln->key != NULL && strcmp(cln->key, o->key) == 0) {
        cln->used = 1;
        o->flags |= OPT_SET;
        o->val = cln->val;
        opt_getval(o);
        break;
      }
    }
    must = (o->flags & OPT_MUST);
    if (!(o->flags & OPT_SET) && (must || verbose)) {
      fprintf(stderr, "cfg: %s not set, default: ", o->key);
      opt_fprintptr(stderr, o);
      fprintf(stderr, "\n");
      if (must) ret |= CFG_NOTSET;
    }
  }

  if (flags & CFG_CHECKUSE) {
    for (j = 0; j < cfg->nln; j++) {
      cln = cfg->lns + j;
      if (cln->key != NULL && !cln->used && verbose) {
        fprintf(stderr, "cfg: unused line: %s = %s\n",
            cln->key, cln->val);
        ret |= CFG_UNUSED;
      }
    }
  }
  return ret;
}


/* dump the current values */
INLINE void cfg_dump(const cfg_t *cfg)
{
  int i, len = 2;
  opt_t *ol = cfg->opts;

  /* get the width of the widest entry */
  for (i = 0; i < cfg->nopt; i++)
    len = intmax(len, strlen(ol[i].key));

  /* print values of all options */
  for (i = 0; i < cfg->nopt; i++) {
    fprintf(stderr, "%*s: ", len + 1, ol[i].key);
    opt_fprintptr(stderr, ol + i);
    fprintf(stderr, ",  %s\n", ol[i].desc);
  }
}

#endif /* ZCOM_CFG__ */
#endif /* ZCOM_CFG */





#ifdef  ZCOM_LOG
#ifndef ZCOM_LOG__
#define ZCOM_LOG__


typedef struct {
  FILE *fp;
  const char *fname;
  unsigned flags;
} logfile_t;

#define LOG_WRITESCREEN  0x01
#define LOG_FLUSHAFTER   0x02
#define LOG_NOWRITEFILE  0x10
#define LOG_APPEND       0x80


INLINE logfile_t *log_open(const char *fn)
{
  logfile_t *log;

  xnew(log, 1);
  if (fn == NULL) fn = "LOG";
  log->fname = fn;
  log->flags = 0;
  return log;
}


INLINE int log_printf(logfile_t *log, char *fmt, ...)
{
  va_list args;

  if (log == NULL) return 1;
  if (log->fp == NULL) {
    const char *aw = (log->flags & LOG_APPEND) ? "a" : "w";
    xfopen(log->fp, log->fname, aw, return 1);
  }
  if ((log->flags & LOG_NOWRITEFILE) == 0) {
    va_start(args, fmt);
    vfprintf(log->fp, fmt, args);
    va_end(args);
  }
  if (log->flags & LOG_WRITESCREEN) {
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
  }
  if (log->flags & LOG_FLUSHAFTER)
    fflush(log->fp);
  return 0;
}


INLINE void log_close(logfile_t *log)
{
  if (log == NULL) return;
  if (log->fp != NULL) { fclose(log->fp); log->fp = NULL; }
  free(log);
}


/* close & reopen log file to make sure that stuff is written to disk */
INLINE int log_hardflush(logfile_t *log)
{
  if (log->fp == NULL || log->fname == NULL) return 1;
  fclose(log->fp);
  xfopen(log->fp, log->fname, "a", return 1);
  return 0;
}

#if defined(HAVEVAM) && defined(NEED_WTRACE)
STRCLS logfile_t log_stock_[1] = {{ NULL, "TRACE", 0 }};
#define wtrace(fmt, ...) { \
  if (fmt) log_printf(log_stock_, fmt, ##__VA_ARGS__); \
  else if (log_stock_->fp) { fclose(log_stock_->fp); log_stock_->fname = NULL; } }
#endif

#endif /* ZCOM_LOG__ */
#endif /* ZCOM_LOG */





#ifdef  ZCOM_AV
#ifndef ZCOM_AV__
#define ZCOM_AV__
#include <stdio.h>
#include <stdarg.h>
#include <math.h>


typedef struct {
  double s, sx;
} av0_t; /* simplest averager without variance */


INLINE void av0_clear(av0_t *av) { av->s = 1e-20; av->sx = 0; }
INLINE double av0_getave(const av0_t *av) { return av->sx / av->s; }
INLINE void av0_add(av0_t *av, double x) { av->s += 1; av->sx += x; }
INLINE void av0_addw(av0_t *av, double x, double w) { av->s += w; av->sx += x * w; }


typedef struct {
  double s, sx, sx2; /* sum, sum x, variance */
} av_t;

INLINE void av_clear(av_t *av) { av->s = av->sx = av->sx2 = 0; }
INLINE double av_getave(const av_t *av) { return (av && av->s > 0) ? av->sx/av->s : 0; }
INLINE double av_getvar(const av_t *av) { return (av && av->s > 0) ? av->sx2/av->s : 0; }
INLINE double av_getdev(const av_t *av) { return (av && av->s > 0) ? sqrt(av_getvar(av)) : 0; }

/* add a new value to av_t with a weight `w' */
INLINE void av_addw(av_t *av, double x, double w)
{
  double s, sx;

  av->s = (s = av->s) + w;
  av->sx = (sx = av->sx) + x*w;
  if (s <= 0.0) return;
  av->sx2 += (x - sx/s)*(x - av->sx/av->s)*w;
}
#define av_add(av, x) av_addw(av, x, 1)

/* adaptive averaging: sX = sX * gam + X */
INLINE void av_gaddw(av_t *av, double x, double w, double ngam)
{
  double s, sx, del, gam = 1.0 - ngam;

  av->s = (s = av->s)*gam + w;
  av->sx = (sx = av->sx)*gam + w*x;
  if (s <= 0.0) return;
  del = x*s - sx;
  av->sx2 = (av->sx2 + w*del*del/(s*av->s))*gam;
}

#define av_gadd(av, x, ngam) av_gaddw(av, x, 1, ngam)


/* average of n quantities */
typedef struct {
  int n;
  double s;
  double *x; /* buffer, current x value */
  double *sx, *sxb; /* sum */
  double *sx2; /* variance */
} avn_t;

/* open average for n quantities */
INLINE avn_t *avn_open(int n)
{
  avn_t *a;
  int i;

  xnew(a, 1);
  die_if (n <= 0, "avn needs at least n %d >= 1\n", n);
  a->n = n;
  xnew(a->x, n);
  xnew(a->sx, n);
  xnew(a->sxb, n);
  xnew(a->sx2, n*n);
  a->s = 0;
  for (i = 0; i < n; i++) a->x[i] = a->sx[i] = a->sxb[i] = 0;
  for (i = 0; i < n * n; i++) a->sx2[i] = 0;
  return a;
}

INLINE void avn_close(avn_t *a)
{
  free(a->x);
  free(a->sx);
  free(a->sxb);
  free(a->sx2);
  free(a);
}

/* add values to avn_t with a weight `w'
 * must add all values simultaneously, otherwise a->s is messed up */
INLINE void avn_addwv(avn_t *a, const double *x, double w)
{
  int k, l, n = a->n;
  double s;

  a->s = (s = a->s) + w;
  for (k = 0; k < n; k++) {
    a->sx[k] = (a->sxb[k] = a->sx[k]) + x[k] * w;
  }
  if (s > 0) { /* update variance */
    for (k = 0; k < n; k++)
      for (l = k; l < n; l++)
        a->sx2[k*n + l] += (x[k] - a->sxb[k]/s) * (x[l] - a->sx[l]/a->s) * w;
  }
}

#define avn_addv(a, x) avn_addwv(a, x, 1)

/* add values to avn_t with a weight `w'
 * use argument list */
INLINE void avn_addw(avn_t *a, double w, ...)
{
  int k;
  va_list va;

  va_start(va, w);
  for (k = 0; k < a->n; k++) {
    a->x[k] = va_arg(va, double);
  }
  va_end(va);
  avn_addwv(a, a->x, w);
}


/* weighted update: sX = sX*gam + X */
INLINE void avn_gaddwv(avn_t *a, const double *x, double w, double ngam)
{
  int k, l, n = a->n;
  double s, gam = 1.0 - ngam;

  a->s = (s = a->s)*gam + w;
  for (k = 0; k < n; k++) {
    a->sx[k] = (a->sxb[k] = a->sx[k]) * gam + w * x[k];
  }
  if (s > 0) { /* update variance */
    for (k = 0; k < n; k++)
      for (l = k; l < n; l++)
        a->sx2[k*n + l] = gam * (a->sx2[k*n + l] +
            w*(x[k]*s - a->sxb[k]) * (x[l]*s - a->sxb[l])/(s*a->s));
  }
}

#define avn_gaddv(a, x, ngam) avn_gaddwv(a, x, 1, ngam)

/* weighted update
 * use argument list */
INLINE void avn_gaddw(avn_t *a, double w, double ngam, ...)
{
  int k;
  va_list va;

  va_start(va, ngam);
  for (k = 0; k < a->n; k++)
    a->x[k] = va_arg(va, double);
  va_end(va);
  avn_gaddwv(a, a->x, w, ngam);
}

/* these macros are only available if we have variable arguments macros */
#ifdef HAVEVAM
#define anv_add(a, ...) avn_addw(a, 1.0, ## __VARARGS__)
#define anv_gadd(a, ngam, ...) avn_gaddw(a, 1.0, ngam, ## __VARARGS__)
#endif

INLINE void avn_clear(avn_t *a)
{
  int i;

  a->s = 0;
  for (i = 0; i < a->n; i++)
    a->x[i] = a->sx[i] = a->sxb[i] = 0;
  for (i = 0; i < a->n * a->n; i++)
    a->sx2[i] = 0;
}

/* get average of quantity k */
INLINE double avn_getave(const avn_t *a, int k)
{
  die_if (k < 0 || k >= a->n, "avn index %d out of range %d\n", k, a->n);
  return (a->s > 0) ? a->sx[k]/a->s : 0;
}

/* get averages of all quantities */
INLINE double *avn_getaven(const avn_t *a, double *val)
{
  int k;

  if (a->s <= 0.) {
    for (k = 0; k < a->n; k++) val[k] = 0;
  } else {
    for (k = 0; k < a->n; k++)
      val[k] = a->sx[k] / a->s;
  }
  return val;
}

/* get cross variance of quantities k and l */
INLINE double avn_getvar(const avn_t *a, int k, int l)
{
  die_if (k < 0 || k >= a->n || l < 0 || l >= a->n,
      "avn index %d, %d out of range %d\n", k, l, a->n);
  if (k > l) intswap(k, l);
  return (a->s > 0) ? a->sx2[k * a->n + l]/a->s : 0;
}

/* get variances of all quantities */
INLINE double *avn_getvarn(const avn_t *a, double *val)
{
  int k, l, n = a->n;

  if (a->s <= 0.) {
    for (k = 0; k < n * n; k++) val[k] = 0;
  } else {
    for (k = 0; k < n; k++) {
      for (l = k; l < n; l++) {
        val[k*n + l] = a->sx2[k*n + l] / a->s;
        if (l > k) val[l*n + k] = val[k*n + l];
      }
    }
  }
  return val;
}

/* get standard deviation of quantity k */
INLINE double avn_getdev(const avn_t *a, int k)
{
  die_if (k < 0 || k >= a->n, "avn index %d out of range %d\n", k, a->n);
  return (a->s > 0) ? sqrt(a->sx2[k * a->n + k]/a->s) : 0;
}

/* get standard deviations of all quantities */
INLINE double *avn_getdevn(const avn_t *a, double *val)
{
  int k, n = a->n;

  if (a->s <= 0.) {
    for (k = 0; k < n; k++) val[k] = 0;
  } else {
    for (k = 0; k < n; k++)
      val[k] = sqrt(a->sx2[k*n + k] / a->s);
  }
  return val;
}

/* get correlation coefficient between quantities k and l */
INLINE double avn_getcor(const avn_t *a, int k, int l)
{
  int n = a->n;
  die_if (k < 0 || k >= n || l < 0 || l >= n,
      "avn index %d, %d out of range %d\n", k, l, n);
  if (k > l) intswap(k, l);
  return (a->s > 0) ? a->sx2[k*n + l] / sqrt(a->sx2[k*n + k] * a->sx2[l*n + l]) : 0;
}

/* get correlation coefficients among all quantities */
INLINE double *avn_getcorn(const avn_t *a, double *val)
{
  int k, l, n = a->n;

  if (a->s <= 0.) {
    for (k = 0; k < n * n; k++) val[k] = 0;
  } else {
    for (k = 0; k < n; k++) {
      for (l = k; l < n; l++) {
        val[k*n + l] = a->sx2[k*n + l] / sqrt(a->sx2[k*n + k] * a->sx2[l*n + l]);
        if (l > k) val[l*n + k] = val[k*n + l];
      }
    }
  }
  return val;
}

#endif /* ZCOM_AV__ */
#endif /* ZCOM_AV */





#ifdef  ZCOM_HIST
#ifndef ZCOM_HIST__
#define ZCOM_HIST__


#define HIST_VERBOSE    0x0001
#define HIST_ADDAHALF   0x0010
#define HIST_NOZEROES   0x0020
#define HIST_KEEPLEFT   0x0040
#define HIST_KEEPRIGHT  0x0080
#define HIST_KEEPLEFT2  0x0040
#define HIST_KEEPRIGHT2 0x0080
#define HIST_KEEPEDGE   (HIST_KEEPLEFT | HIST_KEEPRIGHT | HIST_KEEPLEFT2 | HIST_KEEPRIGHT2)
#define HIST_KEEPHIST   0x0100
#define HIST_OVERALL    0x0200
#define HIST_ADDITION   0x1000


/* compute sum, average and variance */
INLINE double *histgetsums_(const double *h, int rows, int n,
    double xmin, double dx, double *sums)
{
  double *xav, *xxc, x, w;
  int i, r;

  xav = sums + rows;
  xxc = xav  + rows;
  for (r = 0; r < rows; r++) {
    sums[r] = xav[r] = xxc[r] = 0.;
    for (i = 0; i < n; i++) {
      x = xmin + (i+.5)*dx;
      w = h[r*n + i];
      sums[r] += w;
      xav[r]  += w*x;
      xxc[r]  += w*x*x;
    }
    if (sums[r] > 1e-5) {
      xav[r] /= sums[r];
      xxc[r] = xxc[r]/sums[r] - xav[r]*xav[r];
    }
  }
  return sums;
}


/* old names */
#define wdist(h, m, n, x0, dx, fn) \
  wdistex(h, m, n, x0, dx, HIST_ADDAHALF | HIST_VERBOSE, fn)
#define wdistex histsave

#define histsave(h, rows, n, xmin, dx, flags, fn) \
  histsavex((const double *) h, rows, n, xmin, dx, fn, \
            NULL, NULL, NULL, flags)

/* write histograms to file
 * histogram 'h' contains 'rows' histograms,
 * each contains 'n' entries, from 'xmin' to 'xmin+dx*n'
 * (*fwheader) is function to print additional information
 * (*fnorm) is advanced normalization function */
INLINE int histsavex(const double *h, int rows, int n, double xmin, double dx,
    const char *fn, int (*fwheader)(FILE *fp, void *data),
    double (*fnorm)(int r, int ix, double xmin, double dx, void *data),
    void *pdata, unsigned flags)
{
  const int version = 0;
  FILE *fp;
  int i, r, rp, rowp, imax, imin;
  const double *p;
  double sm, *sums, fac, delta;
  double smtot[3], *htot = NULL;

  if (fn == NULL) fn = "HIST";
  xfopen(fp, fn, "w", return -1);

  /* get statistics */
  xnew(sums, rows * 3);
  histgetsums_(h, rows, n, xmin, dx, sums);

  /* compute the overall histogram */
  if (flags & HIST_OVERALL) {
    xnew(htot, n); /* the overall histogram */
    for (i = 0; i < n; i++) htot[i] = 0.;

    for (r = 0; r < rows; r++)
      for (i = 0; i < n; i++)
        htot[i] += h[r*n + i];
    histgetsums_(htot, 1, n, xmin, dx, smtot);
    rowp = rows + 1;
  } else {
    rowp = rows;
  }

  /* print basic information */
  fprintf(fp, "# %d 0x%X | %d %d %g %g | ",
      version, flags, rows, n, xmin, dx);
  for (r = 0; r < rows; r++) /* number of visits */
    fprintf(fp, "%g ", sums[r]);
  fprintf(fp, "| ");
  for (r = 0; r < rows; r++) /* average, standard deviation */
    fprintf(fp, "%g %g ", sums[r+rows], sqrt(sums[r+rows*2]));
  fprintf(fp, "| ");
  if (fwheader != NULL) (*fwheader)(fp, pdata);
  fprintf(fp, "\n");

  delta = (flags & HIST_ADDAHALF) ? 0.5 : 0;

  for (r = 0; r < rowp; r++) {
    p = (r == rows) ? htot : (h+r*n);

    if (flags & HIST_KEEPRIGHT) {
      imax = n;
    } else { /* trim the right edge */
      for (i = n-1; i >= 0; i--)
        if (p[i] > 0)
          break;
      imax = i+1;
      if (imax == 0)
        continue;
    }

    if (flags & HIST_KEEPLEFT) {
      imin = 0;
    } else { /* trim the left edge */
      for (i = 0; i < imax; i++)
        if (p[i] > 0)
          break;
      imin = i;
    }

    sm = (r == rows) ? smtot[0] : sums[r];
    if (fabs(sm) < 1e-6) fac = 1.;
    else fac = 1.0/(sm*dx);

    for (i = imin; i < imax; i++) {
      if ((flags & HIST_NOZEROES) && p[i] < 1e-6)
        continue;
      fprintf(fp, "%g ", xmin+(i+delta)*dx);
      if (flags & HIST_KEEPHIST)
        fprintf(fp, "%20.14E ", p[i]);
      rp = (r == rows) ? (-1) : r;
      if (fnorm != NULL) /* advanced normalization, note the r = -1 case */
        fac = (*fnorm)(rp, i, xmin, dx, pdata);
      fprintf(fp, "%20.14E %d\n", p[i]*fac, rp);
    }
    fprintf(fp, "\n");
  }
  fclose(fp);
  if (flags & HIST_VERBOSE) {
    fprintf(stderr, "successfully wrote %s\n", fn);
    for (r = 0; r < rows; r++)
      fprintf(stderr, "%2d cnt: %20.4f av: %10.4f(%10.4f)\n",
          r, sums[r], sums[r+rows], sums[r+rows*2]);
  }
  free(sums);
  if (flags & HIST_OVERALL) {
    free(htot);
  }
  return 0;
}


/* fetch histogram size */
INLINE int histgetinfo(const char *fn, int *row, double *xmin, double *xmax, double *xdel,
    int *version, unsigned *fflags)
{
  FILE *fp;
  char s[1024];
  int n;

  xfopen(fp, fn, "r", return -1);
  if (fgets(s, sizeof s, fp) == NULL) {
    fprintf(stderr, "%s: missing the first line\n", fn);
    fclose(fp);
    return -1;
  }
  if (6 != sscanf(s, "# %d 0x %X | %d %d %lf %lf ",
        version, fflags, row, &n, xmin, xdel)) {
    fprintf(stderr, "%s: bad first line\n%s", fn, s);
    fclose(fp);
    return -1;
  }
  *xmax = *xmin + *xdel * n;
  fclose(fp);
  return 0;
}


/* skip a | */
INLINE char *skipabar_(char *p)
{
  int next = -1;
  sscanf(p, " | %n", &next);
  return (next < 0) ? NULL : (p + next);
}


#define histload(h, rows, n, xmin, dx, fn, flags) \
  histloadx((double *) h, rows, n, xmin, dx, fn, \
            NULL, NULL, NULL, flags)

/* load a previous histogram
 * (*frheader) function to read additional header info.
 * (*fnorm) normalization factor
 * flags can have HIST_ADDITION and/or HIST_VERBOSE */
INLINE int histloadx(double *hist, int rows, int n, double xmin, double dx,
    const char *fn,
    int (*frheader)(const char *s, void *data),
    double (*fnorm)(int r, int ix, double xmin, double dx, void *data),
    void *pdata, unsigned flags)
{
  static char s[40960] = "";
#ifdef _OPENMP
#pragma omp threadprivate(s)
#endif
  FILE *fp;
  char *p;
  int verbose = (flags & HIST_VERBOSE);
  int add = (flags & HIST_ADDITION);
  int ver, next, hashist;
  int i, i1, r, r1, nlin = 0;
  unsigned fflags;
  double x, y, y2, fac, delta, *arr, *sums = NULL;

  xfopen(fp, fn, "r", return -1);

  /* check the first line */
  if (fgets(s, sizeof s, fp) == NULL || s[0] != '#') {
    fprintf(stderr, "%s: missing the first line\n", fn);
    fclose(fp);
    return -1;
  }
  nlin++;
  if (6 != sscanf(s, " # %d 0x %X | %d%d%lf%lf | %n", &ver, &fflags, &r, &i, &y, &x, &next)
      || i < n || r != rows || fabs(x - dx) > 1e-5) {
    fprintf(stderr, "Error: bins = %d, %d, ng = %d, %d; dx = %g, %g\n",
        i, n, r, rows, x, dx);
    fclose(fp);
    return -1;
  }
  delta   = ((fflags & HIST_ADDAHALF) ? .5 : 0.);
  hashist =  (fflags & HIST_KEEPHIST);
  /* scan sums */
  xnew(sums, rows);
  for (p = s+next, r = 0; r < rows; r++) {
    if (1 != sscanf(p, "%lf%n", sums + r, &next)) {
      fprintf(stderr, "cannot read sums from at %d/%d, s:\n%s\np:\n%s\n", r, rows, s, p);
      goto EXIT;
    }
    p += next;
  }
  if ((p = skipabar_(p)) == NULL) goto EXIT;
  for (r = 0; r < rows; r++) {
    if (2 != sscanf(p, "%lf%lf%n", &y, &y2, &next)) {
      fprintf(stderr, "cannot read average/stddev from at %d/%d, s:\n%s\np:\n%s\n", r, rows, s, p);
      goto EXIT;
    }
    p += next;
  }
  if ((p = skipabar_(p)) == NULL) goto EXIT;
  if (frheader != NULL) {
    if (0 != frheader(p, pdata))
      goto EXIT;
  }


  if (!add) { /* clear histogram */
    for (i = 0; i < rows*n; i++) hist[i] = 0.;
  }

  /* loop over r = 0..rows-1 */
  for (r = 0; r < rows; r++) {
    arr = hist + r*n;
    fac = sums[r]*dx;
    while (fgets(s, sizeof s, fp)) {
      nlin++;
      for (p = s+strlen(s)-1; isspace((unsigned char)(*p)) && p >= s; p--)
        *p = '\0'; /* trim ending */
      if (s[0] == '#' || s[0] == '\0') break;
      if (hashist) {
        if (4 != sscanf(s, "%lf%lf%lf%d", &x, &y, &y2, &r1)) {
          fprintf(stderr, "error on line %d\n", nlin);
          goto EXIT;
        }
      } else { /* simple */
        if (3 != sscanf(s, "%lf%lf%d", &x, &y2, &r1)) {
          fprintf(stderr, "error on line %d\n", nlin);
          goto EXIT;
        }
      }
      if (r1 < 0) break; /* overall histogram */

      if (r1 < r) {
        fprintf(stderr, "wrong column index %d vs. %d on line %d, s=[%s]\n",
            r1, r, nlin, s);
        goto EXIT;
      } else if (r1 > r) {
        r = r1;
        arr = hist + r*n;
        fac = sums[r]*dx;
      }
      i1 = (int)((x - xmin)/dx - delta + .5);
      if (i1 < 0 || i1 >= n) {
        fprintf(stderr, "cannot find index for x = %g, delta = %g, i = %d/%d, on line %d\n",
            x, delta, i1, n, nlin);
        goto EXIT;
      }
      if (!hashist) {
        if (fnorm != NULL) {
          fac = (*fnorm)(r, i1, xmin, dx, pdata);
          fac = ((fabs(fac) < 1e-8) ? 1. : 1./fac);
        }
        y = y2*fac;
      }
      if (add) arr[i1] += y;
      else arr[i1] = y;
    }
  }
  if (verbose)
    fprintf(stderr, "histogram loaded successfully from %s\n", fn);

  if (sums) free(sums);
  fclose(fp);
  return 0;
EXIT:
  fprintf(stderr, "error occurs at file %s, line %d, s:%s\n", fn, nlin, s);
  if (sums) free(sums);
  /* we always clear histogram on error */
  for (i = 0; i < rows*n; i++) hist[i] = 0.;
  return -1;
}


/* add x[r] into the rth row of the histogram, h
 * with weight w r = 0..rows-1
 * return the number of successful rows */
INLINE int histadd(const double *xarr, double w, double *h, int rows,
    int n, double xmin, double dx, unsigned flags)
{
  int r, ix, good = 0, verbose = flags & HIST_VERBOSE;
  double x;

  for (r = 0; r < rows; r++) {
    if ( (x = xarr[r]) < xmin ) {
      if (verbose)
        fprintf(stderr, "histadd underflows %d: %g < %g\n", r, x, xmin);
      continue;
    }
    if ( (ix = (int)((x - xmin)/dx)) >= n ) {
      if (verbose)
        fprintf(stderr, "histadd overflows %d: %g > %g\n", r, x, xmin+dx*n);
      continue;
    }
    h[r*n + ix] += w;
    good++;
  }
  return good;
}


/* object wrappers */
typedef struct {
  int rows;
  int n;
  double xmin;
  double dx;
  double *arr;
} hist_t;

typedef hist_t hs_t;

#define hs_clear(hs) dblcleararr(hs->arr, hs->rows * hs->n)


#define hs_open1(x0, x1, dx) hs_open(1, x0, x1, dx)

INLINE hist_t *hs_open(int rows, double xmin, double xmax, double dx)
{
  hist_t *hs;

  xnew(hs, 1);
  hs->rows = rows;
  hs->xmin = xmin;
  hs->dx   = dx;
  hs->n = (int)((xmax - xmin)/dx + 0.99999999);
  xnew(hs->arr, hs->n * hs->rows);
  return hs;
}


INLINE void hs_close(hist_t *hs)
{
  free(hs->arr);
  free(hs);
}


INLINE void hs_check(const hist_t *hs)
{
  die_if (hs == NULL, "hs is %p", (const void *) hs);
  die_if (hs->arr == NULL || hs->rows == 0 || hs->n == 0,
    "hist: arr %p rows %d n %d\n", (const void *)(hs->arr), hs->rows, hs->n);
}


#define hs_save(hs, fn, flags) hs_savex(hs, fn, NULL, NULL, NULL, flags)

INLINE int hs_savex(const hist_t *hs, const char *fn,
    int (*fwheader)(FILE *, void *),
    double (*fnorm)(int, int, double, double, void *),
    void *pdata, unsigned flags)
{
  hs_check(hs);
  return histsavex(hs->arr, hs->rows, hs->n, hs->xmin, hs->dx, fn,
      fwheader, fnorm, pdata, flags);
}


#define hs_load(hs, fn, flags) hs_loadx(hs, fn, NULL, NULL, NULL, flags)

INLINE int hs_loadx(hist_t *hs, const char *fn,
    int (frheader)(const char *, void *),
    double (*fnorm)(int, int, double, double, void *),
    void *pdata, unsigned flags)
{
  hs_check(hs);
  return histloadx(hs->arr, hs->rows, hs->n, hs->xmin, hs->dx, fn,
      frheader, fnorm, pdata, flags);
}


INLINE int hs_add(hist_t *hs, const double *x, double w, unsigned flags)
{
  hs_check(hs);
  return histadd(x, w, hs->arr, hs->rows, hs->n, hs->xmin, hs->dx, flags);
}


#define hs_add1ez(hs, x, flags) hs_add1(hs, 0, x, 1, flags)

INLINE int hs_add1(hist_t *hs, int r, double x, double w, unsigned flags)
{
  hs_check(hs);
  die_if (r >= hs->rows || r < 0, "bad row index %d\n", r);
  return histadd(&x, w, hs->arr + r*hs->n, 1, hs->n, hs->xmin, hs->dx, flags);
}


/* get average of a certain `row' */
INLINE double hs_getave(const hist_t *hs, int row, double *sum, double *var)
{
  double arr[3];

  histgetsums_(hs->arr + row * hs->n, 1, hs->n, hs->xmin, hs->dx, arr);
  if (sum) *sum = arr[0];
  if (var) *var = arr[2];
  return arr[1];
}




/* two dimensional histograms */


#define HIST2_VERBOSE    0x0001
#define HIST2_ADDAHALF   0x0010
#define HIST2_NOZEROES   0x0020
#define HIST2_KEEPLEFT   0x0040
#define HIST2_KEEPRIGHT  0x0080
#define HIST2_KEEPLEFT2  0x0040
#define HIST2_KEEPRIGHT2 0x0080
#define HIST2_KEEPEDGE   (HIST2_KEEPLEFT | HIST2_KEEPRIGHT | HIST2_KEEPLEFT2 | HIST2_KEEPRIGHT2)
#define HIST2_KEEPHIST   0x0100
#define HIST2_OVERALL    0x0200
#define HIST2_ADDITION   0x1000


INLINE void hist2getsums_(const double *h, int n,
    double xmin, double dx, int m, double ymin, double dy, double *s)
{
  double x, y, w;
  int i, j;

  s[0] = s[1] = s[2] = s[3] = s[4] = s[5] = 0;
  for (i = 0; i < n; i++) {
    x = xmin + (i+.5)*dx;
    for (j = 0; j < m; j++) {
      y = ymin + (j+.5)*dy;
      w = h[i*m + j];
      s[0]  += w;
      s[1]  += w * x;
      s[2]  += w * y;
      s[3]  += w * x * x;
      s[4]  += w * x * y;
      s[5]  += w * y * y;
    }
  }
  if ( s[0] > 0 ) {
    s[1] /= s[0];
    s[2] /= s[0];
    s[3]  = s[3] / s[0] - s[1] * s[1];
    s[4]  = s[4] / s[0] - s[1] * s[2];
    s[5]  = s[5] / s[0] - s[2] * s[2];
  }
}


/* write rows n x m histograms to file */
INLINE int hist2save(const double *h, int rows, int n, double xmin, double dx,
    int m, double ymin, double dy, unsigned flags, const char *fn)
{
  const int version = 1; /* v1 allows different dimension in x and y */
  FILE *fp;
  int i, j, r, imax, imin, jmax, jmin, nm;
  const double *p;
  double (*sums)[6], fac, delta;

  if (fn == NULL) fn = "HIST2";
  xfopen(fp, fn, "w", return 1);

  nm = n * m;
  xnew(sums, rows);
  for ( r = 0; r < rows; r++ )
    hist2getsums_(h + nm, n, xmin, dx, m, ymin, dy, sums[r]);
  /* print basic information */
  fprintf(fp, "# %d 0x%X | %d %d %g %g %d %g %g | ",
      version, flags, rows, n, xmin, dx, m, ymin, dy);
  for (r = 0; r < rows; r++) /* number of visits */
    fprintf(fp, "%g ", sums[r][0]);
  fprintf(fp, " | ");
  for (r = 0; r < rows; r++) /* averages and covariance */
    fprintf(fp, "%g %g %g %g %g ", sums[r][1], sums[r][2],
        sums[r][3], sums[r][4], sums[r][5]);
  fprintf(fp, "| \n");

  delta = (flags & HIST2_ADDAHALF) ? 0.5 : 0;

  for (r = 0; r < rows; r++) { /* the rth data set */
    p = h + r*nm;

    if (flags & HIST2_KEEPRIGHT) {
      imax = n;
    } else { /* trim the right edge of i */
      for (i = n-1; i >= 0; i--) {
        for (j = 0; j < m; j++)
          if (p[i*m + j] > 0) break;
        if (j < m) break; /* found a nonzero entry */
      }
      imax = i+1;
      if (imax == 0)
        continue;
    }

    if (flags & HIST2_KEEPLEFT) {
      imin = 0;
    } else { /* trim the left edge of i */
      for (i = 0; i < imax; i++) {
        for (j = 0; j < m; j++)
          if (p[i*m + j] > 0) break;
        if (j < m) break; /* found a nonzero entry */
      }
      imin = i;
    }

    if (flags & HIST2_KEEPRIGHT2) {
      jmax = m;
    } else { /* trim the right edge of j */
      for (j = m-1; j >= 0; j--) {
        for (i = imin; i < imax; i++)
          if (p[i*m + j] > 0) break;
        if (i < imax) break;
      }
      jmax = j+1;
    }

    if (flags & HIST2_KEEPLEFT2) {
      jmin = 0;
    } else { /* trim the left edge of j */
      for (j = 0; j < jmax; j++) {
        for (i = imin; i < imax; i++)
          if (p[i*m + j] > 0) break;
        if (i < imax) break;
      }
      jmin = j;
    }

    if ( fabs(sums[r][0]) < 1e-6 ) fac = 1.;
    else fac = 1.0 / (sums[r][0] * dx * dy);

    for (i = imin; i < imax; i++) {
      for (j = jmin; j < jmax; j++) {
        double x, y;
        if ((flags & HIST2_NOZEROES) && p[i*m + j] < 1e-16)
          continue;
        x = xmin + (i+delta)*dx;
        y = ymin + (j+delta)*dy;
        fprintf(fp, "%g %g ", x, y);
        if (flags & HIST2_KEEPHIST)
          fprintf(fp, "%20.14E ", p[i*m+j]);
        fprintf(fp, "%20.14E %d\n", p[i*m+j]*fac, r);
      }
      fprintf(fp, "\n");
    }
    fprintf(fp, "\n#\n");
  }
  fclose(fp);
  if (flags & HIST2_VERBOSE) {
    fprintf(stderr, "successfully wrote %s\n", fn);
    for (r = 0; r < rows; r++)
      fprintf(stderr, "%2d cnt: %20.4f xav: %10.4f(%10.4f) yav: %10.4f(%10.4f)\n",
          r, sums[r][0], sums[r][1], sums[r][2], sums[r][3], sums[r][4]);
  }
  free(sums);
  return 0;
}


INLINE int hist2load(double *hist, int rows, int n, double xmin, double dx,
    int m, double ymin, double dy, unsigned flags, const char *fn)
{
  FILE *fp;
  int verbose = (flags & HIST2_VERBOSE);
  int add = (flags & HIST2_ADDITION);
  int ver, next, hashist;
  int i, j, r, r1, nm, nlin = 0;
  unsigned fflags;
  double x, y, xx, xy, yy, g, g2, fac, delta, *arr, *sums = NULL;
  double xmin1, dx1, ymin1, dy1;
  char s[40960] = "", *p;

  xfopen(fp, fn, "r", return -1);

  nm = n * m;
  /* check the first line */
  if (fgets(s, sizeof s, fp) == NULL || s[0] != '#') {
    fprintf(stderr, "%s: missing the first line\n", fn);
    fclose(fp);
    return -1;
  }
  nlin++;
  if (9 != sscanf(s, " # %d 0x %X | %d%d%lf%lf%d%lf%lf | %n", &ver, &fflags, &r,
        &i, &xmin1, &dx1, &j, &ymin1, &dy1, &next)
      || i < n || j < m || r != rows
      || fabs(dx1 - dx) > 1e-5 || fabs(dy1 - dy) > 1e-5 ) {
    fprintf(stderr, "Error: bins %d, %d; %d, %d; ng %d, %d; dx %g, %g; dy %g, %g\n",
        i, n, j, m, r, rows, dx1, dx, dy1, dy);
    fclose(fp);
    return -1;
  }
  delta   = ((fflags & HIST2_ADDAHALF) ? .5 : 0.);
  hashist =  (fflags & HIST2_KEEPHIST);
  /* scan sums */
  xnew(sums, rows);
  for (p = s+next, r = 0; r < rows; r++) {
    if (1 != sscanf(p, "%lf%n", sums + r, &next)) {
      fprintf(stderr, "cannot read sums from at %d/%d, s:\n%s\np:\n%s\n", r, rows, s, p);
      goto EXIT;
    }
    p += next;
  }
  if ((p = skipabar_(p)) == NULL) goto EXIT;
  for (r = 0; r < rows; r++) {
    if (5 != sscanf(p, "%lf%lf%lf%lf%lf%n", &x, &y, &xx, &xy, &yy, &next)) {
      fprintf(stderr, "cannot read ave./cov. from at %d/%d, s:\n%s\np:\n%s\n", r, rows, s, p);
      goto EXIT;
    }
    p += next;
  }
  if ((p = skipabar_(p)) == NULL) goto EXIT;

  if ( !add ) { /* clear histogram */
    for (i = 0; i < rows*nm; i++) hist[i] = 0.;
  }

  /* loop over r = 0..rows-1 */
  for (r = 0; r < rows; r++) {
    arr = hist + r*nm;
    fac = sums[r] * dx * dy;
    while (fgets(s, sizeof s, fp)) {
      nlin++;
      for (p = s+strlen(s)-1; p >= s && isspace((unsigned char)(*p)); p--)
        *p = '\0'; /* trim ending */
      if (s[0] == '#') break;
      if (s[0] == '\0') continue;

      if (hashist) {
        if (5 != sscanf(s, "%lf%lf%lf%lf%d", &x, &y, &g, &g2, &r1)) {
          fprintf(stderr, "error on line %d\n", nlin);
          goto EXIT;
        }
      } else {
        if (4 != sscanf(s, "%lf%lf%lf%d", &x, &y, &g2, &r1)) {
          fprintf(stderr, "error on line %d\n", nlin);
          goto EXIT;
        }
      }
      if (r1 != r) {
        fprintf(stderr, "wrong column index %d vs. %d on line %d\n",
          r1, r, nlin);
        goto EXIT;
      }
      i = (int)((x - xmin)/dx - delta + .5);
      if (i < 0 || i >= n) {
        fprintf(stderr, "cannot find index for x = %g\n", x);
        goto EXIT;
      }
      j = (int)((y - ymin)/dy - delta + .5);
      if (j < 0 || j >= m) {
        fprintf(stderr, "cannot find index for y = %g\n", y);
        return -1;
      }
      if (!hashist) {
        g = g2*fac;
      }
      if (add) arr[i*m+j] += g;
      else arr[i*m+j] = g;
    }
  }
  if (verbose) fprintf(stderr, "%s loaded successfully\n", fn);
  fclose(fp);
  return 0;
EXIT:
  fprintf(stderr, "error occurs at file %s, line %d, s:%s\n", fn, nlin, s);
  if (sums) free(sums);
  for (i = 0; i < rows*nm; i++) hist[i] = 0.;
  fclose(fp);
  return -1;
}


/* add (x, y) into the histogram h with weight w
 * return the number of successful rows */
INLINE int hist2add1(double x, double y, double w, double *h,
    int n, double xmin, double dx,
    int m, double ymin, double dy, int verbose)
{
  int ix, iy;

  if ( x < xmin ) {
    if ( verbose )
      fprintf(stderr, "hist2add underflows: x %g < %g\n",
          x, xmin);
    return -1;
  }
  if ( y < xmin ) {
    if ( verbose )
      fprintf(stderr, "hist2add underflows: y %g < %g\n",
          y, ymin);
    return -1;
  }
  if ( (ix = (int)((x - xmin)/dx)) >= n ) {
    if (verbose)
      fprintf(stderr, "hist2add overflows: x %g > %g\n",
          x, xmin + dx*n);
    return -1;
  }
  if ( (iy = (int)((y - ymin)/dy)) >= m ) {
    if (verbose)
      fprintf(stderr, "hist2add overflows: y %g > %g\n",
          y, ymin + dy*m);
    return -1;
  }
  h[ix*m + iy] += w;
  return 0;
}


/* add (xarr[stride * r], yarr[stride * r]) of weight w
 * into the rth row of histogram h, r = 0..rows - 1
 * return the number of successful rows */
INLINE int hist2add(const double *xarr, const double *yarr, int stride,
    double w, double *h, int rows,
    int n, double xmin, double dx,
    int m, double ymin, double dy, unsigned flags)
{
  int r, ix, iy, good = 0, verbose = flags & HIST2_VERBOSE;
  double x, y;

  for (r = 0; r < rows; r++) {
    if ( (x = xarr[stride * r]) < xmin ) {
      if ( verbose )
        fprintf(stderr, "hist2add underflows, row %d: x %g < %g\n",
            r, x, xmin);
      continue;
    }
    if ( (y = yarr[stride * r]) < xmin ) {
      if ( verbose )
        fprintf(stderr, "hist2add underflows, row %d: y %g < %g\n",
            r, y, ymin);
      continue;
    }
    if ( (ix = (int)((x - xmin)/dx)) >= n ) {
      if (verbose)
        fprintf(stderr, "hist2add overflows, row %d: x %g > %g\n",
            r, x, xmin + dx*n);
      continue;
    }
    if ( (iy = (int)((y - ymin)/dy)) >= m ) {
      if (verbose)
        fprintf(stderr, "hist2add overflows, row %d: y %g > %g\n",
            r, y, ymin + dy*m);
      continue;
    }
    h[r*n*m + ix*m + iy] += w;
    good++;
  }
  return good;
}


typedef struct {
  int rows;
  int n, m;
  double xmin, ymin;
  double dx, dy;
  double *arr, *dumptr;
} hist2_t;

typedef hist2_t hs2_t;

#define hs2_clear(hs2) dblcleararr(hs2->arr, hs2->rows * hs2->n * hs2->m)

#define hs2_open1(xmin, xmax, dx, ymin, ymax, dy) \
  hs2_open(1, xmin, xmax, dx, ymin, ymax, dy)

INLINE hist2_t *hs2_open(int rows, double xmin, double xmax, double dx,
    double ymin, double ymax, double dy)
{
  hist2_t *hs2;

  xnew(hs2, 1);
  hs2->rows = rows;
  hs2->xmin = xmin;
  hs2->dx   = dx;
  hs2->n    = (int)((xmax - xmin)/dx + 0.99999999);
  hs2->ymin = ymin;
  hs2->dy   = dy;
  hs2->m    = (int)((ymax - ymin)/dy + 0.99999999);
  xnew(hs2->arr, hs2->n * hs2->m * hs2->rows);
  return hs2;
}


INLINE void hs2_close(hist2_t *hs2)
{
  free(hs2->arr);
  free(hs2);
}


INLINE void hs2_check(const hist2_t *hs)
{
  die_if (hs == NULL, "hist2 is %p", (const void *) hs);
  die_if (hs->arr == NULL || hs->rows == 0 || hs->n == 0 || hs->m == 0,
    "hist2: arr %p rows %d n %d m %d\n",
    (const void *)(hs->arr), hs->rows, hs->n, hs->m);
}


INLINE int hs2_save(const hist2_t *hs, const char *fn, unsigned flags)
{
  hs2_check(hs);
  return hist2save(hs->arr, hs->rows, hs->n, hs->xmin, hs->dx,
      hs->m, hs->ymin, hs->dy, flags, fn);
}


INLINE int hs2_load(hist2_t *hs, const char *fn, unsigned flags)
{
  hs2_check(hs);
  return hist2load(hs->arr, hs->rows, hs->n, hs->xmin, hs->dx,
      hs->m, hs->ymin, hs->dy, flags, fn);
}


#define hs2_add1ez(hs, x, y, flags) hs2_add1(hs, 0, x, y, 1.0, flags)

INLINE int hs2_add1(hist2_t *hs, int r, double x, double y,
    double w, unsigned flags)
{
  hs2_check(hs);
  return hist2add1(x, y, w, hs->arr+r*hs->n*hs->m,
      hs->n, hs->xmin, hs->dx, hs->m, hs->ymin, hs->dy, flags & HIST2_VERBOSE);
}


INLINE int hs2_add(hist2_t *hs, const double *x, const double *y, int stride,
    double w, unsigned flags)
{
  int r, good = 0;
  hs2_check(hs);
  for ( r = 0; r < hs->rows; r++ )
    good += (hs2_add1(hs, r, x[stride*r], y[stride*r], w, flags) == 0);
  return good;
}


#endif /* ZCOM_HIST__ */
#endif /* ZCOM_HIST */





#ifdef  ZCOM_RNG
#ifndef ZCOM_RNG__
#define ZCOM_RNG__

#include <stdio.h>
#include <string.h>
#include <math.h>

#define MTFILE    "MTSEED"  /* default file */
#define MTSEED    5489UL    /* default seed */

/* Mersenne Twister was developed by Makoto Matsumoto and Takuji Nishimura */
#define MT_N 624
#define MT_M 397
#define MT_UMASK 0x80000000UL /* most significant w-r bits */
#define MT_LMASK 0x7fffffffUL /* least significant r bits */

typedef struct {
  int idx;
  uint32_t arr[MT_N];
} mtrng_t;


/* local copy for convenience */
STRCLS mtrng_t mrstock_ = {-1, {0}}; /* index in mr_, -1: uninitialized */

STRCLS mtrng_t *mr_ = &mrstock_;
/* by default `mr_' is pointed to `mtstock_', but we replace it
 * by a thread private version by calling mtmkprivate(seed)
 * this trick allows the different random numbers generated
 * from different threads even by calling the default versions
 * of the functions, e.g., rand01() */
#ifdef _OPENMP
#pragma omp threadprivate(mr_)
#endif


/* in the default scrambling, we create a new RNG to be safe */
#define mtscramble(seed) { \
  if (mr_ == &mrstock_) mr_ = mtrng_open0(); \
  mtrng_scramble(mr_, seed); }

/* free the default RNG */
#define mtclosedef() { if (mr_ != &mrstock_) mtrng_close(mr_); }


/* default versions */
#define mtsave(fn)          mtrng_save(mr_, fn)
#define mtload(fn, seed)    mtrng_load(mr_, fn, seed)
#define mtrand()            mtrng_rand(mr_)
#define rand32()            mtrng_rand32(mr_)
#define rand01()            mtrng_rand01(mr_) /* double, [0, 1) */
#define randunif(a, b)      mtrng_randunif(mr_, a, b) /* double, [a, b) */
#define randgaus()          mtrng_randgaus(mr_)
#define randgam(k)          mtrng_randgam(mr_, k)
#define randchisqr(n)       mtrng_randchisqr(mr_, n)
#define randpair(n, j)      mtrng_randpair(mr_, n, j)
#define metroacc0(r)        mtrng_metroacc0(mr_, r)
#define metroacc1(de, bet)  mtrng_metroacc1(mr_, de, bet)

/* old aliases */
#define rnd0()              rand01()
#define rnd(a, b)           randunif(a, b)
#define grand0()            randgaus()


INLINE mtrng_t *mtrng_open0(void)
{
  mtrng_t *mr;

  xnew(mr, 1);
  mr->idx = -1;
  return mr;
}


INLINE void mtrng_close(mtrng_t *mr)
{
  free(mr);
}


/* save the current state to file */
INLINE int mtrng_save(mtrng_t *mr, const char *fn)
{
  FILE *fp;
  int k;

  if (mr->idx < 0) return 1; /* RNG was never used, so it cannot be saved */
  if (fn == NULL) fn = MTFILE;
  xfopen(fp, fn, "w", return -1);
  fprintf(fp, "MTSEED\n%d\n", mr->idx);
  for (k = 0; k < MT_N; k++)
    fprintf(fp, "%" PRIu32 "\n", mr->arr[k]);
  fclose(fp);
  return 0;
}


/* randomize the array `mr_' */
INLINE void mtrng_scramble(mtrng_t *mr, uint32_t seed)
{
  int k;

  mr->arr[0] = ((seed + MTSEED) * 314159265ul + 271828183ul) & 0xfffffffful;
  for (k = 1; k < MT_N; k++) { /* the final mask is for 64-bit machines */
    mr->arr[k] = 1812433253ul * (mr->arr[k - 1] ^ (mr->arr[k - 1] >> 30)) + k;
    /* mr->arr[k] = (mr->arr[k] + seed) * 22695477ul + 1ul; */
    mr->arr[k] = ((mr->arr[k] + seed) * 314159265ul + 1ul) & 0xfffffffful;
  }
  mr->idx = MT_N; /* request for an update */
}


INLINE mtrng_t *mtrng_open(uint32_t seed)
{
  mtrng_t *mr = mtrng_open0();
  mtrng_scramble(mr, seed);
  return mr;
}


/* load mr state from `fn', or if it fails, use `seed' to initialize mr  */
INLINE int mtrng_load(mtrng_t *mr, const char *fn, uint32_t seed)
{
  char s[64];
  int k, z, err = 1;
  FILE *fp;

  if (fn == NULL) fn = MTFILE;
  if ((fp = fopen(fn, "r")) != NULL) { /* try to load from file */
    if (fgets(s, sizeof s, fp) == NULL) {
      fprintf(stderr, "%s is empty\n", fn);
    } else if (strncmp(s, "MTSEED", 6) != 0) { /* to check the first line */
      fprintf(stderr, "%s corrupted\n", fn);
    } else if (fscanf(fp, "%d", &mr->idx) != 1) {
      fprintf(stderr, "no index in %s\n", fn);
    } else {
      if (mr->idx < 0) mr->idx = MT_N; /* request updating */
      for (z = 1, k = 0; k < MT_N; k++) {
        if (fscanf(fp, "%" SCNu32, &mr->arr[k]) != 1) break;
        if (mr->arr[k] != 0) z = 0; /* a non-zero number */
      }
      if (k != MT_N) fprintf(stderr, "%s incomplete %d/%d\n", fn, k, MT_N);
      else err = z; /* clear error, if array is nonzero */
    }
    fclose(fp);
  }

  if (err) mtrng_scramble(mr, seed);
  return (mr->idx < 0);
}


#define mtrng_rand32(mr) mtrng_rand(mr)
/* must be double to avoid the round-off error that gives >= 1 result */
#define mtrng_rand01(mr) (mtrng_rand32(mr) * (1./4294967296.0)) /* double, [0, 1) */
#define mtrng_randunif(mr, a, b) ((a) + ((b) - (a)) * mtrng_rand01(mr)) /* double, [a, b) */

/* return an unsigned random number */
INLINE uint32_t mtrng_rand(mtrng_t *mr)
{
  static const uint32_t mag01[2] = {0, 0x9908b0dfUL}; /* MATRIX_A */
#ifdef _OPENMP
#pragma omp threadprivate(mag01)
#endif
  uint32_t x;
  int k;

  if (mr->idx < 0) mtrng_load(mr, NULL, 0);
  if (mr->idx >= MT_N) { /* generate MT_N words at one time */
    for (k = 0; k < MT_N - MT_M; k++) {
      x = (mr->arr[k] & MT_UMASK) | (mr->arr[k+1] & MT_LMASK);
      mr->arr[k] = mr->arr[k+MT_M] ^ (x>>1) ^ mag01[x&1UL];
    }
    for (; k < MT_N-1; k++) {
      x = (mr->arr[k] & MT_UMASK) | (mr->arr[k+1] & MT_LMASK);
      mr->arr[k] = mr->arr[k+(MT_M-MT_N)] ^ (x>>1) ^ mag01[x&1UL];
    }
    x = (mr->arr[MT_N-1] & MT_UMASK) | (mr->arr[0] & MT_LMASK);
    mr->arr[MT_N-1] = mr->arr[MT_M-1] ^ (x>>1) ^ mag01[x&1UL];
    mr->idx = 0;
  }
  x = mr->arr[ mr->idx++ ];
  /* tempering */
  x ^= (x >> 11);
  x ^= (x <<  7) & 0x9d2c5680UL;
  x ^= (x << 15) & 0xefc60000UL;
  x ^= (x >> 18);
  return x;
}


#undef MT_N
#undef MT_M
#undef MT_UMASK
#undef MT_LMASK


/* Gaussian distribution with zero mean and unit variance
 * using ratio method */
INLINE double mtrng_randgaus(mtrng_t *mr)
{
  double x, y, u, v, q;
  do {
    u = 1 - mtrng_rand01(mr);
    v = 1.7156*(mtrng_rand01(mr) - .5);  /* >= 2*sqrt(2/e) */
    x = u - 0.449871;
    y = fabs(v) + 0.386595;
    q = x*x  + y*(0.196*y - 0.25472*x);
    if (q < 0.27597) break;
  } while (q > 0.27846 || v*v > -4*u*u*log(u));
  return v/u;
}


/* return a random number that satisfies the gamma distribution
 * p(x) = x^(k - 1) exp(-x) / Gamma(k) */
INLINE double mtrng_randgam(mtrng_t *mr, double k)
{
  int lt1 = 0;
  double a, b, x, v, u;

  if (k <= 0) {
    fprintf(stderr, "mtrng_randgam: k %g must be positive\n", k);
    return 0.;
  }
  if ( k < 1 ) {
    lt1 = 1;
    k += 1;
  }
  a = k - 1./3;
  b = 1./3/sqrt(a);

  for ( ; ; ) {
    do {
      x = mtrng_randgaus(mr);
      v = 1 + b * x;
    } while ( v <= 0 );
    v *= v * v;
    x *= x;
    u = mtrng_rand01(mr);
    if ( u <= 1 - 0.331 * x * x ) break;
    u = log(u);
    if ( u <= 0.5 * x + a * (1 - v + log(v)) ) break;
  }

  x = a * v;
  if ( lt1 ) x *= pow(1 - mtrng_rand01(mr), 1./(k - 1));
  return x;
}


/* return a random number that satisfies the chi-squared distribution,
 * which is the sum of the squares n Gaussian random numbers */
INLINE double mtrng_randchisqr(mtrng_t *mr, double n)
{
  return 2 * mtrng_randgam(mr, n*.5);
}


/* random pair index (i, j) */
INLINE int mtrng_randpair(mtrng_t *mr, int n, int *j)
{
  int pid = (int) (mtrng_rand01(mr) * n * (n - 1)), i;
  i = pid / (n - 1);
  *j = pid - i * (n - 1);
  if (*j >= i) (*j)++;
  return i;
}


/* Metropolis acceptance probability rand01() < exp(- bet * de), assuming bet > 0
 * defined as a macro, in case r is an integer */
#define mtrng_metroacc1(mr, de, bet) \
  ((de <= 0) ? 1 : mtrng_metroacc0(mr, -bet * de))

/* Metropolis acceptance probability rand01() < exp(r), assuming r > 0 */
INLINE int mtrng_metroacc0(mtrng_t *mr, double r)
{
  r = exp(r);
  return mtrng_rand01(mr) < r;
}


#endif /* ZCOM_RNG__ */
#endif /* ZCOM_RNG */





#ifdef  ZCOM_RC
#ifndef ZCOM_RC__
#define ZCOM_RC__
/* routines for complex numbers
 * the functions are similar to the rv2_ ones
 * but here the structures instead of the pointers are passed to the functions */


typedef struct { float re, im; } fcomplex_t;

typedef struct { double re, im; } dcomplex_t;

typedef struct { real re, im; } rcomplex_t;

#if 0
/* complex zero */
static const rcomplex_t rc_zero = {0.f, 0.f};
#endif


/* make complex */
INLINE fcomplex_t fc_make(float re, float im)
{
  fcomplex_t a;
  a.re = re;
  a.im = im;
  return a;
}

/* make complex */
INLINE dcomplex_t dc_make(double re, double im)
{
  dcomplex_t a;
  a.re = re;
  a.im = im;
  return a;
}

/* make complex */
INLINE rcomplex_t rc_make(real re, real im)
{
  rcomplex_t a;
  a.re = re;
  a.im = im;
  return a;
}


/* complex conjugate */
INLINE fcomplex_t fc_conj(fcomplex_t a)
{
  a.im = - a.im;
  return a;
}

/* complex conjugate */
INLINE dcomplex_t dc_conj(dcomplex_t a)
{
  a.im = - a.im;
  return a;
}

/* complex conjugate */
INLINE rcomplex_t rc_conj(rcomplex_t a)
{
  a.im = - a.im;
  return a;
}


/* norm */
#define fc_norm(a) (float) sqrt( fc_norm2(a) )

/* norm */
#define dc_norm(a) (double) sqrt( dc_norm2(a) )

/* norm */
#define rc_norm(a) (real) sqrt( rc_norm2(a) )

/* square of the norm */
INLINE float fc_norm2(fcomplex_t a)
{
  return a.re * a.re + a.im * a.im;
}

/* square of the norm */
INLINE double dc_norm2(dcomplex_t a)
{
  return a.re * a.re + a.im * a.im;
}

/* square of the norm */
INLINE real rc_norm2(rcomplex_t a)
{
  return a.re * a.re + a.im * a.im;
}


/* complex times float */
INLINE fcomplex_t fc_smul(fcomplex_t a, float s)
{
  a.re *= s;
  a.im *= s;
  return a;
}

/* complex times double */
INLINE dcomplex_t dc_smul(dcomplex_t a, double s)
{
  a.re *= s;
  a.im *= s;
  return a;
}

/* complex times real */
INLINE rcomplex_t rc_smul(rcomplex_t a, real s)
{
  a.re *= s;
  a.im *= s;
  return a;
}


/* complex divided by float  */
INLINE fcomplex_t fc_sdiv(fcomplex_t a, float s)
{
  a.re /= s;
  a.im /= s;
  return a;
}

/* complex divided by double  */
INLINE dcomplex_t dc_sdiv(dcomplex_t a, double s)
{
  a.re /= s;
  a.im /= s;
  return a;
}

/* complex divided by real  */
INLINE rcomplex_t rc_sdiv(rcomplex_t a, real s)
{
  a.re /= s;
  a.im /= s;
  return a;
}


/* addition */
INLINE fcomplex_t fc_add(fcomplex_t a, fcomplex_t b)
{
  a.re += b.re;
  a.im += b.im;
  return a;
}

/* addition */
INLINE dcomplex_t dc_add(dcomplex_t a, dcomplex_t b)
{
  a.re += b.re;
  a.im += b.im;
  return a;
}

/* addition */
INLINE rcomplex_t rc_add(rcomplex_t a, rcomplex_t b)
{
  a.re += b.re;
  a.im += b.im;
  return a;
}


/* a + s * b */
INLINE fcomplex_t fc_sadd(fcomplex_t a, fcomplex_t b, float s)
{
  a.re += b.re * s;
  a.im += b.re * s;
  return a;
}

/* a + s * b */
INLINE dcomplex_t dc_sadd(dcomplex_t a, dcomplex_t b, double s)
{
  a.re += b.re * s;
  a.im += b.re * s;
  return a;
}

/* a + s * b */
INLINE rcomplex_t rc_sadd(rcomplex_t a, rcomplex_t b, real s)
{
  a.re += b.re * s;
  a.im += b.re * s;
  return a;
}


/* multiplication */
INLINE fcomplex_t fc_mul(fcomplex_t a, fcomplex_t b)
{
  fcomplex_t c;
  c.re = a.re * b.re - a.im * b.im;
  c.im = a.re * b.im + a.im * b.re;
  return c;
}

/* multiplication */
INLINE dcomplex_t dc_mul(dcomplex_t a, dcomplex_t b)
{
  dcomplex_t c;
  c.re = a.re * b.re - a.im * b.im;
  c.im = a.re * b.im + a.im * b.re;
  return c;
}

/* multiplication */
INLINE rcomplex_t rc_mul(rcomplex_t a, rcomplex_t b)
{
  rcomplex_t c;
  c.re = a.re * b.re - a.im * b.im;
  c.im = a.re * b.im + a.im * b.re;
  return c;
}


/* a / b */
INLINE fcomplex_t fc_div(fcomplex_t a, fcomplex_t b)
{
  float nm2 = fc_norm2(b);
  return fc_sdiv( fc_mul(a, fc_conj(b)), nm2 );
}

/* a / b */
INLINE dcomplex_t dc_div(dcomplex_t a, dcomplex_t b)
{
  double nm2 = dc_norm2(b);
  return dc_sdiv( dc_mul(a, dc_conj(b)), nm2 );
}

/* a / b */
INLINE rcomplex_t rc_div(rcomplex_t a, rcomplex_t b)
{
  real nm2 = rc_norm2(b);
  return rc_sdiv( rc_mul(a, rc_conj(b)), nm2 );
}

#endif /* ZCOM_RC__ */
#endif /* ZCOM_RC */





#ifdef  ZCOM_RV2
#ifndef ZCOM_RV2__
#define ZCOM_RV2__
#include <stdio.h>
#include <string.h>
#include <math.h>


#ifndef FV2_T
#define FV2_T fv2_t
typedef float fv2_t[2];
#endif

#ifndef DV2_T
#define DV2_T dv2_t
typedef double dv2_t[2];
#endif

#ifndef RV2_T
#define RV2_T rv2_t
typedef real rv2_t[2];
#endif


#define fv2_print(r, nm, fmt, nl) fv2_fprint(stdout, r, nm, fmt, nl)

#define dv2_print(r, nm, fmt, nl) dv2_fprint(stdout, r, nm, fmt, nl)

#define rv2_print(r, nm, fmt, nl) rv2_fprint(stdout, r, nm, fmt, nl)

INLINE void fv2_fprint(FILE *fp, const float *r, const char *nm,
    const char *fmt, int nl)
{
  int i;
  if (nm) fprintf(fp, "%s: ", nm);
  for (i = 0; i < 2; i++)
    fprintf(fp, fmt, r[i], nl);
  fprintf(fp, "%c", (nl ? '\n' : ';'));
}

INLINE void dv2_fprint(FILE *fp, const double *r, const char *nm,
    const char *fmt, int nl)
{
  int i;
  if (nm) fprintf(fp, "%s: ", nm);
  for (i = 0; i < 2; i++)
    fprintf(fp, fmt, r[i], nl);
  fprintf(fp, "%c", (nl ? '\n' : ';'));
}

INLINE void rv2_fprint(FILE *fp, const real *r, const char *nm,
    const char *fmt, int nl)
{
  int i;
  if (nm) fprintf(fp, "%s: ", nm);
  for (i = 0; i < 2; i++)
    fprintf(fp, fmt, r[i], nl);
  fprintf(fp, "%c", (nl ? '\n' : ';'));
}


/* due to that pointer may overlap with each other,
 * be careful when using the const modifier */
INLINE float *fv2_make(float *x, float a, float b)
{
  x[0] = a;
  x[1] = b;
  return x;
}

/* due to that pointer may overlap with each other,
 * be careful when using the const modifier */
INLINE double *dv2_make(double *x, double a, double b)
{
  x[0] = a;
  x[1] = b;
  return x;
}

/* due to that pointer may overlap with each other,
 * be careful when using the const modifier */
INLINE real *rv2_make(real *x, real a, real b)
{
  x[0] = a;
  x[1] = b;
  return x;
}


#define fv2_makev(rx, x) fv2_make(rx, (float) x[0], (float) x[1])

#define dv2_makev(rx, x) dv2_make(rx, (double) x[0], (double) x[1])

#define rv2_makev(rx, x) rv2_make(rx, (real) x[0], (real) x[1])


#define fv2_zero(x) fv2_make(x, 0, 0)

#define dv2_zero(x) dv2_make(x, 0, 0)

#define rv2_zero(x) rv2_make(x, 0, 0)


INLINE float *fv2_copy(float *x, const float *src)
{
  x[0] = src[0];
  x[1] = src[1];
  return x;
}

INLINE double *dv2_copy(double *x, const double *src)
{
  x[0] = src[0];
  x[1] = src[1];
  return x;
}

INLINE real *rv2_copy(real *x, const real *src)
{
  x[0] = src[0];
  x[1] = src[1];
  return x;
}


/* use macro to avoid const qualifier of src */
#define fv2_ncopy(x, src, n) memcpy(x, src, 2*n*sizeof(float))

/* use macro to avoid const qualifier of src */
#define dv2_ncopy(x, src, n) memcpy(x, src, 2*n*sizeof(double))

/* use macro to avoid const qualifier of src */
#define rv2_ncopy(x, src, n) memcpy(x, src, 2*n*sizeof(real))


INLINE void fv2_swap(float * RESTRICT x, float * RESTRICT y)
{
  float z[2];
  fv2_copy(z, x);
  fv2_copy(x, y);
  fv2_copy(y, z);
}

INLINE void dv2_swap(double * RESTRICT x, double * RESTRICT y)
{
  double z[2];
  dv2_copy(z, x);
  dv2_copy(x, y);
  dv2_copy(y, z);
}

INLINE void rv2_swap(real * RESTRICT x, real * RESTRICT y)
{
  real z[2];
  rv2_copy(z, x);
  rv2_copy(x, y);
  rv2_copy(y, z);
}


INLINE float fv2_sqr(const float *x)
{
  return x[0] * x[0] + x[1] * x[1];
}

INLINE double dv2_sqr(const double *x)
{
  return x[0] * x[0] + x[1] * x[1];
}

INLINE real rv2_sqr(const real *x)
{
  return x[0] * x[0] + x[1] * x[1];
}


INLINE float fv2_norm(const float *x)
{
  return (float) sqrt(fv2_sqr(x));
}

INLINE double dv2_norm(const double *x)
{
  return (double) sqrt(dv2_sqr(x));
}

INLINE real rv2_norm(const real *x)
{
  return (real) sqrt(rv2_sqr(x));
}


INLINE float fv2_dot(const float *x, const float *y)
{
  return x[0] * y[0] + x[1] * y[1];
}

INLINE double dv2_dot(const double *x, const double *y)
{
  return x[0] * y[0] + x[1] * y[1];
}

INLINE real rv2_dot(const real *x, const real *y)
{
  return x[0] * y[0] + x[1] * y[1];
}


INLINE float fv2_cross(const float *x, const float *y)
{
  return x[0] * y[1] - x[1] * y[0];
}

INLINE double dv2_cross(const double *x, const double *y)
{
  return x[0] * y[1] - x[1] * y[0];
}

INLINE real rv2_cross(const real *x, const real *y)
{
  return x[0] * y[1] - x[1] * y[0];
}


INLINE float *fv2_neg(float * RESTRICT x)
{
  x[0] = -x[0];
  x[1] = -x[1];
  return x;
}

INLINE double *dv2_neg(double * RESTRICT x)
{
  x[0] = -x[0];
  x[1] = -x[1];
  return x;
}

INLINE real *rv2_neg(real * RESTRICT x)
{
  x[0] = -x[0];
  x[1] = -x[1];
  return x;
}


INLINE float *fv2_neg2(float * RESTRICT nx, const float *x)
{
  nx[0] = -x[0];
  nx[1] = -x[1];
  return nx;
}

INLINE double *dv2_neg2(double * RESTRICT nx, const double *x)
{
  nx[0] = -x[0];
  nx[1] = -x[1];
  return nx;
}

INLINE real *rv2_neg2(real * RESTRICT nx, const real *x)
{
  nx[0] = -x[0];
  nx[1] = -x[1];
  return nx;
}


INLINE float *fv2_inc(float * RESTRICT x, const float *dx)
{
  x[0] += dx[0];
  x[1] += dx[1];
  return x;
}

INLINE double *dv2_inc(double * RESTRICT x, const double *dx)
{
  x[0] += dx[0];
  x[1] += dx[1];
  return x;
}

INLINE real *rv2_inc(real * RESTRICT x, const real *dx)
{
  x[0] += dx[0];
  x[1] += dx[1];
  return x;
}


INLINE float *fv2_dec(float * RESTRICT x, const float *dx)
{
  x[0] -= dx[0];
  x[1] -= dx[1];
  return x;
}

INLINE double *dv2_dec(double * RESTRICT x, const double *dx)
{
  x[0] -= dx[0];
  x[1] -= dx[1];
  return x;
}

INLINE real *rv2_dec(real * RESTRICT x, const real *dx)
{
  x[0] -= dx[0];
  x[1] -= dx[1];
  return x;
}


INLINE float *fv2_sinc(float * RESTRICT x, const float *dx, float s)
{
  x[0] += s*dx[0];
  x[1] += s*dx[1];
  return x;
}

INLINE double *dv2_sinc(double * RESTRICT x, const double *dx, double s)
{
  x[0] += s*dx[0];
  x[1] += s*dx[1];
  return x;
}

INLINE real *rv2_sinc(real * RESTRICT x, const real *dx, real s)
{
  x[0] += s*dx[0];
  x[1] += s*dx[1];
  return x;
}


INLINE float *fv2_smul(float *x, float s)
{
  x[0] *= s;
  x[1] *= s;
  return x;
}

INLINE double *dv2_smul(double *x, double s)
{
  x[0] *= s;
  x[1] *= s;
  return x;
}

INLINE real *rv2_smul(real *x, real s)
{
  x[0] *= s;
  x[1] *= s;
  return x;
}


INLINE float *fv2_smul2(float * RESTRICT y, const float *x, float s)
{
  y[0] = x[0] * s;
  y[1] = x[1] * s;
  return y;
}

INLINE double *dv2_smul2(double * RESTRICT y, const double *x, double s)
{
  y[0] = x[0] * s;
  y[1] = x[1] * s;
  return y;
}

INLINE real *rv2_smul2(real * RESTRICT y, const real *x, real s)
{
  y[0] = x[0] * s;
  y[1] = x[1] * s;
  return y;
}


INLINE float *fv2_normalize(float *x)
{
  float r = fv2_norm(x);
  if (r > 0.f) fv2_smul(x, 1.f/r);
  return x;
}

INLINE double *dv2_normalize(double *x)
{
  double r = dv2_norm(x);
  if (r > 0.f) dv2_smul(x, 1.f/r);
  return x;
}

INLINE real *rv2_normalize(real *x)
{
  real r = rv2_norm(x);
  if (r > 0.f) rv2_smul(x, 1.f/r);
  return x;
}


INLINE float *fv2_makenorm(float *v, float x, float y)
{
  return fv2_normalize( fv2_make(v, x, y) );
}

INLINE double *dv2_makenorm(double *v, double x, double y)
{
  return dv2_normalize( dv2_make(v, x, y) );
}

INLINE real *rv2_makenorm(real *v, real x, real y)
{
  return rv2_normalize( rv2_make(v, x, y) );
}


/* for in-place difference use fv2_dec */
INLINE float *fv2_diff(float * RESTRICT c, const float *a, const float *b)
{
  c[0] = a[0] - b[0];
  c[1] = a[1] - b[1];
  return c;
}

/* for in-place difference use dv2_dec */
INLINE double *dv2_diff(double * RESTRICT c, const double *a, const double *b)
{
  c[0] = a[0] - b[0];
  c[1] = a[1] - b[1];
  return c;
}

/* for in-place difference use rv2_dec */
INLINE real *rv2_diff(real * RESTRICT c, const real *a, const real *b)
{
  c[0] = a[0] - b[0];
  c[1] = a[1] - b[1];
  return c;
}

/* distance^2 between a and b */
INLINE float fv2_dist2(const float *a, const float *b)
{
  float d0 = a[0] - b[0], d1 = a[1] - b[1];
  return d0*d0 + d1*d1;
}

/* distance^2 between a and b */
INLINE double dv2_dist2(const double *a, const double *b)
{
  double d0 = a[0] - b[0], d1 = a[1] - b[1];
  return d0*d0 + d1*d1;
}

/* distance^2 between a and b */
INLINE real rv2_dist2(const real *a, const real *b)
{
  real d0 = a[0] - b[0], d1 = a[1] - b[1];
  return d0*d0 + d1*d1;
}


/* distance between a and b */
INLINE float fv2_dist(const float *a, const float *b)
{
  float d0 = a[0] - b[0], d1 = a[1] - b[1];
  return (float) sqrt(d0*d0 + d1*d1);
}

/* distance between a and b */
INLINE double dv2_dist(const double *a, const double *b)
{
  double d0 = a[0] - b[0], d1 = a[1] - b[1];
  return (double) sqrt(d0*d0 + d1*d1);
}

/* distance between a and b */
INLINE real rv2_dist(const real *a, const real *b)
{
  real d0 = a[0] - b[0], d1 = a[1] - b[1];
  return (real) sqrt(d0*d0 + d1*d1);
}


/* c = a + b, for in-place addition use fv2_inc */
INLINE float *fv2_add(float * RESTRICT c, const float *a, const float *b)
{
  c[0] = a[0] + b[0];
  c[1] = a[1] + b[1];
  return c;
}

/* c = a + b, for in-place addition use dv2_inc */
INLINE double *dv2_add(double * RESTRICT c, const double *a, const double *b)
{
  c[0] = a[0] + b[0];
  c[1] = a[1] + b[1];
  return c;
}

/* c = a + b, for in-place addition use rv2_inc */
INLINE real *rv2_add(real * RESTRICT c, const real *a, const real *b)
{
  c[0] = a[0] + b[0];
  c[1] = a[1] + b[1];
  return c;
}


/* c = - a - b */
INLINE float *fv2_nadd(float * RESTRICT c, const float *a, const float *b)
{
  c[0] = - a[0] - b[0];
  c[1] = - a[1] - b[1];
  return c;
}

/* c = - a - b */
INLINE double *dv2_nadd(double * RESTRICT c, const double *a, const double *b)
{
  c[0] = - a[0] - b[0];
  c[1] = - a[1] - b[1];
  return c;
}

/* c = - a - b */
INLINE real *rv2_nadd(real * RESTRICT c, const real *a, const real *b)
{
  c[0] = - a[0] - b[0];
  c[1] = - a[1] - b[1];
  return c;
}


/* c = a + b * s */
INLINE float *fv2_sadd(float * RESTRICT c, const float *a, const float *b, float s)
{
  c[0] = a[0] + b[0] * s;
  c[1] = a[1] + b[1] * s;
  return c;
}

/* c = a + b * s */
INLINE double *dv2_sadd(double * RESTRICT c, const double *a, const double *b, double s)
{
  c[0] = a[0] + b[0] * s;
  c[1] = a[1] + b[1] * s;
  return c;
}

/* c = a + b * s */
INLINE real *rv2_sadd(real * RESTRICT c, const real *a, const real *b, real s)
{
  c[0] = a[0] + b[0] * s;
  c[1] = a[1] + b[1] * s;
  return c;
}


/* c = a * s1 + b * s2 */
INLINE float *fv2_lincomb2(float * RESTRICT c, const float *a, const float *b, float s1, float s2)
{
  c[0] = a[0] * s1 + b[0] * s2;
  c[1] = a[1] * s1 + b[1] * s2;
  return c;
}

/* c = a * s1 + b * s2 */
INLINE double *dv2_lincomb2(double * RESTRICT c, const double *a, const double *b, double s1, double s2)
{
  c[0] = a[0] * s1 + b[0] * s2;
  c[1] = a[1] * s1 + b[1] * s2;
  return c;
}

/* c = a * s1 + b * s2 */
INLINE real *rv2_lincomb2(real * RESTRICT c, const real *a, const real *b, real s1, real s2)
{
  c[0] = a[0] * s1 + b[0] * s2;
  c[1] = a[1] * s1 + b[1] * s2;
  return c;
}


/* a = a * s + c */
INLINE float *fv2_fma(float *a, float s, float c)
{
  a[0] = a[0] * s + c;
  a[1] = a[1] * s + c;
  return a;
}

/* a = a * s + c */
INLINE double *dv2_fma(double *a, double s, double c)
{
  a[0] = a[0] * s + c;
  a[1] = a[1] * s + c;
  return a;
}

/* a = a * s + c */
INLINE real *rv2_fma(real *a, real s, real c)
{
  a[0] = a[0] * s + c;
  a[1] = a[1] * s + c;
  return a;
}


/* cosine of the angle of x1-x2-x3 */
INLINE float fv2_cosang(const float *x1, const float *x2, const float *x3,
    float *g1, float *g2, float *g3)
{
  float a[2], b[2], ra, rb, dot;

  ra = fv2_norm(fv2_diff(a, x1, x2));
  fv2_smul(a, 1.f/ra);
  rb = fv2_norm(fv2_diff(b, x3, x2));
  fv2_smul(b, 1.f/rb);
  dot = fv2_dot(a, b);
  if (dot > 1) dot = 1; else if (dot < -1) dot = -1;
  if (g1) {
    fv2_lincomb2(g1, b, a, 1.f/ra, -dot/ra);
    fv2_lincomb2(g3, a, b, 1.f/rb, -dot/rb);
    fv2_nadd(g2, g1, g3);
  }
  return dot;
}

/* cosine of the angle of x1-x2-x3 */
INLINE double dv2_cosang(const double *x1, const double *x2, const double *x3,
    double *g1, double *g2, double *g3)
{
  double a[2], b[2], ra, rb, dot;

  ra = dv2_norm(dv2_diff(a, x1, x2));
  dv2_smul(a, 1.f/ra);
  rb = dv2_norm(dv2_diff(b, x3, x2));
  dv2_smul(b, 1.f/rb);
  dot = dv2_dot(a, b);
  if (dot > 1) dot = 1; else if (dot < -1) dot = -1;
  if (g1) {
    dv2_lincomb2(g1, b, a, 1.f/ra, -dot/ra);
    dv2_lincomb2(g3, a, b, 1.f/rb, -dot/rb);
    dv2_nadd(g2, g1, g3);
  }
  return dot;
}

/* cosine of the angle of x1-x2-x3 */
INLINE real rv2_cosang(const real *x1, const real *x2, const real *x3,
    real *g1, real *g2, real *g3)
{
  real a[2], b[2], ra, rb, dot;

  ra = rv2_norm(rv2_diff(a, x1, x2));
  rv2_smul(a, 1.f/ra);
  rb = rv2_norm(rv2_diff(b, x3, x2));
  rv2_smul(b, 1.f/rb);
  dot = rv2_dot(a, b);
  if (dot > 1) dot = 1; else if (dot < -1) dot = -1;
  if (g1) {
    rv2_lincomb2(g1, b, a, 1.f/ra, -dot/ra);
    rv2_lincomb2(g3, a, b, 1.f/rb, -dot/rb);
    rv2_nadd(g2, g1, g3);
  }
  return dot;
}


/* angle and gradients of x1-x2-x3 */
INLINE float fv2_ang(const float *x1, const float *x2, const float *x3,
    float * RESTRICT g1, float * RESTRICT g2, float * RESTRICT g3)
{
  float dot, sn;
  dot = fv2_cosang(x1, x2, x3, g1, g2, g3);
  sn = (float) sqrt(1 - dot*dot);
  if (sn > 1e-7) sn = -1/sn; else sn = 0.;
  if (g1) {
    fv2_smul(g1, sn);
    fv2_smul(g2, sn);
    fv2_smul(g3, sn);
  }
  return (float) acos(dot);
}

/* angle and gradients of x1-x2-x3 */
INLINE double dv2_ang(const double *x1, const double *x2, const double *x3,
    double * RESTRICT g1, double * RESTRICT g2, double * RESTRICT g3)
{
  double dot, sn;
  dot = dv2_cosang(x1, x2, x3, g1, g2, g3);
  sn = (double) sqrt(1 - dot*dot);
  if (sn > 1e-7) sn = -1/sn; else sn = 0.;
  if (g1) {
    dv2_smul(g1, sn);
    dv2_smul(g2, sn);
    dv2_smul(g3, sn);
  }
  return (double) acos(dot);
}

/* angle and gradients of x1-x2-x3 */
INLINE real rv2_ang(const real *x1, const real *x2, const real *x3,
    real * RESTRICT g1, real * RESTRICT g2, real * RESTRICT g3)
{
  real dot, sn;
  dot = rv2_cosang(x1, x2, x3, g1, g2, g3);
  sn = (real) sqrt(1 - dot*dot);
  if (sn > 1e-7) sn = -1/sn; else sn = 0.;
  if (g1) {
    rv2_smul(g1, sn);
    rv2_smul(g2, sn);
    rv2_smul(g3, sn);
  }
  return (real) acos(dot);
}


/* vertical distance from x to line a-b */
INLINE real rv2_vdist(const real *x, const real *a, const real *b)
{
  real nm[2], d[2], dot;

  rv2_diff(d, x, a);
  rv2_normalize(rv2_diff(nm, a, b));
  dot = rv2_dot(d, nm);
  return rv2_norm(rv2_sinc(d, nm, -dot));
}


/* determinant of a 2x2 matrix */
INLINE real rm2_det(real a[2][2])
{
  return a[0][0]*a[1][1] - a[0][1]*a[1][0];
}


/* inverse matrix b = a^(-1) */
INLINE void rm2_inv(real b[2][2], real a[2][2])
{
  real det = rm2_det(a);
  if (fabs(det) < 1e-30) det = (det < 0) ? -1e-30f: 1e-30f;
  b[0][0] =  a[1][1]/det;
  b[0][1] = -a[0][1]/det;
  b[1][0] = -a[1][0]/det;
  b[1][1] =  a[0][0]/det;
}


#define fv2_rnd0(v)           fv2_rand01(v)

#define dv2_rnd0(v)           dv2_rand01(v)

#define rv2_rnd0(v)           rv2_rand01(v)

#define fv2_rnd(v, a, b)      fv2_randunif(v, a, b)

#define dv2_rnd(v, a, b)      dv2_randunif(v, a, b)

#define rv2_rnd(v, a, b)      rv2_randunif(v, a, b)

/* uniformly distributed random vector in [a, b) */
#define fv2_randunif(v, a, b) fv2_fma(fv2_rand01(v), b - a, -a)

/* uniformly distributed random vector in [a, b) */
#define dv2_randunif(v, a, b) dv2_fma(dv2_rand01(v), b - a, -a)

/* uniformly distributed random vector in [a, b) */
#define rv2_randunif(v, a, b) rv2_fma(rv2_rand01(v), b - a, -a)

/* uniformly distributed random vector in [0, 1) */
INLINE float *fv2_rand01(float *v)
{
  v[0] = (float) rand01();
  v[1] = (float) rand01();
  return v;
}

/* uniformly distributed random vector in [0, 1) */
INLINE double *dv2_rand01(double *v)
{
  v[0] = (double) rand01();
  v[1] = (double) rand01();
  return v;
}

/* uniformly distributed random vector in [0, 1) */
INLINE real *rv2_rand01(real *v)
{
  v[0] = (real) rand01();
  v[1] = (real) rand01();
  return v;
}


/* displace `x0' by a random vector in [-a, a)^2 */
INLINE real *rv2_randdisp(real * RESTRICT x, const real *x0, real a)
{
  x[0] = x0[0] + (real) randunif(-a, a);
  x[1] = x0[1] + (real) randunif(-a, a);
  return x;
}


#define fv2_grand0(v)       fv2_randgaus(v)

#define dv2_grand0(v)       dv2_randgaus(v)

#define rv2_grand0(v)       rv2_randgaus(v)

#define fv2_grand(v, c, r)  fv2_fma(fv2_randgaus(v), r, c)

#define dv2_grand(v, c, r)  dv2_fma(dv2_randgaus(v), r, c)

#define rv2_grand(v, c, r)  rv2_fma(rv2_randgaus(v), r, c)

/* normally distributed random vector */
INLINE float *fv2_randgaus(float *v)
{
  v[0] = (float) randgaus();
  v[1] = (float) randgaus();
  return v;
}

/* normally distributed random vector */
INLINE double *dv2_randgaus(double *v)
{
  v[0] = (double) randgaus();
  v[1] = (double) randgaus();
  return v;
}

/* normally distributed random vector */
INLINE real *rv2_randgaus(real *v)
{
  v[0] = (real) randgaus();
  v[1] = (real) randgaus();
  return v;
}


/* displace `x0' by a normally-distributed random vector */
INLINE float *fv2_randgausdisp(float * RESTRICT x, const float *x0, float a)
{
  x[0] = x0[0] + (float) randgaus() * a;
  x[1] = x0[1] + (float) randgaus() * a;
  return x;
}

/* displace `x0' by a normally-distributed random vector */
INLINE double *dv2_randgausdisp(double * RESTRICT x, const double *x0, double a)
{
  x[0] = x0[0] + (double) randgaus() * a;
  x[1] = x0[1] + (double) randgaus() * a;
  return x;
}

/* displace `x0' by a normally-distributed random vector */
INLINE real *rv2_randgausdisp(real * RESTRICT x, const real *x0, real a)
{
  x[0] = x0[0] + (real) randgaus() * a;
  x[1] = x0[1] + (real) randgaus() * a;
  return x;
}


/* randomly oriented vector on the sphere of radius r */
#define fv2_randdir(v, r) fv2_smul(fv2_randdir0(v), r)

/* randomly oriented vector on the sphere of radius r */
#define dv2_randdir(v, r) dv2_smul(dv2_randdir0(v), r)

/* randomly oriented vector on the sphere of radius r */
#define rv2_randdir(v, r) rv2_smul(rv2_randdir0(v), r)

/* randomly oriented vector on the unit sphere */
INLINE float *fv2_randdir0(float *v)
{
  do {
    fv2_randunif(v, -1, 1);
  } while (fv2_sqr(v) >= 1);
  return fv2_normalize(v);
}

/* randomly oriented vector on the unit sphere */
INLINE double *dv2_randdir0(double *v)
{
  do {
    dv2_randunif(v, -1, 1);
  } while (dv2_sqr(v) >= 1);
  return dv2_normalize(v);
}

/* randomly oriented vector on the unit sphere */
INLINE real *rv2_randdir0(real *v)
{
  do {
    rv2_randunif(v, -1, 1);
  } while (rv2_sqr(v) >= 1);
  return rv2_normalize(v);
}


#define rv2_randball rv2_randdisk

#define rv2_randball0 rv2_randdisk0

/* randomly orientied vector within the sphere of radius `r' */
#define fv2_randdisk(v, r) fv2_smul(fv2_randdisk0(v), r)

/* randomly orientied vector within the sphere of radius `r' */
#define dv2_randdisk(v, r) dv2_smul(dv2_randdisk0(v), r)

/* randomly orientied vector within the sphere of radius `r' */
#define rv2_randdisk(v, r) rv2_smul(rv2_randdisk0(v), r)

/* randomly vector within the unit sphere */
INLINE float *fv2_randdisk0(float *v)
{
  do {
    fv2_randunif(v, -1, 1);
  } while (fv2_sqr(v) >= 1);
  return v;
}

/* randomly vector within the unit sphere */
INLINE double *dv2_randdisk0(double *v)
{
  do {
    dv2_randunif(v, -1, 1);
  } while (dv2_sqr(v) >= 1);
  return v;
}

/* randomly vector within the unit sphere */
INLINE real *rv2_randdisk0(real *v)
{
  do {
    rv2_randunif(v, -1, 1);
  } while (rv2_sqr(v) >= 1);
  return v;
}




#ifndef FM2_T
#define FM2_T fm2_t
typedef float fm2_t[2];
#endif

#ifndef DM2_T
#define DM2_T dm2_t
typedef double dm2_t[2];
#endif

#ifndef RM2_T
#define RM2_T rm2_t
typedef real rm2_t[2];
#endif


#define fm2_print(r, nm, fmt, nl) fm2_fprint(stdout, r, nm, fmt, nl)

#define dm2_print(r, nm, fmt, nl) dm2_fprint(stdout, r, nm, fmt, nl)

#define rm2_print(r, nm, fmt, nl) rm2_fprint(stdout, r, nm, fmt, nl)

INLINE void fm2_fprint(FILE *fp, float r[2][2], const char *nm,
    const char *fmt, int nl)
{
  int i, j;
  if (nm) fprintf(fp, "%s:%c", nm, (nl ? '\n' : ' '));
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 2; j++) {
      fprintf(fp, fmt, r[i][j], nl);
    }
    fprintf(fp, "%s", (nl ? "\n" : "; "));
  }
}

INLINE void dm2_fprint(FILE *fp, double r[2][2], const char *nm,
    const char *fmt, int nl)
{
  int i, j;
  if (nm) fprintf(fp, "%s:%c", nm, (nl ? '\n' : ' '));
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 2; j++) {
      fprintf(fp, fmt, r[i][j], nl);
    }
    fprintf(fp, "%s", (nl ? "\n" : "; "));
  }
}

INLINE void rm2_fprint(FILE *fp, real r[2][2], const char *nm,
    const char *fmt, int nl)
{
  int i, j;
  if (nm) fprintf(fp, "%s:%c", nm, (nl ? '\n' : ' '));
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 2; j++) {
      fprintf(fp, fmt, r[i][j], nl);
    }
    fprintf(fp, "%s", (nl ? "\n" : "; "));
  }
}


INLINE fv2_t *fm2_make(float x[2][2], float a00, float a01, float a10, float a11)
{
  fv2_make(x[0], a00, a01);
  fv2_make(x[1], a10, a11);
  return x;
}

INLINE dv2_t *dm2_make(double x[2][2], double a00, double a01, double a10, double a11)
{
  dv2_make(x[0], a00, a01);
  dv2_make(x[1], a10, a11);
  return x;
}

INLINE rv2_t *rm2_make(real x[2][2], real a00, real a01, real a10, real a11)
{
  rv2_make(x[0], a00, a01);
  rv2_make(x[1], a10, a11);
  return x;
}


#define fm2_makem(rx, x) fm2_make(rx, (float) x[0][0], (float) x[0][1], \
    (float) x[1][0], (float) x[1][1])

#define dm2_makem(rx, x) dm2_make(rx, (double) x[0][0], (double) x[0][1], \
    (double) x[1][0], (double) x[1][1])

#define rm2_makem(rx, x) rm2_make(rx, (real) x[0][0], (real) x[0][1], \
    (real) x[1][0], (real) x[1][1])


#define fm2_zero(x) fm2_make(x, 0, 0, 0, 0)

#define dm2_zero(x) dm2_make(x, 0, 0, 0, 0)

#define rm2_zero(x) rm2_make(x, 0, 0, 0, 0)


#define fm2_one(x) fm2_make(x, 1, 0, 0, 1)

#define dm2_one(x) dm2_make(x, 1, 0, 0, 1)

#define rm2_one(x) rm2_make(x, 1, 0, 0, 1)


/* generate a random orthonormal (unitary) 2x2 matrix */
INLINE fv2_t *fm2_randuni(float a[2][2])
{
  fv2_randdir0(a[0]);
  fv2_make(a[1], a[0][1], -a[0][0]);
  if (rand01() > 0.5) fv2_neg(a[1]);
  return a;
}

/* generate a random orthonormal (unitary) 2x2 matrix */
INLINE dv2_t *dm2_randuni(double a[2][2])
{
  dv2_randdir0(a[0]);
  dv2_make(a[1], a[0][1], -a[0][0]);
  if (rand01() > 0.5) dv2_neg(a[1]);
  return a;
}

/* generate a random orthonormal (unitary) 2x2 matrix */
INLINE rv2_t *rm2_randuni(real a[2][2])
{
  rv2_randdir0(a[0]);
  rv2_make(a[1], a[0][1], -a[0][0]);
  if (rand01() > 0.5) rv2_neg(a[1]);
  return a;
}


#endif /* ZCOM_RV2__ */
#endif /* ZCOM_RV2 */





#ifdef  ZCOM_RV3
#ifndef ZCOM_RV3__
#define ZCOM_RV3__

#ifndef FV3_T
#define FV3_T fv3_t
typedef float fv3_t[3];
#endif

#ifndef DV3_T
#define DV3_T dv3_t
typedef double dv3_t[3];
#endif

#ifndef RV3_T
#define RV3_T rv3_t
typedef real rv3_t[3];
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>


#define fv3_print(r, nm, fmt, nl) fv3_fprint(stdout, r, nm, fmt, nl)

#define dv3_print(r, nm, fmt, nl) dv3_fprint(stdout, r, nm, fmt, nl)

#define rv3_print(r, nm, fmt, nl) rv3_fprint(stdout, r, nm, fmt, nl)

INLINE void fv3_fprint(FILE *fp, float *r, const char *nm, const char *fmt, int nl)
{
  int i;

  if (nm) fprintf(fp, "%s: ", nm);
  for (i = 0; i < 3; i++) fprintf(fp, fmt, r[i]);
  fprintf(fp, "%c", nl ? '\n' : ';');
}

INLINE void dv3_fprint(FILE *fp, double *r, const char *nm, const char *fmt, int nl)
{
  int i;

  if (nm) fprintf(fp, "%s: ", nm);
  for (i = 0; i < 3; i++) fprintf(fp, fmt, r[i]);
  fprintf(fp, "%c", nl ? '\n' : ';');
}

INLINE void rv3_fprint(FILE *fp, real *r, const char *nm, const char *fmt, int nl)
{
  int i;

  if (nm) fprintf(fp, "%s: ", nm);
  for (i = 0; i < 3; i++) fprintf(fp, fmt, r[i]);
  fprintf(fp, "%c", nl ? '\n' : ';');
}


/* due to possible pointer overlap, 'const' are not add to some parameters */

INLINE float *fv3_make(float *x, float a, float b, float c)
{
  x[0] = a;
  x[1] = b;
  x[2] = c;
  return x;
}

INLINE double *dv3_make(double *x, double a, double b, double c)
{
  x[0] = a;
  x[1] = b;
  x[2] = c;
  return x;
}

INLINE real *rv3_make(real *x, real a, real b, real c)
{
  x[0] = a;
  x[1] = b;
  x[2] = c;
  return x;
}


#define fv3_makev(rv, v) fv3_make(rv, (float) v[0], (float) v[1], (float) v[2])

#define dv3_makev(rv, v) dv3_make(rv, (double) v[0], (double) v[1], (double) v[2])

#define rv3_makev(rv, v) rv3_make(rv, (real) v[0], (real) v[1], (real) v[2])


#define fv3_zero(x) fv3_make(x, 0, 0, 0)

#define dv3_zero(x) dv3_make(x, 0, 0, 0)

#define rv3_zero(x) rv3_make(x, 0, 0, 0)


INLINE float *fv3_copy(float * RESTRICT x, const float *src)
{
  x[0] = src[0];
  x[1] = src[1];
  x[2] = src[2];
  return x;
}

INLINE double *dv3_copy(double * RESTRICT x, const double *src)
{
  x[0] = src[0];
  x[1] = src[1];
  x[2] = src[2];
  return x;
}

INLINE real *rv3_copy(real * RESTRICT x, const real *src)
{
  x[0] = src[0];
  x[1] = src[1];
  x[2] = src[2];
  return x;
}


/* use macro to avoid const qualifier of src */
#define fv3_ncopy(x, src, n) memcpy(x, src, 3*n*sizeof(float))

/* use macro to avoid const qualifier of src */
#define dv3_ncopy(x, src, n) memcpy(x, src, 3*n*sizeof(double))

/* use macro to avoid const qualifier of src */
#define rv3_ncopy(x, src, n) memcpy(x, src, 3*n*sizeof(real))


INLINE void fv3_swap(float * RESTRICT x, float * RESTRICT y)
{
  float z[3];
  fv3_copy(z, x);
  fv3_copy(x, y);
  fv3_copy(y, z);
}

INLINE void dv3_swap(double * RESTRICT x, double * RESTRICT y)
{
  double z[3];
  dv3_copy(z, x);
  dv3_copy(x, y);
  dv3_copy(y, z);
}

INLINE void rv3_swap(real * RESTRICT x, real * RESTRICT y)
{
  real z[3];
  rv3_copy(z, x);
  rv3_copy(x, y);
  rv3_copy(y, z);
}


INLINE float fv3_sqr(const float *x)
{
  return x[0]*x[0] + x[1]*x[1] + x[2]*x[2];
}

INLINE double dv3_sqr(const double *x)
{
  return x[0]*x[0] + x[1]*x[1] + x[2]*x[2];
}

INLINE real rv3_sqr(const real *x)
{
  return x[0]*x[0] + x[1]*x[1] + x[2]*x[2];
}


INLINE float fv3_norm(const float *x)
{
  return (float) sqrt( fv3_sqr(x) );
}

INLINE double dv3_norm(const double *x)
{
  return (double) sqrt( dv3_sqr(x) );
}

INLINE real rv3_norm(const real *x)
{
  return (real) sqrt( rv3_sqr(x) );
}


/* if x == y, try to use sqr */
INLINE float fv3_dot(const float *x, const float *y)
{
  return x[0]*y[0] + x[1]*y[1] + x[2]*y[2];
}

/* if x == y, try to use sqr */
INLINE double dv3_dot(const double *x, const double *y)
{
  return x[0]*y[0] + x[1]*y[1] + x[2]*y[2];
}

/* if x == y, try to use sqr */
INLINE real rv3_dot(const real *x, const real *y)
{
  return x[0]*y[0] + x[1]*y[1] + x[2]*y[2];
}


INLINE float *fv3_cross(float * RESTRICT z, const float *x, const float *y)
{
  z[0] = x[1]*y[2] - x[2]*y[1];
  z[1] = x[2]*y[0] - x[0]*y[2];
  z[2] = x[0]*y[1] - x[1]*y[0];
  return z;
}

INLINE double *dv3_cross(double * RESTRICT z, const double *x, const double *y)
{
  z[0] = x[1]*y[2] - x[2]*y[1];
  z[1] = x[2]*y[0] - x[0]*y[2];
  z[2] = x[0]*y[1] - x[1]*y[0];
  return z;
}

INLINE real *rv3_cross(real * RESTRICT z, const real *x, const real *y)
{
  z[0] = x[1]*y[2] - x[2]*y[1];
  z[1] = x[2]*y[0] - x[0]*y[2];
  z[2] = x[0]*y[1] - x[1]*y[0];
  return z;
}


INLINE float *fv3_neg(float *x)
{
  x[0] = -x[0];
  x[1] = -x[1];
  x[2] = -x[2];
  return x;
}

INLINE double *dv3_neg(double *x)
{
  x[0] = -x[0];
  x[1] = -x[1];
  x[2] = -x[2];
  return x;
}

INLINE real *rv3_neg(real *x)
{
  x[0] = -x[0];
  x[1] = -x[1];
  x[2] = -x[2];
  return x;
}


INLINE float *fv3_neg2(float * RESTRICT nx, const float *x)
{
  nx[0] = -x[0];
  nx[1] = -x[1];
  nx[2] = -x[2];
  return nx;
}

INLINE double *dv3_neg2(double * RESTRICT nx, const double *x)
{
  nx[0] = -x[0];
  nx[1] = -x[1];
  nx[2] = -x[2];
  return nx;
}

INLINE real *rv3_neg2(real * RESTRICT nx, const real *x)
{
  nx[0] = -x[0];
  nx[1] = -x[1];
  nx[2] = -x[2];
  return nx;
}


INLINE float *fv3_inc(float * RESTRICT x, const float *dx)
{
  x[0] += dx[0];
  x[1] += dx[1];
  x[2] += dx[2];
  return x;
}

INLINE double *dv3_inc(double * RESTRICT x, const double *dx)
{
  x[0] += dx[0];
  x[1] += dx[1];
  x[2] += dx[2];
  return x;
}

INLINE real *rv3_inc(real * RESTRICT x, const real *dx)
{
  x[0] += dx[0];
  x[1] += dx[1];
  x[2] += dx[2];
  return x;
}


INLINE float *fv3_dec(float *x, const float *dx)
{
  x[0] -= dx[0];
  x[1] -= dx[1];
  x[2] -= dx[2];
  return x;
}

INLINE double *dv3_dec(double *x, const double *dx)
{
  x[0] -= dx[0];
  x[1] -= dx[1];
  x[2] -= dx[2];
  return x;
}

INLINE real *rv3_dec(real *x, const real *dx)
{
  x[0] -= dx[0];
  x[1] -= dx[1];
  x[2] -= dx[2];
  return x;
}


INLINE float *fv3_sinc(float * RESTRICT x, const float *dx, float s)
{
  x[0] += dx[0] * s;
  x[1] += dx[1] * s;
  x[2] += dx[2] * s;
  return x;
}

INLINE double *dv3_sinc(double * RESTRICT x, const double *dx, double s)
{
  x[0] += dx[0] * s;
  x[1] += dx[1] * s;
  x[2] += dx[2] * s;
  return x;
}

INLINE real *rv3_sinc(real * RESTRICT x, const real *dx, real s)
{
  x[0] += dx[0] * s;
  x[1] += dx[1] * s;
  x[2] += dx[2] * s;
  return x;
}


INLINE float *fv3_smul(float *x, float s)
{
  x[0] *= s;
  x[1] *= s;
  x[2] *= s;
  return x;
}

INLINE double *dv3_smul(double *x, double s)
{
  x[0] *= s;
  x[1] *= s;
  x[2] *= s;
  return x;
}

INLINE real *rv3_smul(real *x, real s)
{
  x[0] *= s;
  x[1] *= s;
  x[2] *= s;
  return x;
}


/* if y == x, just use smul */
INLINE float *fv3_smul2(float * RESTRICT y, const float *x, float s)
{
  y[0] = x[0] * s;
  y[1] = x[1] * s;
  y[2] = x[2] * s;
  return y;
}

/* if y == x, just use smul */
INLINE double *dv3_smul2(double * RESTRICT y, const double *x, double s)
{
  y[0] = x[0] * s;
  y[1] = x[1] * s;
  y[2] = x[2] * s;
  return y;
}

/* if y == x, just use smul */
INLINE real *rv3_smul2(real * RESTRICT y, const real *x, real s)
{
  y[0] = x[0] * s;
  y[1] = x[1] * s;
  y[2] = x[2] * s;
  return y;
}


INLINE float *fv3_normalize(float *x)
{
  float r = fv3_norm(x);
  if (r > 0.f) fv3_smul(x, 1.f/r);
  return x;
}

INLINE double *dv3_normalize(double *x)
{
  double r = dv3_norm(x);
  if (r > 0.f) dv3_smul(x, 1.f/r);
  return x;
}

INLINE real *rv3_normalize(real *x)
{
  real r = rv3_norm(x);
  if (r > 0.f) rv3_smul(x, 1.f/r);
  return x;
}


INLINE float *fv3_makenorm(float *v, float x, float y, float z)
{
  return fv3_normalize( fv3_make(v, x, y, z) );
}

INLINE double *dv3_makenorm(double *v, double x, double y, double z)
{
  return dv3_normalize( dv3_make(v, x, y, z) );
}

INLINE real *rv3_makenorm(real *v, real x, real y, real z)
{
  return rv3_normalize( rv3_make(v, x, y, z) );
}


/* for in-place difference use fv3_dec */
INLINE float *fv3_diff(float * RESTRICT c, const float *a, const float *b)
{
  c[0] = a[0] - b[0];
  c[1] = a[1] - b[1];
  c[2] = a[2] - b[2];
  return c;
}

/* for in-place difference use dv3_dec */
INLINE double *dv3_diff(double * RESTRICT c, const double *a, const double *b)
{
  c[0] = a[0] - b[0];
  c[1] = a[1] - b[1];
  c[2] = a[2] - b[2];
  return c;
}

/* for in-place difference use rv3_dec */
INLINE real *rv3_diff(real * RESTRICT c, const real *a, const real *b)
{
  c[0] = a[0] - b[0];
  c[1] = a[1] - b[1];
  c[2] = a[2] - b[2];
  return c;
}


/* distance^2 between a and b */
INLINE float fv3_dist2(const float *a, const float *b)
{
  float d0 = a[0] - b[0], d1 = a[1] - b[1], d2 = a[2] - b[2];
  return d0*d0 + d1*d1 + d2*d2;
}

/* distance^2 between a and b */
INLINE double dv3_dist2(const double *a, const double *b)
{
  double d0 = a[0] - b[0], d1 = a[1] - b[1], d2 = a[2] - b[2];
  return d0*d0 + d1*d1 + d2*d2;
}

/* distance^2 between a and b */
INLINE real rv3_dist2(const real *a, const real *b)
{
  real d0 = a[0] - b[0], d1 = a[1] - b[1], d2 = a[2] - b[2];
  return d0*d0 + d1*d1 + d2*d2;
}


/* distance between a and b */
INLINE float fv3_dist(const float *a, const float *b)
{
  float d0 = a[0] - b[0], d1 = a[1] - b[1], d2 = a[2] - b[2];
  return (float) sqrt(d0*d0 + d1*d1 + d2*d2);
}

/* distance between a and b */
INLINE double dv3_dist(const double *a, const double *b)
{
  double d0 = a[0] - b[0], d1 = a[1] - b[1], d2 = a[2] - b[2];
  return (double) sqrt(d0*d0 + d1*d1 + d2*d2);
}

/* distance between a and b */
INLINE real rv3_dist(const real *a, const real *b)
{
  real d0 = a[0] - b[0], d1 = a[1] - b[1], d2 = a[2] - b[2];
  return (real) sqrt(d0*d0 + d1*d1 + d2*d2);
}


/* c = a + b, for in-place addition use fv3_inc */
INLINE float *fv3_add(float * RESTRICT c, const float *a, const float *b)
{
  c[0] = a[0] + b[0];
  c[1] = a[1] + b[1];
  c[2] = a[2] + b[2];
  return c;
}

/* c = a + b, for in-place addition use dv3_inc */
INLINE double *dv3_add(double * RESTRICT c, const double *a, const double *b)
{
  c[0] = a[0] + b[0];
  c[1] = a[1] + b[1];
  c[2] = a[2] + b[2];
  return c;
}

/* c = a + b, for in-place addition use rv3_inc */
INLINE real *rv3_add(real * RESTRICT c, const real *a, const real *b)
{
  c[0] = a[0] + b[0];
  c[1] = a[1] + b[1];
  c[2] = a[2] + b[2];
  return c;
}


/* c = - a - b */
INLINE float *fv3_nadd(float * RESTRICT c, const float *a, const float *b)
{
  c[0] = - a[0] - b[0];
  c[1] = - a[1] - b[1];
  c[2] = - a[2] - b[2];
  return c;
}

/* c = - a - b */
INLINE double *dv3_nadd(double * RESTRICT c, const double *a, const double *b)
{
  c[0] = - a[0] - b[0];
  c[1] = - a[1] - b[1];
  c[2] = - a[2] - b[2];
  return c;
}

/* c = - a - b */
INLINE real *rv3_nadd(real * RESTRICT c, const real *a, const real *b)
{
  c[0] = - a[0] - b[0];
  c[1] = - a[1] - b[1];
  c[2] = - a[2] - b[2];
  return c;
}


/* c = a + b * s */
INLINE float *fv3_sadd(float * RESTRICT c, const float *a, const float *b, float s)
{
  c[0] = a[0] + b[0] * s;
  c[1] = a[1] + b[1] * s;
  c[2] = a[2] + b[2] * s;
  return c;
}

/* c = a + b * s */
INLINE double *dv3_sadd(double * RESTRICT c, const double *a, const double *b, double s)
{
  c[0] = a[0] + b[0] * s;
  c[1] = a[1] + b[1] * s;
  c[2] = a[2] + b[2] * s;
  return c;
}

/* c = a + b * s */
INLINE real *rv3_sadd(real * RESTRICT c, const real *a, const real *b, real s)
{
  c[0] = a[0] + b[0] * s;
  c[1] = a[1] + b[1] * s;
  c[2] = a[2] + b[2] * s;
  return c;
}


/* c = a * s1 + b * s2 */
INLINE float *fv3_lincomb2(float * RESTRICT c, const float *a, const float *b,
    float s1, float s2)
{
  c[0] = a[0] * s1 + b[0] * s2;
  c[1] = a[1] * s1 + b[1] * s2;
  c[2] = a[2] * s1 + b[2] * s2;
  return c;
}

/* c = a * s1 + b * s2 */
INLINE double *dv3_lincomb2(double * RESTRICT c, const double *a, const double *b,
    double s1, double s2)
{
  c[0] = a[0] * s1 + b[0] * s2;
  c[1] = a[1] * s1 + b[1] * s2;
  c[2] = a[2] * s1 + b[2] * s2;
  return c;
}

/* c = a * s1 + b * s2 */
INLINE real *rv3_lincomb2(real * RESTRICT c, const real *a, const real *b,
    real s1, real s2)
{
  c[0] = a[0] * s1 + b[0] * s2;
  c[1] = a[1] * s1 + b[1] * s2;
  c[2] = a[2] * s1 + b[2] * s2;
  return c;
}


/* a = a * s + c */
INLINE float *fv3_fma(float *a, float s, float c)
{
  a[0] = a[0] * s + c;
  a[1] = a[1] * s + c;
  a[2] = a[2] * s + c;
  return a;
}

/* a = a * s + c */
INLINE double *dv3_fma(double *a, double s, double c)
{
  a[0] = a[0] * s + c;
  a[1] = a[1] * s + c;
  a[2] = a[2] * s + c;
  return a;
}

/* a = a * s + c */
INLINE real *rv3_fma(real *a, real s, real c)
{
  a[0] = a[0] * s + c;
  a[1] = a[1] * s + c;
  a[2] = a[2] * s + c;
  return a;
}


/* angle and gradients of cos(x1-x2-x3) */
INLINE float fv3_cosang(const float *x1, const float *x2, const float *x3,
    float * RESTRICT g1, float * RESTRICT g2, float * RESTRICT g3)
{
  float a[3], b[3], ra, rb, dot;

  ra = fv3_norm(fv3_diff(a, x1, x2));
  fv3_smul(a, 1.f/ra);
  rb = fv3_norm(fv3_diff(b, x3, x2));
  fv3_smul(b, 1.f/rb);
  dot = fv3_dot(a, b);
  if (dot > 1) dot = 1; else if (dot < -1) dot = -1;
  if (g1) {
    fv3_lincomb2(g1, b, a, 1.f/ra, -dot/ra);
    fv3_lincomb2(g3, a, b, 1.f/rb, -dot/rb);
    fv3_nadd(g2, g1, g3);
  }
  return dot;
}

/* angle and gradients of cos(x1-x2-x3) */
INLINE double dv3_cosang(const double *x1, const double *x2, const double *x3,
    double * RESTRICT g1, double * RESTRICT g2, double * RESTRICT g3)
{
  double a[3], b[3], ra, rb, dot;

  ra = dv3_norm(dv3_diff(a, x1, x2));
  dv3_smul(a, 1.f/ra);
  rb = dv3_norm(dv3_diff(b, x3, x2));
  dv3_smul(b, 1.f/rb);
  dot = dv3_dot(a, b);
  if (dot > 1) dot = 1; else if (dot < -1) dot = -1;
  if (g1) {
    dv3_lincomb2(g1, b, a, 1.f/ra, -dot/ra);
    dv3_lincomb2(g3, a, b, 1.f/rb, -dot/rb);
    dv3_nadd(g2, g1, g3);
  }
  return dot;
}

/* angle and gradients of cos(x1-x2-x3) */
INLINE real rv3_cosang(const real *x1, const real *x2, const real *x3,
    real * RESTRICT g1, real * RESTRICT g2, real * RESTRICT g3)
{
  real a[3], b[3], ra, rb, dot;

  ra = rv3_norm(rv3_diff(a, x1, x2));
  rv3_smul(a, 1.f/ra);
  rb = rv3_norm(rv3_diff(b, x3, x2));
  rv3_smul(b, 1.f/rb);
  dot = rv3_dot(a, b);
  if (dot > 1) dot = 1; else if (dot < -1) dot = -1;
  if (g1) {
    rv3_lincomb2(g1, b, a, 1.f/ra, -dot/ra);
    rv3_lincomb2(g3, a, b, 1.f/rb, -dot/rb);
    rv3_nadd(g2, g1, g3);
  }
  return dot;
}


/* angle and gradients of x1-x2-x3 */
INLINE float fv3_ang(const float *x1, const float *x2, const float *x3,
    float * RESTRICT g1, float * RESTRICT g2, float * RESTRICT g3)
{
  float dot, sn;

  dot = fv3_cosang(x1, x2, x3, g1, g2, g3);
  sn = (float) sqrt(1 - dot*dot);
  if (sn < 1e-7) sn = 1; else sn = -1.f/sn;
  if (g1) {
    fv3_smul(g1, sn);
    fv3_smul(g2, sn);
    fv3_smul(g3, sn);
  }
  return (float) acos(dot);
}

/* angle and gradients of x1-x2-x3 */
INLINE double dv3_ang(const double *x1, const double *x2, const double *x3,
    double * RESTRICT g1, double * RESTRICT g2, double * RESTRICT g3)
{
  double dot, sn;

  dot = dv3_cosang(x1, x2, x3, g1, g2, g3);
  sn = (double) sqrt(1 - dot*dot);
  if (sn < 1e-7) sn = 1; else sn = -1.f/sn;
  if (g1) {
    dv3_smul(g1, sn);
    dv3_smul(g2, sn);
    dv3_smul(g3, sn);
  }
  return (double) acos(dot);
}

/* angle and gradients of x1-x2-x3 */
INLINE real rv3_ang(const real *x1, const real *x2, const real *x3,
    real * RESTRICT g1, real * RESTRICT g2, real * RESTRICT g3)
{
  real dot, sn;

  dot = rv3_cosang(x1, x2, x3, g1, g2, g3);
  sn = (real) sqrt(1 - dot*dot);
  if (sn < 1e-7) sn = 1; else sn = -1.f/sn;
  if (g1) {
    rv3_smul(g1, sn);
    rv3_smul(g2, sn);
    rv3_smul(g3, sn);
  }
  return (real) acos(dot);
}


/* vertical distance from `x' to the line extended by `a' and `b' */
INLINE float fv3_vdist(const float *x, const float *a, const float *b)
{
  float nm[3], d[3], dot;

  fv3_diff(d, x, a);
  fv3_normalize(fv3_diff(nm, a, b));
  dot = fv3_dot(d, nm);
  return fv3_norm(fv3_sinc(d, nm, -dot));
}

/* vertical distance from `x' to the line extended by `a' and `b' */
INLINE double dv3_vdist(const double *x, const double *a, const double *b)
{
  double nm[3], d[3], dot;

  dv3_diff(d, x, a);
  dv3_normalize(dv3_diff(nm, a, b));
  dot = dv3_dot(d, nm);
  return dv3_norm(dv3_sinc(d, nm, -dot));
}

/* vertical distance from `x' to the line extended by `a' and `b' */
INLINE real rv3_vdist(const real *x, const real *a, const real *b)
{
  real nm[3], d[3], dot;

  rv3_diff(d, x, a);
  rv3_normalize(rv3_diff(nm, a, b));
  dot = rv3_dot(d, nm);
  return rv3_norm(rv3_sinc(d, nm, -dot));
}


/* signed distance from x to the plane extended by a, b, c */
INLINE float fv3_vpdist(const float *x, const float *a, const float *b, const float *c)
{
  float u[3], v[3], m[3];

  fv3_diff(u, b, a);
  fv3_diff(v, c, b);
  fv3_normalize(fv3_cross(m, u, v));
  fv3_diff(u, x, a);
  return fv3_dot(u, m);
}

/* signed distance from x to the plane extended by a, b, c */
INLINE double dv3_vpdist(const double *x, const double *a, const double *b, const double *c)
{
  double u[3], v[3], m[3];

  dv3_diff(u, b, a);
  dv3_diff(v, c, b);
  dv3_normalize(dv3_cross(m, u, v));
  dv3_diff(u, x, a);
  return dv3_dot(u, m);
}

/* signed distance from x to the plane extended by a, b, c */
INLINE real rv3_vpdist(const real *x, const real *a, const real *b, const real *c)
{
  real u[3], v[3], m[3];

  rv3_diff(u, b, a);
  rv3_diff(v, c, b);
  rv3_normalize(rv3_cross(m, u, v));
  rv3_diff(u, x, a);
  return rv3_dot(u, m);
}


/* light weight dihedral */
INLINE float fv3_dih(const float *xi, const float *xj, const float *xk, const float *xl,
    float * RESTRICT gi, float * RESTRICT gj, float * RESTRICT gk, float * RESTRICT gl)
{
  float tol, phi, cosphi = 1.f;
  float nxkj, nxkj2, m2, n2;
  float xij[3], xkj[3], xkl[3], uvec[3], vvec[3], svec[3];
  float m[3], n[3]; /* the planar vector of xij x xkj,  and xkj x xkj */

  fv3_diff(xij, xi, xj);
  fv3_diff(xkj, xk, xj);
  fv3_diff(xkl, xk, xl);
  nxkj2 = fv3_sqr(xkj);
  nxkj = (float) sqrt(nxkj2);
  tol = (sizeof(float) == sizeof(float)) ? nxkj2 * 6e-8f : nxkj2 * 1e-16f;

  fv3_cross(m, xij, xkj);
  m2 = fv3_sqr(m);
  fv3_cross(n, xkj, xkl);
  n2 = fv3_sqr(n);
  if (m2 > tol && n2 > tol) {
    cosphi = fv3_dot(m, n);
    cosphi /= (float) sqrt(m2 * n2);
    if (cosphi >= 1.f) cosphi = 1.f;
    else if (cosphi < -1.f) cosphi = -1.f;
  }
  phi = (float) acos(cosphi);
  if (fv3_dot(n, xij) < 0.0) phi = -phi;

  /* optionally calculate the gradient */
  if (gi != NULL) {
    if (m2 > tol && n2 > tol) {
      fv3_smul2(gi, m, nxkj/m2);
      fv3_smul2(gl, n, -nxkj/n2);
      fv3_smul2(uvec, gi, fv3_dot(xij, xkj)/nxkj2);
      fv3_smul2(vvec, gl, fv3_dot(xkl, xkj)/nxkj2);
      fv3_diff(svec, uvec, vvec);
      fv3_diff(gj, svec, gi);
      fv3_nadd(gk, svec, gl);
    } else { /* clear the gradients */
      fv3_zero(gi);
      fv3_zero(gj);
      fv3_zero(gk);
      fv3_zero(gl);
    }
  }
  return phi;
}

/* light weight dihedral */
INLINE double dv3_dih(const double *xi, const double *xj, const double *xk, const double *xl,
    double * RESTRICT gi, double * RESTRICT gj, double * RESTRICT gk, double * RESTRICT gl)
{
  double tol, phi, cosphi = 1.f;
  double nxkj, nxkj2, m2, n2;
  double xij[3], xkj[3], xkl[3], uvec[3], vvec[3], svec[3];
  double m[3], n[3]; /* the planar vector of xij x xkj,  and xkj x xkj */

  dv3_diff(xij, xi, xj);
  dv3_diff(xkj, xk, xj);
  dv3_diff(xkl, xk, xl);
  nxkj2 = dv3_sqr(xkj);
  nxkj = (double) sqrt(nxkj2);
  tol = (sizeof(double) == sizeof(float)) ? nxkj2 * 6e-8f : nxkj2 * 1e-16f;

  dv3_cross(m, xij, xkj);
  m2 = dv3_sqr(m);
  dv3_cross(n, xkj, xkl);
  n2 = dv3_sqr(n);
  if (m2 > tol && n2 > tol) {
    cosphi = dv3_dot(m, n);
    cosphi /= (double) sqrt(m2 * n2);
    if (cosphi >= 1.f) cosphi = 1.f;
    else if (cosphi < -1.f) cosphi = -1.f;
  }
  phi = (double) acos(cosphi);
  if (dv3_dot(n, xij) < 0.0) phi = -phi;

  /* optionally calculate the gradient */
  if (gi != NULL) {
    if (m2 > tol && n2 > tol) {
      dv3_smul2(gi, m, nxkj/m2);
      dv3_smul2(gl, n, -nxkj/n2);
      dv3_smul2(uvec, gi, dv3_dot(xij, xkj)/nxkj2);
      dv3_smul2(vvec, gl, dv3_dot(xkl, xkj)/nxkj2);
      dv3_diff(svec, uvec, vvec);
      dv3_diff(gj, svec, gi);
      dv3_nadd(gk, svec, gl);
    } else { /* clear the gradients */
      dv3_zero(gi);
      dv3_zero(gj);
      dv3_zero(gk);
      dv3_zero(gl);
    }
  }
  return phi;
}

/* light weight dihedral */
INLINE real rv3_dih(const real *xi, const real *xj, const real *xk, const real *xl,
    real * RESTRICT gi, real * RESTRICT gj, real * RESTRICT gk, real * RESTRICT gl)
{
  real tol, phi, cosphi = 1.f;
  real nxkj, nxkj2, m2, n2;
  real xij[3], xkj[3], xkl[3], uvec[3], vvec[3], svec[3];
  real m[3], n[3]; /* the planar vector of xij x xkj,  and xkj x xkj */

  rv3_diff(xij, xi, xj);
  rv3_diff(xkj, xk, xj);
  rv3_diff(xkl, xk, xl);
  nxkj2 = rv3_sqr(xkj);
  nxkj = (real) sqrt(nxkj2);
  tol = (sizeof(real) == sizeof(float)) ? nxkj2 * 6e-8f : nxkj2 * 1e-16f;

  rv3_cross(m, xij, xkj);
  m2 = rv3_sqr(m);
  rv3_cross(n, xkj, xkl);
  n2 = rv3_sqr(n);
  if (m2 > tol && n2 > tol) {
    cosphi = rv3_dot(m, n);
    cosphi /= (real) sqrt(m2 * n2);
    if (cosphi >= 1.f) cosphi = 1.f;
    else if (cosphi < -1.f) cosphi = -1.f;
  }
  phi = (real) acos(cosphi);
  if (rv3_dot(n, xij) < 0.0) phi = -phi;

  /* optionally calculate the gradient */
  if (gi != NULL) {
    if (m2 > tol && n2 > tol) {
      rv3_smul2(gi, m, nxkj/m2);
      rv3_smul2(gl, n, -nxkj/n2);
      rv3_smul2(uvec, gi, rv3_dot(xij, xkj)/nxkj2);
      rv3_smul2(vvec, gl, rv3_dot(xkl, xkj)/nxkj2);
      rv3_diff(svec, uvec, vvec);
      rv3_diff(gj, svec, gi);
      rv3_nadd(gk, svec, gl);
    } else { /* clear the gradients */
      rv3_zero(gi);
      rv3_zero(gj);
      rv3_zero(gk);
      rv3_zero(gl);
    }
  }
  return phi;
}


#define fv3_rnd0(v)           fv3_rand01(v)

#define dv3_rnd0(v)           dv3_rand01(v)

#define rv3_rnd0(v)           rv3_rand01(v)

#define fv3_rnd(v, a, b)      fv3_randunif(v, a, b)

#define dv3_rnd(v, a, b)      dv3_randunif(v, a, b)

#define rv3_rnd(v, a, b)      rv3_randunif(v, a, b)

/* uniformly distributed random vector in [a, b) */
#define fv3_randunif(v, a, b) fv3_fma(fv3_rand01(v), b - a, -a)

/* uniformly distributed random vector in [a, b) */
#define dv3_randunif(v, a, b) dv3_fma(dv3_rand01(v), b - a, -a)

/* uniformly distributed random vector in [a, b) */
#define rv3_randunif(v, a, b) rv3_fma(rv3_rand01(v), b - a, -a)

/* uniformly distributed random vector in [0, 1) */
INLINE float *fv3_rand01(float *v)
{
  v[0] = (float) rand01();
  v[1] = (float) rand01();
  v[2] = (float) rand01();
  return v;
}

/* uniformly distributed random vector in [0, 1) */
INLINE double *dv3_rand01(double *v)
{
  v[0] = (double) rand01();
  v[1] = (double) rand01();
  v[2] = (double) rand01();
  return v;
}

/* uniformly distributed random vector in [0, 1) */
INLINE real *rv3_rand01(real *v)
{
  v[0] = (real) rand01();
  v[1] = (real) rand01();
  v[2] = (real) rand01();
  return v;
}


/* displace `x0' by a random vector in [-a, a)^3 */
INLINE real *rv3_randdisp(real * RESTRICT x, const real *x0, real a)
{
  x[0] = x0[0] + (real) randunif(-a, a);
  x[1] = x0[1] + (real) randunif(-a, a);
  x[2] = x0[2] + (real) randunif(-a, a);
  return x;
}


#define fv3_grand0(v)       fv3_randgaus(v)

#define dv3_grand0(v)       dv3_randgaus(v)

#define rv3_grand0(v)       rv3_randgaus(v)

#define fv3_grand(v, c, r)  fv3_fma(fv3_randgaus(v), r, c)

#define dv3_grand(v, c, r)  dv3_fma(dv3_randgaus(v), r, c)

#define rv3_grand(v, c, r)  rv3_fma(rv3_randgaus(v), r, c)

/* normally distributed random vector */
INLINE float *fv3_randgaus(float *v)
{
  v[0] = (float) randgaus();
  v[1] = (float) randgaus();
  v[2] = (float) randgaus();
  return v;
}

/* normally distributed random vector */
INLINE double *dv3_randgaus(double *v)
{
  v[0] = (double) randgaus();
  v[1] = (double) randgaus();
  v[2] = (double) randgaus();
  return v;
}

/* normally distributed random vector */
INLINE real *rv3_randgaus(real *v)
{
  v[0] = (real) randgaus();
  v[1] = (real) randgaus();
  v[2] = (real) randgaus();
  return v;
}


#define rv3_granddisp(x, x0, a) rv3_randgausdisp(x, x0, a)

/* displace `x0' by a normally-distributed random vector */
INLINE float *fv3_randgausdisp(float * RESTRICT x, const float *x0, float a)
{
  x[0] = x0[0] + a * (float) randgaus();
  x[1] = x0[1] + a * (float) randgaus();
  x[2] = x0[2] + a * (float) randgaus();
  return x;
}

/* displace `x0' by a normally-distributed random vector */
INLINE double *dv3_randgausdisp(double * RESTRICT x, const double *x0, double a)
{
  x[0] = x0[0] + a * (double) randgaus();
  x[1] = x0[1] + a * (double) randgaus();
  x[2] = x0[2] + a * (double) randgaus();
  return x;
}

/* displace `x0' by a normally-distributed random vector */
INLINE real *rv3_randgausdisp(real * RESTRICT x, const real *x0, real a)
{
  x[0] = x0[0] + a * (real) randgaus();
  x[1] = x0[1] + a * (real) randgaus();
  x[2] = x0[2] + a * (real) randgaus();
  return x;
}


/* randomly oriented vector on the sphere of radius r */
#define fv3_randdir(v, r) fv3_smul(fv3_randdir0(v), r)

/* randomly oriented vector on the sphere of radius r */
#define dv3_randdir(v, r) dv3_smul(dv3_randdir0(v), r)

/* randomly oriented vector on the sphere of radius r */
#define rv3_randdir(v, r) rv3_smul(rv3_randdir0(v), r)

/* randomly oriented vector on the unit sphere */
INLINE float *fv3_randdir0(float *v)
{
  double a, b, sq, s;

  do { /* projection on the x-y plane */
    a = randunif(-1, 1);
    b = randunif(-1, 1);
    sq = a * a + b * b;
  } while (sq >= 1); /* avoid sin() and cos() */

  s = 2. * sqrt(1 - sq);
  return fv3_make(v, (float) (a * s), (float) (b * s), (float) (1 - 2 * sq));
}

/* randomly oriented vector on the unit sphere */
INLINE double *dv3_randdir0(double *v)
{
  double a, b, sq, s;

  do { /* projection on the x-y plane */
    a = randunif(-1, 1);
    b = randunif(-1, 1);
    sq = a * a + b * b;
  } while (sq >= 1); /* avoid sin() and cos() */

  s = 2. * sqrt(1 - sq);
  return dv3_make(v, (double) (a * s), (double) (b * s), (double) (1 - 2 * sq));
}

/* randomly oriented vector on the unit sphere */
INLINE real *rv3_randdir0(real *v)
{
  double a, b, sq, s;

  do { /* projection on the x-y plane */
    a = randunif(-1, 1);
    b = randunif(-1, 1);
    sq = a * a + b * b;
  } while (sq >= 1); /* avoid sin() and cos() */

  s = 2. * sqrt(1 - sq);
  return rv3_make(v, (real) (a * s), (real) (b * s), (real) (1 - 2 * sq));
}


/* randomly orientied vector within the sphere of radius `r' */
#define fv3_randball(v, r) fv3_smul(fv3_randball0(v), r)

/* randomly orientied vector within the sphere of radius `r' */
#define dv3_randball(v, r) dv3_smul(dv3_randball0(v), r)

/* randomly orientied vector within the sphere of radius `r' */
#define rv3_randball(v, r) rv3_smul(rv3_randball0(v), r)

/* randomly orientied vector within the unit sphere */
INLINE float *fv3_randball0(float *v)
{
  do {
    fv3_randunif(v, -1, 1);
  } while (fv3_sqr(v) >= 1);
  return v;
}

/* randomly orientied vector within the unit sphere */
INLINE double *dv3_randball0(double *v)
{
  do {
    dv3_randunif(v, -1, 1);
  } while (dv3_sqr(v) >= 1);
  return v;
}

/* randomly orientied vector within the unit sphere */
INLINE real *rv3_randball0(real *v)
{
  do {
    rv3_randunif(v, -1, 1);
  } while (rv3_sqr(v) >= 1);
  return v;
}


/* heavy-weight dihedral calculation */

/* structure for dihedral calculation */
typedef struct {
  int  szreal; /* sizeof real */
  int  pad0;   /* padding */
  real phi; /* cis is zero, clockwise positive */
  real cos; /* cos(m, n) */
  real sgn; /* (0, pi) is 1.0, otherwise -1.0 */

  real g2;
  real g[4][3]; /* gradient for each particle */

  real div; /* the divergence */
  real d4ij, d4ik, d4jj, d4jk, d4jl, d4kk, d4kl;

  unsigned int flags; /* a copy of flags used */
  int t1, t2, t3; /* GROMACS shift indices */
  const void *pbcdata; /* periodic boundary condition descriptor */
  int (*pbcdiff)(real *xij, const real *xi, const real *xj, const void *);
    /* function to handle pbc, use GROMACS convention: the last is the difference */
} dihcalc_t;

#define DIH_GRAD  0x0001
#define DIH_DIV   0x0002
/*#define DIH_CONJ  0x0004 */
/*#define DIH_PROJ  0x0008 */
#define DIH_I     0x0010
#define DIH_J     0x0020
#define DIH_K     0x0040
#define DIH_L     0x0080
#define DIH_FOUR  (DIH_I|DIH_J|DIH_K|DIH_L)
/* the four atoms involved */
#define DIH_ALL   (DIH_FOUR|DIH_GRAD|DIH_DIV)
/* only I and L, so no divergence */
#define DIH_ENDS  (DIH_GRAD|DIH_I|DIH_L)
/* polymer convention, 0 == trans */
#define DIH_POLYMER 0x1000

/* compute the dihedral angle, gradient g and divergence
 * of the field v conjugate to gradient (v.g = 1)
 *
 * if dih is NULL and flags is 0, only the dihedral angle is computed
 * optionally, the gradient and divergent are computed with flags
 * DIH_GRAD and DIH_DIV respectively (the latter requires the former)
 * routine for treating periodic boundary condition can specified by
 * assigning a function pointer to dih->pbcdiff with additional information
 * to dih->pbcdata entry, otherwise, dih->pbcdiff *must* be set to NULL
 * the procedure of computing similar to that in GROMACS
 *
 * the conjugate field v = g / [g.g], such that v.g = 1, where g = grad(phi)
 * it is not explicitly computed (since it lies along the gradient)
 * however, the denominator is saved to dih->g2
 * the calculation of the divergence of v is simplified by the fact that
 * the divergence of the gradient is always zero, i.e., div.g = 0, thus
 *     div.v = -2 [ g.(gg).g ] /[g.g]^2,
 * where gg = grad grad(phi) involves: d4ij, d4ik, ..., d4kl.
 *
 * both g and div can be computed for a subset of the four involving atoms
 * by passing `flags' a combination of DIH_I, DIH_J, DIH_K and DIH_L
 * however, *all* moments d4ij, d4ik, ... , d4kl are always calculated
 * though only the involved ones are used to produce the divergence. */
#define rv3_calcdihv(dih, x, idx, flags) \
  rv3_calcdih(dih, x[*(idx)], x[*(idx+1)], x[*(idx+2)], x[*(idx+3)], flags)

INLINE real rv3_calcdih(dihcalc_t *dih,
    const real *xi, const real *xj, const real *xk, const real *xl,
    unsigned int flags)
{
  real dot, scl, tol, vol, phi, sgn, cosphi;
  real nxkj, nxkj2, m2, n2;
  real xij[3], xkj[3], xkl[3];
  real m[3], n[3]; /* the planar vector of xij x xkj,  and xkj x xkj */

  if (dih != NULL && sizeof(real) != dih->szreal) {
    fprintf(stderr, "size real should be %d instead of %d\n",
        (int) sizeof(real), (int) dih->szreal);
    exit(1);
  }
  if (dih != NULL && dih->pbcdiff != NULL) { /* handle pbc */
    dih->t1 = (*dih->pbcdiff)(xij, xi, xj, dih->pbcdata);
    dih->t2 = (*dih->pbcdiff)(xkj, xk, xj, dih->pbcdata);
    dih->t3 = (*dih->pbcdiff)(xkl, xk, xl, dih->pbcdata);
  } else {
    rv3_diff(xij, xi, xj);
    rv3_diff(xkj, xk, xj);
    rv3_diff(xkl, xk, xl);
  }
  nxkj2 = rv3_sqr(xkj);
  nxkj = (real) sqrt(nxkj2);
  if (sizeof(real) <= 4)
    tol = nxkj2 * 6e-8f;
  else
    tol = nxkj2 * 1e-16f;

  rv3_cross(m, xij, xkj);
  m2 = rv3_sqr(m);
  rv3_cross(n, xkj, xkl);
  n2 = rv3_sqr(n);
  if (m2 > tol && n2 > tol) {
    scl = (real) sqrt(m2*n2);
    dot = rv3_dot(m, n);
    cosphi = dot/scl;
    if (cosphi >= (real) 1.) cosphi = 1.f;
    else if (cosphi < (real)(-1.)) cosphi = -1.f;
  } else {
    cosphi = 1.f;
  }
  phi = (real) acos(cosphi);
  vol = rv3_dot(n, xij);
  sgn = (vol > 0.0f) ? 1.0f : -1.0f;
  phi *= sgn;
  if (flags & DIH_POLYMER) { /* switch to polymer convention, 0 == trans */
    if (phi > 0) phi -= M_PI;
    else phi += M_PI;
  }
  if (dih != NULL) {
    dih->phi = phi;
    dih->sgn = sgn;
    dih->cos = cosphi;
    dih->flags = flags;
  }

  /* optionally calculate the gradient */
  if (dih != NULL && (flags & (DIH_GRAD|DIH_DIV))) { /* divergence implies gradient */
    /* clear divergence */
    dih->div = dih->d4ij = dih->d4ik = dih->d4jj = dih->d4jk = dih->d4jl = dih->d4kk = dih->d4kl = 0.0f;

    /* calculate the gradient of the dihedral */
    if (m2 > tol && n2 > tol) {
      real uvec[3], vvec[3], svec[3], g2all, invg2;
      unsigned doi, doj, dok, dol;

      doi = (flags & DIH_I);
      doj = (flags & DIH_J);
      dok = (flags & DIH_K);
      dol = (flags & DIH_L);

      rv3_smul2(dih->g[0], m,  nxkj/m2);
      rv3_smul2(dih->g[3], n, -nxkj/n2);

      rv3_smul2(uvec, dih->g[0], rv3_dot(xij, xkj)/nxkj2);
      rv3_smul2(vvec, dih->g[3], rv3_dot(xkl, xkj)/nxkj2);
      rv3_diff(svec, uvec, vvec);

      rv3_diff(dih->g[1], svec, dih->g[0]);
      rv3_nadd(dih->g[2], svec, dih->g[3]);

      g2all = 0.0f;
      if (doi) g2all += rv3_sqr(dih->g[0]);
      if (doj) g2all += rv3_sqr(dih->g[1]);
      if (dok) g2all += rv3_sqr(dih->g[2]);
      if (dol) g2all += rv3_sqr(dih->g[3]);
      dih->g2 = g2all;
      invg2 = 1.0f/g2all;

      if (flags & DIH_DIV) {
        real xkjv[3], nvv[3], mvv[3];
        real gjxij, gjmvv, gjxkl, gjnvv;
        real gkmvv, gknvv, gkxkl, gkxij;
        real kivkj, klvkj, ljvkj, ijvkj;
        real kikl, ijlj;
        real tmp1, tmp2;
        real sinmn;

        rv3_smul2(mvv, m, 1.0f/m2);
        rv3_smul2(nvv, n, 1.0f/n2);
        rv3_smul2(xkjv, xkj, 1.0f/nxkj);

        sinmn = vol*nxkj/(m2*n2);

        ijvkj = rv3_dot(xij, xkjv);
        kivkj = nxkj-ijvkj;
        klvkj = rv3_dot(xkl, xkjv);
        ljvkj = nxkj-klvkj;

        ijlj = ijvkj*ljvkj;
        kikl = kivkj*klvkj;

        gjxij = rv3_dot(dih->g[1], xij);
        gjxkl = rv3_dot(dih->g[1], xkl);
        gjmvv = rv3_dot(dih->g[1], mvv);
        gjnvv = rv3_dot(dih->g[1], nvv);
        gkxij = rv3_dot(dih->g[2], xij);
        gkxkl = rv3_dot(dih->g[2], xkl);
        gkmvv = rv3_dot(dih->g[2], mvv);
        gknvv = rv3_dot(dih->g[2], nvv);

        tmp1 = nxkj2*sinmn;
        tmp2 = tmp1/m2;
        dih->d4ij = kikl*tmp2;
        dih->d4ik = ijlj*tmp2;
        tmp2 = tmp1/n2;
        dih->d4jl = kikl*tmp2;
        dih->d4kl = ijlj*tmp2;

        dih->d4jj = -(gjxij*gjmvv+gjxkl*gjnvv)/nxkj
                +2.0f*(kivkj*gjmvv-klvkj*gjnvv)*(-kikl*sinmn);

        dih->d4jk = (gjxij*gkmvv+gjxkl*gknvv)/nxkj
              +(-(gjmvv*ljvkj+gkmvv*klvkj)*(ijvkj*kivkj)
                +(gjnvv*ijvkj+gknvv*kivkj)*(ljvkj*klvkj) )*sinmn;

        dih->d4kk = -(gkxkl*gknvv+gkxij*gkmvv)/nxkj
                +2.0f*(ljvkj*gknvv-ijvkj*gkmvv)*(ijlj*sinmn);

        /* summarize */
        if ((flags & DIH_FOUR) == DIH_FOUR) {
          tmp1 = dih->d4jj + dih->d4kk;
          tmp2 = dih->d4ij + dih->d4ik+dih->d4jk+dih->d4jl+dih->d4kl;
        } else {
          tmp1 = tmp2 = 0.0f;
          if (doj) { tmp1 += dih->d4jj; }
          if (dok) { tmp1 += dih->d4kk; }
          if (doi && doj) tmp2 += dih->d4ij;
          if (doi && dok) tmp2 += dih->d4ik;
          if (doj && dok) tmp2 += dih->d4jk;
          if (doj && dol) tmp2 += dih->d4jl;
          if (dok && dol) tmp2 += dih->d4kl;
        }
        dih->div = -2.0f*(tmp1+2.0f*tmp2)*(invg2*invg2);
      } /* do divergence */

    } else { /* clear the gradients */
      int j;
      for (j = 0; j < 4; j++)
        rv3_zero(dih->g[j]);
    }
  }
  return phi;
}

/* Gauss integral and solid angles */


/* compute the trihedral angle
 * http://planetmath.org/encyclopedia/TrihedralAngle.html
 * tan(omega/2) = vol/den,
 * where
 * den = r1 (r2.r3) + r2 (r1.r3) + r3 (r1.r2) + r1 r2 r3
 */
INLINE real rv3_solidang(const real *v1, const real *v2, const real *v3,
  real * RESTRICT g1, real * RESTRICT g2, real * RESTRICT g3)
{
  real vc[3];
  real r1, r2, r3;
  real ang, vol, den, v2d2, scnum, scden;
  const real eps = (real) 1e-10;

  r1 = rv3_norm(v1);
  r2 = rv3_norm(v2);
  r3 = rv3_norm(v3);
  if (g1 != NULL) rv3_zero(g1);
  if (g2 != NULL) rv3_zero(g2);
  if (g3 != NULL) rv3_zero(g3);

  /* at least two points coincide */
  if (r1 < eps || r2 < eps || r3 < eps) return 0;

  /* the numerator */
  vol = rv3_dot(v3, rv3_cross(vc, v1, v2));

  /* the denominator */
  den  = r1 * rv3_dot(v3, v2);
  den += r2 * rv3_dot(v3, v1);
  den += r3 * (r1*r2 + rv3_dot(v1, v2));

  v2d2 = vol*vol + den*den;

  /* this happens if two vector are opposite
     the solid angle could be evolved from  +/-pi or 0
     but unfortunately, we don't know which one */
  if (v2d2 < eps) return 0;

  if (g1 != NULL && g2 != NULL && g3 != NULL) { /* compute the gradients */
    scnum =  2.f*den/v2d2;
    scden = -2.f*vol/v2d2;

    /* cross products */
    rv3_smul(rv3_cross(g3, v1, v2), scnum);
    rv3_smul(rv3_cross(g1, v2, v3), scnum);
    rv3_smul(rv3_cross(g2, v3, v1), scnum);

    /* compute the contributions to the denominator */
    rv3_lincomb2(vc, v2, v3, r3, r2);
    rv3_sinc(vc, v1, (rv3_dot(v2, v3) + r2*r3)/r1);
    rv3_sinc(g1, vc, scden);

    rv3_lincomb2(vc, v1, v3, r3, r1);
    rv3_sinc(vc, v2, (rv3_dot(v1, v3) + r1*r3)/r2);
    rv3_sinc(g2, vc, scden);

    rv3_lincomb2(vc, v1, v2, r2, r1);
    rv3_sinc(vc, v3, (rv3_dot(v1, v2) + r1*r2)/r3);
    rv3_sinc(g3, vc, scden);
  }

  /* calculate tan(omega/2) */
  ang = (real) atan2(vol, den); /* 0 to pi */
  return 2*ang;
}


/* compute the Gauss integral for the two line segments, with gradients
 *    int_i \int_j (dri X drj).rij/ rij^3,
 * over two line segments rip - ri, rjp - rj, and rij = ri - rj
 * (-2 pi, 2 pi)
 * Note the sign is opposite to that of the dihedral */
INLINE real rv3_solidang2g(const real *ri, const real *rip,
    const real *rj, const real *rjp,
    real * RESTRICT gi, real * RESTRICT gip,
    real * RESTRICT gj, real * RESTRICT gjp)
{
  rv3_t v0, v1, v2, v3, g0, g1, g2, g3, g4, g5;
  real ang1, ang2;

  rv3_diff(v0, ri, rj);
  rv3_diff(v1, ri, rjp);
  rv3_diff(v2, rip, rj);
  rv3_diff(v3, rip, rjp);

  ang1 = rv3_solidang(v0, v1, v2, g0, g1, g2);
  ang2 = rv3_solidang(v2, v1, v3, g3, g4, g5);

  rv3_inc(rv3_inc(rv3_copy(gi,  g0), g1), g4);
  rv3_inc(rv3_inc(rv3_copy(gip, g2), g3), g5);
  rv3_neg(rv3_inc(rv3_inc(rv3_copy(gj,  g0), g2), g3));
  rv3_neg(rv3_inc(rv3_inc(rv3_copy(gjp, g1), g4), g5));

  return ang1 + ang2;
}


/* compute the double integral, old code
 *    \int_i \int_j (dri X drj).rij/ rij^3,
 * over two line segments rip - ri, rjp - rj, and rij = ri - rj
 * (-2 pi, 2 pi)
 * Note the sign is opposite to that of the dihedral */
INLINE real rv3_solidang2(const real *ri, const real *rip,
    const real *rj, const real *rjp)
{
  real v0[3], v1[3], v2[3], v3[3], vc[3];
  double r0, r1, r2, r3;
  double ang, vol, dn1, dn2, dn, tmp;

  r0 = rv3_norm(rv3_diff(v0, ri, rj));
  r1 = rv3_norm(rv3_diff(v1, ri, rjp));
  r2 = rv3_norm(rv3_diff(v2, rip, rj));
  r3 = rv3_norm(rv3_diff(v3, rip, rjp));

  /* avoid coplanar vectors */
  vol = rv3_dot(v0, rv3_cross(vc, v1, v2));
  if (fabs(vol) < 1e-28) return 0;

  /* calculate the denominator */
  tmp = r1*r2 + rv3_dot(v1, v2);
  /* http://planetmath.org/encyclopedia/TrihedralAngle.html
   * tan(omega/2) = vol/den,
   * where
   * den = r1 (r2.r3) + r2 (r1.r3) + r3 (r1.r2) + r1 r2 r3
   * */
  dn1  = r1 * rv3_dot(v0, v2);
  dn1 += r2 * rv3_dot(v0, v1) + r0 * tmp;
  dn2  = r1 * rv3_dot(v3, v2);
  dn2 += r2 * rv3_dot(v3, v1) + r3 * tmp;

  /* calculate tan(omega1/2 + omega2/2) */
  dn = (dn1 + dn2)/(dn1*dn2 - vol*vol);
  ang = atan(fabs(vol) * dn) + (dn < 0 ? M_PI : 0); /* 0 to pi */

  return (real) (vol > 0 ? 2*ang : -2*ang);
}
/* routines for 3x3 matrices */


#ifndef FM3_T
#define FM3_T fm3_t
typedef float fm3_t[3][3];
#endif

#ifndef DM3_T
#define DM3_T dm3_t
typedef double dm3_t[3][3];
#endif

#ifndef RM3_T
#define RM3_T rm3_t
typedef real rm3_t[3][3];
#endif


#define fm3_print(m, nm, fmt, nl) fm3_fprint(stdout, m, nm, fmt, nl)

#define dm3_print(m, nm, fmt, nl) dm3_fprint(stdout, m, nm, fmt, nl)

#define rm3_print(m, nm, fmt, nl) rm3_fprint(stdout, m, nm, fmt, nl)

INLINE void fm3_fprint(FILE *fp, float (*m)[3], const char *nm, const char *fmt, int nl)
{
  int i, j;

  if (nm) fprintf(fp, "%s:%c", nm, nl ? '\n' : ' ');
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++)
      fprintf(fp, fmt, m[i][j]);
    fprintf(fp, "%s", nl ? "\n" : "; ");
  }
}

INLINE void dm3_fprint(FILE *fp, double (*m)[3], const char *nm, const char *fmt, int nl)
{
  int i, j;

  if (nm) fprintf(fp, "%s:%c", nm, nl ? '\n' : ' ');
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++)
      fprintf(fp, fmt, m[i][j]);
    fprintf(fp, "%s", nl ? "\n" : "; ");
  }
}

INLINE void rm3_fprint(FILE *fp, real (*m)[3], const char *nm, const char *fmt, int nl)
{
  int i, j;

  if (nm) fprintf(fp, "%s:%c", nm, nl ? '\n' : ' ');
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++)
      fprintf(fp, fmt, m[i][j]);
    fprintf(fp, "%s", nl ? "\n" : "; ");
  }
}


INLINE fv3_t *fm3_make(float rx[3][3], float a00, float a01, float a02,
    float a10, float a11, float a12, float a20, float a21, float a22)
{
  fv3_make(rx[0], a00, a01, a02);
  fv3_make(rx[1], a10, a11, a12);
  fv3_make(rx[2], a20, a21, a22);
  return rx;
}

INLINE dv3_t *dm3_make(double rx[3][3], double a00, double a01, double a02,
    double a10, double a11, double a12, double a20, double a21, double a22)
{
  dv3_make(rx[0], a00, a01, a02);
  dv3_make(rx[1], a10, a11, a12);
  dv3_make(rx[2], a20, a21, a22);
  return rx;
}

INLINE rv3_t *rm3_make(real rx[3][3], real a00, real a01, real a02,
    real a10, real a11, real a12, real a20, real a21, real a22)
{
  rv3_make(rx[0], a00, a01, a02);
  rv3_make(rx[1], a10, a11, a12);
  rv3_make(rx[2], a20, a21, a22);
  return rx;
}


#define fm3_makem(rx, x) fm3_make(rx, \
    (float) x[0][0], (float) x[0][1], (float) x[0][2], \
    (float) x[1][0], (float) x[1][1], (float) x[1][2], \
    (float) x[2][0], (float) x[2][1], (float) x[2][2])

#define dm3_makem(rx, x) dm3_make(rx, \
    (double) x[0][0], (double) x[0][1], (double) x[0][2], \
    (double) x[1][0], (double) x[1][1], (double) x[1][2], \
    (double) x[2][0], (double) x[2][1], (double) x[2][2])

#define rm3_makem(rx, x) rm3_make(rx, \
    (real) x[0][0], (real) x[0][1], (real) x[0][2], \
    (real) x[1][0], (real) x[1][1], (real) x[1][2], \
    (real) x[2][0], (real) x[2][1], (real) x[2][2])


/* zero matrix */
#define fm3_zero(x) fm3_makem(x, 0, 0, 0, 0, 0, 0, 0, 0, 0)

/* zero matrix */
#define dm3_zero(x) dm3_makem(x, 0, 0, 0, 0, 0, 0, 0, 0, 0)

/* zero matrix */
#define rm3_zero(x) rm3_makem(x, 0, 0, 0, 0, 0, 0, 0, 0, 0)


/* identity matrix */
#define fm3_one(x) fm3_makem(x, 1, 0, 0, 0, 1, 0, 0, 0, 1)

/* identity matrix */
#define dm3_one(x) dm3_makem(x, 1, 0, 0, 0, 1, 0, 0, 0, 1)

/* identity matrix */
#define rm3_one(x) rm3_makem(x, 1, 0, 0, 0, 1, 0, 0, 0, 1)


/* a = b */
INLINE fv3_t *fm3_copy(float a[3][3], float b[3][3])
{
  fv3_copy(a[0], b[0]);
  fv3_copy(a[1], b[1]);
  fv3_copy(a[2], b[2]);
  return a;
}

/* a = b */
INLINE dv3_t *dm3_copy(double a[3][3], double b[3][3])
{
  dv3_copy(a[0], b[0]);
  dv3_copy(a[1], b[1]);
  dv3_copy(a[2], b[2]);
  return a;
}

/* a = b */
INLINE rv3_t *rm3_copy(real a[3][3], real b[3][3])
{
  rv3_copy(a[0], b[0]);
  rv3_copy(a[1], b[1]);
  rv3_copy(a[2], b[2]);
  return a;
}


/* transpose */
INLINE fv3_t *fm3_trans(float a[3][3])
{
  float x;

  x = a[0][1], a[0][1] = a[1][0], a[1][0] = x;
  x = a[0][2], a[0][2] = a[2][0], a[2][0] = x;
  x = a[2][1], a[2][1] = a[1][2], a[1][2] = x;
  return a;
}

/* transpose */
INLINE dv3_t *dm3_trans(double a[3][3])
{
  double x;

  x = a[0][1], a[0][1] = a[1][0], a[1][0] = x;
  x = a[0][2], a[0][2] = a[2][0], a[2][0] = x;
  x = a[2][1], a[2][1] = a[1][2], a[1][2] = x;
  return a;
}

/* transpose */
INLINE rv3_t *rm3_trans(real a[3][3])
{
  real x;

  x = a[0][1], a[0][1] = a[1][0], a[1][0] = x;
  x = a[0][2], a[0][2] = a[2][0], a[2][0] = x;
  x = a[2][1], a[2][1] = a[1][2], a[1][2] = x;
  return a;
}


/* a = u^T v */
INLINE fv3_t *fm3_vtv(float a[3][3], const float *u, const float *v)
{
  fv3_smul2(a[0], v, u[0]);
  fv3_smul2(a[1], v, u[1]);
  fv3_smul2(a[2], v, u[2]);
  return a;
}

/* a = u^T v */
INLINE dv3_t *dm3_vtv(double a[3][3], const double *u, const double *v)
{
  dv3_smul2(a[0], v, u[0]);
  dv3_smul2(a[1], v, u[1]);
  dv3_smul2(a[2], v, u[2]);
  return a;
}

/* a = u^T v */
INLINE rv3_t *rm3_vtv(real a[3][3], const real *u, const real *v)
{
  rv3_smul2(a[0], v, u[0]);
  rv3_smul2(a[1], v, u[1]);
  rv3_smul2(a[2], v, u[2]);
  return a;
}


/* a += b */
INLINE fv3_t *fm3_inc(float a[3][3], float b[3][3])
{
  fv3_inc(a[0], b[0]);
  fv3_inc(a[1], b[1]);
  fv3_inc(a[2], b[2]);
  return a;
}

/* a += b */
INLINE dv3_t *dm3_inc(double a[3][3], double b[3][3])
{
  dv3_inc(a[0], b[0]);
  dv3_inc(a[1], b[1]);
  dv3_inc(a[2], b[2]);
  return a;
}

/* a += b */
INLINE rv3_t *rm3_inc(real a[3][3], real b[3][3])
{
  rv3_inc(a[0], b[0]);
  rv3_inc(a[1], b[1]);
  rv3_inc(a[2], b[2]);
  return a;
}


/* a += b*s */
INLINE fv3_t *fm3_sinc(float a[3][3], float b[3][3], float s)
{
  fv3_sinc(a[0], b[0], s);
  fv3_sinc(a[1], b[1], s);
  fv3_sinc(a[2], b[2], s);
  return a;
}

/* a += b*s */
INLINE dv3_t *dm3_sinc(double a[3][3], double b[3][3], double s)
{
  dv3_sinc(a[0], b[0], s);
  dv3_sinc(a[1], b[1], s);
  dv3_sinc(a[2], b[2], s);
  return a;
}

/* a += b*s */
INLINE rv3_t *rm3_sinc(real a[3][3], real b[3][3], real s)
{
  rv3_sinc(a[0], b[0], s);
  rv3_sinc(a[1], b[1], s);
  rv3_sinc(a[2], b[2], s);
  return a;
}


/* c = a b */
INLINE fv3_t *fm3_mul(float c[3][3], float a[3][3], float b[3][3])
{
  int i, j;
  for (i = 0; i < 3; i++)
    for (j = 0; j < 3; j++)
      c[i][j] = a[i][0]*b[0][j] + a[i][1]*b[1][j] + a[i][2]*b[2][j];
  return c;
}

/* c = a b */
INLINE dv3_t *dm3_mul(double c[3][3], double a[3][3], double b[3][3])
{
  int i, j;
  for (i = 0; i < 3; i++)
    for (j = 0; j < 3; j++)
      c[i][j] = a[i][0]*b[0][j] + a[i][1]*b[1][j] + a[i][2]*b[2][j];
  return c;
}

/* c = a b */
INLINE rv3_t *rm3_mul(real c[3][3], real a[3][3], real b[3][3])
{
  int i, j;
  for (i = 0; i < 3; i++)
    for (j = 0; j < 3; j++)
      c[i][j] = a[i][0]*b[0][j] + a[i][1]*b[1][j] + a[i][2]*b[2][j];
  return c;
}


/* c = a b^T */
INLINE fv3_t *fm3_mult(float c[3][3], float a[3][3], float b[3][3])
{
  int i, j;
  for (i = 0; i < 3; i++)
    for (j = 0; j < 3; j++)
      c[i][j] = fv3_dot(a[i], b[j]);
  return c;
}

/* c = a b^T */
INLINE dv3_t *dm3_mult(double c[3][3], double a[3][3], double b[3][3])
{
  int i, j;
  for (i = 0; i < 3; i++)
    for (j = 0; j < 3; j++)
      c[i][j] = dv3_dot(a[i], b[j]);
  return c;
}

/* c = a b^T */
INLINE rv3_t *rm3_mult(real c[3][3], real a[3][3], real b[3][3])
{
  int i, j;
  for (i = 0; i < 3; i++)
    for (j = 0; j < 3; j++)
      c[i][j] = rv3_dot(a[i], b[j]);
  return c;
}


/* c = a^T b */
INLINE fv3_t *fm3_tmul(float c[3][3], float a[3][3], float b[3][3])
{
  int i, j;
  for (i = 0; i < 3; i++)
    for (j = 0; j < 3; j++)
      c[i][j] = a[0][i]*b[0][j] + a[1][i]*b[1][j] + a[2][i]*b[2][j];
  return c;
}

/* c = a^T b */
INLINE dv3_t *dm3_tmul(double c[3][3], double a[3][3], double b[3][3])
{
  int i, j;
  for (i = 0; i < 3; i++)
    for (j = 0; j < 3; j++)
      c[i][j] = a[0][i]*b[0][j] + a[1][i]*b[1][j] + a[2][i]*b[2][j];
  return c;
}

/* c = a^T b */
INLINE rv3_t *rm3_tmul(real c[3][3], real a[3][3], real b[3][3])
{
  int i, j;
  for (i = 0; i < 3; i++)
    for (j = 0; j < 3; j++)
      c[i][j] = a[0][i]*b[0][j] + a[1][i]*b[1][j] + a[2][i]*b[2][j];
  return c;
}


/* c = a v */
INLINE float *fm3_mulvec(float * RESTRICT c, float a[3][3], const float *v)
{
  c[0] = fv3_dot(a[0], v);
  c[1] = fv3_dot(a[1], v);
  c[2] = fv3_dot(a[2], v);
  return c;
}

/* c = a v */
INLINE double *dm3_mulvec(double * RESTRICT c, double a[3][3], const double *v)
{
  c[0] = dv3_dot(a[0], v);
  c[1] = dv3_dot(a[1], v);
  c[2] = dv3_dot(a[2], v);
  return c;
}

/* c = a v */
INLINE real *rm3_mulvec(real * RESTRICT c, real a[3][3], const real *v)
{
  c[0] = rv3_dot(a[0], v);
  c[1] = rv3_dot(a[1], v);
  c[2] = rv3_dot(a[2], v);
  return c;
}


/* c = a^T v */
INLINE float *fm3_tmulvec(float * RESTRICT c, float a[3][3], const float *v)
{
  c[0] = a[0][0]*v[0] + a[1][0]*v[1] + a[2][0]*v[2];
  c[1] = a[0][1]*v[0] + a[1][1]*v[1] + a[2][1]*v[2];
  c[2] = a[0][2]*v[0] + a[1][2]*v[1] + a[2][2]*v[2];
  return c;
}

/* c = a^T v */
INLINE double *dm3_tmulvec(double * RESTRICT c, double a[3][3], const double *v)
{
  c[0] = a[0][0]*v[0] + a[1][0]*v[1] + a[2][0]*v[2];
  c[1] = a[0][1]*v[0] + a[1][1]*v[1] + a[2][1]*v[2];
  c[2] = a[0][2]*v[0] + a[1][2]*v[1] + a[2][2]*v[2];
  return c;
}

/* c = a^T v */
INLINE real *rm3_tmulvec(real * RESTRICT c, real a[3][3], const real *v)
{
  c[0] = a[0][0]*v[0] + a[1][0]*v[1] + a[2][0]*v[2];
  c[1] = a[0][1]*v[0] + a[1][1]*v[1] + a[2][1]*v[2];
  c[2] = a[0][2]*v[0] + a[1][2]*v[1] + a[2][2]*v[2];
  return c;
}


/* return 0 rotation matrix around v for ang */
INLINE fv3_t *fm3_mkrot(float m[3][3], const float *v, float ang)
{
  float c = (float) cos(ang), s = (float) sin(ang), nc, n[3];

  fv3_copy(n, v);
  fv3_normalize(n);
  nc = 1 - c;
  m[0][0] = n[0] * n[0] * nc + c;
  m[0][1] = n[0] * n[1] * nc - n[2] * s;
  m[0][2] = n[0] * n[2] * nc + n[1] * s;
  m[1][0] = n[1] * n[0] * nc + n[2] * s;
  m[1][1] = n[1] * n[1] * nc + c;
  m[1][2] = n[1] * n[2] * nc - n[0] * s;
  m[2][0] = n[2] * n[0] * nc - n[1] * s;
  m[2][1] = n[2] * n[1] * nc + n[0] * s;
  m[2][2] = n[2] * n[2] * nc + c;
  return m;
}

/* return 0 rotation matrix around v for ang */
INLINE dv3_t *dm3_mkrot(double m[3][3], const double *v, double ang)
{
  double c = (double) cos(ang), s = (double) sin(ang), nc, n[3];

  dv3_copy(n, v);
  dv3_normalize(n);
  nc = 1 - c;
  m[0][0] = n[0] * n[0] * nc + c;
  m[0][1] = n[0] * n[1] * nc - n[2] * s;
  m[0][2] = n[0] * n[2] * nc + n[1] * s;
  m[1][0] = n[1] * n[0] * nc + n[2] * s;
  m[1][1] = n[1] * n[1] * nc + c;
  m[1][2] = n[1] * n[2] * nc - n[0] * s;
  m[2][0] = n[2] * n[0] * nc - n[1] * s;
  m[2][1] = n[2] * n[1] * nc + n[0] * s;
  m[2][2] = n[2] * n[2] * nc + c;
  return m;
}

/* return 0 rotation matrix around v for ang */
INLINE rv3_t *rm3_mkrot(real m[3][3], const real *v, real ang)
{
  real c = (real) cos(ang), s = (real) sin(ang), nc, n[3];

  rv3_copy(n, v);
  rv3_normalize(n);
  nc = 1 - c;
  m[0][0] = n[0] * n[0] * nc + c;
  m[0][1] = n[0] * n[1] * nc - n[2] * s;
  m[0][2] = n[0] * n[2] * nc + n[1] * s;
  m[1][0] = n[1] * n[0] * nc + n[2] * s;
  m[1][1] = n[1] * n[1] * nc + c;
  m[1][2] = n[1] * n[2] * nc - n[0] * s;
  m[2][0] = n[2] * n[0] * nc - n[1] * s;
  m[2][1] = n[2] * n[1] * nc + n[0] * s;
  m[2][2] = n[2] * n[2] * nc + c;
  return m;
}


/* rotate `x' around `u' by `ang', save the result to `y' */
INLINE float *fv3_rot(float * RESTRICT y, const float *x, const float *u, float ang)
{
  float m[3][3];

  fm3_mkrot(m, u, ang);
  fm3_mulvec(y, m, x);
  return y;
}

/* rotate `x' around `u' by `ang', save the result to `y' */
INLINE double *dv3_rot(double * RESTRICT y, const double *x, const double *u, double ang)
{
  double m[3][3];

  dm3_mkrot(m, u, ang);
  dm3_mulvec(y, m, x);
  return y;
}

/* rotate `x' around `u' by `ang', save the result to `y' */
INLINE real *rv3_rot(real * RESTRICT y, const real *x, const real *u, real ang)
{
  real m[3][3];

  rm3_mkrot(m, u, ang);
  rm3_mulvec(y, m, x);
  return y;
}


/* determinant of a 3x3 matrix */
INLINE float fm3_det(float a[3][3])
{
  return a[0][0] * (a[1][1]*a[2][2] - a[1][2]*a[2][1])
      +  a[0][1] * (a[1][2]*a[2][0] - a[1][0]*a[2][2])
      +  a[0][2] * (a[1][0]*a[2][1] - a[1][1]*a[2][0]);
}

/* determinant of a 3x3 matrix */
INLINE double dm3_det(double a[3][3])
{
  return a[0][0] * (a[1][1]*a[2][2] - a[1][2]*a[2][1])
      +  a[0][1] * (a[1][2]*a[2][0] - a[1][0]*a[2][2])
      +  a[0][2] * (a[1][0]*a[2][1] - a[1][1]*a[2][0]);
}

/* determinant of a 3x3 matrix */
INLINE real rm3_det(real a[3][3])
{
  return a[0][0] * (a[1][1]*a[2][2] - a[1][2]*a[2][1])
      +  a[0][1] * (a[1][2]*a[2][0] - a[1][0]*a[2][2])
      +  a[0][2] * (a[1][0]*a[2][1] - a[1][1]*a[2][0]);
}


/* inverse matrix b = a^(-1) */
INLINE fv3_t *fm3_inv(float b[3][3], float a[3][3])
{
  float d00, d01, d02, detm;
  d00 = a[1][1]*a[2][2] - a[1][2]*a[2][1];
  d01 = a[1][2]*a[2][0] - a[1][0]*a[2][2];
  d02 = a[1][0]*a[2][1] - a[1][1]*a[2][0];
  detm = a[0][0]*d00 + a[0][1]*d01 + a[0][2]*d02;
  if (fabs(detm) < 1e-30) detm = (detm < 0) ? -1e-30f: 1e-30f;
  b[0][0] = d00/detm;
  b[0][1] = (a[2][1]*a[0][2] - a[0][1]*a[2][2])/detm;
  b[0][2] = (a[0][1]*a[1][2] - a[0][2]*a[1][1])/detm;
  b[1][0] = d01/detm;
  b[1][1] = (a[2][2]*a[0][0] - a[2][0]*a[0][2])/detm;
  b[1][2] = (a[0][2]*a[1][0] - a[1][2]*a[0][0])/detm;
  b[2][0] = d02/detm;
  b[2][1] = (a[2][0]*a[0][1] - a[2][1]*a[0][0])/detm;
  b[2][2] = (a[0][0]*a[1][1] - a[0][1]*a[1][0])/detm;
  return b;
}

/* inverse matrix b = a^(-1) */
INLINE dv3_t *dm3_inv(double b[3][3], double a[3][3])
{
  double d00, d01, d02, detm;
  d00 = a[1][1]*a[2][2] - a[1][2]*a[2][1];
  d01 = a[1][2]*a[2][0] - a[1][0]*a[2][2];
  d02 = a[1][0]*a[2][1] - a[1][1]*a[2][0];
  detm = a[0][0]*d00 + a[0][1]*d01 + a[0][2]*d02;
  if (fabs(detm) < 1e-30) detm = (detm < 0) ? -1e-30f: 1e-30f;
  b[0][0] = d00/detm;
  b[0][1] = (a[2][1]*a[0][2] - a[0][1]*a[2][2])/detm;
  b[0][2] = (a[0][1]*a[1][2] - a[0][2]*a[1][1])/detm;
  b[1][0] = d01/detm;
  b[1][1] = (a[2][2]*a[0][0] - a[2][0]*a[0][2])/detm;
  b[1][2] = (a[0][2]*a[1][0] - a[1][2]*a[0][0])/detm;
  b[2][0] = d02/detm;
  b[2][1] = (a[2][0]*a[0][1] - a[2][1]*a[0][0])/detm;
  b[2][2] = (a[0][0]*a[1][1] - a[0][1]*a[1][0])/detm;
  return b;
}

/* inverse matrix b = a^(-1) */
INLINE rv3_t *rm3_inv(real b[3][3], real a[3][3])
{
  real d00, d01, d02, detm;
  d00 = a[1][1]*a[2][2] - a[1][2]*a[2][1];
  d01 = a[1][2]*a[2][0] - a[1][0]*a[2][2];
  d02 = a[1][0]*a[2][1] - a[1][1]*a[2][0];
  detm = a[0][0]*d00 + a[0][1]*d01 + a[0][2]*d02;
  if (fabs(detm) < 1e-30) detm = (detm < 0) ? -1e-30f: 1e-30f;
  b[0][0] = d00/detm;
  b[0][1] = (a[2][1]*a[0][2] - a[0][1]*a[2][2])/detm;
  b[0][2] = (a[0][1]*a[1][2] - a[0][2]*a[1][1])/detm;
  b[1][0] = d01/detm;
  b[1][1] = (a[2][2]*a[0][0] - a[2][0]*a[0][2])/detm;
  b[1][2] = (a[0][2]*a[1][0] - a[1][2]*a[0][0])/detm;
  b[2][0] = d02/detm;
  b[2][1] = (a[2][0]*a[0][1] - a[2][1]*a[0][0])/detm;
  b[2][2] = (a[0][0]*a[1][1] - a[0][1]*a[1][0])/detm;
  return b;
}


/* compute eigenvalues of a 3x3 matrix
 * solving a cubic equation
 * use double for internal calculation */
INLINE float *fm3_eigval(float v[3], float a[3][3])
{
  double m, p, q, pr, pr3, a00, a11, a22;

  m = (a[0][0] + a[1][1] + a[2][2])/3;
  a00 = a[0][0] - m;
  a11 = a[1][1] - m;
  a22 = a[2][2] - m;
  q = ( a00 * (a11*a22 - a[1][2]*a[2][1])
      + a[0][1] * (a[1][2]*a[2][0] - a[1][0]*a22)
      + a[0][2] * (a[1][0]*a[2][1] - a11*a[2][0]) ) / 2.0;
  p = (a00*a00 + a11*a11 + a22*a22) / 6.0
    + (a[0][1]*a[1][0] + a[1][2]*a[2][1] + a[2][0]*a[0][2]) / 3.0;
  /* solve x^3 - 3 p x  - 2 q = 0 */
  pr = sqrt(p);
  pr3 = p * pr;
  if (pr3 <= fabs(q)) {
    if (q < 0.) { /* choose phi = pi/3 */
      v[1] = v[0] = (float) (m + pr);
      v[2] = (float) (m - 2.0 * pr);
    } else { /* phi = 0 */
      v[0] = (float) (m + 2.0 * pr);
      v[2] = v[1] = (float) (m - pr);
    }
  } else {
    double phi = acos(q/pr3)/3.0; /* 0 < phi < pi/3 */

    v[0] = (float) (m + 2.0 * pr * cos(phi));  /* largest */
    v[1] = (float) (m + 2.0 * pr * cos(phi - 2*M_PI/3)); /* second largest */
    v[2] = (float) (m + 2.0 * pr * cos(phi + 2*M_PI/3)); /* smallest */
  }
  return v;
}

/* compute eigenvalues of a 3x3 matrix
 * solving a cubic equation
 * use double for internal calculation */
INLINE double *dm3_eigval(double v[3], double a[3][3])
{
  double m, p, q, pr, pr3, a00, a11, a22;

  m = (a[0][0] + a[1][1] + a[2][2])/3;
  a00 = a[0][0] - m;
  a11 = a[1][1] - m;
  a22 = a[2][2] - m;
  q = ( a00 * (a11*a22 - a[1][2]*a[2][1])
      + a[0][1] * (a[1][2]*a[2][0] - a[1][0]*a22)
      + a[0][2] * (a[1][0]*a[2][1] - a11*a[2][0]) ) / 2.0;
  p = (a00*a00 + a11*a11 + a22*a22) / 6.0
    + (a[0][1]*a[1][0] + a[1][2]*a[2][1] + a[2][0]*a[0][2]) / 3.0;
  /* solve x^3 - 3 p x  - 2 q = 0 */
  pr = sqrt(p);
  pr3 = p * pr;
  if (pr3 <= fabs(q)) {
    if (q < 0.) { /* choose phi = pi/3 */
      v[1] = v[0] = (double) (m + pr);
      v[2] = (double) (m - 2.0 * pr);
    } else { /* phi = 0 */
      v[0] = (double) (m + 2.0 * pr);
      v[2] = v[1] = (double) (m - pr);
    }
  } else {
    double phi = acos(q/pr3)/3.0; /* 0 < phi < pi/3 */

    v[0] = (double) (m + 2.0 * pr * cos(phi));  /* largest */
    v[1] = (double) (m + 2.0 * pr * cos(phi - 2*M_PI/3)); /* second largest */
    v[2] = (double) (m + 2.0 * pr * cos(phi + 2*M_PI/3)); /* smallest */
  }
  return v;
}

/* compute eigenvalues of a 3x3 matrix
 * solving a cubic equation
 * use double for internal calculation */
INLINE real *rm3_eigval(real v[3], real a[3][3])
{
  double m, p, q, pr, pr3, a00, a11, a22;

  m = (a[0][0] + a[1][1] + a[2][2])/3;
  a00 = a[0][0] - m;
  a11 = a[1][1] - m;
  a22 = a[2][2] - m;
  q = ( a00 * (a11*a22 - a[1][2]*a[2][1])
      + a[0][1] * (a[1][2]*a[2][0] - a[1][0]*a22)
      + a[0][2] * (a[1][0]*a[2][1] - a11*a[2][0]) ) / 2.0;
  p = (a00*a00 + a11*a11 + a22*a22) / 6.0
    + (a[0][1]*a[1][0] + a[1][2]*a[2][1] + a[2][0]*a[0][2]) / 3.0;
  /* solve x^3 - 3 p x  - 2 q = 0 */
  pr = sqrt(p);
  pr3 = p * pr;
  if (pr3 <= fabs(q)) {
    if (q < 0.) { /* choose phi = pi/3 */
      v[1] = v[0] = (real) (m + pr);
      v[2] = (real) (m - 2.0 * pr);
    } else { /* phi = 0 */
      v[0] = (real) (m + 2.0 * pr);
      v[2] = v[1] = (real) (m - pr);
    }
  } else {
    double phi = acos(q/pr3)/3.0; /* 0 < phi < pi/3 */

    v[0] = (real) (m + 2.0 * pr * cos(phi));  /* largest */
    v[1] = (real) (m + 2.0 * pr * cos(phi - 2*M_PI/3)); /* second largest */
    v[2] = (real) (m + 2.0 * pr * cos(phi + 2*M_PI/3)); /* smallest */
  }
  return v;
}


/* sort `s' to descending order, order `u' and `v' correspondingly */
INLINE void fv3_sort3(float s[3], float (*u)[3], float (*v)[3])
{
  float tmp;

  if (s[2] > s[1]) {
    tmp = s[1]; s[1] = s[2]; s[2] = tmp;
    if (u) fv3_swap(u[1], u[2]);
    if (v) fv3_swap(v[1], v[2]);
  }
  if (s[1] > s[0]) {
    tmp = s[0]; s[0] = s[1]; s[1] = tmp;
    if (u) fv3_swap(u[0], u[1]);
    if (v) fv3_swap(v[0], v[1]);
  }
  if (s[2] > s[1]) {
    tmp = s[1]; s[1] = s[2]; s[2] = tmp;
    if (u) fv3_swap(u[1], u[2]);
    if (v) fv3_swap(v[1], v[2]);
  }
}

/* sort `s' to descending order, order `u' and `v' correspondingly */
INLINE void dv3_sort3(double s[3], double (*u)[3], double (*v)[3])
{
  double tmp;

  if (s[2] > s[1]) {
    tmp = s[1]; s[1] = s[2]; s[2] = tmp;
    if (u) dv3_swap(u[1], u[2]);
    if (v) dv3_swap(v[1], v[2]);
  }
  if (s[1] > s[0]) {
    tmp = s[0]; s[0] = s[1]; s[1] = tmp;
    if (u) dv3_swap(u[0], u[1]);
    if (v) dv3_swap(v[0], v[1]);
  }
  if (s[2] > s[1]) {
    tmp = s[1]; s[1] = s[2]; s[2] = tmp;
    if (u) dv3_swap(u[1], u[2]);
    if (v) dv3_swap(v[1], v[2]);
  }
}

/* sort `s' to descending order, order `u' and `v' correspondingly */
INLINE void rv3_sort3(real s[3], real (*u)[3], real (*v)[3])
{
  real tmp;

  if (s[2] > s[1]) {
    tmp = s[1]; s[1] = s[2]; s[2] = tmp;
    if (u) rv3_swap(u[1], u[2]);
    if (v) rv3_swap(v[1], v[2]);
  }
  if (s[1] > s[0]) {
    tmp = s[0]; s[0] = s[1]; s[1] = tmp;
    if (u) rv3_swap(u[0], u[1]);
    if (v) rv3_swap(v[0], v[1]);
  }
  if (s[2] > s[1]) {
    tmp = s[1]; s[1] = s[2]; s[2] = tmp;
    if (u) rv3_swap(u[1], u[2]);
    if (v) rv3_swap(v[1], v[2]);
  }
}


/* return the pivot row r and column c, starting from (r0, c0)
 * cmap[r0] registers the actual column index */
INLINE double fm3_pivot_(float m[3][3], int r0, int cmap[])
{
  int i, j, r, c;
  double tmp, max;
  float t;

  /* 1. find the pivot row and column */
  max = -1;
  for (j = r0; j < 3; j++)
    for (i = r0; i < 3; i++)
      if ((tmp = fabs(m[i][j])) > max)
        r = i, c = j, max = tmp;

  /* 2. put the pivot to the left-top corner */
  /* swap rows r and r0, which doesn't affect the solution */
  if (r != r0) fv3_swap(m[r], m[r0]);

  if (c != r0) { /* swap columns c and r0 */
    for (i = 0; i < 3; i++) /* must be from row 0 */
      t = m[i][c], m[i][c] = m[i][r0], m[i][r0] = t;
    i = cmap[c], cmap[c] = cmap[r0], cmap[r0] = i;
  }
  return max;
}

/* return the pivot row r and column c, starting from (r0, c0)
 * cmap[r0] registers the actual column index */
INLINE double dm3_pivot_(double m[3][3], int r0, int cmap[])
{
  int i, j, r, c;
  double tmp, max;
  double t;

  /* 1. find the pivot row and column */
  max = -1;
  for (j = r0; j < 3; j++)
    for (i = r0; i < 3; i++)
      if ((tmp = fabs(m[i][j])) > max)
        r = i, c = j, max = tmp;

  /* 2. put the pivot to the left-top corner */
  /* swap rows r and r0, which doesn't affect the solution */
  if (r != r0) dv3_swap(m[r], m[r0]);

  if (c != r0) { /* swap columns c and r0 */
    for (i = 0; i < 3; i++) /* must be from row 0 */
      t = m[i][c], m[i][c] = m[i][r0], m[i][r0] = t;
    i = cmap[c], cmap[c] = cmap[r0], cmap[r0] = i;
  }
  return max;
}

/* return the pivot row r and column c, starting from (r0, c0)
 * cmap[r0] registers the actual column index */
INLINE double rm3_pivot_(real m[3][3], int r0, int cmap[])
{
  int i, j, r, c;
  double tmp, max;
  real t;

  /* 1. find the pivot row and column */
  max = -1;
  for (j = r0; j < 3; j++)
    for (i = r0; i < 3; i++)
      if ((tmp = fabs(m[i][j])) > max)
        r = i, c = j, max = tmp;

  /* 2. put the pivot to the left-top corner */
  /* swap rows r and r0, which doesn't affect the solution */
  if (r != r0) rv3_swap(m[r], m[r0]);

  if (c != r0) { /* swap columns c and r0 */
    for (i = 0; i < 3; i++) /* must be from row 0 */
      t = m[i][c], m[i][c] = m[i][r0], m[i][r0] = t;
    i = cmap[c], cmap[c] = cmap[r0], cmap[r0] = i;
  }
  return max;
}


/* Solve matrix equation a x = 0 by Gaussian elimination (full-pivot)
 * The matrix 'a' is destroyed, solutions are saved as *row* vectors in 'x'
 * return the number of solutions */
INLINE int fm3_solvezero(float a[3][3], float (*x)[3])
{
  double max, tol, tol1, tol2;
  int cmap[3] = {0, 1, 2};
  float a00;

  max = fm3_pivot_(a, 0, cmap); /* pivot for column 0 */

  if (max <= 0) { /* matrix is zero */
    fv3_make(x[0], 1, 0, 0);
    fv3_make(x[1], 0, 1, 0);
    fv3_make(x[2], 0, 0, 1);
    return 3;
  }

  /* normalize row 0 such that a[0][0] = 1 */
  a00 = a[0][0];
  fv3_smul(a[0], 1/a00);
  fv3_smul(a[1], 1/a00);
  fv3_smul(a[2], 1/a00);
  /* gaussian elimination */
  a[1][1] -= a[1][0] * a[0][1];
  a[1][2] -= a[1][0] * a[0][2];
  a[2][1] -= a[2][0] * a[0][1];
  a[2][2] -= a[2][0] * a[0][2];

  max = fm3_pivot_(a, 1, cmap); /* pivot for column 1 */
  tol1 = 10.*(sizeof(double) == sizeof(float) ? DBL_EPSILON : FLT_EPSILON);
  /* estimate intrinsic error: the determinant is supposed to
   * be zero now; if not, use it as the intrinsic error */
  tol2 = 3 * sqrt(fabs(a[1][1]*a[2][2] - a[1][2]*a[2][1]));
  tol = tol1 > tol2 ? tol1 : tol2;

  if (max <= tol) { /* zero */
    a[1][ cmap[0] ] = a[0][0];
    a[1][ cmap[1] ] = a[0][1];
    a[1][ cmap[2] ] = a[0][2];
    fv3_makenorm(x[0], a[1][1], -a[1][0], 0);
    fv3_normalize( fv3_cross(x[1], a[1], x[0]) );
    return 2;
  }

  x[0][ cmap[1] ] = a[1][2];
  x[0][ cmap[2] ] = -a[1][1];
  x[0][ cmap[0] ] = - a[0][1] * a[1][2] - a[0][2] * (-a[1][1]);
  fv3_normalize(x[0]);
  return 1;
}

/* Solve matrix equation a x = 0 by Gaussian elimination (full-pivot)
 * The matrix 'a' is destroyed, solutions are saved as *row* vectors in 'x'
 * return the number of solutions */
INLINE int dm3_solvezero(double a[3][3], double (*x)[3])
{
  double max, tol, tol1, tol2;
  int cmap[3] = {0, 1, 2};
  double a00;

  max = dm3_pivot_(a, 0, cmap); /* pivot for column 0 */

  if (max <= 0) { /* matrix is zero */
    dv3_make(x[0], 1, 0, 0);
    dv3_make(x[1], 0, 1, 0);
    dv3_make(x[2], 0, 0, 1);
    return 3;
  }

  /* normalize row 0 such that a[0][0] = 1 */
  a00 = a[0][0];
  dv3_smul(a[0], 1/a00);
  dv3_smul(a[1], 1/a00);
  dv3_smul(a[2], 1/a00);
  /* gaussian elimination */
  a[1][1] -= a[1][0] * a[0][1];
  a[1][2] -= a[1][0] * a[0][2];
  a[2][1] -= a[2][0] * a[0][1];
  a[2][2] -= a[2][0] * a[0][2];

  max = dm3_pivot_(a, 1, cmap); /* pivot for column 1 */
  tol1 = 10.*(sizeof(double) == sizeof(double) ? DBL_EPSILON : FLT_EPSILON);
  /* estimate intrinsic error: the determinant is supposed to
   * be zero now; if not, use it as the intrinsic error */
  tol2 = 3 * sqrt(fabs(a[1][1]*a[2][2] - a[1][2]*a[2][1]));
  tol = tol1 > tol2 ? tol1 : tol2;

  if (max <= tol) { /* zero */
    a[1][ cmap[0] ] = a[0][0];
    a[1][ cmap[1] ] = a[0][1];
    a[1][ cmap[2] ] = a[0][2];
    dv3_makenorm(x[0], a[1][1], -a[1][0], 0);
    dv3_normalize( dv3_cross(x[1], a[1], x[0]) );
    return 2;
  }

  x[0][ cmap[1] ] = a[1][2];
  x[0][ cmap[2] ] = -a[1][1];
  x[0][ cmap[0] ] = - a[0][1] * a[1][2] - a[0][2] * (-a[1][1]);
  dv3_normalize(x[0]);
  return 1;
}

/* Solve matrix equation a x = 0 by Gaussian elimination (full-pivot)
 * The matrix 'a' is destroyed, solutions are saved as *row* vectors in 'x'
 * return the number of solutions */
INLINE int rm3_solvezero(real a[3][3], real (*x)[3])
{
  double max, tol, tol1, tol2;
  int cmap[3] = {0, 1, 2};
  real a00;

  max = rm3_pivot_(a, 0, cmap); /* pivot for column 0 */

  if (max <= 0) { /* matrix is zero */
    rv3_make(x[0], 1, 0, 0);
    rv3_make(x[1], 0, 1, 0);
    rv3_make(x[2], 0, 0, 1);
    return 3;
  }

  /* normalize row 0 such that a[0][0] = 1 */
  a00 = a[0][0];
  rv3_smul(a[0], 1/a00);
  rv3_smul(a[1], 1/a00);
  rv3_smul(a[2], 1/a00);
  /* gaussian elimination */
  a[1][1] -= a[1][0] * a[0][1];
  a[1][2] -= a[1][0] * a[0][2];
  a[2][1] -= a[2][0] * a[0][1];
  a[2][2] -= a[2][0] * a[0][2];

  max = rm3_pivot_(a, 1, cmap); /* pivot for column 1 */
  tol1 = 10.*(sizeof(double) == sizeof(real) ? DBL_EPSILON : FLT_EPSILON);
  /* estimate intrinsic error: the determinant is supposed to
   * be zero now; if not, use it as the intrinsic error */
  tol2 = 3 * sqrt(fabs(a[1][1]*a[2][2] - a[1][2]*a[2][1]));
  tol = tol1 > tol2 ? tol1 : tol2;

  if (max <= tol) { /* zero */
    a[1][ cmap[0] ] = a[0][0];
    a[1][ cmap[1] ] = a[0][1];
    a[1][ cmap[2] ] = a[0][2];
    rv3_makenorm(x[0], a[1][1], -a[1][0], 0);
    rv3_normalize( rv3_cross(x[1], a[1], x[0]) );
    return 2;
  }

  x[0][ cmap[1] ] = a[1][2];
  x[0][ cmap[2] ] = -a[1][1];
  x[0][ cmap[0] ] = - a[0][1] * a[1][2] - a[0][2] * (-a[1][1]);
  rv3_normalize(x[0]);
  return 1;
}


/* given an eigenvalue, return the corresponding eigenvectors
 * Note there might be multiple eigenvectors for the eigenvalue */
INLINE int fm3_eigvecs(float (*vecs)[3], float mat[3][3], float val)
{
  float m[3][3];

  fm3_copy(m, mat); /* make a matrix */
  m[0][0] -= val;
  m[1][1] -= val;
  m[2][2] -= val;
  return fm3_solvezero(m, vecs);
}

/* given an eigenvalue, return the corresponding eigenvectors
 * Note there might be multiple eigenvectors for the eigenvalue */
INLINE int dm3_eigvecs(double (*vecs)[3], double mat[3][3], double val)
{
  double m[3][3];

  dm3_copy(m, mat); /* make a matrix */
  m[0][0] -= val;
  m[1][1] -= val;
  m[2][2] -= val;
  return dm3_solvezero(m, vecs);
}

/* given an eigenvalue, return the corresponding eigenvectors
 * Note there might be multiple eigenvectors for the eigenvalue */
INLINE int rm3_eigvecs(real (*vecs)[3], real mat[3][3], real val)
{
  real m[3][3];

  rm3_copy(m, mat); /* make a matrix */
  m[0][0] -= val;
  m[1][1] -= val;
  m[2][2] -= val;
  return rm3_solvezero(m, vecs);
}


/* given the matrix 'mat' and its eigenvalues 'v' return eigenvalues 'vecs'
 * ideally, eigenvalues should be sorted in magnitude-descending order
 * by default, vecs are transposed as a set of column vectors
 * set 'nt' != 0 to disable it: so vecs[0] is the first eigenvector  */
INLINE fv3_t *fm3_eigsys(float v[3], float vecs[3][3], float mat[3][3], int nt)
{
  float vs[5][3] = {{0}}; /* for safety, vs needs 5 rows */
  int n = 0, nn, i = 0;

  fm3_eigval(v, mat);

  for (nn = i = 0; i < 3; i++) {
    n = fm3_eigvecs(vs + nn, mat, v[nn]);
    if (n == 0) return NULL;
    if ((nn += n) >= 3) break;
  }

  fm3_copy(vecs, vs);
  fv3_sort3(v, vecs, NULL);

  return nt ? vecs : fm3_trans(vecs);
}

/* given the matrix 'mat' and its eigenvalues 'v' return eigenvalues 'vecs'
 * ideally, eigenvalues should be sorted in magnitude-descending order
 * by default, vecs are transposed as a set of column vectors
 * set 'nt' != 0 to disable it: so vecs[0] is the first eigenvector  */
INLINE dv3_t *dm3_eigsys(double v[3], double vecs[3][3], double mat[3][3], int nt)
{
  double vs[5][3] = {{0}}; /* for safety, vs needs 5 rows */
  int n = 0, nn, i = 0;

  dm3_eigval(v, mat);

  for (nn = i = 0; i < 3; i++) {
    n = dm3_eigvecs(vs + nn, mat, v[nn]);
    if (n == 0) return NULL;
    if ((nn += n) >= 3) break;
  }

  dm3_copy(vecs, vs);
  dv3_sort3(v, vecs, NULL);

  return nt ? vecs : dm3_trans(vecs);
}

/* given the matrix 'mat' and its eigenvalues 'v' return eigenvalues 'vecs'
 * ideally, eigenvalues should be sorted in magnitude-descending order
 * by default, vecs are transposed as a set of column vectors
 * set 'nt' != 0 to disable it: so vecs[0] is the first eigenvector  */
INLINE rv3_t *rm3_eigsys(real v[3], real vecs[3][3], real mat[3][3], int nt)
{
  real vs[5][3] = {{0}}; /* for safety, vs needs 5 rows */
  int n = 0, nn, i = 0;

  rm3_eigval(v, mat);

  for (nn = i = 0; i < 3; i++) {
    n = rm3_eigvecs(vs + nn, mat, v[nn]);
    if (n == 0) return NULL;
    if ((nn += n) >= 3) break;
  }

  rm3_copy(vecs, vs);
  rv3_sort3(v, vecs, NULL);

  return nt ? vecs : rm3_trans(vecs);
}


/* SVD decomposition of a 3x3 matrix A = U S V^T */
INLINE void fm3_svd(float a[3][3], float u[3][3], float s[3], float v[3][3])
{
  int i, rank;
  float ata[3][3], us[3][3];

  /* A^T A = V S^2 V^T, so (A^T A) V = V S^2 */

  /* 1. compute A^T A and its eigenvectors, which is V */
  fm3_tmul(ata, a, a);
  fm3_eigsys(s, v, ata, 1);

  /* 2. U^T = S^{-1} V^T A^T, and each row of U^T is an eigenvector
   * since eigenvectors are to be normalized, S^{-1} is unnecessary */
  if (s[0] <= 0.0) {
    rank = 0;
    fm3_copy(u, v);
  } else {
    double tol = 10. * sqrt(DBL_EPSILON);
    /* the test i = 1 + (s[1] > s[0]*tol) + (s[2] > s[0]*tol); */
    fm3_mult(u, v, a);
    for (i = 0; i < 3; i++) {
      fv3_copy(us[i], u[i]); /* save a copy of V^T A^T before normalizing it */
      s[i] = fv3_norm(u[i]);
      if (s[i] > 0) fv3_smul(u[i], 1/s[i]);
    }
    rank = 1;
    rank += (fabs(fv3_dot(u[0], u[1])) < tol && s[1] > tol);
    rank += (fabs(fv3_dot(u[0], u[2])) < tol && fabs(fv3_dot(u[1], u[2])) < tol && s[2] > tol);
    if (rank <= 2) {
      if (rank == 1) {
        float z[3] = {0, 0, 0}, w, tmp;

        w = (float) fabs(u[0][i = 0]);
        if ((tmp = (float) fabs(u[0][1])) < w) w = tmp, i = 1;
        if ((tmp = (float) fabs(u[0][2])) < w) i = 2;
        z[i] = 1.0f; /* select the smallest element in u[0] as z */
        fv3_normalize( fv3_cross(u[1], z, u[0]) );
        s[1] = fv3_dot(u[1], us[1]); /* S = U^T (V^T A^T)^T is more accurate than sqrt(A^T A) */
        if (s[1] < 0) { s[1] = -s[1]; fv3_neg(u[1]); } /* make sure s[1] > 0 */
      }
      fv3_normalize( fv3_cross(u[2], u[0], u[1]) );
      s[2] = fv3_dot(u[2], us[2]);
      if (s[2] < 0) { s[2] = -s[2]; fv3_neg(u[2]); }
    }
    fv3_sort3(s, u, v);
  }
  fm3_trans(v);
  fm3_trans(u);
}

/* SVD decomposition of a 3x3 matrix A = U S V^T */
INLINE void dm3_svd(double a[3][3], double u[3][3], double s[3], double v[3][3])
{
  int i, rank;
  double ata[3][3], us[3][3];

  /* A^T A = V S^2 V^T, so (A^T A) V = V S^2 */

  /* 1. compute A^T A and its eigenvectors, which is V */
  dm3_tmul(ata, a, a);
  dm3_eigsys(s, v, ata, 1);

  /* 2. U^T = S^{-1} V^T A^T, and each row of U^T is an eigenvector
   * since eigenvectors are to be normalized, S^{-1} is unnecessary */
  if (s[0] <= 0.0) {
    rank = 0;
    dm3_copy(u, v);
  } else {
    double tol = 10. * sqrt(DBL_EPSILON);
    /* the test i = 1 + (s[1] > s[0]*tol) + (s[2] > s[0]*tol); */
    dm3_mult(u, v, a);
    for (i = 0; i < 3; i++) {
      dv3_copy(us[i], u[i]); /* save a copy of V^T A^T before normalizing it */
      s[i] = dv3_norm(u[i]);
      if (s[i] > 0) dv3_smul(u[i], 1/s[i]);
    }
    rank = 1;
    rank += (fabs(dv3_dot(u[0], u[1])) < tol && s[1] > tol);
    rank += (fabs(dv3_dot(u[0], u[2])) < tol && fabs(dv3_dot(u[1], u[2])) < tol && s[2] > tol);
    if (rank <= 2) {
      if (rank == 1) {
        double z[3] = {0, 0, 0}, w, tmp;

        w = (double) fabs(u[0][i = 0]);
        if ((tmp = (double) fabs(u[0][1])) < w) w = tmp, i = 1;
        if ((tmp = (double) fabs(u[0][2])) < w) i = 2;
        z[i] = 1.0f; /* select the smallest element in u[0] as z */
        dv3_normalize( dv3_cross(u[1], z, u[0]) );
        s[1] = dv3_dot(u[1], us[1]); /* S = U^T (V^T A^T)^T is more accurate than sqrt(A^T A) */
        if (s[1] < 0) { s[1] = -s[1]; dv3_neg(u[1]); } /* make sure s[1] > 0 */
      }
      dv3_normalize( dv3_cross(u[2], u[0], u[1]) );
      s[2] = dv3_dot(u[2], us[2]);
      if (s[2] < 0) { s[2] = -s[2]; dv3_neg(u[2]); }
    }
    dv3_sort3(s, u, v);
  }
  dm3_trans(v);
  dm3_trans(u);
}

/* SVD decomposition of a 3x3 matrix A = U S V^T */
INLINE void rm3_svd(real a[3][3], real u[3][3], real s[3], real v[3][3])
{
  int i, rank;
  real ata[3][3], us[3][3];

  /* A^T A = V S^2 V^T, so (A^T A) V = V S^2 */

  /* 1. compute A^T A and its eigenvectors, which is V */
  rm3_tmul(ata, a, a);
  rm3_eigsys(s, v, ata, 1);

  /* 2. U^T = S^{-1} V^T A^T, and each row of U^T is an eigenvector
   * since eigenvectors are to be normalized, S^{-1} is unnecessary */
  if (s[0] <= 0.0) {
    rank = 0;
    rm3_copy(u, v);
  } else {
    double tol = 10. * sqrt(DBL_EPSILON);
    /* the test i = 1 + (s[1] > s[0]*tol) + (s[2] > s[0]*tol); */
    rm3_mult(u, v, a);
    for (i = 0; i < 3; i++) {
      rv3_copy(us[i], u[i]); /* save a copy of V^T A^T before normalizing it */
      s[i] = rv3_norm(u[i]);
      if (s[i] > 0) rv3_smul(u[i], 1/s[i]);
    }
    rank = 1;
    rank += (fabs(rv3_dot(u[0], u[1])) < tol && s[1] > tol);
    rank += (fabs(rv3_dot(u[0], u[2])) < tol && fabs(rv3_dot(u[1], u[2])) < tol && s[2] > tol);
    if (rank <= 2) {
      if (rank == 1) {
        real z[3] = {0, 0, 0}, w, tmp;

        w = (real) fabs(u[0][i = 0]);
        if ((tmp = (real) fabs(u[0][1])) < w) w = tmp, i = 1;
        if ((tmp = (real) fabs(u[0][2])) < w) i = 2;
        z[i] = 1.0f; /* select the smallest element in u[0] as z */
        rv3_normalize( rv3_cross(u[1], z, u[0]) );
        s[1] = rv3_dot(u[1], us[1]); /* S = U^T (V^T A^T)^T is more accurate than sqrt(A^T A) */
        if (s[1] < 0) { s[1] = -s[1]; rv3_neg(u[1]); } /* make sure s[1] > 0 */
      }
      rv3_normalize( rv3_cross(u[2], u[0], u[1]) );
      s[2] = rv3_dot(u[2], us[2]);
      if (s[2] < 0) { s[2] = -s[2]; rv3_neg(u[2]); }
    }
    rv3_sort3(s, u, v);
  }
  rm3_trans(v);
  rm3_trans(u);
}


/* an old alias */
#define rotfit3 rv3_rmsd

/* Fit x to y by rotation and translation of the `x'
 * If `refl', reflection can also be used.
 * The best-fit structure is saved to `xf', if not NULL */
INLINE float fv3_rmsd(fv3_t * RESTRICT x, fv3_t * RESTRICT xf,
    fv3_t * RESTRICT y, const float *w, int n, int refl,
    float (* RESTRICT r)[3], float * RESTRICT t)
{
  int i;
  float wtot = 0, sq, dev = 0, dev0, detm;
  fv3_t xc, yc, xs, ys, sig, t_;
  float u[3][3], v[3][3], s[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, xy[3][3], r_[3][3];

  if (r == NULL) r = r_;
  if (t == NULL) t = t_;

  /* 1. compute the centers */
  fv3_zero(xc);
  fv3_zero(yc);
  if (w == NULL) {
    for (i = 0; i < n; i++) {
      fv3_inc(xc, x[i]);
      fv3_inc(yc, y[i]);
    }
    wtot = (float) n;
  } else {
    for (wtot = 0., i = 0; i < n; i++) {
      fv3_sinc(xc, x[i], w[i]);
      fv3_sinc(yc, y[i], w[i]);
      wtot += w[i];
    }
  }
  fv3_smul(xc, 1.f/wtot);
  fv3_smul(yc, 1.f/wtot);

  /* 2. compute 3x3 asymmetric covariance matrix S = (x-xc) (y-yc)^T */
  for (i = 0; i < n; i++) {
    fv3_diff(xs, x[i], xc); /* shift to the center avoid the translation */
    fv3_diff(ys, y[i], yc);
    fm3_vtv(xy, xs, ys);
    sq  = fv3_sqr(xs);
    sq += fv3_sqr(ys);
    if (w) {
      fm3_sinc(s, xy, w[i]);
      dev += w[i]*sq;
    } else {
      fm3_inc(s, xy);
      dev += sq; /* Tr(x^T x + y^T y) */
    }
  }
  dev0 = dev;

  /* 3. SVD decompose S = u sig v^T */
  fm3_svd(s, u, sig, v);

  /* 4. compute R = v u^T */
  fm3_mult(r, v, u);
  detm = fm3_det(r);

#define rmsd_dump_(title) { const char *rfmt = "%22.14f"; \
    printf("rmsd [" title "], fatal error: detm = %g, n = %d\n", detm, n); \
    fm3_print(s, "s = (x - xc) (y - yc)^T", rfmt, 1); \
    printf("det(s) = %g\n", fm3_det(s)); \
    fm3_print(u, "u", rfmt, 1); \
    printf("det(u) = %g\n", fm3_det(u)); \
    fm3_print(v, "v", rfmt, 1); \
    printf("det(v) = %g\n", fm3_det(v)); \
    fv3_print(sig, "sig", rfmt, 1); \
    fm3_print(r, "r = v.u (rotation matrix)", rfmt, 1); \
    printf("det(r) = %g\n", fm3_det(r)); \
    fm3_mult(r, u, v); fm3_print(r, "r' = u.v", rfmt, 1); \
    printf("det(r') = %g\n", fm3_det(r)); \
    exit(1); }
  if (fabs(fabs(detm) - 1) > 0.01) {
    fprintf(stderr, "detm: %g\n", detm);
    rmsd_dump_("bad svd");
  }
  if (detm < 0 && !refl) { /* to avoid a reflection */
    fm3_trans(u);
    fv3_neg(u[2]); /* flip the last eigenvector */
    fm3_mul(r, v, u);
    dev -= 2*(sig[0] + sig[1] - sig[2]);
    detm = fm3_det(r);
    if (fabs(fabs(detm) - 1) > 0.01) rmsd_dump_("bad inv.");
#undef rmsd_dump_
  } else {
    dev -= 2 * (sig[0] + sig[1] + sig[2]); /* -2 Tr(R x y^T) */
  }
  if (dev < 0) dev = 0;
  fv3_diff(t, yc, fm3_mulvec(xs, r, xc)); /* t = yc - R xc */

  /* 5. compute the rotated structure */
  if (xf || dev < dev0*0.01) { /* if there's a large cancellation recompute the deviation */
    float xfi[3];

    for (dev = 0, i = 0; i < n; i++) {
      fv3_add(xfi, fm3_mulvec(xs, r, x[i]), t); /* xfi = R x + t */
      sq = fv3_dist2(y[i], xfi);
      if (xf) fv3_copy(xf[i], xfi);
      dev +=  (w ? w[i]*sq : sq); /* recompute the deviation */
    }
  }
  return (float) sqrt(dev/wtot);
}

/* Fit x to y by rotation and translation of the `x'
 * If `refl', reflection can also be used.
 * The best-fit structure is saved to `xf', if not NULL */
INLINE double dv3_rmsd(dv3_t * RESTRICT x, dv3_t * RESTRICT xf,
    dv3_t * RESTRICT y, const double *w, int n, int refl,
    double (* RESTRICT r)[3], double * RESTRICT t)
{
  int i;
  double wtot = 0, sq, dev = 0, dev0, detm;
  dv3_t xc, yc, xs, ys, sig, t_;
  double u[3][3], v[3][3], s[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, xy[3][3], r_[3][3];

  if (r == NULL) r = r_;
  if (t == NULL) t = t_;

  /* 1. compute the centers */
  dv3_zero(xc);
  dv3_zero(yc);
  if (w == NULL) {
    for (i = 0; i < n; i++) {
      dv3_inc(xc, x[i]);
      dv3_inc(yc, y[i]);
    }
    wtot = (double) n;
  } else {
    for (wtot = 0., i = 0; i < n; i++) {
      dv3_sinc(xc, x[i], w[i]);
      dv3_sinc(yc, y[i], w[i]);
      wtot += w[i];
    }
  }
  dv3_smul(xc, 1.f/wtot);
  dv3_smul(yc, 1.f/wtot);

  /* 2. compute 3x3 asymmetric covariance matrix S = (x-xc) (y-yc)^T */
  for (i = 0; i < n; i++) {
    dv3_diff(xs, x[i], xc); /* shift to the center avoid the translation */
    dv3_diff(ys, y[i], yc);
    dm3_vtv(xy, xs, ys);
    sq  = dv3_sqr(xs);
    sq += dv3_sqr(ys);
    if (w) {
      dm3_sinc(s, xy, w[i]);
      dev += w[i]*sq;
    } else {
      dm3_inc(s, xy);
      dev += sq; /* Tr(x^T x + y^T y) */
    }
  }
  dev0 = dev;

  /* 3. SVD decompose S = u sig v^T */
  dm3_svd(s, u, sig, v);

  /* 4. compute R = v u^T */
  dm3_mult(r, v, u);
  detm = dm3_det(r);

#define rmsd_dump_(title) { const char *rfmt = "%22.14f"; \
    printf("rmsd [" title "], fatal error: detm = %g, n = %d\n", detm, n); \
    dm3_print(s, "s = (x - xc) (y - yc)^T", rfmt, 1); \
    printf("det(s) = %g\n", dm3_det(s)); \
    dm3_print(u, "u", rfmt, 1); \
    printf("det(u) = %g\n", dm3_det(u)); \
    dm3_print(v, "v", rfmt, 1); \
    printf("det(v) = %g\n", dm3_det(v)); \
    dv3_print(sig, "sig", rfmt, 1); \
    dm3_print(r, "r = v.u (rotation matrix)", rfmt, 1); \
    printf("det(r) = %g\n", dm3_det(r)); \
    dm3_mult(r, u, v); dm3_print(r, "r' = u.v", rfmt, 1); \
    printf("det(r') = %g\n", dm3_det(r)); \
    exit(1); }
  if (fabs(fabs(detm) - 1) > 0.01) {
    fprintf(stderr, "detm: %g\n", detm);
    rmsd_dump_("bad svd");
  }
  if (detm < 0 && !refl) { /* to avoid a reflection */
    dm3_trans(u);
    dv3_neg(u[2]); /* flip the last eigenvector */
    dm3_mul(r, v, u);
    dev -= 2*(sig[0] + sig[1] - sig[2]);
    detm = dm3_det(r);
    if (fabs(fabs(detm) - 1) > 0.01) rmsd_dump_("bad inv.");
#undef rmsd_dump_
  } else {
    dev -= 2 * (sig[0] + sig[1] + sig[2]); /* -2 Tr(R x y^T) */
  }
  if (dev < 0) dev = 0;
  dv3_diff(t, yc, dm3_mulvec(xs, r, xc)); /* t = yc - R xc */

  /* 5. compute the rotated structure */
  if (xf || dev < dev0*0.01) { /* if there's a large cancellation recompute the deviation */
    double xfi[3];

    for (dev = 0, i = 0; i < n; i++) {
      dv3_add(xfi, dm3_mulvec(xs, r, x[i]), t); /* xfi = R x + t */
      sq = dv3_dist2(y[i], xfi);
      if (xf) dv3_copy(xf[i], xfi);
      dev +=  (w ? w[i]*sq : sq); /* recompute the deviation */
    }
  }
  return (double) sqrt(dev/wtot);
}

/* Fit x to y by rotation and translation of the `x'
 * If `refl', reflection can also be used.
 * The best-fit structure is saved to `xf', if not NULL */
INLINE real rv3_rmsd(rv3_t * RESTRICT x, rv3_t * RESTRICT xf,
    rv3_t * RESTRICT y, const real *w, int n, int refl,
    real (* RESTRICT r)[3], real * RESTRICT t)
{
  int i;
  real wtot = 0, sq, dev = 0, dev0, detm;
  rv3_t xc, yc, xs, ys, sig, t_;
  real u[3][3], v[3][3], s[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, xy[3][3], r_[3][3];

  if (r == NULL) r = r_;
  if (t == NULL) t = t_;

  /* 1. compute the centers */
  rv3_zero(xc);
  rv3_zero(yc);
  if (w == NULL) {
    for (i = 0; i < n; i++) {
      rv3_inc(xc, x[i]);
      rv3_inc(yc, y[i]);
    }
    wtot = (real) n;
  } else {
    for (wtot = 0., i = 0; i < n; i++) {
      rv3_sinc(xc, x[i], w[i]);
      rv3_sinc(yc, y[i], w[i]);
      wtot += w[i];
    }
  }
  rv3_smul(xc, 1.f/wtot);
  rv3_smul(yc, 1.f/wtot);

  /* 2. compute 3x3 asymmetric covariance matrix S = (x-xc) (y-yc)^T */
  for (i = 0; i < n; i++) {
    rv3_diff(xs, x[i], xc); /* shift to the center avoid the translation */
    rv3_diff(ys, y[i], yc);
    rm3_vtv(xy, xs, ys);
    sq  = rv3_sqr(xs);
    sq += rv3_sqr(ys);
    if (w) {
      rm3_sinc(s, xy, w[i]);
      dev += w[i]*sq;
    } else {
      rm3_inc(s, xy);
      dev += sq; /* Tr(x^T x + y^T y) */
    }
  }
  dev0 = dev;

  /* 3. SVD decompose S = u sig v^T */
  rm3_svd(s, u, sig, v);

  /* 4. compute R = v u^T */
  rm3_mult(r, v, u);
  detm = rm3_det(r);

#define rmsd_dump_(title) { const char *rfmt = "%22.14f"; \
    printf("rmsd [" title "], fatal error: detm = %g, n = %d\n", detm, n); \
    rm3_print(s, "s = (x - xc) (y - yc)^T", rfmt, 1); \
    printf("det(s) = %g\n", rm3_det(s)); \
    rm3_print(u, "u", rfmt, 1); \
    printf("det(u) = %g\n", rm3_det(u)); \
    rm3_print(v, "v", rfmt, 1); \
    printf("det(v) = %g\n", rm3_det(v)); \
    rv3_print(sig, "sig", rfmt, 1); \
    rm3_print(r, "r = v.u (rotation matrix)", rfmt, 1); \
    printf("det(r) = %g\n", rm3_det(r)); \
    rm3_mult(r, u, v); rm3_print(r, "r' = u.v", rfmt, 1); \
    printf("det(r') = %g\n", rm3_det(r)); \
    exit(1); }
  if (fabs(fabs(detm) - 1) > 0.01) {
    fprintf(stderr, "detm: %g\n", detm);
    rmsd_dump_("bad svd");
  }
  if (detm < 0 && !refl) { /* to avoid a reflection */
    rm3_trans(u);
    rv3_neg(u[2]); /* flip the last eigenvector */
    rm3_mul(r, v, u);
    dev -= 2*(sig[0] + sig[1] - sig[2]);
    detm = rm3_det(r);
    if (fabs(fabs(detm) - 1) > 0.01) rmsd_dump_("bad inv.");
#undef rmsd_dump_
  } else {
    dev -= 2 * (sig[0] + sig[1] + sig[2]); /* -2 Tr(R x y^T) */
  }
  if (dev < 0) dev = 0;
  rv3_diff(t, yc, rm3_mulvec(xs, r, xc)); /* t = yc - R xc */

  /* 5. compute the rotated structure */
  if (xf || dev < dev0*0.01) { /* if there's a large cancellation recompute the deviation */
    real xfi[3];

    for (dev = 0, i = 0; i < n; i++) {
      rv3_add(xfi, rm3_mulvec(xs, r, x[i]), t); /* xfi = R x + t */
      sq = rv3_dist2(y[i], xfi);
      if (xf) rv3_copy(xf[i], xfi);
      dev +=  (w ? w[i]*sq : sq); /* recompute the deviation */
    }
  }
  return (real) sqrt(dev/wtot);
}


/* generate a random orthonormal (unitary) 3x3 matrix */
INLINE fv3_t *fm3_randuni(float a[3][3])
{
  float dot;

  fv3_randdir0(a[0]);

  fv3_randunif(a[1], -1, 1);
  /* component of a[1] normal to a[0] */
  dot = fv3_dot(a[0], a[1]);
  fv3_normalize( fv3_sinc(a[1], a[0], -dot) );

  fv3_cross(a[2], a[0], a[1]);
  return a;
}

/* generate a random orthonormal (unitary) 3x3 matrix */
INLINE dv3_t *dm3_randuni(double a[3][3])
{
  double dot;

  dv3_randdir0(a[0]);

  dv3_randunif(a[1], -1, 1);
  /* component of a[1] normal to a[0] */
  dot = dv3_dot(a[0], a[1]);
  dv3_normalize( dv3_sinc(a[1], a[0], -dot) );

  dv3_cross(a[2], a[0], a[1]);
  return a;
}

/* generate a random orthonormal (unitary) 3x3 matrix */
INLINE rv3_t *rm3_randuni(real a[3][3])
{
  real dot;

  rv3_randdir0(a[0]);

  rv3_randunif(a[1], -1, 1);
  /* component of a[1] normal to a[0] */
  dot = rv3_dot(a[0], a[1]);
  rv3_normalize( rv3_sinc(a[1], a[0], -dot) );

  rv3_cross(a[2], a[0], a[1]);
  return a;
}


#endif /* ZCOM_RV3__ */
#endif /* ZCOM_RV3 */





#ifdef  ZCOM_RVN
#ifndef ZCOM_RVN__
#define ZCOM_RVN__
/* D-dimensional real vector */


#ifndef D
#define D 3
#endif


#ifndef DM /* aligned array dimension */
#ifdef RVN_ALIGN
/* double arrays of multiples of 4 can use -xhost options in Intel C
 * and avoid possible compiler optimization mistakes */
#define DM ((D + (RVN_ALIGN) - 1) / (RVN_ALIGN) * (RVN_ALIGN))
#else
/* by default, we set D == DM */
#define DM D
#endif
#endif


#ifndef FVN_T
#define FVN_T fvn_t
typedef float fvn_t[DM];
#endif

#ifndef DVN_T
#define DVN_T dvn_t
typedef double dvn_t[DM];
#endif

#ifndef RVN_T
#define RVN_T rvn_t
typedef real rvn_t[DM];
#endif


#define fvn_print(r, nm, fmt, nl) fvn_fprint(stdout, r, nm, fmt, nl)

#define dvn_print(r, nm, fmt, nl) dvn_fprint(stdout, r, nm, fmt, nl)

#define rvn_print(r, nm, fmt, nl) rvn_fprint(stdout, r, nm, fmt, nl)

INLINE void fvn_fprint(FILE *fp, const float *r, const char *nm,
    const char *fmt, int nl)
{
  int i;
  if (nm) fprintf(fp, "%s: ", nm);
  for (i = 0; i < D; i++)
    fprintf(fp, fmt, r[i], nl);
  fprintf(fp, "%c", (nl ? '\n' : ';'));
}

INLINE void dvn_fprint(FILE *fp, const double *r, const char *nm,
    const char *fmt, int nl)
{
  int i;
  if (nm) fprintf(fp, "%s: ", nm);
  for (i = 0; i < D; i++)
    fprintf(fp, fmt, r[i], nl);
  fprintf(fp, "%c", (nl ? '\n' : ';'));
}

INLINE void rvn_fprint(FILE *fp, const real *r, const char *nm,
    const char *fmt, int nl)
{
  int i;
  if (nm) fprintf(fp, "%s: ", nm);
  for (i = 0; i < D; i++)
    fprintf(fp, fmt, r[i], nl);
  fprintf(fp, "%c", (nl ? '\n' : ';'));
}


INLINE float *fvn_make(float *x, ...)
{
  int i;
  va_list vl;

  va_start(vl, x);
  for (i = 0; i < D; i++)
    x[i] = (float) va_arg(vl, double);
#if D < DM
  for (i = D; i < DM; i++) x[i] = (float) 0;
#endif
  va_end(vl);
  return x;
}

INLINE double *dvn_make(double *x, ...)
{
  int i;
  va_list vl;

  va_start(vl, x);
  for (i = 0; i < D; i++)
    x[i] = (double) va_arg(vl, double);
#if D < DM
  for (i = D; i < DM; i++) x[i] = (double) 0;
#endif
  va_end(vl);
  return x;
}

INLINE real *rvn_make(real *x, ...)
{
  int i;
  va_list vl;

  va_start(vl, x);
  for (i = 0; i < D; i++)
    x[i] = (real) va_arg(vl, double);
#if D < DM
  for (i = D; i < DM; i++) x[i] = (real) 0;
#endif
  va_end(vl);
  return x;
}


INLINE float *fvn_zero(float *x)
{
  int i;

  /* clear all the way up to DM */
  for (i = 0; i < DM; i++) x[i] = 0;
  return x;
}

INLINE double *dvn_zero(double *x)
{
  int i;

  /* clear all the way up to DM */
  for (i = 0; i < DM; i++) x[i] = 0;
  return x;
}

INLINE real *rvn_zero(real *x)
{
  int i;

  /* clear all the way up to DM */
  for (i = 0; i < DM; i++) x[i] = 0;
  return x;
}


INLINE float *fvn_copy(float *x, const float *src)
{
  int i;

  for (i = 0; i < DM; i++)
    x[i] = src[i];
  return x;
}

INLINE double *dvn_copy(double *x, const double *src)
{
  int i;

  for (i = 0; i < DM; i++)
    x[i] = src[i];
  return x;
}

INLINE real *rvn_copy(real *x, const real *src)
{
  int i;

  for (i = 0; i < DM; i++)
    x[i] = src[i];
  return x;
}


/* use macro to avoid const qualifier of src */
#define fvn_ncopy(x, src, n) memcpy(x, src, D*n*sizeof(float))

/* use macro to avoid const qualifier of src */
#define dvn_ncopy(x, src, n) memcpy(x, src, D*n*sizeof(double))

/* use macro to avoid const qualifier of src */
#define rvn_ncopy(x, src, n) memcpy(x, src, D*n*sizeof(real))


INLINE void fvn_swap(float * RESTRICT x, float * RESTRICT y)
{
  fvn_t z;
  fvn_copy(z, x);
  fvn_copy(x, y);
  fvn_copy(y, z);
}

INLINE void dvn_swap(double * RESTRICT x, double * RESTRICT y)
{
  dvn_t z;
  dvn_copy(z, x);
  dvn_copy(x, y);
  dvn_copy(y, z);
}

INLINE void rvn_swap(real * RESTRICT x, real * RESTRICT y)
{
  rvn_t z;
  rvn_copy(z, x);
  rvn_copy(x, y);
  rvn_copy(y, z);
}


#define fvn_sqr(x) fvn_dot(x, x)

#define dvn_sqr(x) dvn_dot(x, x)

#define fvn_sqr(x) fvn_dot(x, x)
#define fvn_norm(x) (float) sqrt(fvn_sqr(x))

#define dvn_sqr(x) dvn_dot(x, x)
#define dvn_norm(x) (double) sqrt(dvn_sqr(x))

#define rvn_sqr(x) rvn_dot(x, x)
#define rvn_norm(x) (real) sqrt(rvn_sqr(x))

#if DM == 2
#define fvn_dot(x, y) fv2_dot(x, y)
#elif DM == 3
#define fvn_dot(x, y) fv3_dot(x, y)
#else
INLINE float fvn_dot(const float *x, const float *y)
{
  int i;
  float dot = 0;

  /* assuming x[i], y[i] == 0 for i >= D */
  for (i = 0; i < DM; i++) dot += x[i] * y[i];
  return dot;
}
#endif

#if DM == 2
#define dvn_dot(x, y) dv2_dot(x, y)
#elif DM == 3
#define dvn_dot(x, y) dv3_dot(x, y)
#else
INLINE double dvn_dot(const double *x, const double *y)
{
  int i;
  double dot = 0;

  /* assuming x[i], y[i] == 0 for i >= D */
  for (i = 0; i < DM; i++) dot += x[i] * y[i];
  return dot;
}
#endif

#if DM == 2
#define rvn_dot(x, y) rv2_dot(x, y)
#elif DM == 3
#define rvn_dot(x, y) rv3_dot(x, y)
#else
INLINE real rvn_dot(const real *x, const real *y)
{
  int i;
  real dot = 0;

  /* assuming x[i], y[i] == 0 for i >= D */
  for (i = 0; i < DM; i++) dot += x[i] * y[i];
  return dot;
}
#endif


INLINE float *fvn_neg(float * RESTRICT x)
{
  int i;

  /* assuming x[i] == 0 for i >= D */
  for (i = 0; i < DM; i++) x[i] = -x[i];
  return x;
}

INLINE double *dvn_neg(double * RESTRICT x)
{
  int i;

  /* assuming x[i] == 0 for i >= D */
  for (i = 0; i < DM; i++) x[i] = -x[i];
  return x;
}

INLINE real *rvn_neg(real * RESTRICT x)
{
  int i;

  /* assuming x[i] == 0 for i >= D */
  for (i = 0; i < DM; i++) x[i] = -x[i];
  return x;
}


INLINE float *fvn_neg2(float * RESTRICT nx, const float *x)
{
  int i;

  /* assuming x[i] == 0 for i >= D */
  for (i = 0; i < DM; i++) nx[i] = -x[i];
  return nx;
}

INLINE double *dvn_neg2(double * RESTRICT nx, const double *x)
{
  int i;

  /* assuming x[i] == 0 for i >= D */
  for (i = 0; i < DM; i++) nx[i] = -x[i];
  return nx;
}

INLINE real *rvn_neg2(real * RESTRICT nx, const real *x)
{
  int i;

  /* assuming x[i] == 0 for i >= D */
  for (i = 0; i < DM; i++) nx[i] = -x[i];
  return nx;
}


INLINE float *fvn_inc(float * RESTRICT x, const float *dx)
{
  int i;

  /* assuming dx[i] == 0 for i >= D */
  for (i = 0; i < DM; i++) x[i] += dx[i];
  return x;
}

INLINE double *dvn_inc(double * RESTRICT x, const double *dx)
{
  int i;

  /* assuming dx[i] == 0 for i >= D */
  for (i = 0; i < DM; i++) x[i] += dx[i];
  return x;
}

INLINE real *rvn_inc(real * RESTRICT x, const real *dx)
{
  int i;

  /* assuming dx[i] == 0 for i >= D */
  for (i = 0; i < DM; i++) x[i] += dx[i];
  return x;
}


INLINE float *fvn_dec(float * RESTRICT x, const float *dx)
{
  int i;

  /* assuming dx[i] == 0 for i >= D */
  for (i = 0; i < DM; i++) x[i] -= dx[i];
  return x;
}

INLINE double *dvn_dec(double * RESTRICT x, const double *dx)
{
  int i;

  /* assuming dx[i] == 0 for i >= D */
  for (i = 0; i < DM; i++) x[i] -= dx[i];
  return x;
}

INLINE real *rvn_dec(real * RESTRICT x, const real *dx)
{
  int i;

  /* assuming dx[i] == 0 for i >= D */
  for (i = 0; i < DM; i++) x[i] -= dx[i];
  return x;
}


INLINE float *fvn_sinc(float * RESTRICT x, const float *dx, float s)
{
  int i;

  /* assuming dx[i] == 0 for i >= D */
  for (i = 0; i < DM; i++) x[i] += s * dx[i];
  return x;
}

INLINE double *dvn_sinc(double * RESTRICT x, const double *dx, double s)
{
  int i;

  /* assuming dx[i] == 0 for i >= D */
  for (i = 0; i < DM; i++) x[i] += s * dx[i];
  return x;
}

INLINE real *rvn_sinc(real * RESTRICT x, const real *dx, real s)
{
  int i;

  /* assuming dx[i] == 0 for i >= D */
  for (i = 0; i < DM; i++) x[i] += s * dx[i];
  return x;
}


INLINE float *fvn_smul(float *x, float s)
{
  int i;

  for (i = 0; i < DM; i++) x[i] *= s;
  return x;
}

INLINE double *dvn_smul(double *x, double s)
{
  int i;

  for (i = 0; i < DM; i++) x[i] *= s;
  return x;
}

INLINE real *rvn_smul(real *x, real s)
{
  int i;

  for (i = 0; i < DM; i++) x[i] *= s;
  return x;
}


INLINE float *fvn_smul2(float * RESTRICT y, const float *x, float s)
{
  int i;

  /* assuming x[i] == 0 for i >= D */
  for (i = 0; i < DM; i++) y[i] = x[i] * s;
  return y;
}

INLINE double *dvn_smul2(double * RESTRICT y, const double *x, double s)
{
  int i;

  /* assuming x[i] == 0 for i >= D */
  for (i = 0; i < DM; i++) y[i] = x[i] * s;
  return y;
}

INLINE real *rvn_smul2(real * RESTRICT y, const real *x, real s)
{
  int i;

  /* assuming x[i] == 0 for i >= D */
  for (i = 0; i < DM; i++) y[i] = x[i] * s;
  return y;
}


INLINE float *fvn_normalize(float *x)
{
  float r = fvn_norm(x);
  if (r > (float) 0) fvn_smul(x, (float) 1./r);
  return x;
}

INLINE double *dvn_normalize(double *x)
{
  double r = dvn_norm(x);
  if (r > (double) 0) dvn_smul(x, (double) 1./r);
  return x;
}

INLINE real *rvn_normalize(real *x)
{
  real r = rvn_norm(x);
  if (r > (real) 0) rvn_smul(x, (real) 1./r);
  return x;
}


INLINE float *fvn_makenorm(float *v, ...)
{
  int i;
  va_list vl;

  va_start(vl, v);
  for (i = 0; i < D; i++)
    v[i] = (float) va_arg(vl, double);
  va_end(vl);
#if D < DM
  for (i = D; i < DM; i++) v[i] = (float) 0;
#endif
  return fvn_normalize( v );
}

INLINE double *dvn_makenorm(double *v, ...)
{
  int i;
  va_list vl;

  va_start(vl, v);
  for (i = 0; i < D; i++)
    v[i] = (double) va_arg(vl, double);
  va_end(vl);
#if D < DM
  for (i = D; i < DM; i++) v[i] = (double) 0;
#endif
  return dvn_normalize( v );
}

INLINE real *rvn_makenorm(real *v, ...)
{
  int i;
  va_list vl;

  va_start(vl, v);
  for (i = 0; i < D; i++)
    v[i] = (real) va_arg(vl, double);
  va_end(vl);
#if D < DM
  for (i = D; i < DM; i++) v[i] = (real) 0;
#endif
  return rvn_normalize( v );
}


/* for in-place difference use fvn_dec */
INLINE float *fvn_diff(float * RESTRICT c, const float *a, const float *b)
{
  int i;

  /* assuming a[i] = b[i] = 0 for i >= D */
  for (i = 0; i < DM; i++) c[i] = a[i] - b[i];
  return c;
}

/* for in-place difference use dvn_dec */
INLINE double *dvn_diff(double * RESTRICT c, const double *a, const double *b)
{
  int i;

  /* assuming a[i] = b[i] = 0 for i >= D */
  for (i = 0; i < DM; i++) c[i] = a[i] - b[i];
  return c;
}

/* for in-place difference use rvn_dec */
INLINE real *rvn_diff(real * RESTRICT c, const real *a, const real *b)
{
  int i;

  /* assuming a[i] = b[i] = 0 for i >= D */
  for (i = 0; i < DM; i++) c[i] = a[i] - b[i];
  return c;
}


/* distance^2 between a and b */
#if DM == 2
#define fvn_dist2(a, b) fv2_dist2(a, b)
#elif DM == 3
#define fvn_dist2(a, b) fv3_dist2(a, b)
#else
INLINE float fvn_dist2(const float *a, const float *b)
{
  fvn_t d;
  return fvn_sqr(fvn_diff(d, a, b));
}
#endif

/* distance^2 between a and b */
#if DM == 2
#define dvn_dist2(a, b) dv2_dist2(a, b)
#elif DM == 3
#define dvn_dist2(a, b) dv3_dist2(a, b)
#else
INLINE double dvn_dist2(const double *a, const double *b)
{
  dvn_t d;
  return dvn_sqr(dvn_diff(d, a, b));
}
#endif

/* distance^2 between a and b */
#if DM == 2
#define rvn_dist2(a, b) rv2_dist2(a, b)
#elif DM == 3
#define rvn_dist2(a, b) rv3_dist2(a, b)
#else
INLINE real rvn_dist2(const real *a, const real *b)
{
  rvn_t d;
  return rvn_sqr(rvn_diff(d, a, b));
}
#endif


/* distance between a and b */
INLINE float fvn_dist(const float *a, const float *b)
{
  return (float) sqrt(fvn_dist2(a, b));
}

/* distance between a and b */
INLINE double dvn_dist(const double *a, const double *b)
{
  return (double) sqrt(dvn_dist2(a, b));
}

/* distance between a and b */
INLINE real rvn_dist(const real *a, const real *b)
{
  return (real) sqrt(rvn_dist2(a, b));
}


/* c = a + b, for in-place addition use fvn_inc */
INLINE float *fvn_add(float * RESTRICT c, const float *a, const float *b)
{
  int i;

  /* assuming a[i] = b[i] = 0 for i >= D */
  for (i = 0; i < DM; i++) c[i] = a[i] + b[i];
  return c;
}

/* c = a + b, for in-place addition use dvn_inc */
INLINE double *dvn_add(double * RESTRICT c, const double *a, const double *b)
{
  int i;

  /* assuming a[i] = b[i] = 0 for i >= D */
  for (i = 0; i < DM; i++) c[i] = a[i] + b[i];
  return c;
}

/* c = a + b, for in-place addition use rvn_inc */
INLINE real *rvn_add(real * RESTRICT c, const real *a, const real *b)
{
  int i;

  /* assuming a[i] = b[i] = 0 for i >= D */
  for (i = 0; i < DM; i++) c[i] = a[i] + b[i];
  return c;
}


/* c = - a - b */
INLINE float *fvn_nadd(float * RESTRICT c, const float *a, const float *b)
{
  int i;

  /* assuming a[i] = b[i] = 0 for i >= D */
  for (i = 0; i < DM; i++) c[i] = - a[i] - b[i];
  return c;
}

/* c = - a - b */
INLINE double *dvn_nadd(double * RESTRICT c, const double *a, const double *b)
{
  int i;

  /* assuming a[i] = b[i] = 0 for i >= D */
  for (i = 0; i < DM; i++) c[i] = - a[i] - b[i];
  return c;
}

/* c = - a - b */
INLINE real *rvn_nadd(real * RESTRICT c, const real *a, const real *b)
{
  int i;

  /* assuming a[i] = b[i] = 0 for i >= D */
  for (i = 0; i < DM; i++) c[i] = - a[i] - b[i];
  return c;
}


/* c = a + b * s */
INLINE float *fvn_sadd(float * RESTRICT c, const float *a, const float *b, float s)
{
  int i;

  /* assuming a[i] = b[i] = 0 for i >= D */
  for (i = 0; i < DM; i++) c[i] = a[i] + b[i] * s;
  return c;
}

/* c = a + b * s */
INLINE double *dvn_sadd(double * RESTRICT c, const double *a, const double *b, double s)
{
  int i;

  /* assuming a[i] = b[i] = 0 for i >= D */
  for (i = 0; i < DM; i++) c[i] = a[i] + b[i] * s;
  return c;
}

/* c = a + b * s */
INLINE real *rvn_sadd(real * RESTRICT c, const real *a, const real *b, real s)
{
  int i;

  /* assuming a[i] = b[i] = 0 for i >= D */
  for (i = 0; i < DM; i++) c[i] = a[i] + b[i] * s;
  return c;
}


/* c = a * s1 + b * s2 */
INLINE float *fvn_lincomb2(float * RESTRICT c, const float *a, const float *b, float s1, float s2)
{
  int i;

  /* assuming a[i] = b[i] = 0 for i >= D */
  for (i = 0; i < DM; i++) c[i] = a[i] * s1 + b[i] * s2;
  return c;
}

/* c = a * s1 + b * s2 */
INLINE double *dvn_lincomb2(double * RESTRICT c, const double *a, const double *b, double s1, double s2)
{
  int i;

  /* assuming a[i] = b[i] = 0 for i >= D */
  for (i = 0; i < DM; i++) c[i] = a[i] * s1 + b[i] * s2;
  return c;
}

/* c = a * s1 + b * s2 */
INLINE real *rvn_lincomb2(real * RESTRICT c, const real *a, const real *b, real s1, real s2)
{
  int i;

  /* assuming a[i] = b[i] = 0 for i >= D */
  for (i = 0; i < DM; i++) c[i] = a[i] * s1 + b[i] * s2;
  return c;
}


/* a = a * s + c */
INLINE float *fvn_fma(float *a, float s, float c)
{
  int i;

  for (i = 0; i < DM; i++) a[i] = a[i] * s + c;
  return a;
}

/* a = a * s + c */
INLINE double *dvn_fma(double *a, double s, double c)
{
  int i;

  for (i = 0; i < DM; i++) a[i] = a[i] * s + c;
  return a;
}

/* a = a * s + c */
INLINE real *rvn_fma(real *a, real s, real c)
{
  int i;

  for (i = 0; i < DM; i++) a[i] = a[i] * s + c;
  return a;
}


/* cosine of the angle of x1-x2-x3 */
INLINE float fvn_cosang(const float *x1, const float *x2, const float *x3,
    float *g1, float *g2, float *g3)
{
  fvn_t a, b;
  float ra, rb, dot;

  ra = fvn_norm(fvn_diff(a, x1, x2));
  fvn_smul(a, 1.f/ra);
  rb = fvn_norm(fvn_diff(b, x3, x2));
  fvn_smul(b, 1.f/rb);
  dot = fvn_dot(a, b);
  if (dot > 1) dot = 1; else if (dot < -1) dot = -1;
  if (g1) {
    fvn_lincomb2(g1, b, a, 1.f/ra, -dot/ra);
    fvn_lincomb2(g3, a, b, 1.f/rb, -dot/rb);
    fvn_nadd(g2, g1, g3);
  }
  return dot;
}

/* cosine of the angle of x1-x2-x3 */
INLINE double dvn_cosang(const double *x1, const double *x2, const double *x3,
    double *g1, double *g2, double *g3)
{
  dvn_t a, b;
  double ra, rb, dot;

  ra = dvn_norm(dvn_diff(a, x1, x2));
  dvn_smul(a, 1.f/ra);
  rb = dvn_norm(dvn_diff(b, x3, x2));
  dvn_smul(b, 1.f/rb);
  dot = dvn_dot(a, b);
  if (dot > 1) dot = 1; else if (dot < -1) dot = -1;
  if (g1) {
    dvn_lincomb2(g1, b, a, 1.f/ra, -dot/ra);
    dvn_lincomb2(g3, a, b, 1.f/rb, -dot/rb);
    dvn_nadd(g2, g1, g3);
  }
  return dot;
}

/* cosine of the angle of x1-x2-x3 */
INLINE real rvn_cosang(const real *x1, const real *x2, const real *x3,
    real *g1, real *g2, real *g3)
{
  rvn_t a, b;
  real ra, rb, dot;

  ra = rvn_norm(rvn_diff(a, x1, x2));
  rvn_smul(a, 1.f/ra);
  rb = rvn_norm(rvn_diff(b, x3, x2));
  rvn_smul(b, 1.f/rb);
  dot = rvn_dot(a, b);
  if (dot > 1) dot = 1; else if (dot < -1) dot = -1;
  if (g1) {
    rvn_lincomb2(g1, b, a, 1.f/ra, -dot/ra);
    rvn_lincomb2(g3, a, b, 1.f/rb, -dot/rb);
    rvn_nadd(g2, g1, g3);
  }
  return dot;
}


/* angle and gradients of x1-x2-x3 */
INLINE float fvn_ang(const float *x1, const float *x2, const float *x3,
    float * RESTRICT g1, float * RESTRICT g2, float * RESTRICT g3)
{
  float dot, sn;
  dot = fvn_cosang(x1, x2, x3, g1, g2, g3);
  sn = (float) sqrt(1 - dot*dot);
  if (sn > 1e-7) sn = -1/sn; else sn = 0.;
  if (g1) {
    fvn_smul(g1, sn);
    fvn_smul(g2, sn);
    fvn_smul(g3, sn);
  }
  return (float) acos(dot);
}

/* angle and gradients of x1-x2-x3 */
INLINE double dvn_ang(const double *x1, const double *x2, const double *x3,
    double * RESTRICT g1, double * RESTRICT g2, double * RESTRICT g3)
{
  double dot, sn;
  dot = dvn_cosang(x1, x2, x3, g1, g2, g3);
  sn = (double) sqrt(1 - dot*dot);
  if (sn > 1e-7) sn = -1/sn; else sn = 0.;
  if (g1) {
    dvn_smul(g1, sn);
    dvn_smul(g2, sn);
    dvn_smul(g3, sn);
  }
  return (double) acos(dot);
}

/* angle and gradients of x1-x2-x3 */
INLINE real rvn_ang(const real *x1, const real *x2, const real *x3,
    real * RESTRICT g1, real * RESTRICT g2, real * RESTRICT g3)
{
  real dot, sn;
  dot = rvn_cosang(x1, x2, x3, g1, g2, g3);
  sn = (real) sqrt(1 - dot*dot);
  if (sn > 1e-7) sn = -1/sn; else sn = 0.;
  if (g1) {
    rvn_smul(g1, sn);
    rvn_smul(g2, sn);
    rvn_smul(g3, sn);
  }
  return (real) acos(dot);
}


/* vertical distance from x to line a-b */
INLINE real rvn_vdist(const real *x, const real *a, const real *b)
{
  rvn_t nm, d;
  real dot;

  rvn_diff(d, x, a);
  rvn_normalize(rvn_diff(nm, a, b));
  dot = rvn_dot(d, nm);
  return rvn_norm(rvn_sinc(d, nm, -dot));
}


#define fvn_rnd0(v)           fvn_rand01(v)

#define dvn_rnd0(v)           dvn_rand01(v)

#define rvn_rnd0(v)           rvn_rand01(v)

#define fvn_rnd(v, a, b)      fvn_randunif(v)

#define dvn_rnd(v, a, b)      dvn_randunif(v)

#define rvn_rnd(v, a, b)      rvn_randunif(v)

/* uniformly distributed random vector in [a, b) */
#define fvn_randunif(v, a, b) fvn_fma(fvn_rand01(v), b - a, -a)

/* uniformly distributed random vector in [a, b) */
#define dvn_randunif(v, a, b) dvn_fma(dvn_rand01(v), b - a, -a)

/* uniformly distributed random vector in [a, b) */
#define rvn_randunif(v, a, b) rvn_fma(rvn_rand01(v), b - a, -a)

/* uniformly distributed random vector in [0, 1) */
INLINE float *fvn_rand01(float *v)
{
  int i;

  for (i = 0; i < D; i++)
    v[i] = (float) rand01();
#if D < DM
  for (i = D; i < DM; i++) v[i] = (float) 0;
#endif
  return v;
}

/* uniformly distributed random vector in [0, 1) */
INLINE double *dvn_rand01(double *v)
{
  int i;

  for (i = 0; i < D; i++)
    v[i] = (double) rand01();
#if D < DM
  for (i = D; i < DM; i++) v[i] = (double) 0;
#endif
  return v;
}

/* uniformly distributed random vector in [0, 1) */
INLINE real *rvn_rand01(real *v)
{
  int i;

  for (i = 0; i < D; i++)
    v[i] = (real) rand01();
#if D < DM
  for (i = D; i < DM; i++) v[i] = (real) 0;
#endif
  return v;
}


#if DM == 2
#define rvn_randdisp(x, x0, a) rv2_randdisp(x, x0, a)
#elif DM == 3
#define rvn_randdisp(x, x0, a) rv3_randdisp(x, x0, a)
#else
/* displace `x0' by a random vector in [-a, a)^D */
INLINE real *rvn_randdisp(real * RESTRICT x, const real *x0, real a)
{
  int i;

  for (i = 0; i < D; i++)
    x[i] = x0[i] + (real) randunif(-a, a);
#if D < DM
  for (i = D; i < DM; i++) x[i] = (real) 0;
#endif
  return x;
}
#endif


#define fvn_grand0(v)       fvn_randgaus(v)

#define dvn_grand0(v)       dvn_randgaus(v)

#define rvn_grand0(v)       rvn_randgaus(v)

#define fvn_grand(v, a, b)  fvn_fma(fvn_randgaus(v), b - a, -a)

#define dvn_grand(v, a, b)  dvn_fma(dvn_randgaus(v), b - a, -a)

#define rvn_grand(v, a, b)  rvn_fma(rvn_randgaus(v), b - a, -a)


/* normally distributed random vector */
INLINE float *fvn_randgaus(float *v)
{
  int i;

  for (i = 0; i < D; i++)
    v[i] = (float) randgaus();
#if D < DM
  for (i = D; i < DM; i++) v[i] = (float) 0;
#endif
  return v;
}

/* normally distributed random vector */
INLINE double *dvn_randgaus(double *v)
{
  int i;

  for (i = 0; i < D; i++)
    v[i] = (double) randgaus();
#if D < DM
  for (i = D; i < DM; i++) v[i] = (double) 0;
#endif
  return v;
}

/* normally distributed random vector */
INLINE real *rvn_randgaus(real *v)
{
  int i;

  for (i = 0; i < D; i++)
    v[i] = (real) randgaus();
#if D < DM
  for (i = D; i < DM; i++) v[i] = (real) 0;
#endif
  return v;
}


/* displace `x0' by a normally-distributed random vector */
#if DM == 2
#define fvn_randgausdisp(x, x0, a) fv2_randgausdisp(x, x0, a)
#elif DM == 3
#define fvn_randgausdisp(x, x0, a) fv3_randgausdisp(x, x0, a)
#else
INLINE float *fvn_randgausdisp(float * RESTRICT x, const float *x0, float a)
{
  int i;

  for (i = 0; i < D; i++)
    x[i] = x0[i] + (float) randgaus() * a;
#if D < DM
  for (i = D; i < DM; i++) x[i] = (float) 0;
#endif
  return x;
}
#endif

/* displace `x0' by a normally-distributed random vector */
#if DM == 2
#define dvn_randgausdisp(x, x0, a) dv2_randgausdisp(x, x0, a)
#elif DM == 3
#define dvn_randgausdisp(x, x0, a) dv3_randgausdisp(x, x0, a)
#else
INLINE double *dvn_randgausdisp(double * RESTRICT x, const double *x0, double a)
{
  int i;

  for (i = 0; i < D; i++)
    x[i] = x0[i] + (double) randgaus() * a;
#if D < DM
  for (i = D; i < DM; i++) x[i] = (double) 0;
#endif
  return x;
}
#endif

/* displace `x0' by a normally-distributed random vector */
#if DM == 2
#define rvn_randgausdisp(x, x0, a) rv2_randgausdisp(x, x0, a)
#elif DM == 3
#define rvn_randgausdisp(x, x0, a) rv3_randgausdisp(x, x0, a)
#else
INLINE real *rvn_randgausdisp(real * RESTRICT x, const real *x0, real a)
{
  int i;

  for (i = 0; i < D; i++)
    x[i] = x0[i] + (real) randgaus() * a;
#if D < DM
  for (i = D; i < DM; i++) x[i] = (real) 0;
#endif
  return x;
}
#endif


/* randomly oriented vector on the sphere of radius r */
#define fvn_randdir(v, r) fvn_smul(fvn_randdir0(v), r)

/* randomly oriented vector on the sphere of radius r */
#define dvn_randdir(v, r) dvn_smul(dvn_randdir0(v), r)

/* randomly oriented vector on the sphere of radius r */
#define rvn_randdir(v, r) rvn_smul(rvn_randdir0(v), r)

/* randomly oriented vector on the unit sphere */
INLINE float *fvn_randdir0(float *v)
{
#if D < 5
  while ( fvn_sqr(fvn_randunif(v, -1, 1)) >= 1 ) ;
  return fvn_normalize(v);
#else
  /* if D >= 5, normal distribution is faster */
  return fvn_normalize( fvn_randgaus(v) );
#endif
}

/* randomly oriented vector on the unit sphere */
INLINE double *dvn_randdir0(double *v)
{
#if D < 5
  while ( dvn_sqr(dvn_randunif(v, -1, 1)) >= 1 ) ;
  return dvn_normalize(v);
#else
  /* if D >= 5, normal distribution is faster */
  return dvn_normalize( dvn_randgaus(v) );
#endif
}

/* randomly oriented vector on the unit sphere */
INLINE real *rvn_randdir0(real *v)
{
#if D < 5
  while ( rvn_sqr(rvn_randunif(v, -1, 1)) >= 1 ) ;
  return rvn_normalize(v);
#else
  /* if D >= 5, normal distribution is faster */
  return rvn_normalize( rvn_randgaus(v) );
#endif
}


/* randomly oriented vector within the sphere of radius `r' */
#define fvn_randball(v, r) fvn_smul(fvn_randball0(v), r)

/* randomly oriented vector within the sphere of radius `r' */
#define dvn_randball(v, r) dvn_smul(dvn_randball0(v), r)

/* randomly oriented vector within the sphere of radius `r' */
#define rvn_randball(v, r) rvn_smul(rvn_randball0(v), r)

/* randomly vector within the unit sphere */
INLINE float *fvn_randball0(float *v)
{
#if D < 5
  while ( fvn_sqr( fvn_randunif(v, -1, 1) ) >= 1 ) ;
  return v;
#else
  float r = (float) pow(rand01(), 1.0/D), nm;
  /* first obtain a orientation */
  while ( (nm = fvn_norm(fvn_randgaus(v))) <= 1e-8 ) ;
  /* the probability density rho(r) ~ r^(D - 1), so the cumulative
   * distribution P(r) = r^D, and r is obtained from P(r)^(1/D) */
  return fvn_smul(v, r/nm);
#endif
}

/* randomly vector within the unit sphere */
INLINE double *dvn_randball0(double *v)
{
#if D < 5
  while ( dvn_sqr( dvn_randunif(v, -1, 1) ) >= 1 ) ;
  return v;
#else
  double r = (double) pow(rand01(), 1.0/D), nm;
  /* first obtain a orientation */
  while ( (nm = dvn_norm(dvn_randgaus(v))) <= 1e-8 ) ;
  /* the probability density rho(r) ~ r^(D - 1), so the cumulative
   * distribution P(r) = r^D, and r is obtained from P(r)^(1/D) */
  return dvn_smul(v, r/nm);
#endif
}

/* randomly vector within the unit sphere */
INLINE real *rvn_randball0(real *v)
{
#if D < 5
  while ( rvn_sqr( rvn_randunif(v, -1, 1) ) >= 1 ) ;
  return v;
#else
  real r = (real) pow(rand01(), 1.0/D), nm;
  /* first obtain a orientation */
  while ( (nm = rvn_norm(rvn_randgaus(v))) <= 1e-8 ) ;
  /* the probability density rho(r) ~ r^(D - 1), so the cumulative
   * distribution P(r) = r^D, and r is obtained from P(r)^(1/D) */
  return rvn_smul(v, r/nm);
#endif
}




#ifndef FMN_T
#define FMN_T fmn_t
typedef float fmn_t[D][DM];
#endif

#ifndef DMN_T
#define DMN_T dmn_t
typedef double dmn_t[D][DM];
#endif

#ifndef RMN_T
#define RMN_T rmn_t
/* only the second dimension needs to be DM, the first can be D */
typedef real rmn_t[D][DM];
#endif


#define fmn_print(r, nm, fmt, nl) fmn_fprint(stdout, r, nm, fmt, nl)

#define dmn_print(r, nm, fmt, nl) dmn_fprint(stdout, r, nm, fmt, nl)

#define rmn_print(r, nm, fmt, nl) rmn_fprint(stdout, r, nm, fmt, nl)

INLINE void fmn_fprint(FILE *fp, float r[][DM], const char *nm,
    const char *fmt, int nl)
{
  int i, j;
  if (nm) fprintf(fp, "%s:%c", nm, (nl ? '\n' : ' '));
  for (i = 0; i < D; i++) {
    for (j = 0; j < D; j++) {
      fprintf(fp, fmt, r[i][j], nl);
    }
    fprintf(fp, "%s", (nl ? "\n" : "; "));
  }
}

INLINE void dmn_fprint(FILE *fp, double r[][DM], const char *nm,
    const char *fmt, int nl)
{
  int i, j;
  if (nm) fprintf(fp, "%s:%c", nm, (nl ? '\n' : ' '));
  for (i = 0; i < D; i++) {
    for (j = 0; j < D; j++) {
      fprintf(fp, fmt, r[i][j], nl);
    }
    fprintf(fp, "%s", (nl ? "\n" : "; "));
  }
}

INLINE void rmn_fprint(FILE *fp, real r[][DM], const char *nm,
    const char *fmt, int nl)
{
  int i, j;
  if (nm) fprintf(fp, "%s:%c", nm, (nl ? '\n' : ' '));
  for (i = 0; i < D; i++) {
    for (j = 0; j < D; j++) {
      fprintf(fp, fmt, r[i][j], nl);
    }
    fprintf(fp, "%s", (nl ? "\n" : "; "));
  }
}


INLINE fvn_t *fmn_make(float x[][DM], ...)
{
  int i, j;
  va_list vl;

  va_start(vl, x);
  for (i = 0; i < D; i++)
    for (j = 0; j < D; j++)
      x[i][j] = (float) va_arg(vl, double);
  va_end(vl);
  return x;
}

INLINE dvn_t *dmn_make(double x[][DM], ...)
{
  int i, j;
  va_list vl;

  va_start(vl, x);
  for (i = 0; i < D; i++)
    for (j = 0; j < D; j++)
      x[i][j] = (double) va_arg(vl, double);
  va_end(vl);
  return x;
}

INLINE rvn_t *rmn_make(real x[][DM], ...)
{
  int i, j;
  va_list vl;

  va_start(vl, x);
  for (i = 0; i < D; i++)
    for (j = 0; j < D; j++)
      x[i][j] = (real) va_arg(vl, double);
  va_end(vl);
  return x;
}


INLINE fvn_t *fmn_zero(float x[][DM])
{
  int i;

  for (i = 0; i < D; i++) fvn_zero(x[i]);
  return x;
}

INLINE dvn_t *dmn_zero(double x[][DM])
{
  int i;

  for (i = 0; i < D; i++) dvn_zero(x[i]);
  return x;
}

INLINE rvn_t *rmn_zero(real x[][DM])
{
  int i;

  for (i = 0; i < D; i++) rvn_zero(x[i]);
  return x;
}


INLINE fvn_t *fmn_one(float x[][DM])
{
  int i;

  for (i = 0; i < D; i++) {
    fvn_zero(x[i]);
    x[i][i] = (float) 1;
  }
  return x;
}

INLINE dvn_t *dmn_one(double x[][DM])
{
  int i;

  for (i = 0; i < D; i++) {
    dvn_zero(x[i]);
    x[i][i] = (double) 1;
  }
  return x;
}

INLINE rvn_t *rmn_one(real x[][DM])
{
  int i;

  for (i = 0; i < D; i++) {
    rvn_zero(x[i]);
    x[i][i] = (real) 1;
  }
  return x;
}


/* generate a random orthonormal (unitary) DxD matrix */
INLINE fvn_t *fmn_randuni(float a[][DM])
{
  int i, j;
  float dot;

  fvn_randdir0(a[0]);
  for (i = 1; i < D; i++) {
    fvn_randdir0(a[i]);
    /* normalize against previous vectors */
    for (j = 0; j < i; j++) {
      dot = fvn_dot(a[i], a[j]);
      fvn_normalize( fvn_sinc(a[i], a[j], -dot) );
    }
  }
  return a;
}

/* generate a random orthonormal (unitary) DxD matrix */
INLINE dvn_t *dmn_randuni(double a[][DM])
{
  int i, j;
  double dot;

  dvn_randdir0(a[0]);
  for (i = 1; i < D; i++) {
    dvn_randdir0(a[i]);
    /* normalize against previous vectors */
    for (j = 0; j < i; j++) {
      dot = dvn_dot(a[i], a[j]);
      dvn_normalize( dvn_sinc(a[i], a[j], -dot) );
    }
  }
  return a;
}

/* generate a random orthonormal (unitary) DxD matrix */
INLINE rvn_t *rmn_randuni(real a[][DM])
{
  int i, j;
  real dot;

  rvn_randdir0(a[0]);
  for (i = 1; i < D; i++) {
    rvn_randdir0(a[i]);
    /* normalize against previous vectors */
    for (j = 0; j < i; j++) {
      dot = rvn_dot(a[i], a[j]);
      rvn_normalize( rvn_sinc(a[i], a[j], -dot) );
    }
  }
  return a;
}


#endif /* ZCOM_RVN__ */
#endif /* ZCOM_RVN */





#ifdef  ZCOM_CHOLESKY
#ifndef ZCOM_CHOLESKY__
#define ZCOM_CHOLESKY__
#include <stdio.h>
#include <math.h>


/* Cholesky decomposition */


/* compute the Cholesky decomposition
 * the input matrix `a' should be positive definite
 * on return the left-bottom triangle is filled by the matrix L */
INLINE int choldecomp(real *a, int n)
{
  int i, j, k;
  real y;

  for ( i = 0; i < n; i ++ ) {
    for ( j = 0; j <= i; j++ ) {
      /* A(i, j) = L(i, 0) L(j, 0) + L(i, 1) L(j, 1) + ... + L(i, j) L(j, j)
       *         = sum {k = 0 to j - 1} L(i, k) L(j, k) + L(i, j) L(j, j) */
      for ( y = a[i*n + j], k = 0; k < j; k++ )
        y -= a[i*n + k] * a[j*n + k];
      if ( i == j ) {
        if ( y < 0 ) {
          fprintf(stderr, "cholesky: negative element on %d\n", i);
          return -1;
        }
        a[i*n + i] = sqrt(y);
      } else {
        a[j*n + i] = a[i*n + j] = y / a[j*n + j];
      }
    }
  }
  return 0;
}


/* solve a x = b by Cholesky decomposition
 * on return, `x' is saved in `b' */
INLINE int cholsolve(real *a, real *b, int n)
{
  int i, j;
  real y;

  if ( choldecomp(a, n) != 0 ) return -1;
  /* solve L y = b
   * sum {j = 0 to i - 1} L(i, j) y(j) + L(i, i) y(i) = b(i) */
  for ( i = 0; i < n; i++ ) {
    for ( y = b[i], j = 0; j < i; j++ )
      y -= a[i*n + j] * b[j];
    b[i] = y / a[i*n + i];
  }
  /* solve L^T x = y */
  for ( i = n - 1; i >= 0; i-- ) {
    for ( y = b[i], j = i + 1; j < n; j++ )
      y -= a[i*n + j] * b[j]; /* a(i, j) == a(j, i) */
    b[i] = y / a[i*n + i];
  }
  return 0;
}


/* inverse the matrix `a', b = a^(-1) by Cholesky decomposition */
INLINE int cholinv(real *a, real *b, int n)
{
  int i, j, k;
  real y;

  if ( choldecomp(a, n) != 0 ) return -1;
  for ( k = 0; k < n; k++ ) {
    /* solve L y = b_k, with b_k(i) = delta(k, i)
     * sum {j = 0 to i - 1} L(i, j) y(j) + L(i, i) y(i) = b(i) */
    for ( i = 0; i < n; i++ ) {
      y = (i == k) ? 1 : 0;
      for ( j = 0; j < i; j++ )
        y -= a[i*n + j] * b[j*n + k];
      b[i*n + k] = y / a[i*n + i];
    }
    /* solve L^T x = y */
    for ( i = n - 1; i >= 0; i-- ) {
      for ( y = b[i*n + k], j = i + 1; j < n; j++ )
        y -= a[i*n + j] * b[j*n + k]; /* a(i, j) == a(j, i) */
      b[i*n + k] = y / a[i*n + i];
    }
  }
  return 0;
}


#endif /* ZCOM_CHOLESKY__ */
#endif /* ZCOM_CHOLESKY */





#ifdef  ZCOM_LU
#ifndef ZCOM_LU__
#define ZCOM_LU__
#include <stdio.h>
#include <math.h>


/* LU decomposition */


STRCLS const real lu_tiny = 1e-20; /* absolute minimal value for a pivot */


/* solve A x = b by L U decomposition
 * on return, matrix `a' is destroyed, and vector `b' becomes `x' */
INLINE int lusolve(real * RESTRICT a, real * RESTRICT b, int n)
{
  int i, j, k, ip = 0;
  real x, max;

  for (i = 0; i < n; i++) {  /* normalize each equation */
    for (max = 0.0, j = 0; j < n; j++)
      if ((x = fabs(a[i*n + j])) > max)
        max = x;
    if (max < lu_tiny) return 1;
    for (x = 1.0/max, j = 0; j < n; j++)
      a[i*n + j] *= x;
    b[i] *= x;
  }

  /* step 1: A = L U, column by column */
  for (j = 0; j < n; j++) {
    /* matrix U */
    for (i = 0; i < j; i++) {
      for (x = a[i*n + j], k = 0; k < i; k++)
        x -= a[i*n + k] * a[k*n + j];
      a[i*n + j] = x;
    }

    /* matrix L, diagonal of L are 1 */
    ip = j;
    max = 0;
    for (i = j; i < n; i++) {
      for (x = a[i*n + j], k = 0; k < j; k++)
        x -= a[i*n + k] * a[k*n + j];
      a[i*n + j] = x;
      if (fabs(x) >= max) {
        max = fabs(x);
        ip = i;
      }
    }

    if (j != ip) { /* swap the pivot row with the jth row */
      for (k = 0; k < n; k++)
        x = a[ip*n + k], a[ip*n + k] = a[j*n + k], a[j*n + k] = x;
      x = b[ip], b[ip] = b[j], b[j] = x;
    }
    if (fabs(a[j*n + j]) < lu_tiny)
      a[j*n + j] = lu_tiny;
    /* divide by the pivot element, for the L matrix */
    if (j != n - 1)
      for (x = 1.0/a[j*n + j], i = j + 1; i < n; i++)
        a[i*n + j] *= x;
  }

  /* step 2: solve the equation L U x = b */
  for (i = 0; i < n; i++) { /* L y = b */
    x = b[i];
    for (j = 0; j < i; j++) x -= a[i*n + j] * b[j];
    b[i] = x;
  }
  for (i = n - 1; i >= 0; i--) { /* U x = y. */
    x = b[i];
    for (j = i + 1; j < n; j++) x -= a[i*n + j] * b[j];
    b[i] = x / a[i*n + i];
  }
  return 0;
}


/* invert matrix `a' as b = a^(-1)
 * on return, matrix `a' is destroyed */
INLINE int luinv(real * RESTRICT a, real * RESTRICT b, int n)
{
  int i, j, k, ip = 0;
  real x, max;

  /* initialize the matrix as the identity matrix */
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      b[i*n + j] = (i == j);

  for (i = 0; i < n; i++) {  /* normalize each equation */
    for (max = 0.0, j = 0; j < n; j++)
      if ((x = fabs(a[i*n + j])) > max)
        max = x;
    if (max < lu_tiny) return 1;
    for (x = 1.0/max, j = 0; j < n; j++)
      a[i*n + j] *= x;
    b[i*n + i] *= x;
  }

  /* solve A = L U, column by column */
  for (j = 0; j < n; j++) {
    /* matrix U */
    for (i = 0; i < j; i++) {
      for (x = a[i*n + j], k = 0; k < i; k++)
        x -= a[i*n + k] * a[k*n + j];
      a[i*n + j] = x;
    }

    /* matrix L, diagonal of L are 1 */
    ip = j;
    max = 0;
    for (i = j; i < n; i++) {
      for (x = a[i*n + j], k = 0; k < j; k++)
        x -= a[i*n + k] * a[k*n + j];
      a[i*n + j] = x;
      if (fabs(x) >= max) {
        max = fabs(x);
        ip = i;
      }
    }

    if (j != ip) { /* swap the pivot row with the jth row */
      for (k = 0; k < n; k++) {
        x = a[ip*n + k], a[ip*n + k] = a[j*n + k], a[j*n + k] = x;
        x = b[ip*n + k], b[ip*n + k] = b[j*n + k], b[j*n + k] = x;
      }
    }
    if (fabs(a[j*n + j]) < lu_tiny)
      a[j*n + j] = lu_tiny;
    /* divide by the pivot element, for the L matrix */
    if (j != n - 1)
      for (x = 1.0/a[j*n + j], i = j + 1; i < n; i++)
        a[i*n + j] *= x;
  }

  for ( k = 0; k < n; k++ ) {
    /* solve L U x = b_k */
    for (i = 0; i < n; i++) { /* L y = b */
      x = b[i*n + k];
      for (j = 0; j < i; j++) x -= a[i*n + j] * b[j*n + k];
      b[i*n + k] = x;
    }
    for (i = n - 1; i >= 0; i--) { /* U x = y. */
      x = b[i*n + k];
      for (j = i + 1; j < n; j++) x -= a[i*n + j] * b[j*n + k];
      b[i*n + k] = x / a[i*n + i];
    }
  }
  return 0;
}

#endif /* ZCOM_LU__ */
#endif /* ZCOM_LU */





#ifdef  ZCOM_SVD
#ifndef ZCOM_SVD__
#define ZCOM_SVD__


/* singular value decomposition of mxn matrix `a'
 * a[m*n] (or u[m*n] on return), w[n], v[n*n] */
INLINE int svd(real *a, real *w, real *v, int m, int n)
{
  int flag, i, it, j, jj, k, l, nm;
  real c, f, h, s, x, y, z;
  real anorm = 0, g, scl;
  real *rv1;

  die_if (m < n, "ERROR: m %d < n %d\n", m, n);
  xnew(rv1, n);

  /* Householder reduction to bidiagonal form */
  for (g = s = scl = 0., i = 0; i < n; i++) {
    /* left-hand reduction */
    l = i + 1;
    rv1[i] = scl * g;
    g = s = scl = 0.0;
    if (i < m) {
      for (k = i; k < m; k++)
        scl += (real) fabs(a[k*n+i]);
      if (scl > 0.) {
        for (k = i; k < m; k++) {
          a[k*n+i] = x = a[k*n+i]/scl;
          s += x*x;
        }
        f = a[i*n+i];
        g = (real) ((f > 0.) ? -sqrt(s) : sqrt(s));
        h = f * g - s;
        a[i*n+i] = f - g;
        if (i != n - 1) {
          for (j = l; j < n; j++) {
            for (s = 0.0, k = i; k < m; k++)
              s += a[k*n+i] * a[k*n+j];
            f = s / h;
            for (k = i; k < m; k++)
              a[k*n+j] += f * a[k*n+i];
          }
        }
        for (k = i; k < m; k++)
          a[k*n+i] = a[k*n+i]*scl;
      }
    }
    w[i] = scl*g;

    /* right-hand reduction */
    g = s = scl = 0.0;
    if (i < m && i != n - 1) {
      for (k = l; k < n; k++)
        scl += (real) fabs(a[i*n+k]);
      if (scl > 0.) {
        for (k = l; k < n; k++) {
          a[i*n+k] = x = a[i*n+k]/scl;
          s += x*x;
        }
        f = a[i*n+l];
        g = (real) ((f > 0) ? -sqrt(s) : sqrt(s));
        h = f * g - s;
        a[i*n+l] = f - g;
        for (k = l; k < n; k++)
          rv1[k] = a[i*n+k] / h;
        if (i != m - 1) {
          for (j = l; j < m; j++) {
            for (s = 0.0, k = l; k < n; k++)
              s += a[j*n+k] * a[i*n+k];
            for (k = l; k < n; k++)
              a[j*n+k] += s * rv1[k];
          }
        }
        for (k = l; k < n; k++)
          a[i*n+k] *= scl;
      }
    }
    x = (real) fabs(w[i]);
    x += (real) fabs(rv1[i]);
    if (x > anorm) anorm = x;
  }

  /* accumulate the right-hand transformation */
  for (i = n - 1; i >= 0; i--) {
    if (i < n - 1) {
      if (g != 0) {
        for (j = l; j < n; j++)
          v[j*n+i] = ((a[i*n+j] / a[i*n+l]) / g);
        /* real division to avoid underflow */
        for (j = l; j < n; j++) {
          for (s = 0.0, k = l; k < n; k++)
            s += (a[i*n+k] * v[k*n+j]);
          for (k = l; k < n; k++)
            v[k*n+j] += (s * v[k*n+i]);
        }
      }
      for (j = l; j < n; j++)
        v[i*n+j] = v[j*n+i] = 0.0;
    }
    v[i*n+i] = 1.0;
    g = rv1[i];
    l = i;
  }

  /* accumulate the left-hand transformation */
  for (i = n - 1; i >= 0; i--) {
    l = i + 1;
    g = w[i];
    if (i < n - 1)
      for (j = l; j < n; j++) a[i*n+j] = 0;
    if (g != 0) {
      g = 1 / g;
      if (i != n - 1) {
        for (j = l; j < n; j++) {
          for (s = 0.0, k = l; k < m; k++)
            s += (a[k*n+i] * a[k*n+j]);
          f = s/a[i*n+i]*g;
          for (k = i; k < m; k++)
            a[k*n+j] += f*a[k*n+i];
        }
      }
      for (j = i; j < m; j++)
        a[j*n+i] = a[j*n+i]*g;
    } else {
      for (j = i; j < m; j++) a[j*n+i] = 0.0;
    }
    a[i*n+i] += 1.;
  }

  /* diagonalize the bidiagonal form */
  for (k = n - 1; k >= 0; k--) { /* loop over singular values */
    for (it = 0; it < 200; it++) { /* loop over allowed iterations */
      flag = 1;
      for (l = k; l >= 0; l--) { /* test for splitting */
        nm = l - 1;
        if (fabs(rv1[l]) + anorm == anorm) {
          flag = 0;
          break;
        }
        if (fabs(w[nm]) + anorm == anorm)
          break;
      }
      if (flag) {
        c = 0.0;
        s = 1.0;
        for (i = l; i <= k; i++) {
          f = s * rv1[i];
          if (fabs(f) + anorm == anorm) continue;
          g = w[i];
          h = (real) dblhypot(f, g);
          w[i] = h;
          h = 1 / h;
          c = g * h;
          s = (- f * h);
          for (j = 0; j < m; j++) {
            y = a[j*n+nm];
            z = a[j*n+i];
            a[j*n+nm] = y * c + z * s;
            a[j*n+i] = z * c - y * s;
          }
        }
      }
      z = w[k];
      if (l == k) { /* convergence */
        if (z < 0.0) { /* flip sign of w */
          w[k] = -z;
          for (j = 0; j < n; j++)
            v[j*n+k] = -v[j*n+k];
        }
        break;
      }
      if (it >= 200) {
        free(rv1);
        fprintf(stderr, "svd: failed to converge\n");
        return -1;
      }

      /* shift from bottom 2 x 2 minor */
      x = w[l];
      nm = k - 1;
      y = w[nm];
      g = rv1[nm];
      h = rv1[k];
      f = ((y - z) * (y + z) + (g - h) * (g + h)) / (2 * h * y);
      g = (real) dblhypot(f, 1.0);
      if (f < 0.) g = -g;
      f = ((x - z) * (x + z) + h * (y/(f + g) - h)) / x;

      /* next QR transformation */
      c = s = 1.0;
      for (j = l; j <= nm; j++) {
        i = j + 1;
        g = rv1[i];
        y = w[i];
        h = s * g;
        g = c * g;
        z = (real) dblhypot(f, h);
        rv1[j] = z;
        c = f / z;
        s = h / z;
        f = x * c + g * s;
        g = g * c - x * s;
        h = y * s;
        y = y * c;
        for (jj = 0; jj < n; jj++) {
          x = v[jj*n+j];
          z = v[jj*n+i];
          v[jj*n+j] = x * c + z * s;
          v[jj*n+i] = z * c - x * s;
        }
        w[j] = z = (real) dblhypot(f, h);
        if (z > 0.) { c = f/z; s = h/z; }
        f = c * g + s * y;
        x = c * y - s * g;
        for (jj = 0; jj < m; jj++) {
          y = a[jj*n+j];
          z = a[jj*n+i];
          a[jj*n+j] = y * c + z * s;
          a[jj*n+i] = z * c - y * s;
        }
      }
      rv1[l] = 0.0;
      rv1[k] = f;
      w[k] = x;
    }
  }
  free(rv1);
  return 0;
}


INLINE int svdback(real *u, real *w, real *v, int m, int n, real *x, real *b)
{
  int i, j;
  real *b1, y;

  xnew(b1, n);
  for (i = 0; i < n; i++) {
    if (w[i] <= 0.) { b1[i] = 0.; continue; }
    for (y = 0, j = 0; j < m; j++)
      y += u[j*n+i]*b[j];
    b1[i] = y/w[i];
  }
  for (i = 0; i < n; i++) {
    for (y = 0., j = 0; j < n; j++)
      y += v[i*n+j]*b1[j];
    x[i] = y;
  }
  free(b1);
  return 0;
}


INLINE int svdsolve(real *a, real *x, real *b, int n, real rerr)
{
  int i;
  real *u, *v, *w, wmax, wmin;

  xnew(w, n); xnew(u, n*n); xnew(v, n*n);
  for (i = 0; i < n*n; i++) u[i] = a[i];
  svd(u, w, v, n, n);
  for (wmax = 0., i = 0; i < n; i++)
    if (w[i] > wmax) wmax = w[i];
  for (wmin = wmax*rerr, i = 0; i < n; i++)
    if (w[i] < wmin) w[i] = wmin;
  for (i = 0; i < n; i++) printf("%g  ", w[i]);
  printf("\n");
  svdback(u, w, v, n, n, x, b);
  free(u); free(v); free(w);
  return 0;
}

#endif /* ZCOM_SVD__ */
#endif /* ZCOM_SVD */





#ifdef  ZCOM_EIG
#ifndef ZCOM_EIG__
#define ZCOM_EIG__

#ifdef __INTEL_COMPILER
#pragma warning push
#pragma warning(disable:1572) /* float-point comparison */
#endif


/* To reduce a real symmetric matrix 'm' to tridiagonal by Householder transformations.
 * The diagonal elements are saved in vector 'd' and off-diagonal elements 'e'.  */
INLINE void tridiag(real *m, real d[], real e[], int n)
{
  int i, j, k;
  real H, sigma, p, K, *x;

  /* use d[i] to indicate if the i'th Householder transformation is performed */
  for (i = 0; i < n; i++) d[i] = 0;

  /* n-2 Householder transformations */
  for (i = 0; i < n - 2; i++) {
    x = m + i*n; /* alias x[k] == m[i*n+k] */

    for (H = 0, k = i + 1; k < n; k++) H += x[k]*x[k];
    sigma = (real)(x[i + 1] > 0 ? sqrt(H) : -sqrt(H)); /* sigma = sgn(x1) |x| */
    e[i] = -sigma; /* P x = - sigma e1 */
    H += sigma*x[i + 1]; /* H= (1/2) |u|^2 = |x|^2 + sigma x1 */

    /* To avoid singularity due to (partially) diagonal matrix as input */
    if (sigma + m[i*n + i] == m[i*n + i]) {
      e[i] = m[i*n + i + 1];
      continue;
    }

    x[i + 1] += sigma;  /* u = x + sigma e1, we now switch to 'u' */
    for (j = i + 1; j < n; j++) m[j*n + i] = x[j]/H; /* save u/H in column i */

    /*  CALCULATE P A P */
    K = 0;
    for (j = i + 1; j < n; j++) {
      /* calculate p=A u /H, we only use the up triangle */
      for (p = 0, k = i + 1; k <= j; k++) p += m[k*n + j]*x[k];
      for (k = j + 1; k < n; k++) p += m[j*n + k]*x[k];
      e[j] = (p /= H); /* save p temporarily to e[j], notice e[i+1..n-1] are not used yet.*/
      K += x[j]*p; /* K = u' p / (2H) */
    }
    K /= (2*H); /* K = u' p / (2H) */
    for (j = i + 1; j < n; j++) e[j] -= K*x[j];  /* form  q = p - K u */
    for (j = i + 1; j < n; j++) /* calculate A' = A - q u' - u q' (only right-top triangle) */
      for (k = j; k < n; k++)
        m[j*n + k] -= e[j]*x[k] + x[j]*e[k];

    d[i] = 1; /* indicate that the transformation is performed */
  }
  e[n - 2] = m[(n - 2)*n + n - 1]; /* for i == n-2 */
  e[n - 1] = 0;

  /* if only eigenvalues are required, enable the above line and ignore the rest */

  /* To form Q = P1 ... Pn-2 */
  d[n - 2] = m[(n - 2)*n + n - 2]; d[n - 1] = m[(n - 1)*n + n - 1]; /* copy last two eigenvalues */
  m[(n - 2)*n + n - 2] = 1; m[(n - 2)*n + n - 1] = 0; /* initialize the right-bottom corner */
  m[(n - 1)*n + n - 2] = 0; m[(n - 1)*n + n - 1] = 1;

  /* P Q = (1 - u u'/H) Q = Q - (u/H) (u' Q) */
  for (i = n - 3; i >= 0; i--) { /* for each P */
    x = m + i*n; /* alias x[k] == m[i*n+k] */

    /* Form eigenvector, ONLY if i'th transformation is performed */
    if (d[i] != 0) {
      for (j = i + 1; j < n; j++) {
        /* form K = u'Q */
        for (K = 0, k = i + 1; k < n; k++) K += x[k]*m[k*n + j];
        /* Q = Q - K (u/H)  */
        for (k = i + 1; k < n; k++) m[k*n + j] -= K*m[k*n + i];
      }
    }
    /* copy the diagonal element and proceed */
    d[i] = m[i*n + i];
    m[i*n + i] = 1;
    for (j = i + 1; j < n; j++) m[i*n + j] = m[j*n + i] = 0.;
  }
}


/* diagonalize the tridiagonal matrix by QR algorithm,
   whose diagonal is d[0..n-1], off-diagonal is e[0..n-2];
 * reduce from the left-top to right-left */
INLINE void eigtriqr(real d[], real e[], int n, real *mat)
{
  const int itermax = 1000;
  int i, j, k, m, iter, sgn;
  real ks = 0, r, c, s, delta, f, t1, t2, tol;

  e[n - 1] = 0;
  tol = (sizeof(real) == sizeof(float)) ? 1e-6f : 1e-12f;
  for (i = 0; i < n; i++) {
    /* for each eigenvalue */
    for (iter = 0; iter < itermax; iter++) {
      /* Look for a single small subdiagonal element to split the matrix */
      for (m = i; m < n - 1; m++) {
        double d1 = fabs(d[m + 1]), d2 = fabs(d[m]);
        if (fabs(e[m]) < (d1 + d2) * tol)
          break;
      }

      /* I have isolated d[i] from other matrix elements
       * so that d[i] is the eigenvalue.
       * stop iteration and look for next(i+1) eigenvalue  */
      if (m == i) break;

      /* form shift ks */
      delta = d[m] - d[m - 1];
      sgn = ((delta > 0) ? 1: -1);
      delta /= e[m - 1];
      r = (real) dblhypot(delta, 1);
      ks = d[m] + sgn*e[m - 1]/(r + (real) fabs(delta));

      /* Rotations */
      for (j = i; j <= m - 1; j++) {
        /* calculate c and s */
        if (j == i) {
          /* First rotation */
          r = (real) dblhypot(d[i] - ks, e[i]);
          c = (d[i] - ks)/r;
          s = e[i]/r;
        } else {
          /* Givens rotations */
          r = (real) dblhypot(e[j - 1], f);
          c = e[j - 1]/r;
          s = f/r;
          e[j - 1] = r;
        }

        /* update the diagonal and off-diagonal elements */
        r = s*(d[j + 1] - d[j]) + 2*c*e[j];
        d[j]   += s*r;
        d[j + 1] -= s*r;
        e[j]    = c*r - e[j];
        f       = s*e[j + 1];
        e[j + 1] *= c;

        /* update eigenvectors */
        for (k = 0; k < n; k++) {
          t1 = mat[k*n + j];
          t2 = mat[k*n + j + 1];
          mat[k*n + j]   = c*t1 + s*t2;
          mat[k*n + j + 1] = -s*t1 + c*t2;
        }
      } /* end of rotations */
    } /* end for iteration */
    /*printf("Iterate %d times for %d'th eigenvalue.\n", iter, i);*/
  }/* end for each eigenvalue */
}


/* sort eigenvalues and eigenvectors in ascending order */
INLINE void eigsort(real *d, real *v, int n)
{
  int i, j, im;
  real max, tmp;

  for (i = 0; i < n - 1; i++) {
    /* search the maximal eigenvalue */
    for (max = d[i], im = i, j = i + 1; j < n; j++) {
      if (d[j] > max) max = d[im = j];
    }
    if (im != i) { /* change column im and i */
      tmp = d[i], d[i] = d[im], d[im] = tmp;
      for (j = 0; j < n; j++)
        tmp = v[j*n + i], v[j*n + i] = v[j*n + im], v[j*n + im] = tmp;
    }
  }
}


/* solve eigensystem of a real symmetric matrix `mat',
 * eigenvalues saved to `d', eigenvectors to v */
INLINE int eigsym(real *mat, real *d, real *v, int n)
{
  real *e;
  int i;

  xnew(e, n);
  for (i = 0; i < n*n; i++) v[i] = mat[i];
  tridiag(v, d, e, n);
  eigtriqr(d, e, n, v);
  eigsort(d, v, n);
  free(e);
  return 0;
}


#ifdef __INTEL_COMPILER
#pragma warning pop
#endif


#endif /* ZCOM_EIG__ */
#endif /* ZCOM_EIG */





#ifdef  ZCOM_SPECFUNC
#ifndef ZCOM_SPECFUNC__
#define ZCOM_SPECFUNC__

/* returns log(Gamma(a)),
 * where Gamma(a) = \int_0^\infty e^(-t) t^(a-1) dt */
INLINE double lngam(double a)
{
  int i;
  double xp, ahg, y;
  static const double gh = 671./128, sqrt2pi = 2.506628274631000242,
    c[15] = {0.999999999999997092,      57.1562356658629235,      -59.5979603554754912,
            14.1360979747417471,        -0.491913816097620199,       .339946499848118887e-4,
              .465236289270485756e-4,    -.983744753048795646e-4,    .158088703224912494e-3,
             -.210264441724104883e-3,     .217439618115212643e-3,   -.164318106536763890e-3,
              .844182239838527433e-4,    -.261908384015814087e-4,    .368991826595316234e-5};

  die_if (a <= 0., "neg. arg. for lngam(%g)\n", a);
  for (xp = c[0], i = 1; i < 15; i++)
    xp += c[i]/(a + i);
  ahg = a + gh;
  y = (a + .5) * log(ahg) - ahg;
  return y + log( sqrt2pi * xp / a); /* gamma(a) = gamma(a+1)/a */
}


/* returns incomplete gamma function log(gamma(a, x)),
 * where gamma(a, x) = \int_0^x e^(-t) t^(a-1) dt
 * = e^(-x) x^a \sum_{i = 0} Gamma(a)/Gamma(a + 1 + i) x^i
 * for small x, cf. gser() in Numerical-Recipes */
INLINE double lnincgam0(double a, double x)
{
  int i;
  double del, sum, y;

  die_if (x < 0., "neg. arg. for lnincgam0(%g)\n", x);
  if (x <= 0) return -1e30; /* log(0+) */
  sum = del = 1 / a;
  for (i = 1; i <= 1000; i++) {
    del *= x/(a + i);
    sum += del;
    y = fabs(sum);
    if (fabs(del) < y * 5e-16) break;
  }
  y = log(sum);
  return -x + a * log(x) + y;
}


/* returns incomplete gamma function log(Gamma(a, x)),
 * where Gamma(a, x) = \int_x^\infty e^(-t) t^(a-1) dt
 * = e^(-x) x^a [1/(x+1-a-) [1*(1-a)/(x+3-a-) [2*(2-a)/(x+5-a) ...]
 * for large x, cf. gcf() in Numerical-Recipes */
INLINE double lnincgam1(double a, double x)
{
  int i;
  double an, b, c, d, h, del;
  const double fpmin = 1e-300;

  b = x + 1 - a;
  d = 1/b;
  c = 1/fpmin;
  h = d;
  /* modified Lentz's method for the continued fraction */
  for (i = 1; i <= 1000; i++) {
    an = -1.*i*(i - a); /* numerator */
    b += 2;
    d = d*an + b;
    if (fabs(d) < fpmin) d = fpmin;
    c = b + an/c;
    if (fabs(c) < fpmin) c = fpmin;
    d = 1.0/d;
    del = d*c;
    h *= del;
    if (fabs(del - 1) < 5e-16) break;
  }
  h = log(h);
  return -x + a * log(x) + h;
}


/* returns incomplete gamma function log(gamma(a, x)),
 * where gamma(a, x) = \int_0^x e^(-t) t^(a-1) dt */
INLINE double lnincgam(double a, double x)
{
  if (x < a + 1) {
    return lnincgam0(a, x);
  } else {
    double u = lngam(a), v = lnincgam1(a, x);
    return lndif(u, v);
  }
}


/* returns incomplete gamma function log(Gamma(a, x)),
 * where Gamma(a, x) = \int_x^\infty e^(-t) t^(a-1) dt */
INLINE double lnincgamup(double a, double x)
{
  if (x < a + 1) {
    double u = lngam(a), v = lnincgam0(a, x);
    return lndif(u, v);
  } else {
    return lnincgam1(a, x);
  }
}


/* return the p-value, or 1 - cdf(x), for KS distribution */
INLINE double ksq(double x)
{
  double y, y4, y8, y24, y48;

  die_if (x < 0, "neg. arg. for ksq(x = %g)\n", x);
  if (x < 1e-15) {
    return 1.;
  } else if (x < 1.18) {
    x = 1.110720734539591525 / x;
    y = exp(-x * x);
    y8 = pow(y, 8);
    y24 = y8 * y8 * y8;
    y48 = y24 * y24;
    return 1. - 2.25675833419102515 * x * y * (1 + y8 + y24 + y48);
  } else {
    y = exp(-2 * x * x);
    y4 = y * y * y * y;
    y8 = y4 * y4;
    return 2. * (y * (1 + y8) - y4);
  }
}


/* normalized associated Legendre polynomial
 * nplm(x) = sqrt( (2l+1)/(4 pi) (l-m)!/(l+m)!) P_l^m(x)
 * real solution of m <= l, l, m >= 0
 * (1 - x^2) y'' - 2 x y' + [l(l+1) - m^2/(1-x^2)] y = 0 */
INLINE double plegendre(double x, int l, int m)
{
  int i;
  double y, yp, ypp, f, fp, s = 1 - x*x;

  if (m < 0 || m > l || s < 0) return 0;
  for (yp = 1, i = 1; i <= m; i++) yp *= (1 + .5/i)*s;
  yp = sqrt(yp / (4 * M_PI)) * (m % 2 ? -1: 1); /* P(m, m) */
  /* (l-m) P_l^m = x (2l-1) P_{l-1}^m - (l+m-1)*P_{l-2}^m */
  for (fp = 1, ypp = 0, i = m + 1; i <= l; i++, fp = f, ypp = yp, yp = y) {
    f = sqrt( (4. * i * i - 1) / ((i - m) * (i + m)) );
    y = f*(x*yp - ypp/fp);
  }
  return yp;
}

#endif /* ZCOM_SPECFUNC__ */
#endif /* ZCOM_SPECFUNC */





#ifdef  ZCOM_NUMTHR
#ifndef ZCOM_NUMTHR__
#define ZCOM_NUMTHR__


INLINE char *getisprime(char *isp, int n)
{
  int i, j, imax;
  for (i = 1; i < n; i++) isp[i] = (char) (i % 2);
  isp[1] = 0;
  imax = (int) sqrt(i);
  for (i = 3; i < imax; i += 2)
    if (isp[i]) /* remove multiples of i */
      for (j = i*i; j < n; j += 2*i)
        isp[j] = 0;
  return isp;
}


INLINE int gcd(int a, int b)
{
  int c;
  while ( a != 0 ) c = a, a = b % a, b = c;
  return b;
}


INLINE int64_t gcd64(int64_t a, int64_t b)
{
  int64_t c;
  while ( a != 0 ) c = a, a = b % a, b = c;
  return b;
}


/* moduler inverse by the Extended Euclidean algorithm
 * http://en.wikipedia.org/wiki/Extended_Euclidean_algorithm#Modular_integers */
INLINE int modinv(int a, int n)
{
  int t = 0, r = n, nt = 1, nr = a, t0, r0, q;
  while (nr != 0) {
    q = r / nr;
    t0 = nt; nt = t - q * nt; t = t0;
    r0 = nr; nr = r - q * nr; r = r0;
  }
  if (r > 1) return -1;
  return (t < 0) ? t + n : t;
}


INLINE int64_t modinv64(int64_t a, int64_t n)
{
  int64_t t = 0, r = n, nt = 1, nr = a, t0, r0, q;
  while (nr != 0) {
    q = r / nr;
    t0 = nt; nt = t - q * nt; t = t0;
    r0 = nr; nr = r - q * nr; r = r0;
  }
  if (r > 1) return -1;
  return (t < 0) ? t + n : t;
}


/* http://en.wikipedia.org/wiki/Binary_exponentiation */
INLINE int modpow(int x, int e, int m)
{
  int y;
  for ( y = 1; e > 0; x = x * x % m, e >>= 1 )
    if ( e & 0x1 ) y = y * x % m;
  return y;
}


INLINE int64_t modpow64(int64_t x, int64_t e, int64_t m)
{
  int64_t y;
  for ( y = 1; e > 0; x = x * x % m, e >>= 1 )
    if ( e & 0x1 ) y = y * x % m;
  return y;
}


/* solve r^2 = n (mod p), return one x, the other solution is p - r
 * http://en.wikipedia.org/wiki/Tonelli%E2%80%93Shanks_algorithm
 * p must be an odd prime */
INLINE int modpsqrt(int n, int p)
{
  int p1 = (p - 1)/2, q, s, z, c, r, t, m, t2, i, j, b;
  /* compute the Legendre symbol, if it is -1, no quadratic residue */
  if (modpow(n, p1, p) != 1) return -1;
  for ( s = 1, q = p1; q % 2 == 0; s++ ) q /= 2;
  if ( s == 1 ) return modpow(n, (p + 1) / 4, p);
  /* find a non-quadratic residue z */
  for ( z = 2; z < p && modpow(z, p1, p) != p - 1; z++ ) ;
  r = modpow(n, (q + 1) / 2, p);
  c = modpow(z, q, p);
  t = modpow(n, q, p);
  m = s;
  for ( ; t != 1; r = r * b % p, c = b * b % p, t = t * c % p, m = i ) {
    for ( t2 = t, i = 0; i < m && t2 != 1; i++ ) t2 = t2 * t2 % p;
    for ( b = c, j = 0; j < m - i - 1; j++ ) b = b * b % p;
  }
  return r;
}


/* solve r^2 = n (mod p), return one x, the other solution is p - r
 * http://en.wikipedia.org/wiki/Tonelli%E2%80%93Shanks_algorithm
 * p must be an odd prime */
STRCLS int64_t modpsqrt64(int64_t n, int64_t p)
{
  int64_t p1 = (p - 1)/2, q, s, z, c, r, t, m, t2, i, j, b;
  /* compute the Legendre symbol, if it is -1, no quadratic residue */
  if (modpow64(n, p1, p) != 1) return -1;
  for ( s = 1, q = p1; q % 2 == 0; s++ ) q /= 2;
  if ( s == 1 ) return modpow64(n, (p + 1) / 4, p);
  /* find a non-quadratic residue z */
  for ( z = 2; z < p && modpow64(z, p1, p) != p - 1; z++ ) ;
  c = modpow64(z, q, p);
  r = modpow64(n, (q + 1) / 2, p);
  t = modpow64(n, q, p);
  m = s;
  for ( ; t != 1; r = r * b % p, c = b * b % p, t = t * c % p, m = i ) {
    for ( t2 = t, i = 0; i < m && t2 != 1; i++ ) t2 = t2 * t2 % p;
    for ( b = c, j = 0; j < m - i - 1; j++ ) b = b * b % p;
  }
  return r;
}


#endif /* ZCOM_NUMTHR__ */
#endif /* ZCOM_NUMTHR */





#ifdef  ZCOM_SAVGOL
#ifndef ZCOM_SAVGOL__
#define ZCOM_SAVGOL__


/* compute 1d Savitzky-Golay coefficients
 * `der' == 0 for function itself, 1 for first-order derivative */
INLINE double *savgol(int w, int ord, int der, int h, int verbose)
{
  int i, i0, i1, ox, oy, nop, orm, npt;
  double x, xk, y;
  double *mmt, *b, *mat, *x2m, *c;

  if (der > ord) {
    fprintf(stderr, "no %dth order of derivative, order = %d\n", der, ord);
    return NULL;
  }
  nop = ord + 1;
  orm = 2*ord + 1;
  npt = h ? (2*w) : (2*w + 1);
  i0 = -w;
  i1 = h ? w : (w + 1);
  xnew(c, npt);
  xnew(b, nop);
  xnew(mat, nop * nop);
  xnew(mmt, orm);
  xnew(x2m, nop * npt);

  for (i = 0; i < orm; i++) mmt[i] = 0.;
  for (i = i0; i < i1; i++) {
    x = h ? (i + .5) : i;
    /* mmt[k] = < x^k > */
    for (xk = 1., ox = 0; ox < orm; ox++, xk *= x)
      mmt[ox] += xk;
    /* x2m[k*npt + x] = x^k */
    for (xk = 1., ox = 0; ox <= ord; ox++, xk *= x)
      x2m[ox*npt + (i - i0)] = xk;
  }

  /* install matrix from moments */
  for (ox = 0; ox < nop; ox++)
    for (oy = 0; oy < nop; oy++)
      mat[ox*nop + oy] = mmt[ox + oy];

  /* we approximate y(x) = a0 + a1 x + a2 x^2 + ...
   * mat.a = b = x2m.y, or a = mat^(-1).b
   * since mat is symmetrical, rows == columns,
   * we thus extract the first row by solving b = {1, 0, 0, ...} */
  for (i = 0; i < nop; i++) b[i] = 0;
  b[der] = 1.;
  if (lusolve(mat, b, nop) != 0) {
    fprintf(stderr, "unable to inverse matrix!\n");
    free(c);
    c = NULL;
    goto ERR;
  }
  /* c = mat^(-1).x2m */
  for (i = 0; i < npt; i++) {
    for (y = 0, ox = 0; ox < nop; ox++)
      y += b[ox]*x2m[ox*npt + i];
    c[i] = y;
  }
  if (verbose) {
    for (i = 0; i < npt; i++)
      printf("%g\t", c[i]);
    printf("\n");
  }
ERR:
  free(b);
  free(mat);
  free(mmt);
  free(x2m);
  return c;
}


/* compute 2d Savitzky-Golay coefficients
 * h means if it is a histogram */
INLINE double *savgol2d(int iw, int jw, int ord, int h, int verbose)
{
  int i, j, i0, i1, j0, j1, id, nop, orm, npt;
  int io, iq, ox, oy, o1, o2, o3, o4;
  double w, x, y, xk, xyk;
  double *mmt, *b, *mat, *x2m, *c;

  nop = (ord + 1) * (ord + 2) / 2;
  orm = 2*ord + 1;
  i0 = -iw;
  j0 = -jw;
  if (h) { /* for histogram */
    npt = (2*iw) * (2*jw);
    i1 = iw;
    j1 = jw;
  } else {
    npt = (2*iw + 1) * (2*jw + 1);
    i1 = iw + 1;
    j1 = jw + 1;
  }
  xnew(c, npt);
  xnew(b, nop);
  xnew(mat, nop * nop);
  xnew(mmt, orm * orm);
  xnew(x2m, nop * npt);

  for (i = 0; i < orm*orm; i++) mmt[i] = 0.;
  for (i = i0; i < i1; i++) {
    x = h ? (i + .5) : i;
    for (j = j0; j < j1; j++) {
      y = h ? (j + .5) : j;
      w = 1.;
      /* moment matrix */
      xk = w;
      for (ox = 0; ox < orm; ox++) {
        xyk = xk;
        for (oy = 0; oy < orm - ox; oy++) {
          mmt[ox*orm + oy] += xyk;
          xyk *= y;
        }
        xk *= x;
      }
      /* position to z-moment matrix */
      id = (i - i0)*(j1 - j0) + (j - j0);
      for (io = 0, o1 = 0; o1 <= ord; o1++) {
        for (o2 = 0; o2 <= o1; o2++, io++) {
          xyk = w;
          for (ox = 0; ox < o1 - o2; ox++) xyk *= x;
          for (oy = 0; oy < o2; oy++) xyk *= y;
          x2m[io*npt + id] = xyk;
        }
      }
    }
  }

  /* install matrix from moments */
  for (io = 0, o1 = 0; o1 <= ord; o1++)
  for (o2 = 0; o2 <= o1; o2++, io++) {
    /* x^(o1-o2) y^o2 */
    for (iq = 0, o3 = 0; o3 <= ord; o3++)
    for (o4 = 0; o4 <= o3; o4++, iq++) {
      /* x^(o3-o4) y^o4 */
      ox = o3 - o4 + o1 - o2;
      oy = o4 + o2;
      mat[io*nop + iq] = mmt[ox*orm + oy];
    }
  }

  for (i = 0; i < nop; i++) b[i] = 0.;
  b[0] = 1.;
  if (lusolve(mat, b, nop) != 0) {
    fprintf(stderr, "unable to inverse matrix!\n");
    free(c);
    c = NULL;
    goto ERR;
  }
  for (i = 0; i < npt; i++) {
    for (y = 0, io = 0; io < nop; io++)
      y += b[io]*x2m[io*npt + i];
    c[i] = y;
  }
  if (verbose) {
    for (i = i0; i < i1; i++) {
      for (j = j0; j < j1; j++)
        printf("%7.4f ", c[(i - i0)*(j1 - j0) + (j - j0)]);
      printf("\n");
    }
  }
ERR:
  free(b);
  free(mat);
  free(mmt);
  free(x2m);
  return c;
}

#endif /* ZCOM_SAVGOL__ */
#endif /* ZCOM_SAVGOL */





#ifdef  ZCOM_MDS
#ifndef ZCOM_MDS__
#define ZCOM_MDS__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/* compute force and energy */
INLINE real mds_force(real *x, real *f, real *dm, int n, int dim)
{
  const real dmin = 1e-6f;
  int i, j, k;
  real ene = 0., dij, dref, dsc;
  real *dx, *xi, *xj, *fi, *fj;

  xnew(dx, dim);
  for (i = 0; i < n*dim; i++) f[i] = 0.;
  for (i = 0; i < n; i++) {
    xi = x + i*dim;
    fi = f + i*dim;
    for (j = i+1; j < n; j++) {
      xj = x + j*dim;
      fj = f + j*dim;
      for (dij = 0, k = 0; k < dim; k++) {
        dx[k] = xi[k] - xj[k];
        dij += dx[k]*dx[k];
      }
      dij = (real) sqrt(dij);
      dref = dm[i*n+j];
      if (dref < dmin) dref = dmin;
      dsc = dij/dref - 1;
      ene += dsc*dsc;
      /* dij is to be used in denominator in the loop, ensure its > 0 */
      if (dij < dmin) dij = dmin;
      for (k = 0; k < dim; k++) {
        dx[k] *= -(dij - dref)/(dref*dref*dij);
        fi[k] += dx[k];
        fj[k] -= dx[k];
      }
    }
  }
  free(dx);
  return ene;
}

/* make coordinates neat
 * center coordinates
 * rotate to principle coordinates */
INLINE void mds_trim(real *x, int n, int dim)
{
  real *av, *mmt, *eig, *vec, *xi, *b;
  int i, d, d2;

  /* center the graph */
  xnew(av, dim);
  for (i = 0; i < n; i++)
    for (d = 0; d < dim; d++)
      av[d] += x[i*dim + d];
  for (d = 0; d < dim; d++) av[d] /= n;
  for (i = 0; i < n; i++)
    for (d = 0; d < dim; d++)
      x[i*dim + d] -= av[d];
  free(av);

  /* compute moments */
  xnew(mmt, dim*dim);
  xnew(eig, dim);
  xnew(vec, dim*dim);
  xnew(b, dim);
  for (i = 0; i < n; i++) {
    for (d = 0; d < dim; d++)
      for (d2 = 0; d2 < dim; d2++)
        mmt[d*dim+d2] += x[i*dim+d]*x[i*dim+d2];
  }
  eigsym(mmt, eig, vec, dim);
  for (i = 0; i < n; i++) {
    /* rotate x[i*dim .. i*dim+d-1] --> b[0 .. d-1] */
    xi = x + i*dim;
    for (d = 0; d < dim; d++) /* b = xi.vec */
      for (b[d] = 0., d2 = 0; d2 < dim; d2++)
        b[d] += xi[d2]*vec[d2*dim+d];
    for (d = 0; d < dim; d++) xi[d] = b[d];
  }
  free(b);
  free(eig);
  free(vec);
  free(mmt);
}


/* multidimensional scaling - steepest descend
 * given a distance matrix dm[n x n],
 * return best mds position x[n x dim];
 * dim is the target dimensional, e.g. 2
 * return the total discrepancy
 * sum_{i, j} (d(i, j) / dm(i, j) - 1)^2 */
INLINE real mds_min0(real *x, real *dm, int n, int dim, double tol)
{
  int i, j, it, itermax = 100000, npr;
  real *f, *fp, *xp, ene, enep;
  real dt = 1e-1f;

  if (n == 1) {
    for (j = 0; j < dim; j++) x[j] = 0.;
    return 0.0;
  }
  npr = n*(n-1)/2;
  xnew(f, n*dim);
  xnew(xp, n*dim);
  xnew(fp, n*dim);
  ene = mds_force(x, f, dm, n, dim);
  for (it = 0; it < itermax; it++) {
    enep = ene;
    for (i = 0; i < n*dim; i++) { /* backup */
      xp[i] = x[i];
      fp[i] = f[i];
    }
    for (i = 0; i < n*dim; i++) x[i] += f[i]*dt;
    ene = mds_force(x, f, dm, n, dim);
    if (ene > enep) {
      dt *= 0.7f;
      for (i = 0; i < n*dim; i++) { /* recover */
        x[i] = xp[i];
        f[i] = fp[i];
      }
      ene = enep;
    } else {
      if (fabs(ene-enep) < tol*npr*dt) break;
      dt *= 1.03f; /* attempt to increase time step */
    }
  }
  if (it >= itermax) {
    fprintf(stderr, "mds: failed to converge after %d iterations, %g\n",
        it, fabs(ene-enep));
  }
  mds_trim(x, n, dim);
  free(xp);
  free(f);
  free(fp);
  return ene;
}

#endif /* ZCOM_MDS__ */
#endif /* ZCOM_MDS */





#ifdef  ZCOM_PDB
#ifndef ZCOM_PDB__
#define ZCOM_PDB__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>


typedef struct {
  int aid; /* atom index */
  int rid; /* residue index */
  int insert; /* PDB insertion code, column 27 */
  char atnm[8];
  char resnm[8];
  char elem[4];
  real *x; /* pointer to pdbmodel_t.x */
} pdbatom_t; /* a single atom entry */

typedef struct {
  int natm; /* # of lines == # of atoms */
  int nalloc;
  int nres;
  pdbatom_t *atm; /* array of n or nalloc */
  real (*x)[3];  /* coordinate array of n or nalloc */
  int unitnm; /* unit is nanometer instead of angstrom */
  const char *file;  /* name of the source file */
} pdbmodel_t; /* raw data in a pdb model */

/* major functions for generic pdb model */
#define pdbm_open(fn, v) pdbm_read(fn, v)
INLINE pdbmodel_t *pdbm_read(const char *fn, int verbose);
INLINE int pdbm_write(pdbmodel_t *m, const char *fn);


typedef struct {
  int iaa;  /* index of amino acid [0, 20) */
  int nat; /* number of atoms */
  int id[32]; /* indices to the coordinate array */
  unsigned long flags;
  real *xca, *xn, *xc, *xo; /* pointers to pdbacc->x */
} pdbaar_t; /* amino-acid residues */

typedef struct {
  int nres;
  int natm;
  pdbaar_t *res; /* array of nres */
  real (*x)[3]; /* array of natom */
  int unitnm; /* unit is nanometer instead of angstrom */
  const char *file; /* input file */
} pdbaac_t; /* amino-acid chain */


/* protein pdb */
INLINE pdbaac_t *pdbaac_parse(pdbmodel_t *m, int verbose);
INLINE pdbaac_t *pdbaac_open(const char *fn, int verbose);
#define pdbaac_x(c, i, nm) pdbaac_getx(c, i, #nm)

#define AA_CA         0x1
#define AA_N          0x2
#define AA_C          0x4
#define AA_BACKBONE   (AA_CA | AA_N | AA_C)
#define AA_MAINCHAIN  (AA_BACKBONE | AA_O)
#define AA_H2   29
#define AA_H3   30
#define AA_OXT  31


/* don't edit data in the structure, written by mkdb.py */
struct tag_pdb_aadb {
  const char *resnm;      /* residue name */
  const char *atom[25];   /* atoms */
  const char *sub[11];    /* substitutions */
  unsigned long hvflags;  /* backbone and heavy atom flags */
} pdb_aadb[20] = {
{"GLY", {"CA", "N", "C", "O", "HA1", "HA2", "H", NULL}, {"HA3", "HA1", NULL}, 0xful},
{"ALA", {"CA", "N", "C", "O", "CB", "HB1", "HB2", "HB3", "HA", "H", NULL}, {NULL}, 0x1ful},
{"VAL", {"CA", "N", "C", "O", "CB", "HB", "CG1", "HG11", "HG12", "HG13", "CG2", "HG21", "HG22", "HG23", "HA", "H", NULL}, {NULL}, 0x45ful},
{"LEU", {"CA", "N", "C", "O", "CB", "HB1", "HB2", "CG", "HG", "CD1", "HD11", "HD12", "HD13", "CD2", "HD21", "HD22", "HD23", "HA", "H", NULL}, {"HB3", "HB1", NULL}, 0x229ful},
{"ILE", {"CA", "N", "C", "O", "CB", "HB", "CG2", "HG21", "HG22", "HG23", "CG1", "HG11", "HG12", "CD", "HD1", "HD2", "HD3", "HA", "H", NULL}, {"HG13", "HG11", "CD1", "CD", "HD11", "HD1", "HD12", "HD2", "HD13", "HD3", NULL}, 0x245ful},
{"PRO", {"CA", "N", "C", "O", "CD", "HD1", "HD2", "CG", "HG1", "HG2", "CB", "HB1", "HB2", "HA", NULL}, {"HB3", "HB1", "HG3", "HG1", "HD3", "HD1", NULL}, 0x49ful},
{"SER", {"CA", "N", "C", "O", "CB", "HB1", "HB2", "OG", "HG", "HA", "H", NULL}, {"HB3", "HB1", NULL}, 0x9ful},
{"THR", {"CA", "N", "C", "O", "CB", "HB", "CG2", "HG21", "HG22", "HG23", "OG1", "HG1", "HA", "H", NULL}, {NULL}, 0x45ful},
{"CYS", {"CA", "N", "C", "O", "CB", "HB1", "HB2", "SG", "HG", "HA", "H", NULL}, {"HB3", "HB1", NULL}, 0x9ful},
{"MET", {"CA", "N", "C", "O", "CB", "HB1", "HB2", "CG", "HG1", "HG2", "SD", "CE", "HE1", "HE2", "HE3", "HA", "H", NULL}, {"HB3", "HB1", "HG3", "HG1", NULL}, 0xc9ful},
{"ASN", {"CA", "N", "C", "O", "CB", "HB1", "HB2", "CG", "OD1", "ND2", "HD21", "HD22", "HA", "H", NULL}, {"HB3", "HB1", NULL}, 0x39ful},
{"GLN", {"CA", "N", "C", "O", "CB", "HB1", "HB2", "CG", "HG1", "HG2", "CD", "OE1", "NE2", "HE21", "HE22", "HA", "H", NULL}, {"HB3", "HB1", "HG3", "HG1", NULL}, 0x1c9ful},
{"ASP", {"CA", "N", "C", "O", "CB", "HB1", "HB2", "CG", "OD1", "OD2", "HA", "H", NULL}, {"HB3", "HB1", NULL}, 0x39ful},
{"GLU", {"CA", "N", "C", "O", "CB", "HB1", "HB2", "CG", "HG1", "HG2", "CD", "OE1", "OE2", "HA", "H", NULL}, {"HB3", "HB1", "HG3", "HG1", NULL}, 0x1c9ful},
{"LYS", {"CA", "N", "C", "O", "CB", "HB1", "HB2", "CG", "HG1", "HG2", "CD", "HD1", "HD2", "CE", "HE1", "HE2", "NZ", "HZ1", "HZ2", "HZ3", "HA", "H", NULL}, {"HB3", "HB1", "HG3", "HG1", "HD3", "HD1", "HE3", "HE1", NULL}, 0x1249ful},
{"ARG", {"CA", "N", "C", "O", "CB", "HB1", "HB2", "CG", "HG1", "HG2", "CD", "HD1", "HD2", "NE", "HE", "CZ", "NH1", "HH11", "HH12", "NH2", "HH21", "HH22", "HA", "H", NULL}, {"HB3", "HB1", "HG3", "HG1", "HD3", "HD1", NULL}, 0x9a49ful},
{"HIS", {"CA", "N", "C", "O", "CB", "HB1", "HB2", "CG", "ND1", "HD1", "CE1", "HE1", "NE2", "HE2", "CD2", "HD2", "HA", "H", NULL}, {"HB3", "HB1", NULL}, 0x559ful},
{"PHE", {"CA", "N", "C", "O", "CB", "HB1", "HB2", "CG", "CD1", "HD1", "CE1", "HE1", "CZ", "HZ", "CE2", "HE2", "CD2", "HD2", "HA", "H", NULL}, {"HB3", "HB1", NULL}, 0x1559ful},
{"TYR", {"CA", "N", "C", "O", "CB", "HB1", "HB2", "CG", "CD1", "HD1", "CE1", "HE1", "CZ", "OH", "HH", "CE2", "HE2", "CD2", "HD2", "HA", "H", NULL}, {"HB3", "HB1", NULL}, 0x2b59ful},
{"TRP", {"CA", "N", "C", "O", "CB", "HB1", "HB2", "CG", "CD1", "HD1", "NE1", "HE1", "CE2", "CZ2", "HZ2", "CH2", "HH2", "CZ3", "HZ3", "CE3", "HE3", "CD2", "HA", "H", NULL}, {"HB3", "HB1", NULL}, 0x2ab59ful}};


INLINE int pdbaaidx(const char *res)
{
  int i;
  if (strcmp(res, "HID") == 0 || strcmp(res, "HIE") == 0 || strcmp(res, "HIP") == 0)
    res = "HIS"; /* quick fix for HIS */
  for (i = 0; i < 20; i++)
    if (strcmp(res, pdb_aadb[i].resnm) == 0)
      return i;
  return -1;
}


INLINE const char *pdbaaname(int i)
{
  die_if (i < 0 || i >= 20, "invalid amino acid id %d\n", i);
  return pdb_aadb[i].resnm;
}


/* return the index of an atom from */
INLINE int pdbaagetaid(int aa, const char *atnm)
{
  int k;
  for (k = 0; pdb_aadb[aa].atom[k]; k++)
    if (strcmp(pdb_aadb[aa].atom[k], atnm) == 0) return k;
  return -1;
}


/* return the global atom index */
INLINE int pdbaar_getaid(pdbaar_t *r, const char *atnm)
{ int topid = pdbaagetaid(r->iaa, atnm); return (topid < 0) ? -1 : r->id[topid]; }

INLINE int pdbaac_getaid(pdbaac_t *c, int i, const char *atnm)
{ return pdbaar_getaid(c->res + i, atnm); }

/* return coordinates */
INLINE real *pdbaac_getx(pdbaac_t *c, int i, const char *atnm)
{ int id = pdbaac_getaid(c, i, atnm); return (id < 0) ? NULL : c->x[id]; }


/* format atom name, `out' can be same as `inp',
 * `style' can be
 * 0: atom name first:   "H",  "CB", "HE21"
 * 1: atom name first:  " H", " CB", "HE21"
 * 2: atom index first: " H", " CB", "1HE2" */
INLINE char *pdbm_fmtatom(char *out, const char *inp, int style)
{
  size_t n, i;
  char c, cn, atnm[5];
  const char *p;

  die_if (style > 2 || style < 0, "bad format style %d\n", style);

  /* copy `inp' to a buffer without space */
  for (p = inp; *p == ' '; p++) ; /* skip the leading spaces */
  for (n = 0; n < 4 && p[n] && p[n] != ' '; n++)
    atnm[n] = p[n]; /* copy without trailing spaces */
  atnm[n] = '\0';
  die_if (n == 4 && p[n] && p[n] != ' ',
      "bad input atom name [%s]\n", atnm);

  if (style <= 1) { /* style 0:  "H",  "CA", "HE21"
                       style 1: " H", " CA", "HE21" */
    if (n == 4) { /* four characters */
      c = atnm[0];
      if (isdigit(c)) { /* rotate the string: 1HE2 --> HE21; */
        for (i = 1; i < n; i++) out[i-1] = atnm[i];
        out[n-1] = c;
        out[n] = '\0';
      } else strcpy(out, atnm);
    } else { /* one to three characters */
      if (style == 0) {
        strcpy(out, atnm);
      } else { /* leave the first character blank */
        out[0] = ' ';
        strcpy(out+1, atnm);
      }
    }
  } else if (style == 2) { /* style 2: " H", " CA", "1HE2" */
    if (n == 4) { /* four characters */
      c = atnm[0];
      cn = atnm[n - 1];
      if (isalpha(c) && isdigit(cn)) { /* HE21 --> 1HE2 */
        for (i = n-1; i > 0; i--) out[i] = atnm[i-1];
        out[0] = cn;
        out[n] = '\0';
      } else strcpy(out, atnm);
    } else { /* n <= 3, leave the first character blank */
      out[0] = ' ';
      strcpy(out+1, atnm);
    }
  }
  return out;
}


/* switch the unit between angstrom and nanometer */
#define pdbm_a2nm(m)    pdbxswitchunit(m->x, m->natm, &m->unitnm, 0)
#define pdbm_nm2a(m)    pdbxswitchunit(m->x, m->natm, &m->unitnm, 1)
#define pdbaac_a2nm(c)  pdbxswitchunit(c->x, c->natm, &c->unitnm, 0)
#define pdbaac_nm2a(c)  pdbxswitchunit(c->x, c->natm, &c->unitnm, 1)

INLINE void pdbxswitchunit(rv3_t *x, int n, int *unitnm, int nm2a)
{
  die_if (nm2a != *unitnm,
    "unit corruption, nm2a %d, unitnm %d\n", nm2a, *unitnm);
  if (x != NULL) {
    real fac = (real)(nm2a ? 10.0 : 0.1);
    int i;

    for (i = 0; i < n; i++) rv3_smul(x[i], fac);
  }
  *unitnm = !(*unitnm); /* switch the unit */
}


/* read raw atom data from pdb */
INLINE pdbmodel_t *pdbm_readpdb(const char *fn)
{
  const int BSIZ = 256;
  FILE *fp;
  pdbmodel_t *m;
  pdbatom_t *atm;
  int i, ir;
  char s[256], resnm[8] = "";
  float x[3];

  xfopen(fp, fn, "r", return NULL);
  xnew(m, 1);
  m->natm = 0;
  m->nalloc = BSIZ;
  m->file = fn;
  xnew(m->atm, m->nalloc);
  xnew(m->x,   m->nalloc);
  /* read through pdb */
  ir = -1;
  while (fgets(s, sizeof s, fp)) {
    if (strncmp(s, "TER", 3) == 0 ||
        strncmp(s, "ENDMDL", 6) == 0 ||
        strncmp(s, "END", 3) == 0)
      break;
    if (strncmp(s, "ATOM ", 5) != 0)
      continue;
    if (s[16] != ' ' && s[16] != 'A') /* discard alternative position */
      continue;
    i = m->natm;
    if (i >= m->nalloc) {
      m->nalloc += BSIZ;
      xrenew(m->atm, m->nalloc);
      xrenew(m->x,   m->nalloc);
    }
    atm = m->atm + i;
    atm->aid = i;
    atm->insert = s[26];

    /* atom name */
    strip( substr(atm->atnm, s, 12, 4) );
    pdbm_fmtatom(atm->atnm, atm->atnm, 0);
    /* residue name */
    strip( substr(atm->resnm, s, 17, 3) );
    /* residue number */
    sscanf(s+22, "%d", &(atm->rid));
    if (ir == atm->rid && resnm[0] && strcmp(atm->resnm, resnm) != 0) {
      fprintf(stderr, "atom %d, %s, residue %d conflicts %s --> %s, file %s\n",
          i, atm->atnm, ir, resnm, atm->resnm, fn);
    }
    strcpy(resnm, atm->resnm);
    ir = atm->rid;
    /* coordinates */
    sscanf(s+30, "%f%f%f", x, x+1, x+2);
    rv3_make(m->x[i], x[0], x[1], x[2]);
    if (m->unitnm) rv3_smul(m->x[i], (real) 0.1);
    /* element name */
    atm->elem[0] = '\0';
    if (strlen(s) >= 78)
      strip( substr(atm->elem, s, 76, 2) );
    if (atm->elem[0] == '\0') { /* guess */
      atm->elem[0] = atm->atnm[0];
      atm->elem[1] = '\0';
    }
    m->natm++;
  }
  for (i = 0; i < m->natm; i++) /* set atom x */
    m->atm[i].x = m->x[i];
  fclose(fp);
  return m;
}


/* read from GROMACS .gro format */
INLINE pdbmodel_t *pdbm_readgro(const char *fn)
{
  FILE *fp;
  pdbmodel_t *m;
  pdbatom_t *atm;
  int i, ir;
  char s[256], resnm[8] = "";
  float x[3];

  xfopen(fp, fn, "r", return NULL);
  xnew(m, 1);
  if (fgets(s, sizeof s, fp) == NULL) { /* title line */
    fprintf(stderr, "cannot read the first line of %s\n", fn);
    goto ERR;
  }
  if (fgets(s, sizeof s, fp) == NULL) { /* number of particles */
    fprintf(stderr, "cannot read the second line of %s\n", fn);
    goto ERR;
  }
  if (1 != sscanf(s, "%d", &m->natm)) {
    fprintf(stderr, "no # of atoms, %s\n", fn);
    goto ERR;
  }
  m->nalloc = m->natm;
  m->file = fn;
  xnew(m->atm, m->nalloc);
  xnew(m->x,   m->nalloc);
  ir = -1;
  for (i = 0; i < m->natm; i++) {
    if (fgets(s, sizeof s, fp) == NULL) {
      fprintf(stderr, "unable to read atom %d\n", i+1);
      goto ERR;
    }
    atm = m->atm + i;
    atm->aid = i;

    /* atom name */
    strip( substr(atm->atnm, s, 10, 5) );
    pdbm_fmtatom(atm->atnm, atm->atnm, 0);
    /* residue name */
    strip( substr(atm->resnm, s, 5, 5) );
    /* residue number */
    sscanf(s, "%d", &atm->rid);
    if (ir == atm->rid && resnm[0] && strcmp(atm->resnm, resnm) != 0) {
      fprintf(stderr, "atom %d, %s, residue %d conflicts %s --> %s, file %s\n",
          i, atm->atnm, ir, resnm, atm->resnm, fn);
    }
    strcpy(resnm, atm->resnm);
    ir = atm->rid;
    /* coordinates */
    sscanf(s+20, "%f%f%f", x, x+1, x+2);
    rv3_make(m->x[i], x[0], x[1], x[2]);
    if (!m->unitnm) /* x 10 if the unit is nm */
      rv3_smul(m->x[i], (real) 10.);
    atm->x = m->x[i];
    /* guess element name */
    atm->elem[0] = atm->atnm[0];
    atm->elem[1] = '\0';
  }
  fclose(fp);
  return m;
ERR:
  free(m);
  fclose(fp);
  return NULL;
}


/* read pdb */
INLINE pdbmodel_t *pdbm_read(const char *fn, int verbose)
{
  int i, j, ir, iro;
  pdbmodel_t *m;
  const char *p;

  p = strrchr(fn, '.');
  if (p != NULL && strcmp(p + 1, "gro") == 0) {
    m = pdbm_readgro(fn);
  } else {
    m = pdbm_readpdb(fn);
  }
  if (m == NULL) return NULL;

  if (verbose)
    printf("%s has %d residues\n", fn, m->atm[m->natm-1].rid);

  /* sort residue indices */
  for (ir = 0, i = 0; i < m->natm; ir++) {
    iro = m->atm[i].rid;
    for (j = i; j < m->natm && m->atm[j].rid == iro &&
        strcmp(m->atm[j].resnm, m->atm[i].resnm) == 0; j++) {
      m->atm[j].rid = ir;
    }
    if (verbose >= 2)
      printf("atoms %d to %d --> residue %s, %d (%d)\n",
        i+1, j, m->atm[i].resnm, iro, ir+1);
    i = j;
  }
  m->nres = ir;

  if (verbose >= 3) /* dump the PDB */
    for (i = 0; i < m->natm; i++) {
      pdbatom_t *atm = m->atm + i;
      printf("%4d %4s %4d %4s %8.3f %8.3f %8.3f\n",
          atm->aid+1, atm->atnm, atm->rid+1, atm->resnm,
          atm->x[0], atm->x[1], atm->x[2]);
    }
  return m;
}


#define pdbm_free(m) pdbm_close(m)

INLINE void pdbm_close(pdbmodel_t *m)
{
  if (m->atm) free(m->atm);
  if (m->x) free(m->x);
  free(m);
}


/* write data to file fn */
INLINE int pdbm_write(pdbmodel_t *m, const char *fn)
{
  int i, aid, ATMFMT = 1;
  char atnm[8] = "";
  FILE *fp;
  pdbatom_t *atm;
  real x[3];

  if (m->natm <= 0) return 1;
  xfopen(fp, fn, "w", return 1);
  for (aid = 1, i = 0; i < m->natm; i++) {
    atm = m->atm + i;
    pdbm_fmtatom(atnm, atm->atnm, ATMFMT);
    rv3_copy(x, m->x[i]);
    if (m->unitnm) rv3_smul(x, (real) 10.);
    fprintf(fp, "ATOM  %5d %-4s %-4sA%4d    %8.3f%8.3f%8.3f  1.00  0.00          %2s  \n",
        aid++, atnm, atm->resnm, atm->rid+1, x[0], x[1], x[2], atm->elem);
  }
  fprintf(fp, "TER   %5d      %-4sA%4d%54s\n", m->natm+1, atm->resnm, atm->rid+1, "");
  fprintf(fp, "END%77s\n", " ");
  fclose(fp);
  return 0;
}


enum { PDB_CONTACT_CA, PDB_CONTACT_HEAVY, PDB_CONTACT_ALL }; /* ways of searching contacts */

INLINE int iscontactatom(int level, const char *atnm)
{
  if (level == PDB_CONTACT_ALL) return 1;
  else if (level == PDB_CONTACT_HEAVY) return atnm[0] != 'H';
  else return strcmp(atnm, "CA") == 0; /* PDB_CONTACT_CA */
}

/* return a nres x nres matrix that defines if two residues are contacts
 * a pair is considered as a contact only if the distance of two
 * specific-type atoms from the two residues is less than rc
 * 'level' : types of atoms to be used in defining atoms
 *           PDB_CONTACT_CA:      only alpha carbon atoms
 *           PDB_CONTACT_HEAVY:   non-hydrogen atoms
 *           PDB_CONTACT_ALL:     include hydrogen atoms
 * 'nearby': # of adjacent resdiues to be excluded from the list
 * */
INLINE int *pdbm_contact(pdbmodel_t *pm, double rc, int level, int nearby, int dbg)
{
  int ir, jr, i, j, im, jm, ica, jca, n = pm->natm, nres = pm->nres, ct, cnt = 0;
  pdbatom_t *atm = pm->atm;
  real d, dmin, dca;
  int *iscont;

  xnew(iscont, nres*nres);
  for (ir = 0; ir < nres; ir++) {
    for (jr = ir + nearby; jr < nres; jr++) {
      /* compute the minimal distance between atoms
       * in residues `ir' and `jr' of certain types */
      dmin = 1e9; dca = 0; im = jm = -1;
      /* loop through atoms to collect those of residue id `ir'
       * the loop is inefficient, but this function is rarely called */
      for (i = 0; i < n; i++) {
        if (atm[i].rid != ir) continue;
        if (!iscontactatom(level, atm[i].atnm)) continue;
        ica = iscontactatom(PDB_CONTACT_CA, atm[i].atnm);
        /* loop through atoms to collect those of residue id `jr' */
        for (j = 0; j < n; j++) {
          if (atm[j].rid != jr) continue;
          if (!iscontactatom(level, atm[j].atnm)) continue;
          jca = iscontactatom(PDB_CONTACT_CA, atm[j].atnm);
          d = rv3_dist(atm[i].x, atm[j].x);
          if (d < dmin) { dmin = d; im = i; jm = j; }
          if (ica && jca) dca = d; /* CA distance */
        }
      }
      iscont[ir*nres+jr] = iscont[jr*nres+ir] = ct = (dmin < rc) ? 1 : 0;
      if (ct) cnt++;
      if (dbg && ct) /* print decision */
        printf("[%3d] %s%-3d and %s%-3d: dca %6.3fA dmin %6.3fA (%s:%d, %s:%d)\n",
          cnt, atm[im].resnm, ir+1, atm[jm].resnm, jr+1, dca, dmin,
          atm[im].atnm, im+1, atm[jm].atnm, jm+1);
    }
  }
  return iscont;
}


/* build a `pdbacc_t' structure of amino-acid chain information
 * by parsing `m', which is `pdbmodel_t'
 * the coordinates are duplicated, and `m' can be freed afterwards */
INLINE pdbaac_t *pdbaac_parse(pdbmodel_t *m, int verbose)
{
  pdbatom_t *atm;
  pdbaac_t *c;
  pdbaar_t *r;
  int i, k, match;
  unsigned long hvflags;

  xnew(c, 1);
  c->nres = m->nres;
  c->natm = m->natm;
  xnew(c->res, c->nres);
  xnew(c->x, m->natm);
  memcpy(c->x, m->x, sizeof(*(c->x)) * m->natm); /* copy coordinates */
  c->unitnm = m->unitnm;
  c->file = m->file;

  for (i = 0; i < m->natm; i++) {
    atm = m->atm + i;
    r = c->res + atm->rid;
    r->iaa = pdbaaidx(atm->resnm);
    if (r->iaa < 0) {
      fprintf(stderr, "unknown amino acid residue %d/%d[%s]\n",
          atm->rid, m->nres, atm->resnm);
      goto ERR;
    }

    /* match index */
    match = 0;
    for (k = 0; pdb_aadb[r->iaa].atom[k] != NULL; k++) {
      if (strcmp(atm->atnm, pdb_aadb[r->iaa].atom[k]) == 0) {
        r->id[k] = i;
        r->flags |= 1ul << k;
        match = 1;
        break;
      }
    }
    if (!match) { /* check terminals */

#define AAMAPIT_(myif, str, nm) \
    myif (strcmp(atm->atnm, str) == 0) { \
      int aid = pdbaagetaid(r->iaa, #nm); \
      r->id[aid] = i; \
      r->flags |= 1ul << (unsigned long) aid; \
      match = 1; }

#define AAMATCH_(myif, str, nm) \
    myif (strcmp(atm->atnm, str) == 0) { \
      r->id[AA_ ## nm] = i; \
      r->flags |= 1ul << AA_##nm; \
      match = 1; }

      AAMAPIT_(if, "H1", H)
      AAMATCH_(else if, "H2",   H2)
      AAMATCH_(else if, "H3",   H3)
      AAMATCH_(else if, "OXT",  OXT)
      AAMAPIT_(else if, "OC1",  O)
      AAMATCH_(else if, "OC2",  OXT)
      AAMAPIT_(else if, "O1",   O)
      AAMATCH_(else if, "O2",   OXT)
      else { /* check substitutions */
        for (k = 0; pdb_aadb[r->iaa].sub[k] != NULL; k += 2)
          if (strcmp(atm->atnm, pdb_aadb[r->iaa].sub[k]) == 0) {
            int aid = pdbaagetaid(r->iaa, pdb_aadb[r->iaa].sub[k+1]);
            r->id[aid] = i;
            r->flags |= 1ul << (unsigned) aid;
            match = 1;
            break;
          }
      }
    }
    if (!match)
      printf("unknown atom %s:%d res %s%d\n",
          atm->atnm, i+1, atm->resnm, atm->rid+1);
  }

#define pdbaac_pmiss_(xflags) { \
  unsigned long miss = (r->flags ^ xflags) & xflags; \
  fprintf(stderr, "file %s, residue %s%d misses atom(s): ", \
          c->file, pdbaaname(r->iaa), i+1); \
  for (k = 0; pdb_aadb[r->iaa].atom[k] != NULL; k++) { \
    if (miss & (1ul << k)) \
      fprintf(stderr, "%s ", pdb_aadb[r->iaa].atom[k]); } \
  fprintf(stderr, "\n"); }

  /* checking integrity */
  for (i = 0; i < c->nres; i++) {
    r = c->res + i;
    hvflags = pdb_aadb[r->iaa].hvflags;
    if ((r->flags & AA_BACKBONE) != AA_BACKBONE) {
      pdbaac_pmiss_(AA_BACKBONE);
      goto ERR;
    } else if ((r->flags & hvflags) != hvflags) {
      pdbaac_pmiss_(hvflags);
    }
    r->xn  = pdbaac_x(c, i, N);
    r->xca = pdbaac_x(c, i, CA);
    r->xc  = pdbaac_x(c, i, C);
    r->xo  = pdbaac_x(c, i, O);
  }

  /* check bond-length, assume backbone are present */
  for (i = 0; i < c->nres; i++) {
    double x;
    r = c->res + i;
    if (i > 0) {
      x = rv3_dist(pdbaac_x(c, i-1, C), r->xn);
      if (c->unitnm) x *= 10.;
      if (x < .3 || x > 2.3) {
        if (verbose) {
          const char *aap = pdbaaname(c->res[i - 1].iaa);
          const char *aa = pdbaaname(r->iaa);
          fprintf(stderr, "%s: C-N bond between %d (%s) and %d (%s) is broken %g, insert break\n",
            c->file, i, aap, i+1, aa, x);
          goto ERR;
        }
      }
    }
    x = rv3_dist(r->xn, r->xca);
    if (c->unitnm) x *= 10.;
    if (x < .4 || x > 3.0) {
      if (verbose) {
        fprintf(stderr, "%s: N-CA bond of residue %d (%s) is broken %g\n",
          c->file, i+1, pdbaaname(r->iaa), x);
        fprintf(stderr, "N : %8.3f %8.3f %8.3f\n", r->xn[0], r->xn[1], r->xn[2]);
        fprintf(stderr, "CA: %8.3f %8.3f %8.3f\n", r->xca[0], r->xca[1], r->xca[2]);
      }
      goto ERR;
    }
    x = rv3_dist(r->xca, r->xc);
    if (c->unitnm) x *= 10.;
    if (x < .4 || x > 3.0) {
      if (verbose) {
        fprintf(stderr, "%s: CA-C bond of residue %d (%s) is broken %g\n",
          c->file, i+1, pdbaaname(r->iaa), x);
        fprintf(stderr, "CA: %8.3f %8.3f %8.3f\n", r->xca[0], r->xca[1], r->xca[2]);
        fprintf(stderr, "C : %8.3f %8.3f %8.3f\n", r->xc[0], r->xc[1], r->xc[2]);
      }
      goto ERR;
    }
  }
  if (verbose >= 3) {
    for (i = 0; i < c->nres; i++)
      printf("%4d: %s\n", i+1, pdbaaname(c->res[i].iaa));
  }

  return c;
ERR:
  free(c->res);
  free(c->x);
  free(c);
  return NULL;
}


/* create `pdbaac_t' from a PDB file */
INLINE pdbaac_t *pdbaac_open(const char *fn, int verbose)
{
  pdbmodel_t *m;
  pdbaac_t *c;

  m = pdbm_read(fn, verbose);
  c = pdbaac_parse(m, verbose);
  pdbm_free(m);
  return c;
}


#define pdbaac_free(c) pdbaac_close(c)

INLINE void pdbaac_close(pdbaac_t *c)
{
  if (c->res) free(c->res);
  if (c->x) free(c->x);
  free(c);
}


/* parse helices, return the number of helices `nse'
 * (*pse)[0..nse*2 - 1] are start and finishing indices of helices */
INLINE int pdbaac_parsehelices(pdbaac_t *c, int **pse)
{
  int i, nse = 0, is, it, nres = c->nres;
  int aa, aagly, aapro;
  int *se, *ishx, q[5];
  double phi, psi;

  /* A. make an array of nres, identify if each residue is helix */
  xnew(ishx, nres);
  ishx[0] = ishx[nres-1] = 0;
  for (i = 1; i < nres-1; i++) {
    /* make a local 5-tuple */
    die_if ((q[0] = pdbaac_getaid(c, i-1, "C"))  < 0, "no C  of %d\n", i-1);
    die_if ((q[1] = pdbaac_getaid(c, i,   "N"))  < 0, "no N  of %d\n", i);
    die_if ((q[2] = pdbaac_getaid(c, i,   "CA")) < 0, "no CA of %d\n", i);
    die_if ((q[3] = pdbaac_getaid(c, i,   "C"))  < 0, "no C  of %d\n", i);
    die_if ((q[4] = pdbaac_getaid(c, i+1, "N"))  < 0, "no N  of %d\n", i+1);
    phi = rv3_dih(c->x[ q[0] ], c->x[ q[1] ], c->x[ q[2] ], c->x[ q[3] ],
                  NULL, NULL, NULL, NULL);
    psi = rv3_dih(c->x[ q[1] ], c->x[ q[2] ], c->x[ q[3] ], c->x[ q[4] ],
                  NULL, NULL, NULL, NULL);
    ishx[i] = (phi < 0 && psi > -100*M_PI/180 && psi < 80*M_PI/180);
  }

  /* B. searching for segments
   * make 2*pro->ngrp for start/end of each segment
   * range of segment k is se[2*k] <= id < se[2*k+1] */
  xnew(se, 2);
  aagly = pdbaaidx("GLY");
  aapro = pdbaaidx("PRO");
  for (i = 0, is = 0; i < nres; ) { /* try to find the helices */
    while (i < nres && !ishx[i]) i++;
    if (i >= nres) break; /* no more helices */
    is = i;
    while (ishx[i] && i < nres) i++;
    it = i;
    for (; is < it; is++) { /* skip terminal GLY and PRO */
      aa = c->res[is].iaa;
      if (aa != aagly && aa != aapro)  break;
    }
    for (; it > is; it--) {
      aa = c->res[it - 1].iaa;
      if (aa != aagly && aa != aapro) break;
    }
    if (it - is >= 4) { /* successfully find a helical segment */
      xrenew(se, 2*(nse+1));
      se[2*nse] = is;
      se[2*nse+1] = it;
      nse++;
    } else { } /* just let go, don't increment nse */
  }
  free(ishx);
  *pse = se;
  return nse;
}


#endif /* ZCOM_PDB__ */
#endif /* ZCOM_PDB */





#ifdef  ZCOM_MD
#ifndef ZCOM_MD__
#define ZCOM_MD__

#define md_shiftcom(x, n, d) md_shiftcomw(x, NULL, n, d)
#define md_shiftcom3d(x, n) md_shiftcomw3d(x, NULL, n)
#define md_shiftcom2d(x, n) md_shiftcomw2d(x, NULL, n)

INLINE void md_shiftcomw(real * RESTRICT x, const real * RESTRICT w, int n, int d);
/* these two are inline instead macros because they offer type checks */
INLINE void md_shiftcomw2d(rv2_t * RESTRICT x, const real * RESTRICT w, int n)
  { md_shiftcomw((real *) x, w, n, 2); }
INLINE void md_shiftcomw3d(rv3_t * RESTRICT x, const real * RESTRICT w, int n)
  { md_shiftcomw((real *) x, w, n, 3); }

INLINE void md_shiftang2d(rv2_t * RESTRICT x, rv2_t * RESTRICT v, int n);
INLINE void md_shiftang3d(rv3_t * RESTRICT x, rv3_t * RESTRICT v, int n);
INLINE void md_shiftang(real * RESTRICT x, real * RESTRICT v, int n, int d)
{
  if (d == 2) md_shiftang2d((rv2_t *) x, (rv2_t *) v, n);
  else md_shiftang3d((rv3_t *) x, (rv3_t *) v, n);
}


INLINE real md_ekin(const real *v, int nd, int dof, real * RESTRICT tkin);
INLINE real md_ekin2d(rv2_t * RESTRICT v, int n, int dof, real * RESTRICT tkin)
  { return md_ekin((const real *) v, n*2, dof, tkin); }
INLINE real md_ekin3d(rv3_t * RESTRICT v, int n, int dof, real * RESTRICT tkin)
  { return md_ekin((const real *) v, n*3, dof, tkin); }


INLINE void md_vscale(real * RESTRICT v, int nd, int dof, real tp, real ekt, real * RESTRICT ekin, real * RESTRICT tkin);
INLINE void md_vscale2d(rv2_t * RESTRICT v, int n, int dof, real tp, real ekt, real * RESTRICT ekin, real * RESTRICT tkin)
  { md_vscale((real *) v, n*2, dof, tp, ekt, ekin, tkin); }
INLINE void md_vscale3d(rv3_t * RESTRICT v, int n, int dof, real tp, real ekt, real * RESTRICT ekin, real * RESTRICT tkin)
  { md_vscale((real *) v, n*3, dof, tp, ekt, ekin, tkin); }


INLINE void md_vrescale(real * RESTRICT v, int nd, int dof, real tp, real dt, real * RESTRICT ekin, real * RESTRICT tkin);
INLINE void md_vrescale2d(rv2_t * RESTRICT v, int n, int dof, real tp, real dt, real * RESTRICT ekin, real * RESTRICT tkin)
  { md_vrescale((real *) v, n*2, dof, tp, dt, ekin, tkin); }
INLINE void md_vrescale3d(rv3_t * RESTRICT v, int n, int dof, real tp, real dt, real * RESTRICT ekin, real * RESTRICT tkin)
  { md_vrescale((real *) v, n*3, dof, tp, dt, ekin, tkin); }


INLINE void md_vrescalex(real * RESTRICT v, int nd, int dof, real tp, real dt, real * RESTRICT ekin, real * RESTRICT tkin);
INLINE void md_vrescalex2d(rv2_t * RESTRICT v, int n, int dof, real tp, real dt, real * RESTRICT ekin, real * RESTRICT tkin)
  { md_vrescalex((real *) v, n*2, dof, tp, dt, ekin, tkin); }
INLINE void md_vrescalex3d(rv3_t * RESTRICT v, int n, int dof, real tp, real dt, real * RESTRICT ekin, real * RESTRICT tkin)
  { md_vrescalex((real *) v, n*3, dof, tp, dt, ekin, tkin); }


/* shift the center of mass to zero */
INLINE void md_shiftcomw(real * RESTRICT x, const real * RESTRICT w, int n, int d)
{
  int i, j;
  real rc, wtot = 0;

  if (w) for (i = 0; i < n; i++) wtot += w[i];
  else wtot = (real) n;
  for (j = 0; j < d; j++) {
    for (rc = 0, i = 0; i < n; i++)
      rc += x[i*d+j]*(w ? w[i] : 1.f);
    rc /= wtot;
    for (i = 0; i < n; i++)
      x[i*d+j] -= rc;
  }
}


/* annihilate the total angular momentum, 2d */
INLINE void md_shiftang2d(rv2_t * RESTRICT x, rv2_t * RESTRICT v, int n)
{
  int i;
  real am, r2, xc[2] = {0, 0}, xi[2];

  for (i = 0; i < n; i++) rv2_inc(xc, x[i]);
  rv2_smul(xc, 1.f/n);
  for (am = r2 = 0.f, i = 0; i < n; i++) {
    rv2_diff(xi, x[i], xc);
    am += rv2_cross(xi, v[i]);
    r2 += rv2_sqr(x[i]);
  }
  am = -am/r2;
  for (i = 0; i < n; i++) {
    rv2_diff(xi, x[i], xc);
    v[i][0] += -am*xi[1];
    v[i][1] +=  am*xi[0];
  }
}


/* annihilate the total angular momentum, 3d
 * solve
 *   /  y^2 + z^2    -x y      -x y      \
 *   |  -x y       X^2 + z^2   -y z      |  c  =  I
 *   \  -x z         -y z     x^2 + y^2  /
 * use a velocity field
 *    v = c X r
 *   */

INLINE void md_shiftang3d(rv3_t *x, rv3_t *v, int n)
{
  int i;
  real xc[3] = {0, 0, 0}, xi[3], ang[3], am[3] = {0, 0, 0}, dv[3], mat[3][3], inv[3][3];
  real xx = 0, yy = 0, zz = 0, xy = 0, zx = 0, yz = 0;

  for (i = 0; i < n; i++) rv3_inc(xc, x[i]);
  rv3_smul(xc, 1.f/n);
  for (i = 0; i < n; i++) {
    rv3_diff(xi, x[i], xc);
    rv3_cross(ang, xi, v[i]);
    rv3_inc(am, ang);
    xx += xi[0]*xi[0];
    yy += xi[1]*xi[1];
    zz += xi[2]*xi[2];
    xy += xi[0]*xi[1];
    yz += xi[1]*xi[2];
    zx += xi[2]*xi[0];
  }
  mat[0][0] = yy+zz;
  mat[1][1] = xx+zz;
  mat[2][2] = xx+yy;
  mat[0][1] = mat[1][0] = -xy;
  mat[1][2] = mat[2][1] = -yz;
  mat[0][2] = mat[2][0] = -zx;
  rm3_inv(inv, mat);
  ang[0] = -rv3_dot(inv[0], am);
  ang[1] = -rv3_dot(inv[1], am);
  ang[2] = -rv3_dot(inv[2], am);
  /* ang is the solution of M^(-1) * I */
  for (i = 0; i < n; i++) {
    rv3_diff(xi, x[i], xc);
    rv3_cross(dv, ang, xi);
    rv3_inc(v[i], dv);
  }
}


/* return kinetic energy */
INLINE real md_ekin(const real *v, int nd, int dof, real *tkin)
{
  int i;
  real ekin;

  for (ekin = 0, i = 0; i < nd; i++) ekin += v[i]*v[i];
  if (tkin) *tkin = ekin/dof;
  return ekin *= .5f;
}


/* compute the kinetic energy for the thermostats, if ekin != NULL */
INLINE real md_getekin(real *ekin, const real *v, int nd)
{
  int i;
  real ek;

  if (ekin) {
    ek = *ekin;
  } else {
    for (ek = 0, i = 0; i < nd; i++) ek += v[i] * v[i];
    ek *= 0.5f;
  }
  return ek;
}


/* velocity scaling: for regular (no thermostat) MD during equilibration
 * `tp' is the target temperature
 * `ekt' is the observed average kinetic energy, may not be the current *ekin  */
INLINE void md_vscale(real *v, int nd, int dof, real tp, real ekt, real *ekin, real *tkin)
{
  int i;
  real ekav = .5f*tp*dof, s;

  s = (real) sqrt( ekav / ekt );
  for (i = 0; i < nd; i++)
    v[i] *= s;
  if (ekin) *ekin *= s*s;
  if (tkin) *tkin *= s*s;
}


/* velocity rescaling thermostat */
INLINE void md_vrescale(real *v, int nd, int dof, real tp, real dt, real *ekin, real *tkin)
{
  int i;
  real ekav = .5f*tp*dof, ek1, ek2, s;
  double amp;

  ek1 = md_getekin(ekin, v, nd);
  amp = 2 * sqrt(ek1 * ekav * dt / dof);
  ek2 = ek1 + (ekav - ek1) * dt + (real) (amp * randgaus());
  if (ek2 < 0) ek2 = 0;
  s = (real) sqrt(ek2/ek1);
  for (i = 0; i < nd; i++)
    v[i] *= s;
  if (ekin) *ekin = ek2;
  if (tkin) *tkin *= s*s;
}


/* Exact velocity rescaling thermostat */
INLINE void md_vrescalex(real *v, int nd, int dof, real tp, real dt, real *ekin, real *tkin)
{
  int i;
  real ekav = .5f*tp*dof, ek1, ek2, s, c = 0, r, r2;

  if (dt < 10) c = (real) exp(-dt);
  ek1 = md_getekin(ekin, v, nd);
  r = (real) randgaus();
  r2 = (real) randchisqr(dof - 1);
  ek2 = (real)( ek1 + (1 - c) * (ekav*(r2 + r*r)/dof - ek1)
    + 2 * r * sqrt(c*(1 - c) * ekav/dof*ek1) );
  if (ek2 < 0) ek2 = 0;
  s = (real) sqrt(ek2/ek1);
  for (i = 0; i < nd; i++)
    v[i] *= s;
  if (ekin) *ekin = ek2;
  if (tkin) *tkin *= s*s;
}


/* backup thermostat: velocity-rescaling according to a Monte-Carlo move */
INLINE int md_mcvrescale(real *v, int nd, int dof, real tp, real dt, real *ekin, real *tkin)
{
  int i, acc;
  real ek1, ek2, s;
  double logek1, logek2, r, r0;

  ek1 = md_getekin(ekin, v, nd);
  logek1 = log(ek1);
  logek2 = logek1 + dt*(2.f*rand01() - 1);
  ek2 = (real) exp(logek2);
  r = (ek2 - ek1)/tp - .5*dof*(logek2 - logek1);
  if (r <= 0) {
    acc = 1;
  } else {
    r0 = rand01();
    acc = (r0 < exp(-r));
  }
  if ( acc ) {
    s = (real) sqrt(ek2/ek1);
    for (i = 0; i < nd; i++)
      v[i] *= s;
    if (ekin) *ekin = ek2;
    if (tkin) *tkin *= s*s;
  }
  return acc;
}


INLINE int md_mcvrescale2d(rv2_t * RESTRICT v, int n, int dof, real tp, real dt, real * RESTRICT ekin, real * RESTRICT tkin)
  { return md_mcvrescale((real *) v, n*2, dof, tp, dt, ekin, tkin); }
INLINE int md_mcvrescale3d(rv3_t * RESTRICT v, int n, int dof, real tp, real dt, real * RESTRICT ekin, real * RESTRICT tkin)
  { return md_mcvrescale((real *) v, n*3, dof, tp, dt, ekin, tkin); }


/* Nose-Hoover thermostat */
INLINE void md_hoover(real *v, int nd, int dof, real tp, real dt,
    real *zeta, real Q, real *ekin, real *tkin)
{
  int i;
  real ek1, ek2, s, dt2 = .5f*dt;

  ek1 = md_getekin(ekin, v, nd);
  *zeta += (2.f*ek1 - dof * tp)/Q*dt2;

  s = (real) exp(-(*zeta)*dt);
  for (i = 0; i < nd; i++) v[i] *= s;
  ek2 = ek1 * (s*s);
  if (ekin) *ekin = ek2;
  if (tkin) *tkin *= s*s;

  *zeta += (2.f*ek2 - dof * tp)/Q*dt2;
}


INLINE void md_hoover2d(rv2_t *v, int n, int dof, real tp, real dt,
    real *zeta, real Q, real *ekin, real *tkin)
  { md_hoover((real *) v, n*2, dof, tp, dt, zeta, Q, ekin, tkin); }

INLINE void md_hoover3d(rv3_t *v, int n, int dof, real tp, real dt,
    real *zeta, real Q, real *ekin, real *tkin)
  { md_hoover((real *) v, n*3, dof, tp, dt, zeta, Q, ekin, tkin); }


/* Nose-Hoover chain thermostat */
INLINE void md_nhchain(real *v, int nd, int dof, real tp, real scl, real dt,
    real *zeta, const real *Q, int M, real *ekin, real *tkin)
{
  int i, j;
  real ek1, ek2, s, dt2 = .5f*dt, dt4 = .25f*dt, G, xp = 1.f;

  ek1 = md_getekin(ekin, v, nd);

  /* propagate the chain */
  for (j = M-1; j > 0; j--) {
    if (j < M-1) {
      xp = (real) exp(-dt4 * zeta[j+1]);
      zeta[j] *= xp;
    }
    G = (Q[j-1]*zeta[j-1]*zeta[j-1] - tp)/Q[j];
    zeta[j] += G * dt2;
    if (j < M-1)
      zeta[j] *= xp;
  }

  /* the first thermostat variable */
  if (M >= 2) {
    xp = (real) exp(-dt4 * zeta[1]);
    zeta[0] *= xp;
  }
  G = (scl * 2.f * ek1 - dof * tp)/Q[0];
  zeta[0] += G * dt2;
  if (M >= 2)
    zeta[0] *= xp;

  /* scale the velocities */
  s = (real) exp(-(*zeta)*dt);
  for (i = 0; i < nd; i++) v[i] *= s;
  ek2 = ek1 * (s*s);
  if (ekin) *ekin = ek2;
  if (tkin) *tkin *= s*s;

  /* the first thermostat variable */
  if (M >= 2) {
    xp = (real) exp(-dt4*zeta[1]);
    zeta[0] *= xp;
  }
  G = (scl * 2.f * ek1 - dof * tp)/Q[0];
  zeta[0] += G * dt2;
  if (M >= 2)
    zeta[0] *= xp;

  /* propagate the chain */
  for (j = M-1; j > 0; j--) {
    if (j < M-1) {
      xp = (real) exp(-dt4*zeta[j+1]);
      zeta[j] *= xp;
    }
    G = (Q[j-1]*zeta[j-1]*zeta[j-1] - tp)/Q[j];
    zeta[j] += G * dt2;
    if (j < M-1)
      zeta[j] *= xp;
  }
}


INLINE void md_nhchain2d(rv3_t *v, int n, int dof, real tp, real scl, real dt,
    real *zeta, const real *Q, int M, real *ekin, real *tkin)
  { md_nhchain((real *) v, n*2, dof, tp, scl, dt, zeta, Q, M, ekin, tkin); }

INLINE void md_nhchain3d(rv3_t *v, int n, int dof, real tp, real scl, real dt,
    real *zeta, const real *Q, int M, real *ekin, real *tkin)
  { md_nhchain((real *) v, n*3, dof, tp, scl, dt, zeta, Q, M, ekin, tkin); }


/* velocity-scaling Langevin thermostat */
INLINE void md_vslang(real *v, int nd, int dof, real tp, real dt,
    real *zeta, real zeta2, real Q, real *ekin, real *tkin)
{
  int i;
  real ek1, ek2, s, dt2 = .5f*dt, xp, amp;

  ek1 = md_getekin(ekin, v, nd);
  xp = (real) exp(-zeta2*.25*dt);
  amp = (real) sqrt(2*zeta2/Q*dt2);
  *zeta *= xp;
  *zeta += (2.f*ek1 - dof * tp)/Q*dt2;
  *zeta += amp * (real) randgaus(); /* white noise */
  *zeta *= xp;

  s = (real) exp(-(*zeta)*dt);
  for (i = 0; i < nd; i++) v[i] *= s;
  ek2 = ek1 * (s*s);
  if (ekin) *ekin = ek2;
  if (tkin) *tkin *= s*s;

  *zeta *= xp;
  *zeta += (2.f*ek2 - dof * tp)/Q*dt2;
  *zeta += amp * (real) randgaus(); /* white noise */
  *zeta *= xp;
}


INLINE void md_vslang2d(rv2_t *v, int n, int dof, real tp, real dt,
    real *zeta, real zeta2, real Q, real *ekin, real *tkin)
  { md_vslang((real *) v, n*2, dof, tp, dt, zeta, zeta2, Q, ekin, tkin); }

INLINE void md_vslang3d(rv3_t *v, int n, int dof, real tp, real dt,
    real *zeta, real zeta2, real Q, real *ekin, real *tkin)
  { md_vslang((real *) v, n*3, dof, tp, dt, zeta, zeta2, Q, ekin, tkin); }


/* Anderson thermostat */
INLINE void md_andersen(real *v, int n, int d, real tp)
{
  int i, j;

  tp = (real) sqrt(tp);
  i = (int)(rand01() * n);
  for (j = 0; j < d; j++)
    v[i*d + j] = tp * (real) randgaus();
}


/* Langevin thermostat */
INLINE void md_langevin(real *v, int n, int d, real tp, real dt)
{
  int i;
  real c = (real) exp(-dt), amp;

  amp = (real) sqrt((1 - c*c) * tp);
  for (i = 0; i < n*d; i++)
    v[i] = c*v[i] + amp * (real) randgaus();
}


/* Nose-Hoover thermostat/barostat
 * set cutoff to half of the box */
INLINE void md_hoovertp(real *v, int n, int d, int dof, real dt,
    real tp, real pext, real *zeta, real *eta, real Q, real W,
    real vol, real vir, real ptail, int ensx,
    real *ekin, real *tkin)
{
  int i;
  real xp, pint, s, dt2 = dt*.5f, dt4 = dt*.25f;

  /* thermostat */
  *zeta += (2.f * (*ekin) + W * (*eta) * (*eta) - (dof + 1) * tp) * dt2/Q;
  xp = (real) exp(-(*zeta)*dt4); /* zeta won't change until the end */

  /* barostat */
  *eta *= xp;
  pint = (vir + 2.f * (*ekin))/ (d * vol) + ptail;
  *eta += ((pint - pext)*vol + (1 - ensx) * tp)*d*dt2/W;
  *eta *= xp;

  /* scaling velocity */
  s = (real) exp( -dt * (*zeta + *eta) );
  for (i = 0; i < d * n; i++) v[i] *= s;
  *ekin *= s*s;
  *tkin *= s*s;

  /* barostat */
  *eta *= xp;
  pint = (vir + 2.f * (*ekin))/ (d * vol) + ptail;
  *eta += ((pint - pext)*vol + (1 - ensx) * tp)*d*dt2/W;
  *eta *= xp;

  /* thermostat */
  *zeta += (2.f * (*ekin) + W * (*eta) * (*eta) - (dof + 1) * tp) * dt2/Q;
}


/* Nose-Hoover chain thermostat/barostat
 * set cutoff to half of the box */
INLINE void md_nhchaintp(real *v, int n, int d, int dof, real dt,
    real tp, real pext, real *zeta, real *eta, const real *Q, int M, real W,
    real vol, real vir, real ptail, int ensx,
    real *ekin, real *tkin)
{
  int i, j;
  real xpz, pint, s, dt2 = dt*.5f, dt4 = dt*.25f, G, xp;

  /* 1. thermostat */
  /* 1.A propagate the chain */
  for (j = M-1; j > 0; j--) {
    if (j < M-1) {
      xp = (real) exp(-dt4*zeta[j+1]);
      zeta[j] *= xp;
    }
    G = (Q[j-1]*zeta[j-1]*zeta[j-1] - tp)/Q[j];
    zeta[j] += G * dt2;
    if (j < M-1)
      zeta[j] *= xp;
  }

  /* 1.B the first thermostat variable */
  if (M >= 2) {
    xp = (real) exp(-dt4*zeta[1]);
    zeta[0] *= xp;
  }
  G = (2.f * (*ekin) + W * (*eta) * (*eta) - (dof + 1) * tp) / Q[0];
  zeta[0] += G * dt2;
  if (M >= 2)
    zeta[0] *= xp;
  xpz = (real) exp(-zeta[0]*dt4); /* zeta won't change until the end */

  /* 2. barostat */
  *eta *= xpz;
  pint = (vir + 2.f * (*ekin))/ (d * vol) + ptail;
  *eta += ((pint - pext)*vol + (1 - ensx) * tp)*d*dt2/W;
  *eta *= xpz;

  /* 3. scaling velocity */
  s = (real) exp( -dt * (zeta[0] + *eta) );
  for (i = 0; i < d * n; i++) v[i] *= s;
  *ekin *= s*s;
  *tkin *= s*s;

  /* 4. barostat */
  *eta *= xpz;
  pint = (vir + 2.f * (*ekin))/ (d * vol) + ptail;
  *eta += ((pint - pext)*vol + (1 - ensx) * tp)*d*dt2/W;
  *eta *= xpz;

  /* 5. thermostat */
  /* 5.A the first thermostat variable */
  if (M >= 2) {
    xp = (real) exp(-dt4*zeta[1]);
    zeta[0] *= xp;
  }
  G = (2.f * (*ekin) + W * (*eta) * (*eta) - (dof + 1) * tp) / Q[0];
  zeta[0] += G * dt2;
  if (M >= 2)
    zeta[0] *= xp;

  /* 5.B propagate the chain */
  for (j = M-1; j > 0; j--) {
    if (j < M-1) {
      xp = (real) exp(-dt4*zeta[j+1]);
      zeta[j] *= xp;
    }
    G = (Q[j-1]*zeta[j-1]*zeta[j-1] - tp)/Q[j];
    zeta[j] += G * dt2;
    if (j < M-1)
      zeta[j] *= xp;
  }
}


/* Langevin barostat
 *   d eta / dt = -zeta * eta
 *      + [ (Pint - Pext) * V + (1 - ensx) T ] * d / W
 *      + sqrt( 2 * zeta * T / W ) xi
 * the ideal-gas part of the pressure, Pint, is computed as \sum p^2/m / V
 * the additional volume distribution weight is V^(-ensx)
 * the scaling is r = r*s, p = p/s;
 * set the cutoff rc to half of the box */
INLINE void md_langtp(real *v, int n, int d, real dt,
    real tp, real pext, real zeta, real *eta, real W,
    real vol, real vir, real ptail, int ensx,
    real *ekin, real *tkin)
{
  int i;
  real xp, pint, s, dt2 = dt*.5f, dt4 = dt*.25f, amp;

  xp = (real) exp(-zeta*dt4);
  amp = (real) sqrt(2.f*zeta*tp/W*dt2);

  /* barostat: first half to update *eta */
  *eta *= xp;
  pint = (vir + 2.f * (*ekin))/ (d * vol) + ptail;
  *eta += ((pint - pext)*vol + (1 - ensx) * tp)*d*dt2/W;
  *eta += amp * (real) randgaus(); /* random noise */
  *eta *= xp;

  /* scaling velocity */
  s = (real) exp( -dt * (*eta) );
  for (i = 0; i < d * n; i++) v[i] *= s;
  *ekin *= s*s;
  *tkin *= s*s;

  /* barostat: second half to update *eta */
  *eta *= xp;
  pint = (vir + 2.f * (*ekin))/ (d * vol) + ptail;
  *eta += ((pint - pext)*vol + (1 - ensx) * tp)*d*dt2/W;
  *eta += amp * (real) randgaus(); /* random noise */
  *eta *= xp;
}


/* position Langevin barostat
 * limiting case, zeta -> inf., of the full Langevin barostat
 * barodt = dt/(W*zeta), and d * d(eta) = d lnv
 * the ideal-gas part of the pressure is computed as \sum p^2/m / V
 * the scaling is r = r*s, p = p/s;
 * set cutoff to half of the box */
INLINE void md_langtp0(real *v, int n, int d, real barodt,
    real tp, real pext, real *vol, real vir, real ptail, int ensx,
    real *ekin, real *tkin)
{
  int i;
  real pint, amp, vn, s, dlnv;

  /* compute the internal pressure */
  /* note only with half-box cutoff, the formula is accurate */
  pint = (vir + 2.f * (*ekin))/ (d * (*vol)) + ptail;

  amp = (real) sqrt(2.f * barodt);
  dlnv = ((pint - pext) * (*vol)/tp + 1 - ensx)*barodt
       + amp * (real) randgaus();
  vn = *vol * (real) exp( dlnv );

  s = (real) exp( dlnv/d );
  for (i = 0; i < d * n; i++) v[i] *= s;
  *ekin *= s*s;
  *tkin *= s*s;

  *vol = vn;
}


/* position Langevin barostat, with coordinates only
 * NOTE: the first parameter is the degree of freedom
 * the scaling is r = r*s
 * set cutoff to half of the box */
INLINE void md_langp0(int dof, int d, real barodt,
    real tp, real pext, real *vol, real vir, real ptail, int ensx)
{
  real pintv, amp, dlnv;

  pintv = (vir + dof * tp)/d + ptail * (*vol);
  amp = (real) sqrt(2 * barodt);
  dlnv = ((pintv - pext * (*vol))/tp + 1 - ensx)*barodt
       + amp * (real) randgaus();
  *vol *= (real) exp( dlnv );
}


/* sinc(x) = (e^x - e^(-x))/(2 x) */
INLINE double md_mysinc(double x)
{
  double x2, y;

  if (fabs(x) < 1e-2) { /* series expansion */
    x2 = x * x;
    return 1 + (1 + (1 + x2/42.0)*x2/20.0)*x2/6.0;
  }
  y = exp(x);
  return .5 * (y - 1./y)/x;
}


/* Nose-Hoover position update */
INLINE void md_hoovertpdr(real *r, const real *v, int nd,
    real *xp, real l, real eta, real dt)
{
  int i;
  real dtxp, xph, etadt2;

  /* r' = r*exp(eta*dt) + v*(exp(eta*dt) - 1)/eta
   * now exp(eta*dt) is the volume scaling factor
   * so for the reduced coordinates R = r*exp(-eta*dt)
   * R' = R + v*(1 - exp(-eta*dt))/eta; */
  etadt2 = eta * dt * .5f;
  xph = (real) exp(etadt2);
  *xp = xph * xph;
  dtxp = 1.f/xph * dt * (real) md_mysinc(etadt2) / l;
/*
  dtxp = (1 - 1/(*xp))/eta/l;
*/
  for (i = 0; i < nd; i++)
    r[i] += v[i] * dtxp;
}


#define md_mutv2d(v, n, tp, r) md_mutv((real *)(rv2_t *)v, n * 2, tp, r)
#define md_mutv3d(v, n, tp, r) md_mutv((real *)(rv3_t *)v, n * 3, tp, r)

/* mutate velocities with the probability of r */
INLINE int md_mutv(real *v, int nd, real tp, double r)
{
  int i;
  real vamp = (real) sqrt(tp);

  for (i = 0; i < nd; i++)
    if (rand01() < r)
      v[i] = vamp * (real) randgaus();
  return 0;
}


/* multiply velocities by a random unitary matrix */
INLINE int md_unimatv3d(rv3_t *v, int n)
{
  int i;
  real mat[3][3], v1[3];

  rm3_randuni(mat);
  for (i = 0; i < n; i++) {
    rm3_mulvec(v1, mat, v[i]);
    rv3_copy(v[i], v1);
  }
  return 0;
}


/* write a position file */
INLINE int md_writepos(FILE *fp, const real *x, const real *v, int n,
    int d, real scl)
{
  int i, j;

  for (i = 0; i < n; i++) {
    for (j = 0; j < d; j++) fprintf(fp, "%16.14f ", x[i*d + j] * scl);
    if (v)
      for (j = 0; j < d; j++) fprintf(fp, "%16.14f ", v[i*d + j]);
    fprintf(fp, "\n");
  }
  return 0;
}

INLINE int md_writepos2d(FILE *fp, rv2_t *x, rv2_t *v, int n, real scl)
{
  return md_writepos(fp, (const real *) x, (const real *) v, n, 2, scl);
}

INLINE int md_writepos3d(FILE *fp, rv3_t *x, rv3_t *v, int n, real scl)
{
  return md_writepos(fp, (const real *) x, (const real *) v, n, 3, scl);
}


/* read position */
INLINE int md_readpos(FILE *fp, real *x, real *v, int n, int d, real scl)
{
  const char *fmt;
  char s[256], *p;
  int i, j, next;
  real *x0, *v0, xtmp;

  fmt = (sizeof(double) == sizeof(real)) ? "%lf%n" : "%f%n";
  /* back up the current coordinates and velocities, in case of failure */
  xnew(x0, n * d);
  memcpy(x0, x, sizeof(real) * n * d);
  if (v) {
    xnew(v0, n * d);
    memcpy(v0, v, sizeof(real) * n * d);
  }
  for (i = 0; i < n; i++) {
    if (fgets(s, sizeof s, fp) == NULL) goto ERR;
    for (p = s, j = 0; j < d; j++, p += next) {
      if (1 != sscanf(p, fmt, &xtmp, &next)) {
        fprintf(stderr, "cannot read i = %d, j = %d\n", i, j);
        goto ERR;
      }
      x[i*d + j] = xtmp / scl;
    }
    if (v != NULL) {
      for (j = 0; j < d; j++, p += next)
        if (1 != sscanf(p, fmt, v + i*d + j, &next)) {
          fprintf(stderr, "cannot read i = %d, j = %d\n", i, j);
          goto ERR;
        }
    }
  }
  free(x0);
  if (v) free(v0);
  return 0;
ERR:
  fprintf(stderr, "pos file broken on line %d!\n%s\n", i, s);
  /* recover the original coordinates and velocities */
  memcpy(x, x0, n * d * sizeof(real));
  free(x0);
  if (v) {
    memcpy(v, v0, n * d * sizeof(real));
    free(v0);
  }
  return -1;
}

INLINE int md_readpos2d(FILE *fp, rv2_t *x, rv2_t *v, int n, real scl)
{
  return md_readpos(fp, (real *) x, (real *) v, n, 2, scl);
}

INLINE int md_readpos3d(FILE *fp, rv3_t *x, rv3_t *v, int n, real scl)
{
  return md_readpos(fp, (real *) x, (real *) v, n, 3, scl);
}


#endif /* ZCOM_MD__ */
#endif /* ZCOM_MD */





#ifdef  ZCOM_HMC
#ifndef ZCOM_HMC__
#define ZCOM_HMC__

typedef struct {
  int nd;
  real *x, *v, *f;
} hmc_t;


/* the macro versions may accept rv2_t and rv3_t */
#define hmc_push(h, x, v, f) \
  hmc_push_(h, (real *) x, (real *) v, (real *) f)

#define hmc_pop(h, x, v, f, vinv) \
  hmc_pop_(h, (real *) x, (real *) v, (real *) f, vinv)

#define hmc_open(nd, x, v, f) \
  hmc_open_(nd, (real *) x, (real *) v, (real *) f)

#define hmc_open2d(n, x, v, f) hmc_open(n*2, x, v, f)
#define hmc_open3d(n, x, v, f) hmc_open(n*3, x, v, f)

#define HMC_INVERTV 0x0001

/* save x, v, f as the new start point */
INLINE void hmc_push_(hmc_t *h, real *x, real *v, real *f)
{
  memcpy(h->x, x, h->nd * sizeof(real));
  memcpy(h->v, v, h->nd * sizeof(real));
  memcpy(h->f, f, h->nd * sizeof(real));
}


/* set x, v, f from the saved start point */
INLINE void hmc_pop_(hmc_t *h, real *x, real *v, real *f, unsigned flags)
{
  int i, nd = h->nd;

  /* invert velocities */
  if (flags & HMC_INVERTV) {
    for (i = 0; i < nd; i++) h->v[i] = -h->v[i];
  }
  memcpy(x, h->x, nd * sizeof(real));
  memcpy(v, h->v, nd * sizeof(real));
  memcpy(f, h->f, nd * sizeof(real));
}


/* open a hmc object from the start point */
INLINE hmc_t *hmc_open_(int nd, real *x, real *v, real *f)
{
  hmc_t *h;

  xnew(h, 1);
  h->nd = nd;
  xnew(h->x, nd);
  xnew(h->v, nd);
  xnew(h->f, nd);
  hmc_push(h, x, v, f);
  return h;
}


INLINE void hmc_close(hmc_t *h)
{
  free(h->x);
  free(h->v);
  free(h->f);
  free(h);
}


/* compute the reduce-momentum-flipping rate
 * J. Sohl-Dickstein, arXiv 1205.1939
 * the Metropolis probability of accepting x => x+ is min{1, exp(-dep)}
 * that of accepting x~ => x-~ is min{1, exp(-dem)}
 * where `~' means the momentum reversal operation */
INLINE int hmcgetredvflipr(double dem, double dep)
{
  double xp1, xp2;

  die_if (dep <= 0, "the forward move must be rejected, dep %g\n", dep);
  /* 1. If the state x-, hence x-~, has higher energy than x+
   * dem >= dep, then x-~ is more likely rejected, and x~ should
   * inject probability into x; thus, there is no need to flip x
   * 2. We now have dem < dep.  We also have dep > 0, for x => x+
   * has been rejected. If dem <= 0, x~ => x-~ is definitely accepted,
   * then x should compensate the probability outflow of x~ and be flipped
   * 3. The only case left is 0 < dem < dep */
  if ( dem >= dep ) return 0;
  if ( dem <= 0 ) return 1;
  xp1 = exp(dep - dem);
  xp2 = exp(dep);
  return rand01() < (xp1 - 1)/(xp2 - 1);
}

#endif /* ZCOM_HMC__ */
#endif /* ZCOM_HMC */





#ifdef  ZCOM_ISING2
#ifndef ZCOM_ISING2__
#define ZCOM_ISING2__
/* two-dimensional Ising model */


typedef struct {
  int d, l, n;
  int M, E;
  int *s; /* 0 or 1 */
  double *logdos; /* logarithmic density of states */
  /* helper vars */
  uint32_t *uproba; /* temporary probability for MC transitions */
} ising_t;


/* set transition probability */
#define IS2_SETPROBA(is, bet) { \
  double x_ = exp(-4. * bet); \
  is->uproba[2] = (uint32_t) ((double)(0xffffffff) * x_); \
  is->uproba[4] = (uint32_t) ((double)(0xffffffff) * x_*x_); }


/* compute total energy and magnetization */
INLINE int is2_em(ising_t *is)
{
  int l, i, j, s, u, e, m, *p, *pu;

  e = m = 0;
  p = is->s;
  l = is->l;
  for (i = 0; i < l; ) {
    pu = (++i == l) ? is->s : p+l;
    for (j = 0; j < l; ) {
      m += (s = *p++);
      u = *pu++;
      e += s*(u + ((++j == l) ? *(p-l) : *p));
    }
  }
  is->M = m;
  return is->E = -e;
}


INLINE int is2_check(ising_t *is)
{
  int i, e, m;

  for (i = 0; i < is->n; i++)
    if (is->s[i] != 1 && is->s[i] != -1) {
      fprintf(stderr, "error: s[%d] = %d\n", i, is->s[i]);
      return -1;
    }
  e = is->E;
  m = is->M;
  is2_em(is);
  if  (e != is->E || e < -2*is->n || e > 2*is->n
    || m != is->M || m < -is->n   || m > is->n) {
    fprintf(stderr, "error: E = %d, %d; M = %d, %d\n",
        e, is->E, m, is->M);
    return -1;
  }
  return 0;
}


/* pick a random site, count neighbors with different spins */
INLINE int is2_pick(const ising_t *is, int *h)
{
  int id, ix, iy, l, lm, n, nm, *p;

  lm = (l = is->l) - 1;
  nm = (n = is->n) - l;
  id = (int) (rand01() * n);
  iy = id / l, ix = id % l;
  p = is->s + id;
  *h = *p * ( ((ix != 0 ) ? *(p-1) : *(p+lm))   /* left  */
            + ((ix != lm) ? *(p+1) : *(p-lm))   /* right */
            + ((iy != 0 ) ? *(p-l) : *(p+nm))   /* down  */
            + ((iy != lm) ? *(p+l) : *(p-nm))); /* up    */
  return id;
}


/* flip site id, with h different neighbors */
INLINE int is2_flip(ising_t *is, int id, int h)
{
  die_if(id >= is->n, "bad id %d/%d\n", id, is->n);
  is->M += (is->s[id] = -is->s[id])*2;
  return is->E += h*2;
}


/* faster macros for systems with fixed (upon compiling) size
 * to use them one must define IS2_LB before including
 * IS2_PICK()/IS2_PSEQ() and IS2_FLIP() */
#ifdef  IS2_LB  /* L = 2^LB, N = L*L */
#define IS2_L   (1 << IS2_LB)
#define IS2_N   (IS2_L * IS2_L)

#define IS2_GETH(is, id, h) { \
  unsigned ix, iy; \
  iy = id / IS2_L, ix = id % IS2_L; \
  h = is->s[id] * ( is->s[iy*IS2_L + (ix+1)%IS2_L] \
                  + is->s[iy*IS2_L + (ix+IS2_L-1)%IS2_L] \
                  + is->s[(iy+1)%IS2_L*IS2_L + ix] \
                  + is->s[(iy-1+IS2_L)%IS2_L*IS2_L + ix] ); }
#define IS2_IRND(is, id)  id = rand32() >> (32 - 2*IS2_LB);
/* random picking */
#define IS2_PICK(is, id, h) { IS2_IRND(is, id); IS2_GETH(is, id, h); }
#define IS2_ISEQ(is, id)  id = (id + 1) % IS2_N;
/* sequential picking */
#define IS2_PSEQ(is, id, h) { IS2_ISEQ(is, id); IS2_GETH(is, id, h); }

#define IS2_FLIP(is, id, h) { \
  is->M += (is->s[id] = -is->s[id]) * 2; \
  is->E += h * 2; }

#else

#define IS2_PICK(is, id, h)  id = is2_pick(is, &h)
#define IS2_FLIP(is, id, h)  is2_flip(is, id, h)

#endif


INLINE int is2_load(ising_t *is, const char *fname)
{
  FILE *fp;
  int i, lx, ly, n, c;
  char s[80];

  xfopen(fp, fname, "r", return -1);
  if (fgets(s, sizeof s, fp) == NULL) {
    fprintf(stderr, "missing first line %s\n", fname);
    fclose(fp);
    return -1;
  }
  if (4 != sscanf(s, "%d%d%d%d", &i, &lx, &ly, &n)
      || i != 2 || lx != ly || lx != is->l || n != is->n) {
    fprintf(stderr, "bad setting: %dD, %dx%d = %d\n", i, lx, ly, n);
    return -1;
  }
  for (i = 0; i < n; i++) {
    while ((c = fgetc(fp)) != EOF && c == '\n') ;
    if (c == EOF) break;
    is->s[i] = (c == ' ') ? -1 : 1;
  }
  if (i < n)
    fprintf(stderr, "%s: data stopped at i = %d\n", fname, i);
  fclose(fp);
  is2_em(is);
  return 0;
}


INLINE int is2_save(const ising_t *is, const char *fname)
{
  FILE *fp;
  int i, j, l, *p;

  xfopen(fp, fname, "w", return -1);
  l = is->l;
  fprintf(fp, "%d %d %d %d\n", is->d, l, l, is->n);
  for (p = is->s, i = 0; i < l; i++) {
    for (j = 0; j < l; j++, p++)
      fprintf(fp, "%c", (*p > 0) ? '#' : ' ');
    fprintf(fp, "\n");
  }
  fclose(fp);
  return 0;
}


/* initialize an lxl Ising model */
INLINE ising_t *is2_open(int l)
{
  int i, n;
  ising_t *is;

  xnew(is, 1);
  is->d = 2;
  is->l = l;
  is->n = n = l*l;
  xnew(is->s, n);
  for (i = 0; i < n; i++) is->s[i] = -1;
  is->M = -n;
  is->E = -2*n;
  xnew(is->logdos, n + 1);
  xnew(is->uproba, 2*is->d+1);
  is->uproba[0] = 0xffffffff;
  return is;
}


INLINE void is2_close(ising_t *is)
{
  if (is != NULL) {
    free(is->s);
    free(is->logdos);
    free(is->uproba);
    free(is);
  }
}


/* exact solution of ising model */
INLINE double is2_exact(ising_t *is, double beta, double *eav, double *cv)
{
  double lxh, n, ex, f, th, sech, bet2, bsqr, log2, x;
  double lnz, lnz1, lnz2, lnz3, lnz4, dz, ddz;
  double z21, z31, z41, za1;
  double dr1, dr2, dr3, dr4, ddr1, ddr2, ddr3, ddr4;
  double g, g0, dg, ddg, dg0;
  double xn2b, sh2b, coth2b;
  double lnch2b, lncc2b, lncl, lnsl, cd, cdsqr, lnddcl;
  int r, sgn4 = 1, lx, ly;

  lx = is->l;
  ly = is->l;
  lxh = .5*lx;
  n = lx * ly;
  log2 = log(2.0);
  bet2 = 2.*beta;
  bsqr = beta*beta;
  xn2b = exp(-bet2);
  if (lx == 2 && ly == 2) { /* 2x2 system */
    double lnc, lnd;
    x = 8.*beta;
    lnc = lnadd(x, -x);
    lnd = lnaddn(lnc, 6.);
    lnz = lnd + log2;
    if (eav) *eav = -8.*exp(lndif(x, -x) - lnd); /* -8*sinh(8*b)/(3+cosh(8*h)) */
    if (cv) *cv = bsqr * 384. * exp(lnaddn(lnc, 2./3) - 2.0*lnd); /* 64*(1+3cosh(8*b))/(3+cosh(8*b))^2 */
    return lnz;
  } else if (fabs(beta) < 1e-6) { /* high T approx. normal branch unstable if beta < 1e-6 */
    lnz = n * (2.*lnadd(beta, -beta) - log2);
    x = 1. + xn2b;
    if (eav) *eav = -2. * n * (1. - xn2b)/x;
    if (cv) *cv = bsqr * 8.*n*xn2b/(x*x);
    return lnz; /* +n*tanh(beta)^4 */
  }

  lnz1 = lnz2 = lnz3 = lnz4 = 0;
  dr1 = dr2 = dr3 = dr4 = 0;
  ddr1 = ddr2 = ddr3 = ddr4 = 0;
  lnch2b = lnadd(bet2, -bet2) - log2;
  coth2b = 2./(1. - xn2b*xn2b) - 1.;
  lncc2b = lnch2b + log(coth2b); /* ln[ cosh(2b) * coth(2b) ] */
  g0 = bet2 + log(2./(1. + xn2b) - 1.);
  sgn4 = (g0 >= 0) ? 1 : -1;

  sh2b = 0.5*(1./xn2b - xn2b);
  dg0 = 2. + 2./sh2b;
  x = sh2b*sh2b;
  cd = 2. - 2./x; /* cl' = cd * cosh(2b) */
  cdsqr = cd*cd;
  lnddcl = lnaddn(lncc2b, 2.0/(x * sh2b)) + 2.*log2; /* log(cl'') */

  for (r = 0; r < ly; r++) { /* for odd number */
    lncl = lnaddn(lncc2b, -cos((2.*r + 1.)*M_PI/ly));
    lnsl = lncl + 0.5*log(1. - exp(-2.*lncl));
    g = lnadd(lncl, lnsl);
    f = lxh*g;
    lnz1 += lnadd(f, -f);
    lnz2 += lndif(f, -f);

    dg = exp(lnch2b - lnsl)*cd; /* g' = cl'/sl; */
    ex = exp(-f);
    th = 2./(1. + ex*ex) - 1.;
    x = lxh*dg;
    dr1 += x*th;
    dr2 += x/th;

    /* g''=cl''/sl - cl' ^2 *cl/sl^3; */
    ddg = exp(lnddcl - lnsl);
    ddg -= exp(lnch2b*2. + lncl - 3.*lnsl)*cdsqr;
    sech = 2.0*dg/(ex + 1.0/ex); /* g' * sech(0.5*lx*g) */
    ddr1 += lxh*(ddg*th + lxh*(sech*sech));
    sech = 2.0*dg/(ex - 1.0/ex); /* g' * sech(0.5*lx*g) */
    ddr2 += lxh*(ddg/th - lxh*(sech*sech));

    if (r == 0) {
      g = g0;
    } else {
      lncl = lnaddn(lncc2b, -cos(2.0*M_PI*r/ly));
      lnsl = lncl+0.5*log(1-exp(-2*lncl));
      g = lnadd(lncl, lnsl);
      die_if (g < 0.0, "g = %g < 0.\n", g);;
    }
    f = lxh*g;
    lnz3 += lnadd(f, -f); /* log [2 cosh(f)] */
    lnz4 += (f < 0) ? lndif(-f, f) : lndif(f, -f); /* avoid neg. g0 */

    ex = exp(-f);
    th = 2./(1. + ex*ex) - 1.;
    dg = (r == 0) ? dg0 : exp(lnch2b - lnsl)*cd;
    dr3 += lxh*dg*th;
    dr4 += lxh*dg/th;

    if (r == 0) {
      ddg = -4*coth2b*coth2b*exp(-lnch2b);
    } else {
      ddg = exp(lnddcl - lnsl);
      ddg -= exp(lnch2b*2. + lncl - 3.*lnsl)*cdsqr;
    }
    sech = 2.0*dg/(ex + 1.0/ex);
    ddr3 += lxh*(ddg*th + lxh*(sech*sech));
    sech = 2.0*dg/(ex - 1.0/ex);
    ddr4 += lxh*(ddg/th - lxh*(sech*sech));
  }

  z21 = exp(lnz2 - lnz1);
  z31 = exp(lnz3 - lnz1);
  z41 = sgn4*exp(lnz4 - lnz1);
  za1 = 1.0 + z21 + z31 + z41;
  lnz = lnz1 + log(za1);
  lnz += .5*n*log(2.*sh2b) - log2;
  dz = (dr1 + z21*dr2 + z31*dr3 + z41*dr4)/za1;
  if (eav) *eav = - n*coth2b - dz;
  ddr1 += dr1*dr1;
  ddr2 += dr2*dr2;
  ddr3 += dr3*dr3;
  ddr4 += dr4*dr4;
  ddz = (ddr1 + z21*ddr2 + z31*ddr3 + z41*ddr4)/za1;
  if (cv) *cv = bsqr * (-2.*n/(sh2b*sh2b) + ddz - dz*dz);
  return lnz;
}


#define is2_loadlogdos(is, fn) \
  is2loadlogdos(is->logdos, is->l, is->l, fn)

/* load the exact logarithmic density of states from file
 * both n and m should be is->l
 * Minimal Mathematica script to generate exact DOS files

NDOS[m_, n_] := Module[{x, xp, prec = Floor[1.5 n m Log[2]/Log[10]], b, a, c2, s2, c0, s0, cn, sn},
  b = 2 x (1 - x^2);
  a[k_] := (1 + x^2)^2 - b Cos[Pi k/n];
  c0 = (1 - x)^m + x^m (1 + x)^m;
  s0 = (1 - x)^m - x^m (1 + x)^m;
  cn = (1 + x)^m + x^m (1 - x)^m;
  sn = (1 + x)^m - x^m (1 - x)^m;
  c2[k_] := (Sum[ m!/(2 j)!/(m - 2 j)! (a[k]^2 - b^2)^j a[k]^(m - 2 j), {j, 0, IntegerPart[m/2]}] + b^m)/2^(m - 1);
  s2[k_] := (Sum[ m!/(2 j)!/(m - 2 j)! (a[k]^2 - b^2)^j a[k]^(m - 2 j), {j, 0, IntegerPart[m/2]}] - b^m)/2^(m - 1);
  xp = Expand[ N[ (1/2) If[Mod[n, 2] == 0,
    Product[c2[2 k + 1], {k, 0, n/2 - 1}]
  + Product[s2[2 k + 1], {k, 0, n/2 - 1}]
  + c0 cn Product[c2[2 k], {k, 1, n/2 - 1}]
  + s0 sn Product[s2[2 k], {k, 1, n/2 - 1}],
    cn Product[c2[2 k + 1], {k, 0, (n - 3)/2}]
  + sn Product[s2[2 k + 1], {k, 0, (n - 3)/2}]
  + c0 Product[c2[2 k], {k, 1, (n - 1)/2}]
  + s0 Product[s2[2 k], {k, 1, (n - 1)/2}]], prec]];
  Take[Round[Chop[CoefficientList[xp, x]]], {1, -1, 2}]];

savels[fn_, ls_] := Module[{fp = OpenWrite[fn], i},
  For[i = 1, i <= Length[ls], i++, Write[fp, ls[[i]]]]; Close[fp]];

easydos[n_, m_] := Module[{dos = NDOS[n, m], logdos = Table[0, {n m + 1}], i},
  savels["IsingDOS" <> ToString[n] <> "x" <> ToString[m] <> ".txt", dos];
  For[i = 1, i <= n m + 1, i++,
    logdos[[i]] = If[dos[[i]] == 0, -10000, N[Log[dos[[i]]], 17]]];
  savels["islogdos" <> ToString[n] <> "x" <> ToString[m] <> ".txt", logdos]];
  */
INLINE int is2loadlogdos(double *logdos, int n, int m, const char *fn)
{
  char s[1024];
  FILE *fp;
  int i, err = 0;

  if (fn == NULL) { /* use standard file name */
    sprintf(s, "islogdos%dx%d.txt", n, m);
    fn = s;
  }
  xfopen(fp, fn, "r", return -1);

  for (i = 0; i <= n*m;  i++) {
    if (fgets(s, sizeof s, fp) == NULL) {
      printf("file %s ended at line %d/%d\n", fn, i, n*m);
      err = 1;
      break;
    }
    if (1 != sscanf(s, "%lf", &logdos[i])) {
      printf("sscanf failed in reading %s, line %d/%d\n", fn, i, n*m);
      err = 2;
      break;
    }
  }
  fclose(fp);
  return err;
}

#endif /* ZCOM_ISING2__ */
#endif /* ZCOM_ISING2 */





#ifdef  ZCOM_POTTS2
#ifndef ZCOM_POTTS2__
#define ZCOM_POTTS2__
/* two-dimensional Potts model */

typedef struct {
  int d; /* dimension */
  int q; /* number of states of each spin */
  int l, n;
  int E;  /* potential energy */
  int *M; /* M[0..q-1] number of spins in each state */
  int *s; /* s[0..n-1], each s[i] in 0..q-1 */
  /* helper vars */
  double *accprb; /* temporary accumulated probabilities, for heat bath */
  uint32_t *uproba; /* temporary probability for MC transitions */
  double *dproba;
} potts_t;


#define PT2_SETPROBA(pt, bet) { \
  double x_ = exp(-bet), prd_; \
  prd_  = x_; pt->dproba[1] = prd_; pt->uproba[1] = (uint32_t) (4294967295. * prd_); \
  prd_ *= x_; pt->dproba[2] = prd_; pt->uproba[2] = (uint32_t) (4294967295. * prd_); \
  prd_ *= x_; pt->dproba[3] = prd_; pt->uproba[3] = (uint32_t) (4294967295. * prd_); \
  prd_ *= x_; pt->dproba[4] = prd_; pt->uproba[4] = (uint32_t) (4294967295. * prd_); \
}


/* faster macros for systems with fixed (upon compiling) size
 * to use them one must define PT2_LB and PT2_Q before including
 * PT2_PICK()/PT2_PSEQ() and PT2_FLIP() */
#ifdef  PT2_LB  /* L = 2^LB, N = L*L */
#define PT2_L   (1 << PT2_LB)
#define PT2_N   (PT2_L * PT2_L)

#define PT2_GETH(pt, id, h) { \
  unsigned ix, iy; \
  for (ix = 0; ix < PT2_Q; ix++) h[ix] = 0; \
  iy = id / PT2_L, ix = id % PT2_L; \
  h[ pt->s[iy*PT2_L + (ix+1)%PT2_L]       ]++; \
  h[ pt->s[iy*PT2_L + (ix+PT2_L-1)%PT2_L] ]++; \
  h[ pt->s[(iy+1)%PT2_L*PT2_L + ix]       ]++; \
  h[ pt->s[(iy-1+PT2_L)%PT2_L*PT2_L + ix] ]++; }
#define PT2_IRND(pt, id)  id = rand32() >> (32 - 2*PT2_LB);
/* random pick */
#define PT2_PICK(pt, id, h) { PT2_IRND(pt, id); PT2_GETH(pt, id, h); }
#define PT2_ISEQ(pt, id)  id = (id + 1) % PT2_N;
/* sequential pick */
#define PT2_PSEQ(pt, id, h) { PT2_ISEQ(pt, id); PT2_GETH(pt, id, h); }

/* change spin id from so to sn (use PT2_Q instead of pt->q) */
#define PT2_NEWFACE(pt, id, so, sn) { \
  so = pt->s[id]; sn = (so + 1 + (int) (rand01() * (PT2_Q - 1))) % PT2_Q; }

/* change spin id from so to sn according to heat bath algorithm
 * local accprb is somehow faster */
#define PT2_HEATBATH(pt, id, so, sn, h) { \
  static double accprb[PT2_Q+1] = {0.,}; double rs_; \
  so = pt->s[id]; \
  for (sn = 0; sn < PT2_Q; sn++) accprb[sn+1] = accprb[sn] + pt->dproba[4-h[sn]]; \
  for (rs_ = accprb[PT2_Q] * rand01(), sn = 0; sn < PT2_Q; sn++) if (accprb[sn+1] > rs_) break; \
}

#define PT2_FLIP(pt, id, so, sn, h) { \
  pt->s[id] = sn; \
  pt->M[so]--; \
  pt->M[sn]++; \
  pt->E += h[so] - h[sn];  }

#else  /* non-macro version */

#define PT2_PICK(pt, id, h)  id = pt2_pick(pt, h)
#define PT2_NEWFACE(pt, id, so, sn) { \
  so = pt->s[id]; sn = (so + 1 + (int) (rand01() * (pt->q - 1))) % (pt->q); }
#define PT2_HEATBATH(pt, id, so, sn, h) \
  pt2_heatbath(pt, id, &so, &sn, h)
#define PT2_FLIP(pt, id, so, sn, h) {so = pt->s[id]; pt2_flip(pt, id, sn, h); }

INLINE int pt2_pick(const potts_t *pt, int h[])
{
  int i, id, ix, iy, l, lm, n, nm, *p;
  int sl, sr, sd, su;

  lm = (l = pt->l) - 1;
  nm = (n = pt->n) - l;
  id = (int) (rand01() * n);
  iy = id / l, ix = id % l;
  p = pt->s + id;
  for (i = 0; i < pt->q; i++) h[i] = 0;
  sl = ((ix != 0 ) ? *(p-1) : *(p+lm)); h[sl]++;
  sr = ((ix != lm) ? *(p+1) : *(p-lm)); h[sr]++;
  sd = ((iy != 0 ) ? *(p-l) : *(p+nm)); h[sd]++;
  su = ((iy != lm) ? *(p+l) : *(p-nm)); h[su]++;
  return id;
}


INLINE int pt2_heatbath(potts_t *pt, int id, int *so, int *sn,
    const int h[])
{
  double rs_;
  int i, mx_ = 4;
  *so = pt->s[id];
  for (i = 0; i < pt->q; i++)
    pt->accprb[i+1] = pt->accprb[i] + pt->dproba[mx_-h[i]];
  for (rs_ = pt->accprb[pt->q] * rand01(), i = 0; i < pt->q; i++)
    if (pt->accprb[i+1] > rs_) break;
  die_if (i >= pt->q, "no suitable selection, i = %d\n", i);
  *sn = i;
  return 0;
}


/* flip site `id' to `sn', with h different neighbors */
INLINE int pt2_flip(potts_t *pt, int id, int sn, const int h[])
{
  int so = pt->s[id];
  die_if(id >= pt->n, "id %d >= n %d\n", id, pt->n);
  die_if(sn >= pt->q || sn < 0, "invalid sn %d (q = %d)\n", sn, pt->q);
  pt->s[id] = sn;
  pt->M[so]--;
  pt->M[sn]++;
  return pt->E += h[so] - h[sn];
}

#endif /* PT2_LB */


/* compute the total energy and magnetization */
INLINE int pt2_em(potts_t *pt)
{
  int i, j, l, s, s1, s2, *p;

  pt->E = 0;
  p = pt->s;
  l = pt->l;
  for (i = 0; i < pt->q; i++) pt->M[i] = 0;
  for (i = 0; i < l; i++)
    for (j = 0; j < l; j++) {
      s = p[i*l + j];
      s1 = p[((i+1)%l)*l + j];
      if (s1 == s) pt->E--;
      s2 = p[i*l + (j+1)%l];
      if (s2 == s) pt->E--;
      pt->M[s]++;
    }
  return pt->E;
}


/* check */
INLINE int pt2_check(potts_t *pt)
{
  int i, e, *mg, q = pt->q;

  for (i = 0; i < pt->n; i++) /* check spin value */
    die_if (pt->s[i] < 0 || pt->s[i] >= q, "s[%d] %d, q %d\n", i, pt->s[i], q);
  e = pt->E;
  xnew(mg, q);
  for (i = 0; i < q; i++) mg[i] = pt->M[i];
  die_if (e != pt2_em(pt), "error: E = %d, should be %d\n", e, pt->E);
  for (i = 0; i < q; i++)
    die_if (mg[i] != pt->M[i], "error: M(%d) = %d, should be %d", i, mg[i], pt->M[i]);
  free(mg);
  return 0;
}


/* pick a random site (return its id)
 * compute h[j], the numbers of neighboring spins with value j */
/* load spin configuration */
INLINE int pt2_load(potts_t *pt, const char *fname)
{
  FILE *fp;
  int i, lx, ly, n, c;
  char s[80];

  xfopen(fp, fname, "r", return -1);
  if (fgets(s, sizeof s, fp) == NULL) {
    fprintf(stderr, "missing first line %s\n", fname);
    fclose(fp);
    return -1;
  }
  if (4 != sscanf(s, "%d%d%d%d", &i, &lx, &ly, &n)
      || i != 2 || lx != ly || lx != pt->l || n != pt->n) {
    fprintf(stderr, "bad setting: %dD, %dx%d = %d\n", i, lx, ly, n);
    return -1;
  }
  for (i = 0; i < n; i++) {
    while ((c = fgetc(fp)) != EOF && c == '\n') ;
    if (c == EOF) break;
    c -= '0';
    if (c < 0 || c >= pt->q) {
      fprintf(stderr, "BAD %s s[%d] = %d, q = %d\n", fname, i, c, pt->q);
      break;
    }
    pt->s[i] = c;
  }
  if (i < n) {
    fprintf(stderr, "%s: data stopped at i = %d, clear\n", fname, i);
    for (i = 0; i < n; i++) pt->s[i] = 0;
  }
  fclose(fp);
  pt2_em(pt); /* re-compute energy/magnetization */
  return 0;
}


/* save spin configuration */
INLINE int pt2_save(const potts_t *pt, const char *fname)
{
  FILE *fp;
  int i, j, l, *p;

  xfopen(fp, fname, "w", return -1);
  l = pt->l;
  fprintf(fp, "%d %d %d %d\n", pt->d, l, l, pt->n);
  for (p = pt->s, i = 0; i < l; i++) {
    for (j = 0; j < l; j++, p++)
      fprintf(fp, "%c", *p+'0');
    fprintf(fp, "\n");
  }
  fclose(fp);
  return 0;
}


/* initialize an lxl q-state Potts model */
INLINE potts_t *pt2_open(int l, int q)
{
  int i, n;
  potts_t *pt;

  xnew(pt, 1);
  pt->d = 2;
  pt->q = q;
  pt->l = l;
  pt->n = n = l*l;
  xnew(pt->s, n);
  xnew(pt->M, q);
  for (i = 0; i < n; i++)
    pt->s[i] = 0;
  for (pt->M[0] = n, i = 1; i < q; i++)
    pt->M[i] = 0;
  pt->E = -pt->d * n;
  xnew(pt->accprb, q+1);
  pt->accprb[0] = 0.;
  /* dynamic array of uproba/dproba seems to be faster */
  xnew(pt->uproba, 2*pt->d+1);
  pt->uproba[0] = 0xffffffffu;
  xnew(pt->dproba, 2*pt->d+1);
  pt->dproba[0] = 1.;
  return pt;
}


INLINE void pt2_close(potts_t *pt)
{
  if (pt != NULL) {
    free(pt->s);
    free(pt->M);
    free(pt->accprb);
    free(pt->uproba);
    free(pt->dproba);
    free(pt);
  }
}

#endif /* ZCOM_POTTS2__ */
#endif /* ZCOM_POTTS2 */





#ifdef  ZCOM_LJ
#ifndef ZCOM_LJ__
#define ZCOM_LJ__

typedef struct {
  int i, j, in;
  real phi, psi, xi, dx[3], dr2;
} ljpair_t;


#define LJ_SWALLPAIRS 0x100 /* flag of usesw, save all (including out-of-range) pairs */

typedef struct {
  int d; /* dimension = 3 */
  int n; /* number of particles */
  int dof; /* degrees of freedom */

  real rho;
  real l, vol; /* side length and volume */
  real rc2, rc, rcdef; /* real / preferred rc */

  real * RESTRICT x; /* reduced unit (0, 1) */
  real * RESTRICT v, * RESTRICT f;
  real epot0, epot, epots; /* potential energy: pure, with tail correction and shifted potential energy */
  int iepot;  /* integer energy for square-well potential */
  real ekin, tkin, etot;
  real vir; /* virial */
  real epot_shift, epot_tail, p_tail;

  int usesw; /* switched potential */
  real rs, a4, a5, a6, a7; /* parameters */
  ljpair_t *pr;
  int npr;
  real lap, f2, *gdg, *xdg;

  int usesq; /* square well potential */
  int esqinf;
  real ra, ra2, rb, rb2; /* -1 for (ra, rb) */
  real rmin; /* minimal pair distance */

  unsigned isclone; /* is a clone copy, don't free pointers */
} lj_t;

INLINE real lj_energy(lj_t *lj);
INLINE real lj_force(lj_t *lj);

#define lj_shiftcom(lj, v)    md_shiftcom(v, lj->n, lj->d)
#define lj_shiftang(lj, x, v) md_shiftang(x, v, lj->n, lj->d)


/* initialize a fcc lattice */
INLINE void lj_initfcc2d(lj_t *lj)
{
  int i, j, id, n1, n = lj->n;
  real a, noise;

  n1 = (int) (pow(2*n, 1.0/lj->d) + .999999); /* # of particles per side */
  a = 1.f/n1;
  noise = a * 0.00001f;
  for (id = 0, i = 0; i < n1 && id < n; i++)
    for (j = 0; j < n1 && id < n; j++) {
      if ((i+j) % 2 != 0) continue;
      /* add some noise to prevent two particles separated
       * by precisely the cutoff distance, which can be
       * half of the box size */
      lj->x[id*2 + 0] = (i + .5f) * a + randunif(-noise, noise);
      lj->x[id*2 + 1] = (j + .5f) * a + randunif(-noise, noise);
      id++;
    }
}


/* initialize a fcc lattice */
INLINE void lj_initfcc3d(lj_t *lj)
{
  int i, j, k, id, n1, n = lj->n;
  real a, noise;

  n1 = (int) (pow(2*n, 1.0/lj->d) + .999999); /* # of particles per side */
  a = 1.f/n1;
  noise = a * 0.00001f;
  for (id = 0, i = 0; i < n1 && id < n; i++)
    for (j = 0; j < n1 && id < n; j++)
      for (k = 0; k < n1 && id < n; k++) {
        if ((i+j+k) % 2 != 0) continue;
        /* add some noise to prevent two particles separated
         * by precisely the cutoff distance, which can be
         * half of the box size */
        lj->x[id*3 + 0] = (i + .5f) * a + randunif(-noise, noise);
        lj->x[id*3 + 1] = (j + .5f) * a + randunif(-noise, noise);
        lj->x[id*3 + 2] = (k + .5f) * a + randunif(-noise, noise);
        id++;
      }
}


INLINE real lj_gettail(lj_t *lj, real rho, int n, real *ptail)
{
  real irc, irc3, irc6, utail;

  irc = 1/lj->rc;
  irc3 = irc * irc * irc;
  irc6 = irc3 * irc3;
  if (lj->d == 3) {
    utail = (real)( 8*M_PI*rho*n/9*(irc6 - 3)*irc3 );
    if (ptail != NULL)
      *ptail = (real)( 32*M_PI*rho*rho/9*(irc6 - 1.5)*irc3 );
  } else if (lj->d == 2) {
    utail = (real) (M_PI*rho*n*(.4*irc6 - 1)*irc3*irc);
    if (ptail != NULL)
      *ptail = (real) (M_PI*rho*rho*(2.4*irc6 - 3)*irc3*irc);
  }
  return utail;
}


/* set density and compute tail corrections */
INLINE void lj_setrho(lj_t *lj, real rho)
{
  int i;

  lj->rho = rho;
  lj->l = (real) pow(1.*lj->n/rho, 1./lj->d);
  for (lj->vol = 1.f, i = 0; i < lj->d; i++) lj->vol *= lj->l;
  if ((lj->rc = lj->rcdef) > lj->l * .5f) lj->rc = lj->l * .5f;
  lj->rc2 = lj->rc * lj->rc;
  lj->epot_shift = 0.f;
  if (lj->usesw) { /* assume u(L/2) = 0 */
    lj->epot_tail = 0.f;
    lj->p_tail = 0.f;
  } else {
    if ( lj->usesq ) {
      real irc = 1/lj->rc;
      irc *= irc * irc;
      irc *= irc;
      lj->epot_shift = 4*irc*(irc - 1);
    }
    lj->epot_tail = lj_gettail(lj, rho, lj->n, &lj->p_tail);
  }
}


INLINE real lj_pbc(real x, real l)
  { return (real)((x - ((int)((x)+1000.5) - 1000))*l) ; }


INLINE real *lj_vpbc2d(real *v, real l)
  { v[0] = lj_pbc(v[0], l); v[1] = lj_pbc(v[1], l); return v; }


INLINE real *lj_vpbc3d(real *v, real l)
  { v[0] = lj_pbc(v[0], l); v[1] = lj_pbc(v[1], l); v[2] = lj_pbc(v[2], l); return v; }


INLINE real lj_pbcdist2_2d(real *dx, const real *a, const real *b, real l)
  { return rv2_sqr(lj_vpbc2d(rv2_diff(dx, a, b), l)); }

INLINE real lj_pbcdist2_3d(real *dx, const real *a, const real *b, real l)
  { return rv3_sqr(lj_vpbc3d(rv3_diff(dx, a, b), l)); }


/* open an LJ system */
INLINE lj_t *lj_open(int n, int d, real rho, real rcdef)
{
  lj_t *lj;
  int i;

  xnew(lj, 1);
  lj->n = n;
  lj->d = d;
  lj->dof = n * d - d * (d+1)/2;
  xnew(lj->f, n * d);
  xnew(lj->v, n * d);
  xnew(lj->x, n * d);

  lj->rcdef = rcdef;
  lj_setrho(lj, rho);

  lj->esqinf = 1000000;

  if (lj->d == 3) lj_initfcc3d(lj); else lj_initfcc2d(lj);

  /* init. random velocities */
  for (i = 0; i < n * d; i++) lj->v[i] = (real) (rand01() - .5);

  lj_shiftcom(lj, lj->v);
  lj_shiftang(lj, lj->x, lj->v);
  lj->ekin = md_ekin(lj->v, lj->n * lj->d, lj->dof, &lj->tkin);

  lj->isclone = 0;

  lj_force(lj);
  return lj;
}


/* copy flags */
#define LJ_CPX   0x0001
#define LJ_CPV   0x0002
#define LJ_CPF   0x0004
#define LJ_CPPR  0x0020
#define LJ_CPGDG 0x0040
#define LJ_CPXDG 0x0080
#define LJ_CPXVF (LJ_CPX|LJ_CPV|LJ_CPF)

#define lj_copyvec(lj, t, s) memcpy(t, s, lj->d * lj->n * sizeof(real))

/* copy from src to dest
 * cannot copy vectors other than xvf */
INLINE lj_t *lj_copy(lj_t *dest, const lj_t *src, unsigned flags)
{
  /* to preserve the pointers before the memcpy(dest, src) call */
  real *x = dest->x, *v = dest->v, *f = dest->f;

  memcpy(dest, src, sizeof(lj_t));

  if (flags & LJ_CPX) lj_copyvec(src, x, src->x);
  dest->x = x;
  if (flags & LJ_CPV) lj_copyvec(src, v, src->v);
  dest->v = v;
  if (flags & LJ_CPF) lj_copyvec(src, f, src->f);
  dest->f = f;
  return dest;
}


/* make new copy */
INLINE lj_t *lj_clone(const lj_t *src, unsigned flags)
{
  int nd = src->n * src->d;
  lj_t *dest;

  xnew(dest, 1);
  memcpy(dest, src, sizeof(lj_t));
  /* unless specified in flags,
   * arrays are copied literally as pointers */
  dest->isclone = LJ_CPPR | LJ_CPGDG | LJ_CPXDG;
  if (flags & LJ_CPX) {
    xnew(dest->x, nd);
    lj_copyvec(src, dest->x, src->x);
  } else {
    dest->isclone |= LJ_CPX;
  }
  if (flags & LJ_CPV) {
    xnew(dest->v, nd);
    lj_copyvec(src, dest->v, src->v);
  } else {
    dest->isclone |= LJ_CPV;
  }
  if (flags & LJ_CPF) {
    xnew(dest->f, nd);
    lj_copyvec(src, dest->f, src->v);
  } else {
    dest->isclone |= LJ_CPF;
  }
  return dest;
}


INLINE void lj_close(lj_t *lj)
{
  if ( !(lj->isclone & LJ_CPX) ) free(lj->x);
  if ( !(lj->isclone & LJ_CPV) ) free(lj->v);
  if ( !(lj->isclone & LJ_CPF) ) free(lj->f);
  if ( !(lj->isclone & LJ_CPPR)  && lj->pr)
    free(lj->pr);
  if ( !(lj->isclone & LJ_CPGDG) && lj->gdg)
    free(lj->gdg);
  if ( !(lj->isclone & LJ_CPXDG) && lj->xdg)
    free(lj->xdg);
  free(lj);
}


/* write positions (and possibly velocities)
 * Note 1: *actual* position, not unit position is used
 * Note 2: coordinates are *not* wrapped back into the box */
INLINE int lj_writepos(lj_t *lj, const real *x, const real *v, const char *fn)
{
  FILE *fp;

  if (fn == NULL) fn = "lj.pos";
  xfopen(fp, fn, "w", return -1);
  fprintf(fp, "# %d %d %d %.14e\n", lj->d, lj->n, (v != NULL), lj->l);
  md_writepos(fp, x, v, lj->n, lj->d, lj->l);
  fclose(fp);
  return 0;
}


#define LJ_LOADBOX 0x10

/* read the position file (which may include velocities) */
INLINE int lj_readpos(lj_t *lj, real *x, real *v, const char *fn, unsigned flags)
{
  char s[1024];
  FILE *fp;
  int i, j, ret = -1, hasv = 0;
  double l0;

  if (fn == NULL) fn = "lj.pos";
  xfopen(fp, fn, "r", return -1);

  if (fgets(s, sizeof s, fp) == NULL || s[0] != '#') { /* simplified format, old version */
    fprintf(stderr, "Warning: %s has no information line\n", fn);
    rewind(fp);
  } else {
    if (4 != sscanf(s + 1, "%d%d%d%lf", &i, &j, &hasv, &l0)
        || i != lj->d || j != lj->n) {
      fprintf(stderr, "first line is corrupted:\n%s", s);
      goto ERR;
    }
    if (fabs(l0 - lj->l) > 1e-5*lj->l) { /* verify the box size */
      if (flags & LJ_LOADBOX) {
        lj->l = (real) l0;
        for (lj->vol = 1, j = 0; j < lj->d; j++) lj->vol *= lj->l;
        lj_setrho(lj, lj->n/lj->vol);
      } else {
        fprintf(stderr, "box mismatch l %g, should be %g\n", l0, lj->l);
        goto ERR;
      }
    }
  }

  ret = md_readpos(fp, x, hasv ? v : NULL, lj->n, lj->d, lj->l);
ERR:
  fclose(fp);
  return ret;
}


/* initialize square well potential */
INLINE void lj_initsq(lj_t *lj, real ra, real rb)
{
  lj->ra2 = (lj->ra = ra) * ra;
  lj->rb2 = (lj->rb = rb) * rb;
  lj->usesq = 1;
  lj_energy(lj);
}


/* initialize coefficients for the switched potential */
INLINE void lj_initsw(lj_t *lj, real rs)
{
  real rs2, rs3, rs6, rs15, dr, dr2, dr3, dr4, f1, f2, f26, f13;

  lj->rs = rs;
  dr = lj->rs - lj->rc;
  die_if (dr > 0, "rs %g, rc %g\n", lj->rs, lj->rc);

  rs2 = rs*rs;
  rs3 = rs2*rs;
  rs6 = rs3*rs3;
  rs15 = rs6*rs6*rs3;
  dr2 = dr*dr;
  dr3 = dr2*dr;
  dr4 = dr3*dr;
  f1 = rs6 - 1.f;
  f2 = rs6 - 2.f;
  f13 = 2.f*rs6 - 13.f;
  f26 = 7.f*rs6 - 26.f;

  f1 *= rs3;
  f2 *= dr*rs2;
  f13 *= dr3;
  f26 *= dr2*rs;
  lj->a4 = -4.f*(35.f*f1 + 90.f*f2 + 28.f*f13 + 15.f*f26)/(dr4*rs15);
  lj->a5 = 24.f*(14.f*f1 + 39.f*f2 + 14.f*f13 + 7.f*f26)/(dr2*dr3*rs15);
  lj->a6 = -4.f*(70.f*f1 + 204.f*f2 + 84.f*f13 + 39.f*f26)/(dr3*dr3*rs15);
  lj->a7 = 16.f*(5.f*f1 + 15.f*f2 + 7.f*f13 + 3.f*f26)/(dr3*dr4*rs15);

  xnew(lj->pr, lj->n * lj->n);
  xnew(lj->gdg, lj->n * lj->d);
  lj->npr = 0;
  lj->usesw = 1;
}


/* compute the switch potential phi(r) and its derivatives
 * fscal = -phi = uij'/rij
 * psi = phi'/rij
 * xi = psi'/rij
 * Laplacian = psi*rij^2 + 3*phi = psi*rij^2 - 3*fscal */
INLINE real lj_potsw(lj_t *lj, real r, real *fscal, real *psi, real *xi)
{
  if (r < lj->rs) { /* normal lj */
    real invr2, invr6, invr8;
    invr2 = 1 / (r*r);
    invr6 = invr2 * invr2 * invr2;
    invr8 = invr6 * invr2;
    *fscal = (48 * invr6 - 24) * invr8;
    *psi = (672 * invr6 - 192) * invr8 * invr2;
    *xi = -(10752 * invr6 - 1920) * invr6 * invr6;
    return 4 * invr6 * (invr6 - 1);
  } else if (r < lj->rc) { /* polynomial */
    real dr, dr2, dr3, fs, ps, xs, invr, invr2;
    real a4 = lj->a4, a5 = lj->a5, a6 = lj->a6, a7 = lj->a7;
    invr = 1/r;
    dr = r - lj->rc;
    invr2 = invr * invr;
    dr2 = dr * dr;
    dr3 = dr2 * dr;
    fs = dr3*(4*a4 + dr*(5*a5 + dr*(6*a6 + dr*7*a7)))*invr;
    *fscal = -fs;
    ps = dr2*(12*a4 + dr*(20*a5 + dr*(30*a6 + dr*42*a7)));
    *psi = (ps - fs)*invr2;
    xs = dr*(24*a4 + dr*(60*a5 + dr*(120*a6 + dr*210*a7)));
    *xi = (xs*invr - 3*(*psi))*invr2;
    return (dr2*dr2)*(a4 + dr*(a5 + dr*(a6 + dr*a7)));
  } else { /* out of range */
    *fscal = 0;
    *psi = 0;
    *xi = 0;
    return 0;
  }
}


/* 2D energy for square, lj members are not altered */
INLINE int lj_energysq2d(lj_t *lj, rv2_t *x, real *rmin)
{
  real dx[2], dr2, ra2 = lj->ra2, rb2 = lj->rb2, l = lj->l, rm2 = 1e30;
  int i, j, iu = 0, n = lj->n, col = 0;

  for (i = 0; i < n - 1; i++) {
    for (j = i + 1; j < n; j++) {
      dr2 = lj_pbcdist2_2d(dx, x[i], x[j], l);
      if (dr2 < ra2) {
        iu += lj->esqinf;
        col++;
      } else if (dr2 < rb2) {
        iu--;
      }
      if (dr2 < rm2) rm2 = dr2;
    }
  }
  if (rmin != NULL) *rmin = (real) sqrt(rm2);
  /* force the energy to zero in the hard sphere case */
  if (fabs(ra2 - rb2) < 1e-6 && col == 0) {
    iu = 0;
  }
  return iu;
}

/* 3D energy for square, lj members are not altered */
INLINE int lj_energysq3d(lj_t *lj, rv3_t *x, real *rmin)
{
  real dx[3], dr2, ra2 = lj->ra2, rb2 = lj->rb2, l = lj->l, rm2 = 1e30;
  int i, j, iu = 0, n = lj->n, col = 0;

  for (i = 0; i < n - 1; i++) {
    for (j = i + 1; j < n; j++) {
      dr2 = lj_pbcdist2_3d(dx, x[i], x[j], l);
      if (dr2 < ra2) {
        iu += lj->esqinf;
        col++;
      } else if (dr2 < rb2) {
        iu--;
      }
      if (dr2 < rm2) rm2 = dr2;
    }
  }
  if (rmin != NULL) *rmin = (real) sqrt(rm2);
  /* force the energy to zero in the hard sphere case */
  if (fabs(ra2 - rb2) < 1e-6 && col == 0) {
    iu = 0;
  }
  return iu;
}


/* compute 2D energy for switched potential */
INLINE real lj_energysw2d(lj_t *lj, rv2_t *x, real *virial, real *laplace)
{
  int i, j, n = lj->n;
  real dx[2], dr2, dr, l = lj->l, d = (real) lj->d;
  real fscal, psi, xi, ep, vir, lap;

  ep = lap = vir = 0.f;
  for (i = 0; i < n; i++) {
    for (j = i + 1; j < n; j++) {
      dr2 = lj_pbcdist2_2d(dx, x[i], x[j], l);
      if (dr2 > lj->rc2) continue;

      dr = (real) sqrt(dr2);
      ep += lj_potsw(lj, dr, &fscal, &psi, &xi);
      lap += 2.f*(psi*dr2 - d*fscal);
      vir += fscal*dr2;
      rv2_smul(dx, fscal);
    }
  }
  if (virial) *virial = vir;
  if (laplace) *laplace = lap;
  return ep;
}

/* compute 3D energy for switched potential */
INLINE real lj_energysw3d(lj_t *lj, rv3_t *x, real *virial, real *laplace)
{
  int i, j, n = lj->n;
  real dx[3], dr2, dr, l = lj->l, d = (real) lj->d;
  real fscal, psi, xi, ep, vir, lap;

  ep = lap = vir = 0.f;
  for (i = 0; i < n; i++) {
    for (j = i + 1; j < n; j++) {
      dr2 = lj_pbcdist2_3d(dx, x[i], x[j], l);
      if (dr2 > lj->rc2) continue;

      dr = (real) sqrt(dr2);
      ep += lj_potsw(lj, dr, &fscal, &psi, &xi);
      lap += 2.f*(psi*dr2 - d*fscal);
      vir += fscal*dr2;
      rv3_smul(dx, fscal);
    }
  }
  if (virial) *virial = vir;
  if (laplace) *laplace = lap;
  return ep;
}


/* 2D compute force and virial, return energy */
INLINE real lj_energylj2d(lj_t *lj, rv2_t *x, real *virial, real *ep0, real *eps)
{
  real dx[2], dr2, dr6, ep, vir, l = lj->l, rc2 = lj->rc2;
  int i, j, prcnt = 0, n = lj->n;

  if (virial) *virial = 0.f;
  for (ep = vir = 0, i = 0; i < n - 1; i++) {
    for (j = i + 1; j < n; j++) {
      dr2 = lj_pbcdist2_2d(dx, x[i], x[j], l);
      if (dr2 > rc2) continue;
      dr2 = 1.f / dr2;
      dr6 = dr2 * dr2 * dr2;
      vir += dr6 * (48.f * dr6 - 24.f); /* f.r */
      ep += 4 * dr6 * (dr6 - 1);
      prcnt++;
    }
  }
  if (ep0) *ep0 = ep;
  if (eps) *eps = ep - prcnt * lj->epot_shift; /* shifted energy */
  if (virial) *virial = vir;
  return ep + lj->epot_tail; /* unshifted energy */
}

/* 3D compute force and virial, return energy */
INLINE real lj_energylj3d(lj_t *lj, rv3_t *x, real *virial, real *ep0, real *eps)
{
  real dx[3], dr2, dr6, ep, vir, l = lj->l, rc2 = lj->rc2;
  int i, j, prcnt = 0, n = lj->n;

  if (virial) *virial = 0.f;
  for (ep = vir = 0, i = 0; i < n - 1; i++) {
    for (j = i + 1; j < n; j++) {
      dr2 = lj_pbcdist2_3d(dx, x[i], x[j], l);
      if (dr2 > rc2) continue;
      dr2 = 1.f / dr2;
      dr6 = dr2 * dr2 * dr2;
      vir += dr6 * (48.f * dr6 - 24.f); /* f.r */
      ep += 4 * dr6 * (dr6 - 1);
      prcnt++;
    }
  }
  if (ep0) *ep0 = ep;
  if (eps) *eps = ep - prcnt * lj->epot_shift; /* shifted energy */
  if (virial) *virial = vir;
  return ep + lj->epot_tail; /* unshifted energy */
}


/* energy evaluation, do not change members of `lj' */
INLINE real lj_energyx2d(lj_t *lj, rv2_t *x, real *vir, int *iep, real *rmin,
    real *ep0, real *eps, real *lap)
{
  real u, u0 = 0, us = 0;
  int iu = 0;

  if (lj->usesq) {
    iu = lj_energysq2d(lj, x, rmin);
    u0 = us = u = (real) iu;
  } else if (lj->usesw) {
    u = lj_energysw2d(lj, x, vir, lap);
    u0 = us = u;
  } else {
    u = lj_energylj2d(lj, x, vir, &u0, &us);
  }
  if (iep) *iep = iu;
  if (ep0) *ep0 = u0;
  if (eps) *eps = us;
  return u;
}

/* energy evaluation, do not change members of `lj' */
INLINE real lj_energyx3d(lj_t *lj, rv3_t *x, real *vir, int *iep, real *rmin,
    real *ep0, real *eps, real *lap)
{
  real u, u0 = 0, us = 0;
  int iu = 0;

  if (lj->usesq) {
    iu = lj_energysq3d(lj, x, rmin);
    u0 = us = u = (real) iu;
  } else if (lj->usesw) {
    u = lj_energysw3d(lj, x, vir, lap);
    u0 = us = u;
  } else {
    u = lj_energylj3d(lj, x, vir, &u0, &us);
  }
  if (iep) *iep = iu;
  if (ep0) *ep0 = u0;
  if (eps) *eps = us;
  return u;
}


/* energy evaluation, do not change members of `lj' */
INLINE real lj_energyx(lj_t *lj, real *x, real *vir, int *iep, real *rmin,
    real *ep0, real *eps, real *lap)
{
  return lj->d == 2 ?
      lj_energyx2d(lj, (rv2_t *) x, vir, iep, rmin, ep0, eps, lap) :
      lj_energyx3d(lj, (rv3_t *) x, vir, iep, rmin, ep0, eps, lap);
}


/* compute the energy of the current configuration and set lj->epot */
INLINE real lj_energy2d(lj_t *lj)
{
  return lj->epot = lj_energyx2d(lj, (rv2_t *) lj->x, &lj->vir, &lj->iepot,
      &lj->rmin, &lj->epot0, &lj->epots, &lj->lap);
}

/* compute the energy of the current configuration and set lj->epot */
INLINE real lj_energy3d(lj_t *lj)
{
  return lj->epot = lj_energyx3d(lj, (rv3_t *) lj->x, &lj->vir, &lj->iepot,
      &lj->rmin, &lj->epot0, &lj->epots, &lj->lap);
}


INLINE real lj_energy(lj_t *lj)
{
  return (lj->d == 2) ? lj_energy2d(lj) : lj_energy3d(lj);
}


/* compute 2D switched force, save derivative information to lj->pr */
INLINE real lj_forcesw2d(lj_t *lj, rv2_t *x, rv2_t *f, ljpair_t *pr,
    int *ljnpr, real *virial, real *f2, real *laplace)
{
  int i, j, n = lj->n, npr;
  real dx[2], dr2, dr, l = lj->l, d = (real) lj->d;
  real fscal, psi, xi, ep, vir, lap;

  npr = 0;
  ep = lap = vir = 0.f;
  for (i = 0; i < n; i++) rv2_zero(f[i]);
  for (i = 0; i < n; i++) {
    for (j = i + 1; j < n; j++) {
      dr2 = lj_pbcdist2_2d(dx, x[i], x[j], l);
      if (dr2 > lj->rc2) {
        /* save out-of-range pairs, so we can later
         * locate the pair from indices i and j using getpairindex() */
        if (lj->usesw & LJ_SWALLPAIRS) {
          rv2_copy(pr->dx, dx);
          pr->i = i;
          pr->j = j;
          pr->phi = pr->psi = pr->xi = 0.f;
          pr->dr2 = dr2;
          pr->in = 0;
          pr++; npr++;
        }
        continue;
      }

      rv2_copy(pr->dx, dx);
      pr->dr2 = dr2;
      dr = (real) sqrt(dr2);
      ep += lj_potsw(lj, dr, &fscal, &psi, &xi);
      pr->phi = -fscal; /* phi = u'/r */
      pr->psi = psi;  /* psi = phi'/r */
      pr->xi = xi;  /* xi = psi'/r */
      lap += 2.f*(psi*dr2 - d*fscal);
      vir += fscal*dr2; /* f.r */
      rv2_smul(dx, fscal);
      pr->i = i;
      pr->j = j;
      rv2_inc(f[i], dx);
      rv2_dec(f[j], dx);
      pr->in = 1;
      pr++; npr++;
    }
  }
  if (ljnpr) *ljnpr = npr;
  if (virial) *virial = vir;
  if (laplace) *laplace = lap;
  if (f2) for (*f2 = 0.0, i = 0; i < n; i++) *f2 += rv2_sqr(f[i]);
  return ep;
}

/* compute 3D switched force, save derivative information to lj->pr */
INLINE real lj_forcesw3d(lj_t *lj, rv3_t *x, rv3_t *f, ljpair_t *pr,
    int *ljnpr, real *virial, real *f2, real *laplace)
{
  int i, j, n = lj->n, npr;
  real dx[3], dr2, dr, l = lj->l, d = (real) lj->d;
  real fscal, psi, xi, ep, vir, lap;

  npr = 0;
  ep = lap = vir = 0.f;
  for (i = 0; i < n; i++) rv3_zero(f[i]);
  for (i = 0; i < n; i++) {
    for (j = i + 1; j < n; j++) {
      dr2 = lj_pbcdist2_3d(dx, x[i], x[j], l);
      if (dr2 > lj->rc2) {
        /* save out-of-range pairs, so we can later
         * locate the pair from indices i and j using getpairindex() */
        if (lj->usesw & LJ_SWALLPAIRS) {
          rv3_copy(pr->dx, dx);
          pr->i = i;
          pr->j = j;
          pr->phi = pr->psi = pr->xi = 0.f;
          pr->dr2 = dr2;
          pr->in = 0;
          pr++; npr++;
        }
        continue;
      }

      rv3_copy(pr->dx, dx);
      pr->dr2 = dr2;
      dr = (real) sqrt(dr2);
      ep += lj_potsw(lj, dr, &fscal, &psi, &xi);
      pr->phi = -fscal; /* phi = u'/r */
      pr->psi = psi;  /* psi = phi'/r */
      pr->xi = xi;  /* xi = psi'/r */
      lap += 2.f*(psi*dr2 - d*fscal);
      vir += fscal*dr2; /* f.r */
      rv3_smul(dx, fscal);
      pr->i = i;
      pr->j = j;
      rv3_inc(f[i], dx);
      rv3_dec(f[j], dx);
      pr->in = 1;
      pr++; npr++;
    }
  }
  if (ljnpr) *ljnpr = npr;
  if (virial) *virial = vir;
  if (laplace) *laplace = lap;
  if (f2) for (*f2 = 0.0, i = 0; i < n; i++) *f2 += rv3_sqr(f[i]);
  return ep;
}


/* 2D compute force and virial, return energy */
INLINE real lj_forcelj2d(lj_t *lj, rv2_t *x, rv2_t *f, real *virial,
    real *ep0, real *eps, real *f2, real *laplace)
{
  real dx[2], fi[2], dr2, dr6, fs, tmp, ep, vir, lap, l = lj->l, rc2 = lj->rc2;
  int i, j, d, prcnt = 0, n = lj->n;

  for (i = 0; i < n; i++) rv2_zero(f[i]);
  for (ep = vir = lap = 0, i = 0; i < n - 1; i++) {
    rv2_zero(fi);
    for (j = i + 1; j < n; j++) {
      dr2 = lj_pbcdist2_2d(dx, x[i], x[j], l);
      if (dr2 > rc2) continue;
      dr2 = 1.f / dr2;
      dr6 = dr2 * dr2 * dr2;
      fs = dr6 * (48.f * dr6 - 24.f); /* f.r */
      vir += fs; /* f.r */
      if (laplace) /* 2.f for it applies to both particles */
        lap += 2.f * ((168 - 12*2) * dr6 - (48 - 6*2)) * dr6 * dr2;

      fs *= dr2; /* f.r / r^2 */
      for (d = 0; d < 2; d++) {
        tmp = dx[d] * fs;
        fi[d] += tmp;
        f[j][d] -= tmp;
      }

      ep += 4 * dr6 * (dr6 - 1);
      prcnt++;
    }
    rv2_inc(f[i], fi);
  }
  if (ep0) *ep0 = ep;
  if (eps) *eps = ep - prcnt * lj->epot_shift; /* shifted energy */
  if (virial) *virial = vir;
  if (laplace) *laplace = 4*lap;
  if (f2) for (*f2 = 0.f, i = 0; i < n; i++) *f2 += rv2_sqr(f[i]);
  return ep + lj->epot_tail; /* unshifted energy */
}

/* 3D compute force and virial, return energy */
INLINE real lj_forcelj3d(lj_t *lj, rv3_t *x, rv3_t *f, real *virial,
    real *ep0, real *eps, real *f2, real *laplace)
{
  real dx[3], fi[3], dr2, dr6, fs, tmp, ep, vir, lap, l = lj->l, rc2 = lj->rc2;
  int i, j, d, prcnt = 0, n = lj->n;

  for (i = 0; i < n; i++) rv3_zero(f[i]);
  for (ep = vir = lap = 0, i = 0; i < n - 1; i++) {
    rv3_zero(fi);
    for (j = i + 1; j < n; j++) {
      dr2 = lj_pbcdist2_3d(dx, x[i], x[j], l);
      if (dr2 > rc2) continue;
      dr2 = 1.f / dr2;
      dr6 = dr2 * dr2 * dr2;
      fs = dr6 * (48.f * dr6 - 24.f); /* f.r */
      vir += fs; /* f.r */
      if (laplace) /* 2.f for it applies to both particles */
        lap += 2.f * ((168 - 12*3) * dr6 - (48 - 6*3)) * dr6 * dr2;

      fs *= dr2; /* f.r / r^2 */
      for (d = 0; d < 3; d++) {
        tmp = dx[d] * fs;
        fi[d] += tmp;
        f[j][d] -= tmp;
      }

      ep += 4 * dr6 * (dr6 - 1);
      prcnt++;
    }
    rv3_inc(f[i], fi);
  }
  if (ep0) *ep0 = ep;
  if (eps) *eps = ep - prcnt * lj->epot_shift; /* shifted energy */
  if (virial) *virial = vir;
  if (laplace) *laplace = 4*lap;
  if (f2) for (*f2 = 0.f, i = 0; i < n; i++) *f2 += rv3_sqr(f[i]);
  return ep + lj->epot_tail; /* unshifted energy */
}


INLINE real lj_force2d(lj_t *lj)
{
  if (lj->usesq) return lj->epot = lj->epot0 = lj->epots = (real) lj_energysq2d(lj,
    (rv2_t *) lj->x, &lj->rmin); /* no force for square well */
  if (lj->usesw) return lj->epot = lj->epot0 = lj->epots = lj_forcesw2d(lj,
    (rv2_t *) lj->x, (rv2_t *) lj->f,
    lj->pr, &lj->npr, &lj->vir, &lj->f2, &lj->lap);
  return lj->epot = lj_forcelj2d(lj, (rv2_t *) lj->x, (rv2_t *) lj->f,
    &lj->vir, &lj->epot0, &lj->epots, &lj->f2, &lj->lap);
}

INLINE real lj_force3d(lj_t *lj)
{
  if (lj->usesq) return lj->epot = lj->epot0 = lj->epots = (real) lj_energysq3d(lj,
    (rv3_t *) lj->x, &lj->rmin); /* no force for square well */
  if (lj->usesw) return lj->epot = lj->epot0 = lj->epots = lj_forcesw3d(lj,
    (rv3_t *) lj->x, (rv3_t *) lj->f,
    lj->pr, &lj->npr, &lj->vir, &lj->f2, &lj->lap);
  return lj->epot = lj_forcelj3d(lj, (rv3_t *) lj->x, (rv3_t *) lj->f,
    &lj->vir, &lj->epot0, &lj->epots, &lj->f2, &lj->lap);
}


INLINE real lj_force(lj_t *lj)
{
  return (lj->d == 2) ? lj_force2d(lj) : lj_force3d(lj);
}


/* calculate the configurational temperature (bc) for switched potential
 * bc = div(v), where v = g/(g.g), g = grad U,
 * udb = v . grad bc
 * bvir = x . grad bc */
INLINE real lj_bconfsw3d(lj_t *lj, real *udb)
{
  int i, j, ipr, npr = lj->npr, n = lj->n;
  ljpair_t *pr;
  real dg[3], dh[3];
  real phi, psi, xi, d = (real) lj->d;
  real dgdx, dg2, dr2, m = 0.f, h2;
  real gdlap = 0.f, gdm = 0.f, bc, invg2, invg4;
  real dlap, dgdx2;
  rv3_t *h = (rv3_t *) lj->gdg, *f = (rv3_t *) lj->f;

  if (udb) for (i = 0; i < n; i++) rv3_zero(h[i]);

  for (ipr = 0; ipr < npr; ipr++) {
    pr = lj->pr + ipr;
    i = pr->i;
    j = pr->j;
    phi = pr->phi;
    psi = pr->psi;

    dg2 = rv3_sqr( rv3_diff(dg, f[j], f[i]) );
    dgdx = rv3_dot(dg, pr->dx);
    m += psi*(dgdx2 = dgdx*dgdx) + phi*dg2; /* M = g g : grad grad U */
    if (udb) {
      dr2 = pr->dr2;
      xi = pr->xi;
      dlap = xi*dr2 + (2.f + d)*psi;
      gdlap += dlap * dgdx; /* 0.5 g . grad laplace U */
      gdm += (xi*dgdx2 + 3.f*psi*dg2)*dgdx; /* g g g : grad grad grad U, first larger */
      rv3_lincomb2(dh, pr->dx, dg, psi * dgdx, phi);
      rv3_sinc(h[i], dh,  2.f);
      rv3_sinc(h[j], dh, -2.f);
    }
  }
  m *= 2.f;
  gdlap *= 2.f;
  gdm *= 2.f;
  invg2 = 1.f/lj->f2;
  invg4 = invg2 * invg2;
  bc = (lj->lap - m*invg2)*invg2; /* configuration temperature */

  if (udb) {
    for (h2 = 0.f, i = 0; i < n; i++) h2 += rv3_sqr(h[i]);
    /* (1/g) \partial^2 g/ \partial E^2 = <bc*bc + udb>
       \partial bc/ \partial E = <d(bc)^2 + udb> */
    *udb = invg4*(gdlap - (lj->lap*m + h2 + gdm)*invg2 + 2.f*m*m*invg4);
  }

  return bc;
}


/* return r r : grad grad U, must be called after force */
INLINE real lj_vir2sw3d(lj_t *lj)
{
  int ipr, npr = lj->npr;
  real vir2 = 0.f;

  for (ipr = 0; ipr < npr; ipr++) {
    ljpair_t *pr = lj->pr + ipr;
    vir2 += (pr->psi * pr->dr2 + pr->phi) * pr->dr2;
  }
  return vir2;
}


/* compute pressure */
INLINE real lj_calcp(lj_t *lj, real tp)
{
  return (lj->dof * tp + lj->vir) / (lj->d * lj->vol) + lj->p_tail;
}


/* compute pressure, ideal gas part from the kinetic energy  */
INLINE real lj_calcpk(lj_t *lj)
{
  return (2.f * lj->ekin + lj->vir) / (lj->d * lj->vol) + lj->p_tail;
}




#include <stdio.h>
#include <math.h>
#ifndef INLINE
#define INLINE __inline static
#endif


/* default */
#define lj_eos3d lj_eos3dMBWRJZG

enum { LJEOS_MBWRJZG = 0, LJEOS_MBWRKN = 1, LJEOS_PVEhBHKN = 2};

#define lj_eos3dMBWRJZG(rho, T, P, Fex, muex) \
  lj_eos3dMBWR(rho, T, P, Fex, muex, LJEOS_MBWRJZG, NULL)

#define lj_eos3dMBWRKN(rho, T, P, Fex, muex) \
  lj_eos3dMBWR(rho, T, P, Fex, muex, LJEOS_MBWRKN, NULL)


/* compute reference thermal dynamics variables
   using the modified Benedic-Webb-Rubin (MBWR) equation of states
   return the average potential energy
   *P:  pressure
   *Fex: Helmholtz free energy (potential part)
   *muex: Gibbs free energy (potential part) */
INLINE double lj_eos3dMBWR(double rho, double T, double *P,
    double *Fex, double *muex, int eos, const double *x)
{
  /* Reference:
   * J. Karl Johnson, John A. Zollweg, and Keith E. Gubbins (JZG)
   * The Lennard-Jones equation of states revisited,
   * Molecular Physics (1993) Vol. 78, No 3, 591-618
   * Table 10 */
  const double ljparam_JZG1993[] = {0,
     0.8623085097507421,
     2.976218765822098,
    -8.402230115796038,
     0.1054136629203555,
    -0.8564583828174598,     /* 5 */
     1.582759470107601,
     0.7639421948305453,
     1.753173414312048,
     2.798291772190376e+03,
    -4.8394220260857657e-02, /* 10 */
     0.9963265197721935,
    -3.698000291272493e+01,
     2.084012299434647e+01,
     8.305402124717285e+01,
    -9.574799715203068e+02,  /* 15 */
    -1.477746229234994e+02,
     6.398607852471505e+01,
     1.603993673294834e+01,
     6.805916615864377e+01,
    -2.791293578795945e+03,  /* 20 */
    -6.245128304568454,
    -8.116836104958410e+03,
     1.488735559561229e+01,
    -1.059346754655084e+04,
    -1.131607632802822e+02,  /* 25 */
    -8.867771540418822e+03,
    -3.986982844450543e+01,
    -4.689270299917261e+03,
     2.593535277438717e+02,
    -2.694523589434903e+03,  /* 30 */
    -7.218487631550215e+02,
     1.721802063863269e+02,
     3.0 /* gamma, Cf. JZG 1993, Table 7 caption */
  };

  /* Reference:
   * Jiri Kolafa and Ivo Nezbeda
   * The Lennard-Jones fluid: An accurate analytic
   *   and theoretically-based equation of state
   * Fluid Phase Equilibria (1994) Vol. 100, 1-34
   * TABLE 5
   * regressed from data with T <= 6
   * */
  const double ljparam_KN1994[] = {0,
        0.86230851,
        2.97621877,
       -8.40223012,
        0.10541366,
       -0.85645838, /* 5 */
        1.39945300,
       -0.20682219,
        2.66555449,
     1205.90355811,
        0.24414200, /* 10 */
        6.17927577,
      -41.33848427,
       15.14482295,
       88.90243729,
    -2425.74868591, /* 15 */
     -148.52651854,
       68.73779789,
     2698.26346845,
    -1216.87158315,
    -1199.67930914, /* 20 */
       -7.28265251,
    -4942.58001124,
       24.87520514,
    -6246.96241113,
     -235.12327760, /* 25 */
    -7241.61133138,
     -111.27706706,
    -2800.52326352,
     1109.71518240,
     1455.47321956, /* 30 */
    -2577.25311109,
      476.67051504,
        4.52000000  /* gamma */
  };

  double gam;
  double a[8], b[6], c[8], d[6], G[6];
  double F, rhop, rho2 = rho*rho, Pa = 0., Pb = 0., Pt, U, Aex;
  int i;

  /* default parameters */
  if ( eos == LJEOS_MBWRJZG ) x = ljparam_JZG1993;
  else if (eos == LJEOS_MBWRKN ) x = ljparam_KN1994;

  gam = x[33];
  /* Cf. JZG 1993, Table 5 */
  a[0] = x[1]*T + x[2]*sqrt(T) + x[3] + x[4]/T + x[5]/(T*T);
  a[1] = x[6]*T + x[7] + x[8]/T + x[9]/(T*T);
  a[2] = x[10]*T + x[11] + x[12]/T;
  a[3] = x[13];
  a[4] = x[14]/T + x[15]/(T*T);
  a[5] = x[16]/T;
  a[6] = x[17]/T + x[18]/(T*T);
  a[7] = x[19]/(T*T);
  /* Cf. JZG 1993, Table 6 */
  b[0] = (x[20] + x[21]/T)/(T*T);
  b[1] = (x[22] + x[23]/(T*T))/(T*T);
  b[2] = (x[24] + x[25]/T)/(T*T);
  b[3] = (x[26] + x[27]/(T*T))/(T*T);
  b[4] = (x[28] + x[29]/T)/(T*T);
  b[5] = (x[30] + x[31]/T + x[32]/(T*T))/(T*T);
  /* Cf. JZG 1993, Table 8 */
  c[0] = x[2]*sqrt(T)/2 + x[3] + 2*x[4]/T + 3*x[5]/(T*T);
  c[1] = x[7] + 2*x[8]/T + 3*x[9]/(T*T);
  c[2] = x[11] + 2*x[12]/T;
  c[3] = x[13];
  c[4] = 2*x[14]/T + 3*x[15]/(T*T);
  c[5] = 2*x[16]/T;
  c[6] = 2*x[17]/T + 3*x[18]/(T*T);
  c[7] = 3*x[19]/(T*T);
  /* Cf. JZG 1993, Table 9 */
  d[0] = (3*x[20] + 4*x[21]/T)/(T*T);
  d[1] = (3*x[22] + 5*x[23]/(T*T))/(T*T);
  d[2] = (3*x[24] + 4*x[25]/T)/(T*T);
  d[3] = (3*x[26] + 5*x[27]/(T*T))/(T*T);
  d[4] = (3*x[28] + 4*x[29]/T)/(T*T);
  d[5] = (3*x[30] + 4*x[31]/T + 5*x[32]/(T*T))/(T*T);

  /* Cf. JZG 1993, Table 7 */
  F = exp(-gam*rho*rho);
  G[0] = (1 - F)/(2*gam);
  for (rhop = 1, i = 1; i < 6; i++) {
    rhop *= rho*rho;
    G[i] = -(F*rhop - 2*i*G[i-1])/(2*gam);
  }

  Aex = 0;
  Pa = Pb = 0;
  for (U = 0, i = 7; i >= 0; i--) {
    /* Sum {i = 0 to 7} c[i] rho^{i+1} / (i + 1)
     * Cf. JZG 1993, Eq. (9), first term */
    U = rho * (c[i]/(i+1) + U);
    /* Sum {i = 0 to 7} a[i] rho^{i+1} / (i + 1)
     * Cf. JZG 1993, Eq. (5), first term */
    Aex = rho * (a[i]/(i+1) + Aex);
    /* rho * Sum {i = 0 to 7} a[i] rho^{i+1}
     * the leading factor rho is to be multiplied later
     * Cf. JZG 1993, Eq. (7), second term */
    Pa  = rho * (a[i] + Pa);
  }

  for (i = 5; i >= 0; i--) {
    /* Sum {i = 0 to 5} d[i] G[i]
     * Cf. JZG 1993, Eq. (9), second term */
    U += d[i]*G[i];
    /* Sum {i = 0 to 5} b[i] G[i]
     * Cf. JZG 1993, Eq. (5), second term */
    Aex += b[i]*G[i];
    /* (rho*F) * Sum {i = 0 to 5} b[i] rho^{2*(i+1)}
     * the leading factor (rho*F) is to be multiplied later
     * Cf. JZG 1993, Eq. (7), last term */
    Pb = rho2*(b[i] + Pb);
  }
  Pt = rho*(T + Pa + F*Pb); /* Cf. JZG 1993, Eq. (7) */
  if (Fex) *Fex = Aex;
  if (P) *P = Pt;
  if (muex) *muex = Aex + Pt/rho - T;
  return U;
}


INLINE double lj_eos3d_bAhs(double eta)
{
  double e1 = 1 - eta;
  return log(e1)*5/3 + eta*(34 - 33*eta + 4*eta*eta)/(6*e1*e1);
}


INLINE double lj_eos3d_zhs(double eta)
{
  double e1 = 1 - eta;
  return (1 + eta*(1 + eta*(1 - eta*(1 + eta)*2/3)))/(e1*e1*e1);
}


/* equivalent hard-sphere diameter of the hybrid Barker-Henderson theory
 * defined in Eq. (17)
 * d = Int {0 to 2^(1/6)} (1 - exp(-beta*u)) dr
 * Parameters are given by Table 2 with the functional form given by (29)
 *
 * To verify it WolframAlpha or Mathematica
 * Integrate[(1-Exp[-(4/x^12-4/x^6+1)/T]), {x, 0, 2.0^(1.0/6)}]
 * */
INLINE double lj_eos3d_dhBH(double T, double *dfdbeta)
{
  const double Ci[3] = {1.080142248, -0.076383859, 0.011117524};
  const double C1 = 0.000693129, Cln = -0.063920968;
  double x;

  x = sqrt(T);
  *dfdbeta = Ci[2] + 0.5*Ci[1]*x - 0.5*C1*x*T - T*Cln;
  return Ci[2]/T + Ci[1]/x + Ci[0] + C1*x + Cln*log(T);
}


/* The residual second virial coefficient B2_LJ - B2_hs
 * from the hybrid Barker-Henderson theory
 * Parameters are given by Table 2 with the functional form given by (29) */
INLINE double lj_eos3d_dB2hBH(double T, double *dfdbeta)
{
  /* from Table 2 */
  const double Ci[8] = {
    0.02459877,
    0,
   -7.02181962,
    2.90616279,
   -4.13749995,
    0.87361369,
    0.43102052,
   -0.58544978};
  double f = 0, invx = 1/sqrt(T);
  int i;

  *dfdbeta = 0;
  for ( i = 7; i > 0; i-- ) {
    f = (f + Ci[i]) * invx;
    *dfdbeta = (*dfdbeta - Ci[i]*i/2) * invx;
  }
  *dfdbeta *= -T;
  f += Ci[0];
  return f;
}


/* Reference:
 * Jiri Kolafa and Ivo Nezbeda
 * The Lennard-Jones fluid: An accurate analytic
 *   and theoretically-based equation of state
 * Fluid Phase Equilibria (1994) Vol. 100, 1-34
 * http://www.sklogwiki.org/SklogWiki/index.php/Lennard-Jones_equation_of_state
 */
INLINE double lj_eos3dPVEhBH(double rho, double T, double *P, double *A, double *mu)
{
  /* Table 3 */
  const double Cij[5][7] = {
    {0, 0, /* i = 0 */
     2.01546797,
   -28.17881636,
    28.28313847,
   -10.42402873,
    0},
    {0, 0, /* i = -1 */
   -19.58371655,
    75.62340289,
  -120.70586598,
    93.92740328,
   -27.37737354},
    {0, 0, /* i = -2 */
    29.34470520,
  -112.35356937,
   170.64908980,
  -123.06669187,
    34.42288969},
    {0, 0, 0, 0, 0, 0, 0},
    {0, 0, /* i = -4 */
   -13.37031968,
    65.38059570,
  -115.09233113,
    88.91973082,
   -25.62099890}};
  const double gam = 1.92907278;
  double eta, Ahs, AhBH, ACij, z, zhs, zCij, U, UCij;
  double dB2, ddB2, dia, ddia, grho2, xpngrho2;
  double invx = 1/sqrt(T);
  double xprho, xpT, xp;
  int i, j;

  dia = lj_eos3d_dhBH(T, &ddia);
  dB2 = lj_eos3d_dB2hBH(T, &ddB2);
  grho2 = gam*rho*rho;
  xpngrho2 = exp(-grho2);
  eta = M_PI*rho*dia*dia*dia/6;
  Ahs = T*lj_eos3d_bAhs(eta);
  AhBH = xpngrho2*rho*T*dB2;
  ACij = zCij = UCij = 0;
  for ( i = 0; i <= 4; i++ ) {
    xpT = pow(invx, i);
    xprho = rho;
    for ( j = 2; j <= 6; j++ ) {
      xprho *= rho;
      xp = xpT * xprho;
      ACij += Cij[i][j] * xp;
      zCij += j * Cij[i][j] * xp / T;
      UCij += (1 + i*.5) * Cij[i][j] * xp;
    }
  }
  if ( A != NULL ) *A = Ahs + AhBH + ACij;
  zhs = lj_eos3d_zhs(eta);
  z = zhs + rho * (1 - 2*grho2)*xpngrho2*dB2 + zCij;
  if ( P != NULL ) *P = rho * T * z;
  U = 3*(zhs - 1)*ddia/dia + rho*xpngrho2*ddB2 + UCij;
  if ( mu != NULL ) *mu = T*(z - 1) + Ahs + AhBH + ACij;
  return U;
}


INLINE double lj_eos3dx(double rho, double T, double *P,
    double *Fex, double *muex, int eos)
{
  if ( eos == LJEOS_MBWRJZG || eos == LJEOS_MBWRKN ) {
    return lj_eos3dMBWR(rho, T, P, Fex, muex, eos, NULL);
  } else if ( eos == LJEOS_PVEhBHKN ) {
    return lj_eos3dPVEhBH(rho, T, P, Fex, muex);
  } else {
    fprintf(stderr, "Error: unknown equation of state %d\n", eos);
    return 0;
  }
}




/* Lennard-Jones system: Monte Carlo routines */


/* randomly displace particle i with random amplitude */
INLINE int lj_randmv2d(lj_t *lj, real *xi, real amp)
{
  int i, d;

  i = (int) (rand01() * lj->n);
  amp /= lj->l;
  rv2_copy(xi, lj->x + i*2);
  for (d = 0; d < 2; d++) /* displacement */
    xi[d] += (real) randunif(-amp, amp);
  return i;
}

/* randomly displace particle i with random amplitude */
INLINE int lj_randmv3d(lj_t *lj, real *xi, real amp)
{
  int i, d;

  i = (int) (rand01() * lj->n);
  amp /= lj->l;
  rv3_copy(xi, lj->x + i*3);
  for (d = 0; d < 3; d++) /* displacement */
    xi[d] += (real) randunif(-amp, amp);
  return i;
}


/* compute energy data for a 2D pair with a square well potential */
INLINE int lj_pairsq2d(const real *xi, const real *xj, real l,
    real ra2, real rb2, real *pdr2, int inf)
{
  real dx[2], dr2;
  dr2 = lj_pbcdist2_2d(dx, xi, xj, l);
  if (pdr2) *pdr2 = dr2;
  if (dr2 < ra2) return -inf;
  else if (dr2 < rb2) return 1;
  else return 0;
}

/* compute energy data for a 3D pair with a square well potential */
INLINE int lj_pairsq3d(const real *xi, const real *xj, real l,
    real ra2, real rb2, real *pdr2, int inf)
{
  real dx[3], dr2;
  dr2 = lj_pbcdist2_3d(dx, xi, xj, l);
  if (pdr2) *pdr2 = dr2;
  if (dr2 < ra2) return -inf;
  else if (dr2 < rb2) return 1;
  else return 0;
}


/* return the energy change (square well) from displacing x[i] to xi */
INLINE int lj_depotsq2d(lj_t *lj, int i, const real *xi, real *rm)
{
  int j, n = lj->n, npr = 0, inf = lj->esqinf, recalc = 0;
  real l = lj->l, ra2 = lj->ra2, rb2 = lj->rb2;
  real r2o, r2n, rm2o = 0, rm2 = 0;
  rv2_t *x = (rv2_t *) lj->x;
  const real tol = 1e-5;

  if (rm) rm2o = rm2 = (*rm) * (*rm);
  for (j = 0; j < n; j++) { /* pair */
    if (j == i) continue;
    npr -= lj_pairsq2d(x[i], x[j], l, ra2, rb2, &r2o, inf);
    npr += lj_pairsq2d(xi,   x[j], l, ra2, rb2, &r2n, inf);
    if (fabs(r2o - rm2o) < tol) { /* need to re-compute rmin */
      recalc |= 1;
    }
    if (r2n < rm2) { /* new rmin is found */
      recalc |= 2; /* no need to recalc */
      rm2 = r2n;
    }
  }

  /* in order to compute the minimal distance,
   * we need to occasionally recompute the entire system */
  if (recalc == 1) { /* 0, 2, 3 are safe */
    rv2_t xio;
    rv2_copy(xio, x[i]);
    rv2_copy(x[i], xi); /* apply xi */
    lj_energysq2d(lj, x, rm);
    rv2_copy(x[i], xio); /* recover */
  } else {
    if (rm) *rm = (real) sqrt(rm2);
  }

  /* hard sphere, no collision */
  if (fabs(ra2 - rb2) < 2e-6 && npr > -inf/10 && npr < inf/10) {
    npr = 0; /* number of neighbors */
  }
  return -npr; /* increased number of pairs == decreased energy */
}

/* return the energy change (square well) from displacing x[i] to xi */
INLINE int lj_depotsq3d(lj_t *lj, int i, const real *xi, real *rm)
{
  int j, n = lj->n, npr = 0, inf = lj->esqinf, recalc = 0;
  real l = lj->l, ra2 = lj->ra2, rb2 = lj->rb2;
  real r2o, r2n, rm2o = 0, rm2 = 0;
  rv3_t *x = (rv3_t *) lj->x;
  const real tol = 1e-5;

  if (rm) rm2o = rm2 = (*rm) * (*rm);
  for (j = 0; j < n; j++) { /* pair */
    if (j == i) continue;
    npr -= lj_pairsq3d(x[i], x[j], l, ra2, rb2, &r2o, inf);
    npr += lj_pairsq3d(xi,   x[j], l, ra2, rb2, &r2n, inf);
    if (fabs(r2o - rm2o) < tol) { /* need to re-compute rmin */
      recalc |= 1;
    }
    if (r2n < rm2) { /* new rmin is found */
      recalc |= 2; /* no need to recalc */
      rm2 = r2n;
    }
  }

  /* in order to compute the minimal distance,
   * we need to occasionally recompute the entire system */
  if (recalc == 1) { /* 0, 2, 3 are safe */
    rv3_t xio;
    rv3_copy(xio, x[i]);
    rv3_copy(x[i], xi); /* apply xi */
    lj_energysq3d(lj, x, rm);
    rv3_copy(x[i], xio); /* recover */
  } else {
    if (rm) *rm = (real) sqrt(rm2);
  }

  /* hard sphere, no collision */
  if (fabs(ra2 - rb2) < 2e-6 && npr > -inf/10 && npr < inf/10) {
    npr = 0; /* number of neighbors */
  }
  return -npr; /* increased number of pairs == decreased energy */
}


/* commit a particle displacement for a square well potential */
INLINE void lj_commitsq2d(lj_t *lj, int i, const real *xi, int du)
{
  rv2_copy(lj->x + i*2, xi);
  lj->iepot += du;
  lj->epot += du;
}

/* commit a particle displacement for a square well potential */
INLINE void lj_commitsq3d(lj_t *lj, int i, const real *xi, int du)
{
  rv3_copy(lj->x + i*3, xi);
  lj->iepot += du;
  lj->epot += du;
}


/* Metropolis for a square well */
INLINE int lj_metrosq2d(lj_t *lj, real amp, real bet)
{
  int i, du;
  real xi[2], rm;

  i = lj_randmv2d(lj, xi, amp);
  rm = lj->rmin;
  du = lj_depotsq2d(lj, i, xi, &rm);
  /* patch for bet = 0 */
  if (bet >= 0 && du > lj->esqinf/2) return 0;
  if (metroacc1(du, bet)) {
    lj_commitsq2d(lj, i, xi, du);
    lj->rmin = rm;
    return 1;
  }
  return 0;
}

/* Metropolis for a square well */
INLINE int lj_metrosq3d(lj_t *lj, real amp, real bet)
{
  int i, du;
  real xi[3], rm;

  i = lj_randmv3d(lj, xi, amp);
  rm = lj->rmin;
  du = lj_depotsq3d(lj, i, xi, &rm);
  /* patch for bet = 0 */
  if (bet >= 0 && du > lj->esqinf/2) return 0;
  if (metroacc1(du, bet)) {
    lj_commitsq3d(lj, i, xi, du);
    lj->rmin = rm;
    return 1;
  }
  return 0;
}


/* compute energy data for a particle pair, with switched potential  */
INLINE int lj_pairsw2d(lj_t *lj, real *xi, real *xj, real *u, real *vir)
{
  real dx[2], dr2, dr, fscal, psi, ksi;
  dr2 = lj_pbcdist2_2d(dx, xi, xj, lj->l);
  if (dr2 < lj->rc2) {
    dr = (real) sqrt(dr2);
    *u = lj_potsw(lj, dr, &fscal, &psi, &ksi);
    *vir = fscal * dr2; /* f.r */
    return 1;
  } else return 0;
}

/* compute energy data for a particle pair, with switched potential  */
INLINE int lj_pairsw3d(lj_t *lj, real *xi, real *xj, real *u, real *vir)
{
  real dx[3], dr2, dr, fscal, psi, ksi;
  dr2 = lj_pbcdist2_3d(dx, xi, xj, lj->l);
  if (dr2 < lj->rc2) {
    dr = (real) sqrt(dr2);
    *u = lj_potsw(lj, dr, &fscal, &psi, &ksi);
    *vir = fscal * dr2; /* f.r */
    return 1;
  } else return 0;
}


/* return the energy change from displacing x[i] to xi */
INLINE real lj_depotsw2d(lj_t *lj, int i, real *xi, real *vir)
{
  int j, n = lj->n;
  real u = 0.f, du = 0.f, dvir = 0.f;
  rv2_t *x = (rv2_t *) lj->x;

  *vir = 0.0f;
  for (j = 0; j < n; j++) { /* pair */
    if (j == i) continue;
    if (lj_pairsw2d(lj, x[i], x[j], &du, &dvir)) {
      u -= du;
      *vir -= dvir;
    }
    if (lj_pairsw2d(lj, xi, x[j], &du, &dvir)) {
      u += du;
      *vir += dvir;
    }
  }
  return u;
}

/* return the energy change from displacing x[i] to xi */
INLINE real lj_depotsw3d(lj_t *lj, int i, real *xi, real *vir)
{
  int j, n = lj->n;
  real u = 0.f, du = 0.f, dvir = 0.f;
  rv3_t *x = (rv3_t *) lj->x;

  *vir = 0.0f;
  for (j = 0; j < n; j++) { /* pair */
    if (j == i) continue;
    if (lj_pairsw3d(lj, x[i], x[j], &du, &dvir)) {
      u -= du;
      *vir -= dvir;
    }
    if (lj_pairsw3d(lj, xi, x[j], &du, &dvir)) {
      u += du;
      *vir += dvir;
    }
  }
  return u;
}


/* commit a particle displacement
 * like energysw2d, it does not set pair data, lj->pr
 * call lj_forcesw2d() if it is needed */
INLINE void lj_commitsw2d(lj_t *lj, int i, const real *xi, real du, real dvir)
{
  rv2_copy(lj->x + i*2, xi);
  lj->epot0 += du;
  lj->epot += du;
  lj->vir += dvir;
}

/* commit a particle displacement
 * like energysw3d, it does not set pair data, lj->pr
 * call lj_forcesw3d() if it is needed */
INLINE void lj_commitsw3d(lj_t *lj, int i, const real *xi, real du, real dvir)
{
  rv3_copy(lj->x + i*3, xi);
  lj->epot0 += du;
  lj->epot += du;
  lj->vir += dvir;
}


/* Metropolis algorithm */
INLINE int lj_metrosw2d(lj_t *lj, real amp, real bet)
{
  int i;
  real xi[2], du, dvir;

  i = lj_randmv2d(lj, xi, amp);
  du = lj_depotsw2d(lj, i, xi, &dvir);
  if (metroacc1(du, bet)) {
    lj_commitsw2d(lj, i, xi, du, dvir);
    return 1;
  }
  return 0;
}

/* Metropolis algorithm */
INLINE int lj_metrosw3d(lj_t *lj, real amp, real bet)
{
  int i;
  real xi[3], du, dvir;

  i = lj_randmv3d(lj, xi, amp);
  du = lj_depotsw3d(lj, i, xi, &dvir);
  if (metroacc1(du, bet)) {
    lj_commitsw3d(lj, i, xi, du, dvir);
    return 1;
  }
  return 0;
}


/* compute energy data for a 2D Lennard-Jones pair */
INLINE int lj_pairlj2d(real *xi, real *xj, real l, real rc2,
    real *u, real *vir)
{
  real dx[2], dr2, invr2, invr6;
  dr2 = lj_pbcdist2_2d(dx, xi, xj, l);
  if (dr2 < rc2) {
    invr2 = 1.0f / dr2;
    invr6 = invr2 * invr2 * invr2;
    *vir = invr6 * (48.f * invr6 - 24.f); /* f.r */
    *u  = 4.f * invr6 * (invr6 - 1.f);
    return 1;
  } else return 0;
}

/* compute energy data for a 3D Lennard-Jones pair */
INLINE int lj_pairlj3d(real *xi, real *xj, real l, real rc2,
    real *u, real *vir)
{
  real dx[3], dr2, invr2, invr6;
  dr2 = lj_pbcdist2_3d(dx, xi, xj, l);
  if (dr2 < rc2) {
    invr2 = 1.0f / dr2;
    invr6 = invr2 * invr2 * invr2;
    *vir = invr6 * (48.f * invr6 - 24.f); /* f.r */
    *u  = 4.f * invr6 * (invr6 - 1.f);
    return 1;
  } else return 0;
}


/* return the energy change from displacing x[i] to xi */
INLINE real lj_depotlj2d(lj_t *lj, int i, real *xi, real *vir)
{
  int j, n = lj->n;
  real l = lj->l, rc2 = lj->rc2, u = 0.f, du = 0.f, dvir = 0.f;
  rv2_t *x = (rv2_t *) lj->x;

  *vir = 0.0f;
  for (j = 0; j < n; j++) { /* pair */
    if (j == i) continue;
    if (lj_pairlj2d(x[i], x[j], l, rc2, &du, &dvir)) {
      u -= du;
      *vir -= dvir;
    }
    if (lj_pairlj2d(xi, x[j], l, rc2, &du, &dvir)) {
      u += du;
      *vir += dvir;
    }
  }
  return u;
}

/* return the energy change from displacing x[i] to xi */
INLINE real lj_depotlj3d(lj_t *lj, int i, real *xi, real *vir)
{
  int j, n = lj->n;
  real l = lj->l, rc2 = lj->rc2, u = 0.f, du = 0.f, dvir = 0.f;
  rv3_t *x = (rv3_t *) lj->x;

  *vir = 0.0f;
  for (j = 0; j < n; j++) { /* pair */
    if (j == i) continue;
    if (lj_pairlj3d(x[i], x[j], l, rc2, &du, &dvir)) {
      u -= du;
      *vir -= dvir;
    }
    if (lj_pairlj3d(xi, x[j], l, rc2, &du, &dvir)) {
      u += du;
      *vir += dvir;
    }
  }
  return u;
}


/* commit a particle displacement */
INLINE void lj_commitlj2d(lj_t *lj, int i, const real *xi, real du, real dvir)
{
  rv2_copy(lj->x + i*2, xi);
  lj->epot0 += du;
  lj->epot += du;
  lj->vir += dvir;
}

/* commit a particle displacement */
INLINE void lj_commitlj3d(lj_t *lj, int i, const real *xi, real du, real dvir)
{
  rv3_copy(lj->x + i*3, xi);
  lj->epot0 += du;
  lj->epot += du;
  lj->vir += dvir;
}


INLINE int lj_metrolj2d(lj_t *lj, real amp, real bet)
{
  int i;
  real xi[2], du = 0.f, dvir = 0.f;

  i = lj_randmv2d(lj, xi, amp);
  du = lj_depotlj2d(lj, i, xi, &dvir);
  if (metroacc1(du, bet)) {
    lj_commitlj2d(lj, i, xi, du, dvir);
    return 1;
  }
  return 0;
}

INLINE int lj_metrolj3d(lj_t *lj, real amp, real bet)
{
  int i;
  real xi[3], du = 0.f, dvir = 0.f;

  i = lj_randmv3d(lj, xi, amp);
  du = lj_depotlj3d(lj, i, xi, &dvir);
  if (metroacc1(du, bet)) {
    lj_commitlj3d(lj, i, xi, du, dvir);
    return 1;
  }
  return 0;
}


/* return the pair energy between two particles at xi and xj */
INLINE int lj_pair2d(lj_t *lj, real *xi, real *xj, real *u, real *vir)
{
  if (lj->usesq) return lj_pairsq2d(xi, xj, lj->l, lj->ra2, lj->rb2, NULL, lj->esqinf);
  if (lj->usesw) return lj_pairsw2d(lj, xi, xj, u, vir);
  return lj_pairlj2d(xi, xj, lj->l, lj->rc2, u, vir);
}

/* return the pair energy between two particles at xi and xj */
INLINE int lj_pair3d(lj_t *lj, real *xi, real *xj, real *u, real *vir)
{
  if (lj->usesq) return lj_pairsq3d(xi, xj, lj->l, lj->ra2, lj->rb2, NULL, lj->esqinf);
  if (lj->usesw) return lj_pairsw3d(lj, xi, xj, u, vir);
  return lj_pairlj3d(xi, xj, lj->l, lj->rc2, u, vir);
}


/* return the pair energy between two particles at xi and xj */
INLINE int lj_pair(lj_t *lj, real *xi, real *xj, real *u, real *vir)
{
  return lj->d == 2 ?  lj_pair2d(lj, xi, xj, u, vir) : lj_pair3d(lj, xi, xj, u, vir);
}


/* return the energy change from displacing x[i] to xi */
INLINE real lj_depot2d(lj_t *lj, int i, real *xi, real *vir, real *rmin)
{
  if (lj->usesq) return (real) lj_depotsq2d(lj, i, xi, rmin);
  if (lj->usesw) return lj_depotsw2d(lj, i, xi, vir);
  return lj_depotlj2d(lj, i, xi, vir);
}

/* return the energy change from displacing x[i] to xi */
INLINE real lj_depot3d(lj_t *lj, int i, real *xi, real *vir, real *rmin)
{
  if (lj->usesq) return (real) lj_depotsq3d(lj, i, xi, rmin);
  if (lj->usesw) return lj_depotsw3d(lj, i, xi, vir);
  return lj_depotlj3d(lj, i, xi, vir);
}


/* return the energy change from displacing x[i] to xi */
INLINE real lj_depot(lj_t *lj, int i, real *xi, real *vir, real *rmin)
{
  return lj->d == 2 ?  lj_depot2d(lj, i, xi, vir, rmin)
    : lj_depot3d(lj, i, xi, vir, rmin);
}


/* this is defined as a macro for du is `int' in sq case, but real in other cases */
#define lj_commit2d(lj, i, xi, du, dvir) { \
  (lj->usesq) ? lj_commitsq2d(lj, i, xi, du) : \
  (lj->usesw) ? lj_commitsw2d(lj, i, xi, du, dvir) : \
                lj_commitlj2d(lj, i, xi, du, dvir); }

/* this is defined as a macro for du is `int' in sq case, but real in other cases */
#define lj_commit3d(lj, i, xi, du, dvir) { \
  (lj->usesq) ? lj_commitsq3d(lj, i, xi, du) : \
  (lj->usesw) ? lj_commitsw3d(lj, i, xi, du, dvir) : \
                lj_commitlj3d(lj, i, xi, du, dvir); }

/* commit a move */
#define  lj_commit(lj, i, xi, du, dvir) \
  (lj->d == 2 ? lj_commit2d(lj, i, xi, du, dvir) \
              : lj_commit3d(lj, i, xi, du, dvir); )

INLINE int lj_metro2d(lj_t *lj, real amp, real bet)
{
  if (lj->usesq) return lj_metrosq2d(lj, amp, bet);
  if (lj->usesw) return lj_metrosw2d(lj, amp, bet);
  return lj_metrolj2d(lj, amp, bet);
}

INLINE int lj_metro3d(lj_t *lj, real amp, real bet)
{
  if (lj->usesq) return lj_metrosq3d(lj, amp, bet);
  if (lj->usesw) return lj_metrosw3d(lj, amp, bet);
  return lj_metrolj3d(lj, amp, bet);
}


/* Metropolis algorithm */
INLINE int lj_metro(lj_t *lj, real amp, real bet)
{ return lj->d == 2 ? lj_metro2d(lj, amp, bet) : lj_metro3d(lj, amp, bet); }


/* return the energy change of locally displacing a single atom */
INLINE real lj_dupertl2d(lj_t *lj, real amp)
{
  real dvir, xi[2], rmin;
  int i;

  i = lj_randmv2d(lj, xi, amp);
  return lj_depot2d(lj, i, xi, &dvir, &rmin);
}

/* return the energy change of locally displacing a single atom */
INLINE real lj_dupertl3d(lj_t *lj, real amp)
{
  real dvir, xi[3], rmin;
  int i;

  i = lj_randmv3d(lj, xi, amp);
  return lj_depot3d(lj, i, xi, &dvir, &rmin);
}


INLINE real lj_dupertl(lj_t *lj, real amp)
{ return lj->d == 2 ? lj_dupertl2d(lj, amp) : lj_dupertl3d(lj, amp); }


/* return the energy change by random displacements of all atoms */
INLINE real lj_dupertg2d(lj_t *lj, real amp)
{
  int i, d, iep;
  rv2_t *nx;
  real du, vir, rmin, ep0, eps, lap;

  xnew(nx, lj->n);
  amp /= lj->l; /* convert to the reduced unit */
  for (i = 0; i < lj->n; i++)
    for (d = 0; d < 2; d++)
      nx[i][d] = lj->x[i*2 + d] + (real) randunif(-amp, amp);
  du = lj_energyx2d(lj, nx, &vir, &iep, &rmin, &ep0, &eps, &lap) - lj->epot;
  free(nx);
  return du;
}

/* return the energy change by random displacements of all atoms */
INLINE real lj_dupertg3d(lj_t *lj, real amp)
{
  int i, d, iep;
  rv3_t *nx;
  real du, vir, rmin, ep0, eps, lap;

  xnew(nx, lj->n);
  amp /= lj->l; /* convert to the reduced unit */
  for (i = 0; i < lj->n; i++)
    for (d = 0; d < 3; d++)
      nx[i][d] = lj->x[i*3 + d] + (real) randunif(-amp, amp);
  du = lj_energyx3d(lj, nx, &vir, &iep, &rmin, &ep0, &eps, &lap) - lj->epot;
  free(nx);
  return du;
}


INLINE real lj_dupertg(lj_t *lj, real amp)
{ return lj->d == 2 ? lj_dupertg2d(lj, amp) : lj_dupertg3d(lj, amp); }


/* return the energy caused by inserting a random atom
   the tail correction is not applied */
INLINE real lj_duinsert2d(lj_t *lj, real *xt)
{
  int j, n = lj->n;
  real xt0[2], u, du, dvir;

  if (xt == NULL)
    for (xt = xt0, j = 0; j < 3; j++)
      xt[j] = (real) rand01();
  for (u = 0.f, j = 0; j < n; j++) /* pair energy */
    if (lj_pair(lj, xt, lj->x + 2*j, &du, &dvir))
      u += du;
  return u;
}

/* return the energy caused by inserting a random atom
   the tail correction is not applied */
INLINE real lj_duinsert3d(lj_t *lj, real *xt)
{
  int j, n = lj->n;
  real xt0[3], u, du, dvir;

  if (xt == NULL)
    for (xt = xt0, j = 0; j < 3; j++)
      xt[j] = (real) rand01();
  for (u = 0.f, j = 0; j < n; j++) /* pair energy */
    if (lj_pair(lj, xt, lj->x + 3*j, &du, &dvir))
      u += du;
  return u;
}


INLINE real lj_duinsert(lj_t *lj, real *xt)
{ return lj->d == 2 ? lj_duinsert2d(lj, xt) : lj_duinsert3d(lj, xt); }

/* Lennard-Jones system: molecular dynamics routines */


/* velocity scaling for regular (no thermostat) MD during equilibration
 * `tp' is the target temperature
 * `ekt' is the observed average kinetic energy over several steps */
#define lj_vscale(lj, tp, ekt) \
  md_vscale(lj->v, lj->n * lj->d, lj->dof, tp, ekt, &lj->ekin, &lj->tkin)

#define lj_vrescale(lj, tp, thermdt) \
  md_vrescale(lj->v, lj->n * lj->d, lj->dof, tp, thermdt, &lj->ekin, &lj->tkin)

#define lj_vrescalex(lj, tp, thermdt) \
  md_vrescalex(lj->v, lj->n * lj->d, lj->dof, tp, thermdt, &lj->ekin, &lj->tkin);

#define lj_mcvrescale(lj, tp, thermdt) \
  md_mcvrescale(lj->v, lj->n * lj->d, lj->dof, tp, thermdt, &lj->ekin, &lj->tkin);


#define lj_vv(lj, dt) lj_vvx(lj, 1.f, dt)

/* velocity Verlet */
INLINE void lj_vvx(lj_t *lj, real fscal, real dt)
{
  int i, nd = lj->n * lj->d;
  real dtl = dt / lj->l, dthf = dt * .5f * fscal;

  for (i = 0; i < nd; i++) { /* VV part 1 */
    lj->v[i] += lj->f[i] * dthf;
    lj->x[i] += lj->v[i] * dtl;
  }
  lj_force(lj); /* calculate the new force */
  for (i = 0; i < nd; i++) /* VV part 2 */
    lj->v[i] += lj->f[i] * dthf;

  lj->ekin = md_ekin(lj->v, nd, lj->dof, &lj->tkin);
}


/* Nose-Hoover thermostat/barostat
 * set cutoff to half of the box */
#define lj_hoovertp(lj, dt, tp, pext, zeta, eta, Q, W, ensx) \
  md_hoovertp(lj->v, lj->n, lj->d, lj->dof, dt, tp, pext, zeta, eta, \
      Q, W, lj->vol, lj->vir, lj->p_tail, ensx, &lj->ekin, &lj->tkin)


/* Nose-Hoover chain thermostat/barostat
 * set cutoff to half of the box */
#define lj_nhchaintp(lj, dt, tp, pext, zeta, eta, Q, M, W, ensx) \
  md_nhchaintp(lj->v, lj->n, lj->d, lj->dof, dt, tp, pext, zeta, eta, \
      Q, M, W, lj->vol, lj->vir, lj->p_tail, ensx, &lj->ekin, &lj->tkin)


/* Langevin barostat, with kinetic-energy scaling */
#define lj_langtp(lj, dt, tp, pext, zeta, eta, W, ensx) \
  md_langtp(lj->v, lj->n, lj->d, dt, tp, pext, zeta, eta, \
      W, lj->vol, lj->vir, lj->p_tail, ensx, &lj->ekin, &lj->tkin)


/* position Langevin barostat, with kinetic-energy scaling */
INLINE void lj_langtp0(lj_t *lj, real barodt, real tp, real pext, int ensx)
{
  md_langtp0(lj->v, lj->n, lj->d, barodt, tp, pext, &lj->vol,
      lj->vir, lj->p_tail, ensx, &lj->ekin, &lj->tkin);
  lj_setrho(lj, lj->n/lj->vol);
  lj_force(lj);
}


/* old interface */
#define lj_lgvvolmove(lj, barodt, tp, p) \
  lj_langp0(lj, barodt, tp, p, 0)

/* Langevin barostat, with coordinates only, barodt ~ 1e-5 for n = 108 */
INLINE void lj_langp0(lj_t *lj, real barodt, real tp, real pext, int ensx)
{
  md_langp0(lj->dof, lj->d, barodt, tp, pext, &lj->vol, lj->vir, lj->p_tail, ensx);
  lj_setrho(lj, lj->n/lj->vol);
  lj_force(lj);
}

/* velocity Verlet with the scaling step in the Nose-Hoover barostat */
INLINE void lj_vv_hoovertp(lj_t *lj, real dt, real eta)
{
  int i, nd = lj->n*lj->d;
  real dt2 = dt * .5f, xp;

  for (i = 0; i < nd; i++) /* VV part 1 */
    lj->v[i] += lj->f[i] * dt2;

  /* position update with scaling */
  md_hoovertpdr(lj->x, lj->v, nd, &xp, lj->l, eta, dt);
  lj->l *= xp;
  lj_setrho(lj, lj->rho/(xp*xp*xp));
  lj_force(lj); /* calculate the new force */

  for (i = 0; i < nd; i++) /* VV part 2 */
    lj->v[i] += lj->f[i] * dt2;

  lj->ekin = md_ekin(lj->v, nd, lj->dof, &lj->tkin);
}


/* Berendsen barostat: as a backup for constant pressure simulation */
INLINE void lj_pberendsen(lj_t *lj, real barodt, real tp, real pext)
{
  int i;
  real pint, vn, lo = lj->l, s, dlnv;

  pint = (lj->vir + 2.f * lj->ekin)/ (lj->d * lj->vol) + lj->p_tail;

  /* proposed change of log V */
  dlnv = (pint - pext)*lj->vol/tp*barodt;
  if (dlnv < -0.1) dlnv = -0.1; else if (dlnv > 0.1) dlnv = 0.1;
  vn = log(lj->vol) + dlnv;
  vn = exp(vn);
  lj_setrho(lj, lj->n/vn);
  s = lo/lj->l;
  for (i = 0; i < lj->d * lj->n; i++) lj->v[i] *= s;
  lj->ekin *= s*s;
  lj->tkin *= s*s;
}


/* In Monte Carlo barostats, we compute the energy directly */
#define LJ_FIXEDRC 0x4000

#define lj_mcprescale(lj, lnvamp, tp, pext, vmin, vmax, ensx) \
  lj_mctp(lj, lnvamp, tp, pext, vmin, vmax, ensx, 0)

/* Monte Carlo barostat, with kinetic-energy scaling
 * the ideal gas part computed as \sum p^2/m / V
 * the scaling is r = r*s, p = p/s;
 * set cutoff to half of the box */
INLINE int lj_mctp(lj_t *lj, real lnvamp, real tp, real pext,
    real vmin, real vmax, int ensx, unsigned flags)
{
  int acc = 0, i, d = lj->d;
  real lnlo, lnln, lo, ln, vo, vn, s, epo, bet = 1.f/tp;
  double dex;
  lj_t *lj1;

  vo = lj->vol;
  lo = lj->l;
  lnlo = (real) log(lo);
  lnln = (real) (lnlo + lnvamp/d * randunif(-1, 1));
  ln = (real) exp(lnln);
  for (vn = 1, i = 0; i < d; i++) vn *= ln;
  if (vn < vmin || vn >= vmax)
    return 0;
  if ((flags & LJ_FIXEDRC) && ln < lj->rc * 2)
    return 0; /* box too small */

  epo = lj->epot;
  lj1 = lj_clone(lj, LJ_CPF); /* make a copy */
  lj_setrho(lj, lj->n/vn);
  lj_force(lj); /* we change force here */
  dex = bet * (lj->epot - epo + pext * (vn - vo))
      + bet * (pow(vo/vn, 2.0/d) - 1)*lj->ekin
      + d * (lnlo - lnln) * (1 - ensx);
  if (metroacc1(dex, 1.f)) { /* scale the velocities */
    s = lo/lj->l;
    for (i = 0; i < d * lj->n; i++) lj->v[i] *= s;
    lj->ekin *= s*s;
    lj->tkin *= s*s;
    acc = 1;
  } else {
    lj_copy(lj, lj1, LJ_CPF); /* restore force etc. */
  }
  lj_close(lj1);
  return acc;
}


/* Monte Carlo barostat for the square-well potential, for coordinates only
 * suppose lj->rmin has been correctly set
 * use lnvamp 0.03 ~ 0.06 for 256 system */
INLINE int lj_mcpsq(lj_t *lj, real lnvamp, real tp, real pext,
    real vmin, real vmax, int ensx, unsigned flags)
{
  int acc = 0, i, d = lj->d, iep;
  real lnlo, lnln, vo, vn, lo, ln, rmn = 0, epo, bet = 1.f/tp;
  double dex;

  (void) flags;
  vo = lj->vol;
  lo = lj->l;
  lnlo = (real) log(lo);
  lnln = (real) (lnlo + lnvamp/d * randunif(-1, 1));
  ln = (real) exp(lnln);
  for (vn = 1, i = 0; i < d; i++) vn *= ln;
  if (vn < vmin || vn >= vmax) return 0;

  /* check if there is a clash */
  rmn = lj->rmin * ln / lo;
  if (ln < lo) {
    if (ln < lj->rb * 2) return 0; /* box too small */
    if (rmn < lj->ra) return 0;
  }

  /* compute the change of the square-well energy */
  epo = lj->epot;
  lj_setrho(lj, lj->n/vn); /* commit to the new box */
  if (fabs(lj->ra - lj->rb) < 1e-6) { /* skip the energy calculation */
    iep = 0;
  } else {
    if (d == 3) {
      iep = lj_energysq3d(lj, (rv3_t *) lj->x, &rmn);
    } else {
      iep = lj_energysq2d(lj, (rv2_t *) lj->x, &rmn);
    }
  }
  dex = bet * ((real) iep - epo + pext * (vn - vo))
      - (lj->dof + (1 - ensx) * d) * (lnln - lnlo);
  if (rmn > lj->ra && metroacc1(dex, 1.0)) {
    lj->iepot = iep;
    lj->epot = iep;
    lj->rmin = rmn;
    acc = 1;
  } else {
    lj_setrho(lj, lj->n/vo);
  }
  return acc;
}


/* Monte Carlo barostat, coordinates only
 * use lnvamp 0.03 ~ 0.06 for 256 system */
INLINE int lj_mcplj(lj_t *lj, real lnvamp, real tp, real pext,
    real vmin, real vmax, int ensx, unsigned flags)
{
  int acc = 0, i, d = lj->d;
  real lnlo, lnln, lo, ln, vo, vn, epo, bet = 1.f/tp;
  double dex;
  lj_t *lj1;

  vo = lj->vol;
  lo = lj->l;
  lnlo = (real) log(lo);
  lnln = (real) (lnlo + lnvamp/d * randunif(-1, 1));
  ln = (real) exp(lnln);
  for (vn = 1, i = 0; i < d; i++) vn *= ln;
  if (vn < vmin || vn >= vmax)
    return 0;
  if ((flags & LJ_FIXEDRC) && ln < lj->rc * 2)
    return 0; /* box too small */

  epo = lj->epot;
  lj1 = lj_clone(lj, LJ_CPF); /* save a copy */
  lj_setrho(lj, lj->n/vn); /* commit to the new box */
  lj_force(lj);
  dex = bet * (lj->epot - epo + pext * (vn - vo))
      - (lj->dof + (1 - ensx) * d) * (lnln - lnlo);
  if (metroacc1(dex, 1.0)) {
    acc = 1;
  } else {
    lj_copy(lj, lj1, LJ_CPF);
  }
  lj_close(lj1);
  return acc;
}


/* old interface */
#define lj_volmove(lj, lnlamp, tp, p) \
  lj_mcp(lj, lnlamp*lj->d, tp, p, 0, 1e300, 0, LJ_FIXEDRC)

/* Monte Carlo barostat, coordinates only */
INLINE int lj_mcp(lj_t *lj, real lnvamp, real tp, real pext,
    real vmin, real vmax, int ensx, unsigned flags)
{
  if (lj->usesq) { /* use the specialized square-well version */
    return lj_mcpsq(lj, lnvamp, tp, pext, vmin, vmax, ensx, flags);
  } else { /* use the generic version */
    return lj_mcplj(lj, lnvamp, tp, pext, vmin, vmax, ensx, flags);
  }
}

/* Lennard-Jones system: compute the radial distribution function (RDF)
 * using a specially normalized histogram, cf. hist/testrdf.c */


typedef struct {
  hist_t *rdf; /* histogram for radial distribution function */
  int nfr; /* number of frames in rdf */
  av_t avn[1]; /* average of the number of particles */
  lj_t *lj;
  double cfac;
} ljrdf_t;


/* open an ljrdf structure, `rmax' can be 0 */
INLINE ljrdf_t *ljrdf_open(lj_t *lj, double dr, double rmax)
{
  ljrdf_t *ljr;

  xnew(ljr, 1);
  ljr->nfr = 0;
  ljr->lj = lj;
  if (rmax <= 0)
    rmax = (int) (lj->l * .5 / dr) * dr;
  av_clear(ljr->avn);
  ljr->rdf = hs_open(1, 0, rmax, dr);
  ljr->cfac = 1;
  return ljr;
}


INLINE void ljrdf_close(ljrdf_t *ljr)
{
  hs_close(ljr->rdf);
  free(ljr);
}


/* add pairs to the RDF data */
INLINE int ljrdf_add(ljrdf_t *ljr, unsigned flags)
{
  lj_t *lj = ljr->lj;
  int i, j;
  real rc2, dr2, dx[3];
  double dr;

  rc2 = ljr->lj->l/2;
  rc2 = rc2 * rc2;
  for (i = 0; i < lj->n; i++) {
    for (j = i + 1; j < lj->n; j++) {
      if (lj->d == 2)
        dr2 = lj_pbcdist2_2d(dx, lj->x + 2*i, lj->x + 2*j, lj->l);
      else
        dr2 = lj_pbcdist2_3d(dx, lj->x + 3*i, lj->x + 3*j, lj->l);
      if (dr2 >= rc2) continue;
      dr = sqrt(dr2);
      hs_add(ljr->rdf, &dr, 1.0, flags);
    }
  }
  av_add(ljr->avn, lj->n);
  return ++ljr->nfr; /* number of frames */
}


/* header information in writing rdf */
INLINE int ljrdf_fwheader(FILE *fp, void *pdata)
{
  ljrdf_t *ljr = (ljrdf_t *) pdata;
  double nav, nvar;

  nav = av_getave(ljr->avn);
  nvar = av_getvar(ljr->avn);
  fprintf(fp, "RDF %d %d %d %.10e %.10e %.10e %.10e | ",
      ljr->nfr, ljr->lj->d, ljr->lj->n, ljr->lj->l,
      nav, nvar, ljr->cfac);
  return 0;
}


/* header information in reading rdf */
INLINE int ljrdf_frheader(const char *s, void *pdata)
{
  ljrdf_t *ljr = (ljrdf_t *) pdata;
  lj_t *lj = ljr->lj;
  int ret, d, n;
  double l;

  ret = sscanf(s, " RDF %d%d%d%lf ", &(ljr->nfr), &d, &n, &l);
  die_if (d != lj->d, "dimension mismatch %d vs. %d (file)\n", lj->d, d);
  /* in the grand-canonical ensemble the number of particles may not match */
/*
  die_if (n != lj->n, "# of particle mismatch %d vs. %d (file)\n", lj->n, n);
*/
  die_if (fabs(l - lj->l) > 1e-3, "box size mismatch %d vs. %d (file)\n", lj->l, l);
  return (ret == 4) ? 0 : 1;
}


/* normalization */
INLINE double ljrdf_norm(int row, int i, double xmin, double dx, void *pdata)
{
  double x, vsph, nav, npr;
  ljrdf_t *ljr = (ljrdf_t *) pdata;
  lj_t *lj = ljr->lj;

  (void) row;
  x = xmin + i * dx;
  if (lj->d == 2) vsph = 2. * M_PI * dx * (2*x + dx);
  else vsph = 4. * M_PI * dx * (x*(x + dx) + dx*dx/3.);
  nav = av_getave(ljr->avn);
  /* modified g*(r) such that g*(r) = 1 as r goes to infinity
   *
   * The histogram is normalized as
   *  Sum_i h_i = <N(N-1)/2> N_{fr}
   *
   * The true radial distribution function is normalized as
   *  Sum_r g(r) vsph(r) = Int {r = 0 to R} g(r) 4 pi r^2 dr
   *    = V <N(N - 1)> / <N>^2 (by definition)
   *
   *  Sum_r g(r) Vsph(r) <N>^2/(2V) N_{fr} = Sum_i h_i
   * So
   *    g(r) = h_i V / (<N>^2/2) / vsphr / N_{fr}.
   *
   *  However, for the canonical ensemble, g*(r) is normalized such that
   *    1 + rho Int [g*(r) - 1] 4 pi r^2 dr = <dN^2>/<N> = d(rho)/d(beta P)
   *    Int g*(r) 4 pi r^2 dr = {N - [1 - d(rho)/d(beta P)]} / rho.
   * */
  npr = nav * nav / 2;
  return ljr->cfac * lj->vol / (vsph * npr * ljr->nfr);
}


/* save rdf, flags can have HIST_NOZEROES */
INLINE int ljrdf_save(ljrdf_t *ljr, const char *fn, unsigned flags)
{
  return hs_savex(ljr->rdf, fn, ljrdf_fwheader, ljrdf_norm, ljr, flags);
}


/* load rdf, flags can have HIST_ADDITION and/or HIST_VERBOSE */
INLINE int ljrdf_load(ljrdf_t *ljr, const char *fn, unsigned flags)
{
  return hs_loadx(ljr->rdf, fn, ljrdf_frheader, ljrdf_norm, ljr, flags);
}


#endif /* ZCOM_LJ__ */
#endif /* ZCOM_LJ */





#ifdef  ZCOM_ABPRO
#ifndef ZCOM_ABPRO__
#define ZCOM_ABPRO__
#ifdef _OPENMP
#include <omp.h>
#endif

typedef struct {
  int i, j;
  int on; /* constraint is active */
  real dx0[3]; /* difference */
  real r2ref; /* square of the reference distance */
} lgconstr_t;

typedef struct {
  int i, j;
  int tid; /* thread */
  real c;
} abpairid_t; /* pair index */

typedef struct {
  int d; /* dimension */
  int model; /* 1 or 2 */
  int seqid; /* model sequence id */
  int n; /* number of atoms */
  int dof, dof0; /* number of degrees of freedom */
  real clj[2][2], sla, slb;
  int *type; /* 0: A, 1: B */
  real *x, *x1, *dx;
  real *v;
  real *f;
  real *lmx, *xmin;
  real emin, epot, ekin, tkin;
  double t;

  int lgcon; /* enable local constraints */
  int lgcnt; /* total local constraints */
  int lgact; /* active local constraints */
  lgconstr_t *lgc;

#define AB_XXCNT 6
  real *xx[AB_XXCNT]; /* extra memory allocations, each of the size of x */

#ifdef _OPENMP
  int nthreads; /* number of threads */
  real *f_l; /* local force */
  int *homeid; /* [homeid[tid], homeid[tid + 1]): atoms belongs to thread id */
  int paircnt; /* number of pairs */
  abpairid_t *pair; /* the entire pair */
  int *pairid; /* [pairid[tid], pairid[tid + 1]): pairs belong to thread tid */
#endif
} abpro_t;

#define AB_VERBOSE    0x0001
#define AB_SOFTFORCE  0x0010
#define AB_MILCSHAKE  0x0020
#define AB_LMREGISTER 0x0100
#define AB_LMWRITE    0x0200


#define ab_shiftcom(ab, v)      md_shiftcom(v, ab->n, ab->d)
#define ab_shiftang(ab, x, v)   md_shiftang(x, v, ab->n, ab->d)
/* shift center of x to the origin, remove center velocity and angular momentum */
INLINE void ab_rmcom(abpro_t *ab, real *x, real *v)
{
  ab_shiftcom(ab, x);
  ab_shiftcom(ab, v);
  ab_shiftang(ab, x, v); /* remove angular momentum */
}


INLINE real ab_force(abpro_t *ab, real *r, real *f, int soft);


#ifdef _OPENMP
/* compare pair by thread id */
static int ab_prcmp(const void *a, const void *b)
{ return ((abpairid_t *) a)->tid - ((abpairid_t *) b)->tid; }
#endif


/* check connectivity */
INLINE int ab_checkconn(abpro_t *ab, const real *x, double tol)
{
  int i, d = ab->d;
  real r;

  if (tol <= 0.) tol = 1e-3;
  for (i = 0; i < ab->n-1; i++) {
    if (d == 3) {
      r = rv3_dist(x + i*3, x + (i+1)*3);
    } else {
      r = rv2_dist(x + i*2, x + (i+1)*2);
    }
    if (fabs(r-1) > tol) {
      fprintf(stderr, "link (%d,%d) is broken, r = %g\n", i, i+1, r);
      return 1;
    }
  }
  return 0;
}


/* initialize an almost straight chain,
 * randomness given by del */
INLINE int ab_initpos(abpro_t *ab, real *x, real del)
{
  int i, j;
  real dx[3];

  for (j = 0; j < ab->d; j++) ab->x[j] = 0;
  for (i = 0; i < ab->n - 1; i++) {
    for (j = 0; j < ab->d; j++) {
      dx[j] = (2.f*rand()/RAND_MAX - 1)*del + ((j == 0) ? 1.f : 0.f);
    }
    if (ab->d == 3) {
      rv3_normalize(dx);
      rv3_add(x + (i+1)*ab->d, x + i*ab->d, dx);
    } else {
      rv2_normalize(dx);
      rv2_add(x + (i+1)*ab->d, x + i*ab->d, dx);
    }
  }
  ab_shiftcom(ab, x);
  die_if (ab_checkconn(ab, x, 0) != 0, "initpos failed, with del = %g\n", del);
  return 0;
}


/* initialization
 * seqid: 8: 34, 9: 55, 10: 89 */
INLINE abpro_t *ab_open(int seqid, int d, int model, real randdev)
{
  abpro_t *ab;
  int i, j, nd;
  double x;
  const int verbose = 0;

  die_if (d == 2 && model != 1, "%dd only for model 1", d);
  die_if (seqid < 0, "bad seqid %d\n", seqid);

  xnew(ab, 1);
  ab->d = d;

  ab->model = model;
  if (model == 1) { /* initialize model */
    ab->clj[0][0] = 1; ab->clj[1][1] = .5f;
    ab->clj[0][1] = ab->clj[1][0] = -.5f;
    ab->sla = ab->slb = 24;
  } else {
    ab->clj[0][0] = 1;
    ab->clj[0][1] = ab->clj[1][0] = ab->clj[1][1] = .5f;
    ab->sla = ab->slb = 24;
  }

  ab->seqid = seqid;
  /* determine # of atoms */
  x = pow(.5*(sqrt(5.) + 1), seqid + 1);
  i = (seqid % 2) ? (-1) : 1;
  ab->n = (int)( (x + i/x)/sqrt(5.) + .5);

  /* construct sequence */
  xnew(ab->type, ab->n);
  if (seqid < 2) {
    ab->type[0] = seqid;
  } else {
    int *s[2], sl[2], who;
    xnew(s[0], ab->n);
    xnew(s[1], ab->n);
    s[0][0] = 0; sl[0] = 1;
    s[1][0] = 1; sl[1] = 1;
    for (who = 0, i = 2; i <= seqid; i++, who = !who) {
      /* s[who] += s[!who]; */
      die_if (sl[0] + sl[1] > ab->n, "combined length > %d\n", ab->n);
      for (j = 0; j < sl[!who]; j++)
        s[who][sl[who] + j] = s[!who][j];
      sl[who] += sl[!who];
    }
    for (who = !who, j = 0; j < ab->n; j++) {
     ab->type[j] = s[who][j];
    }
    free(s[0]);
    free(s[1]);
  }

  /* number of degrees of freedom */
  ab->dof = ab->dof0 = (ab->d == 2) ? (ab->n - 2) : (2*ab->n - 5);
  if (verbose) {
    printf("n = %3d, d = %d, dof = %3d: ", ab->n, ab->d, ab->dof);
    for (i = 0; i < ab->n; i++)
      printf("%c", ab->type[i]+'A');
    printf("\n");
  }

  nd = ab->n * ab->d;
  xnew(ab->x, nd);
  xnew(ab->x1, nd);
  xnew(ab->v, nd);
  xnew(ab->f, nd);
  xnew(ab->dx, nd);
  xnew(ab->lmx, nd);
  xnew(ab->xmin, nd);

  xnew(ab->xx[0], nd * AB_XXCNT);
  for (i = 1; i < AB_XXCNT; i++)
    ab->xx[i] = ab->xx[0] + i * nd;

#ifdef _OPENMP
  {
    int sz, ir, jr, k;
    abpairid_t *pr;

    ab->nthreads = omp_get_max_threads();
    xnew(ab->f_l, nd * ab->nthreads);

    /* partition home atoms, for thread i: [ab->homeid[i], ab->homeid[i+1]) */
    xnew(ab->homeid, ab->nthreads + 1);
    sz = (ab->n + ab->nthreads - 1) / ab->nthreads; /* chunk size */
    for (i = 0; i < ab->nthreads; i++)
      ab->homeid[ i ] = sz * i;
    ab->homeid[ ab->nthreads ] = ab->n;

    /* make a list of pairs */
    xnew(ab->pair, ab->n * (ab->n - 1) / 2 * sizeof(*ab->pair));
    pr = ab->pair;
    for (i = 0; i < ab->n - 2; i++) {
      for (ir = 0; ir < ab->nthreads; ir++) /* home thread */
        if (i >= ab->homeid[ ir ] && i < ab->homeid[ ir+1 ]) break;
      for (j = i + 2; j < ab->n; j++) {
        for (jr = ir; jr < ab->nthreads; jr++) /* home thread */
          if (j >= ab->homeid[ jr ] && j < ab->homeid[ jr+1 ]) break;
        pr->i = i;
        pr->j = j;
        pr->c = ab->clj[ ab->type[i] ][ ab->type[j] ];
        pr->tid =  (jr > ir && (i + j) % 2 == 0) ? jr : ir;
        pr++;
      }
    }
    ab->paircnt = pr - ab->pair;
    qsort(ab->pair, ab->paircnt, sizeof(*ab->pair), &ab_prcmp);

    /* set up pairid, [pairid[tid], pairid[tid + 1]) pairs for thread tid */
    xnew(ab->pairid, ab->nthreads + 1);
    for (k = 0, ir = 0; ir < ab->nthreads; ir++) {
      for (; k < ab->paircnt; k++)
        if (ab->pair[k].tid == ir) break;
      ab->pairid[ir] = k;
    }
    ab->pairid[ ab->nthreads ] = ab->paircnt;
  }
#endif
  ab_initpos(ab, ab->x, randdev);
  ab->emin = ab->epot = ab_force(ab, ab->x, ab->f, 0);
  return ab;
}


/* close ab */
INLINE void ab_close(abpro_t *ab)
{
  if (!ab) return;
  free(ab->type);
  free(ab->x);
  free(ab->x1);
  free(ab->dx);
  free(ab->v);
  free(ab->f);
  free(ab->lmx);
  free(ab->xmin);
  free(ab->xx[0]);
#ifdef _OPENMP
  free(ab->f_l);
#endif
  free(ab);
}


/* write position file (which may include velocity) */
INLINE int ab_writepos(abpro_t *ab, const real *x, const real *v, const char *fn)
{
  FILE *fp;
  int i, j, d = ab->d, n = ab->n;

  if (fn == NULL) fn = "ab.pos";
  xfopen(fp, fn, "w", return -1);

  fprintf(fp, "# %d %d %d %d %d\n",
      d, ab->model, ab->seqid, n, (v != NULL));
  for (i = 0; i < n; i++) {
    for (j = 0; j < d; j++) fprintf(fp, "%16.14f ", x[i*d+j]);
    if (v)
      for (j = 0; j < d; j++) fprintf(fp, "%16.14f ", v[i*d+j]);
    fprintf(fp, "%d\n", ab->type[i]);
  }
  fclose(fp);
  return 0;
}


/* read position file (which may include velocity) */
INLINE int ab_readpos(abpro_t *ab, real *x, real *v, const char *fn)
{
  char s[1024], *p;
  FILE *fp;
  int i, j, seq, hasv = 0, next, d = ab->d, n = ab->n;
  const char *fmt;
  real vtmp[3], *vi;

  if (fn == NULL) fn = "ab.pos";
  xfopen(fp, fn, "r", return -1);

  if (fgets(s, sizeof s, fp) == NULL || s[0] != '#') {
    fprintf(stderr, "Warning: %s has no information line\n", fn);
    rewind(fp);
  } else {
    if (5 != sscanf(s+1, "%d%d%d%d%d", &i, &j, &seq, &next, &hasv)
        || i != d || j != ab->model || seq != ab->seqid || next != n) {
      fprintf(stderr, "first line is corrupted:\n%s", s);
      goto ERR;
    }
  }

  fmt = (sizeof(double) == sizeof(real)) ? "%lf%n" : "%f%n";
  for (i = 0; i < n; i++) {
    if (fgets(s, sizeof s, fp) == NULL) goto ERR;
    if (strlen(s) < 10) goto ERR;
    for (p = s, j = 0; j < d; j++, p += next)
      if (1 != sscanf(p, fmt, x+i*d+j, &next)) {
        fprintf(stderr, "cannot read i = %d, j = %d\n", i, j);
        goto ERR;
      }
    if (hasv) {
      vi = (v != NULL) ? (v + i*d) : vtmp;
      for (j = 0; j < d; j++, p += next)
        if (1 != sscanf(p, fmt, vi+j, &next)) {
          fprintf(stderr, "cannot read i = %d, j = %d\n", i, j);
          goto ERR;
        }
    }
    if (1 != sscanf(p, "%d", &j) || j != ab->type[i]) {
      fprintf(stderr, "bad type on i = %d, j = %d\n", i, j);
      goto ERR;
    }
  }
  fclose(fp);
  return 0;

ERR:
  fprintf(stderr, "position file [%s] appears to be broken on line %d!\n%s\n", fn, i, s);
  fclose(fp);
  return 1;
}


/* 2D shake with additional constraints */
INLINE int ab_shake2d(abpro_t *ab, rv2_t *x0, rv2_t *x1, rv2_t *v, real dt,
    int itmax, double tol, int verbose)
{
  int i, j, k, again, it, n = ab->n, lgcon = ab->lgcon, lgcnt = ab->lgcnt;
  real dxi[2], g, r2, r2bad, r2ref, tmp, *lgdx0;
  rv2_t *dx0 = (rv2_t *) ab->dx;
  static const real glow = .5, r2max = 4.0;
  lgconstr_t *lgc = ab->lgc;

#ifdef _OPENMP
#pragma omp threadprivate(r2max, glow)
#endif
  /* pre-compute reference difference */
  for (i = 0; i < n-1; i++)
    rv2_diff(dx0[i], x0[i+1], x0[i]);

  /* compute distance in x0 for local constraints */
  for (k = 0; lgcon && k < lgcnt; k++) {
    if (!lgc[k].on) continue;
    i = lgc[k].i;
    j = lgc[k].j;
    rv2_diff(lgc[k].dx0, x0[j], x0[i]);
  }

  for (it = 0; it < itmax; it++) {
    int imin, imax;

    again = 0;
#ifdef _OPENMP
#pragma omp parallel firstprivate(n) private(i, r2, dxi, g)
    {
    int ip = omp_get_thread_num();
    int np = omp_get_num_threads();
    int n1 = n - 1;
    int sz = (n1 + np - 1)/np;
    imin = ip * sz;
    imax = (ip + 1) * sz;
    if (imax > n1) imax = n1;
#else
    imin = 0;
    imax = n - 1;
#endif

    for (i = imin; i < imax; i++) { /* standard constraints */
      r2 = rv2_sqr(rv2_diff(dxi, x1[i + 1], x1[i]));
      if (r2 > r2max) { /* too large, impossible to correct */
        if (verbose)
          fprintf(stderr, "shake: r(%d, %d) = %g\n", i, i+1, sqrt(r2));
        r2 = r2max;
      }

      if (fabs(r2 - 1) > tol) {
        if (!again) { again = 1; r2bad = r2; }

        g = rv2_dot(dxi, dx0[i]);
        if (fabs(g) < glow) { /* inner product too small */
          if (verbose)
            fprintf(stderr, "shake: bad alignment %d-%d, %g, dot = %g\n", i, i+1, sqrt(r2), g);
          g = (g > 0) ? glow : -glow;
        }
        g = (1 - r2) / (4 * g);
        rv2_sinc(x1[i],   dx0[i], -g);
        if (v) rv2_sinc(v[i], dx0[i], -g/dt);
        /* be careful as i + 1 == imax belongs to the next block */
        if (i == imax - 1)
#ifdef _OPENMP
#pragma omp critical
#endif
        {
          rv2_sinc(x1[i + 1], dx0[i], g);
          if (v) rv2_sinc(v[i + 1], dx0[i], g/dt);
        }
        else {
          rv2_sinc(x1[i + 1], dx0[i], g);
          if (v) rv2_sinc(v[i + 1], dx0[i], g/dt);
        }
      }
    }
#ifdef _OPENMP
    } /* end of parallel code */
#endif

    /* local constraints */
    if (lgcon) {
      for (k = 0; k < lgcnt; k++) {
        if (!lgc[k].on) continue;
        i = lgc[k].i;
        j = lgc[k].j;
        r2 = rv2_sqr(rv2_diff(dxi, x1[j], x1[i]));
        tmp = (r2ref = lgc[k].r2ref) * r2max;
        if (r2 > tmp) r2 = tmp;
        if (fabs(r2 - r2ref) > tol * r2ref) {
          if (!again) again = 1;
          g = rv2_dot(dxi, lgc[k].dx0);
          tmp = glow * r2ref;
          if (fabs(g) < tmp) g = g > 0 ? tmp : -tmp;
          g = (r2ref - r2) / (4 * g);
          lgdx0 = lgc[k].dx0;
          rv2_sinc(x1[i], lgdx0, -g);
          rv2_sinc(x1[j], lgdx0, +g);
          if (v) {
            rv2_sinc(v[i], lgdx0, -g/dt);
            rv2_sinc(v[j], lgdx0, +g/dt);
          }
        }
      }
    }

    if (!again) break;
  }

  if (it >= itmax) {
    if (verbose) {
      const char *fnf = "shakefail.pos";
      fprintf(stderr, "shake: failed after %d iter. r = 1%+g, see %s\n", it, sqrt(r2bad)-1, fnf);
      ab_writepos(ab, (real *) x1, NULL, fnf);
    }
    return -1;
  }

  return 0;
}

/* 3D shake with additional constraints */
INLINE int ab_shake3d(abpro_t *ab, rv3_t *x0, rv3_t *x1, rv3_t *v, real dt,
    int itmax, double tol, int verbose)
{
  int i, j, k, again, it, n = ab->n, lgcon = ab->lgcon, lgcnt = ab->lgcnt;
  real dxi[3], g, r2, r2bad, r2ref, tmp, *lgdx0;
  rv3_t *dx0 = (rv3_t *) ab->dx;
  static const real glow = .5, r2max = 4.0;
  lgconstr_t *lgc = ab->lgc;

#ifdef _OPENMP
#pragma omp threadprivate(r2max, glow)
#endif
  /* pre-compute reference difference */
  for (i = 0; i < n-1; i++)
    rv3_diff(dx0[i], x0[i+1], x0[i]);

  /* compute distance in x0 for local constraints */
  for (k = 0; lgcon && k < lgcnt; k++) {
    if (!lgc[k].on) continue;
    i = lgc[k].i;
    j = lgc[k].j;
    rv3_diff(lgc[k].dx0, x0[j], x0[i]);
  }

  for (it = 0; it < itmax; it++) {
    int imin, imax;

    again = 0;
#ifdef _OPENMP
#pragma omp parallel firstprivate(n) private(i, r2, dxi, g)
    {
    int ip = omp_get_thread_num();
    int np = omp_get_num_threads();
    int n1 = n - 1;
    int sz = (n1 + np - 1)/np;
    imin = ip * sz;
    imax = (ip + 1) * sz;
    if (imax > n1) imax = n1;
#else
    imin = 0;
    imax = n - 1;
#endif

    for (i = imin; i < imax; i++) { /* standard constraints */
      r2 = rv3_sqr(rv3_diff(dxi, x1[i + 1], x1[i]));
      if (r2 > r2max) { /* too large, impossible to correct */
        if (verbose)
          fprintf(stderr, "shake: r(%d, %d) = %g\n", i, i+1, sqrt(r2));
        r2 = r2max;
      }

      if (fabs(r2 - 1) > tol) {
        if (!again) { again = 1; r2bad = r2; }

        g = rv3_dot(dxi, dx0[i]);
        if (fabs(g) < glow) { /* inner product too small */
          if (verbose)
            fprintf(stderr, "shake: bad alignment %d-%d, %g, dot = %g\n", i, i+1, sqrt(r2), g);
          g = (g > 0) ? glow : -glow;
        }
        g = (1 - r2) / (4 * g);
        rv3_sinc(x1[i],   dx0[i], -g);
        if (v) rv3_sinc(v[i], dx0[i], -g/dt);
        /* be careful as i + 1 == imax belongs to the next block */
        if (i == imax - 1)
#ifdef _OPENMP
#pragma omp critical
#endif
        {
          rv3_sinc(x1[i + 1], dx0[i], g);
          if (v) rv3_sinc(v[i + 1], dx0[i], g/dt);
        }
        else {
          rv3_sinc(x1[i + 1], dx0[i], g);
          if (v) rv3_sinc(v[i + 1], dx0[i], g/dt);
        }
      }
    }
#ifdef _OPENMP
    } /* end of parallel code */
#endif

    /* local constraints */
    if (lgcon) {
      for (k = 0; k < lgcnt; k++) {
        if (!lgc[k].on) continue;
        i = lgc[k].i;
        j = lgc[k].j;
        r2 = rv3_sqr(rv3_diff(dxi, x1[j], x1[i]));
        tmp = (r2ref = lgc[k].r2ref) * r2max;
        if (r2 > tmp) r2 = tmp;
        if (fabs(r2 - r2ref) > tol * r2ref) {
          if (!again) again = 1;
          g = rv3_dot(dxi, lgc[k].dx0);
          tmp = glow * r2ref;
          if (fabs(g) < tmp) g = g > 0 ? tmp : -tmp;
          g = (r2ref - r2) / (4 * g);
          lgdx0 = lgc[k].dx0;
          rv3_sinc(x1[i], lgdx0, -g);
          rv3_sinc(x1[j], lgdx0, +g);
          if (v) {
            rv3_sinc(v[i], lgdx0, -g/dt);
            rv3_sinc(v[j], lgdx0, +g/dt);
          }
        }
      }
    }

    if (!again) break;
  }

  if (it >= itmax) {
    if (verbose) {
      const char *fnf = "shakefail.pos";
      fprintf(stderr, "shake: failed after %d iter. r = 1%+g, see %s\n", it, sqrt(r2bad)-1, fnf);
      ab_writepos(ab, (real *) x1, NULL, fnf);
    }
    return -1;
  }

  return 0;
}


/* shake x1 according to x0 */
INLINE int ab_shake(abpro_t *ab, real * RESTRICT x0, real * RESTRICT x1,
    real * RESTRICT v, real dt, int itmax, double tol, int verbose)
{
  if (itmax <= 0) itmax = 3000;
  if (tol <= 0.) tol = (sizeof(real) == sizeof(double)) ? 1e-6 : 1e-4;
  return (ab->d == 3) ?
    ab_shake3d(ab, (rv3_t *) x0, (rv3_t *) x1, (rv3_t *) v, dt, itmax, tol, verbose) :
    ab_shake2d(ab, (rv2_t *) x0, (rv2_t *) x1, (rv2_t *) v, dt, itmax, tol, verbose);
}


INLINE int ab_rattle2d(abpro_t *ab, rv2_t *x0, rv2_t *v,
    int itmax, double tol, int verbose)
{
  int i, j, k, again, it, n = ab->n, lgcon = ab->lgcon, lgcnt = ab->lgcnt;
  real dv[2], g, rvbad, *lgdx0;
  rv2_t *dx = (rv2_t *) ab->dx;
  lgconstr_t *lgc = ab->lgc;

  for (i = 0; i < n-1; i++)
    rv2_diff(dx[i], x0[i+1], x0[i]);

  for (k = 0; lgcon && k < lgcnt; k++) { /* local constraints */
    if (!lgc[k].on) continue;
    i = lgc[k].i;
    j = lgc[k].j;
    rv2_diff(lgc[k].dx0, x0[j], x0[i]);
  }

  for (it = 0; it < itmax; it++) {
    for (again = 0, i = 0; i < n-1; i++) {
      rv2_diff(dv, v[i+1], v[i]);
      g = .5f * rv2_dot(dx[i], dv);
      if (fabs(g) > tol) {
        if (!again) { again = 1; rvbad = g; }
        rv2_sinc(v[i],   dx[i],  g);
        rv2_sinc(v[i+1], dx[i], -g);
      }
    }

    for (k = 0; lgcon && k < lgcnt; k++) { /* local constraints */
      if (!lgc[k].on) continue;
      i = lgc[k].i;
      j = lgc[k].j;
      rv2_diff(dv, v[j], v[i]);
      lgdx0 = lgc[k].dx0;
      g = .5f * rv2_dot(lgdx0, dv);
      if (fabs(g) > tol) {
        if (!again) again = 1;
        rv2_sinc(v[i], lgdx0, +g);
        rv2_sinc(v[j], lgdx0, -g);
      }
    }

    if (!again) break;
  }
  if (it >= itmax) {
    if (verbose) {
      const char *fnf = "rattlefail.pos";
      fprintf(stderr, "rattle: failed after %d iter. rv = %+g, see %s\n", it, rvbad, fnf);
      ab_writepos(ab, (real *) x0, (real *) v, fnf);
    }
    return -1;
  }
  return 0;
}

INLINE int ab_rattle3d(abpro_t *ab, rv3_t *x0, rv3_t *v,
    int itmax, double tol, int verbose)
{
  int i, j, k, again, it, n = ab->n, lgcon = ab->lgcon, lgcnt = ab->lgcnt;
  real dv[3], g, rvbad, *lgdx0;
  rv3_t *dx = (rv3_t *) ab->dx;
  lgconstr_t *lgc = ab->lgc;

  for (i = 0; i < n-1; i++)
    rv3_diff(dx[i], x0[i+1], x0[i]);

  for (k = 0; lgcon && k < lgcnt; k++) { /* local constraints */
    if (!lgc[k].on) continue;
    i = lgc[k].i;
    j = lgc[k].j;
    rv3_diff(lgc[k].dx0, x0[j], x0[i]);
  }

  for (it = 0; it < itmax; it++) {
    for (again = 0, i = 0; i < n-1; i++) {
      rv3_diff(dv, v[i+1], v[i]);
      g = .5f * rv3_dot(dx[i], dv);
      if (fabs(g) > tol) {
        if (!again) { again = 1; rvbad = g; }
        rv3_sinc(v[i],   dx[i],  g);
        rv3_sinc(v[i+1], dx[i], -g);
      }
    }

    for (k = 0; lgcon && k < lgcnt; k++) { /* local constraints */
      if (!lgc[k].on) continue;
      i = lgc[k].i;
      j = lgc[k].j;
      rv3_diff(dv, v[j], v[i]);
      lgdx0 = lgc[k].dx0;
      g = .5f * rv3_dot(lgdx0, dv);
      if (fabs(g) > tol) {
        if (!again) again = 1;
        rv3_sinc(v[i], lgdx0, +g);
        rv3_sinc(v[j], lgdx0, -g);
      }
    }

    if (!again) break;
  }
  if (it >= itmax) {
    if (verbose) {
      const char *fnf = "rattlefail.pos";
      fprintf(stderr, "rattle: failed after %d iter. rv = %+g, see %s\n", it, rvbad, fnf);
      ab_writepos(ab, (real *) x0, (real *) v, fnf);
    }
    return -1;
  }
  return 0;
}


/* shake v according to x0 */
INLINE int ab_rattle(abpro_t *ab, const real *x0, real *v, int itmax, double tol, int verbose)
{
  if (itmax <= 0) itmax = 3000;
  if (tol <= 0.) tol = 1e-4;
  return (ab->d == 3) ?
    ab_rattle3d(ab, (rv3_t *) x0, (rv3_t *) v, itmax, tol, verbose) :
    ab_rattle2d(ab, (rv2_t *) x0, (rv2_t *) v, itmax, tol, verbose);
}


INLINE int ab_milcshake2d(abpro_t *ab, rv2_t *x0, rv2_t *x1, rv2_t *v, real dt,
    int itmax, double tol, int verbose)
{
  int i, again, it, n = ab->n, nl;
  rv2_t *dx0 = (rv2_t *) ab->xx[0], *dx1 = (rv2_t *) ab->xx[1], *x = (rv2_t *) ab->xx[2];
  real *dl = ab->xx[2], *dm = dl + n, *du = dm + n, *lam = du + n, *rhs = lam + n;
  real y;

  nl = n - 1;
  for (i = 0; i < nl; i++) {
    rv2_diff(dx1[i], x1[i], x1[i+1]);
    rv2_diff(dx0[i], x0[i], x0[i+1]);
    rhs[i] = 1 - rv2_sqr(dx1[i]);
  }

  /* dm[0..nl-1], du[0..nl-2], dl[1..nl-1] */
  dm[0] =  4*rv2_dot(dx0[0], dx1[0]);
  du[0] = -2*rv2_dot(dx0[1], dx1[0]);
  for (i = 1; i < nl; i++) {
    dl[i] = -2*rv2_dot(dx1[i], dx0[i-1]);
    dm[i] =  4*rv2_dot(dx1[i], dx0[i]);
    du[i] = -2*rv2_dot(dx1[i], dx0[i+1]); /* no dx0[nl], but doesn't matter */
  }

  /* solve matrix equation D lam = rhs
   * first LU decompose D;
   * U --> du with diagonal being unity;
   * L --> dm and dl with dl unchanged */
  if (fabs(dm[0]) < 1e-6) return 1;
  for (i = 1; i < nl; i++) {
    dm[i] -= dl[i] * (du[i-1] /= dm[i-1]);
    if (fabs(dm[i]) < 1e-6) return i+1;
  }

  for (it = 1; it <= itmax; it++) {
    lam[0] = rhs[0]/dm[0];
    for (i = 1; i < nl; i++) /* solving L v = rhs */
      lam[i] = (rhs[i] - dl[i]*lam[i-1])/dm[i];
    for (i = nl - 1; i > 0; i--) /* solving U lam = v */
      lam[i-1] -= du[i-1]*lam[i];

    rv2_ncopy(x, x1, n);
    /* update the new position */
    for (i = 0; i < nl; i++) {
      rv2_sinc(x[i],   dx0[i],  lam[i]);
      rv2_sinc(x[i+1], dx0[i], -lam[i]);
    }

    /* calculate the maximal error */
    for (again = 0, i = 0; i < nl; i++) {
      y = 1 - rv2_dist2(x[i], x[i+1]);
      if (fabs(y) > tol) again = 1;
      rhs[i] += y;
    }
    if (!again) break;
  }

  rv2_ncopy(x1, x, n);
  if (v != NULL) { /* correct velocities */
    for (i = 0; i < n-1; i++) {
      rv2_sinc(v[i],   dx0[i],  lam[i]/dt);
      rv2_sinc(v[i+1], dx0[i], -lam[i]/dt);
    }
  }

  if (it >= itmax) {
    if (verbose) {
      const char *fnf = "shakefail.pos";
      fprintf(stderr, "milcshake: failed after %d iter. see %s\n", it, fnf);
      ab_writepos(ab, (real *) x1, NULL, fnf);
    }
    return -1;
  }
  return 0;
}

INLINE int ab_milcshake3d(abpro_t *ab, rv3_t *x0, rv3_t *x1, rv3_t *v, real dt,
    int itmax, double tol, int verbose)
{
  int i, again, it, n = ab->n, nl;
  rv3_t *dx0 = (rv3_t *) ab->xx[0], *dx1 = (rv3_t *) ab->xx[1], *x = (rv3_t *) ab->xx[2];
  real *dl = ab->xx[3], *dm = dl + n, *du = dm + n, *lam = du + n, *rhs = lam + n;
  real y;

  nl = n - 1;
  for (i = 0; i < nl; i++) {
    rv3_diff(dx1[i], x1[i], x1[i+1]);
    rv3_diff(dx0[i], x0[i], x0[i+1]);
    rhs[i] = 1 - rv3_sqr(dx1[i]);
  }

  /* dm[0..nl-1], du[0..nl-2], dl[1..nl-1] */
  dm[0] =  4*rv3_dot(dx0[0], dx1[0]);
  du[0] = -2*rv3_dot(dx0[1], dx1[0]);
  for (i = 1; i < nl; i++) {
    dl[i] = -2*rv3_dot(dx1[i], dx0[i-1]);
    dm[i] =  4*rv3_dot(dx1[i], dx0[i]);
    du[i] = -2*rv3_dot(dx1[i], dx0[i+1]); /* no dx0[nl], but doesn't matter */
  }

  /* solve matrix equation D lam = rhs
   * first LU decompose D;
   * U --> du with diagonal being unity;
   * L --> dm and dl with dl unchanged */
  if (fabs(dm[0]) < 1e-6) return 1;
  for (i = 1; i < nl; i++) {
    dm[i] -= dl[i] * (du[i-1] /= dm[i-1]);
    if (fabs(dm[i]) < 1e-6) return i+1;
  }

  for (it = 1; it <= itmax; it++) {
    lam[0] = rhs[0]/dm[0];
    for (i = 1; i < nl; i++) /* solving L v = rhs */
      lam[i] = (rhs[i] - dl[i]*lam[i-1])/dm[i];
    for (i = nl - 1; i > 0; i--) /* solving U lam = v */
      lam[i-1] -= du[i-1]*lam[i];

    rv3_ncopy(x, x1, n);
    /* update the new position */
    for (i = 0; i < nl; i++) {
      rv3_sinc(x[i],   dx0[i],  lam[i]);
      rv3_sinc(x[i+1], dx0[i], -lam[i]);
    }

    /* calculate the maximal error */
    for (again = 0, i = 0; i < nl; i++) {
      y = 1 - rv3_dist2(x[i], x[i+1]);
      if (fabs(y) > tol) again = 1;
      rhs[i] += y;
    }
    if (!again) break;
  }

  rv3_ncopy(x1, x, n);
  if (v != NULL) { /* correct velocities */
    for (i = 0; i < n-1; i++) {
      rv3_sinc(v[i],   dx0[i],  lam[i]/dt);
      rv3_sinc(v[i+1], dx0[i], -lam[i]/dt);
    }
  }

  if (it >= itmax) {
    if (verbose) {
      const char *fnf = "shakefail.pos";
      fprintf(stderr, "milcshake: failed after %d iter. see %s\n", it, fnf);
      ab_writepos(ab, (real *) x1, NULL, fnf);
    }
    return -1;
  }
  return 0;
}


/* MILC shake, make |dr| = 1
 * for a random config., about 30~40% faster than shake
 * but slower than shake for near-minimum config.  */
INLINE int ab_milcshake(abpro_t *ab, real *x0, real *x1, real *v, real dt,
    int itmax, double tol, int verbose)
{
  if (itmax <= 0) itmax = 3000;
  if (tol <= 0.) tol = (sizeof(real) == sizeof(double)) ? 1e-6 : 1e-4;
  return (ab->d == 3) ?
    ab_milcshake3d(ab, (rv3_t *) x0, (rv3_t *) x1, (rv3_t *) v, dt, itmax, tol, verbose) :
    ab_milcshake2d(ab, (rv2_t *) x0, (rv2_t *) x1, (rv2_t *) v, dt, itmax, tol, verbose);
}


INLINE int ab_milcrattle2d(abpro_t *ab, rv2_t *x, rv2_t *v)
{
  int i, n = ab->n, nl;
  rv2_t *dx = (rv2_t *) ab->xx[0], *dv = (rv2_t *) ab->xx[1];
  real *dl = ab->xx[2], *dm = dl + n, *du = dm + n, *lam = du + n, *rhs = lam + n;

  nl = n - 1;
  for (i = 0; i < nl; i++) {
    rv2_diff(dx[i], x[i], x[i+1]);
    rv2_diff(dv[i], v[i], v[i+1]);
  }

  /* dm[0..nl-1], du[0..nl-2], dl[1..nl-1] */
  dm[0] = 2*rv2_dot(dx[0], dx[0]);
  du[0] =  -rv2_dot(dx[1], dx[0]);
  for (i = 1; i < nl; i++) {
    dl[i] =  -rv2_dot(dx[i], dx[i-1]);
    dm[i] = 2*rv2_dot(dx[i], dx[i]);
    du[i] =  -rv2_dot(dx[i], dx[i+1]); /* no dx[nl], but doesn't matter */
  }
  for (i = 0; i < nl; i++)
    rhs[i] = -rv2_dot(dv[i], dx[i]);

  /* solve matrix equation D lam = rhs
   * first LU decompose D;
   * U --> du with diagonal being unity;
   * L --> dm and dl with dl unchanged */
  if (fabs(dm[0]) < 1e-6) return 1;
  for (i = 1; i < nl; i++) {
    dm[i] -= dl[i] * (du[i-1] /= dm[i-1]);
    if (fabs(dm[i]) < 1e-6) return i+1;
  }

  lam[0] = rhs[0]/dm[0];
  for (i = 1; i < nl; i++) /* solving L v = rhs */
    lam[i] = (rhs[i] - dl[i]*lam[i-1])/dm[i];
  for (i = nl - 1; i > 0; i--) /* solving U lam = v */
    lam[i-1] -= du[i-1]*lam[i];

  /* update the new position */
  for (i = 0; i < nl; i++) {
    rv2_sinc(v[i],   dx[i],  lam[i]);
    rv2_sinc(v[i+1], dx[i], -lam[i]);
  }
  return 0;
}

INLINE int ab_milcrattle3d(abpro_t *ab, rv3_t *x, rv3_t *v)
{
  int i, n = ab->n, nl;
  rv3_t *dx = (rv3_t *) ab->xx[0], *dv = (rv3_t *) ab->xx[1];
  real *dl = ab->xx[2], *dm = dl + n, *du = dm + n, *lam = du + n, *rhs = lam + n;

  nl = n - 1;
  for (i = 0; i < nl; i++) {
    rv3_diff(dx[i], x[i], x[i+1]);
    rv3_diff(dv[i], v[i], v[i+1]);
  }

  /* dm[0..nl-1], du[0..nl-2], dl[1..nl-1] */
  dm[0] = 2*rv3_dot(dx[0], dx[0]);
  du[0] =  -rv3_dot(dx[1], dx[0]);
  for (i = 1; i < nl; i++) {
    dl[i] =  -rv3_dot(dx[i], dx[i-1]);
    dm[i] = 2*rv3_dot(dx[i], dx[i]);
    du[i] =  -rv3_dot(dx[i], dx[i+1]); /* no dx[nl], but doesn't matter */
  }
  for (i = 0; i < nl; i++)
    rhs[i] = -rv3_dot(dv[i], dx[i]);

  /* solve matrix equation D lam = rhs
   * first LU decompose D;
   * U --> du with diagonal being unity;
   * L --> dm and dl with dl unchanged */
  if (fabs(dm[0]) < 1e-6) return 1;
  for (i = 1; i < nl; i++) {
    dm[i] -= dl[i] * (du[i-1] /= dm[i-1]);
    if (fabs(dm[i]) < 1e-6) return i+1;
  }

  lam[0] = rhs[0]/dm[0];
  for (i = 1; i < nl; i++) /* solving L v = rhs */
    lam[i] = (rhs[i] - dl[i]*lam[i-1])/dm[i];
  for (i = nl - 1; i > 0; i--) /* solving U lam = v */
    lam[i-1] -= du[i-1]*lam[i];

  /* update the new position */
  for (i = 0; i < nl; i++) {
    rv3_sinc(v[i],   dx[i],  lam[i]);
    rv3_sinc(v[i+1], dx[i], -lam[i]);
  }
  return 0;
}


/* MILC rattle, make dr.v = 0 */
INLINE int ab_milcrattle(abpro_t *ab, real *x, real *v)
{
  return (ab->d == 3) ?
    ab_milcrattle3d(ab, (rv3_t *) x, (rv3_t *) v) :
    ab_milcrattle2d(ab, (rv2_t *) x, (rv2_t *) v);
}


INLINE real ab_energy2dm1(abpro_t *ab, rv2_t *r, int soft)
{
  int i, j, n = ab->n;
  real ua = 0, ulj = 0;
  rv2_t *dx = (rv2_t *) ab->dx;

  for (i = 0; i < n - 1; i++)
    rv2_diff(dx[i], r[i+1], r[i]);

  for (i = 0; i < n - 2; i++)
    ua += 1.f - rv2_dot(dx[i+1], dx[i]);

#ifdef _OPENMP
#pragma omp parallel for reduction(+:ulj) private(i, j)
#endif
  for (i = 0; i < n - 2; i++) {
    real dr, dr2, dr6;
    for (j = i+2; j < n; j++) {
      dr2 = rv2_dist2(r[j], r[i]);
      if (soft && dr2 < 1.f) {
        dr = (real) sqrt(dr2);
        ulj += (52 - 48*dr) - ab->clj[ab->type[i]][ab->type[j]]*(28 - 24*dr);
      } else {
        dr2 = 1/dr2;
        dr6 = dr2*dr2*dr2;
        ulj += 4*dr6*(dr6 - ab->clj[ab->type[i]][ab->type[j]]);
      }
    }
  }
  return ua * .25f  + ulj;
}

INLINE real ab_energy3dm1(abpro_t *ab, rv3_t *r, int soft)
{
  int i, j, n = ab->n;
  real ua = 0, ulj = 0;
  rv3_t *dx = (rv3_t *) ab->dx;

  for (i = 0; i < n - 1; i++)
    rv3_diff(dx[i], r[i+1], r[i]);

  for (i = 0; i < n - 2; i++)
    ua += 1.f - rv3_dot(dx[i+1], dx[i]);

#ifdef _OPENMP
#pragma omp parallel for reduction(+:ulj) private(i, j)
#endif
  for (i = 0; i < n - 2; i++) {
    real dr, dr2, dr6;
    for (j = i+2; j < n; j++) {
      dr2 = rv3_dist2(r[j], r[i]);
      if (soft && dr2 < 1.f) {
        dr = (real) sqrt(dr2);
        ulj += (52 - 48*dr) - ab->clj[ab->type[i]][ab->type[j]]*(28 - 24*dr);
      } else {
        dr2 = 1/dr2;
        dr6 = dr2*dr2*dr2;
        ulj += 4*dr6*(dr6 - ab->clj[ab->type[i]][ab->type[j]]);
      }
    }
  }
  return ua * .25f  + ulj;
}


INLINE real ab_energy3dm2(abpro_t *ab, rv3_t *r, int soft)
{
  int i, j, n = ab->n;
  real ua = 0, ud = 0, ulj = 0;
  rv3_t *dx = (rv3_t *) ab->dx;

  for (i = 0; i < n - 1; i++)
    rv3_diff(dx[i], r[i+1], r[i]);

  for (i = 1; i < n-1; i++)
    ua += rv3_dot(dx[i], dx[i-1]);

  for (i = 1; i < n-2; i++)
    ud -= .5f * rv3_dot(dx[i+1], dx[i-1]);

#ifdef _OPENMP
#pragma omp parallel for reduction(+:ulj) private(i, j)
#endif
  for (i = 0; i < n-2; i++) {
    real dr2, dr6;
    for (j = i+2; j < n; j++) {
      dr2 = rv3_dist2(r[j], r[i]);
      if (soft && dr2 < 1.f) {
        ulj += ab->clj[ab->type[i]][ab->type[j]]*(ab->sla - ab->slb*(real) sqrt(dr2));
      } else {
        dr2 = 1.f/dr2;
        dr6 = dr2*dr2*dr2;
        ulj += 4.f*ab->clj[ab->type[i]][ab->type[j]]*dr6*(dr6 - 1.f);
      }
    }
  }
  return ua + ud + ulj;
}


INLINE real ab_energy(abpro_t *ab, real *r, int soft)
{
  if (ab->model == 2)
    return ab_energy3dm2(ab, (rv3_t *) r, soft);
  else if (ab->d == 3)
    return ab_energy3dm1(ab, (rv3_t *) r, soft);
  else
    return ab_energy2dm1(ab, (rv2_t *) r, soft);
}


INLINE real ab_force2dm1(abpro_t *ab, rv2_t *r, rv2_t *f_g, int soft)
{
  int i, j, n = ab->n;
  rv2_t *dx = (rv2_t *) ab->dx;
  real U = 0.0f, ua = 0.0f, *dxm, *dxp;
  real dr2, dr6, ff, c;
  rv2_t *f, dxi;
  real ulj = 0.f;

  for (i = 0; i < n - 1; i++)
    rv2_diff(dx[i], r[i+1], r[i]);

  for (i = 0; i < n; i++) rv2_zero(f_g[i]);
  for (i = 1; i < n - 1; i++) {
    dxp = dx[i];
    dxm = dx[i-1];
    ua += 1.f - rv2_dot(dxp, dxm);
    rv2_sinc(f_g[i-1], dxp, -.25f);
    rv2_sinc(f_g[i],   dxp,  .25f);
    rv2_sinc(f_g[i],   dxm, -.25f);
    rv2_sinc(f_g[i+1], dxm,  .25f);
  }

#ifdef _OPENMP
#pragma omp parallel firstprivate(n) private(i, j)
{ /* parallel code starts here */
  int ip = omp_get_thread_num();
  int np = omp_get_num_threads();
  int imin = ab->homeid[ip], imax = ab->homeid[ip + 1];
  int ipr, ipr0 = ab->pairid[ip], ipr1 = ab->pairid[ip + 1];
  rv2_t *f_l = (rv2_t *) ab->f_l;
  f = f_l + n * ip; /* point to the proper local force */
  /* clear the local force */
  for (i = 0; i < n; i++) rv2_zero(f[i]);
#else
  f = f_g;
#endif

#ifdef _OPENMP
  for (ipr = ipr0; ipr < ipr1; ipr++) {
    i = ab->pair[ipr].i;
    j = ab->pair[ipr].j;
    c = ab->pair[ipr].c;
#else
  for (i = 0; i < n - 2; i++)
  for (j = i + 2; j < n; j++) {
    c = ab->clj[ ab->type[i] ][ ab->type[j] ];
#endif

    dr2 = rv2_sqr( rv2_diff(dxi, r[i], r[j]) );

    if (soft && dr2 < 1.) {
      dr2 = (real) sqrt(dr2);
      ulj += (52.f - 28.f*c) - 24.f*dr2*(2.f-c);
      ff = 24.f*(2.f - c)/dr2;
    } else {
      dr2 = 1.f/dr2;
      dr6 = dr2*dr2*dr2;
      ulj += 4.f*dr6*(dr6 - c);
      ff = 24.f*dr2*dr6*(dr6*2.f - c);
    }
    rv2_sinc(f[i], dxi, +ff);
    rv2_sinc(f[j], dxi, -ff);
  }

#ifdef _OPENMP
#pragma omp barrier
  for (i = imin; i < imax; i++) /* collect global force, f_l flushed by barrier */
    for (j = 0; j < np; j++) {
      rv2_inc(f_g[i], f_l[n*j + i]);
    }

#pragma omp atomic
  U += ulj;
} /* parallel code stops */
#else
  U += ulj;
#endif

  return ua * 0.25f + U;
}

INLINE real ab_force3dm1(abpro_t *ab, rv3_t *r, rv3_t *f_g, int soft)
{
  int i, j, n = ab->n;
  rv3_t *dx = (rv3_t *) ab->dx;
  real U = 0.0f, ua = 0.0f, *dxm, *dxp;
  real dr2, dr6, ff, c;
  rv3_t *f, dxi;
  real ulj = 0.f;

  for (i = 0; i < n - 1; i++)
    rv3_diff(dx[i], r[i+1], r[i]);

  for (i = 0; i < n; i++) rv3_zero(f_g[i]);
  for (i = 1; i < n - 1; i++) {
    dxp = dx[i];
    dxm = dx[i-1];
    ua += 1.f - rv3_dot(dxp, dxm);
    rv3_sinc(f_g[i-1], dxp, -.25f);
    rv3_sinc(f_g[i],   dxp,  .25f);
    rv3_sinc(f_g[i],   dxm, -.25f);
    rv3_sinc(f_g[i+1], dxm,  .25f);
  }

#ifdef _OPENMP
#pragma omp parallel firstprivate(n) private(i, j)
{ /* parallel code starts here */
  int ip = omp_get_thread_num();
  int np = omp_get_num_threads();
  int imin = ab->homeid[ip], imax = ab->homeid[ip + 1];
  int ipr, ipr0 = ab->pairid[ip], ipr1 = ab->pairid[ip + 1];
  rv3_t *f_l = (rv3_t *) ab->f_l;
  f = f_l + n * ip; /* point to the proper local force */
  /* clear the local force */
  for (i = 0; i < n; i++) rv3_zero(f[i]);
#else
  f = f_g;
#endif

#ifdef _OPENMP
  for (ipr = ipr0; ipr < ipr1; ipr++) {
    i = ab->pair[ipr].i;
    j = ab->pair[ipr].j;
    c = ab->pair[ipr].c;
#else
  for (i = 0; i < n - 2; i++)
  for (j = i + 2; j < n; j++) {
    c = ab->clj[ ab->type[i] ][ ab->type[j] ];
#endif

    dr2 = rv3_sqr( rv3_diff(dxi, r[i], r[j]) );

    if (soft && dr2 < 1.) {
      dr2 = (real) sqrt(dr2);
      ulj += (52.f - 28.f*c) - 24.f*dr2*(2.f-c);
      ff = 24.f*(2.f - c)/dr2;
    } else {
      dr2 = 1.f/dr2;
      dr6 = dr2*dr2*dr2;
      ulj += 4.f*dr6*(dr6 - c);
      ff = 24.f*dr2*dr6*(dr6*2.f - c);
    }
    rv3_sinc(f[i], dxi, +ff);
    rv3_sinc(f[j], dxi, -ff);
  }

#ifdef _OPENMP
#pragma omp barrier
  for (i = imin; i < imax; i++) /* collect global force, f_l flushed by barrier */
    for (j = 0; j < np; j++) {
      rv3_inc(f_g[i], f_l[n*j + i]);
    }

#pragma omp atomic
  U += ulj;
} /* parallel code stops */
#else
  U += ulj;
#endif

  return ua * 0.25f + U;
}


INLINE real ab_force3dm2(abpro_t *ab, rv3_t *r, rv3_t *f_g, int soft)
{
  int i, j, n = ab->n;
  rv3_t *dx = (rv3_t *) ab->dx;
  real U = 0.f, ua = 0.f, ud = 0.f, *dxm, *dxp;
  real dr2, dr6, ff, c;
  rv3_t *f, dxi;
  real ulj = 0.f;

  for (i = 0; i < n - 1; i++)
    rv3_diff(dx[i], r[i+1], r[i]);

  for (i = 0; i < n; i++) rv3_zero(f_g[i]);

  for (i = 1; i < n-1; i++) {
    dxp = dx[i];
    dxm = dx[i-1];
    rv3_inc(f_g[i-1], dxp);
    rv3_dec(f_g[i],   dxp);
    rv3_inc(f_g[i],   dxm);
    rv3_dec(f_g[i+1], dxm);
    ua += rv3_dot(dxp, dxm);
  }

  for (i = 1; i < n-2; i++) {
    dxp = dx[i+1];
    dxm = dx[i-1];
    rv3_sinc(f_g[i-1], dxp, -.5f);
    rv3_sinc(f_g[i],   dxp,  .5f);
    rv3_sinc(f_g[i+1], dxm, -.5f);
    rv3_sinc(f_g[i+2], dxm,  .5f);
    ud -= .5f*rv3_dot(dxp, dxm);
  }

#ifdef _OPENMP
#pragma omp parallel firstprivate(n) private(i, j)
{ /* parallel code starts here */
  int ip = omp_get_thread_num();
  int np = omp_get_num_threads();
  int imin = ab->homeid[ip], imax = ab->homeid[ip + 1];
  int ipr, ipr0 = ab->pairid[ip], ipr1 = ab->pairid[ip + 1];
  rv3_t *f_l = (rv3_t *) ab->f_l;
  f = f_l + n * ip; /* point to the proper local force */
  /* clear the local force */
  for (i = 0; i < n; i++) rv3_zero(f[i]);
#else
  f = f_g;
#endif

#ifdef _OPENMP
  for (ipr = ipr0; ipr < ipr1; ipr++) {
    i = ab->pair[ipr].i;
    j = ab->pair[ipr].j;
    c = ab->pair[ipr].c;
#else
  for (i = 0; i < n - 2; i++)
  for (j = i + 2; j < n; j++) {
    c = ab->clj[ ab->type[i] ][ ab->type[j] ];
#endif

    dr2 = rv3_sqr( rv3_diff(dxi, r[i], r[j]) );

    if (soft && dr2 < 1.f) {
      dr2 = (real) sqrt(dr2);
      ulj += c*(ab->sla - ab->slb*dr2);
      ff = (ab->slb*c)/dr2;
    } else {
      dr2 = 1.f/dr2;
      dr6 = dr2*dr2*dr2;
      ulj += 4.f*c*dr6*(dr6 - 1.f);
      ff = 48.f*c*dr2*dr6*(dr6 - .5f);
    }
    rv3_sinc(f[i], dxi, +ff);
    rv3_sinc(f[j], dxi, -ff);
  }
#ifdef _OPENMP
#pragma omp barrier
  for (i = imin; i < imax; i++) /* collect global force, barrier flushes f_l */
    for (j = 0; j < np; j++)
      rv3_inc(f_g[i], f_l[n*j + i]);
#pragma omp atomic
  U += ulj;
} /* parallel code ends here */
#else
  U += ulj;
#endif

  return ua + ud + U;
}


/* compute force f */
INLINE real ab_force(abpro_t *ab, real *r, real *f, int soft)
{
  if (ab->d == 2)
    return ab_force2dm1(ab, (rv2_t *) r, (rv2_t *) f, soft);
  else if (ab->model == 1)
    return ab_force3dm1(ab, (rv3_t *) r, (rv3_t *) f, soft);
  else
    return ab_force3dm2(ab, (rv3_t *) r, (rv3_t *) f, soft);
}


/* minimizes the energy of a given configuration.
   The minimized configuration is saved in ab->lmx
   When a lowest energy configuration is found, the result is
   saved to global variable ab->xmin, with ab->emin updated. */
INLINE real ab_localmin(abpro_t *ab, const real *r, int itmax,
    double tol, int sh_itmax, double sh_tol, unsigned flags)
{
  int t, i, j, id, n = ab->n, d = ab->d;
  real up, u = 0, step = 0.02, del, mem = 1;
  real **x = ab->xx, **f = ab->xx + 2, *v = ab->xx[4];
  const real DELMAX = 0.20f;

  if (itmax <= 0) itmax = 10000;
  if (tol <= 0.) tol = 1e-12;
  /* to make a working copy */
  memcpy(x[id = 0], r, n*d*sizeof(real));
  up = ab_force(ab, x[id], f[id], 0);
  memset(v, 0, n*d*sizeof(real));

  for (t = 1; t <= itmax; t++) {
    for (i = 0; i < n; i++)
      for (j = 0; j < d; j++) {
        del = v[i*d+j] = v[i*d+j] * mem + f[id][i*d+j] * step;
        if (del > DELMAX) del = DELMAX; else if (del < -DELMAX) del = -DELMAX;
        x[!id][i*d+j] = x[id][i*d+j]+del;
      }

    if (flags & AB_MILCSHAKE) {
      if (ab_milcshake(ab, x[id], x[!id], NULL, 0., sh_itmax, sh_tol, 0) != 0) goto SHRINK;
    } else {
      if (ab_shake(ab, x[id], x[!id], NULL, 0., sh_itmax, sh_tol, 0) != 0) goto SHRINK;
    }
    u = ab_force(ab, x[!id], f[!id], 0);
    if (u > up) { mem = 0; goto SHRINK; }

    id = !id;
    if (up - u < tol) break;
    up = u;
    mem = 0.9;
    step *= 1.1;
    continue;

SHRINK:
    step *= 0.5;
  }
  if (t > itmax && (flags & AB_VERBOSE))
    fprintf(stderr, "localmin failed to converge, t = %d.\n", t);

  memcpy(ab->lmx, x[id], n*d*sizeof(real));
  if (u < ab->emin && (flags & AB_LMREGISTER)) {
    ab->emin = u;
    memcpy(ab->xmin, x[id], n*d*sizeof(real));
    if (flags & AB_LMWRITE)
      ab_writepos(ab, ab->xmin, NULL, "abmin.pos");
  }

  return u;
}


#define ab_ekin(ab, tk) md_ekin(ab->v, ab->n * ab->d, ab->dof, tk)

#define ab_vrescale(ab, tp, dt, ek, tk) \
    md_vrescale(ab->v, ab->n * ab->d, ab->dof, tp, dt, ek, tk)


INLINE int ab_vv2d(abpro_t *ab, real fscal, real dt, int soft, int milc)
{
  int i, verbose = 1, n = ab->n;
  real dth = .5f*dt*fscal;
  rv2_t *v = (rv2_t *) ab->v, *x = (rv2_t *) ab->x, *x1 = (rv2_t *) ab->x1, *f = (rv2_t *) ab->f;

#ifdef _OPENMP
#pragma omp parallel for schedule(static)
#endif
  for (i = 0; i < n; i++) { /* vv part 1 */
    rv2_sinc(v[i], f[i], dth); /* v += f * dth */
    rv2_sadd(x1[i], x[i], v[i], dt); /* x1 = x + v * dt */
  }
  if (milc) {
    i = ab_milcshake(ab, ab->x, ab->x1, ab->v, dt, 0, 0., verbose);
  } else {
    i = ab_shake(ab, ab->x, ab->x1, ab->v, dt, 0, 0., verbose);
  }
  die_if (i != 0, "t=%g: shake failed\n", ab->t);
  rv2_ncopy(x, x1, n);

  ab->epot = ab_force(ab, ab->x, ab->f, soft); /* calculate force */

#ifdef _OPENMP
#pragma omp parallel for schedule(static)
#endif
  for (i = 0; i < n; i++) { /* vv part 2 */
    rv2_sinc(v[i], f[i], dth);
  }
  if (milc) {
    i = ab_milcrattle(ab, ab->x, ab->v);
  } else {
    i = ab_rattle(ab, ab->x, ab->v, 0, 0., verbose);
  }

  ab->ekin = ab_ekin(ab, &ab->tkin);

  die_if (i != 0, "t=%g: failed rattle\n", ab->t);
  ab->t += dt;
  return 0;
}

INLINE int ab_vv3d(abpro_t *ab, real fscal, real dt, int soft, int milc)
{
  int i, verbose = 1, n = ab->n;
  real dth = .5f*dt*fscal;
  rv3_t *v = (rv3_t *) ab->v, *x = (rv3_t *) ab->x, *x1 = (rv3_t *) ab->x1, *f = (rv3_t *) ab->f;

#ifdef _OPENMP
#pragma omp parallel for schedule(static)
#endif
  for (i = 0; i < n; i++) { /* vv part 1 */
    rv3_sinc(v[i], f[i], dth); /* v += f * dth */
    rv3_sadd(x1[i], x[i], v[i], dt); /* x1 = x + v * dt */
  }
  if (milc) {
    i = ab_milcshake(ab, ab->x, ab->x1, ab->v, dt, 0, 0., verbose);
  } else {
    i = ab_shake(ab, ab->x, ab->x1, ab->v, dt, 0, 0., verbose);
  }
  die_if (i != 0, "t=%g: shake failed\n", ab->t);
  rv3_ncopy(x, x1, n);

  ab->epot = ab_force(ab, ab->x, ab->f, soft); /* calculate force */

#ifdef _OPENMP
#pragma omp parallel for schedule(static)
#endif
  for (i = 0; i < n; i++) { /* vv part 2 */
    rv3_sinc(v[i], f[i], dth);
  }
  if (milc) {
    i = ab_milcrattle(ab, ab->x, ab->v);
  } else {
    i = ab_rattle(ab, ab->x, ab->v, 0, 0., verbose);
  }

  ab->ekin = ab_ekin(ab, &ab->tkin);

  die_if (i != 0, "t=%g: failed rattle\n", ab->t);
  ab->t += dt;
  return 0;
}


/* one step of velocity verlet integrator */
INLINE int ab_vv(abpro_t *ab, real fscal, real dt, unsigned flags)
{
  int soft = (flags & AB_SOFTFORCE), milc = (flags & AB_MILCSHAKE);
  return (ab->d == 3) ?
    ab_vv3d(ab, fscal, dt, soft, milc) :
    ab_vv2d(ab, fscal, dt, soft, milc);
}


/* Brownian dynamics */
INLINE int ab_brownian(abpro_t *ab, real T, real fscal, real dt, unsigned flags)
{
  int soft = (flags & AB_SOFTFORCE), milc = (flags & AB_MILCSHAKE);
  int i, nd = ab->n * ab->d, verbose = 1;
  real amp = (real) sqrt(2*dt*T);

  for (i = 0; i < nd; i++)
    ab->x1[i] = ab->x[i] + fscal*ab->f[i]*dt + (real)(randgaus() * amp);

  if (milc) {
    i = ab_milcshake(ab, ab->x, ab->x1, NULL, 0.f, 0, 0., verbose);
  } else {
    i = ab_shake(ab, ab->x, ab->x1, NULL, 0.f, 0, 0., verbose);
  }
  die_if (i != 0, "t=%g: failed shake\n", ab->t);
  memcpy(ab->x, ab->x1, nd*sizeof(real));

  ab->epot = ab_force(ab, ab->x, ab->f, soft); /* calculate force */
  ab->t += dt;
  return 0;
}


/* local geometric constraints (LGC) */

/* initialize local constraints,
 * level 1: aba, 2: abba, 3: both */
INLINE void ab_initconstr(abpro_t *ab, int level)
{
  int i, di, n = ab->n;
  real dr0, rref[2][2] = {{1.115f, 1.16f}, {1.09f, 1.2f}}; /* empirical constraint distances */

  if (level < 0) { /* default level */
    if (ab->model == 2) level = 1; else level = 3;
  }
  if (ab->d == 2 || level == 0) return;
  ab->lgcnt = 0;
  xnew(ab->lgc, 1);
  for (di = 2; di <= 3; di++) { /* loop over ABA and ABBA */
    if ( !(level & (di - 1)) ) continue;
    dr0 = rref[ab->model - 1][di - 2];

    for (i = 0; i < n - di; i++) {
      if (ab->type[i] != 0 || ab->type[i + di] != 0) continue;
      xrenew(ab->lgc, ab->lgcnt + 1);
      ab->lgc[ab->lgcnt].i = i;
      ab->lgc[ab->lgcnt].j = i + di;
      ab->lgc[ab->lgcnt].on = 0;
      ab->lgc[ab->lgcnt].r2ref = dr0 * dr0;
      ab->lgcnt++;
    }
  }
  ab->lgcon = 1; /* turn on constraints by default */
  ab->lgact = 0; /* no constraint is active yet */
}


/* update constraints if atoms are close enough*/
INLINE void ab_updconstr(abpro_t *ab, double r2max)
{
  int i, j, k, lgcnt = ab->lgcnt;
  real dr2;

  if (!ab->lgcon) return;
  if (r2max <= 0) r2max = 0.3; /* default value */
  for (k = 0; k < lgcnt; k++) { /* try to turn on constraints */
    if (ab->lgc[k].on) continue;
    i = ab->lgc[k].i;
    j = ab->lgc[k].j;
    dr2 = rv3_dist2(ab->x + 3*i, ab->x + 3*j);
    if (fabs(dr2 - ab->lgc[k].r2ref) < r2max) {
      ab->lgc[k].on = 1;
      ab->lgact++;
    }
  }
  ab->dof = ab->dof0 - ab->lgact;
}

#endif /* ZCOM_ABPRO__ */
#endif /* ZCOM_ABPRO */





#ifdef  ZCOM_CAGO
#ifndef ZCOM_CAGO__
#define ZCOM_CAGO__


/* alpha-carbon based Go-model */
typedef struct {
  int n; /* number of residues */
  int dof; /* degree of freedom */
  unsigned flags; /* input flags */

  real kb; /* .5 kb (b - b0)^2, ~ 200 */
  real ka; /* .5 ka (a - a0)^2, ~ 40 */
  real kd1, kd3; /* kd1 (1 - cos(d - d0)) + kd3 (1 - cos(3*(d-d0))), ~ 1 & 0.5 */
  real nbe, nbc; /* nbc ~ 4 A */

  rv3_t *xref;
  real epotref; /* energy of the reference structure */
  int *iaa; /* integer amino acid type */
  real *bref; /* bonds */
  real *aref; /* angle */
  real *dref; /* dihedral */
  real *r2ref; /* pair distance */

  int ncont; /* number of defined contacts */
  int *iscont; /* if the pair i-j is a contact */

  /* variables for MD simulations */
  rv3_t *x, *v, *f, *x1;
  real ekin, tkin, epot;
} cago_t;


#define CAGO_VERBOSE 0x1000

INLINE real cago_force(cago_t *go, rv3_t *x, rv3_t *f);

#define cago_ekin(go, v, tk) md_ekin3d(v, go->n, go->dof, tk)

#define cago_vrescale(go, tp, dt, ek, tk) \
  md_vrescale3d(go->v, go->n, go->dof, tp, dt, ek, tk)

#define cago_vrescalex(go, tp, dt, ek, tk) \
  md_vrescalex3d(go->v, go->n, go->dof, tp, dt, ek, tk)

#define cago_mcvrescale(go, tp, dt, ek, tk) \
  md_mcvrescale3d(go->v, go->n, go->dof, tp, dt, ek, tk)

/* convenient macro for computing RMSD from the reference structure */
#define cago_rmsd(go, x, xf) rv3_rmsd(x, xf, go->xref, NULL, go->n, 0, NULL, NULL)

/* compute the reference bond lengths, angles, dihedrals and pair distances */
INLINE int cago_refgeo(cago_t *go)
{
  int i, j, n = go->n;

  /* calculate reference bond lengths, angles, dihedrals */
  xnew(go->bref, n - 1); /* bonds */
  for (i = 0; i < n - 1; i++)
    go->bref[i] = rv3_dist(go->xref[i], go->xref[i + 1]);

  xnew(go->aref, n - 2); /* angles */
  for (i = 1; i < n - 1; i++)
    go->aref[i - 1]  = rv3_ang(go->xref[i - 1], go->xref[i], go->xref[i + 1],
      NULL, NULL, NULL);

  xnew(go->dref, n - 3); /* dihedrals */
  for (i = 0; i < n - 3; i++)
    go->dref[i] = rv3_dih(go->xref[i], go->xref[i + 1],
        go->xref[i + 2], go->xref[i + 3], NULL, NULL, NULL, NULL);

  /* reference pair distances */
  xnew(go->r2ref, n*n);
  for (i = 0; i < n - 1; i++)
    for (j = i + 1; j < n; j++)
      go->r2ref[j*n + i] = go->r2ref[i*n + j]
          = rv3_dist2(go->xref[i], go->xref[j]);
  return 0;
}


/* return cago_t from pdb file fnpdb
 * `rcc' is the cutoff radius for defining contacts
 * `ctype' is one of PDB_CONTACT_CA, _HEAVY, _ALL
 * `nsexcl' is the number of successive residues to be excluded as contacts
 * e.g., nsexcl = 4 means `a' and `d' in -a-b-c-d- are excluded */
INLINE cago_t *cago_open1(const char *fnpdb, real rcc, int ctype, int nsexcl, unsigned flags)
{
  cago_t *go;
  int i, j;
  pdbmodel_t *pm;
  pdbaac_t *c;

  /* read all atoms from the .pdb file */
  if ((pm = pdbm_read(fnpdb, 0)) == NULL) {
    fprintf(stderr, "cannot open PDB file %s\n", fnpdb);
    return NULL;
  }
  xnew(go, 1);
  go->iscont = pdbm_contact(pm, rcc, ctype, nsexcl, flags & CAGO_VERBOSE);
  c = pdbaac_parse(pm, 0); /* parse it into amino-acid residues */
  pdbm_free(pm);
  if (c == NULL) {
    fprintf(stderr, "cannot parse PDB from %s to residues\n", fnpdb);
    return NULL;
  }

  go->n = c->nres;
  go->dof = go->n*3 - 6;
  xnew(go->xref, go->n);
  xnew(go->iaa, go->n);
  /* extract the coordinates of alpha carbon atoms */
  for (i = 0; i < go->n; i++) {
    rv3_copy(go->xref[i], c->res[i].xca);
    go->iaa[i] = c->res[i].iaa; /* integer amino-acid type */
  }
  pdbaac_free(c); /* throw away pdbaac */

  /* compute the reference bond length, angles, etc. */
  cago_refgeo(go);

  /* count the number of contacts */
  for (go->ncont = 0, i = 0; i < go->n - 1; i++)
    for (j = i + 1; j < go->n; j++)
      go->ncont += go->iscont[ i*go->n + j ];
  return go;
}


/* set force parameters */
INLINE void cago_setfparam(cago_t *go, real kb, real ka, real kd1, real kd3,
    real nbe, real nbc)
{
  go->kb = kb;
  go->ka = ka;
  go->kd1 = kd1;
  go->kd3 = kd3;
  go->nbe = nbe;
  go->nbc = nbc;
}


#define cago_openez(fndpb, kb, ka, kd1, kd3, nbe, nbc, rcc) \
  cago_open(fnpdb, kb, ka, kd1, kd3, nbe, nbc, rcc, \
            PDB_CONTACT_HEAVY, 4, CAGO_VERBOSE)


/* return a pointer to cago_t from PDB file `fnpdb'
 * cago_open1() + bond parameters */
INLINE cago_t *cago_open(const char *fnpdb, real kb, real ka, real kd1, real kd3,
    real nbe, real nbc, real rcc, int ctype, int nsexcl, unsigned flags)
{
  cago_t *go = cago_open1(fnpdb, rcc, ctype, nsexcl, flags);
  if (go == NULL) return NULL;
  cago_setfparam(go, kb, ka, kd1, kd3, nbe, nbc);
  return go;
}


/* destroy cago_t */
INLINE void cago_close(cago_t *go)
{
  if (go->x) free(go->x);
  if (go->v) free(go->v);
  if (go->f) free(go->f);
  if (go->x1) free(go->x1);
  if (go->iscont) free(go->iscont);
  free(go->bref);
  free(go->aref);
  free(go->dref);
  free(go->r2ref);
  free(go->xref);
  free(go->iaa);
  memset(go, '\0', sizeof(*go));
  free(go);
}


/* remove center of mass motion, linear and angular */
INLINE void cago_rmcom(cago_t *go, rv3_t *x, rv3_t *v)
{
  md_shiftcom3d(x, go->n);
  md_shiftcom3d(v, go->n);
  md_shiftang3d(x, v, go->n);
}


/* initialize molecular dynamics
 *  o create an initial structure
 *    if `open', start from a nearly-straight chain,
 *      with a disturbance of `rndamp' in the x, y directions
 *    otherwise start from the reference structure,
 *      with a random disturbance of `rndamp'
 *  o initialize the velocity with the center of mass motion removed
 *  o compute the initial force and energy */
INLINE int cago_initmd(cago_t *go, int open, double rndamp, double T0)
{
  int i, n = go->n;
  real s, dx[3];

  xnew(go->f, n);
  xnew(go->v, n);
  xnew(go->x, n);
  xnew(go->x1, n);

  /* initialize position */
  if (open) { /* open chain */
    for (i = 0; i < n - 1; i++) {
      rv3_normalize( rv3_make(dx, 1,
            (real) randunif(-rndamp, rndamp),
            (real) randunif(-rndamp, rndamp) ) );
      /* x_{i+1} = x_i + dx * bref[i] */
      rv3_sadd(go->x[i + 1], go->x[i], dx, go->bref[i]);
    }
  } else { /* copy from xref, slightly disturb it */
    for (i = 0; i < n; i++)
      rv3_sadd(go->x[i], go->xref[i], rv3_randunif(dx, -1, 1), rndamp);
  }
  go->epotref = cago_force(go, go->xref, go->f);

  /* initialize velocities */
  for (i = 0; i < n; i++)
    rv3_randunif(go->v[i], -0.5f, 0.5f);
  cago_rmcom(go, go->x, go->v); /* remove center of mass motion */
  for (s = 0, i = 0; i < n; i++)
    s += rv3_sqr(go->v[i]);
  s = sqrt(3 * n * T0 / s);
  for (i = 0; i < n; i++)
    rv3_smul(go->v[i], s);
  go->ekin = cago_ekin(go, go->v, &go->tkin);
  return 0;
}


/* bond energy 1/2 k (r - r0)^2 */
INLINE real potbond(rv3_t a, rv3_t b, real r0, real k,
    rv3_t fa, rv3_t fb)
{
  real dx[3], r, dr;

  r = rv3_norm( rv3_diff(dx, a, b) );
  dr = r - r0;
  if (fa != NULL) {
    real amp = k * dr / r;
    rv3_sinc(fa, dx, -amp);
    rv3_sinc(fb, dx,  amp);
  }
  return .5f * k * dr * dr;
}


/* harmonic angle 1/2 k (ang - ang0)^2 */
INLINE real potang(rv3_t a, rv3_t b, rv3_t c, real ang0, real k,
    rv3_t fa, rv3_t fb, rv3_t fc)
{
  real dang, amp, ga[3], gb[3], gc[3];

  if (fa) { /* compute gradient */
    dang = rv3_ang(a, b, c, ga, gb, gc) - ang0;
    amp = -k * dang;
    rv3_sinc(fa, ga, amp);
    rv3_sinc(fb, gb, amp);
    rv3_sinc(fc, gc, amp);
  } else {
    dang = rv3_ang(a, b, c, NULL, NULL, NULL) - ang0;
  }
  return .5f * k * dang * dang;
}


/* 1-3 dihedral: k1 * (1 - cos(dang)) + k3 * (1 - cos(3*dang)) */
INLINE real potdih13(rv3_t a, rv3_t b, rv3_t c, rv3_t d, real ang0,
    real k1, real k3, rv3_t fa, rv3_t fb, rv3_t fc, rv3_t fd)
{
  real dang, amp, ga[3], gb[3], gc[3], gd[3];

  if (fa) {
    dang = rv3_dih(a, b, c, d, ga, gb, gc, gd) - ang0;
    amp  = (real)( -k1 * sin(dang) - 3 * k3 * sin(3*dang));
    rv3_sinc(fa, ga, amp);
    rv3_sinc(fb, gb, amp);
    rv3_sinc(fc, gc, amp);
    rv3_sinc(fd, gd, amp);
  } else {
    dang = rv3_dih(a, b, c, d, NULL, NULL, NULL, NULL) - ang0;
  }
  return (real)( k1 * (1 - cos(dang)) + k3 * (1 - cos(3 * dang)) );
}


/* 12-10 potential: u = 5(rc/r)^12 - 6(rc/r)^10,
 * the minimum is at r = rc, and u = -1 */
INLINE real pot1210(rv3_t a, rv3_t b, real rc2, real eps, rv3_t fa, rv3_t fb)
{
  real dx[3], dr2, invr2, invr4, invr6, invr10, amp;

  dr2 = rv3_sqr( rv3_diff(dx, a, b) );
  invr2 = rc2 / dr2;
  invr4 = invr2 * invr2;
  invr6 = invr4 * invr2;
  invr10 = invr4 * invr6;
  if (fa) {
    amp = 60 * eps * (invr2 - 1) * invr10 / dr2;
    rv3_sinc(fa, dx,  amp);
    rv3_sinc(fb, dx, -amp);
  }
  return eps * (5 * invr2 - 6) * invr10;
}


/* repulsive potential: (rc/r)^12 */
INLINE real potr12(rv3_t a, rv3_t b, real rc2, real eps, rv3_t fa, rv3_t fb)
{
  real dx[3], dr2, invr2, invr6, u, amp;

  dr2 = rv3_sqr( rv3_diff(dx, a, b) );
  invr2 = rc2 / dr2;
  invr6 = invr2 * invr2 * invr2;
  u = eps * invr6 * invr6;
  if (fa) {
    amp = 12 * u / dr2;
    rv3_sinc(fa, dx,  amp);
    rv3_sinc(fb, dx, -amp);
  }
  return u;
}


/* force field from C. Clementi, H. Nymeyer, J. N. Onuchic,
 * J. Mol. Biol, Vol. 298 (2000) 937-953 */
INLINE real cago_force(cago_t *go, rv3_t *x, rv3_t *f)
{
  int i, j, id, n = go->n;
  real ene = 0, kb = go->kb, ka = go->ka, kd1 = go->kd1, kd3 = go->kd3;
  real nbe = go->nbe, nbc2 = go->nbc * go->nbc;

  if (f != NULL) {
    for (i = 0; i < n; i++) rv3_zero(f[i]);
  }

  /* bonds */
  for (i = 0; i < n - 1; i++)
    ene += potbond(x[i], x[i + 1], go->bref[i], kb, f[i], f[i + 1]);

  /* angles */
  for (i = 0; i < n - 2; i++)
    ene += potang(x[i], x[i + 1], x[i + 2], go->aref[i],
              ka, f[i], f[i + 1], f[i + 2]);

  /* dihedrals */
  for (i = 0; i < n - 3; i++)
    ene += potdih13(x[i], x[i + 1], x[i + 2], x[i + 3], go->dref[i],
          kd1, kd3, f[i], f[i + 1], f[i + 2], f[i + 3]);

  /* non-bonded */
  for (i = 0; i < n - 4; i++)
    for (j = i + 4; j < n; j++) {
      id = i*n + j;
      if ( go->iscont[id] ) { /* contact pair */
        ene += pot1210(x[i], x[j], go->r2ref[id], nbe, f[i], f[j]);
      } else {
        ene += potr12(x[i], x[j], nbc2, nbe, f[i], f[j]);
      }
    }
  return ene;
}


/* velocity Verlet */
INLINE int cago_vv(cago_t *go, real fscal, real dt)
{
  int i, n = go->n;
  real dth = .5f*dt;
  rv3_t *v = go->v, *x = go->x, *f = go->f;

  die_if (x == NULL || v == NULL || f == NULL,
      "NULL point call cago_initmd() first, %p %p %p\n", x, v, f);

  for (i = 0; i < n; i++) { /* VV part 1 */
    rv3_sinc(v[i], f[i], dth*fscal);
    rv3_sinc(x[i], v[i], dt);
  }

  go->epot = cago_force(go, go->x, go->f); /* calculate force */

  for (i = 0; i < n; i++) { /* VV part 2 */
    rv3_sinc(v[i], f[i], dth*fscal);
  }
  go->ekin = cago_ekin(go, go->v, &go->tkin);
  return 0;
}


/* the change of the potential energy */
INLINE real cago_depot(cago_t *go, rv3_t *x, int i, rv3_t xi)
{
  int j, id, n = go->n;
  rv3_t *xn = go->x1; /* we use x1 freely here */
  real ene = 0;
  real ka = go->ka, kb = go->kb, kd1 = go->kd1, kd3 = go->kd3;
  real nbe = go->nbe, nbc2 = go->nbc * go->nbc;

  /* copy coordinates */
  for (j = 0; j < n; j++) {
    if (j == i) rv3_copy(xn[i], xi);
    else rv3_copy(xn[j], x[j]);
  }

  /* bonds */
  for (j = i - 1; j <= i; j++) {
    if (j < 0 || j >= n - 1) continue;
    ene -= potbond(x[j], x[j + 1], go->bref[j], kb, NULL, NULL);
    ene += potbond(xn[j], xn[j + 1], go->bref[j], kb, NULL, NULL);
  }

  /* angles */
  for (j = i - 1; j <= i + 1; j++) {
    if (j < 1 || j >= n - 1) continue;
    ene -= potang(x[j - 1], x[j], x[j + 1], go->aref[j - 1], ka,
        NULL, NULL, NULL);
    ene += potang(xn[j - 1], xn[j], xn[j + 1], go->aref[j - 1], ka,
        NULL, NULL, NULL);
  }

  /* dihedrals */
  for (j = i - 3; j <= i; j++) {
    if (j < 0 || j >= n - 3) continue;
    ene -= potdih13(x[j], x[j + 1], x[j + 2], x[j + 3], go->dref[j],
        kd1, kd3, NULL, NULL, NULL, NULL);
    ene += potdih13(xn[j], xn[j + 1], xn[j + 2], xn[j + 3], go->dref[j],
        kd1, kd3, NULL, NULL, NULL, NULL);
  }

  /* non-bonded interaction */
  for (j = 0; j < n; j++) {
    if (j > i - 4 && j < i + 4) continue;

    id = i*n + j;
    if ( go->iscont[id] ) { /* contact pair */
      ene -= pot1210(x[i], x[j], go->r2ref[id], nbe, NULL, NULL);
      ene += pot1210(xn[i], xn[j], go->r2ref[id], nbe, NULL, NULL);
    } else { /* non-contact pair */
      ene -= potr12(x[i], x[j], nbc2, nbe, NULL, NULL);
      ene += potr12(xn[i], xn[j], nbc2, nbe, NULL, NULL);
    }
  }
  return ene;
}


/* metropolis algorithm */
INLINE int cago_metro(cago_t *go, real amp, real bet)
{
  int i;
  rv3_t xi;
  real du;

  i = (int) (go->n * rand01());
  rv3_inc(rv3_randunif(xi, -amp, amp), go->x[i]);
  du = cago_depot(go, go->x, i, xi);
  if (du < 0 || rand01() < exp(-bet * du)) {
    rv3_copy(go->x[i], xi);
    go->epot += du;
    return 1;
  } else
    return 0;
}


/* count the number of native contacts that are formed in the structure `x'
 * this counting process is independent of the process of defining contacts
 *   although the two processes are very similar, and may be the same
 * here, given a set of defined contacts, we simple observe how many pairs
 *   are close enough to be regarded as contacts
 * a contact is formed if the pair distance is <= gam * native-distance
 * return the number of contacts
 * `*Q' is the ratio of formed contacts / the total number of contacts  */
INLINE int cago_ncontacts(cago_t *go, rv3_t *x, real gam, real *Q, int *mat)
{
  int i, j, id, nct = 0, n = go->n;

  if (gam < 0) gam = 1.2; /* default value */
  if (mat) for (id = 0; id < n * n; id++) mat[id] = 0;

  for (i = 0; i < n - 1; i++)
    for (j = i + 1; j < n; j++) {
      id = i * n + j;
      if ( !go->iscont[id] ) continue;
      if (rv3_dist(x[i], x[j]) < sqrt(go->r2ref[id]) * gam) {
        if (mat) mat[id] = mat[j*n + i] = 1;
        nct++;
      }
    }

  if (Q) *Q = nct / go->ncont;
  return nct;
}


/* write position/velocity file */
INLINE int cago_writepos(cago_t *go, rv3_t *x, rv3_t *v, const char *fn)
{
  FILE *fp;

  if (fn == NULL) fn = "cago.pos";
  xfopen(fp, fn, "w", return -1);
  fprintf(fp, "# %d %d\n", go->n, (v != NULL));
  md_writepos3d(fp, x, v, go->n, 1);
  fclose(fp);
  return 0;
}


/* read position/velocity file */
INLINE int cago_readpos(cago_t *go, rv3_t *x, rv3_t *v, const char *fn)
{
  char s[1024];
  FILE *fp;
  int i, hasv = 0, ret = -1;

  if (fn == NULL) fn = "cago.pos";
  xfopen(fp, fn, "r", return -1);
  if (fgets(s, sizeof s, fp) == NULL || s[0] != '#') {
    fprintf(stderr, "Warning: %s has no information line\n", fn);
    rewind(fp);
  } else {
    if (2 != sscanf(s + 1, "%d%d", &i, &hasv) || i != go->n ) {
      fprintf(stderr, "first line is corrupted:\n%s", s);
      goto ERR;
    }
  }
  ret = md_readpos3d(fp, x, hasv ? v : NULL, go->n, 1);
ERR:
  fclose(fp);
  return ret;
}


/* output pdb format */
INLINE int cago_writepdb(cago_t *go, rv3_t *x, const char *fn)
{
  FILE *fp;
  int i, n = go->n;

  xfopen(fp, fn, "w", return -1);
  for (i = 0; i < n; i++)
    fprintf(fp, "ATOM  %5d  CA  %-4sA%4d    %8.3f%8.3f%8.3f  1.00  0.00           C  \n",
        i + 1, pdbaaname(go->iaa[i]), i + 1, x[i][0], x[i][1], x[i][2]);
  fprintf(fp, "END%77s\n", " ");
  fclose(fp);
  return 0;
}

#endif /* ZCOM_CAGO__ */
#endif /* ZCOM_CAGO */





#ifdef  ZCOM_GLEZ
#ifndef ZCOM_GLEZ__
#define ZCOM_GLEZ__
#if defined(Macintosh) || defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


static int glez_x, glez_y; /* current position */
static int glez_msdown; /* mouse state */

typedef struct tag_glez_menukey_t {
  int id;
  int key;
  const char *str;
  struct tag_glez_menukey_t *sub; /* pointer to sub menus */
} glez_menukey_t;

static glez_menukey_t *glez_user_menukey;

enum { GLEZ_MENU0 = 1000,
  GLEZ_MOVXM, GLEZ_MOVXP, GLEZ_MOVYM, GLEZ_MOVYP, GLEZ_MOVZM, GLEZ_MOVZP,
  GLEZ_ROTXM, GLEZ_ROTXP, GLEZ_ROTYM, GLEZ_ROTYP, GLEZ_ROTZM, GLEZ_ROTZP,
  GLEZ_SCLM, GLEZ_SCLP, GLEZ_FULLS, GLEZ_MENU1 };

/* rotation sub-menu */
STRCLS glez_menukey_t glez_menukey_rot[] = {
  {GLEZ_ROTXM,  'x', "Rotate around -x", NULL},
  {GLEZ_ROTXP,  'X', "Rotate around +x", NULL},
  {GLEZ_ROTYM,  'y', "Rotate around -y", NULL},
  {GLEZ_ROTYP,  'Y', "Rotate around +y", NULL},
  {GLEZ_ROTZM,  'z', "Rotate around -z", NULL},
  {GLEZ_ROTZP,  'Z', "Rotate around +z", NULL},
  {-1, '\0', NULL, NULL}};

/* scaling sub-menu */
STRCLS glez_menukey_t glez_menukey_scl[] = {
  {GLEZ_SCLM,   's', "Zoom out", NULL},
  {GLEZ_SCLP,   'S', "Zoom in", NULL},
  {GLEZ_FULLS,  'f', "Toggle fullscreen", NULL},
  {-1, '\0', NULL, NULL}};

STRCLS glez_menukey_t glez_menukey_mov[] = {
  {GLEZ_MOVXM,  'l', "Move toward -x", NULL},
  {GLEZ_MOVXP,  'r', "Move toward +x", NULL},
  {GLEZ_MOVYM,  'd', "Move toward -y", NULL},
  {GLEZ_MOVYP,  'u', "Move toward +y", NULL},
  {GLEZ_MOVZM,  'f', "Move toward -y", NULL},
  {GLEZ_MOVZP,  'n', "Move toward +y", NULL},
  {-1, '\0', NULL, NULL}};

/* main menu */
STRCLS glez_menukey_t glez_menukey[] = {
  {0,           0, "Move",   glez_menukey_mov},
  {0,           0, "Rotate", glez_menukey_rot},
  {0,           0, "Zoom",   glez_menukey_scl},
  {-1, '\0', NULL, NULL}};

static void (*glez_user_reshapefunc)(int w, int h) = NULL;
#define glezReshapeFunc(f)  { glez_user_reshapefunc = f;  glutReshapeFunc(glez_reshapefunc); }

static void (*glez_user_menufunc)(int id) = NULL;
static void (*glez_user_keyboardfunc)(unsigned char c, int x, int y) = NULL;

static void (*glez_user_mousefunc)(int button, int state, int w, int h) = NULL;
#define glezMouseFunc(f)    { glez_user_mousefunc = f;  glutMouseFunc(glez_mousefunc); }

static void (*glez_user_motionfunc)(int w, int h) = NULL;
#define glezMotionFunc(f)   { glez_user_motionfunc = f;  glutMotionFunc(glez_motionfunc); }


#ifdef _OPENMP
#pragma omp threadprivate(glez_x, glez_y, glez_msdown)
#pragma omp threadprivate(glez_user_menukey)
#pragma omp threadprivate(glez_user_reshapefunc)
#pragma omp threadprivate(glez_user_menufunc)
#pragma omp threadprivate(glez_user_keyboardfunc)
#pragma omp threadprivate(glez_user_mousefunc)
#pragma omp threadprivate(glez_user_motionfunc)
#endif


/* toggle full screen state */
INLINE void glez_fullscreen(void)
{
  static int full = 0, x, y, w, h;
#ifdef _OPENMP
#pragma omp threadprivate(full, x, y, w, h)
#endif

  full = !full;
  if (full) {
    x = glutGet(GLUT_WINDOW_X);
    y = glutGet(GLUT_WINDOW_Y);
    w = glutGet(GLUT_WINDOW_WIDTH);
    h = glutGet(GLUT_WINDOW_HEIGHT);
    glutFullScreen();
  } else {
    glutPositionWindow(x, y);
    glutReshapeWindow(w, h);
  }
}


/* standard reshape function for GLUT
 * x: (-1, 1), y: (-1, 1), z: (-10, 10) */
INLINE void glez_reshapefunc(int w, int h)
{
  double xs = 1, ys = 1, zs = 10;

  if (w > h) xs = 1.*w/h;
  else ys = 1.*h/w;
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-xs, xs, -ys, ys, -zs, zs);
  glMatrixMode(GL_MODELVIEW);

  if (glez_user_reshapefunc) (*glez_user_reshapefunc)(w, h);
}


/* menu function */
INLINE void glez_menufunc(int id)
{
  GLfloat mat[4][4], amp;

  if (id <= GLEZ_MENU0 || id >= GLEZ_MENU1) {
    if (glez_user_menufunc) (*glez_user_menufunc)(id);
  } else if (id == GLEZ_SCLM || id == GLEZ_SCLP) { /* scaling */
    GLfloat s = (id == GLEZ_SCLP) ? 1.02f : 1.0f/1.02f;

    glScalef(s, s, s);
    glutPostRedisplay();
  } else if (id == GLEZ_FULLS) { /* full screen */
    glez_fullscreen();
    glutPostRedisplay();
  } else if (id >= GLEZ_MOVXM && id <= GLEZ_MOVZP) { /* translations */
    amp = ((id + GLEZ_MOVXM) % 2) ? .02f : -.02f;
    id = (id - GLEZ_MOVXM) / 2;
    glGetFloatv(GL_MODELVIEW_MATRIX, (GLfloat *) mat);
    glTranslatef(mat[0][id]*amp, mat[1][id]*amp, mat[2][id]*amp);
    glutPostRedisplay();
  } else if (id >= GLEZ_ROTXM && id <= GLEZ_ROTZP) { /* rotations */
    if (id < GLEZ_ROTXM || id > GLEZ_ROTZP) return;
    amp = ((id + GLEZ_ROTXM) % 2) ? 5.f : -5.f;
    id = (id - GLEZ_ROTXM) / 2;
    glGetFloatv(GL_MODELVIEW_MATRIX, (GLfloat *) mat);
    glRotatef(amp, mat[0][id], mat[1][id], mat[2][id]);
    glutPostRedisplay();
  }
}


/* recursively match short-cut keys */
INLINE int glez_keylow(unsigned char c, glez_menukey_t *mk)
{
  int i;

  if (mk == NULL) return 0;
  for (i = 0; ; i++) {
    if (mk[i].sub != NULL) {
      if (glez_keylow(c, mk[i].sub)) return 1;
    } else if (mk[i].key == 0) {
      break;
    } else if (c == mk[i].key) {
      glez_menufunc(mk[i].id);
      return 1;
    }
  }
  return 0;
}


/* system keyboard function */
INLINE void glez_keyboardfunc(unsigned char c, int x, int y)
{
  if (glez_keylow(c, glez_menukey)) return;
  if (glez_keylow(c, glez_user_menukey)) return;
  /* pass an unhandled key to glez_user_keyboardfunc */
  if (glez_user_keyboardfunc) (*glez_user_keyboardfunc)(c, x, y);
}


/* create a menu hierarchy as specified by mk */
INLINE void glez_addmenu(glez_menukey_t *mk)
{
  int i, menuid, subid;
  char s[64];

  if (mk == NULL) return;
  for (i = 0; ; i++) {
    if (mk[i].sub != NULL) { /* sub menu */
      menuid = glutGetMenu(); /* get menu id */
      subid = glutCreateMenu(glez_menufunc);
      glez_addmenu(mk[i].sub); /* recursively create sub-menus */
      glutSetMenu(menuid); /* return to the menu */
      glutAddSubMenu(mk[i].str, subid);
    } else if (mk[i].key == 0) {
      break;
    } else { /* regular menu */
      sprintf(s, "%.32s, key: %c\n", mk[i].str, mk[i].key);
      glutAddMenuEntry(s, mk[i].id);
    }
  }
}


INLINE void glezMenuKeyFunc(void (*menuf)(int), void (*keyf)(unsigned char, int, int),
    glez_menukey_t *mk)
{
  glez_user_menufunc = menuf;
  glez_user_keyboardfunc = keyf;
  glez_user_menukey = mk;

  glutCreateMenu(glez_menufunc);
  glez_addmenu(mk); /* add user menu */
  glez_addmenu(glez_menukey); /* add system menu */
  glutAttachMenu(GLUT_RIGHT_BUTTON);

  glutKeyboardFunc(glez_keyboardfunc);
}


INLINE void glez_mousefunc(int button, int state, int x, int y)
{
  if (state == GLUT_DOWN) {
    glez_msdown++;
    if (button == 3)
      glez_menufunc(GLEZ_SCLP);
    else if (button == 4)
      glez_menufunc(GLEZ_SCLM);
  } else if (--glez_msdown <= 0) {
    glez_msdown = 0;
  }
  glez_x = x;
  glez_y = y;
  if (glez_user_mousefunc) (*glez_user_mousefunc)(button, state, x, y);
}


/* mouse motion function for GLUT */
INLINE void glez_motionfunc(int x, int y)
{
  if (x == glez_x && y == glez_y) return;
  if (glez_msdown) {
    float angx = (float)( (y - glez_y) * 360.f / glutGet(GLUT_WINDOW_HEIGHT) );
    float angy = (float)( (x - glez_x) * 360.f / glutGet(GLUT_WINDOW_WIDTH) );
    float mat[4][4];

    glGetFloatv(GL_MODELVIEW_MATRIX, (GLfloat *) mat);
    glRotatef(angx, mat[0][0], mat[1][0], mat[2][0]);
    glRotatef(angy, mat[0][1], mat[1][1], mat[2][1]);
    glutPostRedisplay();
  }
  glez_x = x;
  glez_y = y;
  if (glez_user_motionfunc) (*glez_user_motionfunc)(x, y);
}


STRCLS int glezInitWindow(int *argc, char **argv, int w, int h, const char *name)
{
  int winid;

  glutInit(argc, argv);
  w = intmin(w, glutGet(GLUT_SCREEN_HEIGHT));
  h = intmin(h, glutGet(GLUT_SCREEN_WIDTH));
  glutInitWindowSize(w, h);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  winid = glutCreateWindow(name);

  /* register glez functions */
  glezReshapeFunc(NULL);
  glezMenuKeyFunc(NULL, NULL, NULL);
  glezMouseFunc(NULL);
  glezMotionFunc(NULL);

  return winid;
}


/* draw a stick from a to b, with radius r and nface faces */
INLINE void glez_drawstick(real a[], real b[], real r, int nface)
{
  int i;
  real l, c, s, th;
  rv3_t x, y, z, p, q, u;

  rv3_diff(z, b, a);
  l = rv3_norm(z); /* stick length */
  rv3_smul(z, 1.f/l);

  rv3_normalize( rv3_make(x, z[1], -z[0], 0) ); /* a vector perpendicular to v */
  rv3_normalize( rv3_cross(y, z, x) );

  glBegin(GL_QUAD_STRIP);
  for (i = 0; i <= nface; i++) {
    th = 2.*M_PI*i/nface;
    c = (real) cos(th);
    s = (real) sin(th);
    rv3_lincomb2(u, x, y, c, s);
    rv3_lincomb2(p, a, u, 1.f, r);
    rv3_lincomb2(q, b, u, 1.f, r);
    glNormal3d(u[0], u[1], u[2]);
    glVertex3d(p[0], p[1], p[2]);
    glVertex3d(q[0], q[1], q[2]);
  }
  glEnd();
}

#endif /* ZCOM_GLEZ__ */
#endif /* ZCOM_GLEZ */





/* finishing up */
#ifdef __INTEL_COMPILER
  #pragma warning pop
#elif defined(__GNUC__) && ( __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6))
  /* diagonistic push and pop are added in GCC 4.6 */
  #pragma GCC diagnostic pop
#endif

#ifdef _MSC_VER
  #pragma warning(pop)
#endif
