#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

int validate_name();
int validate_mobile();
int validate_email();
int search_name();

void listContacts(AddressBook *addressBook) 
{
    // Sort contacts based on the chosen criteria
   
   printf("*********************************************************************\n");
   for(int i=0;i<addressBook->contactCount;i++)
   {
	printf("Name : %s\n",addressBook -> contacts[i].name);
	printf("Mobile : %s\n",addressBook -> contacts[i].phone);
	printf("Email : %s\n",addressBook -> contacts[i].email);
	printf("\n");
   }
   printf("*********************************************************************\n");
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}

int f=0,v=0;
void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
	//printf("Enter the name:");
	do
        {
		printf("Enter the name :");
		scanf(" %[^\n]",addressBook -> contacts[addressBook->contactCount].name);
		f = validate_name(addressBook -> contacts[addressBook -> contactCount].name);

		if(f)
			printf("*** Please Enter a valid name - Name should contain only alphabets ***\n");


	}while(f);

	f = 0;
	do

	{
		v=0;
		printf("Enter the mobile number:");
		scanf(" %[^\n]",addressBook -> contacts[addressBook -> contactCount].phone);
		f = validate_mobile(addressBook -> contacts[addressBook -> contactCount].phone);

		if(f==1)
			printf("*** Please enter a valid mobile number - Mobile number should contain 10-digit ***\n");


		if(f==2)
			printf("*** Please enter a valid mobile number - The entered mobile number contains non-numeric values ***\n");
	
		for(int i=0;i<addressBook->contactCount;i++)
		{
			if((strcmp(addressBook->contacts[addressBook -> contactCount].phone,addressBook->contacts[i].phone)) == 0)
			{
				printf("*** The entered mobile number already exists ***\n");
				v=1;
			
			}
		}

	}while(f||v);


	f=0;

	do
	{
		v=0;
		printf("Enter the Email ID:");
		scanf(" %[^\n]",addressBook -> contacts[addressBook -> contactCount].email);
		f = validate_email(addressBook -> contacts[addressBook -> contactCount].email,addressBook);
		
		if(f==1)
			printf("*** Invalid email id - The ID should contain atleast 1 alphabet, 1 number along with @ and .  ***\n");
		
		for(int i=0;i<addressBook->contactCount;i++)
		{
			if((strcmp(addressBook->contacts[addressBook -> contactCount].email,addressBook->contacts[i].email)) == 0)
			{
				printf("*** The entered email Id already exists ***\n");
				v=1;
			}
		}
		


	}while(f||v);


    	
	addressBook -> contactCount++;
	printf("The contact added successfully\n");

	
}

void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
	printf("1) Name\n2) Mobile\n3) Email\n");
	printf("Enter the option:");
	int opt;
	scanf(" %d",&opt);

	char s[30];
	int f=0;

	switch(opt)
	{
		case 1:
			printf("Enter the name to be searched :");
			scanf(" %[^\n]",s);
			
			search_name(s,addressBook);

			break;

		case 2:
			printf("Enter the Mobile number to be searched :");
			scanf(" %[^\n]",s);
			for(int i=0;i<addressBook->contactCount;i++)
			{
				f = strcmp(s,addressBook->contacts[i].phone);

				if(f==0)
				{
					printf("Name : %s\n",addressBook->contacts[i].name);
					printf("Mobile : %s\n",addressBook->contacts[i].phone);
					printf("Email : %s\n",addressBook->contacts[i].email);
					break;
				}

			}

				if(f<0 || f>0)
					printf("*** The entered Mobile number is not found ***\n");

				break;

		case 3:
			printf("Enter the email id to be searched :");
			scanf(" %[^\n]",s);
			for(int i=0;i<addressBook->contactCount;i++)
			{
				f = strcmp(s,addressBook->contacts[i].email);
				
				if(f==0)
				{
					printf("Name : %s\n",addressBook->contacts[i].name);
					printf("Mobile : %s\n",addressBook->contacts[i].phone);
					printf("Email : %s\n", addressBook->contacts[i].email);
					break;
				}

			}
			if(f<0 || f>0)
			printf("*** The entered email id is not found ***\n");

			break;

		default:
			printf("Invalid input\n");
	}

}


