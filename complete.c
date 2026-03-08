#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#define USERNAME "admin"
#define PASSWORD "admin"
struct client{
	char name[50];
	int id;
	char accountNo[15];
	char phoneNumber[15];
	char password[30];
	float balance;
	float interestRate;
	float interest;
}c[100];
int globalCount;
char globalAccountNo[15];
int main()
{
	while(1){
	system("cls");
	char choice_1[20], ch;
	//char admin[5]= "admin", client[6]= "client";
	int TRUE=1, FALSE=0, value;
	printf("**************************************************\n");
	printf("**************************************************\n\n");
	printf("\tWelcome to Banking System!\n\n");
	printf("**************************************************\n");
	printf("**************************************************\n\n");
	printf("\tSelect Menu:\n");
	printf("\t1.Admin\n\t2.Client\n\t3.Exit\n");

		gets(choice_1);
		if(strcmp(choice_1, "1") == 0 || strcasecmp(choice_1, "admin")==0)
			{
				printf("\tWelcome to Admin portal! Please login to continue...\n");
				//security system
				value=login();
				printf("\n");
				if(value==TRUE)
				{
					adminFunction();
					
				}
				else{
					break;
				}
				
			}
		else if(strcmp(choice_1, "2") == 0 || strcasecmp(choice_1, "client")==0)
			{
				clientFunction();
				
			}
		else if(strcmp(choice_1, "3") == 0){
			printf("\nProgram Terminated\n");
			break;
		}
		else
			{
				printf("\tNo valid options selected! Try again or press 'esc' to exit!\n");
				if((ch=getch()) == 27)
					{
						printf("\tTerminated Successfully!\n ");
						break;
					}
			}
}

	
	getch();
	return 0;
}
//login system
int login()
{
	int i;
	int attempts = 3;
	char user[10], pass[10];
	char ch;
	while(attempts !=0)
	{
		printf("\n\nEnter login details:");
		printf("\nUsername: ");
		fgets(user, sizeof(user), stdin);
		user[strcspn(user, "\n")] = '\0';
		printf("Password: ");
		i=0;
			while( (ch = getch()) != 13)
			{
				pass[i] = ch;
				i++;
				printf("*");
			}
		pass[i]='\0';
		if ((strcmp(PASSWORD, pass)== 0) && strcmp(USERNAME, user)==0)
		{
			printf("\n\n------------Login successful! Wait few seeconds------------ ");
	        Sleep(1500);
			return 1;
			attempts = 0;
		}
//		else if ((strcmp(PASSWORD, pass)== 0) && strcmp(USERNAME, user)!=0)
//		{
//			printf("\nLogin failed! Username not found.");
//			if(attempts==0)
//			printf("\n%d attempts left. ", --attempts);
//		}
//		else if ((strcmp(PASSWORD, pass)!= 0) && strcmp(USERNAME, user)==0)
//		{
//			printf("\nLogin failed! Incorrect password.");
//			printf("\n%d attempts left. ", --attempts);
//		}
		else{
			printf("\nLogin failed! Username and password not found.");
			attempts--;
			if (attempts !=0){
				printf("\n%d attempt left. ", attempts);
			}
			else{
				printf("\nCan't login! Contact headoffice. ");
				return 0;
				break;
			}
			
		}
	}
}
//count data in file
int count()
{  
	int count, temp, maxId = 0;
    FILE *fptr;

    fptr = fopen("clients.txt", "rb");
    if (fptr == NULL) {
        fopen("clents.txt", "rb");  // exit early on error
    }

    count = 0;
    while (fread(&c[count], sizeof(struct client), 1, fptr) == 1) {
        temp = c[count].id;
        if (temp > maxId) {
            maxId = temp;
        }
        count++;

        if (count >= 100)
        {
        	printf("Error while counting. Size limitation.\n");
        	break;
		}
    }

    //printf("count = %d, maxId = %d", count, maxId);
    strcpy(globalAccountNo, c[maxId-1].accountNo); //maxId-1 because array index starts from zero. 
    globalCount = count;
    //printf("max id: %d, account no: %s, \n count: %d", maxId, c[maxId-1].accountNo, count);
	fclose(fptr);
	return maxId;
}
//admin function
void adminFunction()
{ 
	int cnt=count();int adch, subch, menuch;
	char name[30];
	int flag=0, t, i;
    FILE *fptr;
	fptr = fopen("clients.txt", "rb");
	fread(c, sizeof(struct client), cnt, fptr);
	while(1){
	system("cls");
	printf("*************1.Register client **********\n");
	printf("*************2.Search Client   **********\n");
	printf("*************3.Update Balance  **********\n");
	printf("*************4.Withdraw Balance**********\n");
	printf("*************5.Exit            **********\n");
	scanf("%d", &adch);
	fflush(stdin);
	if (adch==2){
	while(1){
	t=search();
	if(t!=-1)
	{
		printf("Client found! \n");
		printf("Name: %s\nID: %d\nAccount number: %s\nPhone number: %s\nAccount balance: %f\nInterest amount: %f\nCurrent interest rate: %f\n", c[t].name, c[t].id, c[t].accountNo, c[t].phoneNumber, c[t].balance, c[t].interest, c[t].interestRate);
	    
	}
	else if(t==-1){
		char ch;
		printf("Client not found! Press 1 for new registration and esc to return to menu.\n");
		fflush(stdin);
		if((ch=getch())==49)
		{
			newRegistration();
			//printf("new registration function currently under construction. Please come back later!");
		}
		else if((ch=getch())==27){
			break;
		}
		else
		{
			printf("Program terminated");
			getch();
			return 1;
		}
		
	}
	printf("\n\n1.Continue searching\n");
	printf("2.Return\n");
	scanf("%d", &menuch);
	if(menuch==1){
		continue;
	}
	else if(menuch==2){
		break;
	}
	}}
	else if(adch == 1){
		newRegistration();
	}
	else if(adch == 3){
		printf("\n*******1.Update deposit*******\n");
		printf("\n*******2.Add Interest*******\n");
		scanf("%d", &subch);
		if(subch==1){
			updateDepo();
		}
		if(subch==2){
			addInterest();
		}
	}
	else if(adch ==4){
		withdrawAmnt();
	}
	else if(adch == 5){
		fclose(fptr);
		break;
	}
	
}}
//new registration
void newRegistration()
{
	int maxId=count();
	int i;
	//to create new account number
	long long int num;
	char newAccountNo[15];
//	printf("%s\n", globalAccountNo); error handeling
	num = atoll(globalAccountNo);
	num+=10;
//	printf("%lld", num); error handeling
	sprintf(newAccountNo, "%lld", num);
//	printf("\n%s", newAccountNo); error handeling
	FILE *fptr;
	fptr = fopen("clients.txt", "ab");
	if(fptr==NULL)
	{
		printf("Error! File couldn't be opened for new registration.");
	}
	else{
		
		printf("\n-------------Enter client details-------------\n");
			i=globalCount+1;
//			printf("Client ID: ");
//			scanf("%s", c[cnt].id);
			c[i].id=maxId+1;
			printf("Client ID: %d\n", c[i].id);
			printf("Name: ");
			fflush(stdin);	
			gets(c[i].name);
			strcpy(c[i].accountNo, newAccountNo);
			printf("Account Number: %s\n", c[i].accountNo);
//			printf("Account number: ");
//			fflush(stdin);
//			gets(c[i].accountNo);
			printf("Contact number: ");
			fflush(stdin);
			gets(c[i].phoneNumber);
			printf("Account balance: ");
			scanf("%f", &c[i].balance);
			printf("Current interest rate(p.a.): ");
			scanf("%f", &c[i].interestRate);
		}
		fwrite(&c[i], sizeof(struct client),1, fptr);
		printf("\nClients data stored successfully!. press enter to return to menu.\n");
		getch();
	fclose(fptr);
	
}



