//LUCAS MURILO SILVA SOUSA RA:200866 LUCAS LIBARDI SARAIVA 200694
//GRUPO 5


//sistemas adicionais:SISTEMA DE BUSCA RA

/*detalhes importantes:não é possivel digitar um ra maior ou menor que 6 digitos,não é possivel cadastrar um
nome ou ra que esteja em branco */






#include<stdio.h>
#include<stdlib.h>
#include<string.h>



struct info_livro{
char sigla; // [L]ivre, [E]mprestado, [R]eservado
int reg; // registro do livro
};

typedef struct aluno{
char nome[80];
char RA[7];
int emprestado; // qtde de livros emprestados – Max=3
int reservado; // qtde de livros reservados – Max =1
struct info_livro tabela[4];
}aluno;

//estrutura auxiliar para pesquisar ra e não sobrescrever dados 
struct aux_info_livro{
char sigla; // [L]ivre, [E]mprestado, [R]eservado
int reg; // registro do livro
};

typedef struct aux_aluno{
char nome[80];
char RA[7];
int emprestado; // qtde de livros emprestados – Max=3
int reservado; // qtde de livros reservados – Max =1
struct aux_info_livro tabela[4];
}aux_aluno;

struct info_aluno{
char sigla;
char RA[7];
int dia_ret; // dia – máx=31
int mes_ret; // mes: fev=28 dias
int dia_dev; // mes: abril=jun=set=nov=30 dias
int mes_dev; // os demais = 31 dias
};

typedef struct livro{
int reg; // gerado automaticamente
char titulo[80];
char autor[80];
struct info_aluno status[2];
} livro;





void aloca_aluno(aluno **p,int tamanho);
void aloca_aluno2(aux_aluno **p,int tamanho);

void aloca_livro(livro **p,int tamanho);

void cadastro_aluno(aluno *p,aux_aluno *a);
void cadastro_livro(livro *pl);

int quantidade();//quantidade de alunos
int verifica_livro();
int verifica(aluno *p,char *p_ra);//verifica se o aluno pode pegar um livro
void verifica_sigla(livro *p,char *ra);

void grava(aluno *p,char *str,int pos);
void grava_livro(livro *p,char *str,int pos);

void imprime_t_alunos(aluno *p,char modo,int pos);//p ponteiro para aluno,modo é modo de exibição se é total ou parcial,int pos é a posição do ra a ser procurado
void imprime_livro(livro *p);

int busca_ra(aluno *p,char *p_ra);
int busca_ra2(aux_aluno *p,char *p_ra);

int busca_titulo(livro *p,char *pesquisa,int op,char *ra,aluno *a);

void emprestar(livro *p,aluno *a);

void altera_aluno(aluno *a,char *ra,int *reg,int);




main()
{
	aluno *alunos=NULL;
	livro *livros=NULL;
	aux_aluno *alunos2=NULL;
	
	
	
	int op,qtde_a=0,pesq,ra_p;//ra numero de pesquisa;ra_p recebe a posicão do resultado da pesquisa do ra
	char ra[7],*p_ra,pesquisa[80],*p_pes,pesquisa2,*p_pes2;

	
	
	p_ra=ra;
	p_pes=pesquisa;
	p_pes2=&pesquisa2;
	
	aloca_aluno(&alunos,1);//aloca espaço para apenas uma estrutura
	aloca_aluno2(&alunos2,1);//aloca espaço para a auxiliar
	aloca_livro(&livros,1);
	
	
	printf("Bem vindo a biblioteca!Facens\n");
	system("pause");
	do{
		
		system("cls");
        printf("\n\nOpcoes disponiveis:\n\n[1] Cadastro-Aluno\n[2] Cadastro-livro\n[3] Relatorio\n[4] Emprestar/reservar livro\n[5] sair.\n");
        printf("Digite a opcao desejada: ");
        scanf("%d", &op);
        fflush(stdin);
        
        
        switch(op){
		
		case 1:
				
			cadastro_aluno(alunos,alunos2);
			
			break;
		case 2:
			cadastro_livro(livros);
			
			break;
		case 3:
			system("cls");
			printf("[1]-ver todos alunos \n[2]-pesquisar aluno por RA \n[3]-ver todos os livros \n[4]-pesquisar por titulo do livro \n[5]-pesquisar por status\n\n");
			scanf("%i",&pesq);
			fflush(stdin);
			
			switch(pesq){
				
				case 1: imprime_t_alunos(alunos,'1',1);
		     	break;
				case 2:
					    printf("digite o RA:\n");
					    scanf("%s",p_ra);
					    fflush(stdin);
					    ra_p=busca_ra(alunos,p_ra);
						
					    
					    if(ra_p!=-1){
					    	
					    imprime_t_alunos(alunos,'2',ra_p);
					    
						}
					break;
				case 3:
					
					imprime_livro(livros);//deve mostrar do arquivo e não da memoria
					break;
				case 4:
					printf("\nDigite o titulo do livro:\n");	
					gets(p_pes);
					fflush(stdin);	
					busca_titulo(livros,p_pes,pesq,p_ra,alunos);//p_ra e alunos não será utilizado aqui 
					break;
				case 5:
					printf("\nDigite o status a ser procurado\n");
					scanf("%c",p_pes2);
					fflush(stdin);
					
					busca_titulo(livros,p_pes2,pesq,p_ra,alunos);//p_ra não será utilizado aqui
					break;
				default:
                printf("\nOpcao nao reconhecida!");
                system("Pause");
			}
			
			break;
		case 4:
			system("cls");
			emprestar(livros,alunos);
			break;
		case 5:
			break;
		
		default:
                printf("\nOpcao nao reconhecida!");
		
		}
        
        
	}while(op!=5);
	
	
	return 0;
}
// ALOCAÇÃO DINAMICA E CADASTRO DE ALUNO
void aloca_aluno(aluno **p,int tamanho)
{
	if((*p =(aluno *)realloc(*p,tamanho*sizeof(aluno)))==NULL){
		printf("erro na alocação\n");
		exit(1);
	}
}

