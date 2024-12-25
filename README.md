# Script de Traitement des Données avec Bash et C

Ce projet contient un script Bash associé à un programme en C pour traiter des fichiers CSV contenant des données sur les stations et les consommateurs. Il automatise la gestion des fichiers, traite les données et génère des résultats triés dans une structure de répertoires organisée.

---

## Fonctionnalités

- **Validation des Entrées** :
  - Vérifie que le fichier CSV spécifié existe dans le répertoire `input/`.
  - Valide les paramètres passés au script.
- **Gestion des Répertoires** :
  - Crée automatiquement les répertoires nécessaires : `input`, `tmp`, `output`, `resultat`.
  - Archive les résultats précédents dans le répertoire `resultat`.
- **Traitement des Données** :
  - Filtre les données avec `awk` en fonction des paramètres spécifiés.
  - Exécute un programme en C pour un traitement avancé des données.
  - Enregistre les résultats triés dans le répertoire `output`.
- **Gestion des Erreurs** :
  - Gère les erreurs dans la compilation et l'exécution du programme en C.
  - Informe l'utilisateur des problèmes avec des messages clairs.

---

## Pré-requis

### Logiciels Nécessaires

- **Bash** : Pour exécuter le script.
- **awk** : Pour le prétraitement des données CSV.
- **gcc** : Pour compiler le programme en C.
- **make** : Pour gérer la compilation avec le Makefile.

### Structure des Répertoires

```
.
├── input/          # Répertoire pour les fichiers CSV d'entrée (fourni par l'utilisateur)
├── tmp/            # Répertoire pour les fichiers temporaires
├── output/         # Répertoire pour les résultats finaux triés
├── resultat/       # Répertoire pour archiver les anciens résultats
├── script.sh       # Script Bash principal
├── C/              # Répertoire contenant le programme en C et le Makefile
│   ├── main.c      # Fichier principal du programme en C
│   ├── avl_station.c # Implémentation de l'arbre AVL
│   ├── avl_station.h # Fichier d'en-tête pour l'arbre AVL
│   └── Makefile    # Fichier Makefile pour compiler le programme en C
```

---

## Installation

1. Clonez le dépôt :
   ```bash
   git clone https://github.com/<votre-utilisateur>/<nom-du-depot>.git
   cd <nom-du-depot>
   ```

2. Assurez-vous que les dépendances sont installées :
   ```bash
   sudo apt update
   sudo apt install gcc make
   ```

3. Placez votre fichier CSV dans le répertoire `input/`.

---

## Utilisation

Exécutez le script avec la commande suivante :
```bash
./script.sh <nom_fichier> <type_station> <type_consommateur> [identifiant_centrale]
```

### Arguments
- `<nom_fichier>` : Nom du fichier CSV à traiter (doit être situé dans le répertoire `input/`).
- `<type_station>` : Type de station à analyser (`hvb`, `hva`, `lv`).
- `<type_consommateur>` : Type de consommateur (`comp`, `indiv`, `all`).
- `[identifiant_centrale]` : (Optionnel) Identifiant spécifique de la centrale à analyser.

### Exemple
```bash
./script.sh data.csv hva comp 2
```

---

## Fonctionnement du Script

1. **Validation des Entrées** :
   - Vérifie que le fichier spécifié existe dans `input/`.
   - Crée les répertoires nécessaires.

2. **Prétraitement des Données** :
   - Utilise `awk` pour filtrer et nettoyer les données en fonction des paramètres.

3. **Compilation et Exécution du Programme C** :
   - Compile le programme C avec `make`.
   - Exécute le programme C pour un traitement avancé.

4. **Résultats** :
   - Les résultats intermédiaires sont enregistrés dans `tmp/resultat_intermediaire.txt`.
   - Les résultats finaux triés sont sauvegardés dans `output/`.

---

## Résultats

- **Fichier Intermédiaire** : Enregistré dans `tmp/resultat_intermediaire.txt`.
- **Fichier Final** : Sauvegardé dans `output/<type_station>_<type_consommateur>.csv`.

### Exemple de Résultat
```
output/hva_comp.csv
```

---

## Gestion des Erreurs

### Erreurs Courantes
1. **Fichier Manquant** :
   - Assurez-vous que le fichier existe dans le répertoire `input/`.
   - Message d'erreur :
     ```
     Erreur : Le fichier <nom_fichier> n'existe pas dans le dossier 'input'.
     ```

2. **Échec de la Compilation** :
   - Vérifiez les fichiers source du programme en C et le Makefile.
   - Assurez-vous que `gcc` et `make` sont installés.

3. **Problèmes d'Exécution** :
   - Validez le contenu et le format du fichier CSV d'entrée.

---

## Contribution

1. Forkez le dépôt.
2. Créez une nouvelle branche :
   ```bash
   git checkout -b feature/nouvelle-fonctionnalite
   ```
3. Commitez vos modifications :
   ```bash
   git commit -m "Ajout d'une nouvelle fonctionnalité"
   ```
4. Poussez vers votre branche :
   ```bash
   git push origin feature/nouvelle-fonctionnalite
   ```
5. Ouvrez une Pull Request.

---

