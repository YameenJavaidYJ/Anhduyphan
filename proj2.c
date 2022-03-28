#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Process
{
    int pid, arrival, burst_time, priority, lastActive, waitingTime, response;
};

struct Circular_Linked_List
{
    struct Process data;
    struct Circular_Linked_List *next;
};

typedef struct Circular_Linked_List node;
typedef struct Process Process_;

node * init_node()
{
    node * temp;
    Process_ process;
    process.pid = -1;
    process.arrival = -1;
    process.burst_time = -1;
    temp = (node * )malloc(sizeof(node));
    temp->data = process;
    temp->next = NULL;
    return temp;
}

node * get_tail(node * n)
{
    node * temp = n;
    while (temp->next != NULL)
        temp = temp->next;
    return temp;
}

node * insert_node(node * n, Process_ p)
{
    node * temp;
    node * tail;
    temp = init_node();
    temp->data = p;

    if (n == NULL)
        n = temp;

    else
    {
        tail = get_tail(n);
        tail->next = temp;
    }
    return n; 
}

node * removeNode(node * n)
{
    node * next;
    next = n->next;
    return next;
}

int calculateTurnAround(int arrival, int current, int turnAround)
{
    int difference = 0;
    difference = current - arrival;
    turnAround = turnAround + difference;
    return turnAround;
}


int calculateWait(int current, int lastActive)
{
    int difference = 0;
    difference = current - lastActive;
    return difference;
}

int calculateResponse(int arrival, int current, int response)
{
    int difference = 0;
    difference = current - arrival;
    response = response + difference;
    return response;
}

node * rebuild_LinkedList(node * oldNode, node * init_node, int time)
{
    Process_ p;
    while(oldNode != NULL)
    {
        p = oldNode->data;
        if (p.arrival <= time)
            init_node = insert_node(init_node, p);
        oldNode = removeNode(oldNode);
    }
    return init_node;
}

node * sortedInsert (node * n, Process_ p)
{
    node * current_ll = n; 
    node * next = current_ll->next;
    node * new_node;
    node * head;
    Process_ newP, nextP;
    new_node = init_node();
    new_node = insert_node(new_node, p);
    new_node = removeNode(new_node);
    newP = current_ll->data;

    if (p.burst_time < newP.burst_time) 
    {
        new_node->next = current_ll;
        return new_node;
    }
    if (current_ll->next == NULL)  
    {
        current_ll->next = new_node;
        return current_ll;
    }

    while (current_ll != NULL)
    {
        newP = current_ll->data;
        nextP = next->data;
        if( p.burst_time < nextP.burst_time) 
        {
            new_node->next = next;
            current_ll->next = new_node;
            return n;
        }
        if(next->next == NULL)
        {
            next->next = new_node;
            return head;
        }
        next = next->next;
        current_ll = current_ll->next;
    }
    return new_node;
}

node * rebuild_LinkedListSorted(node * oldNode, node * init_node, int time)
{
    Process_ p0, p1;

    while (oldNode != NULL)
    {
        p0 = oldNode->data;

        if (p0.arrival <= time)
        {
            if (init_node == NULL)
                init_node = insert_node(init_node, p0);
            p1 = init_node->data;
            
            if (p1.pid == -1)
            {
                init_node = insert_node(init_node, p0);
                init_node = removeNode(init_node);
            }
            else
                init_node = sortedInsert(init_node, p0);
        }
        oldNode = removeNode(oldNode);
    }
    return init_node;
}

node * updateArrival(node * head, int t)
{
    Process_ p;

    while (head != NULL)
    {
        p = head->data;

        if (p.arrival <= t)
            head = removeNode(head);
        else
            break;
    }

    return head; 
}


void FCFS(node * n)
{
    Process_ process;
    node * head = n; 
    node * current = n;
    int currentTime = 0; 
    int workTime = 0;
    float turnAroundTime = 0;
    float waitTime = 0;
    float responseTime = 0;
    float cpuSimulation;

    if(current == NULL)
        return; 

    process = current->data;
    responseTime = process.arrival;

    
    while (current != NULL)
    {
        if (process.arrival <= currentTime)
        {
            if(process.burst_time == 0)
            {
                printf("<System Time:\t%d>\t\tprocess %d has finished......\n",
                       currentTime, process.pid);
                waitTime += process.waitingTime;
                current = removeNode(current);
                turnAroundTime = calculateTurnAround(process.arrival, currentTime, 
                                                turnAroundTime);
                
                if (current != NULL)
                {
                    process = current->data;
                    process.waitingTime += calculateWait(currentTime, process.lastActive);

                    while (process.waitingTime > currentTime)
                    {
                        currentTime++;
                        printf("<System time:\t%d>\t\tNo process is currently running.\n",
                         currentTime);
                    }

                    responseTime = calculateResponse(process.arrival, currentTime, 
                                                responseTime);
                }

                else
                {
                    printf("<System time:\t%d>\t\tAll processes have finished!\n", 
                           currentTime);
                    break;
                }
            }
            
            printf("<System time:\t%d>\t\tprocess %d is running.\n", currentTime, 
                   process.pid);
            process.burst_time--;
            workTime++;
        }

        currentTime++;
    }

    cpuSimulation = (((float)workTime / (float)currentTime) * 100);
    printf("--------------------------------------------------------------------------------\n");
    printf("Average CPU usage:\t\t%0.3f\n", cpuSimulation);
    printf("Average waiting time:\t\t%0.3f\n", waitTime/6);
    printf("Average response time:\t\t%0.3f\n", responseTime/6);
    printf("Average turn around time:\t%0.3f\n", turnAroundTime/6);
    printf("--------------------------------------------------------------------------------\n");
}


