#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <dos.h>
#include <stdlib.h>
#define TAM 50

struct Elem
{
   char nome[30];
   int nr;
};
struct Lista
{
   Elem M[TAM];
   int Fim;
};

void telainicial();
void moldura(int li,int ci,int lf,int cf,int cor);
void carregamento();
void tela1_dados();
void tela1_ledados();
void escreve_dados1();
void tela2_dados();
void tela2_ledados();
void escreve_dados2();
void grava_produto();
void grava_fornecedor();
void consulta_produto();
void consulta_fornecedor();
void altera_produto();
void altera_fornecedor();
void apaga_produto();
void apaga_fornecedor();
void menu();
void moldura_relatorio();
void relatorio_produto();
void relatorio_fornecedor();
void relatoriotxt_fornecedor(Lista *);
void lins(Lista *,Elem);
//void lins_fornc(Lista*,Elem);
char lrem(Lista *,Elem);
//char lrem_fornc(Elem);
void geralista_prod(Lista *);
void geralista_fornc(Lista *);
int tamanhoprod();
int tamanhofornc();

struct reg_produto
{
   char des[30];
   long codf;
   long codp;
   int qt;
   float pc;
   char status;
};
struct reg_fornecedor
{
   char fornc[30];
   long codf;
   char ender[35];
   char num[8];
   char email[30];
   char cpf[14];
   char tel[13];
   char status;
};


reg_produto produto;
reg_fornecedor fornecedor;

FILE *prod;
FILE *fornc;

Lista LP,LF,L;

void main()
{
    fornc=fopen("c:\\sacai\\fornecedores.dat","rb+");
    if (fornc==NULL)
    {
       fornc=fopen("c:\\sacai\\fornecedores.dat","wb+");
    }
    fornc=fopen("c:\\sacai\\fornecedores.dat","rb+");
    geralista_fornc(&L);
    fclose(fornc);
    clrscr();
    carregamento();
    clrscr();
    moldura(1,1,20,80,1);
    telainicial();
    getch();
    menu();

}
//MENU
void menu()
{
    int op1,op2;
    do
    {
       window(2,2,79,19);textbackground(0);clrscr();window(1,1,80,25);
       gotoxy(37,3);textcolor(5);cprintf("MENU");
       textcolor(7);
       gotoxy(32,5);printf("Departamentos:");
       gotoxy(5,6);printf("<1> Produtos           <2> Fornecedores           <3> Sair do programa");
       gotoxy(3,8);printf("Opcao:");
       window(10,8,12,8);textbackground(1);clrscr();
       window(1,1,80,25);textbackground(0);
       do
       {
	 gotoxy(10,8);printf("  ");
	 fflush(stdin);
	 gotoxy(10,8);scanf("%d",&op1);
	 fflush(stdin);
       }while((op1<1) || (op1>3));
       if (op1==1)
       {
	 gotoxy(3,10);printf("PRODUTOS");
	 gotoxy(3,11);printf("<1> Adicionar");
	 gotoxy(3,12);printf("<2> Consultar");
	 gotoxy(3,13);printf("<3> Alterar");
	 gotoxy(3,14);printf("<4> Apagar");
	 gotoxy(3,15);printf("<5> Relatorio");
	 gotoxy(3,16);printf("<6> Voltar");
	 gotoxy(3,18);printf("Opcao:");
	 window(10,18,12,18);textbackground(1);clrscr();
	 window(1,1,80,25);textbackground(0);
	 do
	 {
	   gotoxy(10,18);printf("  ");
	   fflush(stdin);
	   gotoxy(10,18);scanf("%d",&op2);
	   fflush(stdin);
	 }while((op2<1) || (op2>6));
	 switch(op2)
	 {
	   case 1:window(2,2,79,19);textbackground(0);clrscr();
		  grava_produto();
		  break;
	   case 2:window(2,2,79,19);textbackground(0);clrscr();
		  consulta_produto();
		  break;
	   case 3:window(2,2,79,19);textbackground(0);clrscr();
		  altera_produto();
		  break;
	   case 4:window(2,2,79,19);textbackground(0);clrscr();
		  apaga_produto();
		  break;
	   case 5:window(2,2,79,19);textbackground(0);clrscr();
		  relatorio_produto();
		  break;
	   case 6:window(2,2,79,19);textbackground(0);clrscr();
		  menu();
		  break;
	 }
       }
       if (op1==2)
       {
	 gotoxy(3,10);printf("FORNECEDORES");
	 gotoxy(3,11);printf("<1> Adicionar");
	 gotoxy(3,12);printf("<2> Consultar");
	 gotoxy(3,13);printf("<3> Alterar");
	 gotoxy(3,14);printf("<4> Apagar");
	 gotoxy(3,15);printf("<5> Relatorio");
	 gotoxy(3,16);printf("<6> Voltar");
	 gotoxy(3,18);printf("Opcao:");
	 window(10,18,12,18);textbackground(1);clrscr();
	 window(1,1,80,25);textbackground(0);
	 do
	 {
	   gotoxy(10,18);printf("  ");
	   fflush(stdin);
	   gotoxy(10,18);scanf("%d",&op2);
	   fflush(stdin);
	 }while((op2<1) || (op2>6));
	 switch(op2)
	 {
	   case 1:window(2,2,79,19);textbackground(0);clrscr();
		  grava_fornecedor();
		  break;
	   case 2:window(2,2,79,19);textbackground(0);clrscr();
		  consulta_fornecedor();
		  break;
	   case 3:window(2,2,79,19);textbackground(0);clrscr();
		  altera_fornecedor();
		  break;
	   case 4:window(2,2,79,19);textbackground(0);clrscr();
		  apaga_fornecedor();
		  break;
	   case 5:window(2,2,79,19);textbackground(0);clrscr();
		  relatoriotxt_fornecedor(&L);
		  break;
	   case 6:window(2,2,79,19);textbackground(0);clrscr();
		  menu();
		  break;
	 }
       }
    }while (op1!=3);
}
/*Este procedimento insere uma moldura na tela com dimensoes e cor desejada.*/
void lins(Lista *L,Elem X)
{
    int i=L->Fim;
    if (i<TAM)
    {
      while ((i>0) && (strcmp(X.nome,L->M[i-1].nome)<0))
      {
	    strcpy(L->M[i].nome,L->M[i-1].nome);
	    L->M[i].nr=L->M[i-1].nr;
	    i--;
      }
      strcpy(L->M[i].nome,X.nome);
      L->M[i].nr=X.nr;
      L->Fim++;
    }
}

