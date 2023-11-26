/* Trabalho PRP - A
   Dupla: Arthur Brixius da Costa e Matheus Barreto */

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <strings.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>

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

bool campoEstaPreenchido(int valorCampo)
{
  bool campoEstaPreenchido = valorCampo != 0;
  return campoEstaPreenchido;
}

bool ganhouNaLinha(int tabuleiro[][TAMANHO_JOGO_DA_VELHA])
{
  for (int i = 0; i < TAMANHO_JOGO_DA_VELHA; i++)
  {
    bool todosCamposDaLinhaEstaoPreenchidos = campoEstaPreenchido(tabuleiro[i][0]) && campoEstaPreenchido(tabuleiro[i][1]) && campoEstaPreenchido(tabuleiro[i][2]);
    if (!todosCamposDaLinhaEstaoPreenchidos)
    {
      continue;
    }
    bool todosDaLinhaSaoIguais = tabuleiro[i][0] == tabuleiro[i][1] && tabuleiro[i][1] == tabuleiro[i][2];
    if (todosDaLinhaSaoIguais)
    {
      return true;
    }
  }
  return false;
}

bool ganhouNaColuna(int tabuleiro[][TAMANHO_JOGO_DA_VELHA])
{
  for (int j = 0; j < TAMANHO_JOGO_DA_VELHA; j++)
  {
    bool todosCamposDaColunaEstaoPreenchidos = campoEstaPreenchido(tabuleiro[j][0]) && campoEstaPreenchido(tabuleiro[j][1]) && campoEstaPreenchido(tabuleiro[j][2]);
    if (!todosCamposDaColunaEstaoPreenchidos)
    {
      continue;
    }
    bool todosDaColunaSaoIguais = tabuleiro[0][j] == tabuleiro[1][j] && tabuleiro[1][j] == tabuleiro[2][j];
    if (todosDaColunaSaoIguais)
      return true;
  }
  return false;
}

bool ganhouNaDiagonalPrincipal(int tabuleiro[][TAMANHO_JOGO_DA_VELHA])
{
  bool todosCamposDaDiagonalPrincipalEstaoPreenchidos = campoEstaPreenchido(tabuleiro[0][0]) && campoEstaPreenchido(tabuleiro[1][1]) && campoEstaPreenchido(tabuleiro[2][2]);
  if (!todosCamposDaDiagonalPrincipalEstaoPreenchidos)
  {
    return false;
  }
  bool todosDaDiagonalSaoIguais = tabuleiro[0][0] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][2];
  return todosDaDiagonalSaoIguais;
}

bool ganhouNaDiagonalSecundaria(int tabuleiro[][TAMANHO_JOGO_DA_VELHA])
{
  bool todosCamposDaDiagonalSecundariaEstaoPreenchidos = campoEstaPreenchido(tabuleiro[0][2]) && campoEstaPreenchido(tabuleiro[1][1]) && campoEstaPreenchido(tabuleiro[2][0]);
  if (!todosCamposDaDiagonalSecundariaEstaoPreenchidos)
  {
    return false;
  }
  bool todosDaDiagonalSaoIguais = tabuleiro[0][2] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][0];
  return todosDaDiagonalSaoIguais;
}

bool jogoTerminouPorAlguemGanhar(int tabuleiro[][TAMANHO_JOGO_DA_VELHA])
{
  bool alguemGanhou = ganhouNaLinha(tabuleiro) || ganhouNaColuna(tabuleiro) || ganhouNaDiagonalPrincipal(tabuleiro) || ganhouNaDiagonalSecundaria(tabuleiro);
  return alguemGanhou;
}

bool ehPosicaoLivre(int tabuleiro[][TAMANHO_JOGO_DA_VELHA], Jogada jogada)
{
  return tabuleiro[jogada.linha][jogada.coluna] == 0;
}

