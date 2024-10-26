#include <iostream>
#include <queue> // Para recorrido por niveles
#include <conio.h>
#include <stdlib.h>

// Estructura para el nodo del árbol
struct Nodo {
    int numero;
    Nodo *izquierda;
    Nodo *derecha;
    Nodo *padre;
};

// Puntero global para el árbol
Nodo *arbol = NULL;

// Función para crear un nuevo nodo
Nodo *crear_nodo(int n, Nodo *padre) {
    Nodo *Nodo1 = new Nodo();
    Nodo1->numero = n;
    Nodo1->izquierda = NULL;
    Nodo1->derecha = NULL;
    Nodo1->padre = padre;
    return Nodo1;
}

// Función para insertar números en el árbol
void insertar_numeros(Nodo *&arbol, int n, Nodo *padre) {
    if (arbol == NULL) {
        Nodo *Nodo1 = crear_nodo(n, padre);
        arbol = Nodo1;
    } else {
        int Raiz = arbol->numero;
        if (n < Raiz) {
            insertar_numeros(arbol->izquierda, n, arbol);
        } else {
            insertar_numeros(arbol->derecha, n, arbol);
        }
    }
}

// Función para imprimir el árbol completo
void mostrar_arbol(Nodo *arbol, int contador) {
    if (arbol == NULL) {
        return;
    } else {
        mostrar_arbol(arbol->derecha, contador + 1);
        for (int i = 0; i < contador; i++) {
            std::cout << "   ";
        }
        std::cout << arbol->numero << std::endl;
        mostrar_arbol(arbol->izquierda, contador + 1);
    }
}

// Función para buscar un elemento en el árbol
bool buscar_nodo(Nodo *arbol, int elemento) {
    if (arbol == NULL) {
        return false;
    } else if (arbol->numero == elemento) {
        return true;
    } else if (elemento < arbol->numero) {
        return buscar_nodo(arbol->izquierda, elemento);
    } else {
        return buscar_nodo(arbol->derecha, elemento);
    }
}

// Función para imprimir en preOrden el árbol
void recorrido_preOrden(Nodo *arbol) {
    if (arbol == NULL) {
        return;
    } else {
        std::cout << arbol->numero << " - ";
        recorrido_preOrden(arbol->izquierda);
        recorrido_preOrden(arbol->derecha);
    }
}

// Función para imprimir en inOrden el árbol
void recorrido_inOrden(Nodo *arbol) {
    if (arbol == NULL) {
        return;
    } else {
        recorrido_inOrden(arbol->izquierda);
        std::cout << arbol->numero << " - ";
        recorrido_inOrden(arbol->derecha);
    }
}

// Función para imprimir en postOrden el árbol
void recorrido_postOrden(Nodo *arbol) {
    if (arbol == NULL) {
        return;
    } else {
        recorrido_postOrden(arbol->izquierda);
        recorrido_postOrden(arbol->derecha);
        std::cout << arbol->numero << " - ";
    }
}

// Función para recorrer el árbol por niveles
void recorrido_por_niveles(Nodo *arbol) {
    if (arbol == NULL) return;

    std::queue<Nodo *> q;
    q.push(arbol);

    while (!q.empty()) {
        Nodo *nodo_actual = q.front();
        q.pop();
        std::cout << nodo_actual->numero << " - ";

        if (nodo_actual->izquierda) {
            q.push(nodo_actual->izquierda);
        }
        if (nodo_actual->derecha) {
            q.push(nodo_actual->derecha);
        }
    }
}

// Función para encontrar el nodo más izquierdo posible
Nodo *nodo_mas_izquierdo(Nodo *arbol) {
    if (arbol == NULL) {
        return NULL;
    }
    if (arbol->izquierda) {
        return nodo_mas_izquierdo(arbol->izquierda);
    } else {
        return arbol;
    }
}

// Función para reemplazar dos nodos
void reemplazar_nodo(Nodo *arbol, Nodo *nuevo_nodo) {
    if (arbol->padre) {
        if (arbol->numero == arbol->padre->izquierda->numero) {
            arbol->padre->izquierda = nuevo_nodo;
        } else if (arbol->numero == arbol->padre->derecha->numero) {
            arbol->padre->derecha = nuevo_nodo;
        }
    }
    if (nuevo_nodo) {
        nuevo_nodo->padre = arbol->padre;
    }
}