void aloca_aluno2(aux_aluno **p,int tamanho)
{
	if((*p =(aux_aluno *)realloc(*p,tamanho*sizeof(aux_aluno)))==NULL){
		printf("erro na alocação\n");
		exit(1);
	}
}

void cadastro_aluno(aluno *p,aux_aluno *a)
{
	
	int i,qtde,ra;

	do{
	system("cls");
	printf("Nome do aluno:\n");
	gets(p->nome);
	fflush(stdin);
	
	printf("Numero RA:\n");
	gets(p->RA);
	fflush(stdin);
	//buscaRa
	if(strcmp(p->RA,"")==0||strcmp(p->nome,"")==0){
		printf("\nNome ou RA nao digitado\n");
		system("pause");
	}
	
	if(strlen(p->RA)<6||strlen(p->RA)>6){
		printf("\nO RA deve ter 6 digitos\n");
		system("pause");
		strcpy(p->nome,"");//para repetir já que o ra está invalido
	}
	
    }while(strcmp(p->RA,"")==0||strcmp(p->nome,"")==0);
    
    ra=busca_ra2(a,p->RA);
	
	if(ra!=-1){
		return;
	}
	
	
	
	p->emprestado=0;
	p->reservado=0;
	
	for(i=0;i<4;i++){
		//(pl->status+i)->mes_dev
	(p->tabela+i)->sigla='L';
	(p->tabela+i)->reg=0;
    }
    
    grava(p,"ab",1);		//adicionar o registro;ab Acrescenta dados binários no fim do arquivo
}

void imprime_t_alunos(aluno *p,char modo,int pos)
{
	int i,q_aluno,tab,achou=-1;
	FILE *p_aluno=NULL;
	
	q_aluno=quantidade();//verifica retorna a quantidade de estruturas dentro do arquivo
	system("cls");
	
	if((p_aluno=fopen("aluno.bin","rb"))==NULL)
  	printf("\nErro ao abrir o arquivo\n");
  	
  	else if(modo=='1')
  	{
	  	for(i=0;i<q_aluno;i++)
	    {
	    	
			fseek(p_aluno,i*sizeof(aluno),0);//se posiciona no inicio do arquivo e vai pulando as estruturas de acordo com i
			fread(p,sizeof(aluno),1,p_aluno);//p é a região da memoria onde serão armazenados os dados lidos
										  //sizeof(dados)é o tamanho da unidade a ser lida,1 indica quantas devem ser lidas
										  //fptr é da onde os dados serão lidos
			printf("----------------------");
			printf("\nNome:%s \nRA:%s \nEmprestados:%i \nReservados:%i \n\n",p->nome,p->RA,p->emprestado,p->reservado);
		
			
				for(tab=0;tab<4;tab++){
					
					if(p->emprestado>0||p->reservado>0)
					{
			
					printf("tabela:%i sigla:%c Reg:%i\n",tab+1,(p->tabela+tab)->sigla,(p->tabela+tab)->reg);
					
					}
			}
			printf("\n");
	    }//for
		fclose(p_aluno);
	}//imprimir todos
	else if(modo=='2'){
			
		for(i=0;i<q_aluno;i++)
    	{
	    	
		fseek(p_aluno,i*sizeof(aluno),0);//posiciona no inicio do arquivo e pula estruturas de acordo com i
		fread(p,sizeof(aluno),1,p_aluno);//p é a região da memoria onde serão armazenados os dados lidos
									  //sizeof(dados)é o tamanho da unidade a ser lida,1 indica quantas devem ser lidas
									  //p_aluno é da onde os dados serão lidos
		if(i==pos){
			
			printf("\nNome:%s \nRA:%s \nEmprestados:%i \nReservados:%i \n\n",p->nome,p->RA,p->emprestado,p->reservado);
			
			
			if(p->emprestado>0||p->reservado>0){
				
				for(tab=0;tab<4;tab++){
				
					printf("tabela:%i\n %c-%i\n",tab+1,(p->tabela+tab)->sigla,(p->tabela+tab)->reg);
				}
			}
		}
	
    	}//for
	fclose(p_aluno);  //DENTRO do else - abriu com rb
	}
		
	
  	system("pause");
  	
}

