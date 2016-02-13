segment .data			;Segmento de datos
cadena db 50 			;Cadena a almacenar
segment .text			;Segmento de codigo
	global _start		;punto de entrada al programa (usando con el enlazador id)
_start:				;Inicio del programa
	mov edx,50d 		;Longitud del bufer
	mov ecx,cadena		;Cadena al leer
	mov ebx,0		;Entrada estandar
	mov eax,3		;Numero de llamada al sistema sys_red
	int 0x80		;Interrupcion de llamadas al sistema del kernel de linux
	mov edx,50d		;Logngitud de cadena
	mov ecx,cadena		;Cadena a escribir
	mov ebx,1		;Salida estandar
	mov eax,4		;Numero de llamada al sitema sys_write
	int 0x80 		;Interrupcion de llamdas al sistema del kernel de linux
	mov eax,1		;NUmero de llamda al sistema sys_exit
	int 0x80		;Interrupcion de llamdas al sistema del kernel de lunux 
				;nasm -f elf -o nombre.o nombre.asm
				;ld nombredelejecutabel -o nombre.o
