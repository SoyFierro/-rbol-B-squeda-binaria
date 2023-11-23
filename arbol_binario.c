#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

struct Nodo {
    int dato;
    struct Nodo* izquierda;
    struct Nodo* derecha;
};

// Función para verificar si un árbol es un Árbol de Búsqueda Binaria (BST)
bool esArbolCorrecto(struct Nodo* raiz, int min, int max) {
    if (raiz == NULL) {
        return true;
    }

    if (raiz->dato < min || raiz->dato > max) {
        return false;
    }

    return (esArbolCorrecto(raiz->izquierda, min, raiz->dato - 1) &&
            esArbolCorrecto(raiz->derecha, raiz->dato + 1, max));
}


// funcion para crear un nuevo nodo
struct Nodo* crearNodo(int valor) {
    //Asigno en memoria para el nuevo nodo
    struct Nodo* nuevoNodo = (struct Nodo*)malloc(sizeof(struct Nodo));
    //Aqui asigno los valores al nuevo nodo
    nuevoNodo->dato = valor;
    nuevoNodo->izquierda = NULL;
    nuevoNodo->derecha = NULL;
    return nuevoNodo;
}

// funcion para insertar un nodo en el arbol de busqueda binaria
struct Nodo* insertar(struct Nodo* raiz, int valor) {
    // Si la raiz es nula creo un nuevo nodo con el valor dado
    if (raiz == NULL) {
        return crearNodo(valor);
    }

    // Si el valor es menor que el valor de la raíz inserto el dato en el sub arbol izquierdo
    if (valor < raiz->dato) {
        raiz->izquierda = insertar(raiz->izquierda, valor);
    } else if (valor > raiz->dato) {  // Si el valor es mayor que el valor de la raiz inserto el dato en el sub arbol derecho
        raiz->derecha = insertar(raiz->derecha, valor);
    }

    return raiz; //Aqui no mas devuelvo la raiz actualizada
}

// funcion para recorrer el arbol en preorden
void preorden(struct Nodo* raiz) {
    //Aqui imprimo el valor de la raiz antes de recorrer los subarboles
    if (raiz != NULL) {
        printf("%d ", raiz->dato);
        preorden(raiz->izquierda);
        preorden(raiz->derecha);
    }
}

// funcion para recorrer el arbol en inorden
void inorden(struct Nodo* raiz) {
    // Recorro los subarboles izquierdo raiz y derecho
    if (raiz != NULL) {
        inorden(raiz->izquierda);
        printf("%d ", raiz->dato);
        inorden(raiz->derecha);
    }
}

// funcion para recorrer el arbol en postorden
void postorden(struct Nodo* raiz) {
    // Recorro los subarboles izquierdo derecho y la raíz al final
    if (raiz != NULL) {
        postorden(raiz->izquierda);
        postorden(raiz->derecha);
        printf("%d ", raiz->dato);
    }
}

// funcion para buscar un nodo en el arbol
void buscarNodo(struct Nodo* raiz, int valor) {
    if (raiz == NULL) {  // Aqui si la raiz es nula el nodo no se encuentra
        printf("Nodo no encontrado\n");
        return;
    }

     // Aqui si el valor coincide con el valor de la raíz el nodo se ha encontrado
    if (valor == raiz->dato) {
        printf("Nodo encontrado\n");
        if (raiz->izquierda != NULL) { 
            printf("Nodo en izquierda: %d\n", raiz->izquierda->dato);
        } else {
            printf("No hay nodo a la izquierda\n");
        }

        if (raiz->derecha != NULL) {
            printf("Nodo en derecha: %d\n", raiz->derecha->dato);
        } else {
            printf("No hay nodo a la derecha\n");
        }

        return;
    }

    // Aqui si el valor es menor que el valor de la raiz empieza a buscar en el subarbol izquierdo
    if (valor < raiz->dato) {
        buscarNodo(raiz->izquierda, valor);
    } else {     // si el valor es mayor que el valor de la raiz busca en el subarbol derecho
        buscarNodo(raiz->derecha, valor);
    }
}

// Funcion para encontrar el nodo minimo en un arbol
struct Nodo* encontrarMinimo(struct Nodo* raiz) {
    if (raiz->izquierda != NULL) {
        return encontrarMinimo(raiz->izquierda);
    }
    return raiz;
}

// Funcion para eliminar un nodo del arbol
struct Nodo* eliminar(struct Nodo* raiz, int valor) {
    if (raiz == NULL) {
        return raiz;
    }

    if (valor < raiz->dato) {
        raiz->izquierda = eliminar(raiz->izquierda, valor);
    } else if (valor > raiz->dato) {
        raiz->derecha = eliminar(raiz->derecha, valor);
    } else {
        if (raiz->izquierda == NULL) {
            struct Nodo* temp = raiz->derecha;
            free(raiz);
            return temp;
        } else if (raiz->derecha == NULL) {
            struct Nodo* temp = raiz->izquierda;
            free(raiz);
            return temp;
        }

        struct Nodo* temp = encontrarMinimo(raiz->derecha);
        raiz->dato = temp->dato;
        raiz->derecha = eliminar(raiz->derecha, temp->dato);
    }

    return raiz;
}

// Función para insertar nodos de manera recursiva
void insertarNodos(struct Nodo** raiz, int numNodos) {
    // Aqui si hay mas nodos que insertar los inserta en caso de ser mayor a 0
    if (numNodos > 0) {
        int valor;
        printf("Ingresa el valor del nodo: ");
        scanf("%d", &valor);
        //Inserto el nodo en el arbol y actualizo la raiz
        *raiz = insertar(*raiz, valor);
        // Aqui hago una llamada recursiva para insertar los nodos restantes
        insertarNodos(raiz, numNodos - 1);
    }
}

int main() {
    struct Nodo* raiz = NULL;

    int numNodos;
    
    printf("Ingresa cuantos nodos quieres insertar: ");
    scanf("%d", &numNodos);

    // Inserto nodos en el arbol de manera recursiva
    insertarNodos(&raiz, numNodos);
    
    // Verificar si el árbol es un Árbol de Búsqueda Binaria (BST)
    if (esArbolCorrecto(raiz, INT_MIN, INT_MAX)) {
        printf("El arbol no un Arbol de Búsqueda Binaria\n");
    } else {
        printf("El arbol si es un Arbol de Busqueda Binaria\n");
    }

    printf("\nrecorrido en preorden: ");
    preorden(raiz);

    printf("\nrecorrido en inorden: ");
    inorden(raiz);

    printf("\nrecorrido en postorden: ");
    postorden(raiz);


    int valorBusqueda;
    printf("\nIngresa el valor a buscar en el arbol: ");
    scanf("%d", &valorBusqueda);
    buscarNodo(raiz, valorBusqueda);

    
    int valorEliminar;
    printf("\nIngresa el valor a eliminar del arbol: ");
    scanf("%d", &valorEliminar);
    raiz = eliminar(raiz, valorEliminar);

    
    printf("\nRecorrido en Preorden al eliminar %d: ", valorEliminar);
    preorden(raiz);

    printf("\nRecorrido en Inorden al eliminar %d: ", valorEliminar);
    inorden(raiz);

    printf("\nRecorrido en Postorden al eliminar %d: ", valorEliminar);
    postorden(raiz);

    return 0;
}
