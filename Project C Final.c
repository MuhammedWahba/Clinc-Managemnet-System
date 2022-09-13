/************************************************************/
/* AUTHOR      : Mina Asser , Mohamed Wahba                 */
/* DESCRIPTION : CLINIC MANAGMENT PROJECT [project.c]       */
/* DATE        : 7 SEP 2022                                 */
/* VERSION     : Final Version                              */
/************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "STD_Types.h"

typedef struct Node_Type Node;

struct Node_Type{
	u8 Name[10];
	u8 Age;
	u8 Gender[10];
	u16 ID;
	u8 res;
	Node *Next;
};

Node* head = NULL;         /*start the head of the linked list*/

#define AdminPass      1234

u8 PasswordFlag = 0,ExitFlag = 0;
u16 ListLength = 0; /* initializing list length */

u8* AvailableSlots[6] = {"2pm to 2:30pm","2:30pm to 3pm","3pm to 3:30pm","4pm to 4:30pm","4:30pm to 5pm","Not Reserved"}; /* defining reservation slots */
u8 ReservedSlots [6] = {0}; /* initializing reserved slots */
/* funtions prototypes */
void  AddPatient  (void);
void  EditPatient (void);
void  ReserveSlot (void);
void  CancelReservation (void);
void  ViewRecord (void);
void  ViewReservation (void);

