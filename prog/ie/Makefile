deps = $(wildcard *.h)

csrcs = $(wildcard *.c)
progs = $(patsubst %.c, %, $(csrcs))

all: $(progs)

$(progs): % : %.c $(deps)
	icc -Wall -Wremarks -DLDBL -DFFTW $< -o $@ -lfftw3l

remote = cz1@129.109.88.204
remoteBossman = $(remote):/Bossman/cz1/mu

Bossman: clean
	rsync -avLz *.[ch] *.py Makefile README.md $(remoteBossman)/prog/ie/

clean:
	find . -name "*~" | xargs rm -f
	rm -rf bin obj iemu*.dat a.out cr*.dat Br*.dat $(progs) \
		*.obj *.exe
	rstrip.py -Rlv

