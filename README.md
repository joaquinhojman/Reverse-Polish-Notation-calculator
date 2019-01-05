# Reverse-Polish-Notation-calculator
Implementation of Reverse Polish Notation calculator in C

Este programa procesará la entrada estándar y la interpretará como un cálculo en notación polaca inversa, imprimiendo por salida estándar el resultado.

Operaciones

Todas las operaciones trabajarán con números enteros, y devolverán números enteros.

Las operaciones pueden ser: suma (+), resta (-), multiplicación (*), división (/), obtener la raíz (sqrt), obtener la potencia (^), obtener el logaritmo (log) y operador ternario (?).

La operación de suma debe agarrar los dos últimos elementos y sumar el último con el anterior: 5 10 + → 10 + 5 = 15

La operación de resta debe agarrar los dos últimos elementos y restar el último con el anterior: 5 10 - → 10 - 5 = 5

La operación de multiplicación debe agarrar los dos últimos elementos y multiplicar el último con el anterior: 5 10 * → 10 * 5 = 50.

La operación de división debe agarrar los dos últimos elementos y dividir (de forma entera) el último por el anterior: 5 10 / → 10 / 5 = 2, 3 10 / → 10 / 3 = 3. En caso de encontrarse con que el divisor es 0, se considerará como un error.

La operación de obtener la raíz agarra el último operando y obtiene la parte entera de la raíz de dicho operando: 5 10 sqrt → sqrt(10) = 3  En caso que el argumento sea negativo, se considerará como un error.

La operación para obtener la potencia debe agarrar los últimos dos elementos y elevar el último por el anterior: 5 10 ^ → 10^5 = 100000. En caso que el argumento del exponente sea negativo, se considerará como un error.

La operación de obtener el logaritmo agarra los últimos dos operandos, y calcular la parte entera del logaritmo del último operando, en base del penúltimo: 5 10 log → log_5 (10) = 1. En caso que la base sea un número menor o igual a 1, se considerará como un error.

La operación del operador ternario debe agarrar los últimos 3 elementos. En caso que el último operando sea distinto de 0, debe devolver el penúltimo, en caso de ser 0 debe devolver el antepenúltimo: 5 10 0 ? → (0? 10 : 5) = 5.

El programa principal es "dc.c".