int main()
{
	u8 mode,counter = 0,adminchoice,userchoice,ans;
	u16 pass;
	
	 printf("\t\t\t###########################################################################");
    printf("\n\t\t\t############                                                   ############");
    printf("\n\t\t\t############             CLINIC MANAGMENT PROJECT              ############");
    printf("\n\t\t\t############                                                   ############");
    printf("\n\t\t\t###########################################################################");
    printf("\n\t\t\t---------------------------------------------------------------------------\n");
    printf("\n\t\t\t----------------------------------------------------------------------------\n");	

	while (ExitFlag == 0)
	{
		printf("For Admin Mode, Please Enter 1\n");
	    printf("For User Mode, Please Enter 2\n");
		printf("To Exit, Please Enter 3\n");
		printf("Your Option: ");
		scanf("%d",&mode);
	
	switch(mode)
	{
		case 1: system("cls");
				printf("Welcome in Admin Mode.\n");
				
				while(PasswordFlag == 0)
				{
					printf("Please, Enter your Password: ");
					scanf("%d",&pass);
					
					if(pass == AdminPass)
					{
						PasswordFlag = 1;
						break;
					}
					
					counter++;
					if(counter == 3)
					{
						break;
					}
					printf("Wrong Password, Try Again.\n");
				}
				
					if(PasswordFlag == 1 )
				{
					
			       PasswordFlag = 0;
				   while(1)
				   {
					   printf("\nTo Add new Patient, Enter 1\n");
				       printf("\nTo Edit Patient's Record, Enter 2\n");
				       printf("\nTo Reserve With Doctor, Enter 3\n");
				       printf("\nTo Cancel Rservation, Enter 4\n");
				       printf("\nYour Option: ");
				       fflush(stdout);
				       scanf("%d",&adminchoice);
				       system("cls");
				       switch(adminchoice)
				       {
				       	case 1: AddPatient();   break;
				       	case 2: EditPatient();         break;
				       	case 3: ReserveSlot();  	   break;
				       	case 4: CancelReservation();   break;
				       	default: printf("Wrong Entry.\n\n"); break;
				       }
					   
					   printf("Do you want to continue in Admin mode?\n1:yes\t2:no\n");
					   printf("Your answer: "); fflush(stdout);
					   scanf("%d",&ans);
					   if(ans == 1)
						   continue;
					   else
						   break;
				   }
					
				}else{
					printf("Acess Denied.\n\n");
				}
		break;
		
		case 2: system("cls");
				printf("Welcome in User Mode.\n\n");
				
				while(1)
				{
					printf("\nTo View Patient's Record, Enter 1\n");
			        printf("\nTo View Patient's Rservation, Enter 2\n");
			        printf("\nYour Option: ");
			        fflush(stdout);
			        scanf("%d",&userchoice);
			        system("cls");
			        switch(userchoice)
			        {
			        	case 1: ViewRecord();              break;
			        	case 2: ViewReservation();         break;
			        	default: printf("Wrong Entry.\n");     break;
			        }
					printf("Do you want to continue in User mode?\n1:yes\t2:no\n");
				    printf("Your answer: ");
				    scanf("%d",&ans);
				    if(ans == 1)
				 	   continue;
				    else
				 	   break;
				}
		break;
		
		case 3: printf("\nOK.\nGood Bye.\n"); 
				ExitFlag = 1;
		break;
		
		default: printf("Wrong Entry.\n\n");   break;
	}
	}
	
	return 0;
}
//1- Add Patient 
//.....................
void AddPatient ()
{
	u8 flag = 0;
	u16 id;
	
	printf("Enter Patient's ID: "); 
	scanf("%d",&id);
	
	if (ListLength == 0)
	{
		/* adding node */
		Node* temp = (Node*) malloc(sizeof(Node));
		printf("Enter Patient's Name: ");
		scanf("%s",temp -> Name);
		printf("Enter Patient's age: ");
		scanf("%d",&temp -> Age);
		printf("Enter Patient's Gender: ");
		scanf("%s",temp -> Gender);
		temp -> ID = id;
		temp -> res = 5;
		temp -> Next = head;
		head = temp;
		
		printf("New patient added successfully.\n\n");
	}
	else{
		Node* temp = (Node*) malloc(sizeof(Node));
		Node* Last = head;
		while( Last != NULL)
		{
			if(Last -> ID == id)
			{
				flag = 1;
				break;
			}
			Last = Last -> Next;
		}
		
		if(flag == 1)
		{
			printf("ID already exists.\n\n");
		}
		else{
		    printf("Enter Patient's Name: "); 
		    scanf("%s",temp -> Name);
		    printf("Enter Patient's age: "); 
		    scanf("%d",&temp -> Age);
		    printf("Enter Patient's Gender: "); 
		    scanf("%s",temp -> Gender);
			temp -> ID = id;
			temp -> res = 5;
			temp -> Next = NULL;
			Last = head;
			while((Last->Next) != NULL)
			{
				Last = Last->Next;
			}
			Last->Next = temp;
			printf("New patient added successfully.\n\n");
		}
	}
	ListLength++;
}
//2- Edit Patient
//.....................
void  EditPatient ()
{
	u8 flag = 0;
	u16 id;
	printf("Enter Patient's ID to Edit: "); 
	scanf("%d",&id); 
	if (ListLength == 0)
	{
		printf("No information avaialble.\n\n");
	}else{
		Node* Last = head;
		while(Last != NULL)
		{
			if(Last -> ID == id)
			{
				flag = 1;
				break;
			}
			Last = Last -> Next;
		}
		if(flag == 1)
		{
			printf("Enter new information.\n");
		    printf("Enter Patient's Name: ");
		    scanf("%s",Last -> Name);
		    printf("Enter Patient's age: "); 
		    scanf("%d",&Last -> Age);
		    printf("Enter Patient's Gender: "); 
		    scanf("%s",Last -> Gender);
			printf("Edit patient successfully.\n\n");
		}else{
			printf("Wrong ID.\n\n");
		}
	}
}
//3- Reserve Slot
//.....................
void  ReserveSlot ()
{
	u16 id;
	Node * ptr = head;
	u16 pos=0; // position of id 
	u8 check=0; // check if user can reserver or not 
	u8 resv=0;
	printf("\n\nEnter The Id To Reserve : ");
	scanf("%d",&id); // Taking id from user
	while ( ptr != NULL)
	{
		
		if ( ptr->ID == id )
		{
			pos++;
			break;
		}
		
		ptr=ptr->Next;
	}// end of while loop
	
	if( pos > 0)
	{
		for (u8 i=0 ; i < 5 ; i++ )
	{
		if(ReservedSlots[i]==0)
			printf("%d- %s\n",i+1,AvailableSlots[i]);
		else
		{
			check++;
		}
	}
		if(check>=5)
		{
			printf("\n Sorry No Availble Reservetions !");
			return;
		}
		else
		{
			printf("\nYou Choice = ");
			scanf("%d",&resv);
		}
		if( resv > 0 && resv <= 5)
		{
		ptr->res = resv-1;
		ReservedSlots[resv-1]=1;
		}
		else
			printf("Wrong Choice !");
	}// end of if condition
	else
		printf("incorrect ID !");
	
}
//3-  Cancel Reservation 
//.....................
void  CancelReservation ()
{
    u16 id;
	Node * ptr = head;
	u16 pos=0; // position of id 


	printf("\n\nEnter The Id To Cancel Reserve : ");
	scanf("%d",&id); // Taking id from user
	while ( ptr != NULL)
	{
		
		if ( ptr->ID == id )
		{
			pos++;
			break;
		}
		
		ptr=ptr->Next;
	}// end of while loop
	
	if( pos > 0)
	{
	
		if(ReservedSlots[ptr->res]==1)
		{
			printf("Your Reservetion: ( %s ) is cancelled \n",AvailableSlots[ptr->res]);
			ReservedSlots[ptr->res]=0;
			ptr->res = 5;
			
		}
		
		else
		{
			printf("This ID didn't reseverd !");
		}
		
	}// end of if condition
	else
		printf("incorrect ID !");
	
}
//4-  View Record
//.....................
void  ViewRecord ()
{
	u8 flag = 0;
	u16 id;
	
	printf("Enter Patient's ID to View Record: ");
	scanf("%d",&id); 
	if (ListLength == 0)
	{
		printf("No information avaialble.\n\n");
	}else{
		Node* Last = head;
		while(Last != NULL)
		{
			if(Last -> ID == id)
			{
				flag = 1;
				break;
			}
			Last = Last -> Next;
		}
		if(flag == 1)
		{
		    printf("Patient's Name: %s \n",Last->Name); 
		    printf("Patient's age: %d \n",Last -> Age); 
		    printf("Patient's Gender: %s \n\n",Last -> Gender); 
		}else{
			printf("Wrong ID.\n\n");
		}
	}
}
//5-  View Reservation
//.....................
void  ViewReservation ()
{
	Node* Last = head;

	printf("All reservations: \n\n");
	
	if(ListLength == 0)
	{
		printf("No information avaialble.\n\n");
	}else{
		while(Last != NULL)
		{
			if(Last->res == 5)
			{
				printf("Patient: (%s) with ID: (%d) has not reserved yet. \n\n",Last->Name,Last->ID);
			}
			else
			{
				printf("Patient: (%s) with ID: (%d) has reservation at (%s) \n\n",Last->Name,Last->ID,AvailableSlots[Last->res]);
			}		
			Last = Last->Next;
		}
	}	
}