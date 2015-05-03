#ifndef MODEL_H__
#define MODEL_H__





/* parameters and basic data types */





#include "xdouble.h"
#include "util.h"





/* types of the charging parameter, xi */
enum {
  XITYPE_F,
  XITYPE_R,
  XITYPE_T,
  XITYPE_COUNT
};

const char *xitypes[] = {"f", "r", "t", "XITYPE_COUNT"};



/* types of the global charging parameter, xi */
enum {
  LAMTYPE_F,
  LAMTYPE_R,
  LAMTYPE_C,
  LAMTYPE_H,
  LAMTYPE_T,
  LAMTYPE_COUNT
};

const char *lamtypes[] = {"f", "r", "c", "h", "t", "LAMTYPE_COUNT"};



/* types of interactions */
enum {
  POTTYPE_HS,
  POTTYPE_WCA,
  POTTYPE_LJ,
  POTTYPE_GAUSS,
  POTTYPE_COUNT
};

const char *pottypes[] = {"Hard-sphere", "WCA", "LJ", "Gauss", "POTTYPE_COUNT"};



/* types of closures */
enum {
  IETYPE_PY,
  IETYPE_HNC,
  IETYPE_SQR,
  IETYPE_IR, /* inverse Rowlinson */
  IETYPE_HC, /* Hutchinson-Conkie */
  IETYPE_BS, /* series of bridge function components */
  IETYPE_COUNT
};

const char *ietypes[] = {"PY", "HNC", "SQR", "IR", "HC", "BS", "IETYPE_COUNT"};



/* types of solvers */
enum {
  SOLVER_PICARD,
  SOLVER_MDIIS,
  SOLVER_COUNT
};

const char *solvers[] = {"Picard", "MDIIS", "SOLVER_COUNT"};



typedef struct {
  xdouble damp;
  int streakmax;
} picard_params_t;



typedef struct {
  int nbases; /* number of bases */
  xdouble damp;
  int streakmax;
} mdiis_params_t;



/* types of self-consistent equations */
enum {
  SCTYPE_NONE,
  SCTYPE_P,
  SCTYPE_MU,
  SCTYPE_COUNT
};

const char *sctypes[] = {"None", "P", "mu", "SCTYPE_COUNT"};



typedef struct {
  int dim;
  xdouble rho;
  xdouble temp;
  xdouble beta;

  /* parameters for the density, rho, scan */
  int nrho;
  xdouble rhomax;
  xdouble drho;

  /* parameters for the charging parameter, xi, scan */
  int nxi;
  int xitype;

  /* parameters for the global charging parameter, lam, scan */
  int nlam;
  int lamtype;

  int pottype;
  int ietype;
  xdouble ies;
  int npt;
  int ffttype;
  xdouble rmax;
  int itmax;
  xdouble tol;
  int solver;
  xdouble bmuref;
  picard_params_t picard[1];
  mdiis_params_t mdiis[1];
  xdouble crmax;
  char *fncrtr;
  int verbose;
  const char *prog;
  const char *fncfg;
  const char *fnrep;
  const char *fnref;

  int sctype; /* self-consistent type */
  xdouble scdsmax; /* maximal updating magnitude for the parameter in the self-consistent equation */
  xdouble sctol; /* tolerance for s */

  int hsr; /* hard-sphere fluid, xi-r route */

  /* density series of the bridge function */
  int bslmax;
  const char *fnbs;
} model_t;



/* set default values of the parameters */
__inline static void model_default(model_t *m)
{
  memset(m, 0, sizeof(*m));
  m->dim = 3;
  m->rho = 0.3L;
  m->rhomax = m->rho;
  m->temp = 2;
  m->beta = 0.5;
  m->bmuref = 0;
  m->nrho = 1;
  m->drho = 0.01L;
  m->nxi = 100; /* number of xi scans */
  m->xitype = XITYPE_F;
  m->nlam = 100;
  m->lamtype = LAMTYPE_C;
  m->pottype = POTTYPE_HS;
  m->ietype = IETYPE_PY;
  m->ies = 0.5;
  m->npt = 2048;
  m->ffttype = 1;
  m->rmax = (xdouble) m->npt / 100;
  m->itmax = 20000;
  m->tol = 1e-10;
  m->solver = SOLVER_MDIIS;
  m->picard->damp = 0.5;
  m->picard->streakmax = 5;
  m->mdiis->damp = 0.5;
  m->mdiis->nbases = 3;
  m->mdiis->streakmax = 100;
  m->crmax = 1e30;
  m->fncrtr = NULL;
  m->verbose = 0;
  m->prog = NULL;
  m->fncfg = NULL;
  m->fnrep = NULL;
  m->fnref = "../../data/hs/Pmuhsvs12.dat";
  m->bslmax = 6;
  m->fnbs = "../../data/hs/crtrD3M8192ms.dat";
  m->sctype = SCTYPE_NONE;
  m->scdsmax = 0.1;
  m->sctol = 1e-8;
}



