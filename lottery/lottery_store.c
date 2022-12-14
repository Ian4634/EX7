#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
// u have no money
// booster 剩餘數位處理
// 每天結束記得加一次免費抽
// 問題：兩個booster 同時開只計算到一個
// booster就傳陣列booster value給sell 再做處理即可
// result check 可以用陣列代表每個result, 再用一個func去處理。

// ************可能的問題***************** 
// 1. user check results時輸入不合法
void bg_of_day(int *saving, int *speed_level, int *taste_level, int *time, int *price, int boosters[], int booster_status[]); 

void bg_of_area(int *area, int *saving, int *speed_level, int *taste_level, int *time, int *price);

int ask_action(int price, int up_speed_cost, int up_taste_cost, int time, int actions[]);

void result_check(int results[], int results_sell[][2], int booster_status[]);

void take_action(int actions[], int *saving, int *time, int *price, int *day_earning, int *up_speed_cost, int *speed_level, int *up_taste_cost, int *taste_level, int booster_status[], int results[], int results_sell[][2]);

void sell(int *saving, int *time, int price, int *day_earning, int booster_status[]);

void up_speed(int *saving, int *up_speed_cost, int *speed_level);

void up_taste(int *saving, int *up_taste_cost, int *taste_level);

// ************* graphing funcions********************
void graph_main(int *free_choices, int *open_cost, int *n, int *choosen_arr, int *saving, int *boosters, int *price);

int graph_input_validate(int input, int *n, int *choosen_arr);

void choosen_arr_initialize(int *n, int *choosen_arr);

void take_action_lottery(int prize_type, int *saving, int *choosen_arr, int *free_choices, int *boosters, int *price, int *n, int *input);

int digit_count(int n);                     

int reverse(int cell_num);

void graph_numline(int n);

void graphing(int n);

int power(int original, int n);

int cell_value_calculation(int cell_num);
// ************* graphing funcions**********************

int main(){
    printf("Welcome, young boss!\n");
    // initialize variables
    int up_speed_cost = 50, up_taste_cost = 100;
    int speed_level = 0, time = 15,  taste_level = 0, price = 0, action; 
    int saving = 0; int area = 1;
    int continue_or_not = 1;
    int day_earning = 0;
    int boosters[3] = {0, 0, 0}; // [0] = speed, [1] = price, [2] = area
    
    int booster_status[3] = {0,0,0}; // [0] = 0 means speed booster closed.
    
    int actions[4]; // stores actions at each area
    
    // 1:沒錢升級 2:無法再快 3:速度升級 4:味道升級 5: 賣熱狗
    int results[5] = {0}; int results_sell[5][2]; // [0] num of hotdogs made, [1] earn
    //price = taste*10 + 30, time = 15-speed_level
    
    // *********************lottery variables*****************************************
    int n = 3; int prizes_left = 9;
    int free_choices = 1; int open_cost = 500; int *choosen_arr = malloc((n*n)*sizeof(int));
    // initialize choosen_arr
    for (int i=0;i<n;i++){
        choosen_arr[i] = 0;
    }
    //************************************************************************************
    //bg_of_day(&saving, &speed_level, &taste_level, &time, &price, boosters, booster_status);
    //ask_action(price, up_speed_cost, up_taste_cost, time, actions);
    
    // operations
    //take_action(actions,&saving, &time, &price, &day_earning,&up_speed_cost, &speed_level, &up_taste_cost, &taste_level, booster_status, results, results_sell);
    //result_check(results, results_sell, booster_status);
    //************************************************************************************
    graphing(3);
    graph_main(&free_choices, &open_cost, &n, choosen_arr, &saving, &boosters[0], &price);
    
    
    return 0;
}

