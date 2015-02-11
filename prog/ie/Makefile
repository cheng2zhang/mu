progs = muhs ieodfftw

all: $(progs)

muhs: muhs.c loadgr.h zcom.h fft.h slowdht.h fftx.h ieutil.h xdouble.h
	icc -Wall -Wremarks -DLDBL -DFFTW $< -o $@ -lfftw3l

ieodfftw: ievir.c loadgr.h zcom.h fft.h slowdht.h fftx.h ieutil.h xdouble.h
	icc -Wall -Wremarks -DLDBL -DFFTW $< -o $@ -lfftw3l

remote = cz1@129.109.88.204

Bossman: clean
	rsync -avLz *.[ch] $(remote):lwork/mu/mc

clean:
	find . -name "*~" | xargs rm -f
	make -C mc clean
	rm -rf bin obj iemu*.dat a.out cr*.dat Br*.dat $(progs)
	rstrip.py -Rlv