/*void lins_fornc(Lista *L,Elem X)
{
    int i=LF.Fim;
    if (i<TAM)
    {
      while ((i>0) && (strcpy(X.nome,LF.M[i-1].nome)<0))
      {
	 strcpy(LF.M[i].nome,LF.M[i-1].nome);
	 LF.M[i].nr=LF.M[i-1].nr;
	 i--;
      }
      strcpy(LF.M[i].nome,X.nome);
      LF.M[i].nr=X.nr;
      LF.Fim++;
    }
}
*/
char lrem(Lista *L,Elem X)
{
    int i=0;
    while ((i<L->Fim) && (strcmp(X.nome,L->M[i].nome)>0))
       i++;
    if ((i<L->Fim) && (strcmp(X.nome,L->M[i].nome)==0))
    {
       while(i<L->Fim-1)
       {
	       strcpy(L->M[i].nome,L->M[i+1].nome);
	       L->M[i].nr=L->M[i+1].nr;
	       i++;
       }
       L->Fim--;
       return 1;
    }
    return 0;
}

/*char lrem_fornc(Elem X)
{
    int i=0;
    while ((i<LF.Fim) && (strcmp(X.nome,LF.M[i].nome)>0))
       i++;
    if ((i<LF.Fim) && (strcmp(X.nome,LF.M[i].nome)==0))
    {
       while(i<LF.Fim-1)
       {
	 strcpy(LF.M[i].nome,LF.M[i+1].nome);
	 LF.M[i].nr=LF.M[i+1].nr;
	 i++;
       }
       LF.Fim--;
       return 1;
    }
    return 0;
}
*/
int tamanhoprod()
{
    fseek(prod,0,SEEK_END);
    return ftell(prod)/sizeof(reg_produto);
}
int tamanhofornc()
{
    fseek(fornc,0,SEEK_END);
    return ftell(fornc)/sizeof(reg_fornecedor);
}

/*void geralista_prod(Lista *L)
{
    L->Fim=0;
    int nr;
    
    Elem X;
    for (nr=0;nr<tamanhoprod();nr++)
    {
       fseek(prod,nr*sizeof(reg_produto),SEEK_SET);
       fread(&contato,sizeof(reg_produto),1,prod);
       strcpy(X.nome,contato.des);
       X.nr=nr;
       lins(L,X);
    }
} */
void geralista_fornc(Lista *L)
{
    L->Fim=0;
    int nr;
    Elem X;
    for (nr=0;nr<tamanhofornc();nr++)
    {
       fseek(fornc,nr*sizeof(reg_fornecedor),SEEK_SET);
       fread(&fornecedor,sizeof(reg_fornecedor),1,fornc);
       if (fornecedor.status!='0')
       {
	     strcpy(X.nome,fornecedor.fornc);
	     X.nr=nr;
	     lins(L,X);
       }
    }
}


void relatoriotxt_fornecedor(Lista *L)
{
    fornc=fopen("c:\\sacai\\fornecedores.dat","rb+");
    if (fornc==NULL)
    {
       fornc=fopen("c:\\sacai\\fornecedores.dat","wb+");
    }
    //fornc=fopen("c:\\sacai\\fornecedores.dat","rb+");
    char nomearq[20];
    gotoxy(17,10);printf("Nome do arquivo de texto:");
    gotoxy(42,10);scanf("%s",nomearq);
    strcat(nomearq,".txt");
    FILE *arqtxt=fopen(nomearq,"w");
    if (!arqtxt)
    {
       window(2,2,79,19);textbackground(0);clrscr();
       cprintf("Impossivel criar arquivo");
       getchar();
       menu();
    }
    window(2,2,79,19);textbackground(0);clrscr();
    window(1,1,80,25);
    textcolor(5);
    gotoxy(27,12);cprintf("Gerando arquivo de texto");
    for (int j=4;j<=74;j++)
    {
       gotoxy(j,14);cprintf("Û");
       delay(50);
    }
    textcolor(7);
    window(2,2,79,19);textbackground(0);clrscr();
    fprintf(arqtxt,"Fornecedor                    Codigo    Telefone     Email                         \n");
    fprintf(arqtxt,"===================================================================================\n");
    int nr;
    for(nr=0;nr<L->Fim;nr++)
    {
       fseek(fornc,sizeof(struct reg_fornecedor)*L->M[nr].nr,SEEK_SET);
       fread(&fornecedor,sizeof(struct reg_fornecedor),1,fornc);
       if (fornecedor.status!='0')
       {
	       fprintf(arqtxt,"%-30s%-10d",fornecedor.fornc,fornecedor.codf);
	       fprintf(arqtxt,"%-13s%-30s\n",fornecedor.tel,fornecedor.email);
       }
    }
    fprintf(arqtxt,"===================================================================================\n");
    window(2,2,79,19);textbackground(0);clrscr();
    window(1,1,80,25);
    fclose(arqtxt);
    fclose(fornc);
    getchar();
}

//void lrem(Lista *L
void moldura(int li,int ci,int lf,int cf,int cor)
{
    int i;
    textcolor(cor);
    gotoxy(ci,li);
    for(i=ci;i<=cf;i++)
	cprintf("Í");//alt+205
    gotoxy(ci,li);cprintf("É");//alt+201
    gotoxy(cf,li);cprintf("»");//alt+187
    for(i=li+1;i<lf;i++)
    {
	gotoxy(ci,i);cprintf("º");//alt+186
	gotoxy(cf,i);cprintf("º");
    }
    for(i=ci;i<=cf;i++)
    {
	gotoxy(i,lf);cprintf("Í");//alt+205
    }
    gotoxy(ci,lf);cprintf("È");//alt+200
    gotoxy(cf,lf);cprintf("¼");//alt+188
    textcolor(7);
}

