#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct account
{
	int account_number;
	char name[30];
	char surname[30];
	char adress[30];
	int ID;
	double balance;
};
int check_input_int();
double check_input_double();
int check_input_strings(char inputdata[30]);

void display(int account_number);

int number_of_accounts();

void add_account();
void dissplay_all();
void search();
void transfer();
void withdraw();
void deposit();

void search_for_account_number();
void search_for_name();
void search_for_surname();
void search_for_adress();
void search_for_ID();

int confirmation();

char fname[]={"accounts.dat"};

int main()
{
	int choice;
	while(1)
	{
		system("clear");
		printf("*****************Grebach Central Bank*****************\n\n");
		printf("1. Create new account\n\n");
		printf("2. Display all\n\n");
		printf("3. Search\n\n");
		printf("4. Transfer money\n\n");
		printf("5. Withdraw\n\n");
		printf("6. Deposit\n\n");
		printf("0. Exit\n\n");
		printf("******************************************************\n\n");
		
	printf("Please enter your choice:");
	choice = check_input_int();
	
		switch(choice)
		{
			case 1: add_account();
				break;
	
			case 2: dissplay_all();
				break;
				
			case 3: search();
				break;
	
			case 4: transfer();
				break;
	
			case 5: withdraw();
				break;
			
			case 6: deposit();
				break;
	
			case 0: system("clear");
				exit(0);
	
			default: printf("\nWrong key\n");
				 getchar();
				 break;
		}//end of switch
	
	}//end of while loop
	return 0;
}//end of main
int check_input_int()
{
	char c;
	int check;
	int input_number;
	do
	{
		if(scanf("%d", &input_number) !=1 ) 
		{
			printf("Please enter value in correct format:");
			check=0;
		}
		else
			check=1;
		do
		{
			c=getchar();
		}while(c != '\n' && c != ' ');
			
	}while(check == 0);
	
	return input_number;
}

double check_input_double()
{
	char c;
	int check;
	double input_number;
	do
	{
		if(scanf("%lf", &input_number) !=1 ) 
		{
			printf("Please enter value in correct format:");
			check=0;
		}
		else
			check=1;
		do
		{
			c=getchar();
		}while(c != '\n' && c != ' ');
			
	}while(check == 0);
	
	return input_number;
}

int check_input_strings(char inputdata[30])
{
	int i;
	int c;
	int check;
	c=strlen(inputdata);   
	for(i=0;i<c;i++)
	{
		if(isalpha(inputdata[i]) == 0)
		{
			check = 1;
			break;
		}
	check = 0;
	}
	return check;
}

void display(int account_number)
{
	FILE *fp;
	struct account tmp;
	int found=0;
	
	fp=fopen(fname,"rb");
	if(fp==NULL)
	{
		perror("Error opening file");
		exit(3);
	}
	
	
	while(1)
	{
		fread(&tmp,sizeof(tmp),1,fp);
		
		if(feof(fp))
		{
			break;
		}
		if(tmp.account_number==account_number)
		{
			found=1;
			
			printf("\n\t\t Account Details \n\n");
			
			printf("Account number: %d \n",tmp.account_number);
			printf("Name: %s\n",tmp.name);
			printf("Surname: %s\n",tmp.surname);
			printf("Adress: %s\n",tmp.adress);
			printf("ID: %d\n",tmp.ID);
			printf("Balance: %.2lf\n\n",tmp.balance);
		
		}
	}
	if(found==0)
	{
		printf("\nNot Found");
	}
	fclose(fp);
	getchar();
}

void add_account()
{
	int check;
	FILE *fp;
	struct account tmp;
	
	fp=fopen(fname,"ab");
	if(fp==NULL)
	{
		perror("Error opening file");
		exit(3);
	}
	
	do
	{
		printf("\nEnter name:");
		scanf("%s",tmp.name);
			do
			{ 
				check = check_input_strings(tmp.name);
				if(check == 1)
				{
					printf("Type value in proper format:");
					scanf("%s",tmp.name);
				}
			}while(check != 0);
	
		printf("\nEnter surname:");
		scanf("%s",tmp.surname);
			do
			{ 
				check = check_input_strings(tmp.surname);
				if(check == 1)
				{
					printf("Type value in proper format:");
					scanf("%s",tmp.surname);
				}
			}while(check != 0);
	
		printf("\nEnter adress:");
		scanf("%s",tmp.adress);
			do
			{ 
				check = check_input_strings(tmp.adress);
				if(check == 1)
				{
					printf("Type value in proper format:");
					scanf("%s",tmp.adress);
				}
			}while(check != 0);
	
		printf("\nEnter ID:");
		tmp.ID = check_input_int();
		tmp.account_number = number_of_accounts() + 1;
		tmp.balance=0;
	
	}while(confirmation() == 0);
	
	fwrite(&tmp,sizeof(tmp),1,fp);
	
	fclose(fp);
}

