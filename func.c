#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "list.h"
//function to create a new node.
CUSTOMER* newNode(int a,char *s,int p)
{
    CUSTOMER* temp=(CUSTOMER*)malloc(sizeof(CUSTOMER));
    temp->amt = a; 
    temp->priority = p;
    strcpy(temp->name,s); 
    temp->next = NULL; 
    return temp;
}
//To insert an element in the queue
void insert(CUSTOMER** node,int a,char *s)
{
    CUSTOMER* start = (*node); 
    int p = priority(s,a);
    CUSTOMER* temp = newNode(a,s,p);
    //Checking if the node is empty 
    if(*node == NULL) 
    {
        *node = temp;
        return;
    }
    //if the priority is greater than the value assigned by priority function
    if ((*node)->priority>p) 
    { 
        temp->next = *node; 
        *node = temp; 
    } 
    //if the priority is greater than the value assigned by priority function
    else
    {
        while (start->next!=NULL&&start->next->priority<p) 
        { 
            start = start->next; 
        }  
        temp->next = start->next; 
        start->next = temp; 
    } 
}
//To return the head
CUSTOMER* peek(CUSTOMER** node) 
{ 
    return *node; 
}   
//To delete a node.
void pop(CUSTOMER** node) 
{ 
    //Checking if the node is empty
    if (*node==NULL)
    {
        printf("Queue is Empty\n");
        return;
    } 
    CUSTOMER *temp = (*node); 
    (*node) = (*node)->next; 
    free(temp);
    printf("Succesfully popped\n"); 
} 
//To check if a node is empty or not.
int isEmpty(CUSTOMER** node) 
{ 
    if (*node == NULL)
        return 1;
    return 0; 
} 
//To find the number of lines in a file and it is used in the priority function and print function
int noOfLines(FILE *ptr)
{
    int lines = 0;
    char chr;
    chr=getc(ptr);
    while (chr != EOF)
    {
        //Count whenever new line is encountered
        if (chr == '\n')
        {
            lines = lines + 1;
        }
        //take next character from file.
        chr = getc(ptr);
    }
    return lines;
}
//To assign the priority to a given customer
int priority(char * pname,int pamt)
{
    FILE *fp,*fpriority;//fp is for CSV,fpriority is for the priority file
    int i = 0;
    //Checking if the file can be opened.
    if((fp = fopen("customer.csv","r+"))==NULL)
    {
        printf("Can't open file.\n");
        exit(1);
    }
    rewind(fp);//brings the pointer to the beginning of the file
    char line[1024]; 
    int lines = noOfLines(fp);//finding the no of lines for traversing through the CSV file.
    int amt[lines];
    int times[lines];
    char * field;
    char name[lines][20];
    rewind(fp);
    //Extracting the file details and putting it in 3 arrays namely name,amount and number of times visited
    for(int i = 0;i<lines;i++)
    {
        
        fgets(line,1024,fp);
        field = strtok(line,",");
        strcpy(name[i],field);
        field=strtok(NULL,",");
        amt[i] = atoi(field);
        field = strtok(NULL,",");
        times[i] = atoi(field);
    }
    //to check whether the customer name is present in the file
    int flag = -1;
    for (i = 0;i<lines;i++)
    {
        if (!strcmp(pname,name[i]))
        {
          flag = i;
          break;
        }
    }
    //To give a higher priority if it's greater than the threshold value
    int threshold;//variable to assign the threshold value
    if((fpriority = fopen("priority.txt","r")) == NULL)
    {
        printf("Can't access user set priority using default threshold values.\n");
        threshold = 10000;//default threshold
    }
    else
    {
        fscanf(fpriority,"%d",&threshold);
    }
    //if it is a first time customer a higher priority is given
    if (flag == -1)
    {
        rewind(fp);
        for (i = 0; i<lines; i++)
        {
            fprintf(fp,"%s,%d,%d\n",name[i],amt[i],times[i]);
        }
        fprintf(fp,"%s,%d,1\n",pname,pamt);
        fclose(fp);
	if (fpriority)
		fclose(fpriority);//closing the priority file after priority is assigned.
	if (pamt>threshold)
		return 1;
    return 3;
    }
    else
    {        
        //highest priority is given to the customer who is willing to spend more
        //updating the csv file
        times[flag]++;
        amt[flag] = amt[flag]+pamt;
        rewind(fp);//to bring the pointer to the beginning of the file.
        for (i = 0; i<lines; i++)
        {
            fprintf(fp,"%s,%d,%d\n",name[i],amt[i],times[i]);//
        }
        if (fp)
            fclose(fp);//closing the CSV file pointer
        if (fpriority)
            fclose(fpriority);//closing the priority file pointer
        if (pamt > threshold)
        {   
            return 1;
        }
        else
        {   
            if ((amt[i]/times[i]) > threshold)
                return 2;
            return 4;    
        }
    }
}
//To print the contents of the CSV file
void printcsv()
{
    FILE *fp;
    int i = 0;
    //checking if the file can be opened.
    if((fp=fopen("customer.csv","r+"))==NULL)
    {
        printf("Can't open file.\n");
        exit(1);
    }
    rewind(fp);
    int lines = noOfLines(fp);
    char* field;
    char line[1024];
    int number;
    rewind(fp);
    //printing the contents of the CSV file
    printf("Customer_Name\t\tAmount_Spent\t\tNo_of_times_visited\n");
    for(int i = 0;i<lines;i++)
    {
        
        fgets(line,1024,fp);
        field = strtok(line,",");
        printf("%s\t\t\t",field);
        field=strtok(NULL,",");
        number = atoi(field);
        printf("%d \t\t\t",number);
        field = strtok(NULL,",");
        number = atoi(field);
        printf("%d\n",number);
        
    }
}
//To change the threshold value
void changeThreshold(int t)
{
    FILE * fp;
    fp=fopen("priority.txt","w");
    fprintf(fp,"%d",t);
    fclose(fp);
}
//Delete the content of the files
void reset()
{
    FILE *fp;
    fp=fopen("customer.csv","w");
    fclose(fp);
    fp=fopen("priority.txt","w");
    fprintf(fp,"%d",10000);
    fclose(fp);
}
//To print the contents of the queue
void printQueue(CUSTOMER **node)
{
    int i = 1;
    //checking if the queue is empty.
    if (*node == NULL)
    {
        printf("Empty Queue");
        return;
    }
    //printing the contents of the queue.
    printf("SLno.\tCustomer\tAmount\tPriority\n");
    CUSTOMER * temp = *node;
    while (temp)
    {
        printf("%d\t%s\t\t%d\t%d\n",i,temp->name,temp->amt,temp->priority);
        temp = temp->next;
        i++;
    }
}