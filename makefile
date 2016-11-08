#Carpetas del proyecto

SOURCE_FOLDER=src
BUILD_FOLDER=build
TEMPORAL_FOLDER=tmp
INSTALL_FOLDER=/usr/bin
MAN=man/en
MAN_PAGES=/usr/share/man/man1
MAN_ES=man/es
MAN_PAGES_ES=/usr/share/man/es/man1
VERSION=0.2

#################################
#Opciones de compilacón
#################################
#Optimizacion: -O0 baja, -O1 normal, -O2 optimizado, -O3 alta
#Muestra todos los Warnings
#Compila en el Standard C11
CFLAGS=-O3 -Wall -std=c11

#LINK
LINK= -lz

#Descomentar para debug
#DEBUG=-g

##################################
#Reglas

.PHONY:	all c.o clean folders install uninstall reinstall
all: folders c.o $(TEMPORAL_FOLDER) $(BUILD_FOLDER)
	gcc $(TEMPORAL_FOLDER)/** -o $(BUILD_FOLDER)/emp $(CFLAGS) $(DEBUG) $(LINK)

c.o:
	gcc -c $(SOURCE_FOLDER)/main.c -o $(TEMPORAL_FOLDER)/main.o $(CFLAGS) $(DEBUG) $(LINK)
	gcc -c $(SOURCE_FOLDER)/headers.c -o $(TEMPORAL_FOLDER)/headers.o $(CFLAGS) $(DEBUG) $(LINK)
	gcc -c $(SOURCE_FOLDER)/oper.c -o $(TEMPORAL_FOLDER)/oper.o $(CFLAGS) $(DEBUG) $(LINK)
	gcc -c $(SOURCE_FOLDER)/args.c -o $(TEMPORAL_FOLDER)/args.o $(CFLAGS) $(DEBUG) $(LINK)
	gcc -c $(SOURCE_FOLDER)/error.c -o $(TEMPORAL_FOLDER)/error.o $(CFLAGS) $(DEBUG) $(LINK)

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
	@./config/magic ins

uninstall: $(INSTALL_FOLDER)/emp
	rm $(INSTALL_FOLDER)/emp
	rm $(MAN_PAGES)/emp.1.gz
	rm $(MAN_PAGES_ES)/emp.1.gz
	@./config/magic uins

reinstall: uninstall install

comp_and_make_deb: all make_deb

make_deb:	$(BUILD_FOLDER)/emp $(MAN)/emp.1.gz $(MAN_ES)/emp.1.gz
	@./config/make_deb_package $(BUILD_FOLDER)/emp $(MAN)/emp.1.gz $(MAN_ES)/emp.1.gz $(VERSION)