void dissplay_all()
{
	FILE *fp;
	struct account tmp;
	int found=0;
	
	fp=fopen(fname,"rb");
	if(fp==NULL)
	{
		perror("Error opening file");
		exit(3);
	}
	
	while(1)
	{
		fread(&tmp,sizeof(tmp),1,fp);
	
		if(feof(fp))
		{
			break;
		}
	
		display(tmp.account_number);
		found = 1;
	}
	
	if(found==0)
	{
		printf("\nNot Found");
		getchar();
	}
	fclose(fp);
}

void search()
{
	int choice;
	system("clear");

	printf("*****************Searching*****************\n\n");

	printf("From which data do u wanna search: \n\n");
	printf("1. Number of Account \n\n");
	printf("2. Name \n\n");
	printf("3. Surnname \n\n");
	printf("4. Adress\n\n");
	printf("5. ID \n\n");
	printf("0. Return\n\n");

	printf("*******************************************\n\n");

	printf("Please enter your choice:");
	choice = check_input_int();

	switch(choice)
	{
		case 1: search_for_account_number();
			break;

		case 2: search_for_name();
			break;
			
		case 3: search_for_surname();
			break;

		case 4: search_for_adress();
			break;

		case 5: search_for_ID();
			break;
		
		case 0: break;

		default: printf("\nWrong key\n");
			 getchar();
			 break;
	}//end of switch
}

void transfer()
{
	FILE *fp;
	struct account tmp;
	int found=0;
	double money;
	int enough_money = 0;
	int account_number_from, account_number_to;
	int current_account;
	
	fp=fopen(fname,"r+b");
	if(fp==NULL)
	{
		perror("Error opening file");
		exit(3);
	}
	
	do
	{
		printf("\nEnter the client Account Number from which you want to transfer money:");
		account_number_from = check_input_int();
	
		printf("\nEnter the amount of money you want to transfer:");
		money = check_input_double();
	}while(confirmation() == 0);
	
	for(current_account=0;;current_account++)
	{
		fread(&tmp,sizeof(tmp),1,fp);
	
		if(feof(fp))
		{
			break;
		}
	
		if(tmp.account_number==account_number_from)
		{
			found = 1;
		
			if(tmp.balance-money>=0)
			{
				enough_money = 1;
				tmp.balance-=money;	
	
				if (fseek (fp, (current_account) * sizeof (tmp),SEEK_SET))
				    {
					    perror ("Error seeking in file");
					    exit (3);
				    }
	
				  if (fwrite (&tmp, sizeof (tmp), 1, fp) != 1)
				    {
					    perror ("Error reading from file");
					    exit (3);
				    }
			}
			else
			{
				printf("\nYou dont have enough money");
				enough_money = 0;
				getchar();		
			}	
		}
	}
	
	if(found==0)
	{
		printf("\nNot Found");
		getchar();
	}
	fclose(fp);
	//......................................................
	if(found == 1 && enough_money == 1)
	{
		found = 0;
	
		fp=fopen(fname,"r+b");
		if(fp==NULL)
		{
			perror("Error opening file");
			exit(3);
		}
	do
	{
		printf("\nEnter the client Account Number in which you want to deposit money:");
		account_number_to = check_input_int();
	}while(confirmation() == 0);
	
		for(current_account=0;;current_account++)
		{
			fread(&tmp,sizeof(tmp),1,fp);
	
			if(feof(fp))
			{
				break;
			}
	
			if(tmp.account_number==account_number_to)
			{
				found = 1;
			
				tmp.balance+=money;
		
				if (fseek (fp, (current_account) * sizeof (tmp),SEEK_SET))
				    {
					    perror ("Error seeking in file");
					    exit (3);
				    }
		
				  if (fwrite (&tmp, sizeof (tmp), 1, fp) != 1)
				    {
					    perror ("Error reading from file");
					    exit (3);
				    }
			}
		}
		fclose(fp);
	
		if(found==0)
		{
			printf("\nNot Found");
			getchar();
			fp=fopen(fname,"r+b");
			if(fp==NULL)
			{
				perror("Error opening file");
				exit(3);
			}
			for(current_account=0;;current_account++)
			{
				fread(&tmp,sizeof(tmp),1,fp);
	
				if(feof(fp))
				{
					break;
				}
	
				if(tmp.account_number==account_number_from)
				{
					found = 1;
			
					tmp.balance+=money;
		
					if (fseek (fp, (current_account) * sizeof (tmp),SEEK_SET))
					    {
						    perror ("Error seeking in file");
						    exit (3);
					    }
		
					  if (fwrite (&tmp, sizeof (tmp), 1, fp) != 1)
					    {
						    perror ("Error reading from file");
						    exit (3);
					    }
				}
			}
		
			fclose(fp);
		}
	
	}

}