void take_action_lottery(int prize_type, int *saving, int *choosen_arr, int *free_choices, int *boosters, int *price, int *n, int *input){
    // *input is cell num picked
    switch(prize_type){
        case 1:
            choosen_arr[*input-1] = 1; // 紀錄抽過的
            // prize type 1
            printf("Fortune, fortune! You get $%d!\n", 100*(*price));
            break;
        case 2:
            choosen_arr[*input-1] = 1; // 紀錄抽過的
            // prize type 2
            printf("You get an extra choice!\n");
            *free_choices+=1;
            break;
        case 3: // open up
            choosen_arr[*input-1] = 1; // 紀錄抽過的
            if (*input > *n){ // not first
                int next_cell_picted = *input-*n; // 不用再減一因為不是要index
                printf("Another open on %d!\n", next_cell_picted);
                take_action_lottery(cell_value_calculation(*input-*n), saving, choosen_arr, free_choices, boosters, price, n, &next_cell_picted);              
            }else if(*input <= *n){ // first line
                int next_cell_picted = (*n)*(*n-1) + *input; // 不用再減一因為不是要index
                printf("Another open on %d!\n", next_cell_picted);
                take_action_lottery(cell_value_calculation(next_cell_picted), saving, choosen_arr, free_choices, boosters, price, n, &next_cell_picted);                   
            }else{
                printf("sth unexpected in take action price type 3");
            }
            // prize type 3 ~ 6 success
            //printf("Another open on %d!\n", );
            break;
        case 4: // open underneath
            choosen_arr[*input-1] = 1; // 紀錄抽過的
            if (*input > (*n)*(*n)){ // last line 
                int next_cell_picted = *input % (*n); // 不用再減一因為不是要index
                printf("Another open on %d!\n", next_cell_picted);
                take_action_lottery(cell_value_calculation(*input-*n), saving, choosen_arr, free_choices, boosters, price, n, &next_cell_picted); 
            }else{
                int next_cell_picted = *input + *n; // 不用再減一因為不是要index
                printf("Another open on %d!\n", next_cell_picted);
                take_action_lottery(cell_value_calculation(next_cell_picted), saving, choosen_arr, free_choices, boosters, price, n, &next_cell_picted); 
            }
            break;
        case 5: // open left
            choosen_arr[*input-1] = 1; // 紀錄抽過的
            if (*input % *n == 1){ // left most column
                int next_cell_picted = *input+ (*n-1); // 不用再減一因為不是要index
                printf("Another open on %d!\n", next_cell_picted);
                take_action_lottery(cell_value_calculation(next_cell_picted), saving, choosen_arr, free_choices, boosters, price, n, &next_cell_picted);        
            }else{
                int next_cell_picted = *input - 1; // 不用再減一因為不是要index
                printf("Another open on %d!\n", next_cell_picted);
                take_action_lottery(cell_value_calculation(next_cell_picted), saving, choosen_arr, free_choices, boosters, price, n, &next_cell_picted);        
            }
            break;
        case 6: // open right
            choosen_arr[*input-1] = 1; // 紀錄抽過的
            if(*input % *n == 0){ // right most column
                int next_cell_picted = *input - (*n-1); // 不用再減一因為不是要index
                printf("Another open on %d!\n", next_cell_picted);
                take_action_lottery(cell_value_calculation(next_cell_picted), saving, choosen_arr, free_choices, boosters, price, n, &next_cell_picted);
            }else{
                int next_cell_picted = *input+1; // 不用再減一因為不是要index
                printf("Another open on %d!\n", next_cell_picted);
                take_action_lottery(cell_value_calculation(next_cell_picted), saving, choosen_arr, free_choices, boosters, price, n, &next_cell_picted);
            }
            break;
        case 7:
            choosen_arr[*input-1] = 1; // 紀錄抽過的
            boosters[0] += 1;
            printf("You get a booster!!\n");
            break;
        case 8:
            choosen_arr[*input-1] = 1; // 紀錄抽過的
            boosters[1] += 1;
            printf("You get a booster!!\n");
            break;
        case 9:
            choosen_arr[*input-1] = 1; // 紀錄抽過的
            boosters[2] += 1;
            printf("You get a booster!!\n");
            break;
    }
}

void graph_main(int *free_choices, int *open_cost, int *n, int *choosen_arr, int *saving, int *boosters, int *price){
    
    int flag = 1;
    while(flag){
    
        printf("You can choose\n");
        if (*free_choices > 0){    // if free choice remains
            printf("  [number on cell] to open (- $0)\n");
            
        }else{
            printf("  [number on cell] to open (- $%d)\n", *open_cost);
            
        }
        printf("  [0] to continue the game\n");
        printf("Enter the number(s): ");
        
        int input;
        scanf("%d", &input);
        if ((*free_choices <= 0) && (*saving < *open_cost)){
            printf("You have no money!\n");
            break;
        }
        switch (graph_input_validate(input, n, choosen_arr)){
            case 1: // valid inut
            //printf("free choices %d\n", *free_choices);
                if(*free_choices > 0){
                    *free_choices-= 1;
                }else{
                    *saving -= *open_cost;
                    *open_cost += 500;
                }
                //printf("free choices %d\n", *free_choices);
                take_action_lottery(cell_value_calculation(input), saving, choosen_arr, free_choices, boosters, price, n, &input);
                //printf("free choices %d\n", *free_choices);
                break;
            case 2: // choose to 不抽繼續玩
                flag = 0;
                break;
            case 3: // invalid input
                printf("Invalid input!!!!\n");
                break;
        }
    }
}

