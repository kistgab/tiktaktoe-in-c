/* Trabalho PRP - A
   Dupla: Arthur Brixius da Costa e Matheus Barreto */

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>
#include <stdbool.h>

#define TAMANHO_JOGO_DA_VELHA 3
#define VALOR_TABULEIRO_JOGADOR 1
#define VALOR_TABULEIRO_COMPUTADOR 2

typedef struct jogada
{
  int linha;
  int coluna;
} Jogada;

void preencherTabuleiro(int tabuleiro[][TAMANHO_JOGO_DA_VELHA])
{
  for (int i = 0; i < TAMANHO_JOGO_DA_VELHA; i++)
  {
    for (int j = 0; j < TAMANHO_JOGO_DA_VELHA; j++)
    {
      tabuleiro[i][j] = 0;
    }
  }
}

int sortearNumeroInteiro(int maiorNumero)
{
  srand(time(NULL));
  return rand() % maiorNumero;
}

int sortearJogadorParaComecar()
{
  int MAIOR_NUMERO_JOGADOR_SORTEAR = 2;
  return sortearNumeroInteiro(MAIOR_NUMERO_JOGADOR_SORTEAR);
}

void imprimirTabuleiro(int tabuleiro[][TAMANHO_JOGO_DA_VELHA])
{
  printf("         A   B   C \n");
  for (int i = 0; i < TAMANHO_JOGO_DA_VELHA; i++)
  {
    printf("     %d", i + 1);
    printf(" /");
    for (int j = 0; j < 3; j++)
    {
      if (tabuleiro[i][j] == 0)
      {
        printf("   /"); // se o espaço tem valor 0, ele está vazio
      }
      else if (tabuleiro[i][j] == 1)
      {
        printf(" X /"); // se o espaço tem valor 1, ele é um X
      }
      else if (tabuleiro[i][j] == 2)
      {
        printf(" 0 /"); // se o espaço tem valor 2, ele é um 0
      }
    }
    printf("\n       ------------- \n");
  }
}

bool ganhouNaLinha(int tabuleiro[][TAMANHO_JOGO_DA_VELHA])
{
  for (int i = 0; i < TAMANHO_JOGO_DA_VELHA; i++)
  {
    bool todosDaLinhaSaoIguais = tabuleiro[i][0] == tabuleiro[i][1] && tabuleiro[i][1] == tabuleiro[i][2];
    if (todosDaLinhaSaoIguais)
      return true;
  }
  return false;
}

bool ganhouNaColuna(int tabuleiro[][TAMANHO_JOGO_DA_VELHA])
{
  for (int j = 0; j < TAMANHO_JOGO_DA_VELHA; j++)
  {
    bool todosDaColunaSaoIguais = tabuleiro[0][j] == tabuleiro[1][j] && tabuleiro[1][j] == tabuleiro[2][j];
    if (todosDaColunaSaoIguais)
      return true;
  }
  return false;
}

bool ganhouNaDiagonalPrincipal(int tabuleiro[][TAMANHO_JOGO_DA_VELHA])
{
  bool todosDaDiagonalSaoIguais = tabuleiro[0][0] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][2];
  return todosDaDiagonalSaoIguais;
}

bool ganhouNaDiagonalSecundaria(int tabuleiro[][TAMANHO_JOGO_DA_VELHA])
{
  bool todosDaDiagonalSaoIguais = tabuleiro[0][2] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][0];
  return todosDaDiagonalSaoIguais;
}

bool jogoDeveTerminar(int tabuleiro[][TAMANHO_JOGO_DA_VELHA], int quantidadeDeJogadas)
{
  bool alguemGanhou = ganhouNaLinha(tabuleiro) || ganhouNaColuna(tabuleiro) || ganhouNaDiagonalPrincipal(tabuleiro) || ganhouNaDiagonalSecundaria(tabuleiro);
  return alguemGanhou || quantidadeDeJogadas == 9;
}

bool ehPosicaoLivre(int tabuleiro[][TAMANHO_JOGO_DA_VELHA], Jogada jogada)
{
  return tabuleiro[jogada.linha][jogada.coluna] == 0;
}