void withdraw()
{
	FILE *fp;
	struct account tmp;
	int found=0;
	double money;
	int account_number;
	int current_account;
	
	fp=fopen(fname,"r+b");
	if(fp==NULL)
	{
		perror("Error opening file");
		exit(3);
	}
	
	do
	{
		printf("\nEnter the client Account Number from which you want to withdraw money:");
		account_number = check_input_int();
		
		
		printf("\nEnter the amount of money you want to withdraw:");
		money = check_input_double();
	}while(confirmation() == 0);
	
	for(current_account=0;;current_account++)
	{
		fread(&tmp,sizeof(tmp),1,fp);
	
		if(feof(fp))
		{
			break;
		}
	
		if(tmp.account_number==account_number)
		{
			found = 1;
		
			if(tmp.balance-money>=0)
			{
				tmp.balance-=money;	
				
				if (fseek (fp, (current_account) * sizeof (tmp),SEEK_SET))
				    {
				    	perror ("Error seeking in file");
				    	exit (3);
				    }
	
				  if (fwrite (&tmp, sizeof (tmp), 1, fp) != 1)
				    {
				    	perror ("Error reading from file");
				    	exit (3);
				    }
			}
			else
			{
				printf("\nYou dont have enough money");
				getchar();		
			}	
		}
	}
	
	if(found==0)
	{
		printf("\nNot Found");
		getchar();
	}
	fclose(fp);
}

void deposit()
{
	FILE *fp;
	struct account tmp;
	int found=0;
	double money;
	int account_number;
	int current_account;
	
	fp=fopen(fname,"r+b");
	if(fp==NULL)
	{
		perror("Error opening file");
		exit(3);
	}
	
	do
	{
		printf("\nEnter the client Account Number in which you want to deposit money:");
		account_number = check_input_int();
		
		printf("\nEnter the amount of money you want to deposit:");
		money = check_input_double();
	}while(confirmation()==0);
	
	for(current_account=0;;current_account++)
	{
		fread(&tmp,sizeof(tmp),1,fp);
	
		if(feof(fp))
		{
			break;
		}
	
		if(tmp.account_number==account_number)
		{
			found = 1;
			tmp.balance+=money;
		
			if (fseek (fp, (current_account) * sizeof (tmp),SEEK_SET))
			    {
			    	perror ("Error seeking in file");
			    	exit (3);
			    }
		
			  if (fwrite (&tmp, sizeof (tmp), 1, fp) != 1)
			    {
			    	perror ("Error reading from file");
			    	exit (3);
			    }
		}
	}
	
	if(found==0)
	{
		printf("\nNot Found");
		getchar();
	}
	fclose(fp);
}

//--------------------------SEARCHING FUNCTIONS-------------------------
void search_for_account_number()
{
	FILE *fp;
	struct account tmp;
	int found=0;
	int account_number;
	
	fp=fopen(fname,"rb");
	if(fp==NULL)
	{
		perror("Error opening file");
		exit(3);
	}
	
	printf("\nEnter the client Account Number:");
	account_number = check_input_int();
	
	while(1)
	{
		fread(&tmp,sizeof(tmp),1,fp);
	
		if(feof(fp))
		{
			break;
		}
	
		if(tmp.account_number==account_number)
		{
			found = 1;
			display(tmp.account_number);
		}
	}
	
	if(found==0)
	{
		printf("\nNot Found");
		getchar();
	}
	fclose(fp);
}

