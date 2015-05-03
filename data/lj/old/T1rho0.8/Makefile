progdir = ../../../prog
mcdir = ../../mc
muhs = $(progdir)/muhs

tp = 1
rho = 0.8
lam = 0.344063
#muref = -2.19927
#fnrdf = rdfT$(tp)rho$(rho)n864.dat
muref = -2.2728
fnrdf = rdfT$(tp)rho$(rho)n2048.dat
fngrdf = grdfT$(tp)rho$(rho)n2048.dat
fnpmf = pmfT$(tp)rho$(rho)n256.dat
opts = -R40.96
# we don't use sdr here
ggropts = --grmin=0.3 --rcore=1.3
gropts = --grmin=0.3 --rcore=1.3 --bmuref=$(muref)
figgp = ljBrT$(tp)rho$(rho).gp
figeps = ljBrT$(tp)rho$(rho).eps
figpdf = ljBrT$(tp)rho$(rho).pdf

data: syncin
	$(MAKE) -C $(progdir)
	$(muhs) $(opts) --py -T$(tp) --rho=$(rho) --drho=$(rho) --lj -v --crtr=crtrpy.dat
	$(muhs) $(opts) --hnc -T$(tp) --rho=$(rho) --drho=$(rho) --lj -v --crtr=crtrhnc.dat
	$(muhs) $(opts) -s$(lam) -T$(tp) --rho=$(rho) --drho=$(rho) --lj -v --crtr=crtrsqr.dat
	$(muhs) -T$(tp) --rho=$(rho) --lj -v --gr=$(fngrdf) $(ggropts) --pmf=$(fnpmf)
	$(muhs) -T$(tp) --rho=$(rho) --lj -v --gr=$(fngrdf) $(ggropts)
	$(muhs) -T$(tp) --rho=$(rho) --lj -v --gr=$(fnrdf) $(gropts) --pmf=$(fnpmf) --Brout=Brout1.dat --crtr=crtr1.dat
	$(muhs) -T$(tp) --rho=$(rho) --lj -v --gr=$(fnrdf) $(gropts) --Brout=Brout2.dat --crtr=crtr2.dat
	gnuplot $(figgp)
	epstopdf $(figeps)

syncin:
	rsync -avz $(ipo):lwork/mu/mc/*T$(tp)rho$(rho)n*.dat .

$(figpdf): $(figeps)
	epstopdf $<

$(figeps): $(figgp) $(data)
	gnuplot $<

