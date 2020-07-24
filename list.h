typedef struct Customer
{
    int amt;
    char name[35];
    int priority;
    struct Customer *next;
}CUSTOMER;
CUSTOMER* newNode(int,char *,int);//to create a new node
void insert(CUSTOMER**,int,char *);//to insert a new customer into your queue and file
CUSTOMER* peek(CUSTOMER**);//to return the head of the queue
void pop(CUSTOMER**);//to dequeue
int isEmpty(CUSTOMER**);//to check if the queue is empty
int noOfLines(FILE*);//to find the number of lines in a file.
int priority(char *,int);//to assign priority to the customer
void reset();//to reset the contents of the file
void changeThreshold(int);//to change the threshold
void printcsv();//print the contents of the CSV file
void printQueue(CUSTOMER**);//prints the customer in the queue