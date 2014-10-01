NAME=agdyne
ERLFLAGS=-smp -W1 -Werror -b beam -o ./ebin/
ERLC=erlc

./ebin/%.beam: ./src/%.erl
	$(ERLC) $(ERLFLAGS) $<

all: ./ebin/agdyne_main.beam
