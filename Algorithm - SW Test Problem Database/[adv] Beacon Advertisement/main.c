#include<stdio.h>

int main()
{
	//variables
	int i,j,k,l;
	int N;
	int L[3];
	int P[3];
	int A[50];
	int D[50];
	int totalpoint;
	int temp;

	//init
	totalpoint = 0;

	//read input
	scanf("%d %d %d %d %d %d %d", &N, &(L[0]), &(L[1]), &(L[2]), &(P[0]), &(P[1]), &(P[2]));
	for(i=0; i<N; i++)
	{
		scanf("%d %d", &(A[i]), &(D[i]));
	}

	//sort ads by point
	for(i=0; i<2; i++)
	{
		for(j=i+1; j<3; j++)
		{
			if(P[i] < P[j])
			{
				temp = P[i];
				P[i] = P[j];
				P[j] = temp;
				temp = L[i];
				L[i] = L[j];
				L[j] = temp;
			}
		}
	}

	//012
	for(i=0; i < 50; i++)
	{
		for(j=i+L[0]; j < 50; j++)
		{
			for(k=j+L[1]; k < 50; k++)
			{
				temp = 0;
				for(l=0; l<N; l++)
				{
					if((A[l] <= i) && ((A[l] + D[l]) >= i + L[0]))
					{
						temp += P[0];
					}
					else if((A[l] <= j) && ((A[l] + D[l]) >= j + L[1]))
					{
						temp += P[1];
					}
					else if((A[l] <= k) && ((A[l] + D[l]) >= k + L[2]))
					{
						temp += P[2];
					}
				}
				if(temp > totalpoint)
				{
					totalpoint = temp;
				}
			}
		}
	}

	//021
	for(i=0; i < 50; i++)
	{
		for(j=i+L[0]; j < 50; j++)
		{
			for(k=j+L[2]; k < 50; k++)
			{
				temp = 0;
				for(l=0; l<N; l++)
				{
					if((A[l] <= i) && ((A[l] + D[l]) >= i + L[0]))
					{
						temp += P[0];
					}
					else if((A[l] <= k) && ((A[l] + D[l]) >= k + L[1]))
					{
						temp += P[1];
					}
					else if((A[l] <= j) && ((A[l] + D[l]) >= j + L[2]))
					{
						temp += P[2];
					}
				}
				if(temp > totalpoint)
				{
					totalpoint = temp;
				}
			}
		}
	}

	//102
	for(i=0; i < 50; i++)
	{
		for(j=i+L[1]; j < 50; j++)
		{
			for(k=j+L[0]; k < 50; k++)
			{
				temp = 0;
				for(l=0; l<N; l++)
				{
					if((A[l] <= j) && ((A[l] + D[l]) >= j + L[0]))
					{
						temp += P[0];
					}
					else if((A[l] <= i) && ((A[l] + D[l]) >= i + L[1]))
					{
						temp += P[1];
					}
					else if((A[l] <= k) && ((A[l] + D[l]) >= k + L[2]))
					{
						temp += P[2];
					}
				}
				if(temp > totalpoint)
				{
					totalpoint = temp;
				}
			}
		}
	}

	//120
	for(i=0; i < 50; i++)
	{
		for(j=i+L[1]; j < 50; j++)
		{
			for(k=j+L[2]; k < 50; k++)
			{
				temp = 0;
				for(l=0; l<N; l++)
				{
					if((A[l] <= k) && ((A[l] + D[l]) >= k + L[0]))
					{
						temp += P[0];
					}
					else if((A[l] <= i) && ((A[l] + D[l]) >= i + L[1]))
					{
						temp += P[1];
					}
					else if((A[l] <= j) && ((A[l] + D[l]) >= j + L[2]))
					{
						temp += P[2];
					}
				}
				if(temp > totalpoint)
				{
					totalpoint = temp;
				}
			}
		}
	}

	//201
	for(i=0; i < 50; i++)
	{
		for(j=i+L[2]; j < 50; j++)
		{
			for(k=j+L[0]; k < 50; k++)
			{
				temp = 0;
				for(l=0; l<N; l++)
				{
					if((A[l] <= j) && ((A[l] + D[l]) >= j + L[0]))
					{
						temp += P[0];
					}
					else if((A[l] <= k) && ((A[l] + D[l]) >= k + L[1]))
					{
						temp += P[1];
					}
					else if((A[l] <= i) && ((A[l] + D[l]) >= i + L[2]))
					{
						temp += P[2];
					}
				}
				if(temp > totalpoint)
				{
					totalpoint = temp;
				}
			}
		}
	}

	//210
	for(i=0; i < 50; i++)
	{
		for(j=i+L[2]; j < 50; j++)
		{
			for(k=j+L[1]; k < 50; k++)
			{
				temp = 0;
				for(l=0; l<N; l++)
				{
					if((A[l] <= k) && ((A[l] + D[l]) >= k + L[0]))
					{
						temp += P[0];
					}
					else if((A[l] <= j) && ((A[l] + D[l]) >= j + L[1]))
					{
						temp += P[1];
					}
					else if((A[l] <= i) && ((A[l] + D[l]) >= i + L[2]))
					{
						temp += P[2];
					}
				}
				if(temp > totalpoint)
				{
					totalpoint = temp;
				}
			}
		}
	}

	//write output
	printf("%d\n", totalpoint);
}
