# robo-laurodefreitas-include

* A programação descrita no código robo.ino corresponde à rotina de funcionamento de um robô feito com Arduino e controlado via comunicação serial através de pareamento Bluetooth;

**Detalhes de montagem**

* A estrutura projetada para um robô com este código consiste em um robô contendo dois sensores ultrassônicos para detecção de obstáculos (um na parte dianteira e outro na parte traseira do sistema), dois LEDs RGB (um servindo como farol e outro sendo um indicativo da detecção de obstáculos), uma ponte H e dois motores, um em cada lado;
* Durante a montagem do robô, pode se utilizar um motor em cada lado, sendo ligados à ponte H em canais individuais e comandando uma roda cada um. Nesse caso, as rodas ficariam localizadas preferencialmente na parte traseira do robô, enquanto uma roda maluca seria utilizada na parte dianteira do mesmo, apenas para guiá-lo em seu movimento;
* Pode se utilizar mais duas rodas na parte dianteira, aliadas a um motor cada, aumentando a quantidade de motores utilizados na estrutura de dois para quatro, colocando os motores de cada lado em paralelo e funcionando comandados pelo mesmo canal da ponte H, cada par. Entretanto, a depender da potência consumida pelos motores, utilizar dois deles em paralelo pode acabar ocasionando em não fornecermos a potência total necessária para o funcionamento dos mesmos em toda a sua força, fazendo com que o robô tenha perdas no desempenho;
* A ideia é que, ao ser pareado com um celular ou outro equipamento Bluetooth que permita a comunicação com o Arduino, seja possível controlar o movimento do robô (seja para frente, para trás, ou girando-o para uma direção específica) e ligar o farol do mesmo, através de botões que funcionem como teclas direcionais;
* A programação conta com ações preventivas contra choques e, consequentemente, acidentes. Realizando um movimento para frente e detectando um obstáculo de, no máximo, 30cm de distância, o robô automaticamente será movido para a direita, independente do comando enviado. Detectando um obstáculo nas mesmas condições ao realizar um movimento de ré, o robô será movido para a esquerda;

*Obs.: Visto que toda a programação foi feita por embasamento teórico, não há fotos para ilustrar a montagem.*