void search_for_name()
{
	FILE *fp;
	struct account tmp;
	int found=0;
	char name[30];
	
	fp=fopen(fname,"rb");
	if(fp==NULL)
	{
		perror("Error opening file");
		exit(3);
	}
	
	printf("\nEnter the client Name:");
	scanf("%s",name);
	int check;
		do
		{ 
			check = check_input_strings(name);
			if(check == 1)
			{
				printf("Type value in proper format:");
				scanf("%s",name);
			}
		}while(check != 0);
	getchar();
	
	while(1)
	{
		fread(&tmp,sizeof(tmp),1,fp);
	
		if(feof(fp))
		{
			break;
		}
		if(strcmp(name,tmp.name)==0)
		{
			found = 1;
			display(tmp.account_number);
		}
	}
	if(found==0)
	{
		printf("\nNot Found");
		getchar();
	}
	fclose(fp);
}

void search_for_surname()
{
	FILE *fp;
	struct account tmp;
	int found=0;
	char surname[30];
	
	fp=fopen(fname,"rb");
	if(fp==NULL)
	{
		perror("Error opening file");
		exit(3);
	}
	
	printf("\nEnter the client Surname:");
	scanf("%s",surname);
	int check;
		do
		{ 
			check = check_input_strings(surname);
			if(check == 1)
			{
				printf("Type value in proper format:");
				scanf("%s",surname);
			}
		}while(check != 0);
	getchar();
	
	while(1)
	{
		fread(&tmp,sizeof(tmp),1,fp);
	
		if(feof(fp))
		{
			break;
		}
	
		if(strcmp(surname,tmp.surname)==0)
		{
			found = 1;
			display(tmp.account_number);
		}
	}
	
	if(found==0)
	{
		printf("\nNot Found");
		getchar();
	}
	fclose(fp);
}

void search_for_adress()
{
	FILE *fp;
	struct account tmp;
	int found=0;
	char adress[30];
	
	fp=fopen(fname,"rb");
	if(fp==NULL)
	{
		perror("Error opening file");
		exit(3);
	}
	
	printf("\nEnter the client Adress:");
	scanf("%s",adress);
	int check;
		do
		{ 
			check = check_input_strings(adress);
			if(check == 1)
			{
				printf("Type value in proper format:");
				scanf("%s",adress);
			}
		}while(check != 0);
	getchar();
	
	while(1)
	{
		fread(&tmp,sizeof(tmp),1,fp);
	
		if(feof(fp))
		{
			break;
		}
		if(strcmp(adress,tmp.adress)==0)
		{
			found = 1;
			display(tmp.account_number);
		}
	}
	if(found==0)
	{
		printf("\nNot Found");
		getchar();
	}
	fclose(fp);
}

void search_for_ID()
{
	FILE *fp;
	struct account tmp;
	int found=0;
	int ID;
	
	fp=fopen(fname,"rb");
	if(fp==NULL)
	{
		perror("Error opening file");
		exit(3);
	}
	
	printf("\nEnter the client ID:");
	ID = check_input_int();
	
	while(1)
	{
		fread(&tmp,sizeof(tmp),1,fp);
	
		if(feof(fp))
		{
			break;
		}
	
		if(tmp.ID==ID)
		{
			found = 1;
			display(tmp.account_number);
		}
	}
	
	if(found==0)
	{
		printf("\nNot Found");
		getchar();
	}
	fclose(fp);
}

//----------------------END OF SEARCHING FUNCTIONS----------------------

int number_of_accounts()
{
	struct account tmp;
	int account_number;
	FILE *fp;
	fp=fopen(fname,"ab");
	
	if(fp==NULL)
	{
		perror("Error opening file");
		exit(3);
	}
	account_number=ftell(fp)/sizeof(tmp);
	return account_number;
}

int confirmation()
{
	char c;
	printf("\nAre you sure that you want do that?\n");
	printf("Press \'y\' to continue\n");
	c = getchar();
	if(c != 'y' && c != 'Y') 
		return 0;
	return 1;
}
