#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "list.h"

int main(int argc,char **argv)
{
    CUSTOMER *queue = NULL;
    char choice;
    char name[30];
    char amt[15];
    int amtfinal,thresh;
    do
    {
        printf("*******************************************************************");
        printf("\n\tENTER YOUR CHOICE:-\n\t1)ENTER A NEW/EXISTING CUSTOMER\n\t2)DEQUEUE\n\t3)PRINT QUEUE\n\t4)PRINT THE EXISTING CUSTOMER DETAILS\n\t5)CHANGE THE PRIORITY OF AN EXISTING CUSTOMER\n\t6)RESET\n\tANY OTHER NUMBER TO EXIT: ");
        scanf("%c",&choice);
        printf("*******************************************************************\n");
        switch(choice)
        {
            case '1':printf("Enter the name of the customer: ");
                   scanf("%s",name);
                   while (1)
                   {
                     printf("\nEnter the amount paid by the customer: ");
                     scanf("%s",amt);
                     if (atoi(amt))
                     {
                            amtfinal = atoi(amt);
                            break;
                     }
                     else
                     {
                            printf("**********Invalid Input**********\n");
                     }
                      
                   }
                   insert(&queue,amtfinal,name);
                   printf("Customer entered into the queue");
                   break;
            case '2':pop(&queue);
                   break;
            case '3':printQueue(&queue);
                   break;
            case '4':printcsv();
                   break;
            case '5':while (1)
                   {
                     printf("Enter the new threshold value: ");
                     scanf("%s",amt);
                     if (atoi(amt))
                     {
                            thresh = atoi(amt);
                            break;
                     }
                     else
                     {
                            printf("**********Invalid Input**********\n");
                     }
                      
                   }
                   changeThreshold(thresh);
                   break;
            case '6':reset();
                   break;
            default:printf("Thank you for using our application\n");
                     return 0;
                    break;
        }
        printf("\n*******************************************************************\n");
    }while(choice >= '1' && choice <= '6');
    return 0;
}