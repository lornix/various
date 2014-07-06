#
#
ASFLAGS=-ggdb3
#
AS=as
LD=ld
#
EXECS=rdtsc
#
.phony: all clean

all: $(EXECS)

%: %.s
	$(AS) $(ASFLAGS) $< -o $@.o
	$(LD) $@.o -o $@

clean:
	rm -f *.o $(EXECS)

