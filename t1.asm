	.data
	.align 0
	
#Strings para interação com o usuario
str_erro : .asciiz "Valor digitado invalido\n\n"
str_menu : .asciiz "Bem-vindo à calculadora\n"
str_opera: .asciiz "Digite:\n\n1-soma\n2-subtracao\n3-multiplicacao\n4-divisao\n5-potencia\n6-raiz quadrada\n7-Tabuada\n8-IMC\n9-Fatorial\n10-Fibonacci\n\n"
str_close: .asciiz "\n----Fechando programa----\n"

	.text
	.globl main
	
main:
	#Chamada do menu
	li $v0, 4
	la $a0, str_menu
	syscall
	j menu
	
erro:
	li $v0, 4
	la $a0, str_erro
	syscall
	
menu:
	#Impressao do menu e leitura da entrada da opcao do usuario
	li $v0, 4
	la $a0, str_opera
	syscall
	
	li $v0, 5
	syscall
	move $t1, $v0
	
	li $t9, 0
	ble $t1, $t9 erro
	li $t8, 11
	bge $t1, $t8 erro
	

	
fim:
	#Finaliza o programa, com mensagem
	li $v0, 4
	la $a0, str_close
	syscall
	
	li $v0, 10
	syscall