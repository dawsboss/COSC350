all: receive send build remove

receive: receiver.c
	gcc -o receive -g receiver.c
send: sender.c
	gcc -o send sender.c -g
build: buildsm.c
	gcc -o build buildsm.c -g
remove: removesm.c
	gcc -o remove removesm.c -g
clean:
	rm *.o send receive build remove
