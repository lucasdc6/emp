#Carpetas del proyecto

SOURCE_FOLDER=src
BUILD_FOLDER=build
TEMPORAL_FOLDER=tmp
INSTALL_FOLDER=/usr/bin
MAN=man/en
MAN_PAGES=/usr/share/man/man1
MAN_ES=man/es
MAN_PAGES_ES=/usr/share/man/es/man1

#################################
#Opciones de compilacón
#################################
#Optimizacion: -O0 baja, -O1 normal, -O2 optimizado, -O3 alta
#Muestra todos los Warnings
#Compila en el Standard C99
CFLAGS=-O3 -Wall -std=c99

#Descomentar para debug
#DEBUG=-g

##################################
#Reglas

.PHONY:	all clean folders install uninstall reinstall
all: folders c.o $(TEMPORAL_FOLDER) $(BUILD_FOLDER)
	gcc $(TEMPORAL_FOLDER)/** -o $(BUILD_FOLDER)/emp $(CFLAGS) $(DEBUG)

c.o:
	gcc -c $(SOURCE_FOLDER)/main.c -o $(TEMPORAL_FOLDER)/main.o $(CFLAGS) $(DEBUG)
	gcc -c $(SOURCE_FOLDER)/headers.c -o $(TEMPORAL_FOLDER)/headers.o $(CFLAGS) $(DEBUG)
	gcc -c $(SOURCE_FOLDER)/oper.c -o $(TEMPORAL_FOLDER)/oper.o $(CFLAGS) $(DEBUG)
	gcc -c $(SOURCE_FOLDER)/args.c -o $(TEMPORAL_FOLDER)/args.o $(CFLAGS) $(DEBUG)
	gcc -c $(SOURCE_FOLDER)/error.c -o $(TEMPORAL_FOLDER)/error.o $(CFLAGS) $(DEBUG)

clean:
	rm -r $(TEMPORAL_FOLDER) $(BUILD_FOLDER)

folders:
	-mkdir $(TEMPORAL_FOLDER) $(BUILD_FOLDER)

bytes:
	@echo Bytes por archivo:
	@wc -c $(SOURCE_FOLDER)/** makefile

char:
	@echo Caracteres por archivo:
	@wc -m $(SOURCE_FOLDER)/** makefile

lines:
	@echo Lineas de codigo por archivo:
	@wc -l $(SOURCE_FOLDER)/** makefile

install: $(BUILD_FOLDER)/emp
	cp -p $(BUILD_FOLDER)/emp $(INSTALL_FOLDER)
	cp -p $(MAN)/emp.1.gz $(MAN_PAGES)
	cp -p $(MAN_ES)/emp.1.gz $(MAN_PAGES_ES)

uninstall: $(INSTALL_FOLDER)/emp
	rm $(INSTALL_FOLDER)/emp
	rm $(MAN_PAGES)/emp.1.gz
	rm $(MAN_PAGES_ES)/emp.1.gz

reinstall: uninstall install
