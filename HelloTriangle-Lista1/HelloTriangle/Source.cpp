/* Hello Triangle - c�digo adaptado de https://learnopengl.com/#!Getting-started/Hello-Triangle 
 *
 * Adaptado por Rossana Baptista Queiroz
 * para a disciplina de Processamento Gr�fico - Unisinos
 * Vers�o inicial: 7/4/2017
 * �ltima atualiza��o em 14/08/2023
 *
 */

#include <iostream>
#include <string>
#include <assert.h>
#include <math.h>


using namespace std;

//Classe para manipula��o dos shaders
#include "Shader.h"

// Prot�tipo da fun��o de callback de teclado
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Prot�tipos das fun��es
int setupGeometry();

// Dimens�es da janela (pode ser alterado em tempo de execu��o)
const GLuint WIDTH = 800, HEIGHT = 600;

// Fun��o MAIN
int main()
{
	// Inicializa��o da GLFW
	glfwInit();

	// Cria��o da janela GLFW
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Ola Triangulo! -- Vitor Soares", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// Fazendo o registro da fun��o de callback para a janela GLFW
	glfwSetKeyCallback(window, key_callback);

	// GLAD: carrega todos os ponteiros d fun��es da OpenGL
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;

	}

	// Obtendo as informa��es de vers�o
	const GLubyte* renderer = glGetString(GL_RENDERER); /* get renderer string */
	const GLubyte* version = glGetString(GL_VERSION); /* version as a string */
	cout << "Renderer: " << renderer << endl;
	cout << "OpenGL version supported " << version << endl;

	// Definindo as dimens�es da viewport com as mesmas dimens�es da janela da aplica��o
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);


	// Compilando e buildando o programa de shader
	Shader shader("../shaders/helloTriangle.vs", "../shaders/helloTriangle.fs");

	// Gerando um buffer simples, com a geometria de um tri�ngulo
	GLuint VAO = setupGeometry();
	
	GLint colorLoc = glGetUniformLocation(shader.ID, "inputColor");
	
	shader.Use();
	
	// Loop da aplica��o - "game loop"
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //cor de fundo
		glClear(GL_COLOR_BUFFER_BIT);

		glLineWidth(5);
		glPointSize(20);

		glBindVertexArray(VAO); //Conectando ao buffer de geometria

		//Exerc�cio 5.a (Tri�ngulo preenchido)
		//glUniform4f(colorLoc, 0.0f, 0.0f, 1.0f, 1.0f);
		//glDrawArrays(GL_TRIANGLES, 0, 6);

		//Exerc�cio 5.C (Tri�ngulo com pontos)
		//glUniform4f(colorLoc, 1.0f, 0.5f, 0.0f, 1.0f);
		//glDrawArrays(GL_LINE_LOOP, 0, 6);

		//Exerc�cio 5.b (Tri�ngulo contornado)
		//glUniform4f(colorLoc, 1.0f, 1.0f, 1.0f, 1.0f);
		//glDrawArrays(GL_POINTS, 0, 6);

		//Exerc�cio 5.D pronto junto

		//Exerc�cio 6 e 7
		glUniform4f(colorLoc, 1.0f, 0.5f, 0.0f, 1.0f);
		glDrawArrays(GL_LINE_LOOP, 0, 100);

		glBindVertexArray(0); //Desconectando o buffer de geometria

		// Troca os buffers da tela
		glfwSwapBuffers(window);
	}
	// Pede pra OpenGL desalocar os buffers
	glDeleteVertexArrays(1, &VAO);
	// Finaliza a execu��o da GLFW, limpando os recursos alocados por ela
	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

//Exerc�cio 5
//int setupGeometry()
//{
//	GLfloat vertices[] = {
//		//x   y     z
//		-0.5,  0.9, 0.0, //v0
//		 0.0,  0.0, 0.0, //v1
// 		 0.5,  0.9, 0.0, //v2 
//		-0.5, -0.9, 0.0, //v1
//		 0.0,  0.0, 0.0, //v4
//		 0.5, -0.9, 0.0, //v2
//	};


int setupGeometry()
{
	//Exerc�cio 6 (C�rculo) = num_segments = 100
	//Exerc�cio 6-A (Oct�gono) = num_segments = 8
	//Exerc�cio 6-B (Pent�gono) = num_segments = 5
	const int num_segments = 100;// n�mero de segmentos usados para desenhar o c�rculo
	GLfloat vertices[3 * (num_segments + 1)]; // array para armazenar os v�rtices do c�rculo
	
	//Exerc�cio 6 - do c�rculo 
	for (int i = 0; i <= num_segments; ++i) {
		float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
		vertices[i * 3] = cosf(theta);
		vertices[i * 3 + 1] = sinf(theta);
		vertices[i * 3 + 2] = 0;
	}
	
	//Exerc�cio 7
	//for (int i = 0; i <= num_segments; ++i) {
		//float theta = 4.0f * 3.1415926f * float(i) / float(num_segments); // �ngulo atual
		//vertices[i * 3] = 0.1 * theta * cosf(theta); // coordenada x
		//vertices[i * 3 + 1] = 0.1 * theta * sinf(theta); // coordenada y
		//vertices[i * 3 + 2] = 0; // coordenada z
	//}

	GLuint VBO, VAO;
	//Gera��o do identificador do VBO
	glGenBuffers(1, &VBO);
	//Faz a conex�o (vincula) do buffer como um buffer de array
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//Envia os dados do array de floats para o buffer da OpenGl
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//Gera��o do identificador do VAO (Vertex Array Object)
	glGenVertexArrays(1, &VAO);
	// Vincula (bind) o VAO primeiro, e em seguida  conecta e seta o(s) buffer(s) de v�rtices
	// e os ponteiros para os atributos 
	glBindVertexArray(VAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0); 

	// Desvincula o VAO (� uma boa pr�tica desvincular qualquer buffer ou array para evitar bugs medonhos)
	glBindVertexArray(0); 

	return VAO;
}

