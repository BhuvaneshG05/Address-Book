#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) 
{
	FILE* fptr = fopen("contact.txt","w");
      	
	fprintf(fptr,"#%d#\n",addressBook->contactCount);

	for(int i=0;i<addressBook->contactCount;i++)
	{
		fprintf(fptr,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);

	}
	fclose(fptr);	
}

void loadContactsFromFile(AddressBook *addressBook) 
{ 
	FILE* fptr = fopen("contact.txt","r");
    	if(fptr == NULL)
		printf("File does not exist\n");

	else
	{
		fscanf(fptr,"#%d#\n",&addressBook->contactCount);

		for(int i=0;i<addressBook->contactCount;i++)
		{
			fscanf(fptr," %[^,]%*c%[^,]%*c%[^\n]\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
		}
		fclose(fptr);
	}	
}
