section .data

segment .text
	global _start
_start:
	pop eax	;extraer el contador de argumentos
	pop ebx	;extraer nombre del programa (el puntero)
	argumentos:
		pop ecx		;vamos extrayendo los argumentos
		test ecx,ecx	;comprobamos si llegamos al NULL
		jnz argumentos
	entorno:
		pop edx		;vamos extrayendo las variables
		test edx,edx	;comprobamos si llegamos al NULL
		jnz entorno
