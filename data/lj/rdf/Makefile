progdir = ../../../prog
mcdir = ../../mc
muhs = $(progdir)/muhs

figgp = rdf.gp
figeps = rdf.eps
figpdf = rdf.pdf

data:
	gnuplot $(figgp)
	epstopdf $(figeps)

syncin:
	rsync -avz $(ipo):lwork/mu/mc/test2/*rdf*.dat .

$(figpdf): $(figeps)
	epstopdf $<

$(figeps): $(figgp) $(data)
	gnuplot $<


