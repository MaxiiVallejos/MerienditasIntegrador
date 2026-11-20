#include "pedidos.h"

int main() {
    int opcion;
    char nombreArchivo[] = "pedido.dat";
    
    tPedido vectorPedidos[MAX_PEDIDOS];
    int cantidadPedidos = 0;

    // Al iniciar: cargamos el archivo completo al vector en memoria
    cantidadPedidos = cargarArchivoAVector(nombreArchivo, vectorPedidos);

    do {
        opcion = menu();

        switch (opcion) {
            case 1:
                agregarPedido(vectorPedidos, &cantidadPedidos);
                break;

            case 2:
                verPedidos(vectorPedidos, cantidadPedidos);
                break;

            case 3:
                buscarPorCliente(vectorPedidos, cantidadPedidos);
                break;

            case 4:
                eliminarPedido(vectorPedidos, &cantidadPedidos);
                break;

            case 5:
                // Al salir: guardamos todo el vector actualizado al archivo binario
                guardarVectorAArchivo(nombreArchivo, vectorPedidos, cantidadPedidos);
                printf("Saliendo del programa... Datos guardados correctamente en disco.\n");
                break;

            default:
                printf("Opcion invalida. Intente nuevamente.\n");
        }

    } while (opcion != 5);

    return 0;
}