void addInterest(){
	    int cnt = count();
	    int a;
	    char name[30];
	    int i, flag=0, time;
	    FILE*fptr;
	    fptr = fopen("clients.txt", "rb+");
    	a=search();
	    if(a!=-1){
	    	printf("\nenter the time of interest to be added in months:\n");
		    scanf("%d", &time);
	    	c[a].interest = (c[a].balance*(time/12.0)*c[a].interestRate)/100;
	        c[a].balance=c[a].balance + c[a].interest;
	        printf("\nBalance Updated Successfully. press enter to return to menu\n");
	        getch();
		}
		else if(a==-1){
			printf("\nNo such client found.\n");
			Sleep(1500);
		}
	    rewind(fptr);
	    fseek(fptr, a * sizeof(struct client), SEEK_SET);
        fwrite(&c[a], sizeof(struct client), 1, fptr);
        fclose(fptr);
}

void updateDepo(){
	int cnt=count();
	int a;
	int amnt;
	FILE*fptr;
	fptr = fopen("clients.txt", "rb+");
	a=search();
	if(a!=-1){
		printf("Amount:\t");
	    scanf("%d", &amnt);
		c[a].balance=c[a].balance + amnt;
		printf("\nBalance Updated Successfully. press enter to return to menu\n");
		getch();
	}
	else if(a==-1){
		printf("\nNo such client exist.\n");
		Sleep(1500);
	}
    rewind(fptr);
    fwrite(c, sizeof(struct client), cnt, fptr);
    fclose(fptr);
}
int search(){
	char name[30];
	int cnt=count();
	int i, t, flag=0;
	printf("\nEnter client name: ");
	fflush(stdin);
	gets(name);
	for(i=0; i<cnt; i++)
	{
		if(strcasecmp(name, c[i].name)==0)
		{
			return i;
		}
	}
	return -1;
}
int withdrawAmnt(){
	int with;
	FILE*fptr;
	fptr=fopen("clients.txt", "rb+");
	int a=search();
	if(a!=-1){
		printf("\nEnter the amount withdrawn:\t");
		scanf("%d", &with);
		if(with<=c[a].balance){
		c[a].balance=c[a].balance-with;
		printf("\nBalance Updated Successfully.Press enter to return to menu\n");
		getch();
	    }
	    else{
	    	printf("Insufficient Balance.");
	    	Sleep(1500);
		}
	}
	else if(a==-1){
		printf("\nNo such client exist.\n");
		Sleep(1500);
	}
	rewind(fptr);
    fseek(fptr, a * sizeof(struct client), SEEK_SET);
    fwrite(&c[a], sizeof(struct client), 1, fptr);
    fclose(fptr);
}

