#include <Ultrasonic.h> //inclui a biblioteca do sensor Ultrass�nico

Ultrasonic sensor_frente(8,7); //define o nome do sensor como "sensor_frente" e os pinos de trigger e echo como sendo, respectivamente, 8 e 7
Ultrasonic sensor_tras(6,5); //define o nome do sensor como "sensor_tras" e os pinos de trigger e echo como sendo, respectivamente, 6 e 5

double distancia_frente, distancia_tras; //cria vari�veis globais para armazenar as informa��es de dist�ncia dos sensores

//convencionaremos estas como sendo as entradas de controle do motor do lado esquerdo
int M1_A = 9;
int M1_B = 10;
//convencionaremos estas como sendo as entradas de controle do motor do lado direito
int M2_A = 11;
int M2_B = 12;
//portas do LED farol
int LED1_R = 2;
int LED1_G = 3;
int LED1_B = 4;
//portas do LED alerta
int LED2_R = 14;
int LED2_G = 15;
int LED2_B = 16;

void setup(){

	Serial.begin(9600); //inicializa a comunica��o serial
	pinMode(M1_A, OUTPUT);
	pinMode(M1_B, OUTPUT);
	pinMode(M2_A, OUTPUT);
	pinMode(M2_B, OUTPUT);
	pinMode(LED1_R, OUTPUT);
	pinMode(LED1_G, OUTPUT);
	pinMode(LED1_B, OUTPUT);
	pinMode(LED2_R, OUTPUT);
	pinMode(LED2_G, OUTPUT);
	pinMode(LED2_B, OUTPUT);
	//estabelece os pinos utilizados como sa�das
	Serial.println("Comunica��o iniciada!");
	//mensagem indicando in�cio da comunica��o
	for (int i = 0; i < 3; i++){
		ligaled(LED1_R, LED1_G, LED1_B);
		delay(500);
		desligaled(LED1_R, LED1_G, LED1_B);
		delay(500);
	}
	//la�o de repeti��o para fazer o LED piscar tr�s vezes

}

void loop(){

	distancia_frente = sensor_frente.Ranging(CM); //armazena na vari�vel dist�ncia a medida lida pelo sensor_frente em cent�metros
	distancia_tras = sensor_tras.Ranging(CM); //armazena na vari�vel dist�ncia a medida lida pelo sensor_tras em cent�metros

	while (Serial.available() > 0){ //enquanto houver envio de informa��es pela porta serial
		char com = Serial.read(); //declara um caractere como sendo a leitura da porta serial

		if (com == 'F'){ //caso o caractere lido seja F
			if (distancia_frente <= 30.00){ //analisa se a distancia at� um obst�culo em frente � menor ou igual a 30cm
				alertavermelho(); //acende o LED alerta na cor vermelha
				direita(); //move o rob� para a direita caso a situa��o descrita seja verdadeira
			}
			else{ //em caso de a situa��o descrita ser falsa
				alertaverde(); //acende o LED alerta na cor verde
				frente(); //move o rob� para frente
			}
		}

		if (com == 'D'){ //caso o caractere lido seja D
			alertaverde(); //acende o LED alerta na cor verde
			direita(); //executa a fun��o direita
		}

		if (com == 'E'){ //caso o caractere lido seja E
			alertaverde(); //acende o LED alerta na cor verde
			esquerda(); //executa a fun��o esquerda
		}

		if (com == 'R'){ //caso o caractere lido seja R
			if (distancia_tras <= 30.00){ //analisa se a distancia at� um obst�culo ao fundo � menor ou igual a 30cm
				alertavermelho(); //acende o LED alerta na cor vermelha
				esquerda(); //move o rob� para a esquerda caso a situa��o descrita seja verdadeira
			}
			else{ //em caso de a situa��o descrita ser falsa
				alertaverde(); //acende o LED alerta na cor verde
				re(); //move o rob� para tr�s
			}
		}

		if (com == 'L'){ //caso o caractere lido seja L
			ligaled(LED1_R, LED1_G, LED1_B); //executa a fun��o ligaled
		}
	}
}

void frente(){
//fun��o criada para enviar os sinais necess�rios para que ambos os motores girem no sentido hor�rio/para frente
	digitalWrite(M1_A, HIGH);
	digitalWrite(M1_B, LOW);
	digitalWrite(M2_A, HIGH);
	digitalWrite(M2_B, LOW);

}

void direita(){
//fun��o criada para enviar os sinais necess�rios para que os motores da esquerda girem no sentido hor�rio/para frente e os da direita girem no sentido anti-hor�rio/para tr�s
//isso far� com que o rob� gire para o lado direito
	digitalWrite(M1_A, HIGH);
	digitalWrite(M1_B, LOW);
	digitalWrite(M2_A, LOW);
	digitalWrite(M2_B, HIGH);

}

void esquerda(){
//fun��o criada para enviar os sinais necess�rios para que os motores da direita girem no sentido hor�rio/para frente e os da esquerda girem no sentido anti-hor�rio/para tr�s
//isso far� com que o rob� gire para o lado esquerdo
	digitalWrite(M1_B, HIGH);
	digitalWrite(M2_A, HIGH);
	digitalWrite(M2_B, LOW);

}

void re(){
//fun��o criada para enviar os sinais necess�rios para que ambos os motores girem no sentido anti-hor�rio/para tr�s
	digitalWrite(M1_A, LOW);
	digitalWrite(M1_B, HIGH);
	digitalWrite(M2_A, LOW);
	digitalWrite(M2_B, HIGH);

}

void ligaled(int r, int g, int b){
//fun��o criada para fazer com que o LED farol ligue na cor branca
	digitalWrite(r, HIGH);
	digitalWrite(g, HIGH);
	digitalWrite(b, HIGH);
}

void desligaled(int r, int g, int b){
//fun��o criada para fazer com que o LED farol desligue
	digitalWrite(r, LOW);
	digitalWrite(g, LOW);
	digitalWrite(b, LOW);
}

void alertaverde(){
//fun��o criada para ligar o LED alerta na cor verde
	digitalWrite(LED2_R, LOW);
	digitalWrite(LED2_G, HIGH);
	digitalWrite(LED2_B, LOW);
}

void alertavermelho(){
//fun��o criada para ligar o LED alerta na cor vermelha
	digitalWrite(LED2_R, HIGH);
	digitalWrite(LED2_G, LOW);
	digitalWrite(LED2_B, LOW);
}