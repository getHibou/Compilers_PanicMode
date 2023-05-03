#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>

char token;

int somas(void); // Soma e Subtra��o 
int produto(void); // Multiplica��o 
int num(void); // N�meros ou Sub-express�es

void error_Parenteses(void){ //Quando h� mais de um par�nteses ou falta um na express�o
	fprintf(stderr,"\nEst� faltando um par�ntesis na express�o\n");
}
void error_Divisao(void){ //Quando colocada, n�o permitida
	fprintf(stderr,"\nErro: Operador para divis�o n�o � permitido\n");
}
void error_Porcentagem(void){ //Quando colocada, n�o permitida
	fprintf(stderr,"\nErro: Operador para resto de divis�o n�o � permitido\n");
}
void error_EntradaChar(void){ //Quando colocada, n�o permitida
  fprintf(stderr,"\nErro: Entrada com n�mero e caractere n�o � permitido\n");
}
void error_EntradaEspecial(void){ //Quando colocado um caracter especial, n�o � permitido
  fprintf(stderr,"\nErro: Entrada com caracter especial n�o � permitido\n");
}

void match(char tokenEsperado){
	if(token == tokenEsperado){
    token = getchar();
  }else{
    error_Parenteses();
    while(!isdigit(token))  
    token = getchar();
  }
}

int main(void) {
  setlocale(LC_ALL,"Portuguese");
	int result;
  printf("\nDigite aqui a express�o: \n");
  token = getchar();
  result = somas();
  if(token == '\n'){
  	printf("\nResultado = %d\n", result);
  }else{
    if(isalpha(token)){
      error_EntradaChar();
      printf("\nResultado = %d\n", result);
    }
    if(token == '/'){
      error_Divisao();
    }
    if(token == '%'){
      error_Porcentagem();
    }
    //if(!isanum(token)){
      //error_EntradaEspecial();
    //}
  }
}

int produto(void){
	int temp = num();
	while(token == '*'){
		match('*');
		temp *= num();
	}
	return temp;
}

int somas(void){
  int temp = produto();
	while((token == '+') || (token == '-')){
		switch(token){
			case '+': 
          match('+');
					temp += produto();
					break;
			case '-': 
          match('-');
					temp -= produto();
					break;
		}
	}
  return temp;
}

int num(void){
	int temp;

	if (token == '('){
		match ('(');
		temp = somas();
		match(')');
	}else if (isdigit(token)){
		ungetc(token,stdin);
		scanf("%d", &temp);
		token = getchar();
	}
  return temp;
}
