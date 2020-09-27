all: naufragos #tests reports
	
naufragos : main.o simulacao.o representacao_grafica.o funcao_grafica.o navio.o bote.o recife.o passageiro.o objeto.o utils.o barreiras.o
	gcc -lm -o naufragos main.o simulacao.o representacao_grafica.o funcao_grafica.o navio.o bote.o recife.o passageiro.o objeto.o utils.o barreiras.o `allegro-config --libs`

main.o : main.c simulacao.h
	gcc -ansi -pedantic -Wall -c main.c

simulacao.o : simulacao.c simulacao.h passageiro.h representacao_grafica.h barreiras.h
	gcc -ansi -pedantic -Wall -D_POSIX_C_SOURCE=199309L -c simulacao.c

representacao_grafica.o : representacao_grafica.c representacao_grafica.h representacao.h passageiro.h objeto.h
	gcc -ansi -pedantic -Wall -c representacao_grafica.c

funcao_grafica.o : funcao_grafica.c funcao_grafica.h passageiro.h objeto.h
	gcc -ansi -pedantic -Wall -c funcao_grafica.c
	
representacao_textual.o : representacao_textual.c representacao_textual.h representacao.h passageiro.h objeto.h
	gcc -ansi -pedantic -Wall -c representacao_textual.c

passageiro.o : passageiro.c passageiro.h objeto.h representacao.h utils.h barreiras.h
	gcc -ansi -pedantic -Wall -c passageiro.c

bote.o : bote.c bote.h passageiro.h objeto.h representacao.h utils.h
	gcc -ansi -pedantic -Wall -c bote.c
	
navio.o : navio.c navio.h passageiro.h objeto.h representacao.h utils.h barreiras.h
	gcc -ansi -pedantic -Wall -c navio.c
	
recife.o : recife.c recife.h objeto.h representacao.h utils.h
	gcc -ansi -pedantic -Wall -c recife.c

barreiras.o : barreiras.c barreiras.h representacao_grafica.h utils.h 
	gcc -ansi -pedantic -Wall -c barreiras.c
	
objeto.o : objeto.c objeto.h
	gcc -ansi -pedantic -Wall -c objeto.c

utils.o : utils.c utils.h
	gcc -ansi -pedantic -Wall -c utils.c


#tests : test/minunit.h test/testes.o simulacao.o representacao_textual.o navio.o bote.o recife.o passageiro.o funcao_grafica.o objeto.o utils.o
#	gcc -lm -o tests test/testes.o simulacao.o representacao_textual.o navio.o bote.o recife.o passageiro.o funcao_grafica.o objeto.o utils.o

#testes.o : test/testes.c test/minunit.h utils.h passageiro.h objeto.h simulacao.h representacao_textual.h
#	gcc -ansi -pedantic -Wall -c test/testes.c


#reports : test/relatorio.o test/estatistica.o navio.o bote.o recife.o passageiro.o simulacao.o representacao_textual.o funcao_grafica.o objeto.o utils.o
#	gcc -lm -o reports test/relatorio.o test/estatistica.o navio.o bote.o recife.o passageiro.o simulacao.o representacao_textual.o funcao_grafica.o objeto.o utils.o

#relatorio.o : test/relatorio.c utils.h
#	gcc -ansi -pedantic -Wall -c relatorio.c

#estatistica.o : test/estatistica.c test/estatistica.h
#	gcc -ansi -pedantic -Wall -c test/estatistica.c


.PHONY: clean
clean:
	rm *.o test/*.o -f

