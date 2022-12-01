#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
void print_booster(bool open_or_close_booster[])
{
	// false : 關閉 ; true: 開啟 
	// open_or_close_booster[0] ~  open_or_close_booster[2] 分別對應 1.speed 2.Price 3.Area booster  用此陣列用來表示booster狀態 
	printf("Open/Close boosters:\n");
    if(open_or_close_booster[0]==false){
	printf("  [1] Speed booster (now close)\n");}
    else{printf("  [1] Speed booster (now open)\n");}
    if(open_or_close_booster[1]==false){printf("  [2] Price booster (now close)\n");}
    else{printf("  [2] Price booster (now open)\n");}
    if(open_or_close_booster[2]==false){printf("  [3] Area  booster (now close)\n");}
    else{printf("  [3] Area  booster (now open)\n");}
    printf("  [4] Finish\n");
    printf("Enter the number(s): ");
}
bool check_booster_number(int booster_number)
{
	if(booster_number <1 || booster_number >4) //確認使用者輸入欲開啟的booster number 是否合法 
	{
		printf("Invalid input!!!!\n");
		return false;
	}
	return true;
	
}
bool lottery_checking(int *x_index, int check_number,int x_index_index) //判斷欲打開的樂透號碼是否已被選過 
{

 	bool flag =false;
	for(int i=0;i<x_index_index;i++)
	{
		if(check_number == x_index[i])
		{
			flag = true;
			break; 
		}
	}
	return flag;
}



void print_lottery(int n, int *x_index,int x_index_index) //印出樂透 
{

	int temp = n;
	
	int count_digit = 0;
	
	while(temp!=0)
	{
		
		temp /= 10;
		count_digit++;
	}

	int count =1;//計算最大位數是幾位 
	
	// 照著範例填入空白資訊的解答 
	for (int i = 0; i < (sqrt(n)); i++){
    	printf("+");
	    for (int j = 0; j < (sqrt(n)); j++){
	        for (int k = 0; k < (count_digit)+2; k++) printf("-");
	        printf("+");
	    }
    	printf("\n|");
	    for (int j = 0; j < (sqrt(n)); j++){
	        if (lottery_checking(x_index, count, x_index_index)) printf(" %*c |", count_digit, 'x');
	        else printf(" %*d |", count_digit, count);
	        count++;
	    }
    	printf("\n");
	}
	printf("+");
	for (int j = 0; j <(sqrt(n)); j++){
    	for (int k = 0; k < (count_digit)+2; k++) printf("-");
    	printf("+");
	}
	printf("\n");

}



void print_result_messge(int index, int result_message[], int area_action[], int earn_number[], int earn_money[], int area_flag)//印出指定區域需輸出的訊息 
{

		if(area_action[index] == 1) //代表這個區域使用者是選擇販賣熱狗 (1) 
		{
				printf("You make %d hotdogs here!\n",earn_number[index]);
				printf("You earn $%d!\n",earn_money[index]);
		}
		else if(area_action[index] ==2) //代表這個區域使用者是選擇升級(2) 
		{
				if(result_message[index]==0) //按照EX5給定的條件輸出 
				{
						printf("You glimpse the secret of wind.\n");
                        printf("Your hands can move faster now.\n");
				}
				else if(result_message[index]==-1)//按照EX5給定的條件輸出 
				{
							printf("Can't you tell how poor you are?\n");
                            printf("Go vending your hotdogs instead of thinking about self-improvement!\n");
                            printf("You make %d hotdogs here!\n",earn_number[index]);
							printf("You earn $%d!\n",earn_money[index]);
				}
				else if(result_message[index]==-2)//按照EX5給定的條件輸出 
				{
					printf("Do you want to travel through time?\n");
                    printf("GO WORK!!\n");
                    printf("You make %d hotdogs here!\n",earn_number[index]);
					printf("You earn $%d!\n",earn_money[index]);
				}
		}
		else if(area_action[index]==3)//代表這個區域使用者是選擇升級(3) 
		{
			if(result_message[index]==-3)//按照EX5給定的條件輸出 
			{
				printf("Can't you tell how poor you are?\n");
                printf("Go vending your hotdogs instead of thinking about self-improvement!\n");
                printf("You make %d hotdogs here!\n", earn_number[index]);
				printf("You earn $%d!\n", earn_money[index]);
			}
			else//按照EX5給定的條件輸出 
			{
				 printf("You feel the soul of the ingredients.\n");
                 printf("Your hotdogs are more appetizing now.\n");
			}
		}
	

}



