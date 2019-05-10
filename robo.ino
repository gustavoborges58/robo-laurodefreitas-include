#include <Ultrasonic.h> //inclui a biblioteca do sensor Ultrassônico

Ultrasonic sensor_frente(8,7); //define o nome do sensor como "sensor_frente" e os pinos de trigger e echo como sendo, respectivamente, 8 e 7
Ultrasonic sensor_tras(6,5); //define o nome do sensor como "sensor_tras" e os pinos de trigger e echo como sendo, respectivamente, 6 e 5

double distancia_frente, distancia_tras; //cria variáveis globais para armazenar as informações de distância dos sensores

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

	Serial.begin(9600); //inicializa a comunicação serial
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
	//estabelece os pinos utilizados como saídas
	Serial.println("Comunicação iniciada!");
	//mensagem indicando início da comunicação
	for (int i = 0; i < 3; i++){
		ligaled(LED1_R, LED1_G, LED1_B);
		delay(500);
		desligaled(LED1_R, LED1_G, LED1_B);
		delay(500);
	}
	//laço de repetição para fazer o LED piscar três vezes

}

void loop(){

	distancia_frente = sensor_frente.Ranging(CM); //armazena na variável distância a medida lida pelo sensor_frente em centímetros
	distancia_tras = sensor_tras.Ranging(CM); //armazena na variável distância a medida lida pelo sensor_tras em centímetros

	while (Serial.available() > 0){ //enquanto houver envio de informações pela porta serial
		char com = Serial.read(); //declara um caractere como sendo a leitura da porta serial

		if (com == 'F'){ //caso o caractere lido seja F
			if (distancia_frente <= 30.00){ //analisa se a distancia até um obstáculo em frente é menor ou igual a 30cm
				alertavermelho(); //acende o LED alerta na cor vermelha
				direita(); //move o robô para a direita caso a situação descrita seja verdadeira
			}
			else{ //em caso de a situação descrita ser falsa
				alertaverde(); //acende o LED alerta na cor verde
				frente(); //move o robô para frente
			}
		}

		if (com == 'D'){ //caso o caractere lido seja D
			alertaverde(); //acende o LED alerta na cor verde
			direita(); //executa a função direita
		}

		if (com == 'E'){ //caso o caractere lido seja E
			alertaverde(); //acende o LED alerta na cor verde
			esquerda(); //executa a função esquerda
		}

		if (com == 'R'){ //caso o caractere lido seja R
			if (distancia_tras <= 30.00){ //analisa se a distancia até um obstáculo ao fundo é menor ou igual a 30cm
				alertavermelho(); //acende o LED alerta na cor vermelha
				esquerda(); //move o robô para a esquerda caso a situação descrita seja verdadeira
			}
			else{ //em caso de a situação descrita ser falsa
				alertaverde(); //acende o LED alerta na cor verde
				re(); //move o robô para trás
			}
		}

		if (com == 'L'){ //caso o caractere lido seja L
			ligaled(LED1_R, LED1_G, LED1_B); //executa a função ligaled
		}
	}
}

void frente(){
//função criada para enviar os sinais necessários para que ambos os motores girem no sentido horário/para frente
	digitalWrite(M1_A, HIGH);
	digitalWrite(M1_B, LOW);
	digitalWrite(M2_A, HIGH);
	digitalWrite(M2_B, LOW);

}

void direita(){
//função criada para enviar os sinais necessários para que os motores da esquerda girem no sentido horário/para frente e os da direita girem no sentido anti-horário/para trás
//isso fará com que o robô gire para o lado direito
	digitalWrite(M1_A, HIGH);
	digitalWrite(M1_B, LOW);
	digitalWrite(M2_A, LOW);
	digitalWrite(M2_B, HIGH);

}

void esquerda(){
//função criada para enviar os sinais necessários para que os motores da direita girem no sentido horário/para frente e os da esquerda girem no sentido anti-horário/para trás
//isso fará com que o robô gire para o lado esquerdo
	digitalWrite(M1_B, HIGH);
	digitalWrite(M2_A, HIGH);
	digitalWrite(M2_B, LOW);

}

void re(){
//função criada para enviar os sinais necessários para que ambos os motores girem no sentido anti-horário/para trás
	digitalWrite(M1_A, LOW);
	digitalWrite(M1_B, HIGH);
	digitalWrite(M2_A, LOW);
	digitalWrite(M2_B, HIGH);

}

void ligaled(int r, int g, int b){
//função criada para fazer com que o LED farol ligue na cor branca
	digitalWrite(r, HIGH);
	digitalWrite(g, HIGH);
	digitalWrite(b, HIGH);
}

void desligaled(int r, int g, int b){
//função criada para fazer com que o LED farol desligue
	digitalWrite(r, LOW);
	digitalWrite(g, LOW);
	digitalWrite(b, LOW);
}

void alertaverde(){
//função criada para ligar o LED alerta na cor verde
	digitalWrite(LED2_R, LOW);
	digitalWrite(LED2_G, HIGH);
	digitalWrite(LED2_B, LOW);
}

void alertavermelho(){
//função criada para ligar o LED alerta na cor vermelha
	digitalWrite(LED2_R, HIGH);
	digitalWrite(LED2_G, LOW);
	digitalWrite(LED2_B, LOW);
}