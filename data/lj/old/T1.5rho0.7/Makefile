progdir = ../../../prog
mcdir = ../../mc
muhs = $(progdir)/muhs

tp = 1.5
rho = 0.7
lam = -1.167854
fnrdf = rdfT$(tp)rho$(rho)n2048.dat
fnpmf = pmfT$(tp)rho$(rho)n256.dat
gropts = --grmin=0.3 --rcore=1.3 --sdr=0 --bmuref=-0.4006
figgp = ljBrT$(tp)rho$(rho).gp
figeps = ljBrT$(tp)rho$(rho).eps
figpdf = ljBrT$(tp)rho$(rho).pdf

data: syncin
	$(MAKE) -C $(progdir)
	$(muhs) --py -T$(tp) --rho=$(rho) --drho=$(rho) --lj -v --crtr=crtrpy.dat
	$(muhs) --hnc -T$(tp) --rho=$(rho) --drho=$(rho) --lj -v --crtr=crtrhnc.dat
	$(muhs) -s$(lam) -T$(tp) --rho=$(rho) --drho=$(rho) --lj -v --crtr=crtrsqr.dat
	$(muhs) -T$(tp) --rho=$(rho) --lj -v --gr=$(fnrdf) $(gropts) --pmf=$(fnpmf) --Brout=Brout1.dat --crtr=crtr1.dat
	$(muhs) -T$(tp) --rho=$(rho) --lj -v --gr=$(fnrdf) $(gropts) --Brout=Brout2.dat --crtr=crtr2.dat
	gnuplot $(figgp)
	epstopdf $(figeps)

#./mc1 --rho=0.7 -T1.5 -n256 -01e6 -11e10 -A0.2

syncin:
	rsync -avz $(ipo):lwork/mu/mc/*T$(tp)rho$(rho)*.dat .

$(figpdf): $(figeps)
	epstopdf $<

$(figeps): $(figgp) $(data)
	gnuplot $<

