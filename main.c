#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define TRUE 1
#define FALSE 0

int global_clock = 0;

typedef struct Customer
{
    char id[100000]; // customer id
    int arr_time;    // time customer arrive at bank
    int ser_time;    // how many time the business of customer will cost
    struct Customer *next;
} Customer;

struct queue
{
    int current_served_time; // time already spent by customer currently dealing with business
    int status;              // 0: close, 1: remain one customer, about closing, 2: open
    int count;               // the number of people in the queue
    Customer *front;
    Customer *rear;
};

typedef struct queue queue;

queue tellerQueue[10];

void initialize(queue *q)
{
    q->count = 0;
    q->front = NULL;
    q->rear = NULL;
}

int isempty(queue *q)
{
    return (q->rear == NULL);
}

void enqueue(queue *q, char *id, int arr_time, int ser_time)
{

    Customer *tmp;
    tmp = (Customer *)malloc(sizeof(Customer));

    // data assign
    strcpy(tmp->id, id);
    tmp->arr_time = arr_time;
    tmp->ser_time = ser_time;
    tmp->next = NULL;
    if (!isempty(q))
    {
        q->rear->next = tmp;
        q->rear = tmp;
    }
    else
    {
        q->front = q->rear = tmp;
    }
    q->count++;
}

Customer *dequeue(queue *q)
{

    Customer *tmp;
    Customer *n = q->front;
    tmp = q->front;
    if (q->count >= 2)
    {
        q->front = q->front->next;
        q->count--;
        free(tmp);
    }
    else
    {

        initialize(q);
    }
    return (n);
}

void display(Customer *head)
{
    if (head == NULL)
    {
        printf("NULL\n");
    }
    else
    {
        printf("%s %d %d -> ", head->id, head->arr_time, head->ser_time);
        display(head->next);
    }
}

int GetShortestQueueId(int numbers_of_teller)
{
    int ans = 0;
    int ans_value = tellerQueue[0].count;
    for (int i = 1; i < numbers_of_teller; i++)
    {
        if (tellerQueue[i].status != 0)
        {
            if (tellerQueue[i].count < ans_value)
            {
                ans = i;
                ans_value = tellerQueue[i].count;
            }
        }
    }
    return ans;
}

Customer *getCustomer(int queueId, int index)
{
    Customer *tmp;
    Customer *before = tellerQueue[queueId].front;
    Customer *cur = tellerQueue[queueId].front->next;
    tmp = cur;

    if (tellerQueue[queueId].count <= 2)
    {
        before->next = cur->next;
        tellerQueue[queueId].rear = tellerQueue[queueId].front;
    }
    else
    {
        before->next = cur->next;
    }

    tellerQueue[queueId].count--;

    return cur;
}

int check_if_remain(int numbers_of_teller)
{
    for (int i = 0; i < numbers_of_teller; i++)
    {
        if (tellerQueue[i].count != 0)
        {
            return TRUE;
        }
    }
    return FALSE;
}
int main()
{
    int numbers_of_teller = 0;
    FILE *fptr = fopen("inp.txt", "r");
    FILE *fptr2 = fopen("output.txt", "w+");

    fscanf(fptr, "%d\n", &numbers_of_teller);

    // initialize tellerQueue
    for (int i = 0; i < 10; i++)
    {
        tellerQueue[i].count = 0;
        tellerQueue[i].current_served_time = 0;
        tellerQueue[i].front = NULL;
        tellerQueue[i].rear = NULL;
        tellerQueue[i].status = 2; // open
    }

    char string[100000];
    int num1;
    int num2;
    // read input file
    while (fscanf(fptr, "%s %d %d\n", string, &num1, &num2) != EOF)
    {
        while (global_clock != num1)
        {
            global_clock++;
            for (int i = 0; i < numbers_of_teller; i++)
            {
                if (tellerQueue[i].count > 0)
                {
                    tellerQueue[i].current_served_time++;

                    if (tellerQueue[i].current_served_time >= tellerQueue[i].front->ser_time)
                    {
                        Customer *c = dequeue(&tellerQueue[i]);
                        fprintf(fptr2, "%s %d %d\n", c->id, global_clock, i);
                        tellerQueue[i].current_served_time = 0; // initialize
                    }
                }
            }
        }
        // operation
        if (string[0] == '#')
        { // close operation
            tellerQueue[num2].status = 0;

            // FromTheSecond
            while (tellerQueue[num2].count > 1)
            {
                Customer *customer = getCustomer(num2, 1);
                int shortestQueueId = GetShortestQueueId(numbers_of_teller);
                enqueue(&tellerQueue[shortestQueueId], customer->id, customer->arr_time, customer->ser_time);
            }
        }
        else if (string[0] == '@')
        { // open operation
            tellerQueue[num2].status = 2;
        }
        else
        { // join operation

            // creat a person
            Customer *person = (Customer *)malloc(sizeof(Customer));
            strcpy(person->id, string);

            person->arr_time = num1;
            person->ser_time = num2;
            person->next = NULL;

            int shortest_queue_id = GetShortestQueueId(numbers_of_teller);

            // insert into the shortest queue
            enqueue(&tellerQueue[shortest_queue_id], person->id, person->arr_time, person->ser_time);
        }
    }
    fclose(fptr);
    // processing the remain
    while (check_if_remain(numbers_of_teller))
    {
        global_clock++;
        for (int i = 0; i < numbers_of_teller; i++)
        {
            if (tellerQueue[i].count > 0)
            {
                tellerQueue[i].current_served_time++;

                if (tellerQueue[i].current_served_time >= tellerQueue[i].front->ser_time)
                {
                    Customer *c = dequeue(&tellerQueue[i]);
                    fprintf(fptr2, "%s %d %d\n", c->id, global_clock, i);
                    tellerQueue[i].current_served_time = 0; // initialize
                }
            }
        }
    }
    
    return 0;
} // end of main
