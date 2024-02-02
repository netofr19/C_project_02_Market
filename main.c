#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> //Linux/Mac

typedef struct {
    int code;
    char name[30];
    float price;
} Product;

typedef struct {
    Product prod;
    int amount;
} Cart;

void infoProd(Product prod);
void menu();
void registerProd();
void listProd();
void buyProd();
void viewCart();
Product getProdbyCode(int code);
int * haveinCart(int code);
void finalizeOrder();

static int count_product = 0;
static int count_cart = 0;
static Cart cart[50];
static Product products[50];


int main()
{
    menu();
    return 0;
}

void infoProd(Product prod){
    printf("Code: %d \nName: %s \nPrice:%.2f\n", prod.code, strtok(prod.name, '\n'), prod.price);
}

void menu(){
    printf("====================================\n");
    printf("=========== Welcome! ===============\n");
    printf("========== Geek Shop ===============\n");
    printf("====================================\n");

    printf("Select an option below: \n");
    printf("1 - Register product\n");
    printf("2 - List product\n");
    printf("3 - Buy product\n");
    printf("4 - View cart\n");
    printf("5 - Finalize order\n");
    printf("6 - Log out of the system\n");

    int option;
    scanf("%d", &option);
    getchar();

    switch (option)
    {
    case 1:
        registerProd();
        break;
    case 2:
        listProd();
        break;
    case 3:
        buyProd();
        break;
    case 4:
        viewCart();
        break;
    case 5:
        finalizeOrder();
        break;
    case 6:
        printf("See you soon!\n");
        sleep(2);
        exit(0);
    default:
        printf('Invalid option!\n');
        menu();
        break;
    }
}

void registerProd(){
    printf("======= Product Registration =======\n");
    printf("====================================\n");

    printf("Enter the name of the product: ");
    fgets(products[count_product].name, 30, stdin);

    printf("Enter the price of the product: ");
    scanf("%f", &products[count_product].price);

    printf("Product %s was successfully registered with price = $ %.2f.\n", strtok(products[count_product].name, "\n"), products[count_product].price);

    products[count_product].code = (count_product + 1);

    count_product++;

}

void listProd(){
    
    if(count_product > 0){
        printf("Product listing:\n");
        printf("--------------------\n");
        for (int i = 0; i < count_product; i++){
            infoProd(products[i]);
            printf("--------------------\n");
            sleep(1);
        }
    } else {
        printf("We don't have products registered yet!\n");
    }

}

void buyProd(){
    //In progress...
}

void viewCart(){
    if (count_cart > 0){
        printf("Products in the cart:\n");
        printf("--------------------\n");
        for (int i=0; i < count_cart; i++){
            infoProd(cart[i].prod);
            printf("Amount: %d\n", cart[i].amount);
            printf("--------------------\n");
            sleep(1);
        }

    } else {
        printf("We don't have any products in the cart yet!\n");
    }
}

Product getProdbyCode(int code){
    //In progress...
}

int * haveinCart(int code){
    //In progress...
}

void finalizeOrder(){
    //In progress...
}
