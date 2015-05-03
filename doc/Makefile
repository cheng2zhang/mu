prj=mu

gps=$(wildcard fig/*.gp)
figs=$(patsubst %.gp, %, $(gps))
pdffigs=$(patsubst %, %.pdf, $(figs))
epsfigs=$(patsubst %, %.eps, $(figs))

docpdf = $(prj).pdf

all: $(docpdf)

$(docpdf) : %.pdf: %.tex Makefile $(pdffigs)
	pdflatex $<
	bibtex $*
	pdflatex $<
	pdflatex $<

$(pdffigs): %.pdf: %.gp
	$(MAKE) -C fig

clean:
	$(RM) *.aux *.bbl *.blg *.log *.dvi *.out \
	      *Notes.bib *~
	rstrip.py

$(prj)doc.zip: $(prj).tex $(prj).pdf liquid.bib \
	       $(epsfigs) $(pdffigs) $(figgps) \
	       Makefile
	zip -r $@ $^

zip: $(prj)doc.zip

Bossman: zip
	rsync -avL $(prj)doc.zip \
	  cz1@129.109.88.204:/Bossman/cz1/mu/doc
