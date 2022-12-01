#include<stdio.h>

// 進度: lottery值func 完成

// 呼叫時，負責印出圖、讓使用者抽獎、將獎品效用存起來
int lottery(int n){
    static int prizes_remain = 25; // 每抽一次減一，歸零時變成(n+2)*(n+2)
    static int prize[100000]; // 記錄各cell之獎品，抽過為0
    return 0;
}

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
void graphing(){
    static int n = 11;
    static int prizes_left = 25; //會一直變動
    int cell_num = 1;

    // 處理剩餘獎品數
    if (prizes_left>0){
        --prizes_left;
    }else if(prizes_left == 0){
        prizes_left = (n+2)*(n+2);
    }else{
        printf("sth in line 34 went wrong");
    }
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
    return prize;
}
int main(){
    graphing();
    return 0;
}