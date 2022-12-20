## Implementacion de Forward Checking para Examination Timetabling Problem

# Contexto:
	
	Como parte de la evaluacion del ramo de Inteligencia Artificial, habia que desarrollar un proyecto que culminara en la implementacion de una tecnica Completa/Incompleta para un problema en particular, en mi caso se me asignó la tecnica completa Forward Checking para ETP, sin heuristicas, los detalles de la implementacion se encuentran en el informe, este codigo fue realizado el año 2020 y no sufrido modificaciones desde entonces, los detalles de su implementacion se encuentran en el informe, este tiene una fecha distinta porque se edito para borrar informacion confidencial.

------------------------------------------------------

Consideraciones:

- Para la correcta ejecucion del programa, los archivos .stu y .exm deben estar ubicados en la carpeta Input, ademas estos no deben contener lineas vacias.
	- Si bien hasta el momento esto ultimo no produce problemas de ejecucion, si produce problemas en la logica, puesto que añade un nuevo nodo, aumentando el tiempo de ejecucion y afectando el calculo de timeslots y penalty asociado.
	- Los resultados seran ubicados en la carpeta Output.
		- Si se desea volver a ejecutar el codigo, asegurarse de eliminar los archivos .sol .res .pen puesto que el codigo realiza appends. Por tiempo y poca familiaridad con c++ no puede hacer el clean.
	- Si las carpetas en cuestion no existen o fueron eliminadas, es necesario crearlas para evitar problemas
- Las pruebas en el archivo .stu deben estar ordenadas ascendentemente para cada alumno
	- Ej: s01 4
		 s01 5
		 s03 2
	- La razon es porque dado los inputs provistos siempre estaban ordenados, por lo que la logica para determinar cuando hay conflictos entre examenes esta basada en que se añadiran las pruebas en orden para cada alumno.
- La implementacion registra las soluciones solo en caso de que estas mejoren la cantidad de timeslots o en su defecto el penalty (Cuando la cantidad de timeslots encontrada es igual al mejor valor actual de la iteracion)
	- Si se quisiera verificar que el codigo pasa por todas las soluciones, habria que comentar en la funcion eval las llamadas a la funcion save_sol y añadirla posterior al if else, para que registre todas las soluciones factibles que ha encontrado
	- Esta decision es para reducir el tiempo de ejecucion y al mismo tiempo identificar las mejoras sobre las soluciones, puesto que la ultima entrada siempre va a ser la mejor que encontro el algoritmo en su ejecucion
		- Notar que en caso de que el penalty no se pueda mejorar, no registrara soluciones que tengan el mismo valor.
- No me he detenido a averiguarlo, pero si el .stu hace referencias a pruebas que no estan en el .exm deberia producirse un segfault
	- Se me vino a la mente porque pense podar un input para ver si terminaba la ejecucion en un algun input pequeño, onda, el .exm tiene 4 pruebas y en el .stu hay un estudiante que debe rendir la prueba que no esta en ese range (5 por ej).
- Los timeslot empiezan desde el 1


How to

- Para la compilacion del codigo fuente ingresar en la consola el comando make
	-Para la limpieza del ejecutable ingresar el comando make clean

- Una vez compilado, el programa inicia de la siguiente manera:
	
	./ETP \<instancia\>

			\<instancia\> corresponde al nombre sin extension de los archivos .stu y .exm ubicados en la carpeta Input


	- Ej: ./ETP ejemplo

