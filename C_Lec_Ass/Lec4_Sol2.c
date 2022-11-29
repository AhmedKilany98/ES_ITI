#include <stdio.h>
#include <stdlib.h>
/** Lec 4 Ass 2 */

/** Add two numbers */
void Add(float a,float b)
{
	printf("%f + %f = %f\n",a,b,a+b);
}
/** Subract two numbers */
void Sub(float a,float b)
{
	printf("%f - %f = %f\n",a,b,a-b);
}
/** Multiply two numbers */
void Mul(float a,float b)
{
	printf("%f x %f = %f\n",a,b,a*b);
}
/** Divide two numbers */
void Div(float a,float b)
{
	if(b != 0)
	{
		printf("%f / %f = %f\n",a,b,a/b);
	}
	else 
	{
		printf("Invalid Value can't divide on 0 \n");
	}

}
/** Reminder two numbers */
void Rem(int a,int b)
{
	printf("%d %c %d = %d\n",a,'%',b,a%b);
}
/** And two numbers */
void And(int a,int b)
{
	printf("%d and %d = %d\n",a,b,a&b);
}
/** Or two numbers */
void Or(int a,int b)
{
	printf("%d or %d = %d\n",a,b,a|b);
}
/** Not one numbers */
void Not(int a)
{
	printf("not %d = %d\n",a,~a);
	printf("not %x = %x\n",a,~a);
}
/** Xor two numbers */
void Xor(int a,int b)
{
	printf("%d xor %d = %d\n",a,b,a^b);
}
/** Increment one number */
void Inc(int a)
{
	printf("Inc %d =",a);
	printf(" %d\n",++a);
}
/** Decrement one numbers */
void Dec(int a)
{
	printf("Dec %d =",a);
	printf(" %d\n",--a);
}

/** Calculator */
void Calc(void)
{
	int num1,num2,opt;
	printf("Please Enter operation ID: ");
	scanf(" %d",&opt);
	printf("\n");
	switch(opt)
	{
		case 1:
			printf("Please Enter Number1: ");scanf(" %d",&num1);
			printf("Please Enter Number2: ");scanf(" %d",&num2);
			Add(num1,num2);
		break;
		
		case 2:
			printf("Please Enter Number1: ");scanf(" %d",&num1);
			printf("Please Enter Number2: ");scanf(" %d",&num2);
			Sub(num1,num2);
		break;
		
		case 3:
			printf("Please Enter Number1: ");scanf(" %d",&num1);
			printf("Please Enter Number2: ");scanf(" %d",&num2);
			Mul(num1,num2);
		break;
		
		case 4:
			printf("Please Enter Number1: ");scanf(" %d",&num1);
			printf("Please Enter Number2: ");scanf(" %d",&num2);
			Div(num1,num2);
		break;
		
		case 5:
			printf("Please Enter Number1: ");scanf(" %d",&num1);
			printf("Please Enter Number2: ");scanf(" %d",&num2);
			And(num1,num2);
		break;
		
		case 6:
			printf("Please Enter Number1: ");scanf(" %d",&num1);
			printf("Please Enter Number2: ");scanf(" %d",&num2);
			Or(num1,num2);
		break;
		
		case 7:
			printf("Please Enter Number1: ");scanf(" %d",&num1);
			Not(num1);
		break;
		
		case 8:
			printf("Please Enter Number1: ");scanf(" %d",&num1);
			printf("Please Enter Number2: ");scanf(" %d",&num2);
			Xor(num1,num2);
		break;
		
		case 9:
			printf("Please Enter Number1: ");scanf(" %d",&num1);
			printf("Please Enter Number2: ");scanf(" %d",&num2);
			Rem(num1,num2);
		break;
		
		case 10:
			printf("Please Enter Number1: ");scanf(" %d",&num1);
			Inc(num1);
		break;
		
		case 11:
			printf("Please Enter Number1: ");scanf(" %d",&num1);
			Dec(num1);
		break;
		
		case 12:
		exit(0);
		break;
	}
}

 int main()
{
	while(1)
	{
		printf("----------------------------------------------\n");
		printf("Main Menu...\n");
		printf("1-Add\n2-Subtract\n3-Multiply\
		\n4-Divide\n5-And\n6-Or\n7-Not\n8-Xor\
		\n9-reminder\n10-Increment\n11-Decrement\n12-Exit\n");
	
		Calc();
	}
	
	return 0;
}
