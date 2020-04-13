.data

	.align 0

	

#Strings para interação com o usuario

str_erro : .asciiz "Valor digitado invalido\n"

str_menu : .asciiz "Bem-vindo à calculadora"

str_opera: .asciiz "\nDigite:\n1-Soma(A+B)\n2-Subtração(A-B)\n3-Multiplicação(A*B)(com ambos de até 16 bits)\n4-Divisao(A/B)(com ambos de até 16 bits)\n5-Potência(A^B)\n6-Raiz quadrada(sqrt(A))\n7-Tabuada (de um número <429496728)\n8-IMC\n9-Fatorial (A!, com A<13)\n10-Sequencia de Fibonacci até A \n11-Encerrar o programa\n"

str_close: .asciiz "\n----Fechando programa----\n"

str_argsA: .asciiz "Insira o argumento A\n"

str_argsB: .asciiz "Insira também o argumento B\n"

str_Altura: .asciiz "Insira a altura:\n"

str_Peso: .asciiz "Insira o peso:\n"

str_contaplus: .asciiz " + "

str_contaminus: .asciiz " - "

str_contamul: .asciiz " * "

str_contadiv: .asciiz " / "

str_contaelevate: .asciiz " ^ "

str_contasqrt1: .asciiz "sqrt ("

str_contasqrt2: .asciiz ")"

str_contafat: .asciiz "!"

str_contaeq: .asciiz " = "

str_IMC: .asciiz "IMC = "

str_novaLinha: .asciiz "\n"

str_espaco: .asciiz " "



	.text

	.globl main

	

main:

	#Impressão da mensagem de boas vindas e Chamada do menu

	li $v0, 4

	la $a0, str_menu

	syscall

	j menu

	

erro:

	#Imprime mensagem de erro e volta ao menu

	li $v0, 4

	la $a0, str_erro

	syscall

	#j menu # para caso esta "função" esteja em outra região do código

menu:

	#Impressao do menu

	li $v0, 4

	la $a0, str_opera

	syscall


	#Leitura da escolha do usuario e armazenamento da escolha em $t1

	li $v0, 5

	syscall
	
	#Passando o valor lido como parâmetro (via $v0) para escolher uma das funções da calculadora

	#OPCAO 1 - Soma(A+B)
	
	beq $v0, 1, soma

	#OPCAO 2 - Subtração(A-B)
	
	beq $v0, 2, subtracao

	#OPCAO 3 - Multiplicação(A*B)
	
	beq $v0, 3, multiplicacao

	#OPCAO 4 - Divisao(A/B)
	
	beq $v0, 4, divisao

	#OPCAO 5 - Potência(A^B)
	
	beq $v0, 5, potencia

	#OPCAO 6 - Raiz quadrada(sqrt(A))

	beq $v0, 6, raizMain

	#OPCAO 7 - Tabuada (de um número de <400M)

	beq $v0, 7, tabuada

	#OPCAO 8 - IMC (A=Altura, B=Peso)

	beq $v0, 8, IMC

	#OPCAO 9 - Fatorial (A!, com A<13)

	beq $v0, 9, fatorialMain

	#OPCAO 10 - Sequencia de Fibonacci até A (com A<48)
	
	beq $v0, 10, fibonacciMain

	#OPCAO 11 - Encerrar o programa

	beq $v0, 11, fim

	#OPCAO Outro - Erro
	
	j erro

soma:

#Pedindo argumentos A e B

	li $v0, 4
	la $a0, str_argsA
	syscall 
	
	li $v0, 5
	syscall 
	move $t1, $v0 #armazena em t1 o valor de A
	
	li $v0, 4
	la $a0, str_argsB
	syscall 
	
	li $v0, 5
	syscall 
	move $t2, $v0 #armazena em t2 o valor de B
	
	add $t3,$t1,$t2 #faz a soma e armazena em t3
	
	#imprime A+B = %d 
	
	li $v0,1
	move $a0, $t1
	syscall#"A"
	
	li $v0,4
	la $a0, str_contaplus
	syscall#" + "
	
	li $v0,1
	move $a0, $t2
	syscall#"B"
	
	li $v0,4
	la $a0, str_contaeq
	syscall#" = "
	
	li $v0, 1
	move $a0,$t3
	syscall#A+B
	
	li $v0, 4
	la $a0, str_novaLinha
	syscall #printf("\n");
	
	#move $v0,$t3  #Salva o 'retorno da função - não usado 
	#retorna ao menu
	j menu