int lottery_prize(int lottery_type, int size, int money1,int *x_index, int x_index_index) //根據選擇的號碼對應得到的prize 
{

		
	
		int temp_index = x_index_index -1;  
		int last_number = x_index[temp_index]-1; // prize 4~6 根據上次 current cell 隨機選取上下左右相鄰cell 
		int row_number = sqrt(size); //(n*n)開根號 == n 
		int answer =0;
	
			switch(lottery_type) // type 1~9
			{
				case 1:
					printf("Fortune, fortune! You get $%d!\n",(100*money1)); //type1: 獲得獎金  會在main funciton 將獎金計入總和 
					return -1;
				case 2: // type 2 : 獲得免費兌換券   會在main funciton 將兌換券疊加 
					printf("You get an extra choice!\n");
					return -2;
					
				case 3: // the above of the current cell 
					if(last_number>=0 && last_number < row_number) // 代表第一列 第一列cell的上面鄰居cell是最下方
					{
							answer = (last_number+ row_number*(row_number-1)+1);
					} 
					else
					{
							answer = last_number - row_number+1; // 不是邊界的話直接取上方cell 
					}
					//需先確認是否可開啟 
					if(lottery_checking(x_index, answer, x_index_index))
					{
							printf("Bad Luck :(\n"); //若無法開啟 則印出bad luck訊息 
							return -100;
					}
					else
					{
						//printf("open above\n");
						printf("Another open on %d!\n", answer);	//若開啟 則印出bad luck訊息 並在mian funciton中重新進行抽獎(新的號碼) 
						
						return answer;
					}
					break;
				case 4://隨機選取另外一個號碼 
				
					// current cell 下方 cell 
					 
					if(last_number/ row_number == (row_number-1)) // 代表最後一列 最後一列cell下面的鄰居cell是最上方
					{
							answer = (last_number-(row_number*(row_number-1))+1);
					} 
					else
					{
							answer =  last_number + row_number+1; // 不是邊界的話直接取下方cell 
					}
					
					
						
					
					if(lottery_checking(x_index, answer, x_index_index))
					{
							printf("Bad Luck :(\n");//若無法開啟 則印出bad luck訊息 
							return -100;
					}
					else
					{
						//printf("open  underneath\n");
						printf("Another open on %d!\n", answer);	
						return answer;
					}
					break;
				case 5://隨機選取另外一個號碼 
				
					if(last_number%row_number ==0) // 代表最左行 最左行cell左方的鄰居cell是最右方
					{
						answer = (last_number+row_number-1+1); // 寫-1+1比較好理解 也可直接+rownumber 
					} 
					else
					{
						answer  = last_number -1+1; // 不是邊界的話直接取左方cell 寫-1+1比較好理解 也可直接寫 last_number 
					}
				
					
					if(lottery_checking(x_index, answer,x_index_index))
					{
							printf("Bad Luck :(\n");//若無法開啟 則印出bad luck訊息 
							return -100;
					}
					else
					{
					//	printf("open left\n");
						printf("Another open on %d!\n", answer);	//若開啟 則印出bad luck訊息 並在mian funciton中重新進行抽獎(新的號碼) 
						
						return answer;
					}
					break;
				case 6://隨機選取另外一個號碼 
					if(last_number%row_number ==(row_number-1)) // 代表最右行 最右行cell右方的鄰居cell是最左方
					{
							answer =  (last_number-(row_number-1)+1); // 寫-1+1比較好理解 也可直接+rownumber 
					} 
					else
					{
						answer =  last_number +1+1; // 不是邊界的話直接取右方cell 寫+1+1比較好理解 也可直接寫 last_number+2 
					}
			
				
					if(lottery_checking(x_index, answer,x_index_index))
					{
							printf("Bad Luck :(\n");//若無法開啟 則印出bad luck訊息 
							return -100;
					}
					else
					{
						//printf("open right\n");
						printf("Another open on %d!\n", answer);	//若開啟 則印出bad luck訊息 並在mian funciton中重新進行抽獎(新的號碼) 
						
						return answer;
					}
					break;
				case 7: // 獲得一個speed booster 會在main funciton 中疊加 
					printf("You get a booster!!\n"); 
					return -3;
					break;
				case 8:// 獲得一個 price booster 會在main funciton 中疊加 
					printf("You get a booster!!\n");
					return -4;
					break;
				case 9: //獲得一個 area booster 會在main function 中疊加 
					printf("You get a booster!!\n");
					return -5;
					break;
					
			}
			return -500; // error code
}
	

