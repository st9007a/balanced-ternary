EXEC = b3k
TEST = ternary
SRC_TEST = test.c

CC ?= gcc
CFLAGS = -Wall -std=gnu99 -g

GIT_HOOKS := .git/hooks/applied
.PHONY: all
all: $(GIT_HOOKS) $(EXEC)

$(GIT_HOOKS):
	@scripts/install-git-hooks

OBJS = \
	b3k.o

deps := $(OBJS:%.o=.%.o.d)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(TEST): $(SRC_TEST) ternary.c ternary.h
	$(CC) $(CFLAGS) -o $@ $(SRC_TEST) $@.c

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ -MMD -MF .$@.d $<

check: $(EXEC)
	echo  27 | ./$^
	echo -27 | ./$^
	echo   9 | ./$^
	echo  -9 | ./$^

clean:
	$(RM) $(EXEC) $(OBJS) $(deps)

-include $(deps)
