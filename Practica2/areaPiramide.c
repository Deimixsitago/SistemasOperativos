#include <stdio.h>

void HallarVolumenPiramide(){
    double ancho_base; double largo_base; double area_base; double altura_piramide;
    printf ("Ingrese el ancho de la base: ");
    scanf("%lf", &ancho_base);
    printf ("Ingrese el largo de la base: ");
    scanf("%lf", &largo_base);
    printf ("Ingrese la atura de la pirámide: ");
    scanf("%lf", &altura_piramide);
    double volumen_piramide=(largo_base*ancho_base*altura_piramide)/3;
    printf ("El volumen de la pirámide es de: %.15g u3\n",volumen_piramide);
}
int main(){
    HallarVolumenPiramide();
    return 0;
}
