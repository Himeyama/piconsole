PROGRAM = piconsole
SOURCE_CODE = main.cpp

$(PROGRAM): $(SOURCE_CODE)
	g++ $(SOURCE_CODE) -std=c++11 -O2 `pkg-config opencv --cflags --libs` -o $(PROGRAM)

install: $(PROGRAM)
	install -s $(PROGRAM) /usr/bin/$(PROGRAM)