void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    	printf("1)Name\n2)Mobile\n3)Email\n");
	int opt;
	printf("Enter the option:");
	scanf(" %d",&opt);
	char s[30],c,m[10];
	int v=0,f=0,vin=0;


	switch(opt)
	{
		case 1:
			printf("Enter the name to be edited:");
			scanf(" %[^\n]",s);			
			v=search_name(s,addressBook);
			
			if(v==100)
			{
				v=0;
				printf("*** There exists multiple names with the entered value ***\n");
				printf("*** To filter out enter the Mobile number ***\n");
				scanf(" %[^\n]",m);
				
				for(int i=0;i<addressBook->contactCount;i++)
				{
					if((strcmp(m,addressBook->contacts[i].phone))==0)
					{
						v=i+1;
						break;
					}

				}

				if(v)
				{
					v--;
				
					do
					{
						printf("Enter the correct name now:");
						scanf( " %[^\n]",s);
						printf("Are you sure to edit the selected contact[Y/y]:");
						scanf(" %c",&c);
						f=validate_name(s);		
						if(f)
			
							printf("*** Please Enter a valid name - Name should contain only alphabets ***\n");
			
					}while(f);

				

					if((c=='Y' || c=='y'))
					{
						strcpy(addressBook->contacts[v].name,s);
						printf("Name changed successfully\n");

					}	
				
		
				}

				else
					printf("*** Could not find the entered mobile number ***\n");
			}
			
			else if(v!=0)
			{
				v--;
				do
				{
					printf("Enter the correct name now:");
					scanf( " %[^\n]",s);
					printf("Are you sure to edit the selected contact[Y/y]:");
					scanf(" %c",&c);
					f=validate_name(s);		
					if(f)
			
						printf("*** Please Enter a valid name - Name should contain only alphabets ***\n");
			
				}while(f);

				

				if((c=='Y' || c=='y'))
				{
					strcpy(addressBook->contacts[v].name,s);
					printf("Name changed successfully\n");

				}

			}	

			else
				printf("Name to be edited could not be found\n");
	

			break;

		case 2:
			printf("Enter the mobile number to be edited:");
			scanf(" %[^\n]",s);
			v=0;

			for(int i=0;i<addressBook->contactCount;i++)
			{
				if((strcmp(s,addressBook->contacts[i].phone))==0)
				{
					v=i;
					break;
				}

			}

			printf("Are you sure to edit the selected contact[Y/y]:");
			scanf(" %c",&c);

			if(v)
			{

				do
				{
					vin = 0;
					printf("Enter the correct mobile number now:");
					scanf(" %[^\n]",s);
					f=validate_mobile(s);	
					if(f==1)
						printf("*** Please enter a valid mobile number - Mobile number should contain 10-digit ***\n");

					else if(f==2)
						printf("*** Please enter a valid mobile number - The entered mobile number contains non-numeric values ***\n");
				
					for(int i=0;i<addressBook->contactCount;i++)
					{
						if((strcmp(s,addressBook->contacts[i].phone)) == 0)
						{
							printf("*** The entered mobile number already exists ***\n");
							vin=1;
						}
					}
			
				}while(f||vin);

				if((c=='Y' || c=='y'))
				{
					strcpy(addressBook->contacts[v].phone,s);
					printf("Mobile number changed successfully\n");

				}

			}

			else
			printf("*** Mobile number not found ***\n");	


			break;

		case 3:	
			printf("Enter the email id to be edited:");
			scanf(" %[^\n]",s);
			v=0;

			for(int i=0;i<addressBook->contactCount;i++)
			{
				if((strcmp(s,addressBook->contacts[i].email))==0)
				{
					v=i;
					break;
				}

			}


			if(v)
			
			{
				
				printf("Are you sure to edit the selected contact[Y/y]:");
				scanf(" %c",&c);
				do
				{
					vin = 0;
					printf("Enter the correct email id now:");
					scanf(" %[^\n]",s);
					f=validate_email(s);

					if(f==1)
						printf("*** Invalid email id - The ID should contain atleast 1 alphabet, 1 number along with @ and .  ***\n");
		
					for(int i=0;i<addressBook->contactCount;i++)
					{
						if((strcmp(s,addressBook->contacts[i].email)) == 0)
						{
							printf("*** The entered email Id already exists ***\n");
							vin=1;
						}
					}
			
				

				}while(f||vin);
				
				if((c=='Y' || c=='y'))
					{
						strcpy(addressBook->contacts[v].email,s);
						printf("Email Id changed successfully\n");

					}

			}

			else
			printf("*** Email id not found ***\n");	


			break;

		default:
			printf("Invalid input\n");
			break;

	}

}

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
	printf("1)Name\n2)Mobile\n3)Email\n");
     	printf("Choose the option from the above list:");
	int opt,v=0;
	char s[30],c,m[10];
	scanf(" %d",&opt);
	
	switch(opt)
	{
		case 1:
			printf("Enter the name:");
			scanf(" %[^\n]",s);
			v=search_name(s,addressBook);

			if(v==100)
			{
				v=0;
				printf("*** There exists multiple names with the entered value ***\n");
				printf("*** To filter out enter the Mobile number ***\n");
				scanf(" %[^\n]",m);
				
				for(int i=0;i<addressBook->contactCount;i++)
				{
					if((strcmp(m,addressBook->contacts[i].phone))==0)
					{
						v=i+1;
						break;
					}

				}

				if(v)
				{
					v--;

					printf("Are you sure to delete the selected contact[Y/y]:");
					scanf(" %c",&c);

					if(c=='Y' || c=='y')
					{
						for(int i=v;i<addressBook->contactCount;i++)
						{
							addressBook->contacts[i] = addressBook->contacts[i+1];
						}

						addressBook->contactCount--;
						printf("Contact deleted successfully\n");

					}
				}

				else
				{
					printf("*** Entered mobile number could not be found ***\n");

				}
				
			}
				
			
			else if(v!=0)
			{
				v--;	
				printf("Are you sure to delete the selected contact[Y/y]:");
				scanf(" %c",&c);

				if(c=='Y' || c=='y')
				{
					for(int i=v;i<addressBook->contactCount;i++)
					{
						addressBook->contacts[i] = addressBook->contacts[i+1];
					}

					addressBook->contactCount--;
					printf("Contact deleted successfully\n");

				}


			}

			else
				printf("*** Contact not found ***\n");
	
			break;

		case 2:
			printf("Enter the Mobile:");
			scanf(" %[^\n]",s);	
			
			for(int i=0;i<addressBook->contactCount;i++)
			{

				f = strcmp(s,addressBook->contacts[i].phone);

				if(f==0)
				{
					printf("Are you sure to delete the selected contact[Y/y]:");
					scanf(" %c",&c);

					if(c=='Y' || c=='y')
					{
						for(int j=i;j<addressBook->contactCount;j++)
						{
							addressBook->contacts[j] = addressBook->contacts[j+1];
						}

						addressBook->contactCount--;
						printf("Contact deleted successfully\n");

					}
				}
			}

			if(f<0 || f<0)
				printf("*** Contact not Found ***\n");
			
			
			break;

		case 3:			
			printf("Enter the Email Id:");
			scanf(" %[^\n]",s);	
			
			for(int i=0;i<addressBook->contactCount;i++)
			{
				f = strcmp(s,addressBook->contacts[i].email);

				if(f==0)
				{
					printf("Are you sure to delete the selected contact[Y/y]:");
					scanf(" %c",&c);

					if(c=='Y' || c=='y')
					{
						for(int j=i;j<addressBook->contactCount;j++)
						{
							addressBook->contacts[j] = addressBook->contacts[j+1];
						}

						addressBook->contactCount--;
						printf("Contact deleted successfully\n");

					}
				}
			}

			if(f<0 || f>0)
				printf("*** Contact not found ***\n");
	

			break;

		default:
			printf("Invalid input\n");

	}	
}