/* return the index of string from a predefined array */
__inline static int model_select(const char *s, int n, const char **arr)
{
  int i;

  for ( i = 0; i < n; i++ )
    if ( strcmpfuzzy(arr[i], s) == 0 )
      return i;

  if ( isdigit(s[0]) ) {
    i = atoi(s);
    if ( i >= 0 && i < n ) {
      return i;
    }
  }

  fprintf(stderr, "Error: cannot select %s from the array of %d items:", s, n);
  for ( i = 0; i < n; i++ )
    fprintf(stderr, " %s", arr[i]);
  fprintf(stderr, "\n");

  exit(1);
  return 0;
}



/* print help message and die */
__inline static void model_help(const model_t *m)
{
  fprintf(stderr, "Integral equations on a sphere\n");
  fprintf(stderr, "Usage:\n");
  fprintf(stderr, "  %s [Options] [input.cfg]\n\n", m->prog);
  fprintf(stderr, "Options:\n");
  fprintf(stderr, "  -o, --crtr=:   set the output crtr file, default: %s\n", m->fncrtr);
  fprintf(stderr, "  -O, --rep=:    set the output report file, default: %s\n", m->fnrep);
  fprintf(stderr, "  -D, --dim=:    set the dimension, default %d\n", m->dim);
  fprintf(stderr, "  -r, --rho=:    set the (maximal) density, default %g\n", (double) m->rho);
  fprintf(stderr, "  -T:            set the temperautre, default %g\n", (double) m->temp);
  fprintf(stderr, "  -z, --drho=:   set the density increment in a rho scan, default %g\n", (double) m->drho);
  fprintf(stderr, "  -x, --nxi=:    set the number of charging parameters in a xi scan, default %d\n", m->nxi);
  fprintf(stderr, "  -X:            set the charging parameter, xi, type, default %s\n", xitypes[m->xitype]);
  fprintf(stderr, "  -l, --nlam=:   set the number of global charging parameters in a lambda scan, default %d\n", m->nlam);
  fprintf(stderr, "  -L, --lam=:    set the global charging parameter, lambda, type, default %s\n", lamtypes[m->lamtype]);
  fprintf(stderr, "  -P, --pot=:    set the potential type: Hard-sphere, WCA or LJ, default %s\n", pottypes[m->pottype]);
  fprintf(stderr, "  -C, --ie=:     set the closure: PY, HNC, ..., default %s\n", ietypes[m->ietype]);
  fprintf(stderr, "  --sc=:         set the self-consistency type, default %s\n", sctypes[m->sctype]);
  fprintf(stderr, "  -S, --sol=:    set the solver: Picard or MDIIS, default %s\n", solvers[m->solver]);
  fprintf(stderr, "  --tol=:        set the tolerance, default %g\n", (double) m->tol);
  fprintf(stderr, "  --pdamp=:      set the mixing fraction for the new solution in the Picard solver, default %g\n", (double) m->picard->damp);
  fprintf(stderr, "  --mdamp=:      set the mixing fraction for the new solution in the MDIIS solver, default %g\n", (double) m->mdiis->damp);
  fprintf(stderr, "  --nbases=:     set the number of bases of the MDIIS solver, default %d\n", m->mdiis->nbases);
  fprintf(stderr, "  -s, --ies=:    set the parameter of the integral equation, default %g\n", (double) m->ies);
  fprintf(stderr, "  -N, --npt=:    set the number of grid points, default %d\n", m->npt);
  fprintf(stderr, "  -R, --rmax=:   set the radial cutoff, default %g\n", (double) m->rmax);
  fprintf(stderr, "  -Y, --bmuref=: set the reference bmu, default %g\n", (double) m->bmuref);
  fprintf(stderr, "  -8, --crmax=:  set the magnitude of c(r), default %g\n", (double) m->crmax);
  fprintf(stderr, "  -v:            be verbose, -vv to be more verbose, etc.\n");
  fprintf(stderr, "  -h, --help:    display this message\n");
  exit(1);
}