subtracao:

#Pedindo e lendo argumentos A e B

	li $v0, 4
	la $a0, str_argsA
	syscall 
	
	li $v0, 5
	syscall 
	move $t1, $v0 #armazena em t1 o valor de A
	
	li $v0, 4
	la $a0, str_argsB
	syscall 
	
	li $v0, 5
	syscall 
	move $t2, $v0 #armazena em t2 o valor de B
	
	sub $t3,$t1,$t2 #faz a subtracao e armazena em t3
	
	#imprime A-B = %d 
	li $v0,1
	move $a0, $t1
	syscall#"A"
	
	li $v0,4
	la $a0, str_contaminus
	syscall#" - "
	
	li $v0,1
	move $a0, $t2
	syscall#"B"
	
	li $v0,4
	la $a0, str_contaeq
	syscall#" = "
	
	li $v0, 1
	move $a0,$t3
	syscall#A-B
	
	li $v0, 4
	la $a0, str_novaLinha
	syscall #printf("\n");
	
	#move $v0,$t3  #Salva o 'retorno da função - não usado 
	#retorna ao menu
	j menu

multiplicacao:

#Pedindo e lendo argumentos A e B

	li $v0, 4
	la $a0, str_argsA
	syscall 
	
	li $v0, 5
	syscall 
	move $t1, $v0 #armazena em t1 o valor de A
	
	#testa se o numero tem 16 bits
	li $t8,65536
	li $t9,-65536
	bgt $t1,$t8,erro
	blt $t1,$t9,erro
	
	li $v0, 4
	la $a0, str_argsB
	syscall 
	
	li $v0, 5
	syscall 
	move $t2, $v0 #armazena em t2 o valor de B
	
	#testa se o numero tem 16 bits
	li $t8,65536
	li $t9,-65536
	bgt $t1,$t8,erro
	blt $t1,$t9,erro
	
	mul $t3,$t1,$t2 #faz a multiplicacao e armazena em t3
	
	#imprime A*B = %d 
	li $v0,1
	move $a0, $t1
	syscall#"A"
	
	li $v0,4
	la $a0, str_contamul
	syscall#" * "
	
	li $v0,1
	move $a0, $t2
	syscall#"B"
	
	li $v0,4
	la $a0, str_contaeq
	syscall#" = "
	
	li $v0, 1
	move $a0,$t3
	syscall#A*B
	
	li $v0, 4
	la $a0, str_novaLinha
	syscall #printf("\n");
	
	#move $v0,$t3  #Salva o 'retorno da função - não usado 
	#retorna ao menu
	j menu

divisao:

#Pedindo e lendo argumentos A e B

	li $v0, 4
	la $a0, str_argsA
	syscall 
	
	li $v0, 5
	syscall 
	move $t1, $v0 #armazena em t1 o valor de A
	
	#testa se o numero tem 16 bits
	li $t8,65536
	li $t9,-65536
	bgt $t1,$t8,erro
	blt $t1,$t9,erro
	
	li $v0, 4
	la $a0, str_argsB
	syscall 
	
	li $v0, 5
	syscall 
	move $t2, $v0 #armazena em t2 o valor de B
	
	#testa se o numero tem 16 bits
	li $t8,65536
	li $t9,-65536
	bgt $t1,$t8,erro
	blt $t1,$t9,erro
	
	div $t3,$t1,$t2 #faz a multiplicacao e armazena em t3
	
	#imprime A/B = %d
	li $v0,1
	move $a0, $t1
	syscall#"A"
	
	li $v0,4
	la $a0, str_contadiv
	syscall#" / "
	
	li $v0,1
	move $a0, $t2
	syscall#"B"
	
	li $v0,4
	la $a0, str_contaeq
	syscall#" = "
	
	li $v0, 1
	move $a0,$t3
	syscall#A/B
	
	li $v0, 4
	la $a0, str_novaLinha
	syscall #printf("\n");
	
	#move $v0,$t3  #Salva o 'retorno da função - não usado 
	#retorna ao menu
	j menu

