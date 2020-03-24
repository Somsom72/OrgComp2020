	.data
	.align 0
	
#Strings para interação com o usuario
str_erro : .asciiz "Valor digitado invalido\n\n"
str_menu : .asciiz "Bem-vindo à calculadora\n"
str_opera: .asciiz "Digite:\n\n1-soma\n2-subtracao\n3-multiplicacao\n4-divisao\n5-potencia\n6-raiz quadrada\n7-tabuada\n8-IMC\n9-fatorial\n10-fibonacci\n11-Encerrar o programa\n\n"
str_close: .asciiz "\n----Fechando programa----\n"
str_args: .asciiz "Insira o(s) argumento(s)\n"
str_resp: .asciiz "Resposta: "
str_novaLinha: .asciiz "\n"

	.text
	.globl main
	
main:
	#Chamada do menu
	li $v0, 4
	la $a0, str_menu
	syscall
	j menu
	
erro:
	#Imprime mensagem de erro e volta ao menu
	li $v0, 4
	la $a0, str_erro
	syscall
	
menu:
	#Impressao do menu
	li $v0, 4
	la $a0, str_opera
	syscall
	
	#Leitura da escolha do usuario
	li $v0, 5
	syscall
	move $t1, $v0
	
	#Detectar valor inadequado
	li $t9, 0
	ble $t1, $t9 erro
	li $t8, 12
	bge $t1, $t8 erro
	
	#OPCAO 1
	#OPCAO 2
	#OPCAO 3
	#OPCAO 4
	#OPCAO 5
	
	#OPCAO 6
	beq $t1, 6, raizMain
	
	#OPCAO 7
	#OPCAO 8
	
	#OPCAO 9
	beq $t1, 9, fatorialMain
	
	#OPCAO 10
	
	#OPCAO 11
	beq $t1, 11, fim
	
fim:
	#Finaliza o programa com mensagem
	li $v0, 4
	la $a0, str_close
	syscall
	
	li $v0, 10
	syscall


raizMain: 
	#Pedindo argumento
	li $v0, 4
	la $a0, str_args
	syscall 
	
	#Lendo argumento
	li $v0, 5
	syscall 
	move $t1, $v0
	
	#Detectar valor inadequado
	blt $t1, 0, erro
	
	#Loop da raiz
	li $t2, 0 #Inicializando contador
	li $t4, 1 #Inicializando o registrador que guardara o proximo impar a ser somado
	li $t5, 0 #Inicializando o registrador que guardara a soma dos impares
	j raizLoop
	
raizLoop:
	#Retorna ceil(sqrt(n)) para n sem raiz exata, e sqrt(n) para n com raiz exata.
	#Metodo usado: somando iterativamente os impares ate ultrapassar n, retornando o contador.
	bge $t5, $t1, raizImprimir #Se a soma dos impares ultrapassar o quadrado da entrada, acabamos!
	add $t5, $t5, $t4 #Adicionando mais um impar a soma
	addi $t4, $t4, 2 #Atualizando o proximo impar a ser somado
	addi $t2, $t2, 1 #Incrementando o contador
	j raizLoop
	
raizImprimir:
	#Finaliza o loop da raiz, imprimindo o resultado
	li $v0, 4
	la $a0, str_resp
	syscall
	li $v0, 1
	move $a0, $t2
	syscall
	li $v0, 4
	la $a0, str_novaLinha
	syscall
	j menu
		
fatorialMain:
	#Pedindo argumento
	li $v0, 4
	la $a0, str_args
	syscall 
	
	#Lendo argumento
	li $v0, 5
	syscall 
	move $t1, $v0
	
	#Detectar valor inadequado
	blt $t1, 0, erro
	
	#Primeiro tratando os casos de zero e um fatorial
	beq $t1, 0, fatorialZero
	beq $t1, 1, fatorialZero
	
	#Loop do fatorial
	move $t2, $t1 #usando reg. $t2 como contador
	jal fatorialLoop
	
	#Imprimindo resultado
	li $v0, 4
	la $a0, str_resp
	syscall
	li $v0, 1
	move $a0, $t1
	syscall
	li $v0, 4
	la $a0, str_novaLinha
	syscall
	
	j menu
	
fatorialZero:
	# imprime 1
	li $v0, 4
	la $a0, str_resp
	syscall
	li $v0, 1
	li $a0, 1
	syscall
	li $v0, 4
	la $a0, str_novaLinha
	syscall
	
	j menu
	
fatorialLoop:
	# calcula fatorial de inteiros maiores que zero
	addi $t2, $t2, -1
	mul $t1, $t1, $t2
	bgt $t2, 1, fatorialLoop
	
	jr $ra
	
	