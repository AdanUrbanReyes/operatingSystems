#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define numbersProducts 5
typedef struct product{
	int id,amountSale;
	float menudeoPrice;
}product;
product *products;
void startProducts(){
	products=(product*)malloc(sizeof(product)*numbersProducts);
	products[0].id=1;
	products[0].menudeoPrice=2.98;
	products[0].amountSale=0;
	products[1].id=2;
	products[1].menudeoPrice=4.50;
	products[1].amountSale=0;
	products[2].id=3;
	products[2].menudeoPrice=9.98;
	products[2].amountSale=0;
	products[3].id=4;
	products[3].menudeoPrice=4.49;
	products[3].amountSale=0;
	products[4].id=5;
	products[4].menudeoPrice=6.87;
	products[4].amountSale=0;
}
int main(){
	startProducts();
	int idProduct,amountSale,indexProduct;
	char option[3];
	do{
      printf("would you like insert other product? yes/not\n");
      scanf("%s",option);
      if(strncasecmp(option,"y",1))
         continue;
		printf("number product\n");
		scanf("%d",&idProduct);
		switch(idProduct){
			case 1:
				indexProduct=0;
			break;
			case 2:
				indexProduct=1;
			break;
			case 3:
				indexProduct=2;
			break;
			case 4:
				indexProduct=3;
			break;
			case 5:
				indexProduct=4;
			break;
		}
		printf("amount sale in day\n");
		scanf("%d",&amountSale);
		products[indexProduct].amountSale+=amountSale;
   }while(strncasecmp(option,"n",1));
	for(indexProduct=0;indexProduct<numbersProducts;indexProduct++)
		printf("product %d, menudeo price=%g, amount sale %d, total=%g\n",products[indexProduct].id,products[indexProduct].menudeoPrice,products[indexProduct].amountSale,products[indexProduct].amountSale*products[indexProduct].menudeoPrice);
	return 0;
}

