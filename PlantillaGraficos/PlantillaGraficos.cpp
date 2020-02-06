// PlantillaGraficos.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define GLEW_STATIC

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>

using namespace std;

// Declarar una ventana
GLFWwindow* window;
float posXTriangulo = 0.0f, posYTriangulo = 0.0f;
float anguloTriangulo = 0.0f;
double tiempoActual, tiempoAnterior;
double velocidadTriangulo = 0.8;
double velocidadRotacion = 50.0;

void teclado_callback(GLFWwindow *window, int key, int scancode,
	int action, int mods) {
	if (action == GLFW_PRESS || action == GLFW_REPEAT && key == GLFW_KEY_RIGHT) {
		posXTriangulo += 0.01;
	}

	if (action == GLFW_PRESS || action == GLFW_REPEAT && key == GLFW_KEY_LEFT) {
		posXTriangulo -= 0.01;
	}

	if (action == GLFW_PRESS || action == GLFW_REPEAT && key == GLFW_KEY_UP) {
		posYTriangulo += 0.01;
	}

	if (action == GLFW_PRESS || action == GLFW_REPEAT && key == GLFW_KEY_DOWN) {
		posYTriangulo -= 0.01;
	}
}

void actualizar() {
	tiempoActual = glfwGetTime();
	double tiempoDiferencial = tiempoActual - tiempoAnterior;

	int estadoDerecha = glfwGetKey(window, GLFW_KEY_RIGHT);
	int estadoIzquierda = glfwGetKey(window, GLFW_KEY_LEFT);
	int estadoArriba = glfwGetKey(window, GLFW_KEY_UP);
	int estadoAbajo = glfwGetKey(window, GLFW_KEY_DOWN);

	if (estadoDerecha == GLFW_PRESS) {
		anguloTriangulo -= velocidadRotacion * tiempoDiferencial;
		if (anguloTriangulo <= -360.0f) {
			anguloTriangulo = 0;
		}
	}
	if (estadoIzquierda == GLFW_PRESS) {
		anguloTriangulo += velocidadRotacion * tiempoDiferencial;
		if (anguloTriangulo >= 360.0f) {
			anguloTriangulo = 0;
		}
	}
	if (estadoArriba == GLFW_PRESS) {
		double anguloARadianes = (anguloTriangulo + 90.0) * (3.14159 / 180.0);

		posXTriangulo += velocidadTriangulo * cos(anguloARadianes) * tiempoDiferencial;
		posYTriangulo += velocidadTriangulo * sin(anguloARadianes) * tiempoDiferencial;

		if (posXTriangulo <= -1.08) {
			posXTriangulo = 1.00;
		}
		else if (posXTriangulo >= 1.08) {
			posXTriangulo = -1.00;
		}

		if (posYTriangulo <= -1.08) {
			posYTriangulo = 1.00;
		}
		else if (posYTriangulo >= 1.08) {
			posYTriangulo = -1.00;
		}
	}

	tiempoAnterior = tiempoActual;
}

void dibujar() {
	glPushMatrix();
	glTranslatef(posXTriangulo, posYTriangulo, 0.0f);
	glRotatef(anguloTriangulo, 0.0f, 0.0f, 1.0f);
	glScalef(0.4f, 0.7f, 0.7f);
	
	glBegin(GL_TRIANGLES);

	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.15f, 0.0f);
	glVertex3f(0.15f, -0.15f, 0.0f);
	glVertex3f(-0.15f, -0.15f, 0.0f);

	glEnd();
	glPopMatrix();
}

int main() {
	// Si no se pudo iniciar GLFW
	// Terminamos ejecución
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}

	// Si se pudo iniciar GLFW
	// Inicializamos la ventana
	//window = glfwCreateWindow(1500, 600, "Ventana", NULL, NULL);
	window = glfwCreateWindow(600, 600, "Ventana", NULL, NULL);

	// Si no se pudo crear la ventana
	// Terminamos la ejecución
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	// Establecemos la ventana como contexto
	glfwMakeContextCurrent(window);

	// Una vez establecido el contexto se activan las funciones "modernas" (gpu)
	glewExperimental = true;

	GLenum errores = glewInit();
	if (errores != GLEW_OK) {
		glewGetErrorString(errores);
	}

	const GLubyte *versionGL = glGetString(GL_VERSION);
	cout << "Version OpenGL: " << versionGL;

	// Establecemos que con cada evento de teclado se llama
	// a la función teclado_callback
	//glfwSetKeyCallback(window, teclado_callback);

	tiempoActual = glfwGetTime();
	tiempoAnterior = tiempoActual;

	// Ciclo de dibujo (Draw loop)
	while (!glfwWindowShouldClose(window)) {
		// Establecer región de dibujo
		//glViewport(0, 0, 1500, 600);
		glViewport(0, 0, 600, 600);
		// Establecemos el color de borrado
		glClearColor(1, 1, 1, 1);
		// Borrar!
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Actualizar valores y dibujar
		actualizar();
		dibujar();

		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	// Después del ciclo de dibujo
	// Eliminamos ventana y procesos de glfwr
	glfwDestroyWindow(window);
	glfwTerminate();
}