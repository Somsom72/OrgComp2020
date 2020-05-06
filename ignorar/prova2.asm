# Autoria: Luca Maciel Alexander, nUsp: 11219175
# "strncmp" em MIPS, prova 2

	.data
	.align 0
	
pergunta_inicial: .asciiz "Digite a string1, string2, e um inteiro (separados por ENTER).\n"
resposta: .asciiz "Resposta do Strncmp: "
linha: .asciiz "\n"
string1: .space 200
string2: .space 200
	
	.text
	.globl main
	
main:										# codigo principal

	li $v0, 4
	la $a0, pergunta_inicial
	syscall									# imprime prompt inicial
	
	li $v0, 8
	la $a0, string1
	li $a1, 200
	syscall									# captura a string1 em $s0
	la $s0, string1
	
	li $v0, 8
	la $a0, string2
	li $a1, 200
	syscall									# captura a string2 em $s1
	la $s1, string2
	
	li $v0, 5
	syscall									# captura o numero em $s2
	move $s2, $v0
	
	move $s3, $zero							# zera o contador do futuro loop "for"
	j strncmp									# roda strncmp
	
strncmp:										# procedimento principal da "strncmp" (loop for)
	bge $s3, $s2, termina_retorna_zero
	
	addu $s0, $s0, $s3							# assume n em $s3; string em $s0; retorna o caractere (string[n]) em $t0
	lbu $t0, ($s0)
	
	addu $s1, $s1, $s3							# assume n em $s3; string em $s1; retorna o caractere (string[n]) em $t1
	lbu $t1, ($s1)
	
	bne $t0, $t1, termina_retorna_diferenca			# se respectivos caracteres nao batem, termina retornando a diferenca
	
	add $s3, $s3, 1								# incrementa contador
	
	j strncmp 								# fecha o loop for
	
termina_retorna_diferenca: 						# termina o programa no caso de achar char diferente
	li $v0, 4
	la $a0, resposta
	syscall									# imprime mensagem

	sub $a0, $t0, $t1							# guarda diferenca dos caracteres em $a0
	li $v0, 1
	syscall									# imprime resultado

	li $v0, 4
	la $a0, linha
	syscall									# imprime linha

	li $v0, 10									# termina o programa
	syscall	

termina_retorna_zero:							# termina o programa no caso de strings iguais
	li $v0, 4
	la $a0, resposta
	syscall									# imprime mensagem
	
	li $v0, 1
	move $a0, $zero
	syscall									# imprime zero
	
	li $v0, 4
	la $a0, linha
	syscall									# imprime linha
	
	li $v0, 10									# termina o programa
	syscall	

# obs. sem tratamento de excecoes, como entrada de numero maior que uma das strings, ou numero negativo, ou float, etc.
# portanto em entradas inapropriadas, se houver resultado, considerar como lixo.
# FIM