bool ehPosicaoValida(Jogada jogada)
{
  bool ehLinhaValida = jogada.linha >= 0 && jogada.linha < TAMANHO_JOGO_DA_VELHA;
  bool ehColunaValida = jogada.coluna >= 0 && jogada.coluna < TAMANHO_JOGO_DA_VELHA;
  return ehColunaValida && ehLinhaValida;
}

bool ehJogadaValida(int tabuleiro[][TAMANHO_JOGO_DA_VELHA], Jogada jogada)
{
  return ehPosicaoValida(jogada) && ehPosicaoLivre(tabuleiro, jogada);
}

int letraParaColuna(char letra)
{
  switch (toupper(letra))
  {
  case 'A':
    return 0;
    break;
  case 'B':
    return 1;
    break;
  case 'C':
    return 2;
    break;
  default:
    return 999;
  }
}

void realizarJogadaJogador(int tabuleiro[][TAMANHO_JOGO_DA_VELHA])
{
  Jogada jogadaAtual;
  char letraColunaSelecionada;

  do
  {
    printf("\n Onde deseja fazer sua jogada (Linha depois Coluna)? ");
    fflush(stdin);
    scanf("%d %c", &jogadaAtual.linha, &letraColunaSelecionada);
    jogadaAtual.coluna = letraParaColuna(letraColunaSelecionada);
    jogadaAtual.linha -= 1;
    if (ehJogadaValida(tabuleiro, jogadaAtual))
    {
      tabuleiro[jogadaAtual.linha][jogadaAtual.coluna] = VALOR_TABULEIRO_JOGADOR;
      break;
    }
    printf("\nJogada Inválida! Tente novamente");
  } while (!ehJogadaValida(tabuleiro, jogadaAtual));
}

void realizarJogadaComputador(int tabuleiro[][3])
{
  Jogada jogadaAtual;
  bool jogadaComputadorValida = false;
  while (!jogadaComputadorValida)
  {
    jogadaAtual.coluna = sortearNumeroInteiro(TAMANHO_JOGO_DA_VELHA);
    jogadaAtual.linha = sortearNumeroInteiro(TAMANHO_JOGO_DA_VELHA);
    if (ehPosicaoLivre(tabuleiro, jogadaAtual))
    {
      tabuleiro[jogadaAtual.linha][jogadaAtual.coluna] = 2;
      jogadaComputadorValida = true;
    }
  }
}

void iniciarJogoDaVelha()
{
  int tabuleiro[3][3], QuemComeca, JogoTerminou, quantidadeDeJogadas;

  preencherTabuleiro(tabuleiro);
  QuemComeca = sortearJogadorParaComecar();
  if (QuemComeca == 0)
  {
    printf("\n Você Começa!(Você é X) \n \n");
  }
  else
  {
    printf("\n O Computador Começa!(Ele é Bolinha) \n \n");
    realizarJogadaComputador(tabuleiro);
    imprimirTabuleiro(tabuleiro);
  }

  // loop para realizar as jogadas do computador e do jogador
  JogoTerminou = 0;
  while (JogoTerminou == 0)
  {
    // system("clear");
    printf("\n");
    imprimirTabuleiro(tabuleiro);
    realizarJogadaJogador(tabuleiro);
    quantidadeDeJogadas++;
    JogoTerminou = jogoDeveTerminar(tabuleiro, quantidadeDeJogadas);
    if (JogoTerminou)
    {
      break;
    }
    realizarJogadaComputador(tabuleiro);
    quantidadeDeJogadas++;
    JogoTerminou = jogoDeveTerminar(tabuleiro, quantidadeDeJogadas);
  }
}

int main()
{
  setlocale(LC_ALL, "Portuguese");
  int EscolherOpcao;

  while (EscolherOpcao != 2)
  {
    printf("\n Jogo da Velha");
    printf("\n 1. Jogar");
    printf("\n 2. Sair");
    printf("\n Escolha: ");
    scanf("%d", &EscolherOpcao);

    switch (EscolherOpcao)
    {
    case 1:
      iniciarJogoDaVelha();
      break;
    case 2:
      printf("\n Saindo... \n");
      break;
    default:
      printf("\n Valor Inválido. \n");
      break;
    }
  }
}