/* compute dependent variables */
__inline static void model_compute(model_t *m)
{
  m->beta = 1 / m->temp;
  m->rhomax = m->rho;
  m->nrho = (int) (m->rho / m->drho + 0.5);
  m->hsr = ( m->pottype == POTTYPE_HS
         && (m->xitype == XITYPE_R || m->lamtype == LAMTYPE_R) );

  if ( m->ietype == IETYPE_PY
    || m->ietype == IETYPE_HNC
    || m->ietype == IETYPE_BS ) {
    m->ies = 0;
  }

  if ( m->sctype != SCTYPE_NONE
   && !(m->ietype == IETYPE_IR
     || m->ietype == IETYPE_SQR
     || m->ietype == IETYPE_HC) ) {
    fprintf(stderr, "ie type %s is not self-consistent\n",
      sctypes[m->sctype]);
    exit(1);
  }
}



/* load settings from the configuration file `fn' */
__inline static int model_load(model_t *m, const char *fn)
{
  FILE *fp;
  char buf[800], *p, *key, *val;
  int inpar;

  if ( (fp = fopen(fn, "r")) == NULL ) {
    fprintf(stderr, "cannot load %s\n", fn);
    return -1;
  }

  while ( fgets(buf, sizeof buf, fp) ) {
    strstrip(buf); /* remove trailing spaces */
    if ( buf[0] == '\0' || buf[0] == '#' ) continue;

    /* parse the line to a key and a value */
    /* find the end of the key */
    inpar = 0; /* within (...) */
    for ( p = buf; *p; p++ ) {
      if ( (!inpar && isspace(*p)) || *p == '=' ) {
        *p = '\0'; /* end the key part */
        break;
      }
      if ( !inpar && (*p == '(' || *p == '[') )
        inpar = 1; /* enter a parentheses block */
      else if ( inpar && (*p == ')' || *p == ']') )
        inpar = 0; /* leave a parentheses block */
      *p = (char) tolower(*p);
    }
    key = buf;

    /* find the beginning of the value */
    for ( p++; isspace(*p) || *p == '=' ; ) p++;
    val = p;
    for ( ; *p; p++ ) *p = (char) tolower(*p);

    if ( strcmpfuzzy(key, "D") == 0
      || strcmpfuzzy(key, "dim") == 0 ) {
      m->dim = atoi(val);
    } else if ( strcmpfuzzy(key, "rho") ) {
      m->rho = atof(val);
    } else if ( strcmpfuzzy(key, "T") == 0
             || strcmpfuzzy(key, "temp") == 0 ) {
      m->temp = atof(val);
    } else if ( strcmpfuzzy(key, "drho") == 0 ) {
      m->drho = atof(val);
    } else if ( strcmpfuzzy(key, "nxi") == 0 ) {
      m->nxi = atoi(val);
    } else if ( strcmpfuzzy(key, "xitype") == 0 ) {
      m->xitype = model_select(val, XITYPE_COUNT, xitypes);
    } else if ( strcmpfuzzy(key, "nlam") == 0 ) {
      m->nlam = atoi(val);
    } else if ( strcmpfuzzy(key, "lamtype") == 0 ) {
      m->lamtype = model_select(val, LAMTYPE_COUNT, lamtypes);
    } else if ( strcmpfuzzy(key, "bmuref") == 0 ) {
      m->bmuref = atof(val);
    } else if ( strcmpfuzzy(key, "pottype") == 0 ) {
      m->pottype = model_select(val, POTTYPE_COUNT, pottypes);
    } else if ( strcmpfuzzy(key, "closure") == 0
             || strcmpfuzzy(key, "ietype") == 0 ) {
      m->ietype = model_select(val, IETYPE_COUNT, ietypes);
    } else if ( strcmpfuzzy(key, "ies") == 0 ) {
      m->ies = atof(val);
    } else if ( strcmpfuzzy(key, "npt") == 0
             || strcmpfuzzy(key, "n-pts") == 0 ) {
      m->npt = atoi(val);
    } else if ( strcmpfuzzy(key, "rmax") == 0 ) {
      m->rmax = atoi(val);
    } else if ( strcmpfuzzy(key, "itmax") == 0 ) {
      m->itmax = atoi(val);
    } else if ( strcmpfuzzy(key, "tol") == 0 ) {
      m->tol = atof(val);
    } else if ( strcmpfuzzy(key, "solver") == 0 ) {
      m->solver = model_select(val, SOLVER_COUNT, solvers);
    } else if ( strcmpfuzzy(key, "Picard-damp") == 0 ) {
      m->picard->damp = atof(val);
    } else if ( strcmpfuzzy(key, "Picard-streakmax") == 0 ) {
      m->picard->streakmax = atoi(val);
    } else if ( strcmpfuzzy(key, "MDIIS-nbases") == 0 ) {
      m->mdiis->nbases = atoi(val);
    } else if ( strcmpfuzzy(key, "MDIIS-damp") == 0 ) {
      m->mdiis->damp = atof(val);
    } else if ( strcmpfuzzy(key, "MDIIS-streakmax") == 0 ) {
      m->mdiis->streakmax = atoi(val);
    } else if ( strcmpfuzzy(key, "crmax") == 0 ) {
      m->crmax = atof(val);
    } else if ( strcmpfuzzy(key, "fnref") == 0 ) {
      m->fnref = val;
    } else if ( strcmpfuzzy(key, "bslmax") == 0 ) {
      m->bslmax = atoi(val);
    } else if ( strcmpfuzzy(key, "fnbs") == 0 ) {
      m->fnbs = val;
    } else if ( strcmpfuzzy(key, "sctype") == 0 ) {
      m->sctype = model_select(val, SCTYPE_COUNT, sctypes);
    } else if ( strcmpfuzzy(key, "scdsmax") == 0 ) {
      m->scdsmax = atof(val);
    } else if ( strcmpfuzzy(key, "sctol") == 0 ) {
      m->sctol = atof(val);
    } else {
      fprintf(stderr, "Warning: unknown option %s = %s\n", key, val);
      getchar();
    }
  }

  fclose(fp);
  model_compute(m);

  return 0;
}



