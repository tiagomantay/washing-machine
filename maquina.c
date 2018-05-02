#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

int tempoLavag, tempoMolho, centrifuga, sel, nivelAgua=0,atSaiAgua=0,atEntAgua=0,cn=0;
int motor=0,opt=0,SaiAgua=0,prog=0;
int motorDir=0;
void exec(void), mostraProg(void), mostraMenu(void), mostraMotor(int);
void centrifugar(void), esvaziar(void), lavar(void), encher(void), verProg(void);
void molho(void), executar(void), programar(void);


int main(void){
	system("clear");
	opt=6;

	printf("\n\n WASHING MACHINE \n\n");
    printf("\n inicializando ... \n\n");
    sleep(1);

	while(opt!=0){
		system("clear");
		mostraMenu();
		scanf("%d",&opt);

		if(opt==1){
			printf("\n CONFIG  \n\n");
 			programar();
			opt=6;
		}

		else if(opt==2){
			if(prog!=0){

			printf("\n EXECUTE \n\n");
			executar();
			opt=6;
			} else {
				system("clear");
				printf("\n\n\t\tChoose one washing program... \n");
				sleep(2);
			}
		}
	}

	printf("\n\n\t CLOSE \n\n");
}


void mostraMenu(void){
	system("clear");
    	printf("\n\n ========================== MENU =========================== \n\n\n");
    	printf("\t Digite: \n\n\n\t 1 - PROGRAMAR \n\t 2 - EXECUTAR \n\n\t 0 - DESLIGAR \n");
    	printf("\n Escolha uma opção: \t");
}


void programar(void){
	int op;
	opt=0;
	system("clear");
	mostraProg();
	scanf("%d",&sel);
    opt=sel;

	while(opt!=0){

		if(opt==1){
			tempoLavag = 3;
			tempoMolho = 0;
			centrifuga = 3;
			opt=6;
		}

		else if(opt==2){  
			tempoLavag = 5;
        	tempoMolho = 3;
	        centrifuga = 5;
		}

		else if(opt==3){  
        	tempoLavag = 0;
       		tempoMolho = 0;
	        centrifuga = 3;
		}

		else if(opt==4){ 
			system("clear");
			printf("\n\t CUSTOMIZAR \n\n Escolha o tempo de molho:  ");
                        scanf("%d",&tempoMolho);
			printf("\n\n Escolha o tempo de lavagem:  ");
			scanf("%d",&tempoLavag);
			printf("\n\n Escolha o tempo de centrifugação:  ");
			scanf("%d",&centrifuga);
		}


		else if(opt==5){	
			system("clear");
			verProg();
			printf("\n\n\n Pressione qq coisa para sair...\n\n");
			scanf("%d",&opt);
			opt=6;
		}

		verProg();
		printf("\n\n\n\n Confirmar?  (1 - Sim     2 - Não)    ");
		scanf("%d",&op);

		if (op==1){
			prog=1;
			opt=0;
		}

		else if (op==2){
			opt=0;
			prog=0;
		}
	}
}


void executar(void){
	system("clear");
	exec();
	scanf("%d",&opt);

	while(opt==1)
	{
        encher();
		system("clear");

		molho();
		system("clear");

		lavar();
		system("clear");
		printf("\n");

		esvaziar();
		system("clear");

		centrifugar();
		system("clear");

		opt=2;

		system("clear");
		printf("\n\n PROCESSO TERMINADO ! \n");
		sleep(2);
		system("clear");
		printf("\n\n");
	}
	system("clear");
}


void molho(void){
	int m;
	system("clear");
	m=tempoMolho;
	sleep(1);

	while(m>=0){
		system("clear");
        printf("\n CICLO MOLHO >  %d s \n\n\n MOLHO... %d \n",tempoMolho,m);
        sleep(1);
		m--;
                }

	system("clear");
	printf("\n");
	sleep(1);
}


void lavar(void){

	int l;
	l=tempoLavag;

	system("clear");
	sleep(1);

	while(l>0){

		motor=1;		//LIGA MOTOR

		mostraMotor(l);

		l--;

		motor=0;		//DESLIGA MOTOR

		mostraMotor(l);

        if(motorDir==1) motorDir=0;	//MUDA DIREÇÃO DO MOTOR
		else motorDir=1;

		l--;
	}

	system("clear");

	if(l == 0) printf("\n\n Done! \n");
	sleep(2);
	system("clear");
}