node * Highest_priority(node * current_processList)
{
    node * temp = current_processList;
    node * highest_Prio ;
    int max_prio = 0;
    while(temp!=NULL)
    {
        if(temp->data.priority > max_prio)
        {
            max_prio = temp->data.priority;
            highest_Prio = temp;
        }
        temp = temp->next;
    }
    return highest_Prio;
}   





void PP(node * n, int c)
{
    Process_ process;
    int currentTime = 0;
    int workTime = 0;
    int turnAroundTime = 0;
    int execution = 0;
    float response = 0;
    float waitTime = 0;
    node * tempNode = init_node();

    tempNode = rebuild_LinkedListSorted(n, tempNode, currentTime);
    n = updateArrival(n, currentTime);
    process = tempNode->data;
    response = process.arrival;
    process.response = 1;
    process.waitingTime = 0;

    while(c > 0)
    {
        if (process.arrival <= currentTime)
        {
            node * highest_priority = Highest_priority(tempNode);
            printf("This process Should be Execute Now: %d\n",highest_priority->data.pid);
            workTime++;
            printf("<system time    %d> process    %d is running \n", currentTime, process.pid);
            process.burst_time--;
            currentTime++;

            if(process.burst_time <= 0)
            {
                printf("<system time    %d> process    %d is finished.......\n", currentTime, process.pid);
                turnAroundTime = calculateTurnAround(process.arrival, currentTime, turnAroundTime);
                waitTime += process.waitingTime;
                tempNode = removeNode(tempNode);
                c--;

                if (c > 0)
                {
                    while (tempNode == NULL)
                    {
                        printf("<System time:\t%d>\t\tNo process is currently running.\n", currentTime);
                        currentTime++;
                        tempNode = rebuild_LinkedListSorted(n, tempNode, currentTime);
                        n = updateArrival(n, currentTime);
                    }

                    process = tempNode->data;
                    process.waitingTime += calculateWait(currentTime, process.lastActive);
                    process.lastActive = currentTime;
                    execution = process.burst_time;

                    if(process.response != 1)
                    {
                        response = calculateResponse(process.arrival, currentTime, response);
                        process.response = 1;
                    }
                }

                else 
                {
                    printf("<System time:\t%d>\t\tAll processes have finished!\n", currentTime);
                    break;
                }
            }
            process.lastActive = currentTime;
            tempNode->data = process;
            tempNode = rebuild_LinkedListSorted(n, tempNode, currentTime);
            n = updateArrival(n, currentTime);
            process = tempNode->data;
            process.waitingTime += calculateWait(currentTime, process.lastActive);

            if (process.response != 1)
            {
                response = calculateResponse(process.arrival, currentTime, response);
                process.response = 1;
            }
        }

        else 
            currentTime++;
    }
    float cpuSimultation = ((float) workTime / (float)currentTime) * 100;
    printf("-----------------------------------------------------------------------------------\n");
    printf("Average CPU usage:\t\t%0.3f\n", cpuSimultation);
    printf("Average waiting time:\t\t%0.3f\n", waitTime/6);
    printf("Average response time:\t\t%0.3f\n", response/6);
    printf("Average turn around time:\t%0.3f\n", (float)turnAroundTime/6);
    printf("-----------------------------------------------------------------------------------\n");
}

