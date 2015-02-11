progs=mc mc1 gmc

all: $(progs)

$(progs): %: %.c zcom.h
	icc -Wall -Wremarks $< -o $@

remote = cz1@129.109.88.204

Bossman: clean
	rsync -avLz *.[ch] $(remote):lwork/mu/mc

clean:
	find . -name "*~" | xargs rm -f
	rm -rf bin obj a.out $(progs) *.dat
	rstrip.py -Rlv

