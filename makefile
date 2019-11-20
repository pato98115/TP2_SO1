TP1: build/main.o build/background_execution.o build/internal_commands.o build/batch_file.o build/IO_redirection.o
	gcc build/main.o build/background_execution.o build/internal_commands.o build/batch_file.o build/IO_redirection.o -o tp2
build/main.o: 
	gcc -c -Iinc src/main.c -o build/main.o
build/background_execution.o: 
	gcc -c -Iinc src/background_execution.c -o build/background_execution.o
build/internal_commands.o: 
	gcc -c -Iinc src/internal_commands.c -o build/internal_commands.o
build/batch_file.o:
	gcc -c -Iinc src/batch_file.c -o build/batch_file.o
build/IO_redirection.o: 
	gcc -c -Iinc src/IO_redirection.c -o build/IO_redirection.o
clean:
	rm -f tp2 *.o