int quantidade()
{
	long int cont=0;
	FILE *file_p=NULL;
	
	if((file_p=fopen("aluno.bin","rb"))==NULL)//tenta abrir um arquivo chamado "aluno.bin,rb=read binary
	                                          //file_p vai receber o resultado de fopen
	return cont;                            //retorna 0 caso o arquivo não foi encontrado
	
	else
	  {
	  fseek(file_p,0,2);  //posiciona no fim do arquivo; fseek(ponteiro pra FILE,numero de bites para pular,origem onde o ponteiro vai ser posicionado)
	                    //origem origem 0=inicio do arquivo,origem 1=ponto atual do arquivo,origem 2 fim do arquivo
	                    
	  cont=ftell(file_p)/sizeof(aluno);   //qtde de elementos;ftell retorna o numero de bytes desde o começo do arquivo
	  fclose(file_p);    //dentro do ELSE por conta do rb
	  return cont; //retorna a quantidade de estruturas de aluno já existentes no programa
	  }//else
}//verifica

void grava(aluno *p,char *str,int pos)
{
	FILE *file_p=NULL;

	if((file_p=fopen("aluno.bin",str))==NULL)	
  	printf("\nErro ao abrir o arquivo\n");
  	
  	else
  	{
  	if(strcmp(str,"rb+")==0)//*if sem chaves só é valido para proxima instrução
    fseek(file_p,pos*sizeof(aluno),0);
    
  	fwrite(p,sizeof(aluno),1,file_p);//p é a região da memoria onde estão os dados  
								   //sizeof(dados)é o tamanho da unidade a ser escrita,1 indica quantas devem ser escritas
								   //file_p é da onde os dados serão escritos
  	
  	}//else
  	
	fclose(file_p);		//fora do ELSE por conta do ab ou rb+
}

