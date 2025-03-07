#include "atm.h"

int main() {
    cargarSaldo(); // Cargar los saldos al iniciar el programa
    cargarPIN();   // Cargar o registrar el PIN al iniciar el programa

    // Verificar el PIN antes de mostrar el menu
    if (!verificarPIN()) {
        return 0; // Salir del programa si el PIN es incorrecto
    }

    // Seleccionar la cuenta
    printf("Seleccione su cuenta (0, 1, 2): ");
    scanf("%d", &cuentaSeleccionada);
    if (cuentaSeleccionada < 0 || cuentaSeleccionada >= NUM_CUENTAS) {
        printf("Cuenta no valida. Saliendo del programa.\n");
        return 0; // Salir si la cuenta no es valida
    }

    int opc;
    do {
        printf("\n========= Cajero Automatico =========\n");
        printf("1. Consultar saldo\n");
        printf("2. Depositar dinero\n");
        printf("3. Retirar dinero\n");
        printf("4. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opc);

        switch (opc) {
            case 1:
                consultarSaldo();
                break;
            case 2:
                depositar();
                break;
            case 3:
                retirar();
                break;
            case 4:
                guardarSaldo(); // Guardar los saldos antes de salir
                printf("Gracias por usar el Cajero Automatico.\n");
                break;
            default:
                printf("Opcion no valida. Intente de nuevo.\n");
        }
    } while (opc != 4);

    return 0;
}
