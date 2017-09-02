
filefind: checkfiles.h filefind.c
	$(CC) $@.c -o $@

test: filefind
	./filefind /home/arikkert > result
	sort result > result.sort
	find /home/arikkert > result2
	sort result2 > result2.sort
	wc *.sort
	diff *.sort

clean:
	rm -f filefind
	rm -rf result result.sort
	rm -rf result2 result2.sort
