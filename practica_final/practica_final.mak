# Autor: David Carrasco Chicharro
# Asignatura: Metodología de la Programación
# Trabajo: Practica final
# Archivo: practica_final.mak
# Ejecución: make -f practica_final.mak

all : bin/vectores bin/skyline bin/montar bin/matrices_dispersas bin/principal


bin/vectores : obj/vectores.o obj/vectores_funciones.o
	g++ $^ -o $@

bin/skyline : obj/skyline.o obj/skyline_funciones.o
	g++ $^ -o $@

bin/montar : obj/montar.o obj/montar_funciones.o
	g++ $^ -o $@

bin/matrices_dispersas : obj/matrices_dispersas.o obj/matrices_dispersas_funciones.o
	g++ $^ -o $@

bin/principal : obj/principal.o obj/principal_funciones.o
	g++ $^ -o $@

obj/vectores.o : src/vectores.cpp include/vectores_funciones.h
	g++ -c $< -o $@ -Iinclude

obj/vectores_funciones.o : src/vectores_funciones.cpp include/vectores_funciones.h
	g++ -c $< -o $@ -Iinclude

obj/skyline.o : src/skyline.cpp include/skyline_funciones.h
	g++ -c $< -o $@ -Iinclude

obj/skyline_funciones.o : src/skyline_funciones.cpp include/skyline_funciones.h
	g++ -c $< -o $@ -Iinclude

obj/montar.o : src/montar.cpp include/montar_funciones.h
	g++ -c $< -o $@ -Iinclude

obj/montar_funciones.o : src/montar_funciones.cpp include/montar_funciones.h
	g++ -c $< -o $@ -Iinclude


obj/matrices_dispersas.o : src/matrices_dispersas.cpp include/matrices_dispersas_funciones.h
	g++ -c $< -o $@ -Iinclude

obj/matrices_dispersas_funciones.o : src/matrices_dispersas_funciones.cpp include/matrices_dispersas_funciones.h
	g++ -c $< -o $@ -Iinclude

obj/principal.o : src/principal.cpp include/principal_funciones.h
	g++ -c $< -o $@ -Iinclude

obj/principal_funciones.o : src/principal_funciones.cpp include/principal_funciones.h
	g++ -c $< -o $@ -Iinclude


clean :
	@echo Limpiando...
	rm obj/*.o

mrproper : clean
	find ./bin ! -name *.txt -type f -delete