/** 
 * \mainpage
 * 
 * \author Luca Maciel Alexander, 11219175
 * \author Nathan Rodrigues de Oliveira, 11218938
 * \author Yure Pablo do Nascimento Oliveira, 11275317
 * \author Dalton Hiroshi Sato, 11275172
 * \version 1.0
 * \date 2020
 * 
 * \tableofcontents
 * 
 * \section sec1 Breve Descrição do Projeto
 * 
 *  Jogo simples multiplayer com mecânica fundada em frequência de apertos de teclas, 
 *  criado para a disciplina de Sistemas Operacionais SSC0140, demonstrando o uso de threads e semáforos.
 * 
 * 
 * \section sec2 Manual de Instalação
 * 
 * 
 * 
 * \section sec3 Como Jogar
 * 
 * 
 * 
 * \section sec4 Nota Técnica
 * 
 * Jogo de "cabo-de-guerra" virtual. Existem dois jogadores, a cada um é associado um botão do teclado. A partir 
 * do sinal de início, ambos devem apertar suas respectivas teclas o mais frequentemente (rapidamente) possível, 
 * objetivando "puxar a corda" para seu lado. O deslocamento da corda será constantemente atualizado e impresso em 
 * tempo real. Será também implementada a característica de "inércia", implicando que se um jogador estiver ganhando, 
 * fica mais fácil de puxar a corda para seu lado. \n
 * Cada jogador será abstraído como uma thread. Estas tentam constantemente acessar e modificar uma variável que deverá 
 * conter o estado da corda (logo, sendo a região crítica). Um semáforo será utilizado para controlar esses acessos. \n
 * A inércia da corda justifica o sentido do uso do semáforo, pois a quantidade que uma thread altera o estado da corda depende do próprio 
 * estado da corda! Assim, é impossível salvar o deslocamento causado por cada jogador em variáveis separadas, somando as quando 
 * for conveniente. As alterações de deslocamento terão de ser atualizadas imediatamente e diretamente na variável que contém o 
 * estado da corda, pedindo a atuação de um semáforo sobre essa região crítica. 
 * 
*/