void moldura_relatorio(int li,int ci,int lf,int cf,int cor)
{
    int i;
    textcolor(cor);
    gotoxy(ci,li);
    for(i=ci;i<=cf;i++)
	cprintf("Í");
    for(i=ci;i<=cf;i++)
    {
       gotoxy(i,li+2);cprintf("Í");
       gotoxy(i,li+4);cprintf("Í");
    }
    gotoxy(ci,li);cprintf("É");
    gotoxy(cf,li);cprintf("»");
    for(i=li+1;i<lf;i++)
    {
	gotoxy(ci,i);cprintf("º");
	gotoxy(cf,i);cprintf("º");
	gotoxy(ci,li+2);cprintf("Ì");
	gotoxy(cf,li+2);cprintf("¹");
	gotoxy(ci,li+4);cprintf("Ì");
	gotoxy(cf,li+4);cprintf("¹");

    }
    for(i=ci;i<=cf;i++)
    {
	gotoxy(i,lf);cprintf("Í");
    }
    gotoxy(ci,lf);cprintf("È");
    gotoxy(cf,lf);cprintf("¼");
    textcolor(7);
}
/*Este procedimento insere a tela inical, com a logo da empresa.*/
void telainicial()
{
    int i;
    const dl=10;
    textcolor(5);
    //S
    for (i=8;i>=4;i--)
    {
       gotoxy(i,4);cprintf("X");
       delay(dl);
    }
    for (i=5;i<=7;i++)
    {
       gotoxy(4,i);cprintf("X");
       delay(dl);
    }
    for (i=5;i<=8;i++)
    {
       gotoxy(i,7);cprintf("X");
       delay(dl);
    }
    for (i=8;i<=10;i++)
    {
       gotoxy(8,i);cprintf("X");
       delay(dl);
    }
    for (i=7;i>=4;i--)
    {
       gotoxy(i,10);cprintf("X");
       delay(dl);
    }

    //Y
    gotoxy(10,4);cprintf("X");
    delay(dl);
    gotoxy(11,5);cprintf("X");
    delay(dl);
    gotoxy(14,4);cprintf("X");
    delay(dl);
    gotoxy(13,5);cprintf("X");
    delay(dl);
    for (i=6;i<=10;i++)
    {
       gotoxy(12,i);cprintf("X");
       delay(dl);
    }

    //S
    for (i=20;i>=16;i--)
    {
       gotoxy(i,4);cprintf("X");
       delay(dl);
    }
    for (i=5;i<=7;i++)
    {
       gotoxy(16,i);cprintf("X");
       delay(dl);
    }
    for (i=17;i<=20;i++)
    {
       gotoxy(i,7);cprintf("X");
       delay(dl);
    }
    for (i=8;i<=10;i++)
    {
       gotoxy(20,i);cprintf("X");
       delay(dl);
    }
    for (i=19;i>=16;i--)
    {
       gotoxy(i,10);cprintf("X");
       delay(dl);
    }

    //T
    for (i=10;i>=5;i--)
    {
       gotoxy(24,i);cprintf("X");
       delay(dl);
    }
    for (i=22;i<=26;i++)
    {
       gotoxy(i,4);cprintf("X");
       delay(dl);
    }


    //E
    for (i=32;i>=28;i--)
    {
       gotoxy(i,4);cprintf("X");
       delay(dl);
    }
    for (i=5;i<=10;i++)
    {
       gotoxy(28,i);cprintf("X");
       delay(dl);
    }
    for (i=29;i<=32;i++)
    {
       gotoxy(i,10);cprintf("X");
       delay(dl);
    }
    for (i=29;i<=31;i++)
    {
       gotoxy(i,7);cprintf("X");
       delay(dl);
    }

    //M
    for (i=10;i>=4;i--)
    {
       gotoxy(34,i);cprintf("X");
       delay(dl);

    }
    gotoxy(35,5);cprintf("X");
    delay(dl);
    gotoxy(36,6);cprintf("X");
    delay(dl);
    gotoxy(37,5);cprintf("X");
    delay(dl);
    for (i=4;i<=10;i++)
    {
       gotoxy(38,i);cprintf("X");
       delay(dl);

    }

    //O
    for (i=4;i<=10;i++)
    {
       gotoxy(43,i);cprintf("X");
       delay(dl);
    }
    for (i=44;i<=47;i++)
    {
       gotoxy(i,10);cprintf("X");
       delay(dl);
    }
    for (i=10;i>=5;i--)
    {
       gotoxy(47,i);cprintf("X");
       delay(dl);
    }
    for (i=47;i>=43;i--)
    {
       gotoxy(i,4);cprintf("X");
       delay(dl);
    }

    //F
    for (i=10;i>=4;i--)
    {
       gotoxy(49,i);cprintf("X");
       delay(dl);
    }
    for (i=50;i<=53;i++)
    {
       gotoxy(i,4);cprintf("X");
       delay(dl);
    }

    for (i=50;i<=52;i++)
    {
       gotoxy(i,7);cprintf("X");
       delay(dl);
    }

    //A
    for (i=10;i>=4;i--)
    {
       gotoxy(58,i);cprintf("X");
       delay(dl);
    }
    for (i=59;i<=62;i++)
    {
       gotoxy(i,4);cprintf("X");
       delay(dl);
    }
    for (i=5;i<=10;i++)
    {
       gotoxy(62,i);cprintf("X");
       delay(dl);
    }
    for (i=59;i<=61;i++)
    {
       gotoxy(i,7);cprintf("X");
       delay(dl);
    }

    //C
    for (i=68;i>=64;i--)
    {
       gotoxy(i,4);cprintf("X");
       delay(dl);
    }
    for (i=5;i<=10;i++)
    {
       gotoxy(64,i);cprintf("X");
       delay(dl);
    }
    for (i=65;i<=68;i++)
    {
       gotoxy(i,10);cprintf("X");
       delay(dl);
    }
    //‡
    gotoxy(66,11);cprintf("X");
    delay(dl);
    gotoxy(65,12);cprintf("X");
    delay(dl);
    gotoxy(64,13);cprintf("X");
    delay(dl);
    gotoxy(65,13);cprintf("X");
    delay(dl);
    gotoxy(66,13);cprintf("X");
    delay(dl);
    gotoxy(67,13);cprintf("X");
    delay(dl);
    gotoxy(66,14);cprintf("X");
    delay(dl);
    gotoxy(65,15);cprintf("X");
    delay(dl);

    //A
    for (i=10;i>=4;i--)
    {
       gotoxy(70,i);cprintf("X");
       delay(dl);
    }
    for (i=71;i<=74;i++)
    {
       gotoxy(i,4);cprintf("X");
       delay(dl);
    }
    for (i=5;i<=10;i++)
    {
       gotoxy(74,i);cprintf("X");
       delay(dl);
    }
    for (i=71;i<=73;i++)
    {
       gotoxy(i,7);cprintf("X");
       delay(dl);
    }

    //I
    for (i=10;i>=4;i--)
    {
       gotoxy(76,i);cprintf("X");
       delay(dl);
    }
    //¡
    gotoxy(78,3);cprintf("X");
    delay(dl);
    gotoxy(79,2);cprintf("X");
    delay(dl);

    //Info
    gotoxy(21,18);cprintf("Pressione alguma tecla para continuar");
    gotoxy(57,18);
    textcolor(7);
}
/*Este procedimento insere uma animacao de tela de loading. */
void carregamento()
{
    textcolor(5);
    gotoxy(35,12);cprintf("CARREGANDO");
    for (int i=2;i<=79;i=i+2)
    {
       gotoxy(i,14);cprintf("Û");
       delay(50);
    }
    textcolor(7);
}
/*Este procedimento exibe a tela de dados referentes a produto. */
void tela1_dados()
{
    gotoxy(31,2);printf("Cadastrar produto ");
    gotoxy(3,4);printf("Descricao           : ");window(25,4,55,4);textbackground(1);clrscr();window(1,1,80,25);textbackground(0);
    gotoxy(3,6);printf("Codigo do Fornecedor: ");window(25,6,45,6);textbackground(1);clrscr();window(1,1,80,25);textbackground(0);
    gotoxy(3,8);printf("Codigo do Produto   : ");window(25,8,45,8);textbackground(1);clrscr();window(1,1,80,25);textbackground(0);
    gotoxy(3,10);printf("Quantidade          : ");window(25,10,35,10);textbackground(1);clrscr();window(1,1,80,25);textbackground(0);
    gotoxy(3,12);printf("Preco de custo      : ");window(25,12,35,12);textbackground(1);clrscr();window(1,1,80,25);textbackground(0);
}
/*Este procedimento direciona a leitura de dados referentes a produto.*/
void tela1_ledados()
{
    fflush(stdin);
    gotoxy(25,4);gets(produto.des);fflush(stdin);
    gotoxy(25,6);scanf("%d",&produto.codf);fflush(stdin);
    gotoxy(25,8);printf("%d",produto.codp);fflush(stdin);
    gotoxy(25,10);scanf("%d",&produto.qt);fflush(stdin);
    gotoxy(25,12);scanf("%f",&produto.pc);fflush(stdin);
}
/*Este procedimento exibe a impressao dos dados lidos referente a produto.*/
void escreve_dados1()
{
    gotoxy(26,2);printf("Dados do Produto (Impressao)");
    gotoxy(3,4);printf("Descricao           : ");window(25,4,55,4);textbackground(1);clrscr();window(1,1,80,25);textbackground(0);
    gotoxy(3,6);printf("Codigo do Fornecedor: ");window(25,6,45,6);textbackground(1);clrscr();window(1,1,80,25);textbackground(0);
    gotoxy(3,8);printf("Codigo do Produto   : ");window(25,8,45,8);textbackground(1);clrscr();window(1,1,80,25);textbackground(0);
    gotoxy(3,10);printf("Quantidade          : ");window(25,10,35,10);textbackground(1);clrscr();window(1,1,80,25);textbackground(0);
    gotoxy(3,12);printf("Preco de custo      : ");window(25,12,35,12);textbackground(1);clrscr();window(1,1,80,25);textbackground(0);

    gotoxy(25,4);printf(produto.des);
    gotoxy(25,6);printf("%d",produto.codf);
    gotoxy(25,8);printf("%d",produto.codp);
    gotoxy(25,10);printf("%d",produto.qt);
    gotoxy(25,12);printf("R$%5.2f",produto.pc);
    //window(22,14,57,14);textbackground(1);clrscr();window(1,1,80,25);
    //gotoxy(22,14);printf("Digite qualquer tecla para finalizar");
}
/*Este procedimento exibe a tela de dados referente ao fornecedor.*/
void tela2_dados()
{
    gotoxy(30,2);printf("Dados do Fornecedor");
    gotoxy(3,4);printf("Fornecedor          : ");window(25,4,55,4);textbackground(1);clrscr();window(1,1,80,25);textbackground(0);
    gotoxy(3,6);printf("Codigo do Fornecedor: ");window(25,6,45,6);textbackground(1);clrscr();window(1,1,80,25);textbackground(0);
    gotoxy(3,8);printf("Endereco            : ");window(25,8,60,8);textbackground(1);clrscr();window(1,1,80,25);textbackground(0);
    gotoxy(62,8);printf("N£mero:");window(70,8,78,8);textbackground(1);clrscr();window(1,1,80,25);textbackground(0);
    gotoxy(3,10);printf("Email               : ");window(25,10,55,10);textbackground(1);clrscr();window(1,1,80,25);textbackground(0);
    gotoxy(3,12);printf("CPF/CNPJ            : ");window(25,12,40,12);textbackground(1);clrscr();window(1,1,80,25);textbackground(0);
    gotoxy(3,14);printf("Telefone            : ");window(25,14,40,14);textbackground(1);clrscr();window(1,1,80,25);textbackground(0);
}
/*Este procedimento direciona a leitura de dados referentes ao fornecedor.*/
void tela2_ledados()
{
    fflush(stdin);
    gotoxy(25,4);gets(fornecedor.fornc);fflush(stdin);
    gotoxy(25,6);printf("%d",fornecedor.codf);fflush(stdin);
    gotoxy(25,8);gets(fornecedor.ender);fflush(stdin);
    gotoxy(70,8);gets(fornecedor.num);fflush(stdin);
    gotoxy(25,10);gets(fornecedor.email);fflush(stdin);
    gotoxy(25,12);gets(fornecedor.cpf);fflush(stdin);
    gotoxy(25,14);gets(fornecedor.tel);fflush(stdin);
    fflush(stdin);
}
/*Este procedimento exibe os dados lidos referentes ao fornecedor.*/
void escreve_dados2()
{
    gotoxy(25,2);printf("Dados do Fornecedor (Impressao)");
    gotoxy(3,4);printf("Fornecedor          : ");window(25,4,50,4);textbackground(1);clrscr();window(1,1,80,25);textbackground(0);
    gotoxy(3,6);printf("Codigo do Fornecedor: ");window(25,6,45,6);textbackground(1);clrscr();window(1,1,80,25);textbackground(0);
    gotoxy(3,8);printf("Endereco            : ");window(25,8,60,8);textbackground(1);clrscr();window(1,1,80,25);textbackground(0);
    gotoxy(62,8);printf("Numero:");window(70,8,78,8);textbackground(1);clrscr();window(1,1,80,25);textbackground(0);
    gotoxy(3,10);printf("Email               : ");window(25,10,50,10);textbackground(1);clrscr();window(1,1,80,25);textbackground(0);
    gotoxy(3,12);printf("CPF/CNPJ            : ");window(25,12,40,12);textbackground(1);clrscr();window(1,1,80,25);textbackground(0);
    gotoxy(3,14);printf("Telefone            : ");window(25,14,40,14);textbackground(1);clrscr();window(1,1,80,25);textbackground(0);

    gotoxy(25,4);printf("%s",fornecedor.fornc);
    gotoxy(25,6);printf("%d",fornecedor.codf);
    gotoxy(25,8);printf("%s",fornecedor.ender);
    gotoxy(70,8);printf("%s",fornecedor.num);
    gotoxy(25,10);printf("%s",fornecedor.email);
    gotoxy(25,12);printf("%s",fornecedor.cpf);
    gotoxy(25,14);printf("%s",fornecedor.tel);
    //window(22,18,57,18);textbackground(1);clrscr();window(1,1,80,25);
    //gotoxy(22,18);printf("Digite qualquer tecla para finalizar");


}
//Este procedimento grava em um arquivo externo os dados referentes a produtos
void grava_produto()
{
    char ok='s';
    prod=fopen("c:\\sacai\\produtos.dat","rb+");
    if (prod==NULL)
    {
       prod=fopen("c:\\sacai\\produtos.dat","wb+");
       //entrando com dados no arquivo criado
    }
    prod=fopen("c:\\sacai\\produtos.dat","rb+");
    fornc=fopen("c:\\sacai\\fornecedores.dat","rb+");
    if (fornc==NULL)
    {
       fornc=fopen("c:\\sacai\\fornecedores.dat","wb+");
       //entrando com dados no arquivo criado
    }
    fornc=fopen("c:\\sacai\\fornecedores.dat","rb+");
    long n,m,n1,m1;
    fseek(prod,0,SEEK_END);
    n=sizeof(struct reg_produto);
    m=(ftell(prod)/n)+1;
    n1=sizeof(struct reg_fornecedor);
    m1=(ftell(fornc)/n1)+1;
    while ((ok=='s') || (ok=='S'))
    {
       window(2,2,79,19);textbackground(0);clrscr();
       window(1,1,80,25);
       gotoxy(46,18);printf("  ");
       produto.codp=m;
       tela1_dados();
       tela1_ledados();
       if ((produto.codf<0) || (produto.codf>(m1+1)) || (fornecedor.status=='0'))
       {
	 while ((produto.codf<0) || (produto.codf>(m1+1)) || (fornecedor.status=='0'))
	 {
	   gotoxy(47,6);textcolor(4);cprintf("Fornecedor inexistente!!");
	   textcolor(7);
	   getchar();
	   gotoxy(47,6);printf("                       ");
	   fflush(stdin);
	   gotoxy(25,6);printf("                     ");
	   fflush(stdin);
	   gotoxy(25,6);scanf("%d",&produto.codf);
	   fflush(stdin);
	 }
       }
       produto.status='1';
       fseek(prod,0,2);
       fwrite(&produto,sizeof(struct reg_produto),1,prod);
       m=m+1;
       window(46,18,48,18);textbackground(1);clrscr();
       window(1,1,80,25);textbackground(0);
       gotoxy(31,18);printf("Continuar? S/N");
       gotoxy(46,18);ok=getchar();
       fflush(stdin);
    }
    fclose(prod);
}
//Este procedimento grava em um arquivo externo dados referentes a fornecedores
void grava_fornecedor()
{
    char ok='s';
    prod=fopen("c:\\sacai\\fornecedores.dat","rb+");
    if (prod==NULL)
    {
       prod=fopen("c:\\sacai\\fornecedores.dat","wb+");
       //entrando com dados no arquivo criado
    }
    fornc=fopen("c:\\sacai\\fornecedores.dat","rb+");
    long n,m;
    fseek(fornc,0,SEEK_END);
    n=sizeof(struct reg_fornecedor);
    m=(ftell(fornc)/n)+1;
    while ((ok=='s') || (ok=='S'))
    {
       window(2,2,79,19);textbackground(0);clrscr();
       window(1,1,80,25);
       gotoxy(46,18);printf("  ");
       fornecedor.codf=m;
       tela2_dados();
       tela2_ledados();
       fornecedor.status='1';
       fseek(fornc,0,2);
       fwrite(&fornecedor,sizeof(struct reg_fornecedor),1,fornc);
       Elem X;
       strcpy(X.nome,fornecedor.fornc);
       X.nr=m-1;
       lins(&L,X);
       m=m+1;
       window(46,18,48,18);textbackground(1);clrscr();
       window(1,1,80,25);textbackground(0);
       gotoxy(31,18);printf("Continuar? S/N");
       gotoxy(46,18);ok=getchar();
       fflush(stdin);
    }
    fclose(fornc);
}
void consulta_produto()
{
    prod=fopen("c:\\sacai\\produtos.dat","rb+");
    if (prod==NULL)
    {
       /*gotoxy(29,10);textcolor(4);cprintf("Arquivo inexistente!");
       getchar();*/
       prod=fopen("c:\\sacai\\produtos.dat","wb+");
       //consultando com dados no arquivo criado
    }
    prod=fopen("c:\\sacai\\produtos.dat","rb+");
    int nr_reg;
    char ok='s';
    long n;
    fseek(prod,0,SEEK_END);
    n=sizeof(struct reg_produto);
    n=ftell(prod)/n;
    while ((ok=='s') || (ok=='S'))
    {
       window(2,2,79,19);textbackground(0);clrscr();window(1,1,80,25);
       gotoxy(30,9);printf("Consultar produto");
       gotoxy(24,11);printf("Insira o codigo:");window(42,11,54,11);textbackground(1);clrscr();
       window(1,1,80,25);textbackground(0);
       do
       {
	 gotoxy(42,11);printf("           ");
	 gotoxy(42,11);scanf("%d",&nr_reg);
	 fflush(stdin);
       }while(nr_reg>n);
       fseek(prod,sizeof(struct reg_produto) * (nr_reg-1),0);
       fread(&produto,sizeof(struct reg_produto),1,prod);
       if (produto.status=='0')
       {
	 window(2,2,79,19);textbackground(0);clrscr();window(1,1,80,25);
	 gotoxy(29,10);textcolor(4);cprintf("Produto inexistente!");
	 textcolor(7);
	 getchar();
       }
       else
       {
	 window(2,2,79,19);textbackground(0);clrscr();window(1,1,80,25);
	 escreve_dados1();
       }
       window(46,18,48,18);textbackground(1);clrscr();
       window(1,1,80,25);textbackground(0);
       gotoxy(31,18);printf("Continuar? S/N");
       gotoxy(46,18);ok=getchar();
       fflush(stdin);
    }
    fclose(prod);
}
void consulta_fornecedor()
{
    fornc=fopen("c:\\sacai\\fornecedores.dat","rb+");
    if (fornc==NULL)
    {
       /*gotoxy(29,10);textcolor(4);cprintf("Arquivo inexistente!");
       getchar();*/
       fornc=fopen("c:\\sacai\\fornecedores.dat","wb+");
       //consultando com dados no arquivo criado
    }
    fornc=fopen("c:\\sacai\\fornecedores.dat","rb+");
    char ok='s';
    int nr_reg;
    long n;
    fseek(fornc,0,SEEK_END);
    n=sizeof(struct reg_fornecedor);
    n=ftell(fornc)/n;
    while ((ok=='s') || (ok=='S'))
    {
       window(2,2,79,19);textbackground(0);clrscr();window(1,1,80,25);
       gotoxy(29,9);printf("Consultar fornecedor");
       gotoxy(24,11);printf("Insira o codigo:");window(42,11,54,11);textbackground(1);clrscr();
       window(1,1,80,25);textbackground(0);
       do
       {
	 gotoxy(42,11);printf("           ");
	 fflush(stdin);
	 gotoxy(42,11);scanf("%d",&nr_reg);
	 fflush(stdin);
       }while(nr_reg>n);
       fseek(fornc,sizeof(struct reg_fornecedor) * (nr_reg-1),0);
       fread(&fornecedor,sizeof(struct reg_fornecedor),1,fornc);
       if (fornecedor.status=='0')
       {
	 window(2,2,79,19);textbackground(0);clrscr();window(1,1,80,25);
	 gotoxy(28,10);textcolor(4);cprintf("Fornecedor inexistente!");
	 textcolor(7);
	 getchar();
       }
       else
       {
	 window(2,2,79,19);textbackground(0);clrscr();window(1,1,80,25);
	 escreve_dados2();
       }
       window(46,18,48,18);textbackground(1);clrscr();
       window(1,1,80,25);textbackground(0);
       gotoxy(31,18);printf("Continuar? S/N");
       gotoxy(46,18);ok=getchar();
       fflush(stdin);
    }
    fclose(fornc);
}

