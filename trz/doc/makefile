#
# Ogolny makefile do obslugi dokumentow Latexowych
#
TEX  = $(wildcard [a-z]*.tex)
PS   = $(patsubst %.tex,%.ps,$(TEX))
PDF  = $(patsubst %.tex,%.pdf,$(TEX))

all:  pdf

pdf: $(PDF)

%.pdf: %.dvi
	dvipdf $*.dvi

%.dvi: %.tex
	latex $*.tex
	latex $*.tex	

# Tej opcji uzywamy przy wysylaniu paczki
clean:
	rm -f *~
	rm -f *.log
	rm -f *.aux
	rm -f *.dvi
	rm -f *.err
	rm -f *.inf

no_binaries: clean
	rm -f *.pdf
	rm -rf tmp
	rm -f *.css
	rm -f *.png
	rm -f *.html