bool check_whether_could_play_lottery(int price, int lottery_price, int lottery_choice) //確認是否還有足夠金額可以玩樂透 
{
	if((price - lottery_price)<0)
	{
		printf("You have no money!\n");
		return false;
	}
	return true;
}
void print_without_area_booster() //輸出沒有area booster的選擇訊息 
{
	printf("  [5] Done\n");
}
void print_with_area_booster()//輸出 有area booster的選擇訊息 
{
	printf("  [5] Area 5\n");
	printf("  [6] Done\n"); 
}
int main(){
    //printf("Welcome, young boss!\n");//Let's begining this largest game !
	int price=100; 
	int velocity=15;
	int money1=30;
	int money2=50; 
	int money3=100;
	int earn=0;
	int number;
	int total;
	int initial=1;


	int booster[3] = {0,0,0};
	int x_index_index = 0;
	bool open_or_close_booster[3] = {false, false, false};
	int lottery_count = 0;//兌換券數量  
	int lottery_price = 500; //樂透遊玩起始金額 
	int n = 3;
	int *x_index;
	x_index = (int*)malloc(sizeof(int)*(n)*(n)); //置放樂透號碼的動態陣列 
	
	/*
	area(地點)、price(財產)、velocity(做熱狗速度)、
	money1(熱狗價格)、money2(提升速度的價格)、money3(提升廚藝的價格)
	motivate(動機)、earn(當下收入)、number(做的熱狗數量)、want_to_count(是否繼續)
	total(當天總收入)、verify_area(確認總合是否為10)、
	initial、normal、select、sum、End(這些變數只是判斷要不要進入迴圈而已，沒有別的意思。)*/
	int test____tset_a=0;
	int day = 1;
    while(initial==1){ // 仿照EX5 的while迴圈  
        

		
		
		int continue_or_exit = 0;
		int count =0;
		
	
		
	/* 確認使用者要繼續還是要跳出*/ 
	do{
		if(count >0)
		{
			printf("Invalid input!!!!\n");
		}
		printf("Do you want to continue or exit?\n");
		printf("  [1] Continue\n");
		printf("  [2] Exit\n");
		printf("Enter the number(s): ");
		scanf("%d",&continue_or_exit);
		count++; // do this while loop at least twice 
	}while(continue_or_exit != 1 && continue_or_exit != 2); //確認使用者輸入數字是否正確(1~2) 
	
	
	
	
	int lottery_choice=0; //樂透選擇的代號 
	
	
	
	if(continue_or_exit ==1)
	{
		int flag = 0;
		printf("You get one free choice.\n");
		lottery_count += 1;
		//lottery_price = 500;
		//printf("lotter_count %d\n",lottery_count);
		int check_can_play_lottery = 0 ;
		while(flag == 0){	
			if(x_index_index >= (n*n))
			{
				n += 2;
				x_index = (int*)malloc(sizeof(int)*(n)*(n)); //置放樂透號碼的動態陣列 
				x_index_index = 0; 
				lottery_price = 500;
			}
		
			print_lottery(n*n, x_index, x_index_index); //輸出樂透號碼 
			int checking_number = 0;
			int err_count =0; //檢查使用者輸入是否合法 
			do{
					if(err_count>=1)
					{
						printf("Invalid input!!!!\n");
						checking_number = 1;
						break;
						
					}
					printf("You can choose\n");
					if(lottery_count > 0){ //檢查是否是拿免費兌換券兌換 (不須付費) 
						printf("  [number on cell] to open (- $0)\n");    // if free choice remains
						printf("  [0] to continue the game\n");
						printf("Enter the number(s): ");
						scanf("%d",&lottery_choice);
					}
					else //已使用完全部的免費兌換券(須付費抽獎) 
					{
						printf("  [number on cell] to open (- $%d)\n", lottery_price);
						printf("  [0] to continue the game\n");
						printf("Enter the number(s): ");
						scanf("%d",&lottery_choice);
						if(lottery_choice != 0){
						
								if(lottery_checking(x_index, lottery_choice,x_index_index))
								{
									break;
								}
								if(!check_whether_could_play_lottery(price, lottery_price, lottery_choice))
								{
									check_can_play_lottery = 1;
						
									break;
								}
						}
						else
						{
							break;
						}
						
					}
					
					if(lottery_choice ==0)
					{
						break;// 0:跳出抽獎環節 繼續下一天的遊戲 
					} 
				
					err_count +=1;
			}while(lottery_choice< 1 || lottery_choice> (n*n));
		
			if(checking_number !=1){
			
			if(lottery_choice == 0)
			{
				day +=1;
				break;
			}
			if(check_can_play_lottery==1) //沒有足夠金額繼續玩樂透  退出樂透遊戲 
			{
				day +=1;
				break;
			}
			 
			if(!lottery_checking(x_index, lottery_choice,x_index_index)) //檢查使用者輸入的樂透號碼是否合法 
			{
				x_index[x_index_index] = lottery_choice; //存入陣列中代表此號碼已被抽過 
				x_index_index++;
					
			
				if(lottery_count <= 0)   //代表兌換券已使用完畢 
				{
				
					price-= lottery_price;
					lottery_price += 500; //下次金額需加500 
				}
				else
				{
					
					lottery_count -=1; //若還有使用券則扣掉一張使用券 
				}
				
				/*   計算 使用者選擇的樂透號碼對應到的prize type 
					1. reverse the number (EX: 123 -> 321)
					2. take it as hex (321)(16進位)
					3. change it to decimal -> (1 * 16**0) + (2 * 16**1) + (3 * 16**3)
					4. module it by 9(get 0~8 number) and then plus one (you get 1~9) 對應到 prize 1~9  
				*/ 
				int reverse=0;
				int remainder = 0;
				while (lottery_choice != 0) { //reverse the lottery number which user choose
				    remainder = lottery_choice % 10;
				    reverse = (reverse * 10) + remainder;
				    lottery_choice /= 10;
				}
			
				int hex_to_dec = 0;
				int count_index = 0;
				while(reverse != 0) // take the reverse number as hexadecima and change it to decimal 
				{
					hex_to_dec += (reverse%10)*pow(16,count_index);
					count_index++;
					reverse /= 10;
				}
		
				int lottery_type = (hex_to_dec % 9) + 1; // modile this decimal number by 9 and plus 1 
				int stop_flag = 0;
				int return_type = lottery_prize(lottery_type, n*n,money1, x_index, x_index_index);// choose prize type
				
				while(stop_flag ==0){ //根據樂透抽獎回傳的type 進行相對應的動作  這個while回圈請跟 lottery_prize fuction 搭配  
					if(return_type == -1)
					{
						
						price += (100*money1);
						stop_flag = 1;
					//	printf("type: -1\n");
					}
					else if(return_type ==-2)
					{
						
						lottery_count +=1;
						stop_flag = 1;
						//printf("type: -2\n");
					}
					else if(return_type == -3)
					{
					
						booster[0] +=1;
						stop_flag = 1;
					//	printf("type: -3\n");
					}
					else if(return_type==-4)
					{
					
						booster[1] +=1;
						stop_flag = 1;
					//	printf("type: -4\n");
					}
					else if(return_type==-5)
					{
					
						booster[2] += 1;
						stop_flag = 1;
					//	printf("type: -5\n");
					}
					else if(return_type == -100)
					{
						
						stop_flag = 1;
					//	printf("type: -100\n");
					}
					else //代表要重新開另外一個號碼 再進行一次 lottery_prize function 
					{	
						reverse= 0;
						remainder =0;
						hex_to_dec = 0;
						count_index = 0;
						x_index[x_index_index] = return_type;
						x_index_index++;
						while (return_type != 0) { //reverse the lottery number which user choose
							    remainder = return_type % 10;
							    reverse = (reverse * 10) + remainder;
							    return_type /= 10;
						}
						while(reverse != 0) // take the reverse number as hexadecima and change it to decimal 
						{
							hex_to_dec += (reverse%10)*pow(16,count_index);
							count_index++;
							reverse /= 10;
						}
						//printf("type: another number\n");
						return_type = lottery_prize((hex_to_dec % 9) + 1, n*n, money1, x_index, x_index_index);
					/*	if(return_type>=1&& return_tpye<= (n+2)*(n+2))
						{
							x_index[x_index_index] = return_type;
							x_index_index++;
						}*/
					}					
				}
			
			}
			else //不合法的輸入  
			{
				printf("Invalid input!!!!\n");
			}
	}
		
	}
		
	}
	else //結束遊戲 
	{
		printf("Speed booster: %d\n",booster[0]);
		printf("Price booster: %d\n",booster[1]);
		printf("Area booster: %d\n",booster[2]);
		printf("Money: %d\n",price);
		printf("Free choice: %d\n",lottery_count);
		printf("We will miss you. Bye!\n");
		break;
	}

	}
}