// Round Robbin
void rr(node * head, int quantum, int tasks)
{
    int currentTime = 0;
    int workTime = 0;
    int turnAroundTime = 0;
    int waitTime = 0;
    int maxQuantum = quantum;
    int currentQuatum = quantum;
    node * tempNode = init_node();
    tempNode = rebuild_LinkedList(head, tempNode, currentTime);
    tempNode = removeNode(tempNode);
    head = updateArrival(head, currentTime);
    Process_ p = tempNode->data;
    int responseTime = p.arrival;
    p.response = 1;
    int executionTime = p.burst_time;

    while (tasks > 0)
    {
        if (p.arrival <= currentTime)
        {
            workTime++;
            printf("<system time    %d> process    %d is running\n", currentTime, p.pid);
            p.burst_time--;
            currentTime++;
            currentQuatum--;

            if (p.burst_time <= 0)
            {
                printf("<system time    %d> process    %d is finished.......\n", currentTime, p.pid);
                turnAroundTime = calculateTurnAround(p.arrival, currentTime, turnAroundTime);
                waitTime += p.waitingTime;
                tempNode = removeNode(tempNode);
                tasks--;

                if(tasks > 0)
                {
                    while (tempNode == NULL)
                    {
                        printf("<system time    %d> no process is running\n", currentTime);
                        currentTime++;
                        tempNode = rebuild_LinkedList(head, tempNode, currentTime);
                        head = updateArrival(head, currentTime);
                    }

                    p = tempNode->data;
                    p.waitingTime = p.waitingTime + calculateWait(currentTime, p.lastActive);
                    p.lastActive = currentTime;
                    executionTime = p.burst_time;

                    if(p.response != 1)
                    {
                        responseTime = calculateResponse(currentTime, p.arrival, responseTime);
                        p.response = 1;
                    }
                }
                else 
                {
                    printf("<system time    %d> All processes finish ....................\n", currentTime);
                    break;
                }
                currentQuatum = maxQuantum;
            }
            tempNode = rebuild_LinkedList(head, tempNode, currentTime);
            head = updateArrival(head, currentTime);

            if (currentQuatum == 0)
            {
                p.lastActive = currentTime;
                tempNode = removeNode(tempNode);
                tempNode = insert_node(tempNode, p);
                p = tempNode->data;
                p.waitingTime += calculateWait(currentTime, p.lastActive);
                executionTime = p.burst_time;

                if (p.response != 1)
                {
                    responseTime = calculateResponse(currentTime, p.arrival, responseTime);
                    p.response = 1;
                }
                currentQuatum = maxQuantum;
            }
        }
        else
        {
            currentTime++;
            tempNode = rebuild_LinkedList(head, tempNode, currentTime);
            head = updateArrival(head, currentTime);
        }
    }

    
    responseTime = 0 - responseTime;
    float cpu = ((float)workTime/(float)currentTime)*100;
    printf("=================================================================================\n");
    printf("Average Cpu Usage          : %0.2f \n", cpu);
    printf("Average Waiting Time       : %0.2f \n", (float)waitTime/6);
    printf("Average Response Time      : %0.2f \n", (float)responseTime/6);
    printf("Average Turnaround Time    : %0.2f\n", (float)turnAroundTime/6);
    printf("=================================================================================\n");
}

int main(int argc, char *argv[])
{
    char scheduler[5];
    int quantum = -1;
    int runOption = -1;

    if (argc == 3)
    {
        sscanf(argv[2], "%s", scheduler);
        if (strcmp(scheduler, "FCFS") == 0)
        {
            printf("You have chosen the CPU Scheduling Algorithm: %s\n", 
                   scheduler);
            runOption = 0;
        }

        else if (strcmp(scheduler, "PP") == 0)
        {
            printf("You have chosen the CPU Scheduling Algorithm: %s\n", 
                   scheduler);
            runOption = 1;
        }

        else
        {
            
            printf("Usage: CPUSchedulingSimulation [File] [FCFS | RR | PP] ");
            printf("[Quntum Time]\n");
            return 0;
        }
    }

    else if (argc == 4)
    {
        sscanf(argv[2], "%s", scheduler);
        sscanf(argv[3], "%d", &quantum);

        if (quantum < 1)
        {
            printf("You need to have a [Quantum] Value >= 1\n");
            return 0;
        }

        if (strcmp(scheduler, "RR") == 0)
        {
            printf("You have chosen the CPU Scheduling Algorithm: %s\n", 
                   scheduler);
            runOption = 2;
        }

        else
        {
            
            printf("Usage: CPUSchedulingSimulation [File] [FCFS | RR | PP] ");
            printf("[Quntum Time]\n");
            return 0;
        }
    }

    else 
    {
        
        printf("Usage: CPUSchedulingSimulation [File] [FCFS | RR | PP] ");
        printf("[Quntum Time]\n");
        return 0;
    }

    FILE *proccesses = fopen(argv[1], "r");
    node * head = init_node();
    int pid, arrival, burst_time, priority;
    Process_ process;
    int count = 0; 
    while (fscanf(proccesses, "%d %d %d %d", &pid, &arrival, &burst_time, & priority) > 0)
    {
        process.pid = pid;
        process.arrival = arrival;
        process.burst_time = burst_time;
        process.priority = priority;
        process.response = -1;
        process.waitingTime = 0;
        process.lastActive = process.arrival;
        count++;
        head = insert_node(head, process);
    }
    
    head = removeNode(head);
    fclose(proccesses);
    printf("Total %d task have been read from %s. Press 'Enter' to start!", count,
           argv[1]);
    int c = getc(stdin);

    if(c == '\n')
    {
        if(runOption == 0)
            FCFS(head);
        else if (runOption == 1)
            PP(head, count);
        else
            rr(head, quantum, count);
    }
    return 0; 
}