void altera_produto()
{
    int nr_reg;
    char ok='s';
    char okk;
    long n,n1;
    prod=fopen("c:\\sacai\\produtos.dat","rb+");
    if (prod==NULL)
    {
       /*gotoxy(29,10);textcolor(4);cprintf("Arquivo inexistente!");
       getch();*/
       prod=fopen("c:\\sacai\\produtos.dat","wb+");
       //entrando com dados no arquivo criado
    }
    prod=fopen("c:\\sacai\\produtos.dat","rb+");
    fornc=fopen("c:\\sacai\\fornecedores.dat","rb+");
    if (fornc==NULL)
    {
       fornc=fopen("c:\\sacai\\fornecedores.dat","wb+");
       //entrando com dados no arquivo criado
    }
    fornc=fopen("c:\\sacai\\fornecedores.dat","rb+");
    fseek(prod,0,SEEK_END);
    n=sizeof(struct reg_produto);
    n=ftell(prod)/n;
    n1=sizeof(struct reg_fornecedor);
    n1=ftell(fornc)/n1;
    while ((ok=='s') || (ok=='S'))
    {
       window(2,2,79,19);textbackground(0);clrscr();window(1,1,80,25);
       gotoxy(30,9);printf("Alterar produto");
       gotoxy(24,11);printf("Insira o codigo:");
       window(42,11,54,11);textbackground(1);clrscr();
       window(1,1,80,25);textbackground(0);
       do
       {
	  gotoxy(42,11);printf("           ");
	  gotoxy(42,11);scanf("%d",&nr_reg);
	  fflush(stdin);
       }while(nr_reg>n);
       fseek(prod,sizeof(struct reg_produto) * (nr_reg-1),0);
       fread(&produto,sizeof(struct reg_produto),1,prod);
       if (produto.status=='0')
       {
	 window(2,2,79,19);textbackground(0);clrscr();window(1,1,80,25);
	 gotoxy(29,10);textcolor(4);cprintf("Produto inexistente!");
	 textcolor(7);
	 getchar();
       }
       else
       {
	 window(2,2,79,19);textbackground(0);clrscr();window(1,1,80,25);
	 escreve_dados1();
	 fflush(stdin);
	 window(46,18,48,18);textbackground(1);clrscr();
	 window(1,1,80,25);textbackground(0);
	 gotoxy(31,18);printf("Alterar? S/N");
	 gotoxy(46,18);okk=getchar();
	 fflush(stdin);
	 if ((okk=='s') || (okk=='S'))
	 {
	    window(2,2,79,19);textbackground(0);clrscr();
	    window(1,1,80,25);
	    tela1_dados();
	    tela1_ledados();
	    if ((produto.codf<0) || (produto.codf>(n1+2)) || (fornecedor.status=='0'))
	    {
	      while ((produto.codf<0) || (produto.codf>(n1+2)) || (fornecedor.status=='0'))
	      {
		gotoxy(47,6);textcolor(4);cprintf("Fornecedor inexistente!!");
		textcolor(7);
		getchar();
		gotoxy(47,6);printf("                       ");
		fflush(stdin);
		gotoxy(25,6);printf("                     ");
		fflush(stdin);
		gotoxy(25,6);scanf("%d",&produto.codf);
		fflush(stdin);
	      }
	    }
	    fseek(prod,sizeof(struct reg_produto) * (nr_reg-1),0);
	    fwrite(&produto,sizeof(struct reg_produto),1,prod);
	 }
       }
       window(46,18,48,18);textbackground(1);clrscr();
       window(1,1,80,25);textbackground(0);
       gotoxy(31,18);printf("Continuar? S/N");
       gotoxy(46,18);ok=getchar();
       fflush(stdin);
    }
    fclose(prod);
}

