main: Notebook-Files.pdf
	rm -f Notebook-Files.cpp Notebook-Files.ps File-List.txt

Notebook-Files.pdf: Notebook-Files.ps
	ps2pdf $<

Notebook-Files.ps: Notebook-Files.cpp
	vim $< -c "hardcopy > $@" -c q

Notebook-Files.cpp: File-List.txt
	(for f in $$(cat $<); do echo $$f; echo; cat $$f; printf "\n\n\n\n"; done) > $@

File-List.txt:
	find Notebook/ -type f | grep -v filler | grep -v a.out > $@

clean:
	rm -f Notebook-Files.* File-List.txt
