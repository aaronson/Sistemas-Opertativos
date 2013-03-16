all: mt_cliente1 mt_cliente2 mt_server2

mt_cliente1: mt_cliente1.c
	gcc -g mt_cliente1.c -o mt_cliente1

mt_cliente2: mt_cliente2.c
	gcc -g mt_cliente2.c -o mt_cliente2
	
mt_server2: mt_server2.c
	gcc -g mt_server2.c -o mt_server2


clean:
	rm -f mt_cliente1 mt_cliente2 mt_server2
