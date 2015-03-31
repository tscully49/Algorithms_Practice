
ddag: driver.c list.c parser.c dfs.c header.h
	gcc -D DDAG driver.c list.c parser.c dfs.c -o ddag
dag: driver.c list.c parser.c dfs.c header.h
	gcc -D DAG driver.c list.c parser.c dfs.c -o dag
dcomponents: driver.c list.c parser.c components.c dfs.c r_parser.c str.c header.h
	gcc -D DCOMPONENTS driver.c list.c parser.c components.c dfs.c r_parser.c str.c -o dcomponents
components: driver.c list.c parser.c components.c dfs.c r_parser.c str.c header.h
	gcc -D COMPONENTS driver.c list.c parser.c components.c dfs.c r_parser.c str.c -o components
clean:
	rm -f *.o ddag dag dcomponents components