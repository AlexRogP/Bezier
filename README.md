Voici le fichier `README.md` **complet**, optimisé et prêt à **copier-coller directement** dans ton dépôt GitHub :

---

````markdown
# 🧠 Bezier – Simplification d'images par courbes de Bézier

Projet académique réalisé dans le cadre du cours **MAP401** (Mathématiques assistées par ordinateur), à l’Université Grenoble Alpes (Licence 2 Mathématiques & Informatique).

---

## 🎯 Objectif

Extraire les contours d’images binaires, les simplifier via l’algorithme de **Douglas-Peucker**, et les approximer à l’aide de **courbes de Bézier** de degré 2 et 3.  
Les résultats sont exportés au format **EPS** pour une visualisation vectorielle.

---

## 📂 Structure du projet

| Fichier/Module                    | Description                                                      |
|----------------------------------|------------------------------------------------------------------|
| `image.c`, `geom2d.c`, `contours.c` | Traitement d’images, géométrie 2D, extraction de contours         |
| `simplification_contours.c`      | Simplification par segments                                      |
| `simplification_Bezier2.c`       | Simplification par courbes de Bézier degré 2                     |
| `simplification_Bezier3.c`       | Simplification par courbes de Bézier degré 3                     |
| `exemple_sequence_point.c`       | Structures de données pour les séquences de points               |
| `Makefile`                       | Compilation automatique de tous les modules                      |

---

## ⚙️ Compilation

Dans le répertoire du projet, exécuter :
```bash
make
````

---

## 🚀 Exécution

### 1. Extraction de contours

```bash
./extraction_contours image.pbm
```

Affiche le nombre de contours, de points et de segments.

---

 2. Sauvegarde des contours en EPS

```bash
./sauvegarde_contours image.pbm output.eps
```

Génère un fichier EPS contenant les contours extraits.

---

 3. Simplification par segments (Douglas-Peucker)

```bash
./simplification_contours image.pbm output.eps seuil
```

Génère une version simplifiée des contours.

---

 4. Approximation par Bézier de degré 2

```bash
./simplification_Bezier2 image.pbm output.eps seuil
```

---

### 5. Approximation par Bézier de degré 3

```bash
./simplification_Bezier3 image.pbm output.eps seuil
```

---

## 👥 Auteurs

* **Alexis Rognin-Picard**
* **Polina Kobzarenko**

Licence 2 Mathématiques & Informatique – Université Grenoble Alpes

---

## 📝 Licence

Projet académique – usage libre dans un contexte pédagogique.
Pour toute réutilisation externe, merci de citer les auteurs.

