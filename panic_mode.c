#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>

char token;

int somas(void); // Soma e Subtração 
int produto(void); // Multiplicação 
int num(void); // Números ou Sub-expressões

void error_Parenteses(void){ //Quando há mais de um parênteses ou falta um na expressão
	fprintf(stderr,"\nEstá faltando um parêntesis na expressão\n");
}
void error_Divisao(void){ //Quando colocada, não permitida
	fprintf(stderr,"\nErro: Operador para divisão não é permitido\n");
}
void error_Porcentagem(void){ //Quando colocada, não permitida
	fprintf(stderr,"\nErro: Operador para resto de divisão não é permitido\n");
}
void error_EntradaChar(void){ //Quando colocada, não permitida
  fprintf(stderr,"\nErro: Entrada com número e caractere não é permitido\n");
}
void error_EntradaEspecial(void){ //Quando colocado um caracter especial, não é permitido
  fprintf(stderr,"\nErro: Entrada com caracter especial não é permitido\n");
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
  printf("\nDigite aqui a expressão: \n");
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
