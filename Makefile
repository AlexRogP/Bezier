#############################################################################
# Fichier Makefile 
# UE MAP401 - DLST - UGA - 2024/2025
#############################################################################
# utilisation des variables internes $@ $< $^ $*
# $@ : correspond au nom de la cible
# $< : correspond au nom de la premiere dependance
# $^ : correspond � toutes les d�pendances
# $* : correspond au nom du fichier sans extension 
#       (dans les regles generiques uniquement)
#############################################################################
# information sur la regle executee avec la commande @echo
# (une commande commancant par @ n'est pas affichee a l'ecran)
#############################################################################


#############################################################################
# definition des variables locales
#############################################################################

# compilateur C
CC = clang

# chemin d'acces aux librairies (interfaces)
INCDIR = .

# chemin d'acces aux librairies (binaires)
LIBDIR = .

# options pour l'�dition des liens
LDOPTS = -L$(LIBDIR) -lm

# options pour la recherche des fichiers .o et .h
INCLUDEOPTS = -I$(INCDIR)

# options de compilation
COMPILOPTS = -g -Wall $(INCLUDEOPTS)

# liste des executables
EXECUTABLES = detection_contours_partie_1 detection_contours_partie_2 PBM_to_EPS extraction_contours sauvegarde_contours distance_point_segment simplification_contours simplification_bezier2 simplification_bezier3


#############################################################################
# definition des regles
#############################################################################

########################################################
# la règle par défaut
all : $(EXECUTABLES)

########################################################
# regle generique : 
#  remplace les regles de compilation separee de la forme
#	module.o : module.c module.h
#		$(CC) -c $(COMPILOPTS) module.c
%.o : %.c %.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module "$*
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

########################################################
# regles explicites de compilation separee de modules
# n'ayant pas de fichier .h ET/OU dependant d'autres modules
image.o : image.c image.h 
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module image"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

geom2d.o : geom2d.c geom2d.h 
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module geom2d"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

contours.o : contours.c contours.h image.h geom2d.h exemple_sequence_point.h bezier.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module contours"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

detection_contours_partie_1.o : detection_contours_partie_1.c contours.h image.h geom2d.h exemple_sequence_point.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module detection_contours_partie_1"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

exemple_sequence_point.o : exemple_sequence_point.c exemple_sequence_point.h image.h geom2d.h contours.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module exemple_sequence_point"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

detection_contours_partie_2.o : detection_contours_partie_2.c exemple_sequence_point.h contours.h image.h geom2d.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module detection_contours_partie_2"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

PBM_to_EPS.o : PBM_to_EPS.c exemple_sequence_point.h contours.h image.h geom2d.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module PBM_to_EPS"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

extraction_contours.o : extraction_contours.c exemple_sequence_point.h contours.h image.h geom2d.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module PBM_to_EPS"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

sauvegarde_contours.o : sauvegarde_contours.c exemple_sequence_point.h contours.h image.h geom2d.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module PBM_to_EPS"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

distance_point_segment.o : distance_point_segment.c exemple_sequence_point.h contours.h image.h geom2d.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module PBM_to_EPS"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

simplification_contours.o : simplification_contours.c exemple_sequence_point.h contours.h image.h geom2d.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module PBM_to_EPS"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

bezier.o : bezier.c bezier.h exemple_sequence_point.h contours.h image.h geom2d.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module PBM_to_EPS"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<


simplification_bezier2.o : simplification_bezier2.c bezier.h exemple_sequence_point.h contours.h image.h geom2d.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module PBM_to_EPS"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

simplification_bezier3.o : simplification_bezier3.c bezier.h exemple_sequence_point.h contours.h image.h geom2d.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module PBM_to_EPS"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<
		
		
		
########################################################
# regles explicites de creation des executables

detection_contours_partie_1 : detection_contours_partie_1.o contours.o image.o geom2d.o exemple_sequence_point.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

detection_contours_partie_2 : detection_contours_partie_2.o exemple_sequence_point.o image.o geom2d.o contours.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

PBM_to_EPS : PBM_to_EPS.o exemple_sequence_point.o image.o geom2d.o contours.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

extraction_contours : extraction_contours.o exemple_sequence_point.o image.o geom2d.o contours.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

sauvegarde_contours : sauvegarde_contours.o exemple_sequence_point.o image.o geom2d.o contours.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

distance_point_segment : distance_point_segment.o exemple_sequence_point.o image.o geom2d.o contours.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

simplification_contours : simplification_contours.o exemple_sequence_point.o image.o geom2d.o contours.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

simplification_bezier2 : simplification_bezier2.o bezier.o exemple_sequence_point.o image.o geom2d.o contours.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

simplification_bezier3 : simplification_bezier3.o bezier.o exemple_sequence_point.o image.o geom2d.o contours.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@



# regle pour "nettoyer" le r�pertoire
clean:
	rm -fR $(EXECUTABLES) *.o 