void clientFunction(){
	char name[50], phoneNo[15], password[30], rePassword[30];
	float trans;//transfer amount
	system("cls");
	printf("\t\tWelcome to client portal!\n\n ");
	int cnt=count();
 //	int choice = 2;
	int flag=0, t, i, a, flag2=0, flag3=0, attempts, menuOption;
    FILE *fptr;
	fptr = fopen("clients.txt", "rb+");
	fread(c, sizeof(struct client), 3, fptr);
	t=search();
	
	if(t!=-1)
	{
		printf("Welcome %s. \nPlease enter your registered phone number continue. \n", c[t].name);
		attempts=3;
		while(attempts!=0){
		printf("\nPhone number: ");
		fflush(stdin);
		gets(phoneNo);
		if(strcmp(c[t].phoneNumber, phoneNo)==0)
		{
			attempts=0;
			if(c[t].password[0]=='\0'){
				//	flag2 = 1;
				//	printf("\ntrue\n"); error handeling
				attempts = 3;
				
				while(attempts!=0){
				printf("\nCreate your password: ");
				fflush(stdin);
				gets(password);
				printf("\nRe-enter your password to confirm: ");
				fflush(stdin);
				gets(rePassword);
				if(strcmp(password, rePassword)==0){
					printf("\nPassword set successfully. Please re-Run to login.");
					getch();
					strcpy(c[t].password, password);
					fseek(fptr, t * sizeof(struct client), SEEK_SET);
    				fwrite(&c[t], sizeof(struct client), 1, fptr);
    				fflush(fptr);
					//printf("\npassword: %s\n", c[t].password); error handeling
					attempts = 0;
				    }
				else{
					printf("\n\aError! Password doesn't match.");
					attempts--;
						if (attempts !=0){
							printf("\n%d attempt left. ", attempts);
						}
						else{
							break;
				       }
				    }
			      }
				}
			else{
				attempts = 3;
				while(attempts!=0){
					printf("\nPassword: ");
					fflush(stdin);
					gets(password);
					if(strcmp(c[t].password, password)==0){
						printf("\nLogin Successful! Wait few seconds\n\n");
						Sleep(1500);
						while(1){
						system("cls");
						printf("Name: %s\nID: %d\nAccount number: %s\nPhone number: %s\nAccount balance: %f\nCurrent interest rate: %f", c[t].name, c[t].id, c[t].accountNo, c[t].phoneNumber, c[t].balance, c[t].interestRate);
						attempts = 0;
						
						printf("\n\n\n**********1.Transfer Money*********\n");
						printf("**********2.Exit          *********\n");
						scanf("%d", &menuOption);
						fflush(stdin);
						if(menuOption==1){
							a=search();
							char accno[20];
							printf("\nAccoount number:\t");
							fflush(stdin);
							gets(accno);
							for(i = 0; i<cnt; i++){
								if(strcmp(accno, c[i].accountNo)==0){
									flag3 = 1;
									break;
								}
								else{
									flag3=0;
								}
							}
							attempts=3;
							
							if(a!=-1 && flag3==1){
								while(attempts!=0){
								printf("\nAmount:\t");
								scanf("%f", &trans);
								if(trans<=c[t].balance){
									c[t].balance=c[t].balance-trans;
									c[a].balance=c[a].balance+trans;
									attempts=0;
									printf("Balance transfer successful. Press enter to return to menu\n");
									getch();
								}
								else{
									printf("\nInsufficient Balance in account");
									attempts--;
									printf("\n%d attempts left.", attempts);
									if(attempts==0){
										printf("\nTry again or contact your nearest branch\n");
										printf("Press enter to return to transfer menu.");
										getch();
										
									}
								}
							}}
							else if(a==-1 || flag3==0){
								printf("\n Name and Account number didn't match or doesn't exist.'\n");
								Sleep(2000);
								
							}
							
						}
						else if(menuOption==2){
							printf("\n");
							break;
						}}
					}
					else{
						printf("\n\aError! Password doesn't match.");
						attempts--;
						if (attempts !=0){
							printf("\n%d attempt left. ", attempts);
						}
						else{
							printf("\nContact nearest branch!\n");
							Sleep(1500);
							break;
						}
					}
				
				}
			
				}
		
//		printf("Name: %s\nID: %d\nAccount number: %s\nPhone number: %s\nAccount balance: %f\nCurrent interest rate: %f", c[t].name, c[t].id, c[t].accountNo, c[t].phoneNumber, c[t].balance, c[t].interestRate);

		}
		else{
			printf("\aPhone number didn't match!");
			attempts--;
				if (attempts !=0){
					printf("\n%d attempt left. ", attempts);
				}
				else{
					printf("\nContact your nearest branch!\n");
					Sleep(1500);
					break;
				}
			}
		}
		
		
	}
	else if(t==-1){
		printf("Client not found! Contact to your nearest branch.\n");
		printf("\nPress enter to return to main menu");
		getch();
		}
	rewind(fptr);
	fwrite(c, sizeof(struct client), cnt, fptr);
	fclose(fptr);
}



