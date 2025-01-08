#include<stdio.h>
int fn,pn,frames[10],pages[30];
void fifo()
{
	printf("\nFIFO PAGE REPLACEMENT\n");
	int i,j,k=0,faults=0;
	for(i=0;i<fn;i++)
        {
                frames[i]=-1;
        }
	printf("_______________________________________");
	printf("\nREF STRING\tPAGE FRAMES\n\n");
        printf("_______________________________________\n");
	for(i=0;i<pn;i++)
        {
                printf("%d\t\t",pages[i]);
		int avail=0;
		for(j=0;j<fn;j++)
        	{
                	if(frames[j]==pages[i])
			{
				avail=1;
			}
        	}
		if(avail==0)
		{
			faults++;
			frames[k]=pages[i];
			k=(k+1)%fn;
		}
		for(j=0;j<fn;j++)
        	{
                	printf("%d\t",frames[j]);
        	}
		printf("\n");
        }
        printf("_______________________________________");
	printf("\n Page faults: %d\n",faults);
}
int findlru(int time[],int n)
{
	int  i,min=time[0],pos=0;
	for(i=1;i<n;i++)
	{
		if(min>time[i])
		{
			min=time[i];
			pos=i;
		}
	}
	return pos;
}
void lru()
{
	printf("\nLRU PAGE REPLACEMENT\n");
        int i,j,flag1,flag2,counter=0,faults=0,pos,time[10];
        for(i=0;i<fn;i++)
        {
                frames[i]=-1;
        }
        printf("_______________________________________");
        printf("\nREF STRING\tPAGE FRAMES\n\n");
        printf("_______________________________________\n");
        for(i=0;i<pn;i++)
        {
                printf("%d\t\t",pages[i]);
                flag1=flag2=0;
                for(j=0;j<fn;j++)
                {
                        if(frames[j]==pages[i])
                        {
				counter++;
				time[j]=counter;
                                flag1=flag2=1;
				break;
                        }
                }
                if(flag1==0)
                {
			for(j=0;j<fn;j++)
			{
				if(frames[j]==-1)
				{
                        		counter++;
					faults++;
                	        	frames[j]=pages[i];
                	        	time[j]=counter;
					flag2=1;
					break;
				}
			}
                }
		if(flag2==0)
                {
                        pos=findlru(time,fn);
			counter++;
			faults++;
			frames[pos]=pages[i];
			time[pos]=counter;
		}
		for(j=0;j<fn;j++)
                {
                        printf("%d\t",frames[j]);
                }
                printf("\n");
        }
        printf("_______________________________________");
        printf("\n Page faults: %d\n",faults);
}
void optimal()
{
	printf("\nOPTIMAL PAGE REPLACEMENT\n");
        int i,j,k,flag1,flag2,flag3,faults=0,temp[10],max,pos;
        for(i=0;i<fn;i++)
        {
                frames[i]=-1;
        }
        printf("_______________________________________");
        printf("\nREF STRING\tPAGE FRAMES\n\n");
        printf("_______________________________________\n");
        for(i=0;i<pn;i++)
        {
                printf("%d\t\t",pages[i]);
                flag1=flag2=0;
                for(j=0;j<fn;j++)
                {
                        if(frames[j]==pages[i])
                        {
                                flag1=flag2=1;
                                break;
                        }
                }
                if(flag1==0)
                {
                        for(j=0;j<fn;j++)
                        {
                                if(frames[j]==-1)
                                {
                                        faults++;
                                        frames[j]=pages[i];
					flag2=1;
                                        break;
                                }
                        }
                }
                if(flag2==0)
                {
                       	flag3=0;
                        for(j=0;j<fn;j++)
			{
				temp[j]=-1;
				for(k=i+1;k<pn;k++)
				{
					if(frames[j]==pages[k])
					{
						temp[j]=k;
					}
				}
			}
			for(j=0;j<fn;j++)
                        {
                                if(temp[j]==-1)
                                {
                                        pos=j;
					flag3=1;
					break;
                                }
                        }
			if(flag3==0)
			{
				max=temp[0];
				pos=0;
				for(j=0;j<fn;j++)
                        	{
					if(temp[j]>max)
					{
						max=temp[j];
						pos=j;
					}
				}
			}
			frames[pos]=pages[i];
			faults++;
                }
                for(j=0;j<fn;j++)
                {
                        printf("%d\t",frames[j]);
                }
                printf("\n");
        }
        printf("_______________________________________");
        printf("\n Page faults: %d\n",faults);
}
void lfu()
{
	printf("\nLFU PAGE REPLACEMENT\n");
	int i,j,move=0,faults=0,flag,count1[30];
	for(i=0;i<fn;i++)
	{
		frames[i]=-1;
	}
	printf("_______________________________________");
        printf("\nREF STRING\tPAGE FRAMES\n\n");
        printf("_______________________________________\n");
	for(i=0;i<pn;i++)
	{
		printf("%d\t\t",pages[i]);
                flag=0;
		for(j=0;j<fn;j++)
		{
			if(frames[j]==pages[i])
			{
				count1[j]++;
				flag=1;
				break;
			}
		}
		if(flag==0 && faults<fn)
		{
			frames[move]=pages[i];
			count1[move]=1;
			move=(move+1)%fn;
			faults++;
		}
		else if(flag==0)
		{
			int repindex=0,mincount=count1[0];
			for(j=1;j<fn;j++)
			{
				if(count1[j]<mincount)
				{
					mincount=count1[j];
					repindex=j;
				}
			}
			frames[repindex]=pages[i];
			count1[repindex]=1;
			faults++;
		}
		for(j=0;j<fn;j++)
		{
			printf("%d\t",frames[j]);
		}
		printf("\n");
	}
	printf("\nPAGE FAULTS : %d\n",faults);
}
void main()
{
	int i;
	printf("Enter the number of frames: ");
	scanf("%d",&fn);
	printf("Enter the number of pages: ");
        scanf("%d",&pn);
	printf("Enter the reference string: ");
	for(i=0;i<pn;i++)
	{
        	scanf("%d",&pages[i]);
	}
	fifo();
	lru();
	lfu();
}
