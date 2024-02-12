#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// #include <unistd.h> //Linux/Mac

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
    printf("Code: %d \nName: %s \nPrice:%.2f \n", prod.code, strtok(prod.name, "\n"), prod.price);
}

void menu(){
    printf("====================================\n");
    printf("============= Welcome! =============\n");
    printf("============ Geek Shop =============\n");
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
        printf("Invalid option!\n");
        sleep(3);
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

    sleep(2);

    menu();

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
        sleep(2);
        menu();
    } else {
        printf("We don't have products registered yet!\n");
        sleep(2);
        printf("\n");
        menu();
    }

}

void buyProd(){
    if (count_product > 0){
        printf("=========== Available Products ================\n");
        for (int i = 0; i < count_product; i++){
            infoProd(products[i]);
            printf("-------------------------------\n");
            sleep(1);
        }
        printf("Enter the code of the product you want to add to the cart:");
        int code;
        scanf("%d", &code);
        getchar();

        int has_market = 0;

        for (int i=0; i<count_product; i++){
            if(products[i].code == code){
                has_market = 1;

                if (count_cart > 0){
                    int* ret = haveinCart(code);

                    if (ret[0] == 1){
                        cart[ret[1]].amount++;
                        printf("It increase the amount of the product %s already in the cart.\n", strtok(cart[ret[1]].prod.name, "\n"));
                        sleep(2);
                        menu();
                    } else {
                        Product p = getProdbyCode(code);
                        cart[count_cart].prod = p;
                        cart[count_cart].amount = 1;
                        count_cart++;
                        printf("The product %s has been added to the cart.\n", strtok(p.name, "\n"));
                        sleep(2);
                        menu();
                    }
                } else {
                    Product p = getProdbyCode(code);
                    cart[count_cart].prod = p;
                    cart[count_cart].amount=1;
                    count_cart++;
                    printf("The product %s has been added to the cart.\n", strtok(p.name, "\n"));
                    sleep(2);
                    menu();
                }
            }
        }

        if (has_market < 1){
            printf("Product with code %d was not found.\n", code);
            sleep(2);
            menu();
        }

    } else {
        printf("There aren't product to sell.\n");
        printf("\n");
        sleep(2);
        menu();
    }
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
        sleep(2);
        menu();

    } else {
        printf("We don't have any products in the cart yet!\n");
        sleep(2);
        printf("\n");
        menu();
    }
}

Product getProdbyCode(int code){
    Product p;
    for(int i=0; i < count_product; i++){
        if (products[i].code == code){
            p = products[i];
        }
    }
    return p;
}

int * haveinCart(int code){
    int static ret[]={0,0};
    for(int i=0; i < count_cart; i++){
        if (cart[i].prod.code == code){
            ret[0] = 1; // it has the product with this code in the cart
            ret[1] = i; // the product index in the cart
        }
    }
    return ret;
}

void finalizeOrder(){
    if (count_cart > 0){
        float total_value = 0.0;
        printf("Cart Products\n");
        printf("----------------\n");
        for (int i=0; i<count_cart; i++){
            Product p = cart[i].prod;
            int amount = cart[i].amount;
            total_value += p.price * amount;
            infoProd(p);
            printf("Amount: %d\n", amount);
            printf("----------------\n");
            sleep(1);
        }
        printf("Your total purchase is: %.2f\n", total_value);

        //Clean cart
        count_cart = 0;
        printf("Thank you for your preference!\n");
        sleep(5);
        menu();
    } else {
        printf("You don't have any products in your cart yet.\n");
        sleep(3);
        menu();
    }
}