/* handle command line arguments */
__inline static void model_doargs(model_t *m, int argc, char **argv)
{
  int i, j, ch;
  char *p, *q;

  /* reset */
  model_default(m);

  /* set the program name */
  m->prog = argv[0];

  for ( i = 1; i < argc; i++ ) {
    /* it's an argument */
    if ( argv[i][0] != '-' ) {
      m->fncfg = argv[i];
      if ( model_load(m, m->fncfg) != 0 ) {
        fprintf(stderr, "failed to load %s\n", m->fncfg);
        model_help(m);
      }
      continue;
    }

    /* long argument, like --help */
    if ( argv[i][1] == '-' ) {
      /* try to parse the argment
         e.g., `--prog=aaa' is parsed to `--prog' and `aaa' */
      p = argv[i] + 2;
      /* let q point to the argument of the option */
      if ( (q = strchr(p, '=')) != NULL ) {
        *q++ = '\0';
      } else {
        q = NULL;
      }

      if ( strcmp(p, "dim") == 0 ) {
        m->dim = atoi(q);
      } else if ( strcmp(p, "rho") == 0 ) {
        m->rho = atof(q);
      } else if ( strcmp(p, "drho") == 0 ) {
        m->drho = atof(q);
      } else if ( strcmp(p, "nxi") == 0 ) {
        m->nxi = atoi(q);
      } else if ( strcmp(p, "nlam") == 0 ) {
        m->nlam = atoi(q);
      } else if ( strcmp(p, "lam") == 0 ) {
        m->lamtype = model_select(q, LAMTYPE_COUNT, lamtypes);
      } else if ( strcmp(p, "pot") == 0 ) {
        m->pottype = model_select(q, POTTYPE_COUNT, pottypes);
      } else if ( strcmp(p, "ie") == 0 ) {
        m->ietype = model_select(q, IETYPE_COUNT, ietypes);
      } else if ( strcmp(p, "sol") == 0 ) {
        m->solver = model_select(q, SOLVER_COUNT, solvers);
      } else if ( strcmp(p, "ies") == 0 ) {
        m->ies = atof(q);
      } else if ( strcmp(p, "npt") == 0 ) {
        m->npt = atoi(q);
      } else if ( strcmp(p, "rmax") == 0 ) {
        m->rmax = atof(q);
      } else if ( strcmpfuzzy(p, "tol") == 0 ) {
        m->tol = atof(q);
      } else if ( strcmpfuzzy(p, "pdamp") == 0 ) {
        m->picard->damp = atof(q);
      } else if ( strcmpfuzzy(p, "mdamp") == 0 ) {
        m->mdiis->damp = atof(q);
      } else if ( strcmpfuzzy(p, "nbases") == 0 ) {
        m->mdiis->nbases = atoi(q);
      } else if ( strcmp(p, "bmuref") == 0 ) {
        m->bmuref = atof(q);
      } else if ( strcmp(p, "crmax") == 0 ) {
        m->crmax = atof(q);
      } else if ( strcmp(p, "rep") == 0 ) {
        m->fnrep = q;
      } else if ( strcmp(p, "crtr") == 0 ) {
        m->fncrtr = q;
      } else if ( strcmp(p, "sc") == 0 ) {
        m->sctype = model_select(q, SCTYPE_COUNT, sctypes);
      } else if ( strcmp(p, "help") == 0 ) {
        model_help(m);
      } else {
        fprintf(stderr, "unknown option %s\n", argv[i]);
        model_help(m);
      }

      continue;
    }

    /* it is an option
     * loop over characters in the options
     * in this way, `-vo' is understood as `-v -o' */
    for ( j = 1; (ch = argv[i][j]) != '\0'; j++ ) {
      if ( strchr("oOrDTzxXlLPCSsNRY8", ch) != NULL ) {
        /* handle options that require an argument */
        q = p = argv[i] + j + 1;
        if ( *p != '\0' ) {
          /* the argument follows immediately after the option
           * e.g., -oa.dat */
          q = p;
        } else if ( ++i < argc ) {
          /* the option and argument are separated by a space
           * then the argument belongs to the next argv[] element,
           * hence ++i
           * e.g., -o a.dat */
          q = argv[i];
        } else {
          fprintf(stderr, "-%c requires an argument!\n", ch);
          model_help(m);
        }

        if ( ch == 'o' ) {
          m->fncrtr = q;
        } else if ( ch == 'O' ) {
          m->fnrep = q;
        } else if ( ch == 'r' ) { /* override the density */
          m->rho = atof(q);
        } else if ( ch == 'D' ) { /* override the dimension */
          m->dim = atoi(q);
        } else if ( ch == 'T' ) { /* override the temperature */
          m->temp = atof(q);
        } else if ( ch == 'z' ) { /* override the density increment */
          m->drho = atof(q);
        } else if ( ch == 'x' ) { /* override the number of xi's */
          m->nxi = atoi(q);
        } else if ( ch == 'X' ) { /* override the xi type */
          m->xitype = model_select(q, XITYPE_COUNT, xitypes);
        } else if ( ch == 'l' ) { /* override the number of lambda's */
          m->nlam = atoi(q);
        } else if ( ch == 'L' ) { /* override the lambda type */
          m->lamtype = model_select(q, LAMTYPE_COUNT, lamtypes);
        } else if ( ch == 'Y' ) { /* override the reference bmu value */
          m->bmuref = atof(q);
        } else if ( ch == 'P' ) { /* override the potential */
          m->pottype = model_select(q, POTTYPE_COUNT, pottypes);
        } else if ( ch == 'C' ) { /* override the closure */
          m->ietype = model_select(q, IETYPE_COUNT, ietypes);
        } else if ( ch == 'S' ) { /* override the solver */
          m->solver = model_select(q, SOLVER_COUNT, solvers);
        } else if ( ch == 's' ) { /* override the parameter of integral equation */
          m->ies = atof(q);
        } else if ( ch == 'N' ) { /* override the number of FFT points */
          m->npt = atoi(q);
        } else if ( ch == 'R' ) { /* override the radial cutoff */
          m->rmax = atof(q);
        } else if ( ch == '8' ) { /* override the maximal value of c(r) */
          m->crmax = atof(q);
        }
        break; /* skip the rest of the characters in the option */
      } else if ( ch == 'v' ) {
        m->verbose++;
      } else if ( ch == 'h' ) {
        model_help(m);
      } else {
        fprintf(stderr, "unknown option %s, j %d, ch %c\n", argv[i], j, ch);
        model_help(m);
      }
    }
  }

  model_compute(m);
}





#include "ljeos.h" /* standard equation of state */





/* try to obtain the reference values */
__inline static void model_getref(model_t *m)
{
  if ( m->pottype == POTTYPE_LJ ) {
    double pref, Fref, muref;
    ljeos3d_get((double) m->rho, (double) m->temp, &pref, &Fref, &muref);
    m->bmuref = muref / m->temp;
  }
}



#endif /* MODEL_H__ */
