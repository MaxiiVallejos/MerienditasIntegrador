#  MerienditasIntegrador

Repositorio creado para el Trabajo Práctico Integrador de la materia **Algoritmos y Estructuras de Datos 2 (AED2)** de la carrera **Licenciatura en Sistemas de Información (LSI)** - FaCENA-UNNE. Consiste en un sistema de gestión y agenda de pedidos para un local de pastelería artesanal.

---

##  Funcionalidades Principales

El sistema opera cargando los registros en un vector dinámico en memoria RAM al iniciar la aplicación para garantizar velocidad y facilitar las operaciones de ordenamiento y filtrado, guardando los cambios de forma persistente en un archivo binario al salir[cite: 3]:

1. **Agregar Pedido:** Permite registrar nuevos pedidos ingresando ID, cliente, fecha de entrega, descripción y control de anticipos (señas).
2. **Listado Ordenado por Fecha:** Muestra todos los pedidos pendientes ordenados cronológicamente mediante un algoritmo de ordenamiento por burbuja adaptado al formato de fecha (`AAAA-MM-DD`).
3. **Búsqueda por Cliente:** Realiza una búsqueda secuencial en el vector para ubicar rápidamente todos los pedidos asociados a un cliente específico.
4. **Eliminar Pedido (Entregado):** Remueve lógicamente del vector el pedido cuyo ID coincida al ser entregado, actualizando la estructura en memoria.
5. **Persistencia de Datos:** Lectura inicial automática desde `pedido.dat` y volcado/actualización completa al salir del sistema.

---

##  Tecnologías y Estructura del Código

El proyecto está desarrollado en **Lenguaje C** bajo un diseño modular limpio:

* **`main.c`**: Archivo principal que contiene exclusivamente el bucle de ejecución (`do-while`), el menú de opciones y la invocación de las funciones lógicas.
* **`pedidos.h`**: Archivo de cabecera que encapsula las estructuras de datos (`tPedido`), constantes globales y la implementación de todas las funciones del sistema (alta, baja, listado, búsqueda y manejo de archivos binarios).
* **`pedido.dat`**: Archivo binario de almacenamiento persistente en disco.

---

##  Compilación y Ejecución

Para compilar y ejecutar el proyecto en sistemas operativos Linux / Ubuntu mediante la terminal:

1. Clona el repositorio o sitúate en la carpeta del proyecto.
2. Compila el archivo principal con **GCC**:
   ```bash
   gcc main.c -o main
