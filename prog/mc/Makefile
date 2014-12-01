progs=mc mc1 gmc ozgr

all: $(progs)

mc: mc.c zcom.h
	icc -Wall -Wremarks $< -o $@

mc1: mc1.c zcom.h
	icc -Wall -Wremarks $< -o $@

gmc: gmc.c zcom.h
	icc -Wall -Wremarks $< -o $@

deps=zcom.h ieutil.h xdouble.h fft.h fftx.h

ozgr: ozgr.c $(deps)
	icc -Wall -Wremarks -DFFTW $< -o $@ -lfftw3

ieodfftw: ievir.c $(deps)
	icc -Wall -Wremarks -DFFTW $< -o $@ -lfftw3

remote = cz1@129.109.88.204

Bossman: clean
	rsync -avLz *.[ch] $(remote):lwork/mu/mc

clean:
	find . -name "*~" | xargs rm -f
	rm -rf bin obj a.out $(progs) *.dat
	rstrip.py -Rlv