int busca_ra(aluno *p,char *p_ra)
{
	int i,achou=-1,q_aluno;
	FILE *p_aluno=NULL;

	q_aluno=quantidade();
	system("cls");
	
	//printf("%s e %s\n",p->RA,p_ra);
    //	system("pause");
	
	
	if((p_aluno=fopen("aluno.bin","rb"))==NULL)
	  printf("\nErro\n\n");
	else{
		
		for(i=0;i<q_aluno;i++)
    	{
	    	
		fseek(p_aluno,i*sizeof(aluno),0);//posiciona no inicio do arquivo e pula estruturas de acordo com i
		fread(p,sizeof(aluno),1,p_aluno);//p é a região da memoria onde serão armazenados os dados lidos
									  //sizeof(dados)é o tamanho da unidade a ser lida,1 indica quantas devem ser lidas
									  //p_aluno é da onde os dados serão lidos
			
	    //printf("%s e %s\n",p->RA,p_ra);
	    //system("pause");
		if(strcmp(p->RA,p_ra)==0)
		  {
		  achou=i;   //posicao no arquivo
		  i=q_aluno;
	      }//if
    	}//for
    	if(achou==-1){
    		printf("RA nao cadastrado no sistema\n");
    		system("pause");
    		return achou;
		}
	fclose(p_aluno);  //DENTRO do else - abriu com rb
	}
	
	return achou;
}
int busca_ra2(aux_aluno *p,char *p_ra)
{
	int i,achou=-1,q_aluno;
	FILE *p_aluno=NULL;

	q_aluno=quantidade();
	system("cls");
	
	//printf("%s e %s\n",p->RA,p_ra);
    //	system("pause");
	
	
	if((p_aluno=fopen("aluno.bin","rb"))==NULL)
	  {
	  }
	else{
		
		for(i=0;i<q_aluno;i++)
    	{
	    	
		fseek(p_aluno,i*sizeof(aluno),0);//posiciona no inicio do arquivo e pula estruturas de acordo com i
		fread(p,sizeof(aluno),1,p_aluno);//p é a região da memoria onde serão armazenados os dados lidos
									  //sizeof(dados)é o tamanho da unidade a ser lida,1 indica quantas devem ser lidas
									  //p_aluno é da onde os dados serão lidos
			
	    //printf("%s e %s\n",p->RA,p_ra);
	    //system("pause");
		if(strcmp(p->RA,p_ra)==0)
		  {
		   printf("\nRA ja cadastrado\n");
		   system("pause");
		  achou=i;   //posicao no arquivo
		  i=q_aluno;
	      }//if
    	}//for
    	if(achou==-1){
    		//printf("RA nao cadastrado no sistema\n");
    		//system("pause");
    		return achou;
		}
	fclose(p_aluno);  //DENTRO do else - abriu com rb
	}
	
	return achou;
}
// CADASTRO E PESQUISA DE LIVROS
void aloca_livro(livro **p,int tamanho)
{
	if((*p =(livro *)realloc(*p,tamanho*sizeof(livro)))==NULL){
		printf("erro na alocação\n");
		exit(1);
	}
}
void cadastro_livro(livro *pl)
{
	int i,j,num_reg=0;
	
	do{
	system("cls");
	printf("\nNome do livro:\n");
	gets(pl->titulo);
	fflush(stdin);
	
	printf("\nAutor:\n");
	gets(pl->autor);
	fflush(stdin);
	
	if(strcmp(pl->titulo,"")==0||strcmp(pl->autor,"")==0){
		printf("\nTitulo ou Autor nao digitado\n");
		system("pause");
	}
    }while(strcmp(pl->titulo,"")==0||strcmp(pl->autor,"")==0);
	
	
	num_reg=verifica_livro();

	num_reg++;

	pl->reg=num_reg;

	for(i=0;i<2;i++)
	{
//(pl->status+i)->mes_dev

			if(i== 0){
			
			(pl->status+i)->sigla='L';
			
			strcpy((pl->status+i)->RA,"0");
			
			(pl->status+i)->dia_ret=0;
			(pl->status+i)->mes_ret=0;
			(pl->status+i)->dia_dev=0;
			(pl->status+i)->mes_dev=0;
		}else{
			(pl->status+i)->sigla='-';
			
			strcpy((pl->status+i)->RA,"---");
			(pl->status+i)->dia_ret=0;
			(pl->status+i)->mes_ret=0;
			(pl->status+i)->dia_dev=0;
			(pl->status+i)->mes_dev=0;
		}
	}
	  
	grava_livro(pl,"ab",1);
}

int verifica_livro()
{
	long int cont=0;
	FILE *file_p=NULL;
	
	if((file_p=fopen("livros.bin","rb"))==NULL)//tenta abrir um arquivo chamado "aluno.bin,rb=read binary
	                                          //file_p vai receber o resultado de fopen
	return cont;                            //retorna 0 caso o arquivo não foi encontrado
	
	else
	  {
	  fseek(file_p,0,2);  //posiciona no fim do arquivo; fseek(ponteiro pra FILE,numero de bites para pular,origem onde o ponteiro vai ser posicionado)
	                    //origem origem 0=inicio do arquivo,origem 1=ponto atual do arquivo,origem 2 fim do arquivo
	                    
	  cont=ftell(file_p)/sizeof(livro);   //qtde de elementos;ftell retorna o numero de bytes desde o começo do arquivo
	  fclose(file_p);    //dentro do ELSE por conta do rb
	  return cont; //retorna a quantidade de estruturas de livro já existentes no arquivo
	  }//else
}//verifica

void imprime_livro(livro *p)
{
	int i,q_livro,tab,achou=-1,j;
	FILE *p_livro=NULL;
	
	q_livro=verifica_livro();//verifica retorna a quantidade de estruturas dentro do arquivo
	//printf(" numero de livros %i",q_livro);
	
	system("cls");
	
	if((p_livro=fopen("livros.bin","rb"))==NULL)
  	printf("\nErro ao abrir o arquivo\n");
  	
  	else
  	{
	  	for(i=0;i<q_livro;i++)
	    {
	    	
			fseek(p_livro,i*sizeof(livro),0);//se posiciona no inicio do arquivo e vai pulando as estruturas de acordo com i
			fread(p,sizeof(livro),1,p_livro);//p é a região da memoria onde serão armazenados os dados lidos
										  //sizeof(dados)é o tamanho da unidade a ser lida,1 indica quantas devem ser lidas
										  //fptr é da onde os dados serão lidos
			printf("--------------");
			printf("\nRegistro:%i \nTitulo:%s \nAutor:%s \n",p->reg,p->titulo,p->autor);
			
			
			for(j=0;j<2;j++)
			{
				if(((p->status+j)->sigla)=='E' || (((p->status+j)->sigla)=='R' )){
				
				printf("\nStatus[%i]:%c \nRA:%s \nRet:%i/%i \nDev:%i/%i \n\n",j+1,(p->status+j)->sigla,(p->status+j)->RA,(p->status+j)->dia_ret,(p->status+j)->mes_ret,(p->status+j)->dia_dev,(p->status+j)->mes_dev);	//p->tabela[0].sigla
			}
			}
		
	    }//for
		fclose(p_livro);
	}//imprimir todos
	system("pause");
}

