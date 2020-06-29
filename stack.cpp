// START PROGRAM
#include <iostream>

// Essa biblioteca permite o uso da função "system("clear") em S.O Linux.
#include <unistd.h>

using namespace std;

// Essa função pause o programa por 2 segundos e depois limpa o terminal.
void sleepAndClear()
{
  usleep(2000000);
  system("clear");
}

/*
// Estrutura da Pilha:
// att: valor -> valor contido na posição.
// att: *next -> ponteiro que contém o endereço da próxima posição.
*/
struct Stack
{
  int value;
  Stack *next;
};

/*
// Ponteiro que sempre conterá o endereço do topo.
// Caso a pilha esteja vazia, ele aponta para NULL.
*/
Stack *peak;

// Variável que indica de a pilha já foi inicializada.
bool wasStarted = false;

// Muda o estado da pilha de não inicializada para inicializada.
bool isStarted()
{
  wasStarted = true;

  return wasStarted;
}

// ================ START OF STACK FUNCTIONS ================

/*
// Essa função verifica se o topo da pilha aponta para NULL.
// Retorna um booleano, caso seja TRUE (1), quer dizer que
// a pilha está vazia.
*/
bool isEmpty()
{
  bool isEmpty = (peak == NULL) ? true : false;

  return isEmpty;
}

/*
// Essa função primeiramente verifica o estado da pilha
// Caso ainda não tenho sida inicializada, a inicializa
// caso contrário emite um alerta ao usuário.
*/
void startStack()
{
  if (!wasStarted)
  {
    cout << "Allocating memory space..." << endl;
    sleepAndClear();

    peak = NULL;

    isStarted();

    cout << "Stack started!" << endl;
  }
  else
  {
    cout << "The stack was already started!" << endl;
  }
}

/*
// Essa função recebe um valor passado por referência.
// Primeira ela verifica se a pilha ja foi inicializada,
// devolvendo um alerta caso false, se não ela instância
// uma nova pilha, e depois verifica se ela tem valor NULL
// (caso tenha, o motivo é que não foi possivel alocar memória)
// se não, ela seta o valor da nova pilha como sendo o valor passado
// para a função, seu ponteiro aponta para o topo atual, e o novo topo
// passará a ser a nova pilha.
*/
void pushStack(int &value)
{
  if (!wasStarted)
  {
    cout << "The stack wasn't started!" << endl;
  }
  else
  {
    Stack *newStack = new Stack;
    if (newStack == NULL)
    {
      cout << "Error: Memory cannot be allocated." << endl;
    }
    else
    {
      newStack->value = value;
      newStack->next = peak;
      peak = newStack;

      cout << "Added." << endl;
    }
  }
}

/*
// Essa função verifica se a pilha ja foi inicializada
// caso não exibe um alerta, caso tenha verifica se a mesma já está vazia
// caso sim exibe um alerta, se não com a ajuda de um ponteiro auxiliar
// faz com que o auxiliar receba tudo do ponteiro topo, e faz o topo atual
// olhar para o próximo elemento da pilha, o auxiliar entao recebe NULL e depois
// seu espaço de memória é desalocado.
*/
void popStack(int &value)
{
  if (!wasStarted)
  {
    cout << "The stack wasn't started!" << endl;
  }
  else if (isEmpty())
  {
    cout << "The stack already is empty!" << endl;
  }
  else
  {
    Stack *auxiliar;

    value = peak->value;
    auxiliar = peak;
    peak = peak->next;

    auxiliar->next = NULL;
    delete (auxiliar);

    cout << "Peak removed!" << endl;
  }
}
/*
// Essa função executa um pop em massa em todos os elementos da pilha
// até que o topo aponte para NULL e deslacoca o espaço de memória da
// pilha que estava no topo.
// PS: Essa função foi criada separadamente (fora do reiniciar pilha)
// pois tive a idéia de fazer o mesmo procedimento ao encerrar o programa,
// partindo do preceito de que não é uma boa prática repetir linhas de código,
// decidi cria a funcionalidade em separado.
*/
void freeUpMemory()
{
  cout << "Freeing up memory..." << endl;

  Stack *auxiliar;

  while (peak != NULL)
  {
    auxiliar = peak;
    auxiliar->next = NULL;
    peak = peak->next;

    delete (auxiliar);
  }

  peak = NULL;
}

/*
// Essa função verifica se a pilha foi inicializada,
// caso tenho sido, verifica se está vazia e caso não,
// chama a função freeUpMemory() que dá um pop em massa
// após isso indica que a pilha foi reiniciada.
*/
void restartStack()
{
  if (!wasStarted)
  {
    cout << "The stack wasn't started." << endl;
  }
  else if (isEmpty())
  {
    cout << "The stack is empty!" << endl;
  }
  else
  {
    freeUpMemory();
    sleepAndClear();
    cout << "Stack restarted!" << endl;
  }
}

/*
// Essa função verifica se a pilha foi inicializada,
// caso tenho sido, verifica se está vazia e caso não,
// com a ajuda de um ponteiro auxiliar, faz com que o auxiliar
// receba o valor ponteiro topo e em um loop imprime os valores 
// até que o topo aponte para NULL.
*/
void printStack()
{
  if (!wasStarted)
  {
    cout << "The stack wasn't started!" << endl;
  }
  else if (isEmpty())
  {
    cout << "The stack is empty!" << endl;
  }
  else
  {
    Stack *auxiliar;
    auxiliar = peak;

    while (auxiliar != NULL)
    {
      cout << " * " << auxiliar->value << " * " << endl;
      auxiliar = auxiliar->next;
    }

    delete (auxiliar);
  }
}
// ================== END OF STACK FUNCTIONS ==================

// ================ START OF CONTROL FUNCTIONS ================

/*
// Essa função exibe mensagens para indicar que o programa está sendo finalizado
// Desaloca o espaço de memória usado pela pilha usando a funçao freeUpMemory().
// e chama a função exit(0) para encerrar.
*/
void finish()
{
  freeUpMemory();
  sleepAndClear();
  cout << "Shutting down..." << endl;
  sleepAndClear();
  cout << "Program finished!" << endl;
  sleepAndClear();
  exit(0);
}

// Imprime as opções possiveis no programa e passa o valor para a variavel option.
int getMenuOption()
{
  int option;

  cout << "- Dynamic Stack Menu -\nChoose an option." << endl;
  cout << "1 - Start\n2 - Push\n3 - Pop\n4 - Restart\n5 - Print\n\n0 - Finnish\n"
       << endl;
  cout << "Option: ";
  cin >> option;

  system("clear");

  return option;
}

/*
// Essa funçao executa as opções do menu de acordo com o valor recebido
// pela função getMenuOption().
*/
void menu()
{
  switch (getMenuOption())
  {
  case 0:
    finish();
    break;
  case 1:
    startStack();
    sleepAndClear();
    menu();
    break;
  case 2:
    int value;
    cout << "Type a value: ";
    cin >> value;
    pushStack(value);
    sleepAndClear();
    menu();
    break;
  case 3:
    popStack(peak->value);
    sleepAndClear();
    menu();
  case 4:
    restartStack();
    sleepAndClear();
    menu();
    break;
  case 5:
    printStack();
    sleepAndClear();
    menu();
    break;
  default:
    cout << "Invalid option!\nChoose another." << endl;
    sleepAndClear();
    menu();
    break;
  }
}

// Função que tem como única e exclusiva responsabilidade executar o menu.
void run()
{
  menu();
}

// ================ END OF CONTROL FUNCTIONS ================

int main()
{
  run();
}
// END PROGRAM