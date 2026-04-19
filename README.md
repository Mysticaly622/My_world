# My_world

## FR

### Objectif
My_world est un projet C de visualisation et d'edition de terrain isometrique avec CSFML. L'application permet de manipuler une grille d'altitudes, d'interagir avec la camera et de sauvegarder/restaurer l'etat de la carte.

### Fonctionnalites
- Rendu isometrique d'une grille de tuiles.
- Selection de points et edition locale des hauteurs.
- Deplacement, rotation et zoom camera.
- Gestion du niveau de mer.
- Sauvegarde et rechargement de cartes `.legend`.

### Architecture
- `src/`: logique applicative, rendu, gestion des evenements, persistence.
- `include/`: structures, macros et interfaces publiques.
- `assets/`: ressources runtime (textures, audio).
- `save/`: exemples de sauvegardes et sorties de sauvegarde.
- `tests/`: tests unitaires C sans dependance externe.

### Build
Compilation principale:
```sh
make
```

### Execution
Lancer l'application:
```sh
./my_world
```
Charger une sauvegarde:
```sh
./my_world save/canyon_100x100.legend
```

### Tests
Commande unique demandee (build tests instrumentes + execution + coverage):
```sh
make test-run
```
Le coverage est affiche en mode texte via `gcovr` et filtre sur les sources du projet (`src/`, hors `tests/`).

### Limites
- Le rendu depend de CSFML et d'un environnement graphique disponible.
- Les tests unitaires couvrent prioritairement des helpers purs/simples.
- La qualite du rapport de coverage depend de la disponibilite de `gcovr` et d'un binaire gcov compatible.

### Licence
Ce projet est distribue sous licence Apache 2.0. Voir `LICENSE`.

---

## EN

### Goal
My_world is a C project for isometric terrain visualization and editing using CSFML. The application lets you manipulate a height map, interact with the camera, and save/restore map state.

### Features
- Isometric tile grid rendering.
- Point selection and local height editing.
- Camera movement, rotation, and zoom.
- Sea level adjustment.
- Save and reload `.legend` map files.

### Architecture
- `src/`: application logic, rendering, event handling, persistence.
- `include/`: public interfaces, structures, and macros.
- `assets/`: runtime resources (textures, audio).
- `save/`: sample saves and generated save files.
- `tests/`: external-dependency-free C unit tests.

### Build
Main build:
```sh
make
```

### Run
Start the application:
```sh
./my_world
```
Load a save file:
```sh
./my_world save/canyon_100x100.legend
```

### Tests
Single required command (instrumented test build + execution + coverage):
```sh
make test-run
```
Coverage is printed in text mode with `gcovr`, filtered to project sources (`src/`, excluding `tests/`).

### Limits
- Rendering requires CSFML and an available graphical environment.
- Unit tests currently focus on simple/pure helper routines.
- Coverage output quality depends on `gcovr` and a compatible gcov executable.

### License
This project is licensed under Apache 2.0. See `LICENSE`.
