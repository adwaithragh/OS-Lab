#include <stdio.h>
struct process
{
	int pid;
	int at;
	int bt;
	int prio;
	int ct;
	int tat;
	int wt;
	int completed;
	int st;
	int rt;
}p[10],temp;
int n,i,j,total;
void display()
{
	float avgwt=0,avgtat=0;
	printf("___________________________________________________________________________________\nPID | Arrival time | Burst time | Turn around time | Completion time | Waiting time\n___________________________________________________________________________________\n");
	for(i=0;i<n;i++)
        {
		printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",p[i].pid,p[i].at,p[i].bt,p[i].tat,p[i].ct,p[i].wt);
		avgwt+=p[i].wt;
		avgtat+=p[i].tat;
	}
	printf("___________________________________________________________________________________\n");
	printf("\n Average waiting time: %f",avgwt/n);
        printf("\n Average turnaround time: %f\n",avgtat/n);
}
void fcfs()
{
	total=0;
	printf("\nFIRST COME FIRST SERVE\n\n");
	for(i=0;i<n-1;i++)
	{
		for(j=0;j<n-i-1;j++)
		{
			if(p[j].at>p[j+1].at)
			{
				temp=p[j];
				p[j]=p[j+1];
				p[j+1]=temp;
			}
		}
	}
	for(i=0;i<n;i++)
        {
                while(total<p[i].at)
                {
                        total++;
                }
                p[i].ct=total+p[i].bt;
                total=p[i].ct;
                p[i].tat=p[i].ct-p[i].at;
                p[i].wt=p[i].tat-p[i].bt;
        }
	display();
}
void sjf()
{
	int totalburst=0,completed=0,currenttime=0;
	printf("\nSHORTEST JOB FIRST\n\n");
	for(i=0;i<n;i++)
	{
		totalburst+=p[i].bt;
		p[i].completed=0;
	}
        for(i=0;i<n-1;i++)
        {
                for(j=0;j<n-i-1;j++)
                {
                        if(p[j].at>p[j+1].at)
                        {
                                temp=p[j];
                                p[j]=p[j+1];
                                p[j+1]=temp;
                        }
                }
        }
	for(i=0;i<n-1;i++)
        {
                for(j=0;j<n-i-1;j++)
		{
                        if(p[j].at==p[j+1].at && p[j].bt>p[j+1].bt)
                        {
                                temp=p[j];
                                p[j]=p[j+1];
                                p[j+1]=temp;
                        }
                }
        }
        while(completed!=n)
	{
		int min_index=-1;
		int minimum=totalburst;
		for(i=0;i<n;i++)
		{
			if(p[i].at<=currenttime && p[i].completed==0)
			{
				if(p[i].bt<minimum)
				{
					minimum=p[i].bt;
					min_index=i;
				}
				if(p[i].bt==minimum)
				{
					if(p[i].at<p[min_index].at)
					{
						minimum=p[i].bt;
						min_index=i;
					}
				}
			}
		}
		if(min_index==-1)
		{
			currenttime++;
		}
		else
		{
			p[min_index].st=currenttime;
			p[min_index].ct=p[min_index].st+p[min_index].bt;
			p[min_index].tat=p[min_index].ct-p[min_index].at;
			p[min_index].wt=p[min_index].tat-p[min_index].bt;
			completed++;
			p[min_index].completed=1;
			currenttime=p[min_index].ct;
		}
	}
        display();
}
void priority()
{
	int completed=0,currenttime=0;
        printf("\nPRIORITY SCHEDULING\n\n");
        for(i=0;i<n;i++)
        {
                p[i].completed=0;
        }
        for(i=0;i<n-1;i++)
        {
                for(j=0;j<n-i-1;j++)
                {
                        if(p[j].at>p[j+1].at)
                        {
                                temp=p[j];
                                p[j]=p[j+1];
                                p[j+1]=temp;
                        }
                }
        }
        for(i=0;i<n-1;i++)
        {
                for(j=0;j<n-i-1;j++)
                {
                        if(p[j].at==p[j+1].at && p[j].prio>p[j+1].prio)
                        {
                                temp=p[j];
                                p[j]=p[j+1];
                                p[j+1]=temp;
                        }
                }
        }
        while(completed!=n)
        {
                int max_prio=10000;
                int min_index=-1;
                for(i=0;i<n;i++)
                {
                        if(p[i].at<=currenttime && p[i].completed==0)
                        {
                                if(p[i].prio<max_prio)
                                {
                                        max_prio=p[i].prio;
                                        min_index=i;
                                }
                                if(p[i].prio==max_prio)
                                {
                                        if(p[i].at<p[min_index].at)
                                        {
                                                max_prio=p[i].prio;
                                                min_index=i;
                                        }
                                }
                        }
                }
                if(min_index==-1)
                {
                        currenttime++;
                }
                else
                {
                        p[min_index].st=currenttime;
                        p[min_index].ct=p[min_index].st+p[min_index].bt;
                        p[min_index].tat=p[min_index].ct-p[min_index].at;
                        p[min_index].wt=p[min_index].tat-p[min_index].bt;
                        completed++;
                        p[min_index].completed=1;
                        currenttime=p[min_index].ct;
                }
        }
        display();
}
void roundrobin()
{
	int slice,i,j,time,remain,flag;
	float avg_wt=0,avg_tat=0;
	printf("\nROUND ROBIN SCHEDULING\n\n");
	printf("Enter the time slice: ");
	scanf("%d",&slice);
	for(i=0;i<n-1;i++)
        {
                for(j=0;j<n-i-1;j++)
                {
                        if(p[j].at>p[j+1].at)
                        {
                                temp=p[j];
                                p[j]=p[j+1];
                                p[j+1]=temp;
                        }
                }
        }
	for(i=0;i<n;i++)
	{
		p[i].rt=p[i].bt;
		p[i].completed=0;
	}
	remain=n;
        printf("___________________________________________________________________________________\nPID | Arrival time | Burst time | Turn around time | Completion time | Waiting time\n___________________________________________________________________________________\n");
	for(time=0,i=0;remain!=0;)
	{
		if(p[i].rt<=slice && p[i].rt>0)
		{
			time+=p[i].rt;
			p[i].rt=0;
			flag=1;
		}
		else if(p[i].rt>0)
		{
			p[i].rt=p[i].rt-slice;
			time=time+slice;
		}
		if(p[i].rt==0 && flag==1)
		{
			remain--;
                	printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",p[i].pid,p[i].at,p[i].bt,(time-p[i].at),time,(time-p[i].at-p[i].bt));
			avg_tat+=time-p[i].at;
			avg_wt+=(time-p[i].at)-p[i].bt;
			flag=0;
		}
		if(i==(n-1))
		{
			i=0;
		}
		else if(p[i+1].at<=time)
		{
			i++;
		}
		else
		{
			i=0;
		}
	}
	printf("\nAverage turnaround time:%f",avg_tat/n);
        printf("\nAverage waiting time:%f\n",avg_wt/n);
}
void main()
{
	printf("Enter the number of processes\n");
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		printf("Enter the pid,arrival time,burst time,priority\n");
		scanf("%d%d%d%d",&p[i].pid,&p[i].at,&p[i].bt,&p[i].prio);
	}
	fcfs();
	sjf();
	priority();
	roundrobin();
}
-
