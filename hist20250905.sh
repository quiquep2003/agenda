u0_a349@termux:~/$ cs agenda/
README.md  agenda099.c  hist20250826.sh
agenda     gnd2         tex
u0_a349@termux:~/agenda/$ ./agenda

* Agenda de Contactos *
Salir.................: 0
Buscar................: 1
Listar................: 2
Nuevo.................: 3
Borrar................: 4
Opcion................: 3
Ingrese el nombre, un espacio y
el telefono de contacto con guionesjuan carlos 15-3432-2424

* Agenda de Contactos *
Salir.................: 0
Buscar................: 1
Listar................: 2
Nuevo.................: 3
Borrar................: 4
Opcion................: 1
Ingrese un nombre a buscar: juan
40 juan carlos 15-3432-2424

* Agenda de Contactos *
Salir.................: 0
Buscar................: 1
Listar................: 2
Nuevo.................: 3
Borrar................: 4
Opcion................: 1
Ingrese un nombre a buscar: carlos
13 carlos 15-3043-9081

* Agenda de Contactos *
Salir.................: 0
Buscar................: 1
Listar................: 2
Nuevo.................: 3
Borrar................: 4
Opcion................: 0
Salimos!
u0_a349@termux:~/agenda/$ ls
README.md  agenda099.c  hist20250826.sh
agenda     gnd2         tex
u0_a349@termux:~/agenda/$ nano agenda099.cu0_a349@termux:~/agenda/$ git status
On branch master
Your branch is up to date with 'origin/master'.

Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
        modified:   gnd2

no changes added to commit (use "git add" and/or "git commit -a")
u0_a349@termux:~/agenda/$ git add gnd2
u0_a349@termux:~/agenda/$ git status
On branch master
Your branch is up to date with 'origin/master'.

Changes to be committed:
  (use "git restore --staged <file>..." to unstage)
        modified:   gnd2

u0_a349@termux:~/agenda/$ git restore --staged gnd2
u0_a349@termux:~/agenda/$ git status      On branch master
Your branch is up to date with 'origin/master'.

Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
        modified:   gnd2

no changes added to commit (use "git add" and/or "git commit -a")
u0_a349@termux:~/agenda/$ git restore gnd2u0_a349@termux:~/agenda/$ git status      On branch master
Your branch is up to date with 'origin/master'.

nothing to commit, working tree clean
u0_a349@termux:~/agenda/$ ls
README.md  agenda099.c  hist20250826.sh
agenda     gnd2         tex
u0_a349@termux:~/agenda/$ nano tex
u0_a349@termux:~/agenda/$

