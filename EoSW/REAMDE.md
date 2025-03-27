# TFE 2025 - Logique et Programmation

Le TFE 2025 de Logique et Programmation consiste en la réalisation d'un programme intégré de gestion d'une liste d'objets. Ces objets sont constitués au minimum de 3 données. Ex: si vous souhaitez gérer une liste de poneys, vous pouvez stocker leurs nom, couleur et âge.

Ce programme devra comporter au moins 5 options, accessibles depuis un menu:

* **Ajouter une entrée**: il s'agit ici d'ajouter un objet à la fin de la liste
* **Rechercher une entrée**: il s'agit ici de rechercher un objet. Vous devez laisser à l'utilisateur la possibilité de rechercher sur deux critères (mais pas nécessairement en même temps). La recherche ne doit pas tenir compte de la casse.
* **Lister les entrées**: il s'agit ici d'afficher simplement la liste de tous les objets et des données qui les concernent. Astuce: prévoyez que l'écran va défiler, pensez par exemple à afficher les objets par groupes de N objets puis à demander l'appui sur une touche pour continuer la liste
* **Mettre à jour une entrée**: l'utilisateur effectue d'abord une recherche puis peut modifier une donnée dans l'entrée trouvée
* **Effacer une entrée**: l'utilisateur est invité à entrer un critère pour déterminer quel objet sera supprimé. L'objet en question est ensuite retiré du fichier, éventuellement après confirmation

Quelques demandes supplémentaires:

* Les données placées dans le fichier sont des données structurées (vous devez donc utiliser le mot-clé `struct` en C). Le type doit être défini avec `typedef`.
* Le fichier est géré comme un fichier à accès direct: ouverture avec `rb+` et/ou `wb+`
* Il vous est demandé d'utiliser un index en mémoire. Un index est un tableau comprenant deux colonnes: une des colonnes est une copie de la clé primaire, l'autre est une référence à la position de l'enregistrement dans le tableau. Cet index sera utilisé notamment pour accélérer les recherches.
* le menu des options du programme doit boucler: après chaque action, l'utilisateur est ramené au menu. Bien entendu, cela implique que le menu comporte une option pour quitter le programme
* Au démarrage du programme, si le fichier de données n'existe pas, il doit être créé. S'il existe, il ne doit pas être écrasé.
Dans tout le programme, il ne faut utiliser aucune variable globale
* Le fichier est ouvert une seule fois au démarrage du programme et fermé une seule fois à la fermeture du programme
* Chaque fonctionnalité du programme est implantée sous forme d'une fonction
* Astuce: utilisez la fonction qui permet de rechercher un objet à la fois pour afficher les informations d'un objet et trouver un objet à supprimer ou mettre à jour. Dans ce cas, votre fonction devrait renvoyer la position de l'objet dans le fichier

Votre programme doit être strictement personnel, il est bien sûr interdit de recopier la moindre ligne de code d'un camarade (ou d'Internet, ou de quelqu'un d'autre de manière générale). Par contre, n'hésitez pas à vous entraider !!

# EoSW -  Logic and Programming

The 2025 TFE in Logic and Programming involves creating an integrated program to manage a list of objects. These objects must consist of at least 3 data fields. For example, if you want to manage a list of ponies, you could store their name, color, and age.

This program must include at least 5 options, accessible through a menu:

* **Add an entry**: This allows adding an object to the end of the list.
* **Search for an entry**: This allows searching for an object. The user must be able to search using two criteria (but not necessarily simultaneously). The search should be case-insensitive.
* **List entries**: This displays the list of all objects and their associated data. Tip: Consider that the screen will scroll; for example, display objects in groups of N and prompt the user to press a key to continue.
* **Update an entry**: The user first performs a search, then can modify a data field in the found entry.
* **Delete an entry**: The user is prompted to enter a criterion to determine which object will be deleted. The specified object is then removed from the file, possibly after confirmation.

Additional requirements:

* The data stored in the file must be structured (you must use the `struct` keyword in C). The type must be defined using `typedef`.
* The file must be managed as a direct-access file: opened with `rb+` and/or `wb+`.
* You are required to use an in-memory index. An index is a table with two columns: one column is a copy of the primary key, and the other is a reference to the record's position in the table. This index will be used to speed up searches.
* The program's menu must loop: after each action, the user is returned to the menu. Of course, this implies that the menu must include an option to exit the program.
* When the program starts, if the data file does not exist, it must be created. If it exists, it must not be overwritten.
* Throughout the program, no global variables should be used.
* The file must be opened only once at the start of the program and closed only once at the end of the program.
* Each program feature must be implemented as a function.
* Tip: Use the function that searches for an object both to display an object's information and to find an object to delete or update. In this case, your function should return the object's position in the file.

Your program must be strictly personal; it is, of course, forbidden to copy any line of code from a classmate (or from the Internet, or anyone else in general). However, feel free to help each other!