potencia:

#Pedindo e lendo argumentos A e B

	li $v0, 4
	la $a0, str_argsA
	syscall 
	
	li $v0, 5
	syscall 
	move $t1, $v0 #armazena em t1 o valor de A
	
	li $v0, 4
	la $a0, str_argsB
	syscall 
	
	li $v0, 5
	syscall 
	move $t2, $v0 #armazena em t2 o valor de B
	
	bltz $t2, erro #testa se b é uma potencia positiva
	
	move $a0,$t1
	move $a1,$t2
	
	jal calcpot #funcao que recebe em a0 e a1 A e B e retorna em v0 A^B
	
	move $t3,$v0 #armazena em t3 o valor de A^B
	
	#imprime A^B = %d
	li $v0,1
	move $a0, $t1
	syscall#"A"
	
	li $v0,4
	la $a0, str_contaelevate
	syscall#" ^ "
	
	li $v0,1
	move $a0, $t2
	syscall#"B"
	
	li $v0,4
	la $a0, str_contaeq
	syscall#" = "
	
	li $v0, 1
	move $a0,$t3
	syscall#A^B
	
	li $v0, 4
	la $a0, str_novaLinha
	syscall #printf("\n");
	
	#move $v0,$t3  #Salva o 'retorno da função - não usado 
	#retorna ao menu
	j menu
	
calcpot:

	beqz $a1,potde0 #teste se a conta é do tipo A^0 (=1)
	#prepara t0 com 1 e v0 com o valor de A (=A^1)
	li $t0,1 
	move $v0,$a0
	
looppot:

	beq $a1,$t0,fimpot #caso base: A^1 = A
	mul $v0,$v0,$t1 #Se não, A=A*Ai 
	addi $a1,$a1,-1
	j looppot
	
potde0:
	li $v0, 1
	#j fimpot
fimpot:	
	jr $ra	
	
raizMain: 

	#Pedindo argumento

	li $v0, 4

	la $a0, str_argsA

	syscall 

	

	#Lendo argumento e o deixando em t1

	li $v0, 5

	syscall 

	move $t1, $v0

	

	#Detectar valor inadequado

	bltz $t1, erro

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
	la $a0, str_contasqrt1
	syscall #"sqrt("
	
	li $v0, 1
	move $a0,$t1
	syscall#("%d",A)
	
	li $v0, 4
	la $a0, str_contasqrt2
	syscall#")"
	
	li $v0, 4
	la $a0, str_contaeq
	syscall#" = "
	
	li $v0, 1
	move $a0, $t2
	syscall #resultado

	li $v0, 4
	la $a0, str_novaLinha
	syscall #printf("\n")

	j menu

tabuada:

	#Mensagem que pede argumento

	li $v0, 4
	la $a0, str_argsA
	syscall

	#Configuracao para leitura de inteiro

	li $v0, 5
	syscall

	#Comparacao para validade do numero digitado (menor que sizeof(int)/10)

	li $t1, 429496728

	bge $v0, $t1, erro
	

	#Comparaçao para validade do numero digitado (menor que 0)

	addi $t1, $0, 0

	ble $v0, $t1, erro

	
	#Copia valor digitado para registrador temporario

	move $t4, $v0

	addi $t5, $0, 11