void altera_fornecedor()
{
    int nr_reg;
    char ok='s';
    char okk;
    long n;
    fornc=fopen("c:\\sacai\\fornecedores.dat","rb+");
    if (fornc==NULL)
    {
       /*gotoxy(29,10);textcolor(4);cprintf("Arquivo inexistente!");
       getch();*/
       prod=fopen("c:\\sacai\\fornecedores.dat","wb+");
       //entrando com dados no arquivo criado
    }
    fornc=fopen("c:\\sacai\\fornecedores.dat","rb+");
    fseek(fornc,0,SEEK_END);
    n=sizeof(struct reg_fornecedor);
    n=ftell(fornc)/n;
    while ((ok=='s') || (ok=='S'))
    {
       window(2,2,79,19);textbackground(0);clrscr();window(1,1,80,25);
       gotoxy(30,9);printf("Alterar fornecedor");
       gotoxy(24,11);printf("Insira o codigo:");
       window(42,11,54,11);textbackground(1);clrscr();
       window(1,1,80,25);textbackground(0);
       do
       {
	     gotoxy(42,11);printf("           ");
	      gotoxy(42,11);scanf("%d",&nr_reg);
       }while(nr_reg>n);
       fseek(fornc,sizeof(struct reg_fornecedor) * (nr_reg-1),0);
       fread(&fornecedor,sizeof(struct reg_fornecedor),1,fornc);
       if (fornecedor.status=='0')
       {
	     window(2,2,79,19);textbackground(0);clrscr();window(1,1,80,25);
	     gotoxy(28,10);textcolor(4);cprintf("Fornecedor inexistente!");
	     textcolor(7);
	     getchar();
       }
       else
       {
	 window(2,2,79,19);textbackground(0);clrscr();window(1,1,80,25);
	 escreve_dados2();
	 fflush(stdin);
	 window(46,18,48,18);textbackground(1);clrscr();
	 window(1,1,80,25);textbackground(0);
	 gotoxy(31,18);printf("Alterar? S/N");
	 gotoxy(46,18);okk=getchar();
	 fflush(stdin);
	 if ((okk=='s') || (okk=='S'))
	 {
	    window(2,2,79,19);textbackground(0);clrscr();window(1,1,80,25);
	    tela2_dados();
	    tela2_ledados();
	    fseek(fornc,sizeof(struct reg_fornecedor) * (nr_reg-1),0);
	    fwrite(&fornecedor,sizeof(struct reg_fornecedor),1,fornc);
	    Elem X;
	    X.nr=nr_reg;
	    strcpy(X.nome,fornecedor.fornc);
	    lins(&LF,X);
	 }
       }
       window(46,18,48,18);textbackground(1);clrscr();
       window(1,1,80,25);textbackground(0);
       gotoxy(31,18);printf("Continuar? S/N");
       gotoxy(46,18);ok=getchar();
       fflush(stdin);
    }
    fclose(fornc);
}
void apaga_produto()
{
    prod=fopen("c:\\sacai\\produtos.dat","rb+");
    if (prod==NULL)
    {
       /*gotoxy(29,10);textcolor(4);cprintf("Arquivo inexistente!");
       getchar();*/
       prod=fopen("c:\\sacai\\produtos.dat","wb+");
       //consultando com dados no arquivo criado
    }
    prod=fopen("c:\\sacai\\produtos.dat","rb+");
    int nr_reg;
    char ok='s';
    char okk;
    long n;
    fseek(prod,0,SEEK_END);
    n=sizeof(struct reg_produto);
    n=ftell(prod)/n;
    while ((ok=='s') || (ok=='S'))
    {
       window(2,2,79,19);textbackground(0);clrscr();window(1,1,80,25);
       gotoxy(32,9);printf("Apagar produto");
       gotoxy(24,11);printf("Insira o codigo:");window(42,11,54,11);textbackground(1);clrscr();
       window(1,1,80,25);textbackground(0);
       do
       {
	 gotoxy(42,11);printf("           ");
	 fflush(stdin);
	 gotoxy(42,11);scanf("%d",&nr_reg);
	 fflush(stdin);
       }while(nr_reg>n);
       fseek(prod,sizeof(struct reg_produto) * (nr_reg-1),0);
       fread(&produto,sizeof(struct reg_produto),1,prod);
       if (produto.status=='0')
       {
	 window(2,2,79,19);textbackground(0);clrscr();window(1,1,80,25);
	 gotoxy(29,10);textcolor(4);cprintf("Produto inexistente!");
	 textcolor(7);
	 getchar();
       }
       else
       {
	 window(2,2,79,19);textbackground(0);clrscr();window(1,1,80,25);
	 escreve_dados1();
	 window(45,18,47,18);textbackground(1);clrscr();
	 window(1,1,80,25);textbackground(0);
	 gotoxy(31,18);printf("Apagar? S/N");
	 fflush(stdin);
	 gotoxy(45,18);okk=getchar();
	 if ((okk=='s') || (okk=='S'))
	 {
	   window(2,2,79,19);textbackground(0);clrscr();window(1,1,80,25);
	   produto.status='0';
	   fseek(prod,sizeof(struct reg_produto) * (nr_reg-1),0);
	   fwrite(&produto,sizeof(struct reg_produto),1,prod);
	   gotoxy(30,10);textcolor(4);cprintf("Produto removido!");
	   textcolor(7);
	   getchar();
	 }
       }
       window(46,18,48,18);textbackground(1);clrscr();
       window(1,1,80,25);textbackground(0);
       gotoxy(31,18);printf("Continuar? S/N");
       gotoxy(46,18);ok=getchar();
       fflush(stdin);
    }
    fclose(prod);
}
void apaga_fornecedor()
{
    fornc=fopen("c:\\sacai\\fornecedores.dat","rb+");
    if (fornc==NULL)
    {
       /*gotoxy(29,10);textcolor(4);cprintf("Arquivo inexistente!");
       getchar();*/
       fornc=fopen("c:\\sacai\\fornecedores.dat","wb+");
       //consultando com dados no arquivo criado
    }
    fornc=fopen("c:\\sacai\\fornecedores.dat","rb+");
    char ok='s';
    char okk;
    int nr_reg;
    long n;
    fseek(fornc,0,SEEK_END);
    n=sizeof(struct reg_fornecedor);
    n=ftell(fornc)/n;
    while ((ok=='s') || (ok=='S'))
    {
       window(2,2,79,19);textbackground(0);clrscr();window(1,1,80,25);
       gotoxy(30,9);printf("Apagar fornecedor!");
       gotoxy(24,11);printf("Insira o codigo:");window(42,11,54,11);textbackground(1);clrscr();
       window(1,1,80,25);textbackground(0);
       do
       {
	 gotoxy(42,11);printf("           ");
	 fflush(stdin);
	 gotoxy(42,11);scanf("%d",&nr_reg);
	 fflush(stdin);
       }while(nr_reg>n);
       fseek(fornc,sizeof(struct reg_fornecedor) * (nr_reg-1),0);
       fread(&fornecedor,sizeof(struct reg_fornecedor),1,fornc);
       if (fornecedor.status=='0')
       {
	     window(2,2,79,19);textbackground(0);clrscr();window(1,1,80,25);
	     gotoxy(28,10);textcolor(4);cprintf("Fornecedor inexistente!");
	     textcolor(7);
	     getchar();
       }
       else
       {
	 window(2,2,79,19);textbackground(0);clrscr();window(1,1,80,25);
	 escreve_dados2();
	 window(45,18,47,18);textbackground(1);clrscr();
	 window(1,1,80,25);textbackground(0);
	 gotoxy(31,18);printf("Apagar? S/N");
	 fflush(stdin);
	 gotoxy(45,18);okk=getchar();
	 if ((okk=='s') || (okk=='S'))
	 {
	   window(2,2,79,19);textbackground(0);clrscr();window(1,1,80,25);
	   fornecedor.status='0';
	   fseek(fornc,sizeof(struct reg_fornecedor) * (nr_reg-1),0);
	   fwrite(&fornecedor,sizeof(struct reg_fornecedor),1,fornc);
	   Elem X;
	   strcpy(X.nome,fornecedor.fornc);
	   X.nr=nr_reg;
	   lrem(&L,X);
	   gotoxy(29,10);textcolor(4);cprintf("Fornecedor removido!");
	   textcolor(7);
	   getchar();
	 }
       }
       window(46,18,48,18);textbackground(1);clrscr();
       window(1,1,80,25);textbackground(0);
       gotoxy(31,18);printf("Continuar? S/N");
       gotoxy(46,18);ok=getchar();
       fflush(stdin);
    }
    fclose(fornc);
}
void relatorio_produto()
{
    int i;
    long n;int cl=7;
    prod=fopen("c:\\sacai\\produtos.dat","rb+");
    if (prod==NULL)
    {
       prod=fopen("c:\\sacai\\produtos.dat","wb+");
    }
    prod=fopen("c:\\sacai\\produtos.dat","rb+");
    fseek(prod,0,SEEK_END);
    n=sizeof(struct reg_produto);
    n=ftell(prod)/n;
    window(2,2,79,19);textbackground(0);clrscr();window(1,1,80,25);
    moldura_relatorio(2,2,18,79,1);
    gotoxy(28,3);printf("Produtos sem estoque");
    gotoxy(7,5);printf("Descricao");
    gotoxy(35,5);printf("Codigo");
    gotoxy(55,5);printf("Preco de custo");
    for(i=1;i<=n;i++)
    {
       fseek(prod,sizeof(struct reg_produto)*(i-1),0);
       fread(&produto,sizeof(struct reg_produto),1,prod);
       if (cl>16)
       {
	 cl=7;
	 gotoxy(23,17);textcolor(4);cprintf("Pressione ENTER para continuar");
	 textcolor(7);
	 getchar();
	 window(3,7,77,17);textbackground(0);clrscr();window(1,1,80,25);
       }
       if(produto.status=='0')
       {
	 gotoxy(3,cl);printf("%s",produto.des);fflush(stdin);
	 gotoxy(35,cl);printf("%d",produto.codp);fflush(stdin);
	 gotoxy(55,cl);printf("R$%5.2f",produto.pc);fflush(stdin);
	 cl++;
       }
    }
    gotoxy(25,19);printf("Pressione ENTER para voltar");
    getchar();
    fflush(stdin);
    fclose(prod);
}
void relatorio_fornecedor()
{
    int i;
    long n;int cl=7;
    fornc=fopen("c:\\sacai\\fornecedores.dat","rb+");
    if (fornc==NULL)
    {
       fornc=fopen("c:\\sacai\\fornecedores.dat","wb+");
    }
    fornc=fopen("c:\\sacai\\fornecedores.dat","rb+");
    fseek(fornc,0,SEEK_END);
    n=sizeof(struct reg_fornecedor);
    n=ftell(fornc)/n;
    window(2,2,79,19);textbackground(0);clrscr();window(1,1,80,25);
    moldura_relatorio(2,2,18,79,1);
    gotoxy(28,3);printf("Fornecedores ativos");
    gotoxy(7,5);printf("Nome");
    gotoxy(35,5);printf("Codigo");
    gotoxy(55,5);printf("Telefone");
    for(i=1;i<=n;i++)
    {
       fseek(fornc,sizeof(struct reg_fornecedor)*(i-1),0);
       fread(&fornecedor,sizeof(struct reg_fornecedor),1,fornc);
       if (cl>16)
       {
	 cl=7;
	 gotoxy(23,17);textcolor(4);cprintf("Pressione ENTER para continuar");
	 textcolor(7);
	 getchar();
	 window(3,7,77,17);textbackground(0);clrscr();
	 window(1,1,80,25);
       }
       if(fornecedor.status=='1')
       {
	 gotoxy(3,cl);printf("%s",fornecedor.fornc);fflush(stdin);
	 gotoxy(35,cl);printf("%d",fornecedor.codf);fflush(stdin);
	 gotoxy(55,cl);printf("%s",fornecedor.tel);fflush(stdin);
	 cl++;
       }
    }
    gotoxy(21,19);printf("Pressione ENTER para continuar");
    getchar();
    fflush(stdin);
    fclose(prod);
}