int graph_input_validate(int input, int *n, int *choosen_arr){
    
    if (input > 0 && input <= (*n)*(*n) && choosen_arr[input-1] == 0){ // 正常選擇
        return 1;
    }else if(input == 0){ // 選擇離開
        return 2;
    }else{
        return 3;
    }
}

// 確認是否有需要initialize, 無則跳過
void choosen_arr_initialize(int *n, int *choosen_arr){
    int all_choosen = 1;
    for (int i=0;i<*n;i++){
        if (choosen_arr[i] == 0){
            all_choosen = 0;
            break;
        } 
    }
    
    if (all_choosen == 1){
        for (int i=0;i<*n;i++){
            choosen_arr[i] = 0;
        }
    }
}

void result_check(int results[], int results_sell[][2], int booster_status[]){
    int input;
    
    // Opeartions 取出他要求的並印出
    // 終止條件 1. booster開且input = 6, 2. booster沒開且 input = 5
    while ((booster_status[2] == 1 && input != 6) || (booster_status[2] == 0 && input != 5)){
        printf("Which result of the area you want to check?\n");
        printf("  [1] Area 1\n");
        printf("  [2] Area 2\n");
        printf("  [3] Area 3\n");
        printf("  [4] Area 4\n");
        if (booster_status[2] == 1){
            printf("  [5] Area 5\n");   // if booster open
            printf("  [6] Done\n");     // if booster open
        }else{
            printf("  [5] Done\n");     // if booster close
        }
        printf("Enter the number(s): ");
        scanf("%d", &input);
        if ((booster_status[2] == 1 && input == 6) || (booster_status[2] == 0 && input == 5)){break;}
        // operattion: 根據要求列印答案
        switch(results[input-1]){ // results[input-1] 是該區的action
            case 1:
                // lack of money to upgrade
                printf("Can't you tell how poor you are?\n");
                printf("Go vending your hotdogs instead of thinking about self-improvement!\n");
                break;
            case 2:
                // cannot reduce any time
                printf("Do you want to travel through time?\n");
                printf("GO WORK!!\n");
                break;
            case 3:
                // speed upgrade
                printf("You glimpse the secret of wind.\n");
                printf("Your hands can move faster now.\n");
                break;
            case 4:
                // taste upgrade
                printf("You feel the soul of the ingredients.\n");
                printf("Your hotdogs are more appetizing now.\n");
                break;
            case 5:
                // sell hotdogs
                printf("You make %d hotdogs here!\n", results_sell[input-1][0]);
                printf("You earn $%d!\n", results_sell[input-1][1]);
            
        }
    }
    
    
}

void bg_of_day(int *saving, int *speed_level, int *taste_level, int *time, int *price, int boosters[], int booster_status[]){
    *price = *taste_level*10 + 30;
    *time = 15 - *speed_level;
    printf("Chop chop, It's dawn.\n");
    printf("You have %d dollars.\n", *saving);
    printf("You need %d minutes to make a hotdog.\n", *time);
    printf("The price of a hotdog is $%d.\n", *price);
    printf("You have %d speed booster(s), %d price booster(s), %d area booster(s).\n", boosters[0], boosters[1] , boosters[2] );
    
    // small func that prints out messages
    void booster_message(int booster_status[]){
        printf("Open/Close boosters:\n");
        (booster_status[0] == 0) ? printf("  [1] Speed booster (now close)\n") : printf("  [1] Speed booster (now open)\n"); // if booster open;
        (booster_status[1] == 0) ? printf("  [2] Price booster (now close)\n") : printf("  [2] Price booster (now open)\n");
        (booster_status[2] == 0) ? printf("  [3] Area  booster (now close)\n") : printf("  [3] Area  booster (now open)\n");
        printf("  [4] Finish\n");
        printf("Enter the number(s): ");
    }
    
    
    int input;
    int flag = 1;
    while(flag){
        booster_message(booster_status);
        scanf("%d", &input);
        switch(input){
            case 1:
                // if off turn on else turn off
                if (booster_status[0] == 0){booster_status[0] = 1;}else{booster_status[0] = 0;}
                break;
            case 2:
                if (booster_status[1] == 0){booster_status[1] = 1;}else{booster_status[1] = 0;}
                break;
            case 3:
                if (booster_status[2] == 0){booster_status[2] = 1;}else{booster_status[2] = 0;}
                break;
            case 4: 
                flag = 0;
                break;
            default:
                printf("Invalid input!!!!\n");
                break;
        }
        
    }
}

