NAME=agdyne
ERLFLAGS=-smp -W1 -Werror -b beam
ERLC=erlc

%.beam: ./src/%.erl
	$(ERLC) $(ERLFLAGS) $<

all:
