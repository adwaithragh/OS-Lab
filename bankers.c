#include <stdio.h>
int pn,rn,alloc[10][10],max[10][10],avail[10],safeseq[10],flag,finish[10],need[10][10],i,j,k;
void bankers()
{
	for(i=0;i<pn;i++)
	{
		finish[i]=0;
	}
	for(i=0;i<pn;i++)
        {
		flag=0;
		if(finish[i]==0)
		{
			for(j=0;j<rn;j++)
        		{
				if(need[i][j]>avail[j])
				{
					flag=1;
					break;
				}
			}
			if(flag==0)
			{
				finish[i]=1;
				safeseq[k]=i;
				k++;
				for(j=0;j<rn;j++)
                       		{
					avail[j]+=alloc[i][j];
				}
				i=-1;
			}
		}
	}
	flag=0;
	for(i=0;i<pn;i++)
        {
		if(finish[i]==0)
		{
			printf("System is in deadlock\n");
			flag=1;
			break;
		}
	}
	if(flag==0)
	{
		printf("System is in safe state\nSafe sequence is: ");
		for(i=0;i<pn-1;i++)
		{
			printf("P%d->",safeseq[i]);
		}
		printf("P%d\n",safeseq[pn-1]);
	}
}
void main()
{
	printf("Enter the number of processes: ");
	scanf("%d",&pn);
	printf("Enter the number of resources: ");
        scanf("%d",&rn);
	printf("Enter the allocation matrix: \n");
	for(i=0;i<pn;i++)
	{
		for(j=0;j<rn;j++)
        	{
        		scanf("%d",&alloc[i][j]);
		}
	}
	printf("Enter the max matrix: \n");
        for(i=0;i<pn;i++)
        {
                for(j=0;j<rn;j++)
                {
                        scanf("%d",&max[i][j]);
                }
        }
	printf("Enter the available matrix: \n");
        for(j=0;j<rn;j++)
        {
        	scanf("%d",&avail[j]);
        }
        for(i=0;i<pn;i++)
        {
                for(j=0;j<rn;j++)
                {
                        need[i][j]=max[i][j]-alloc[i][j];
                }
        }
	printf("The need matrix is: \n");
        for(i=0;i<pn;i++)
        {
                for(j=0;j<rn;j++)
                {
                        printf("%d\t",need[i][j]);
                }
		printf("\n");
        }
	bankers();
}