void grava_livro(livro *p,char *str,int pos)
{
	FILE *file_p=NULL;

	if((file_p=fopen("livros.bin",str))==NULL)	
  	printf("\nErro ao abrir o arquivo\n");
  	
  	else
  	{
  	if(strcmp(str,"rb+")==0)//*if sem chaves só é valido para proxima instrução
    fseek(file_p,pos*sizeof(livro),0);
    
  	fwrite(p,sizeof(livro),1,file_p);//p é a região da memoria onde estão os dados  
								   //sizeof(dados)é o tamanho da unidade a ser escrita,1 indica quantas devem ser escritas
								   //file_p é da onde os dados serão escritos
  	
  	}//else
  	
	fclose(file_p);		//fora do ELSE por conta do ab ou rb+
}



void verifica_sigla(livro *p,char *ra)
{
	int aux,j,erro,i[4]={4,6,9,11},*p_i,k,i2[7]={1,3,5,7,8,10,12},*p_i2;//i é um vetor para diminuir o numero de if do código
	p_i=i;
	p_i2=i2;
	
	
	for(j=0;j<2;j++)//for para vasculhar os dois status
	{ 
				
				
				if(((p->status+j)->sigla)=='E')
				{
					
					((p->status+j+1)->sigla)='R';
					strcpy((p->status+j+1)->RA,ra);	
			        
			        
			        ((p->status+j+1)->dia_ret)=((p->status+j)->dia_dev)+1;
			        
			        
			        //dev=20/3 dia_ret=21/3
			        
			        
			        
			        for(k=0;k<4;k++)
					{
			        if(((p->status+j)->mes_dev)==*(p_i+k) && ((p->status+j)->dia_dev) <30){
			        	
			        	((p->status+j+1)->mes_ret)=((p->status+j)->mes_dev);
					}
					else if(((p->status+j)->mes_dev)==*(p_i+k) && ((p->status+j)->dia_dev) ==30){
			        	
			        	((p->status+j+1)->mes_ret)=((p->status+j)->mes_dev)+1;
					}
				}
					
					
					for(k=0;k<7;k++)
					{
					 if(((p->status+j)->mes_dev)==*(p_i2+k) && ((p->status+j)->dia_dev) <31){
			        	
			        	((p->status+j+1)->mes_ret)=((p->status+j)->mes_dev);
					}
					else if(((p->status+j)->mes_dev)==*(p_i2+k) && ((p->status+j)->dia_dev) ==31){
			        	
			        	((p->status+j+1)->mes_ret)=((p->status+j)->mes_dev)+1;
					}
				}
					
					
					if(((p->status+j)->mes_dev)==2 && ((p->status+j)->dia_dev) <28){
			        	
			        	((p->status+j+1)->mes_ret)=((p->status+j)->mes_dev);
					}
					else if(((p->status+j)->mes_dev)==2 && ((p->status+j)->dia_dev) ==28){
			        	
			        	((p->status+j+1)->mes_ret)=((p->status+j)->mes_dev)+1;
					}
				
					
			        
			        
					
					
				
					
					for(k=0;k<4;k++)
					{//for para mes e dia e devolução
						
					if(((p->status+j+1)->mes_ret)==*(p_i+k) && (p->status+j+1)->dia_ret >23)
					{
						aux=0;
						aux=((p->status+j+1)->dia_ret)+7;//soma +7 ao dia de retirada ex 25+7
						aux-=30;//subtrai do total de dias para saber que dia deverá devolver
						((p->status+j+1)->dia_dev)=aux;
						(p->status+j+1)->mes_dev=((p->status+j+1)->mes_ret)+1;
					}
					else if(((p->status+j+1)->mes_ret)==*(p_i+k) && (p->status+j+1)->dia_ret <23)
					{
							((p->status+j+1)->dia_dev)=((p->status+j+1)->dia_ret)+7;
							
							(p->status+j+1)->mes_dev=((p->status+j+1)->mes_ret);
					}					
					}//fim do for para os meses com 30 dias
					for(k=0;k<7;k++)
					{
						if(((p->status+j+1)->mes_ret)==*(p_i2+k) && (p->status+j+1)->dia_ret >24)
						{
							aux=0;
							aux=((p->status+j+1)->dia_ret)+7;//soma +7 ao dia de retirada ex 25+7
							aux-=31;//subtrai do total de dias para saber que dia deverá devolver
						((p->status+j+1)->dia_dev)=aux;
						(p->status+j+1)->mes_dev=((p->status+j+1)->mes_ret)+1;
						}
						else if(((p->status+j+1)->mes_ret)==*(p_i2+k) && (p->status+j+1)->dia_ret <24)
						{
							((p->status+j+1)->dia_dev)=((p->status+j+1)->dia_ret)+7;
							(p->status+j+1)->mes_dev=((p->status+j+1)->mes_ret);
						}
					}//fim do for para os meses com 31 dias 
					
					if(((p->status+j+1)->mes_ret)==2 && (p->status+j+1)->dia_ret >21)
					{
						aux=0;
						aux=((p->status+j+1)->dia_ret)+7;//soma +7 ao dia de retirada ex 25+7
						aux-=28;//subtrai do total de dias para saber que dia deverá devolver
						((p->status+j+1)->dia_dev)=aux;
						(p->status+j+1)->mes_dev=((p->status+j+1)->mes_ret)+1;
						
					}else if(((p->status+j+1)->mes_ret)==2 && (p->status+j+1)->dia_ret <21)
					{
							((p->status+j+1)->dia_dev)=((p->status+j+1)->dia_ret)+7;
							(p->status+j+1)->mes_dev=((p->status+j+1)->mes_ret);
					}
					//fim do if e do else para fevereiro
					
					//começar os dados do aluno
					
					
					return;
				}
				
				else if(((p->status+j)->sigla)=='L')//verifica se é igual a L
				{
					((p->status+j)->sigla)='E';
					strcpy((p->status+j)->RA,ra);	
			        
					do{
					erro=0;
					system("cls");
					
					
					
										
					printf("\nDia de retirada\n(1-31)");
					scanf("%i",&(p->status+j)->dia_ret);
					fflush(stdin);
					
					printf("\nMes de retirada(1-12)\n");
					scanf("%i",&(p->status+j)->mes_ret);
					fflush(stdin);
					
					for(k=0;k<4;k++)
					{
					
					if(((p->status+j)->mes_ret)==*(p_i+k) && ((p->status+j)->dia_ret)>30 ){
						erro=1;
						printf("\nDia invalido\n");
						system("pause");
					}
					}
					for(k=0;k<7;k++)
					{
						if(((p->status+j)->mes_ret)==*(p_i2+k) && ((p->status+j)->dia_ret)>31 )
						{
						erro=1;
						printf("\nDia invalido\n");
						system("pause");
						}
					}
					
			
					if(((p->status+j)->dia_ret)<1 ){
						erro=1;
						printf("\nDia invalido\n");
						system("pause");
					}
					
					
					else if((p->status+j)->mes_ret >12 || (p->status+j)->mes_ret <1){
					
						erro=1;
						printf("\nMes invalido\n");
						system("pause");
				    }
				    else if(((p->status+j)->mes_ret)==2 && ((p->status+j)->dia_ret)>28 ){
						erro=1;
						printf("\nDia invalido\n");
						system("pause");
					}
					
				    }while(erro==1);
				
					
					for(k=0;k<4;k++)
					{//for para mes e dia e devolução
						
					if(((p->status+j)->mes_ret)==*(p_i+k) && (p->status+j)->dia_ret >23)
					{
						aux=0;
						aux=((p->status+j)->dia_ret)+7;//soma +7 ao dia de retirada ex 25+7
						aux-=30;//subtrai do total de dias para saber que dia deverá devolver
						((p->status+j)->dia_dev)=aux;
						(p->status+j)->mes_dev=((p->status+j)->mes_ret)+1;
					}
					else if(((p->status+j)->mes_ret)==*(p_i+k) && (p->status+j)->dia_ret <23)
					{
							((p->status+j)->dia_dev)=((p->status+j)->dia_ret)+7;
							
							(p->status+j)->mes_dev=((p->status+j)->mes_ret);
					}					
					}//fim do for para os meses com 30 dias
					for(k=0;k<7;k++)
					{
						if(((p->status+j)->mes_ret)==*(p_i2+k) && (p->status+j)->dia_ret >24)
						{
							aux=0;
							aux=((p->status+j)->dia_ret)+7;//soma +7 ao dia de retirada ex 25+7
							aux-=31;//subtrai do total de dias para saber que dia deverá devolver
						((p->status+j)->dia_dev)=aux;
						(p->status+j)->mes_dev=((p->status+j)->mes_ret)+1;
						}
						else if(((p->status+j)->mes_ret)==*(p_i2+k) && (p->status+j)->dia_ret <24)
						{
							((p->status+j)->dia_dev)=((p->status+j)->dia_ret)+7;
							(p->status+j)->mes_dev=((p->status+j)->mes_ret);
						}
					}//fim do for para os meses com 31 dias 
					 if(((p->status+j)->mes_ret)==2 && (p->status+j)->dia_ret >21)
					{
						aux=0;
						aux=((p->status+j)->dia_ret)+7;//soma +7 ao dia de retirada ex 25+7
						aux-=28;//subtrai do total de dias para saber que dia deverá devolver
						((p->status+j)->dia_dev)=aux;
						(p->status+j)->mes_dev=((p->status+j)->mes_ret)+1;
						
					}else if(((p->status+j)->mes_ret)==2 && (p->status+j)->dia_ret <21)
					{
							((p->status+j)->dia_dev)=((p->status+j)->dia_ret)+7;
							(p->status+j)->mes_dev=((p->status+j)->mes_ret);
					}
					//fim do if e do else para fevereiro
					
					//começar os dados do aluno
					return;
				}//fim do if do L
				
				
				
				
				
 }//fim do for
}


