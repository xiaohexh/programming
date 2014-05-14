LLDIR = src

all:
	for i in $(ALLDIR); do $(MAKE) -C $$i || exit 1;done

clean:
	for i in $(ALLDIR); do $(MAKE) -C $$i clean || exit 1;done
