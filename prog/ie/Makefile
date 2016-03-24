deps = $(wildcard *.h)

csrcs = $(wildcard *.c)
progs = $(patsubst %.c, %, $(csrcs))

CC=icc -Wall -Wremarks

all: $(progs)

$(progs): % : %.c $(deps)
	$(CC) -DLDBL -DFFTW $< -o $@ -lfftw3l

gr: gr_fftw gr_gsl

gr_fftw: gr.c $(deps)
	$(CC) -DFFTW $< -o $@ -lfftw3

gr_gsl: gr.c $(deps)
	$(CC) -DDHT $< -o $@ -lgsl

remote = cz1@129.109.88.204
remoteBossman = $(remote):/Bossman/cz1/mu

Bossman: clean
	rsync -avLz *.[ch] *.py Makefile README.md $(remoteBossman)/prog/ie/

clean:
	find . -name "*~" | xargs rm -f
	rm -rf bin obj iemu*.dat a.out cr*.dat Br*.dat $(progs) \
		*.obj *.exe
	rstrip.py -Rlv

