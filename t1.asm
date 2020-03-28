	.data
	.align 0
	
#Strings para interação com o usuario
str_erro : .asciiz "Valor digitado invalido\n\n"
str_menu : .asciiz "Bem-vindo à calculadora\n"
str_opera: .asciiz "\n\nDigite:\n1-soma\n2-subtracao\n3-multiplicacao\n4-divisao\n5-potencia\n6-raiz quadrada\n7-tabuada - Numero de 1 a 10\n8-IMC - Altura Peso\n9-fatorial\n10-fibonacci\n11-Encerrar o programa\n\n"
str_close: .asciiz "\n----Fechando programa----\n"
str_args: .asciiz "Insira o(s) argumento(s)\n"
str_Altura: .asciiz "Altura: "
str_Peso: .asciiz "Peso: "
str_resp: .asciiz "Resposta: "
str_espaco: .asciiz " "
str_novaLinha: .asciiz "\n\n"

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
	beq $t1, 7, tabuada
	
	#OPCAO 8
	beq $t1, 8, IMC
	
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
	
tabuada:
	#Mensagem que pede argumento
	li $v0, 4
	la $a0, str_args
	syscall
	
	#Configuracao para leitura de inteiro
	li $v0, 5
	syscall
	
	
	#Comparacao para validade do numero digitado (maior que 10)
	addi $t1, $0, 11
	bge $v0, $t1, erro
	
	#Comparaçao para validade do numero digitado (menor que 0)
	addi $t1, $0, 0
	ble $v0, $t1, erro
	
	#Copia valor digitado para registrador temporario
	move $t4, $v0
	addi $t5, $0, 11
	
tabuada_mul:

	#Branch de saída da tabuada (quando ja chegou na multiplicacao por 10)
	bge $t1, $t5, menu

	#Multiplica o valor lido por 0, 1, 2, ... (que esta em $t1)	
	mul $t2, $t4, $t1
	
	#Copia o valor ja multiplicado para $a0, preparando para impressao
	move $a0, $t2
	
	#Comando de impressao de inteiro
	addi $v0, $0, 1
	syscall
	
	#Printando um espaco entre os numeros da tabuada
	addi $v0, $0, 4
	la $a0, str_espaco
	syscall
	
	#Incrementa o contador para comparacao
	addi $t1, $t1, 1
	
	#Jump incondicional para loop's do calculo
	j tabuada_mul

IMC:
	#Imprime string de mensagem
	li $v0, 4
	la $a0, str_args
	syscall

	#Chamada do sistema para leitura de double - Altura
	li $v0, 4
	la $a0, str_Altura
	syscall
	
	li $v0, 7
	syscall
	mov.d $f2, $f0
	
	#Chamada do sistema para leitura de double - Peso
	li $v0, 4
	la $a0, str_Peso
	syscall
	
	li $v0, 7
	syscall
	mov.d $f4, $f0
	
	#IMC => peso/(altura^2)
	mul.d $f6, $f2, $f2
	div.d $f12, $f4, $f6
	
	#Impressao de double e chamada do sistema
	#Impressao de double necessita valor a ser impresso no registrador $f12
	li $v0, 4
	la $a0, str_resp
	syscall
	
	li $v0, 3
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