int validate_name(char* s)
{
	int i=0;
	while(s[i] != '\0')
	{
		if(s[i] >= 65 && s[i] <= 91 || s[i] >= 97 && s[i] <= 123)
			i++;

		else
		{
			return 1;
		}


	}
	return 0;
}


int validate_mobile(char* s)
{
	int i=0,c=0,f=0;
	
	while(s[i] !='\0')
	{
		if(s[i] >= '0' && s[i] <= '9')
		{
			i++;
			c++;
		}

		else
		{
			f=1;
			break;
		}

	}
	

	if(f)
		return 2;

	else if(c==10 && s[c] == '\0')
		return 0;

	else 
		return 1;	
}


int validate_email(char* s,AddressBook* addressBook)
{
	int i=0;
	int a=0,n=0,at=0,dt=0,v=0;

	while(s[i]!='\0')
	{

		if(s[i] >= 65 && s[i]<=91 || s[i] >=97 && s[i]<=123)
		{
			i++;
			a=1;
		}

		if(s[i] >='0' && s[i]<='9')
		{
			i++;
			n=1;
			
		}
		if(s[i] =='@')
		{
			for(int j=i;s[j]!='\0';j++)
				{
					if(s[j] >= 65 && s[j]<=91 || s[j] >=97 && s[j]<=123)
					at=1;

					if(s[j] == '.')
					{
						dt=1;
						i=j;
						break;
					}
			
				}
			i++;
			
		}


		else
		i++;	
	}

	if(n&& dt && a && at)
		return 0;

	else 
		return 1;


}

int  search_name(char* s,AddressBook* addressBook)
{
	int c=0,arr[10]={0};
	for(int i=0;i<addressBook->contactCount;i++)
	{
		if((strcmp(s,addressBook->contacts[i].name)==0))
		{

			arr[c]=i;
			c++;
		}

	}
	if(c==0)
		printf("*** The entered name is not found ***\n");
	
	else if(c==1)
	{
		printf("\n%s\n%s\n%s\n",addressBook->contacts[arr[0]].name,addressBook->contacts[arr[0]].phone,addressBook->contacts[arr[0]].email);
		return arr[0]+1;
	}

	else
	{
		printf("\n");
		for(int i=0;i<c;i++)
		{
			printf("%d\n",i+1);
			printf("%s\n%s\n%s\n",addressBook->contacts[arr[i]].name,addressBook->contacts[arr[i]].phone,addressBook->contacts[arr[i]].email);
		}
		return 100;

			
	}
return 0;
	
}

