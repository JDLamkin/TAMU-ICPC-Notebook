icpc.h:
	echo '#include <../Notebook/Header_Large.cpp>' > $@
	ls ../Notebook/*/*.cpp   | sed -e 's/^/#include </' | sed -e 's/$$/>/' >> $@
	ls ../Notebook/*/*/*.cpp | sed -e 's/^/#include </' | sed -e 's/$$/>/' >> $@
