#ifndef PEDIDOS_H
#define PEDIDOS_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_PEDIDOS 100

typedef char string[50];
typedef char stringDesc[100];

typedef struct {
    int idPedido;
    string cliente;
    string fechaDeEntrega; // Formato recomendado: AAAA-MM-DD
    stringDesc descripcion;
    bool anticipo;
    float montoanticipo;
    float importe;         // Importe total del pedido
} tPedido;

// Funcion para mostrar el menu
int menu() {
    int opcion;
    printf("\n--- GESTION DE PEDIDOS (EN MEMORIA) ---\n");
    printf("1: Agregar pedido\n");
    printf("2: Ver pedidos (Ordenados por fecha)\n");
    printf("3: Buscar pedido por cliente\n");
    printf("4: Eliminar pedido (Entregado)\n");
    printf("5: Salir y Guardar\n");
    printf("Ingrese opcion: ");
    scanf("%d", &opcion);
    return opcion;
}

// Carga el archivo binario completo al vector al iniciar el programa
int cargarArchivoAVector(const char *pArchivo, tPedido pVector[]) {
    FILE *archivo = fopen(pArchivo, "rb");
    if (archivo == NULL) {
        return 0; // Si no existe el archivo aun, hay 0 pedidos cargados
    }

    int cant = 0;
    while (cant < MAX_PEDIDOS && fread(&pVector[cant], sizeof(tPedido), 1, archivo) == 1) {
        cant++;
    }

    fclose(archivo);
    return cant;
}

// Guarda todo el vector de vuelta al archivo binario al salir
void guardarVectorAArchivo(const char *pArchivo, tPedido pVector[], int pCant) {
    FILE *archivo = fopen(pArchivo, "wb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo para guardar.\n");
        return;
    }
    int i;
    for (i = 0; i < pCant; i++) {
        fwrite(&pVector[i], sizeof(tPedido), 1, archivo);
    }

    fclose(archivo);
}

// Ordena el vector por fecha de entrega usando Bubble Sort
void ordenarPorFecha(tPedido pVector[], int pCant) {
    tPedido aux;
    int i, j;
    for (i = 0; i < pCant - 1; i++) {
        for (j = 0; j < pCant - i - 1; j++) {
            if (strcmp(pVector[j].fechaDeEntrega, pVector[j+1].fechaDeEntrega) > 0) {
                aux = pVector[j];
                pVector[j] = pVector[j+1];
                pVector[j+1] = aux;
            }
        }
    }
}

// Funcion para solicitar y cargar los datos de un nuevo pedido en el vector
void agregarPedido(tPedido pVector[], int *pCant) {
    if (*pCant >= MAX_PEDIDOS) {
        printf("Capacidad maxima de pedidos alcanzada.\n");
        return;
    }

    int tieneAnticipo;
    tPedido nuevo;

    printf("ID: ");
    scanf("%d", &nuevo.idPedido);

    printf("Cliente: ");
    scanf(" %49[^\n]", nuevo.cliente);

    printf("Fecha de entrega (ej. 2026-11-25): ");
    scanf(" %49[^\n]", nuevo.fechaDeEntrega);

    printf("Descripcion: ");
    scanf(" %99[^\n]", nuevo.descripcion);

    printf("Importe total del pedido: ");
    scanf("%f", &nuevo.importe);

    printf("Tiene anticipo? (1: Si / 0: No): ");
    scanf("%d", &tieneAnticipo);
    nuevo.anticipo = (tieneAnticipo == 1);

    if (nuevo.anticipo) {
        printf("Monto del anticipo: ");
        scanf("%f", &nuevo.montoanticipo);
    } else {
        nuevo.montoanticipo = 0.0;
    }

    pVector[*pCant] = nuevo;
    (*pCant)++;
    printf("Pedido agregado al vector con exito.\n");
}

// Funcion para ver los pedidos ordenados por fecha
void verPedidos(tPedido pVector[], int pCant) {
    if (pCant == 0) {
        printf("No hay pedidos registrados.\n");
        return;
    }

    ordenarPorFecha(pVector, pCant);

    printf("\n--- LISTA DE PEDIDOS (ORDENADOS POR FECHA) ---\n");
    int i;
    for (i = 0; i < pCant; i++) {
        printf("ID: %d | Cliente: %s | Entrega: %s | Desc: %s | Importe: $%.2f | Anticipo: %s ($%.2f)\n",
               pVector[i].idPedido,
               pVector[i].cliente,
               pVector[i].fechaDeEntrega,
               pVector[i].descripcion,
               pVector[i].importe,
               pVector[i].anticipo ? "Si" : "No",
               pVector[i].montoanticipo);
    }
}

// Funcion para buscar un pedido por cliente en el vector
void buscarPorCliente(tPedido pVector[], int pCant) {
    char clienteBuscado[50];
    bool encontrado = false;

    printf("Ingrese el nombre del cliente a buscar: ");
    scanf(" %49[^\n]", clienteBuscado);

    printf("\n--- RESULTADOS DE LA BUSQUEDA PARA: %s ---\n", clienteBuscado);

    int i;
    for (i = 0; i < pCant; i++) {
        if (strcmp(pVector[i].cliente, clienteBuscado) == 0) {
            printf("ID: %d | Cliente: %s | Entrega: %s | Desc: %s | Importe: $%.2f | Anticipo: %s ($%.2f)\n",
                   pVector[i].idPedido,
                   pVector[i].cliente,
                   pVector[i].fechaDeEntrega,
                   pVector[i].descripcion,
                   pVector[i].importe,
                   pVector[i].anticipo ? "Si" : "No",
                   pVector[i].montoanticipo);
            encontrado = true;
        }
    }

    if (!encontrado) {
        printf("No se encontraron pedidos para el cliente '%s'.\n", clienteBuscado);
    }
}

// Funcion para eliminar un pedido del vector
void eliminarPedido(tPedido pVector[], int *pCant) {
    int idBuscado;
    int pos = -1;
    int i;

    printf("Ingrese el ID del pedido entregado que desea eliminar: ");
    scanf("%d", &idBuscado);

    for (i = 0; i < *pCant; i++) {
        if (pVector[i].idPedido == idBuscado) {
            pos = i;
            break;
        }
    }

    if (pos != -1) {
        for (i = pos; i < *pCant - 1; i++) {
            pVector[i] = pVector[i + 1];
        }
        (*pCant)--;
        printf("Pedido ID %d entregado y eliminado del vector con exito.\n", idBuscado);
    } else {
        printf("No se encontro ningun pedido con el ID %d.\n", idBuscado);
    }
}

#endif