// Función para destruir un nodo
void destruir_nodo(Nodo *nodo) {
    nodo->izquierda = NULL;
    nodo->derecha = NULL;

    delete nodo;
}

// Función para eliminar el nodo
void eliminar_nodo(Nodo *elemento) {
    if (elemento->izquierda && elemento->derecha) {
        Nodo *mas_izquiedo = nodo_mas_izquierdo(elemento->derecha);
        elemento->numero = mas_izquiedo->numero;
        eliminar_nodo(mas_izquiedo);
    } else if (elemento->izquierda) {
        reemplazar_nodo(elemento, elemento->izquierda);
        destruir_nodo(elemento);
    } else if (elemento->derecha) {
        reemplazar_nodo(elemento, elemento->derecha);
    } else {
        reemplazar_nodo(elemento, NULL);
        destruir_nodo(elemento);
    }
}

// Función para buscar el nodo a eliminar
void buscar_nodo_eliminar(Nodo *arbol, int n) {
    if (arbol == NULL) {
        return;
    } else if (n < arbol->numero) {
        buscar_nodo_eliminar(arbol->izquierda, n);
    } else if (n > arbol->numero) {
        buscar_nodo_eliminar(arbol->derecha, n);
    } else {
        eliminar_nodo(arbol);
    }
}

// Función para calcular la altura del árbol
int altura(Nodo *arbol) {
    if (arbol == NULL) {
        return -1; // Devuelve -1 para que la altura de una hoja sea 0
    }
    int alturaIzquierda = altura(arbol->izquierda);
    int alturaDerecha = altura(arbol->derecha);
    return 1 + std::max(alturaIzquierda, alturaDerecha);
}

// Función para contar los nodos
int contar_nodos(Nodo *arbol) {
    if (arbol == NULL) {
        return 0;
    }
    return 1 + contar_nodos(arbol->izquierda) + contar_nodos(arbol->derecha);
}

// Función para contar las hojas
int contar_hojas(Nodo *arbol) {
    if (arbol == NULL) {
        return 0;
    }
    if (arbol->izquierda == NULL && arbol->derecha == NULL) {
        return 1; // Es una hoja
    }
    return contar_hojas(arbol->izquierda) + contar_hojas(arbol->derecha);
}

// Función para verificar si el árbol es completo
bool es_binario_completo(Nodo *arbol, int index, int numero_nodos) {
    if (arbol == NULL) {
        return true;
    }
    if (index >= numero_nodos) {
        return false; // Si hay un nodo que no cumple la condición
    }
    return es_binario_completo(arbol->izquierda, 2 * index + 1, numero_nodos) &&
           es_binario_completo(arbol->derecha, 2 * index + 2, numero_nodos);
}

// Función para verificar si el árbol es lleno
bool es_binario_lleno(Nodo *arbol) {
    if (arbol == NULL) {
        return true;
    }
    if (arbol->izquierda == NULL && arbol->derecha == NULL) {
        return true; // Es una hoja
    }
    if (arbol->izquierda != NULL && arbol->derecha != NULL) {
        return es_binario_lleno(arbol->izquierda) && es_binario_lleno(arbol->derecha);
    }
    return false; // Si un nodo tiene un hijo pero no el otro
}

// Función para eliminar el árbol
void eliminar_arbol(Nodo *&arbol) {
    if (arbol != NULL) {
        eliminar_arbol(arbol->izquierda);
        eliminar_arbol(arbol->derecha);
        destruir_nodo(arbol);
        arbol = NULL;
    }
}

