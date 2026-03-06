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
	printf("\t1.Admin\n\t2.Client\n");
	while(1)
	{
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
					break;
				}
				else{
					break;
				}
				
			}
		else if(strcmp(choice_1, "2") == 0 || strcasecmp(choice_1, "client")==0)
			{
				clientFunction();
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
	}}

	
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
			printf("\n------------Login successful!------------ ");
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
	int cnt=count();int adch, subch;
	char name[30];
	int flag=0, t, i;
    FILE *fptr;
	fptr = fopen("clients.txt", "rb");
	fread(c, sizeof(struct client), cnt, fptr);
	while(1){
	printf("*************1.Register client **********\n");
	printf("*************2.Search Client   **********\n");
	printf("*************3.Update Balance  **********\n");
	printf("*************4.Withdraw Balance**********\n");
	printf("*************5.Exit            **********\n");
	scanf("%d", &adch);
	fflush(stdin);
	if (adch==2){
	t=search();
	if(t!=-1)
	{
		printf("Client found! \n");
		printf("Name: %s\nID: %d\nAccount number: %s\nPhone number: %s\nAccount balance: %f\nInterest amount: %f\nCurrent interest rate: %f\n", c[t].name, c[t].id, c[t].accountNo, c[t].phoneNumber, c[t].balance, c[t].interest, c[t].interestRate);
	
	}
	else if(t==-1){
		char ch;
		printf("Client not found! Press 1 for new registration.\n");
		if((ch=getch())==49)
		{
			newRegistration();
			//printf("new registration function currently under construction. Please come back later!");
		}
		else
		{
			printf("Program terminated");
			getch();
			return 1;
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
		printf("\nClients data stored successfully!. Relogin to view updated info\n");
	
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
	        printf("\nBalance Updated Successfully. Relogin to view updated info\n");
		}
		else if(a==-1){
			printf("\nNo such client found.\n");
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
		printf("\nBalance Updated Successfully. Relogin to view updated info\n");
	}
	else if(a==-1){
		printf("\nNo such client exist.\n");
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
		c[a].balance=c[a].balance-with;
		printf("\nBalance Updated Successfully.\n");
	}
	else if(a==-1){
		printf("\nNo such client exist.\n");
	}
	rewind(fptr);
    fseek(fptr, a * sizeof(struct client), SEEK_SET);
    fwrite(&c[a], sizeof(struct client), 1, fptr);
    fclose(fptr);
}

void clientFunction(){
	char name[50], phoneNo[15], password[30], rePassword[30];
	printf("\t\tWelcome to client portal!\n\n ");
	int cnt=count();
 //	int choice = 2;
	int flag=0, t, i, flag2=0, attempts, menuOption;
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
						printf("\nLogin Successful!\n\n");
						printf("Name: %s\nID: %d\nAccount number: %s\nPhone number: %s\nAccount balance: %f\nCurrent interest rate: %f", c[t].name, c[t].id, c[t].accountNo, c[t].phoneNumber, c[t].balance, c[t].interestRate);
						attempts = 0;
						printf("\n\n\n**********1.Transfer Money*********\n");
						printf("**********2Exit           *********\n");
						scanf("%d", &menuOption);
						fflush(stdin);
						if(menuOption==1){
							printf("Money transfer process under construction. \nThis process should ask user to type phone number or account number. \ncheck if it matches anyone in database. \nif yes, continue money transfer. \nif no destination account doesnot exist. Contact your nearest branch. ");
							
						}
						else if(menuOption==2){
							printf("\n");
							break;
						}
					}
					else{
						printf("\n\aError! Password doesn't match.");
						attempts--;
						if (attempts !=0){
							printf("\n%d attempt left. ", attempts);
						}
						else{
							printf("\nContact nearest branch!\n");
							getch();
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
	
	fclose(fptr);
}



