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
	char phoneNumber[10];
	float balance;
	float interestRate;
	float interest;
}c[100];
int globalCount;
char globalAccountNo[15];
int main()
{
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
				printf("\tClient part!\n");
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
	printf("*************1.Register client**********\n");
	printf("*************2.Search Client************\n");
	printf("*************3.Update Balance**********\n");
	scanf("%d", &adch);
	if (adch==2){
	printf("\nEnter client name: ");
	fflush(stdin);
	gets(name);
	for(i=0; i<cnt; i++)
	{
		if(strcasecmp(name, c[i].name)==0)
		{
			flag = 1;
			t = i;
		}
	}
	if(flag == 1)
	{
		printf("Client found! \n");
		printf("Name: %s\nID: %d\nAccount number: %s\nPhone number: %s\nAccount balance: %f\nCurrent interest rate: %f\n", c[t].name, c[t].id, c[t].accountNo, c[t].phoneNumber, c[t].balance, c[t].interestRate);
	
	}
	else{
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
		else if(subch==2){
			
		}
	}
	fclose(fptr);
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
		printf("\nClients data stored successfully!\n");
	
	fclose(fptr);
	
}