// Menú de opciones
void menu() {
    int opcion, numero, contador = 0;

    do {
        std::cout << "----- Menu -----" << std::endl;
        std::cout << "1. Insertar un numero" << std::endl;
        std::cout << "2. Mostrar el arbol completo" << std::endl;
        std::cout << "3. Buscar un numero" << std::endl;
        std::cout << "4. Recorrido preOrden" << std::endl;
        std::cout << "5. Recorrido inOrden" << std::endl;
        std::cout << "6. Recorrido postOrden" << std::endl;
        std::cout << "7. Eliminar un numero" << std::endl;
        std::cout << "8. Calcular la altura del arbol" << std::endl;
        std::cout << "9. Contar nodos del arbol" << std::endl;
        std::cout << "10. Contar hojas del arbol" << std::endl;
        std::cout << "11. Verificar si el arbol es completo" << std::endl;
        std::cout << "12. Verificar si el arbol es lleno" << std::endl;
        std::cout << "13. Eliminar el arbol completo" << std::endl;
        std::cout << "14. Recorrido por niveles" << std::endl; // Nueva opción
        std::cout << "15. Salir" << std::endl;

        std::cout << "\nIngrese la opcion que desea usar: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                std::cout << "\nIngrese un numero: ";
                std::cin >> numero;
                insertar_numeros(arbol, numero, NULL);
                std::cout << "\n";
                system("pause");
                break;
            case 2:
                std::cout << "\nMostrando el arbol completo:\n\n";
                mostrar_arbol(arbol, contador);
                std::cout << "\n";
                system("pause");
                break;
            case 3:
                std::cout << "\nIngrese el numero que desea buscar: ";
                std::cin >> numero;
                if (buscar_nodo(arbol, numero) == true) {
                    std::cout << "\nEl numero " << numero << " esta en el arbol" << std::endl;
                } else {
                    std::cout << "\nEl numero " << numero << " no esta en el arbol" << std::endl;
                }
                std::cout << "\n";
                system("pause");
                break;
            case 4:
                std::cout << "\nMostrando el recorrido preOrden del arbol: ";
                recorrido_preOrden(arbol);
                std::cout << "\n\n";
                system("pause");
                break;
            case 5:
                std::cout << "\nMostrando el recorrido inOrden del arbol: ";
                recorrido_inOrden(arbol);
                std::cout << "\n\n";
                system("pause");
                break;
            case 6:
                std::cout << "\nMostrando el recorrido postOrden del arbol: ";
                recorrido_postOrden(arbol);
                std::cout << "\n\n";
                system("pause");
                break;
            case 7:
                std::cout << "\nIngrese el numero que desea eliminar: ";
                std::cin >> numero;
                buscar_nodo_eliminar(arbol, numero);
                std::cout << "\n";
                system("pause");
                break;
            case 8:
                std::cout << "\nLa altura del arbol es: " << altura(arbol) << std::endl;
                std::cout << "\n";
                system("pause");
                break;
            case 9:
                std::cout << "\nEl numero de nodos en el arbol es: " << contar_nodos(arbol) << std::endl;
                std::cout << "\n";
                system("pause");
                break;
            case 10:
                std::cout << "\nEl numero de hojas en el arbol es: " << contar_hojas(arbol) << std::endl;
                std::cout << "\n";
                system("pause");
                break;
            case 11: {
                int total_nodos = contar_nodos(arbol);
                if (es_binario_completo(arbol, 0, total_nodos)) {
                    std::cout << "\nEl arbol es completo." << std::endl;
                } else {
                    std::cout << "\nEl arbol no es completo." << std::endl;
                }
                std::cout << "\n";
                system("pause");
                break;
            }
            case 12:
                if (es_binario_lleno(arbol)) {
                    std::cout << "\nEl arbol es lleno." << std::endl;
                } else {
                    std::cout << "\nEl arbol no es lleno." << std::endl;
                }
                std::cout << "\n";
                system("pause");
                break;
            case 13:
                eliminar_arbol(arbol);
                std::cout << "\nEl arbol ha sido eliminado." << std::endl;
                std::cout << "\n";
                system("pause");
                break;
            case 14: // Opción para recorrido por niveles
                std::cout << "\nMostrando el recorrido por niveles del arbol: ";
                recorrido_por_niveles(arbol);
                std::cout << "\n\n";
                system("pause");
                break;
        }
        system("cls");
    } while (opcion != 15);
}

// Función principal
int main() {
    menu();
    return 0;
}