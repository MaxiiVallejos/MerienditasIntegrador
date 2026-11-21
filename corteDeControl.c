#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "pedidos.h"

#define ARCHIVO "Pedidos.dat"
#define TITULO1 "\n*** INFORME PEDIDOS ***\n"

void inicializacion();
void procesoCorte();
void finalizacion();

void principioCorte();
void unPedido();
void finCorte();
void leerPedido();

FILE *archivo;
tPedido pedido, pedidoAnterior;
bool finArchivo;

float totalDia, totalGeneral;
float mayorImporteDia;
string clienteMayorDia;
int cantDias;

int main() {
    inicializacion();
    procesoCorte();
    finalizacion();
    return 0;
}


void leerPedido() {
    finArchivo = (fread(&pedido, sizeof(tPedido), 1, archivo) != 1);
}

void inicializacion() {

    tPedido vector[MAX_PEDIDOS];
    int cant = cargarArchivoAVector(ARCHIVO, vector);

    if (cant == 0) {
        printf("No se encuentra el archivo o no hay pedidos!\n");
        exit(EXIT_FAILURE);
    }

    ordenarPorFecha(vector, cant);
    guardarVectorAArchivo(ARCHIVO, vector, cant);

    archivo = fopen(ARCHIVO, "rb");
    if (archivo == NULL) {
        printf("No se encuentra el archivo!\n");
        exit(EXIT_FAILURE);
    }

    leerPedido();
    pedidoAnterior = pedido;

    totalGeneral = 0;
    cantDias = 0;

    printf("%s", TITULO1);
}

void procesoCorte() {

    while (!finArchivo) {

        principioCorte();

        while (!finArchivo &&
               strcmp(pedido.fechaDeEntrega, pedidoAnterior.fechaDeEntrega) == 0) {
            unPedido();
            leerPedido();
        }

        finCorte();
    }
}

void principioCorte() {
    totalDia = 0;
    mayorImporteDia = -1;
    clienteMayorDia[0] = '\0';

    printf("\nFecha: %s\n", pedido.fechaDeEntrega);
    printf("==========================================================================\n");
    printf("%-20s | %-25s | %-8s | %-14s | %s\n",
           "CLIENTE", "DESCRIPCION PRODUCTO", "ANTICIPO", "MONTO ANTICIPO", "IMPORTE");
    printf("--------------------------------------------------------------------------\n");
}

void unPedido() {

    printf("%-20s | %-25s | %-8s | $%-13.2f | $%.2f\n",
           pedido.cliente,
           pedido.descripcion,
           pedido.anticipo ? "Si" : "No",
           pedido.montoanticipo,
           pedido.importe);

    totalDia += pedido.importe;

    if (pedido.importe > mayorImporteDia) {
        mayorImporteDia = pedido.importe;
        strcpy(clienteMayorDia, pedido.cliente);
    }
}

void finCorte() {

    printf("--------------------------------------------------------------------------\n");
    printf("TOTAL DEL DIA: $%.2f\n", totalDia);
    printf("CLIENTE CON MAYOR COMPRA: %s ($%.2f)\n", clienteMayorDia, mayorImporteDia);
    printf("==========================================================================\n");

    totalGeneral += totalDia;
    cantDias++;

    pedidoAnterior = pedido;
}

void finalizacion() {

    printf("\nCANTIDAD DE DIAS REGISTRADOS: %d\n", cantDias);
    printf("TOTAL GENERAL DE VENTAS: $%.2f\n", totalGeneral);

    fclose(archivo);
}
