#ifndef ATM_H_INCLUDED
#define ATM_H_INCLUDED

#include <stdio.h>

#define MAX_INTENTOS 3 // Maximo numero de intentos
#define NUM_CUENTAS 3 // Numero de cuentas disponibles

float saldos[NUM_CUENTAS] = {0.0, 0.0, 0.0}; // Inicializar los saldos de las cuentas en 0
int cuentaSeleccionada; // Variable para almacenar la cuenta seleccionada
char pin[5]; // Arreglo para almacenar el PIN (4 digitos + caracter nulo)

int verifica(float x) {
    if (x < 0) {
        printf("La cantidad no es valida. Debe ser mayor a 0.\n");
        return 0; // No valido
    }
    return 1; // Valido
}

void consultarSaldo() {
    printf("Tu saldo en la cuenta %d es: $%.2f\n", cuentaSeleccionada, saldos[cuentaSeleccionada]);
}

void depositar() {
    float cantidad;
    printf("Ingrese la cantidad a depositar: ");
    scanf("%f", &cantidad);

    if (verifica(cantidad)) {
        saldos[cuentaSeleccionada] += cantidad;
        printf("Deposito exitoso. Nuevo saldo: $%.2f\n", saldos[cuentaSeleccionada]);
    } else {
        printf("No se pudo realizar el deposito.\n");
    }
}

void retirar() {
    float cantidad;
    printf("Ingrese la cantidad a retirar: ");
    scanf("%f", &cantidad);

    if (verifica(cantidad)) {
        if (cantidad > saldos[cuentaSeleccionada]) {
            printf("Fondos insuficientes. Saldo actual: $%.2f\n", saldos[cuentaSeleccionada]);
        } else {
            saldos[cuentaSeleccionada] -= cantidad;
            printf("Retiro exitoso. Nuevo saldo: $%.2f\n", saldos[cuentaSeleccionada]);
        }
    } else {
        printf("No se pudo realizar el retiro.\n");
    }
}

void guardarSaldo() {
    FILE *archivo = fopen("saldos.txt", "w");
    if (archivo == NULL) {
        printf("Error al guardar los saldos.\n");
        return;
    }
    for (int i = 0; i < NUM_CUENTAS; i++) {
        fprintf(archivo, "%.2f\n", saldos[i]);
    }
    fclose(archivo);
}

void cargarSaldo() {
    FILE *archivo = fopen("saldos.txt", "r");
    if (archivo == NULL) {
        // Si el archivo no existe, se crea con saldos iniciales 0.0
        archivo = fopen("saldos.txt", "w");
        if (archivo == NULL) {
            printf("Error al crear el archivo de saldos.\n");
            return;
        }
        for (int i = 0; i < NUM_CUENTAS; i++) {
            fprintf(archivo, "%.2f\n", saldos[i]);
        }
        fclose(archivo);
    } else {
        // Si el archivo existe, se cargan los saldos
        for (int i = 0; i < NUM_CUENTAS; i++) {
            fscanf(archivo, "%f", &saldos[i]);
        }
        fclose(archivo);
    }
}

void guardarPIN() {
    FILE *archivo = fopen("pin.txt", "w");
    if (archivo == NULL) {
        printf("Error al guardar el PIN.\n");
        return;
    }
    fprintf(archivo, "%s", pin);
    fclose(archivo);
}

void cargarPIN() {
    FILE *archivo = fopen("pin.txt", "r");
    if (archivo == NULL) {
        // Si el archivo no existe, se pide al usuario que registre un nuevo PIN
        printf("====No se encontro un PIN registrado====\n\nPor favor, registre un nuevo PIN (4 digitos): ");
        scanf("%s", pin);
        guardarPIN(); // Guardar el nuevo PIN en el archivo
        printf("\nPIN registrado exitosamente.\n");
    } else {
        // Si el archivo existe, se carga el PIN
        fscanf(archivo, "%s", pin);
        fclose(archivo);
    }
}

int verificarPIN() {
    char pinIngresado[5]; // Arreglo para almacenar el PIN ingresado
    int intentos = 0;

    while (intentos < MAX_INTENTOS) {
        printf("Ingrese su PIN (4 digitos): ");
        scanf("%s", pinIngresado);

        // Comparar el PIN ingresado con el PIN almacenado
        int correcto = 1;
        for (int i = 0; i < 4; i++) {
            if (pinIngresado[i] != pin[i]) {
                correcto = 0; // Si algun digito no coincide, el PIN es incorrecto
                break;
            }
        }

        if (correcto) {
            return 1; // PIN correcto
        } else {
            intentos++;
            printf("PIN incorrecto. Intentos restantes: %d\n", MAX_INTENTOS - intentos);
        }
    }

    printf("Demasiados intentos fallidos. Saliendo del programa.\n");
    return 0; // PIN incorrecto despues de 3 intentos
}

#endif // ATM_H_INCLUDED


