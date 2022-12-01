#include<stdio.h>
#include<ctype.h>

void bg_of_game(); // just two printfs

void bg_of_area(int *area, int *saving, int *speed_level, int *taste_level, int *time, int *price);

int ask_action(int price, int up_speed_cost, int up_taste_cost, int time);

void sell(int *saving, int time, int price, int *day_earning);

void up_speed(int *saving, int *up_speed_cost, int *speed_level);

void up_taste(int *saving, int *up_taste_cost, int *taste_level);
int main(){
    printf("Welcome, young boss!\n");
    // initialize variables
    int up_speed_cost = 50, up_taste_cost = 100;
    int speed_level = 0, time = 15,  taste_level = 0, price = 0, action; 
    int saving = 100; int area = 1;
    int continue_or_not = 1;
    int day_earning = 0;

    //price = taste*10 + 30, time = 15-speed_level
    
    bg_of_game();
    
    
    // operations
    while (continue_or_not){
        bg_of_area(&area, &saving, &speed_level, &taste_level, &time, &price);
        action = ask_action(price, up_speed_cost, up_taste_cost, time);
        if (action == 1){
            sell(&saving, time, price, &day_earning);
        }else if(action == 2){
            if (saving >= up_speed_cost && time > 1){
                up_speed(&saving, &up_speed_cost, &speed_level);
            }else if(saving < up_speed_cost){
                printf("Can't you tell how poor you are?\nGo vending your hotdogs instead of thinking about self-improvement!\n");
                sell(&saving, time, price, &day_earning);
            }else{
                printf("Do you want to travel through time? GO WORK!!\n");
                sell(&saving, time, price, &day_earning);
            }
            
        }else if(action == 3){
            if (saving >= up_taste_cost){
                up_taste(&saving, &up_taste_cost, &taste_level);
            }else{
                printf("Can't you tell how poor you are?\nGo vending your hotdogs instead of thinking about self-improvement!\n");
                sell(&saving, time, price, &day_earning);
            }
            
        }
    // area

        if (area <= 3){
            area += 1;
        }else if(area == 4){
            printf("Well done, you earn $%d today.\n", day_earning);
            area = 1;
            day_earning = 0;
        
            // continue or not
            ask_again:printf("Do you want to continue or exit?\n  [1] Continue\n  [2] Exit\nEnter the number: ");
            scanf("%d", &continue_or_not);
            if (continue_or_not == 2){
                printf("We will miss you. Bye!\n");
                break;
            }else if(continue_or_not == 1){
                printf("Chop chop, It's dawn.\n");
            }else{
                printf("Invalid input!!!!\n");
                goto ask_again;
            }
        }
    }
    
    return 0;
}

void bg_of_day(){
    // printf("Chop chop, It's dawn.\n");
    // printf("You have %d dollars.\n", );
    // printf("You need %d minutes to make a hotdog.\n", );
    // printf("The price of a hotdog is $%d.\n", );
    // printf("You have %d speed booster(s), %d price booster(s), %d area booster(s).\n", , , );
}

void bg_of_area(int *area, int *saving, int *speed_level, int *taste_level, int *time, int *price){
    
    *price = *taste_level*10 + 30;
    *time = 15 - *speed_level;
    printf("You are at Area %d.\n", *area);
    printf("You have %d dollars.\n", *saving);
    printf("You need %d minutes to make a hotdog.\n", *time);
    printf("The price of a hotdog is $%d.\n", *price);
}

int ask_action(int price, int up_speed_cost, int up_taste_cost, int time){
    int action;
    
    while (1){
        printf("Please choose which action you want to take:\n  [1] Sell the hotdogs (+ $%d)\n  [2] Improve your cooking speed (- $%d / - 1 min for making a hotdog)\n  [3] Improve your hotdog flavor (- $%d / + $10 for each hotdog)\nEnter the number: ", price*(180/time), up_speed_cost, up_taste_cost);
        scanf("%d", &action);
        if (action >=1 && action <= 3){
            break;
        }else{
            printf("Invalid input!!!!\n");
        }
    }
    return action;
}

void sell(int *saving,int time, int price, int *day_earning){
    int profit = (180/time)*price; // 
    *saving += profit;
    printf("You make %d hotdogs here!\n", (180/time));
    printf("You earn $%d!\n", profit);
    *day_earning += profit;
}

void up_speed(int *saving, int *up_speed_cost, int *speed_level){
    *saving -= *up_speed_cost;
    *up_speed_cost *= 2;
    *speed_level += 1;
    printf("You glimpse the secret of wind.\nYour hands can move faster now.\n");
}

void up_taste(int *saving, int *up_taste_cost, int *taste_level){

    *saving -= *up_taste_cost;
    *up_taste_cost *= 2;
    *taste_level += 1;
    printf("You feel the soul of the ingredients.\nYour hotdogs are more appetizing now.\n");
}