int busca_titulo(livro *p,char *pesquisa,int op,char *ra,aluno *a)
{
	int i,achou=-1,q_livro,j,k,pos,erro=0,aux=0,existe=0;
	
	char sigla='L',*p_sigla;
	
	p_sigla=&sigla;
	
	FILE *p_livro=NULL;

	q_livro=verifica_livro();
	system("cls");
	
	
	
	
	
	if((p_livro=fopen("livros.bin","rb"))==NULL)
	  printf("\nErro\n\n");
	else{
		
		for(i=0;i<q_livro;i++)
    	{
	    	
		fseek(p_livro,i*sizeof(livro),0);//posiciona no inicio do arquivo e pula estruturas de acordo com i
		fread(p,sizeof(livro),1,p_livro);//p é a região da memoria onde serão armazenados os dados lidos
									  //sizeof(dados)é o tamanho da unidade a ser lida,1 indica quantas devem ser lidas
									  //p_aluno é da onde os dados serão lidos
									  
		if(op == 0)
		{
			if(strcmp(p->titulo,pesquisa)==0)
			
			{
				existe=1;
				return existe;
			}
			
		}
		if(op == 1)
		{
			if(strcmp(p->titulo,pesquisa)==0)
			{
				printf("\nRA:%s \nDev:%i/%i \n ",(p->status+1)->RA,(p->status+1)->dia_dev,(p->status+1)->mes_dev);
				
			}
		}
		if(op == 2)
		{
			
			
			if(strcmp(p->titulo,pesquisa)==0 && (p->status)->sigla == 'E' && (p->status+1)->sigla != 'R')//verificar se O SEGUNDO STATUS ESTÁ COM R
			{
				
				//fisica E
				//fisica L
				
				verifica_sigla(p,ra);
				
				//muda status do livro para E + RA + data retirada + data devolução
				grava_livro(p,"rb+",i);
				
				
				
				altera_aluno(a,ra,&p->reg,2);//altera e grava o aluno
				
				return;
			}
		}
		if(op == 3)
		{
			
			if(strcmp(p->titulo,pesquisa)==0 && (p->status)->sigla == 'L')
			{
				//fisica E
				//fisica L
				
				verifica_sigla(p,ra);
				
				//muda status do livro para E + RA + data retirada + data devolução
				grava_livro(p,"rb+",i);
				
				
				
				altera_aluno(a,ra,&p->reg,3);//altera e grava o aluno
				
				return;
			}
		}
		if(op == 4)
		{
			
			//pesquisa e imprime o titulo
			if(strcmp(p->titulo,pesquisa)==0){
				
				printf("\nRegistro:%i \nTitulo:%s \nAutor:%s  \n",p->reg,p->titulo,p->autor);
		
			
			for(j=0;j<2;j++)
			{
				if(((p->status+j)->sigla)=='E'||((p->status+j)->sigla)=='R')
				{
				
				printf("\nStatus[%i]:%c \nRA:%s \nRet:%i/%i \nDev:%i/%i \n\n",j+1,(p->status+j)->sigla,(p->status+j)->RA,(p->status+j)->dia_ret,(p->status+j)->mes_ret,(p->status+j)->dia_dev,(p->status+j)->mes_dev);	//p->tabela[0].sigla
							
			}
			}
				
			}
		}
		if(op == 5)
		{
			//pesquisa status
			
			
		for(k=0;k<2;k++)
		{
			
			if((p->status+k)->sigla == *pesquisa){
			
				printf("\nRegistro:%i \nTitulo:%s \nAutor:%s \n",p->reg,p->titulo,p->autor);
			
			
			for(j=0;j<2;j++)
			{
				if(((p->status+j)->sigla)=='E'||((p->status+j)->sigla)=='R'){
				
				printf("\nStatus[%i]:%c \nRA:%s \nRet:%i/%i \nDev:%i/%i \n\n",j+1,(p->status+j)->sigla,(p->status+j)->RA,(p->status+j)->dia_ret,(p->status+j)->mes_ret,(p->status+j)->dia_dev,(p->status+j)->mes_dev);	//p->tabela[0].sigla
			}
			}
				
			}
			
		}//for = 2 verifica os dois status de cada livro e imprime caso seja igual a L
		
		}//if op 5
			
    	}//for
		}//ELSE
	
	fclose(p_livro);  //DENTRO do else - abriu com rb
	system("pause");
}
void altera_aluno(aluno *a,char *ra,int *reg,int op)
{
	int i,q_aluno,j;
	
	FILE *p_aluno=NULL;

	q_aluno=quantidade();
	system("cls");
	
	
	if((p_aluno=fopen("aluno.bin","rb"))==NULL)
	  printf("\nErro\n\n");
	else{
		
		for(i=0;i<q_aluno;i++)
    	{
	    	
		fseek(p_aluno,i*sizeof(aluno),0);//posiciona no inicio do arquivo e pula estruturas de acordo com i
		fread(a,sizeof(aluno),1,p_aluno);
		
		
		
		if(strcmp(a->RA,ra)==0 && op ==3)//MUDAR L PARA E
		  {
		  a->emprestado++;
		
		  for(j=0;j<4;j++)
		  {
		  	if(((a->tabela+j)->sigla)=='L')
			  {
		  		((a->tabela+j)->sigla)='E';
		  		((a->tabela+j)->reg)=*reg;
		  		grava(a,"rb+",i);
		  		return;
			  }
		  }
	      }//if
		else if(strcmp(a->RA,ra)==0 && op ==2)
		{
			a->reservado++;
		
		  for(j=0;j<4;j++)
		  {
		  	if(((a->tabela+j)->sigla)=='L')
			  {
		  		((a->tabela+j)->sigla)='R';
		  		((a->tabela+j)->reg)=*reg;
		  		grava(a,"rb+",i);
		  		return;
			  }
		  }
		}
		
	    }
	}
}
// EMPRESTIMO DE LIVRO
void emprestar(livro *p,aluno *a)
{
	
	char *p_ra,ra[7],titulo[7],*p_titulo;
	int res,qtd,reserv,aux;
	
	p_titulo=titulo;
	p_ra=ra;
	
	do{
	system("cls");
	printf("\nPara voltar a tela anterior coloque o ra como 0\n");
	printf("\nDigite seu RA:\n");
	gets(ra);
	if(strcmp(ra,"0")==0)
		return;
	
	res=busca_ra(a,ra);
    }while(res==-1);
	
	
	
	
	qtd=(a->emprestado+res);//foi feito isso para ter como comparar nas linhas de baixo
	reserv=(a->reservado+res);
	
	
	
	
	if((a->emprestado)<3){//verifica se pode pegar mais um livro
	
	printf("\nDigite o titulo do livro:\n");
	gets(p_titulo);
	aux=busca_titulo(p,p_titulo,0,p_ra,a);
	
	if(aux==0){
		printf("\nlivro nao existe\n");
		system("pause");
		return;
	}
	
	busca_titulo(p,p_titulo,3,p_ra,a);//verifica se existe algum livro L se existir altera as informaçoes de livro e aluno e grava nos arquivos
	
	
	}else{
		printf("\nVoce ja esta com 3 livros,nao e possivel pegar outro  emprestado,digite um livro para reservar.\n");
		system("pause");
		system("cls");
		
		printf("\nDigite o titulo do livro:\n");
		gets(p_titulo);
		aux=busca_titulo(p,p_titulo,0,p_ra,a);
	
		if(aux==0){
			printf("\nlivro nao existe\n");
			system("pause");
			return;
		}
		busca_titulo(p,p_titulo,2,p_ra,a);
		
		if(reserv==(a->reservado))//pesquisa por livros emprestados e cria uma reserva
			{
			
				printf("\n---Esse livro ja esta reservado---\n");
				system("pause");
				busca_titulo(p,p_titulo,1,p_ra,a);
				
			}
	}

	if((a->reservado)<1)
	{
		if(qtd==(a->emprestado))//pesquisa por livros emprestados e cria uma reserva
		{
			
			printf("\nO livro \"%s\" nao esta Disponivel para emprestimo\nverificando se e possivel reservar...\n\n",p_titulo);
			system("pause");
			busca_titulo(p,p_titulo,2,p_ra,a);
			
			if(reserv==(a->reservado))//pesquisa por livros emprestados e cria uma reserva
			{
			
				printf("\n---Esse livro ja esta reservado---\n");
				system("pause");
				busca_titulo(p,p_titulo,1,p_ra,a);
				
			}
			
		}	
	}	
	
		
}