tabuada_mul:

	#Branch de saída da tabuada (quando ja chegou na multiplicacao por 10)

	beq $t1, $t5, menu

	#Multiplica o valor lido por 0, 1, 2, ... (que esta em $t1)	

	mul $t2, $t4, $t1

	#imprime o valor base * valor de t1 = valor multiplicado:
	
	move $a0,$t4
	addi $v0, $0, 1
	syscall #valor base
	
	addi $v0, $0, 4
	la $a0, str_contamul
	syscall #" * "
	
	move $a0, $t1
	addi $v0, $0, 1
	syscall #valor de t1
	
	addi $v0, $0, 4
	la $a0, str_contaeq
	syscall #" = "
	
	move $a0,$t2
	addi $v0, $0, 1
	syscall #valor multiplicado
	
	li $v0, 4
	la $a0, str_novaLinha
	syscall #printf("\n");
	
	#Incrementa o contador para comparacao

	addi $t1, $t1, 1

	#Jump incondicional para loop's do calculo

	j tabuada_mul

IMC:

	#Chamada do sistema para leitura de double - Altura

	li $v0, 4
	la $a0, str_Altura
	syscall

	
	li $v0, 7
	syscall
	
	mov.d $f2, $f0 #altura em f2

	#Chamada do sistema para leitura de double - Peso

	li $v0, 4
	la $a0, str_Peso
	syscall

	
	li $v0, 7
	syscall
	
	mov.d $f4, $f0 #peso em f4

	#IMC <= peso/(altura^2)

	mul.d $f6, $f2, $f2 #altura ao quadrado em f6

	div.d $f12, $f4, $f6 #IMC em f12

	

	#Impressao de double e chamada do sistema

	#Impressao de double necessita valor a ser impresso no registrador $f12

	li $v0, 4
	la $a0, str_IMC
	syscall #string

	li $v0, 3
	syscall
	
	li $v0, 4
	la $a0, str_novaLinha
	syscall #printf("\n");

	j menu


fatorialMain:

	#Pedindo argumento

	li $v0, 4

	la $a0, str_argsA

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
	
	li $v0, 1
	move $a0,$t1
	syscall#"A"

	li $v0, 4
	la $a0, str_contafat
	syscall#"!"
	
	li $v0, 4
	la $a0, str_contaeq
	syscall#" = "

	li $v0, 1
	move $a0, $t1
	syscall#resultado

	li $v0, 4
	la $a0, str_novaLinha
	syscall #\n

	j menu

	
fatorialZero:

	# imprime 1

	li $v0, 1
	move $v0,$t1
	syscall#"A"

	li $v0, 4
	la $a0, str_contafat
	syscall#"!"
	
	li $v0, 4
	la $a0, str_contaeq
	syscall#" = "

	li $v0, 1
	li $a0, 1
	syscall#resultado (1)

	li $v0, 4
	la $a0, str_novaLinha
	syscall #\n

	j menu

fatorialLoop:

	# calcula fatorial de inteiros maiores que zero

	addi $t2, $t2, -1

	mul $t1, $t1, $t2

	bgt $t2, 1, fatorialLoop

	jr $ra
	
fibonacciMain:
	#Pedindo argumento
	li $v0, 4
	la $a0, str_argsA
	syscall 
	
	#Lendo argumento
	li $v0, 5
	syscall 
	move $t1, $v0
	
	#Detectar valor inadequado
	ble  $t1, 0, erro
	
	move $t2, $zero
	li $t3, 1
	add $t4, $t2, $t3 #guarda a soma dos elementos anteriores
	
	# imprime reposta
	li $v0, 4
	la $a0, str_novaLinha
	syscall
	
	#imprime o primeiro termo
	li $v0, 1
	li $a0, 1
	syscall
	
	li $v0, 4
	la $a0, str_espaco
	syscall
	
	#imprime o restante
	jal fibonacciLoop
	
	li $v0, 4
	la $a0, str_novaLinha
	syscall
	
	j menu
fibonacciLoop:
	#imprime a sequencia
	li $v0, 1
	move $a0, $t4
	syscall
	
	li $v0, 4
	la $a0, str_espaco
	syscall
	
	move $t2, $t3 #vai guardar o anterior
	move $t3, $t4 #vai guardar o proximo
	
	add $t4, $t2, $t3 #soma = fib1 + fib2
	
	ble $t4, $t1, fibonacciLoop
	
	jr $ra
fim:

	#Finaliza o programa com mensagem

	li $v0, 4

	la $a0, str_close

	syscall

	li $v0, 10

	syscall
