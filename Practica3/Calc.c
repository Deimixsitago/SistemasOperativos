#include <stdio.h>
#include <math.h>

float stack[8];

// Imprimir pila //////////////////////////////////////////////////////
void printStack()
{
    for (int i = 0; i < 8; i++)
    {
        printf("%d. ", 8 - i);
        printf("%f\n", stack[i]);
    }
    printf("\n\n");
}

// Subir números de la pila //////////////////////////////////////////////////////
void stackUp()
{
    for (int i = 1; i < 8; i++)
    {
        stack[i - 1] = stack[i];
    }
}

// Bajar números de la pila //////////////////////////////////////////////////////
void stackDown()
{
    for (int i = 7; i > 0; i--)
    {
        stack[i] = stack[i - 1];
    }
    stack[0] = 0;
}

// Agregar nuevo número //////////////////////////////////////////////////////
void newNumber()
{
    if (stack[0] != 0)
    {
        printf("La pila está llena\n");
        printStack();
    }
    else
    {
        printf("Ingrese el número a ingresar a la pila\n");
        float num;
        scanf("%f", &num);
        printf("\n");
        stackUp();
        stack[7] = num;
        printStack();
    }
}
// Limpíar todos los números //////////////////////////////////////////////////////

void clearAll()
{
    for (int i = 0; i < 8; i++)
    {
        stack[i] = 0;
    }
    printStack();
}

// Limpiar primer número //////////////////////////////////////////////////////
void clearFirstNumber()
{
    for (int i = 0; i < 8; i++)
    {
        if (stack[i] != 0)
        {
            stack[i] = 0;
            break;
        }
    }
    printStack();
}

// Limpiar último número //////////////////////////////////////////////////////

void clearLastNumber()
{
    stackDown();
    printStack();
}

// Operaciones //////////////////////////////////////////////////////
void suma()
{
    // Suma de dos numeros
    stack[6] = stack[6] + stack[7];
    stackDown();
}

void resta()
{
    // Resta de dos numeros
    stack[6] = stack[6] - stack[7];
    stackDown();
}

void mult()
{
    // Multiplicación de dos numeros
    stack[6] = stack[6] * stack[7];
    stackDown();
}

void div()
{
    // división de dos numeros excepto si el denominador es 0
    if (stack[7] == 0)
    {
        printf("No se puede dividir entre 0\n");
    } else{
        stack[6] = stack[6] / stack[7];
        stackDown();
    }
    
}

void seno()
{
    // Calcula el seno en radianes
    stack[7] = sinf(stack[7]);
}

void cosen()
{
    // Calcula el coseno en radianes
    stack[7] = cosf(stack[7]);
}

void tang()
{
    // Calcula la tangente  en radianes solo si no se es multiplo de 90 y a la vez su division entre 90 es primo
    if (fmodf(stack[7], 90.0f) == 0.0f && fmodf(stack[7] / 90.0f, 2.0f) == 1.0f)
    {
        printf("No tiene tangente definida\n");
    }
    else
    {
        stack[7] = tanf(stack[7]);
    }
}

void raCua()
{
    // Calcula la raiz cuadrada
    stack[7] = sqrtf(stack[7]);
}

void potencia()
{
    // Potencia de dos numeros y verifica que no eleve 0 sobre 0 al no estar definido
    if (stack[7] == 0 && stack[6] == 0)
    {
        printf("No se puede elevar 0 a la 0\n");
    }
    else
    {
        stack[6] = powf(stack[7], stack[6]);
        stackDown();
    }
}

// main //////////////////////////////////////////////////////
int main()
{
    printf("//////////////CAlCULADORA RPN\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");
    printStack();
    int eleccion;
    char eleccionChar;
    do
    {
        do
        {
            printf("                                                                      ¿Qué desea hacer?\n 1. Ingresar número       2. Seleccionar operación       3. Limpiar último       4. Limpiar primero       5. Limpiar Todo       6. Salir\n");
            scanf("%d", &eleccion);
            printf("\n");
            if (sizeof(eleccion) != 4 || eleccion > 7 || eleccion < 0)
            {
                printf("\nIngrese un número válido\n");
            }
        } while (sizeof(eleccion) != 4 || eleccion > 7 || eleccion < 0); // Se supone que verifica que sea un int entre [1,6], pero no reconoce los Strings ¯\_(ツ)_/¯

        switch (eleccion)
        {
        case 1:
            newNumber();
            break;

        case 2:
            printf("                                                                    ¿Qué operación desea hacer?\n  +,       -,        *,        /,        r(raiz cuadrada),       p(potencia),      s(seno),      c(coseno),      t(tangente)\n");
            scanf(" %c", &eleccionChar);
            printf("\n");
            if (eleccionChar != '+' && eleccionChar && '-' || eleccionChar && '*' && eleccionChar != '/' && eleccionChar != 'r' && eleccionChar != 'p' && eleccionChar != 's' && eleccionChar != 'c' && eleccionChar != 't')
            {
                printf("\nIngrese un carácter válido\n");
            }

            switch (eleccionChar)
            {
            case '+':
                suma();
                break;

            case '-':
                resta();
                break;

            case '*':
                mult();
                break;

            case '/':
                div();
                break;

            case 'r':
                raCua();
                break;

            case 'p':
                potencia();
                break;

            case 's':
                seno();
                break;

            case 'c':
                cosen();
                break;

            case 't':
                tang();
                break;
            }
            printStack();
            break;

        case 3:
            clearLastNumber();
            break;

        case 4:
            clearFirstNumber();
            break;

        case 5:
            clearAll();
            break;
        }
    } while (eleccion != 6);

    return 0;
}