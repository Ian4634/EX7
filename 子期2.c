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
	printf("  [1] Speed booster (now close)\n");
	}
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
    printf("Welcome, young boss!\n");//Let's begining this largest game !
	int price=100; 
	int velocity=15;
	int money1=30;
	int money2=50; 
	int money3=100;
	int earn=0;
	int number=0;
	int total=0;
	int initial=1;


	int booster[3] = {5,5,5};
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
        
        total=0;
        printf("Chop chop, It's dawn.\n");
        printf("You have %d dollars.\n", price);                 //財產金額
        printf("You need %d minutes to make a hotdog.\n", velocity); //熱狗速度
        printf("The price of a hotdog is $%d.\n", money1);        //熱狗價格
        printf("You have %d speed booster(s), %d price booster(s), %d area booster(s).\n", booster[0], booster[1], booster[2]);
        
        int choose_booster=-1;
        //open_or_close_booster[0] = open_or_close_booster[1] =open_or_close_booster[2] =false;
        while(true) 
        {
        	
        	print_booster(open_or_close_booster); //輸出 booster information 
        	scanf("%d",&choose_booster); //使用者輸入選取數字1~4(4 for finish) 
        	if(check_booster_number(choose_booster)){// 確認使用者輸入合法的數字 
			
	        	if(choose_booster>=1 && choose_booster<=3) //確認使用者不是輸入4 
	        	{
	        		if(open_or_close_booster[choose_booster-1]==true) // 原本開啟 使用者要把它關閉 
	        		{
	        			open_or_close_booster[choose_booster-1]=false;
					}
					else // 原本關閉 使用者要把它開啟 
					{
						open_or_close_booster[choose_booster-1]=true;
					}
				}
				else if(choose_booster ==4) //使用者輸入4 代表跳出booster迴圈 
				{
					break;
				}
			}
			
		}//!!!! 一開始不需要檢查是否還有booster庫存(題目要求)，就算沒有庫存booster還是需要顯示開啟或關閉的狀態
		int check_speed_booster = 0;
		int check_price_booster = 0; 
		if(open_or_close_booster[1]==true && booster[1] >0 ) //使用者選擇完畢後才會開始判斷是否可以進行boost 
		{
				check_price_booster = 1;
				 booster[1] -=1;
			
		} 
		else if(open_or_close_booster[1]==true && booster[1] <=0)
		{
			open_or_close_booster[1] = false;
		}
		if(open_or_close_booster[0]==true && booster[0]>0)
		{
			
			check_speed_booster = 1;
			booster[0] -=1;
			
		}
		else if(open_or_close_booster[0]==true && booster[0]<=0)
		{
			open_or_close_booster[0] = false;
			check_speed_booster  = 0;
		}
		int area_flag = 0; //確認 area_booster 是否有實際開啟 0: close 1:open 
		if(open_or_close_booster[2]==true && booster[2] >0)
		{
			area_flag = 1;
			booster[2] -= 1;
		}
		else if(open_or_close_booster[2]==true && booster[2] <=0)
		{
			open_or_close_booster[2] = false;
		}
		printf("Actions you can take for each area:\n");  
		printf("  [1] Sell the hotdogs\n");
		printf("  [2] Improve your cooking speed\n");
		printf("      (- $%d, - $%d, - $%d, - $%d for next four upgrades)\n", money2, money2*2, money2*4, money2*8);
		printf("  [3] Improve your hotdog flavor\n");
		printf("      (- $%d, - $%d, - $%d, - $%d for next four upgrades)\n", money3, money3*2, money3*4, money3*8);
		printf("Enter the number(s): ");
		int area_action[4]={0,0,0,0};
		for(int i=0;i<4;i++)
		{
			scanf("%d", &area_action[i]); //與ex5不同，ex7為一次輸入四個區域 
										//(第五個區域不用輸入 因為若有開啟 題目限制一定要sell hot dog) 
		}
		
		int result_message[5] = {0,0,0,0,0}; //置放要輸出的訊息代號 
		int earn_money[5] = {0,0,0,0,0}; //各區域所賺的錢 
		int earn_number[5] = {0,0,0,0,0}; //各區域所製作的熱狗數量 
		
			
			for(int i=0;i<4;i++) //當使用者輸入某個區域的選擇是錯誤的時候 必須請使用者重新輸入針對該區域的重新選擇 
			{
				if(area_action[i]<1 || area_action[i]>3) //判斷使用者於每個區域輸入的數字是否是合法的 
				{
					
					
					while(true){
							printf("Invalid input!!!!\n");
							printf("Actions you can take at Area %d:\n", i+1);
							printf("  [1] Sell the hotdogs\n");
							printf("  [2] Improve your cooking speed\n");
							printf("  [3] Improve your hotdog flavor\n");
							printf("Enter the number(s): ");
							scanf("%d", &area_action[i]);	
							if(area_action[i]>=1 && area_action[i]<=3){ //重新輸入後合法，若依然不合法則繼續while 迴圈 
								
								break;
							}
						
					}
				}
			}
		
		/*	測試只輸出一次invalid input*/
	
		total = 0;
		for(int i=0;i<4;i++)
		{
			switch(area_action[i]){ //根據不同的數字採取不同的動作(1: sell 2: upgrade 3:upgrade) 
				case 1:
					number = 180 / velocity;
					if(check_speed_booster==1)
					{
						number *=2;
					}
					if(check_price_booster==1)
					{
						earn = number*money1*2;
					}
					else
					{
						earn = number*money1;
					}
				
					price += earn;              //財產+當下收入
                    total += earn;//當天收入+當下收入
                	earn_money[i] = earn; //各個area 個別的收入 
					earn_number[i] = number; //各個area 個別的數量 
					break;
                case 2:
                	if(price >= money2)
                	{
                		if(velocity > 1)
                		{
                				price -= money2; //財產-消費價格
		                		velocity-=1;     //速度-1 
		                        money2 *= 2; //價格變2倍  /* 提升velocity後也會連續影響後面的area 且upgrade的價格也會隨之提升*/ 
		                		break;
						}
						else
						{
							result_message[i] = -2; //無法提升(速度已為1 無法再加速) 
								//強制賣熱狗 
							number = 180 / velocity;
							if(check_speed_booster==1)
							{
								number *=2;
							}
							if(check_price_booster==1)
							{
								earn = number*money1*2;
							}
							else
							{
								earn = number*money1;
							}
							
							price += earn;              //財產+當下收入
		                    total += earn;//當天收入+當下收入
		                	earn_money[i] = earn; //各個area 個別的收入 
							earn_number[i] = number; //各個area 個別的數量 
							break;
						}
					}
					else
					{
							result_message[i] = -1; //無法提升(財產不足) 
						//強制賣熱狗 
						number = 180 / velocity;
						if(check_speed_booster==1)
						{
							number *=2;
						}
					if(check_price_booster==1)
					{
						earn = number*money1*2;
					}
					else
					{
						earn = number*money1;
					}
						price += earn;              //財產+當下收入
	                    total += earn;//當天收入+當下收入
	                	earn_money[i] = earn; //各個area 個別的收入 
						earn_number[i] = number; //各個area 個別的數量 
                        break;
					}
				case 3:
					if (price >= money3)
					{
						
						price -= money3; //財產-消費價格
                        money1 += 10; //熱狗價格+10
                        money3 *= 2;
                        break;
					}
					else if (price < money3) //無法提升(財產不足) 
					{
						
						result_message[i] = -3;
							//強制賣熱狗 
						number = 180 / velocity;
						if(check_speed_booster==1)
						{
							number *=2;
						}
						if(check_price_booster==1)
					{
						earn = number*money1*2;
					}
					else
					{
						earn = number*money1;
					}
						price += earn;              //財產+當下收入
	                    total += earn;//當天收入+當下收入
	                	earn_money[i] = earn; //各個area 個別的收入 
						earn_number[i] = number; //各個area 個別的數量 
						break;
					}
					
			}
		}
		int result_check = 0;
		if(area_flag==1){ //若有開啟area booster 則 需計算 金額與販賣數量 
			if(check_speed_booster==1){
				if(check_price_booster==1)
				{
						total += (180/velocity)*2*money1*2;
						
						price += (180/velocity)*2*money1*2;
				}
				else
				{
						total += (180/velocity)*2*money1;
						
						price += (180/velocity)*2*money1;
				}
				
			}
			else
			{
				if(check_price_booster==1)
				{
						total += (180/velocity)*money1*2;
						
						price += (180/velocity)*money1*2;
				}
				else
				{
						total += (180/velocity)*money1;
						
						price += (180/velocity)*money1;
				}
			}
		}
		printf("Well done, you earn $%d today.\n", total); //total 為所有攤販收入的總和 
		
		int stop_area_chek_flag = 0; // 確認area_booster是否有凱契並對應接下來所需要停止while迴圈所需的判斷變數 
		do{ //可分別檢視各個攤販狀況 
			printf("Which result of the area you want to check?\n");
			printf("  [1] Area 1\n");
			printf("  [2] Area 2\n");
			printf("  [3] Area 3\n");
			printf("  [4] Area 4\n");
			if(area_flag==1) // area_booster 開啟 
			{
				print_with_area_booster();
			}
			else
			{
				print_without_area_booster(); 
			}
			printf("Enter the number(s): ");
		
			scanf("%d",&result_check);
			/* 檢查使用者輸入是否合法 */ 
		
			if(result_check>=1 && result_check<=4)
			{
				print_result_messge(result_check-1,result_message, area_action, earn_number,earn_money, area_flag);
			}
			else if(result_check ==5)
			{
				if(area_flag==1)
				{
					if(check_speed_booster==1)
					{
						if(check_price_booster==1)
						{
							printf("You make %d hotdogs here!\n",(180/velocity)*2); // 因為是最後一個區域且只能sell hot dog所以直接計算即可 
							printf("You earn $%d!\n",(180/velocity)*2*money1*2); //因為是最後一個區域且只能sell hot dog所以直接計算即可 
						}
						else
						{
							
							printf("You make %d hotdogs here!\n",(180/velocity)*2); // 因為是最後一個區域且只能sell hot dog所以直接計算即可 
							printf("You earn $%d!\n",(180/velocity)*2*money1); //因為是最後一個區域且只能sell hot dog所以直接計算即可 
						}
						
					}
					else
					{
						if(check_price_booster==1)
						{
							printf("You make %d hotdogs here!\n",(180/velocity)); // 因為是最後一個區域且只能sell hot dog所以直接計算即可 
							printf("You earn $%d!\n",(180/velocity)*2*money1*2); //因為是最後一個區域且只能sell hot dog所以直接計算即可 
						}
						else
						{
							
							printf("You make %d hotdogs here!\n",(180/velocity)); // 因為是最後一個區域且只能sell hot dog所以直接計算即可 
							printf("You earn $%d!\n",(180/velocity)*money1); //因為是最後一個區域且只能sell hot dog所以直接計算即可 
						}
						
					}
					
				}
				else
				{
					stop_area_chek_flag =1; // 沒有 area booster 所以代表要結束 
					break;
				}
				
			}
			else if(result_check==6 && area_flag==1) //使用者選擇6 且有 area booster 代表要結束 
			{
				stop_area_chek_flag =1;
			}
			else
			{
				printf("Invalid input!!!!\n");
			}

		}while(stop_area_chek_flag==0);
		
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
	if(continue_or_exit==2)
	{	printf("We will miss you. Bye!\n");
		break;
		
	}
}
}