bool ehPosicaoValida(Jogada jogada)
{
  bool ehLinhaValida = jogada.linha >= 0 && jogada.linha < TAMANHO_JOGO_DA_VELHA;
  bool ehColunaValida = jogada.coluna >= 0 && jogada.coluna < TAMANHO_JOGO_DA_VELHA;
  return ehColunaValida == true && ehLinhaValida == true;
}

bool ehJogadaValida(int tabuleiro[][TAMANHO_JOGO_DA_VELHA], Jogada jogada)
{
  return ehPosicaoValida(jogada) == true && ehPosicaoLivre(tabuleiro, jogada) == true;
}

int letraParaColuna(char letra)
{
  if (letra == 'A')
  {
    return 0;
  }
  if (letra == 'B')
  {
    return 1;
  }
  if (letra == 'C')
  {
    return 2;
  }
  else
  {
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
    scanf("%d%c", &jogadaAtual.linha, &letraColunaSelecionada);
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

void realizarJogadaComputador(int tabuleiro[][TAMANHO_JOGO_DA_VELHA])
{
  int totalJogadasRestantes = 0;
  Jogada jogadasRestantes[9];
  for (int i = 0; i < TAMANHO_JOGO_DA_VELHA; i++)
  {
    for (int j = 0; j < TAMANHO_JOGO_DA_VELHA; j++)
    {
      if (tabuleiro[i][j] == 0)
      {
        jogadasRestantes[totalJogadasRestantes].linha = i;
        jogadasRestantes[totalJogadasRestantes].coluna = j;
        totalJogadasRestantes++;
      }
    }
  }
  int posicaoJogadaSorteada = sortearNumeroInteiro(totalJogadasRestantes);
  Jogada jogadaSorteada = jogadasRestantes[posicaoJogadaSorteada];
  tabuleiro[jogadaSorteada.linha][jogadaSorteada.coluna] = VALOR_TABULEIRO_COMPUTADOR;
    sleep(1); // 1 segundo
  printf("\n Jogada do Computador: \n \n");
}

void imprimirResultadoFinal(char resultado)
{
  printf("******** RESULTADO ********\n");
  printf("*                         *\n");
  if (resultado == 'E')
  {
    printf("*      O Jogo empatou!    *\n");
  }
  else if (resultado == 'C')
  {
    printf("*   O Computador ganhou!  *\n");
  }
  else
  {
    printf("*       Você ganhou!      *\n");
  }
  printf("*                         *\n");
  printf("***************************\n");
}

void iniciarJogoDaVelha()
{
  int tabuleiro[TAMANHO_JOGO_DA_VELHA][TAMANHO_JOGO_DA_VELHA], QuemComeca, quantidadeDeJogadas = 0;
  bool alguemGanhou = false;

  preencherTabuleiro(tabuleiro);
  QuemComeca = sortearJogadorParaComecar();
  if (QuemComeca == 0)
  {
    printf("\n Você Começa!(Você é X) \n \n");
    imprimirTabuleiro(tabuleiro);
  }
  else
  {
    printf("\n O Computador Começa!(Ele é Bolinha) \n \n");
    realizarJogadaComputador(tabuleiro);
    imprimirTabuleiro(tabuleiro);
  }

  // loop para realizar as jogadas do computador e do jogador
  while (!alguemGanhou && quantidadeDeJogadas<9)
  {
    realizarJogadaJogador(tabuleiro);
    imprimirTabuleiro(tabuleiro);
    quantidadeDeJogadas++;
    alguemGanhou = jogoTerminouPorAlguemGanhar(tabuleiro);
    if (alguemGanhou)
    {
        imprimirResultadoFinal('J');
      break;
    }
    realizarJogadaComputador(tabuleiro);
    imprimirTabuleiro(tabuleiro);
    quantidadeDeJogadas++;
    alguemGanhou = jogoTerminouPorAlguemGanhar(tabuleiro);
    if (alguemGanhou)
    {
      imprimirResultadoFinal('C');
    }
  }
  if (!alguemGanhou)
  {
    imprimirResultadoFinal('E');
  }
}

int main()
{
  setlocale(LC_ALL, "Portuguese");
  int EscolherOpcao = -1;

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
