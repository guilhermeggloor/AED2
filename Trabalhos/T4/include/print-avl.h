/*
	Impressão de árvore AVL usando biblioteca NCURSES (requer instalação do pacote ncurses-dev)
	Instalação do pacote: sudo apt install ncurses-dev

    O registro do nó deve corresponder ao apresentado a seguir. O nome do registro e 
    os nomes dos campos podem diferir, mas os tipos e ordem dos campos não.
	struct s_no
	{
		int32_t chave:28;
		int32_t bal:2;
		int32_t reservado:2;
		struct s_no* esq;
		struct s_no* dir;
	};

	Para imprimir a árvore, basta incluir o arquivo print-avl.h e chamar imprime_arvore(ptraiz)
	
	No processo de compilação é necessário usar a opção -lncurses
	Ex.: gcc -o main main.c -lncurses
*/

#include <stdint.h>
#include <string.h>
#include <ncurses.h>

struct __s_no
{
    int32_t chave:28;
    int32_t bal:2;
    int32_t reservado:2;
    struct __s_no* esq;
    struct __s_no* dir;
};

static void imprime_preordem(const struct __s_no *pt, int nivel, int salto_linha, int colunai, int colunaf)
{
	if( pt == NULL )
		return;

	static int interrompe = 0;

	if( nivel > 5 )
	{
		if( interrompe == 0 )
		{
			interrompe = 1;
			attron(COLOR_PAIR(1));	
			mvprintw(0, 0, "Impressão limitada a 5 niveis!");
		}
		return;
	}

	char buffer[16];
	int chave = pt->chave;
	int bal = pt->bal;
	snprintf(buffer, 16, "%i %i", chave, bal);

  	attron(COLOR_PAIR(2));	
	mvprintw(nivel*salto_linha, (colunai+colunaf)/2-strlen(buffer)/2, "%i", chave);
	attroff(COLOR_PAIR(2));
  	attron(COLOR_PAIR(3));
	printw("%i", bal);			
  	attroff(COLOR_PAIR(3));
		
	imprime_preordem(pt->esq, nivel+1, salto_linha, colunai, (colunai+colunaf)/2);	
	imprime_preordem(pt->dir, nivel+1, salto_linha, (colunai+colunaf)/2, colunaf);	
}

void imprime_arvore(const void *ptraiz)
{
	const struct __s_no *ptr = ptraiz;
	int nlinhas, ncolunas, salto_linha;
	
	initscr();
	clear();
	getmaxyx(stdscr, nlinhas, ncolunas);
	salto_linha = (nlinhas-4)/6;

	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_BLACK, COLOR_WHITE);
 	init_pair(3, COLOR_RED, COLOR_GREEN);
  	attron(COLOR_PAIR(1));	

	if( ptr == NULL )
	{
		mvprintw(nlinhas/2, ncolunas/2-7, "Arvore vazia!");
		attroff(COLOR_PAIR(1));
	}
	else
	{
	 	mvprintw(salto_linha/2, ncolunas/2-2, "Raiz");	
 		attroff(COLOR_PAIR(1));
 		
 		imprime_preordem(ptr, 1, salto_linha, 0, ncolunas);
	}
	
	move(getmaxy(stdscr)-1, getmaxx(stdscr)-1);
	refresh();
	getch();
	endwin();
}