void centrifugar(void){
	int c;
	c=centrifuga;
	system("clear");
	printf("\n CICLO CENTRIFUGAÇÃO >  %d s \n\n",centrifuga);

	sleep(1);

	 for(;c>=0;c--){

                printf("\n CENTRIFUGANDO... %d",c);
                motor = 1;
                motorDir = 0;
                sleep(1);
        }
	system("clear");
	printf("\n CENTRIFUGAÇÃO COMPLETA\n");
        motor = 0;
        sleep(1);
	system("clear");

}

void esvaziar(void){

	system("clear");
	printf("\n ESVAZIAR \n\n");
	sleep(1);

	for(;nivelAgua >=0 ; nivelAgua--){

		atSaiAgua=1;            //ATUADOR SAÍDA DE ÁGUA LIGADO
	        printf(" NIVEL DE ÁGUA : %d \n",nivelAgua);
        	sleep(1);

	}

	atSaiAgua=0;			//ATUADOR DE SAÍDA DE ÁGUA DESLIGADO

	system("clear");

	if(nivelAgua==0) printf("\n Máquina Vazia! \n");
	sleep(1);
}

void encher(void){
	printf("\n\n");
	system("clear");
	printf("\n ENCHENDO...\n\n\n");

        for(;nivelAgua < 5 ; nivelAgua++){

		atEntAgua=1;		//ATUADOR ENTRADA DE ÁGUA LIGADO
        	printf(" NIVEL DE ÁGUA  :  %d \n",nivelAgua);
       		sleep(1);

        }

	system("clear");

	if(nivelAgua == 5) printf("\n\n Nível de Água atingido! \n");


	atEntAgua=0;		//ATUADOR ENTRADA DE ÁGUA DESLIGADO
	sleep(1);
}

void exec(void){

	system("clear");
    printf("\n\n EXECUTAR...");
    printf("\n\n\t Executar programação ");

    if      (sel==1) printf(" NORMAL?  ");
    else if (sel==2) printf(" ROUPAS SUJAS?  ");
    else if (sel==3) printf(" CENTRIFUGAR?  ");
    else if (sel==4) printf(" Customizada?  ");
	printf("\n\n\t Confirma? \t (1 - Sim      2- Não) \n\n\t\t\t");
}

void mostraProg(void){
	system("clear");
    printf("\n\n Programar \t OPÇÕES");
    printf("\n\n\t Digite: \n\t 1 - LAVAGEM NORMAL \n\t 2 - ROUPAS SUJAS \n\t");
    printf(" 3 - CENTRIFUGAR \n\t 4 - Customizar \n\t 5 - Ver programação\n\n\t 0 - SAIR \n\n\n\n\t ");

}


void verProg(void){
	system("clear");
    printf("\n\n ==> PROGRAMAÇÃO: \n\n");
    printf("\n\n  Tempo de Molho :         %d",tempoMolho);
    printf("\n\n  Tempo de Lavagem :       %d",tempoLavag);
    printf("\n\n  Tempo de Centrifugação:  %d",centrifuga);
}


//---------------------------------FUNÇAO MOSTRA PROG-------------------------------
void mostraMotor(int l){ //recebe o tempo restante de lavagem

	system("clear");
        printf("\nCICLO LAVAGEM >  %d segundos",tempoLavag);
	printf("\n\n --------------   %d   --------------- \n\n ",l);
        printf("\n Motor = %d   ",motor);

	if(motor==1) printf("Ligado \n\n");
	else printf("Desligado \n\n");

	printf("\n Direção = %d  \n\n",motorDir);

	if(motor==1){

		if (motorDir==1) {
        	printf("\n \t\t >>>>>>>>>>>>>>>>>>>> \n");
        	printf("\n \t\t >>>>>>>>>>>>>>>>>>>> \n");
        	printf("\n \t\t >>>>>>>>>>>>>>>>>>>> \n");
        	printf("\n \t\t >>>>>>>>>>>>>>>>>>>> \n");
		} else {
			printf("\n <<<<<<<<<<<<<<<<<<<< \n");
       		printf("\n <<<<<<<<<<<<<<<<<<<< \n");
       		printf("\n <<<<<<<<<<<<<<<<<<<< \n");
       		printf("\n <<<<<<<<<<<<<<<<<<<< \n");
       		}
	} else {
        printf("\n\t #################### \n");
        printf("\n\t #################### \n");
        printf("\n\t #################### \n");
        printf("\n\t #################### \n");
        printf("\n\t #################### \n");
	}
   sleep(1);
//fim da função mostraMotor
}