int ask_action(int price, int up_speed_cost, int up_taste_cost, int time, int actions[]){
    
    
    // price*(180/time) this is mpney made if sell hot dog
    // choose action            
    printf("Actions you can take for each area:\n");
    printf("  [1] Sell the hotdogs\n");
    printf("  [2] Improve your cooking speed\n");
    printf("      (- $%d, - $%d, - $%d, - $%d for next four upgrades)\n", up_speed_cost, 2*up_speed_cost, 4*up_speed_cost, 8*up_speed_cost);
    printf("  [3] Improve your hotdog flavor\n");
    printf("      (- $%d, - $%d, - $%d, - $%d for next four upgrades)\n",up_taste_cost ,2*up_taste_cost ,4*up_taste_cost ,8*up_taste_cost );
    printf("Enter the number(s): ");
    scanf("%d %d %d %d", &actions[0], &actions[1], &actions[2], &actions[3]);
    
    // test validation
    for (int i=0;i<4;i++){
        //printf("actions[%d] = %d", i, actions[i]);
        if(actions[i] < 1 || actions[i] > 3){
            // re-enter action
            printf("Actions you can take at Area %d:\n", i+1);
            printf("  [1] Sell the hotdogs\n");
            printf("  [2] Improve your cooking speed\n");
            printf("  [3] Improve your hotdog flavor\n");
            printf("Enter the number(s): ");
            int temp;
            scanf("%d", &temp);
            actions[i] = temp;
        }
    }
    return 0;
}

void sell(int *saving,int *time, int price, int *day_earning, int booster_status[]){
    
    if (booster_status[0] == 1 ){ // speed booster open
        int profit = (180/ *time)*2*price; // 
        *saving += profit;
        *day_earning += profit;
    }else if(booster_status[1] == 1){ // taste booster on
        int profit = (180/ *time)*2*price; 
        *saving += profit;
        *day_earning += profit;
    }else{ // no booster
        int profit = (180/ *time)*price; 
        *saving += profit;
        *day_earning += profit;
    }
}

void up_speed(int *saving, int *up_speed_cost, int *speed_level){
    *saving -= *up_speed_cost;
    *up_speed_cost *= 2;
    *speed_level += 1;
    //printf("You glimpse the secret of wind.\nYour hands can move faster now.\n");
}

void up_taste(int *saving, int *up_taste_cost, int *taste_level){

    *saving -= *up_taste_cost;
    *up_taste_cost *= 2;
    *taste_level += 1;
    //printf("You feel the soul of the ingredients.\nYour hotdogs are more appetizing now.\n");
}

