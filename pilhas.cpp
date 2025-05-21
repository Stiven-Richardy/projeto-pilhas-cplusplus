/*
=========================================
| NOME: Stiven Richardy Silva Rodrigues |
| PRONTUÁRIO: CB3030202                 |
| TRUMA: ADS 371                        |
=========================================
*/

#include <iostream>
#include <locale.h>
#include <string>
#include <conio.h>

using namespace std;

#define MAX 30

//VETOR
struct VetorPilha {
	int elementos[MAX];
	int qtde;
};

VetorPilha* initVetor() {
	VetorPilha *p = new VetorPilha();
	p->qtde = 0;
	return p;
}

int isEmptyVetor(VetorPilha*p) {
	return (p->qtde == 0);
}

int countVetor(VetorPilha *p) {
	return (p->qtde);
}

void printVetor(VetorPilha *p) {
	cout << "| Quantidade de números PARES: " << countVetor(p) << endl;
	for(int i=p->qtde-1; i>=0; --i) {
		cout << "| Número: " << p->elementos[i] << endl;
	}
    cout << string(50, '=') << endl;	
}

int pushVetor(VetorPilha *p, int v) {
	int podeEmpilhar = (p->qtde < MAX);
	if (podeEmpilhar) {
	    p->elementos[p->qtde++] = v;
	}
	return podeEmpilhar;
}

int popVetor(VetorPilha *p) {
	int podeDesempilhar = (p->qtde > 0);
	int v;
	if (podeDesempilhar) {
		v = p->elementos[p->qtde-1];
		p->qtde--;
	} else {
		v = -1;
	}
	return v;
}

void freePilhaVetor(VetorPilha *p) {
	free(p);
}

//LISTA ENCADEADA
struct No {
	int dado;
	struct No *ant;
};

struct ListaPilha {
	No *topo;
};

ListaPilha* initLista() {
	ListaPilha *p = new ListaPilha();
	p->topo = NULL;
	return p;
}

int isEmptyLista(ListaPilha *p) {
	return (p->topo == NULL);
}

int countLista(ListaPilha *p) {
	int i = 0;
	No *no;
	no = p->topo;
	while (no != NULL) {
		i++;
		no = no->ant;
	}
	return i;
}

void printLista(ListaPilha *p) {
	No *no;
	no = p->topo;
	cout << "| Quantidade de números ÍMPARES: " << countLista(p) << endl;
	while (no != NULL) {
		cout << "| Número: " << no->dado << endl;
		no = no->ant;
	}
}

void pushLista(ListaPilha *p, int v) {
	No *no = new No;
	no->dado = v;
	no->ant = p->topo;
	p->topo = no;
}

int popLista(ListaPilha *p) {
	int ret;
	if (isEmptyLista(p)) {
		ret = -1;
	}
	else {
		No *no = p->topo;
		ret = no->dado;
		p->topo = p->topo->ant;
		free(no);
	}
	return ret;
}

void freePilhaLista(ListaPilha *p) {
	No *no;
	no = p->topo;
	while (no != NULL) {
		No *aux = no->ant;
		free(no);
		no = aux;
	}
	free(p);
}

void exibeTitulo() {
	cout << string(50, '=') << endl
	 	 << string(13, ' ') << "CADASTRA NÚMEROS INTEIROS" << endl
       	 << string(50, '=') << endl;
}

void limpaTela() {
	cout << string(50, '=') << endl
		 << "Pressione qualquer tecla..." << endl;
	_getch();
	system("cls");
}

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "");
	
	VetorPilha *pilhaPar;
	ListaPilha *pilhaImpar;
	pilhaPar = initVetor();
	pilhaImpar = initLista();
	
	int num;
	int aux;
	
	//INICÍO
	exibeTitulo();
    cout << "| IMPORTANTE: O próximo número a ser digitado,\n| deve ser SEMPRE maior que o anterior." << endl;
	limpaTela();
	
	//COLETA DE NÚMEROS INTEIROS
	exibeTitulo();
	for(int ii = 0; ii < MAX; ++ii) {
		cout << "| Digite o " << (ii+1) << "º número inteiro: ";
		cin >> num;
		
		if(!isEmptyVetor(pilhaPar) || !isEmptyLista(pilhaImpar)) {
			while(num <= aux) {
				cout << "| Erro: Número menor ou igual ao anterior. \n| Digite o " << (ii+1) << "º número inteiro: ";
				cin >> num;
	  	    }
		}
		
		if ((num % 2) == 0) {
			pushVetor(pilhaPar, num);
			aux = num;
		} else {
			pushLista(pilhaImpar, num);
			aux = num;
		}		
	}
	limpaTela();
	
	//EXIBE NÚMEROS PARES E ÍMPARES
	exibeTitulo();
	printVetor(pilhaPar);
	printLista(pilhaImpar);
	limpaTela();
	
	//DESEMPILHA EM ORDEM DECRESCENTE
	exibeTitulo();
	while (!isEmptyVetor(pilhaPar) || !isEmptyLista(pilhaImpar)) {
		if (isEmptyLista(pilhaImpar)) {
			cout << "| Desempilhou: " << popVetor(pilhaPar) << endl;
		}
		else if (isEmptyVetor(pilhaPar)) {
			cout << "| Desempilhou: " << popLista(pilhaImpar) << endl;
		}
		else if (pilhaPar->elementos[pilhaPar->qtde-1] > pilhaImpar->topo->dado) {
			cout << "| Desempilhou: " << popVetor(pilhaPar) << endl;
		}
		else {
			cout << "| Desempilhou: " << popLista(pilhaImpar) << endl;
		}
	}
	cout << string(50, '=') << endl;
	
	//LIMPA VETOR E LISTA ENCADEADA
	freePilhaVetor(pilhaPar);
	freePilhaLista(pilhaImpar);
		
	return 0;
}