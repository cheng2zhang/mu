#!/usr/bin/env python



import os, sys, getopt



rhomin = 0      # minimal rho
rhomax = 1.0    # maximal rho
drho = 0.01
temp = 2
pottype = "HS"
ietype = "PY"
ies = 0.5
nlam = 100
lamtype = "f"
cmd0 = "mulamscan "
fnout = "mulamscan.dat"
fnscan = "mulam.dat"
mdamp = 0.5
nbases = 3
tol = 1e-10
verbose = 0



def usage():
  """ print usage and die """
  print sys.argv[0], "[Options]"
  print """
  Scan over rho to compute the chemical potential

  OPTIONS:
   --rho0:      minimal density
   -r, --rho:   maximal density
   -d, --drho:  density increment
   -T, --temp:  temperature
   --pot:       potential type
   -C, --ie:    closure
   -s, --ies:   parameter of the closure
   -l, --nlam:  number of points for scanning the global parameter
   -L, --lam:   type of the global parameter, f, r, h, c, or t
   --mdamp:     mixing fraction for the new solution for MDIIS
   --nbases:    number of bases for MDIIS
   --tol:       tolerance
   -o, --out:   file name of the output file of each muscan call
   -O, --save:  file name of the scan result
   -v:          verbose
  """
  exit(1)



def doargs():
  ''' Handle common parameters from command line options '''
  try:
    opts, args = getopt.gnu_getopt(sys.argv[1:],
        "r:T:C:d:l:L:o:s:O:hv",
         ["rho0=", "rho=", "drho=",
          "temp=", "pot=", "nlam=", "lam=",
          "mdamp=", "nbases=", "tol=",
          "ie=", "ies=", "out=", "save=", "help",])
  except getopt.GetoptError, err:
    # print help information and exit:
    print str(err) # will print something like "option -a not recognized"
    usage()

  global rhomin, rhomax, drho, pottype
  global nlam, lamtype, cmd0, fnout, fnscan, verbose
  global ietype, ies, mdamp, nbases, tol

  for o, a in opts:
    if o in ("--rho0",):
      rhomin = float(a)
    elif o in ("-r", "--rho",):
      rhomax = float(a)
    elif o in ("--pot",):
      pottype = a
    elif o in ("-C", "--ie",):
      ietype = a
    elif o in ("-s", "--ies",):
      ies = float(a)
    elif o in ("-d", "--drho"):
      drho = float(a)
    elif o in ("-l", "--nlam"):
      nlam = int(a)
    elif o in ("-L", "--lam"):
      lamtype = a
    elif o in ("--mdamp",):
      mdamp = float(a)
    elif o in ("--nbases",):
      nbases = int(a)
    elif o in ("--tol",):
      tol = float(a)
    elif o in ("-o", "--out"):
      fnout = a
    elif o in ("-O", "--save"):
      fnscan = a
    elif o in ("-v",):
      verbose += 1
    elif o in ("-h", "--help",):
      usage()
    else:
      print "don't know how to handle %s" % o
      exit(1)

  return 0



def rho_scan():
  ''' scanning over rho '''

  out = ""
  i = 1
  while 1:
    rho = i * drho
    i += 1

    if rho < rhomin + 0.5 * drho:
      continue

    if rho > rhomax + 0.5 * drho:
      break

    cmd = cmd0 + (
          " --pot=%s -l %s -L %s -r %s -O %s -C %s -s %s --mdamp=%s --nbases=%s --tol=%s" % (
          pottype, nlam, lamtype, rho, fnout, ietype, ies, mdamp, nbases, tol) )

    # run the command
    print "Running:", cmd
    os.system(cmd)

    # retrieve the result
    ln = open(fnout, "r").readlines()[-1]
    arr = ln.split()
    out += "%s" % rho
    for j in range(1, len(arr)):
      out += " %s" % arr[j]
    out += "\n"

  open(fnscan, "w").write(out)
  print "saved results to %s" % fnscan



if __name__ == "__main__":
  doargs()
  rho_scan()
