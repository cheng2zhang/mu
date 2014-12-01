progdir = ../../../prog
mcdir = ../../mc
muhs = $(progdir)/muhs

figgp = Bscale.gp
figeps = Bscale.eps
figpdf = Bscale.pdf

data:
	gnuplot $(figgp)
	epstopdf $(figeps)

$(figpdf): $(figeps)
	epstopdf $<

$(figeps): $(figgp) $(data)
	gnuplot $<