// results: [0][0] = area1 result , ... , [0][4] = area5 result. [1][0] = area1 earning(if any)
// [6] = area2 earning(if any) ... 
void take_action(int actions[], int *saving, int *time, int *price, int *day_earning, int *up_speed_cost, int *speed_level, int *up_taste_cost, int *taste_level, int booster_status[], int results[], int results_sell[][2]){
    for (int i=0;i<4;i++){ // [2,1,2,2]
        if (actions[i] == 1){
            sell(saving, time, *price, day_earning, booster_status);
            results[i] = 5; // 採取的行動
            
            if (booster_status[0] == 1){ // speed booster open
                
                int profit = (180/ *time)*2* (*price); // 暫存，為了存到results.
                results_sell[i][0] = (180/ *time)*2; // 在本區賣的熱狗數
                results_sell[i][1] = profit; // 在本區賺的錢
                
            }else if(booster_status[1] == 1){ // taste booster open
                
                int profit = (180/ *time)*(*price)*2; // 暫存，為了存到results.
                results_sell[i][0] = (180/ *time); // 在本區賣的熱狗數
                results_sell[i][1] = profit; // 在本區賺的錢    
                
            }else{                              // no booster open
            
                int profit = (180/ *time)*(*price); // 暫存，為了存到results.
                results_sell[i][0] = (180/ *time); // 在本區賣的熱狗數
                results_sell[i][1] = profit; // 在本區賺的錢 
            }
  
        }else if(actions[i] == 2){
            if (*saving >= *up_speed_cost && *time > 1){
                up_speed(saving, up_speed_cost, speed_level);
                results[i] =3; // 採取的行動
                *time = 15 - *speed_level;
            }else if(*saving < *up_speed_cost){
                // 沒錢升級
                sell(saving, time, *price, day_earning, booster_status);
                results[i] = 1; // 採取的行動
            }else{
                // 不能在快
                sell(saving, time, *price, day_earning, booster_status);
                results[i] = 2; // 採取的行動
            }
            
        }else if(actions[i] == 3){
            if (*saving >= *up_taste_cost){
                up_taste(saving, up_taste_cost, taste_level);
                *price = *taste_level*10 + 30;
                results[i] = 4; // 採取的行動
            }else{
                // 沒錢升級
                results[i] = 1; // 採取的行動
            }
        }
    }
    
    if (booster_status[2] == 1){ // area booster open
        sell(saving, time, *price, day_earning, booster_status);        
        int profit = (180/ *time)*(*price); // 暫存，為了存到results.
        
        results[4] = 5;
        results_sell[4][0] = (180/ *time); // 在本區賣的熱狗數
        results_sell[4][1] = profit; // 在本區賺的錢 
        
    }
    printf("Well done, you earn $%d today.\n", *day_earning);
}


// **************************Lottery***********************************************************************

// 輸出抽獎圖
int digit_count(int n){
    int digit = 0,remainder = n;
    while (remainder != 0){
        digit++;
        remainder /= 10;
    }
    return digit;
}
int reverse(int cell_num){
    int n, reverse = 0, remainder;

    n = cell_num;
    while (n != 0) {
    remainder = n % 10;
    reverse = reverse * 10 + remainder;
    n /= 10;
  }
    return reverse;
}

// 負責一行數字行
void graph_numline(int n){
    static int cell_num = 1;
    int num_of_minus = digit_count(n*n)+2;
    // 每個cell開始的|、" "和結束的" " 都用printf()印出
    // 所以當spaces == digit of cell num就要把cell num印出，不然就會不夠空格
    for(int i=0;i<n;i++){
        int spaces = num_of_minus - 2;
        printf("| ");
        while(spaces != 0){
            int digits = digit_count(cell_num); // digits = 2; spaces = 
            if (spaces == digits){
                printf("%d", cell_num);
                spaces-= digits; // 因為一次印了好幾個數字，所以要扣
            }else if(spaces > digits){
                printf(" ");
                spaces--;
            }else{
                printf("E");
            }   
        }
        printf(" ");
        cell_num++;
    }
    printf("|\n");
}
void graphing(int n){

    
    // 計算該印出的負號數
    int num_of_minus = digit_count(n*n)+2;
    //int spaces_left_in_cell = num_of_minus - 

    // 畫圖
    for (int row = 0; row<n; row++){ //等一下改成五
        for (int i = 0; i<2;i++){
            // +-那行
            if (i == 0){    
                for (int p = 0;p<n;p++){
                    for (int j=0;j<(num_of_minus+1);j++){
                        if (j== 0){
                            printf("+");
                        }else{
                            printf("-");
                        }  
                    }
                }
                printf("+\n");
            // 數字行
            }else{
                graph_numline(n);

            }
            
        }
        
    }
    // 最後那一行+-
    for (int p = 0;p<n;p++){
        for (int j=0;j<(num_of_minus+1);j++){
            if (j== 0){
                printf("+");
            }else{
                printf("-");
            }  
        }
    }
    printf("+\n");
} 


int power(int original, int n){
    int temp = 1;
    for (int i = 0; i<n;i++){
        temp = temp*original;
    }
    return temp;
}

// 輸入:cell num, 回傳為獎品
int cell_value_calculation(int cell_num){
    int temp = reverse(cell_num); // reverse後
    
    int prize = 0, n = 0;
    // 將temp視為hex並算出其decimal值
    while(temp !=0){
        prize += ((temp%10)*(power(16, n++)));
        temp /= 10;
    }
    return prize%9 + 1;
}


















