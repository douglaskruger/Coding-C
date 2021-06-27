# =============================================================================
#   Copyright © 2020 Skynet Consulting Ltd.
#
#   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
#   copied, or used as the basis for the manufacture or sale of equipment without
#   the express written permission of Skynet Consulting Ltd.
#   =============================================================================
#   This system was written and tested against Debian 9/10 Linux
#   =============================================================================
all:	zork	

zork: actors.o ballop.o clockr.o demons.o dgame.o  dinit.o dmain.o dso1.o dso2.o dso3.o dso4.o \
        dso5.o dso6.o dso7.o dsub.o dverb1.o dverb2.o gdt.o lightp.o local.o nobjs.o np.o np1.o \
        np2.o np3.o nrooms.o objcts.o rooms.o sobjs.o supp.o sverbs.o verbs.o villns.o
	gcc actors.o ballop.o clockr.o demons.o dgame.o dinit.o dmain.o dso1.o dso2.o dso3.o dso4.o \
	dso5.o dso6.o dso7.o dsub.o dverb1.o dverb2.o gdt.o lightp.o local.o nobjs.o np.o np1.o \
	np2.o np3.o nrooms.o objcts.o rooms.o sobjs.o supp.o sverbs.o verbs.o villns.o -o zork

actors.o: actors.c
	gcc -c actors.c -o actors.o

ballop.o: ballop.c
	gcc -c ballop.c -o ballop.o

clockr.o: clockr.c
	gcc -c clockr.c -o clockr.o

demons.o: demons.c
	gcc -c demons.c -o demons.o

dgame.o: dgame.c
	gcc -c dgame.c -o dgame.o

dinit.o: dinit.c
	gcc -c dinit.c -o dinit.o

dmain.o: dmain.c
	gcc -c dmain.c -o dmain.o

dso1.o: dso1.c
	gcc -c dso1.c -o dso1.o

dso2.o: dso2.c
	gcc -c dso2.c -o dso2.o

dso3.o: dso3.c
	gcc -c dso3.c -o dso3.o

dso4.o: dso4.c
	gcc -c dso4.c -o dso4.o

dso5.o: dso5.c
	gcc -c dso5.c -o dso5.o

dso6.o: dso6.c
	gcc -c dso6.c -o dso6.o

dso7.o: dso7.c
	gcc -c dso7.c -o dso7.o

dsub.o: dsub.c
	gcc -c dsub.c -o dsub.o

dverb1.o: dverb1.c
	gcc -c dverb1.c -o dverb1.o

dverb2.o: dverb2.c
	gcc -c dverb2.c -o dverb2.o

gdt.o: gdt.c
	gcc -c gdt.c -o gdt.o

lightp.o: lightp.c
	gcc -c lightp.c -o lightp.o

local.o: local.c
	gcc -c local.c -o local.o

nobjs.o: nobjs.c
	gcc -c nobjs.c -o nobjs.o

np.o: np.c
	gcc -c np.c -o np.o

np1.o: np1.c
	gcc -c np1.c -o np1.o

np2.o: np2.c
	gcc -c np2.c -o np2.o

np3.o: np3.c
	gcc -c np3.c -o np3.o

nrooms.o: nrooms.c
	gcc -c nrooms.c -o nrooms.o

objcts.o: objcts.c
	gcc -c objcts.c -o objcts.o

rooms.o: rooms.c
	gcc -c rooms.c -o rooms.o

sobjs.o: sobjs.c
	gcc -c sobjs.c -o sobjs.o

supp.o: supp.c
	gcc -c supp.c -o supp.o

sverbs.o: sverbs.c
	gcc -c sverbs.c -o sverbs.o

verbs.o: verbs.c
	gcc -c verbs.c -o verbs.o

villns.o: villns.c
	gcc -c villns.c -o villns.o

clean:
	rm -f actors.o ballop.o clockr.o demons.o dgame.o dinit.o dmain.o dso1.o \
		dso2.o dso3.o dso4.o dso5.o dso6.o dso7.o dsub.o dverb1.o dverb2.o \
		gdt.o lightp.o local.o nobjs.o np.o np1.o np2.o np3.o nrooms.o \
		objcts.o rooms.o sobjs.o supp.o sverbs.o verbs.o  villns.o 
