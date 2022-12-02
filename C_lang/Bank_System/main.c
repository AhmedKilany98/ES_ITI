/*****************************************/
/**  File    : main.c	                 */
/**  Author  : Ahmed Kilany              */
/**  Date    : Nov 24, 2022              */
/**  Version : V00                       */
/*****************************************/

#include <stdio.h>
#include <string.h>
#include "Admin.h"
#include "Client.h"

int main()
{
	char ch = 0;
	setbuf(stdout, NULL);
	while (1)
	{
		printf("------------------- Hello in ITI Bank System ----------------\n");
		printf("1-Admin\n");
		printf("2-Client\n");
		printf("3-Exit\n");
		printf("Your Choice: ");
		scanf(" %d", &ch);
		fflush(stdin);
		if(ch == 1)			 /** Admin */
		{
			if (Adm_Login() == 1)
			{
				while (1)
				{
					printf("----------- Welcome in Admin Window --------------------\n");
					printf("1-Add New Account\n");
					printf("2-Open Existing Account\n");
					printf("3-Exit\n");
					printf("Your Choice: ");
					scanf(" %d", &ch);
					fflush(stdin);
					if(ch == 1)			/** Admin Create New Account */
					{
						Adm_CreateNewAccount();
					}
					else if(ch == 2)	/** Admin Open Exist Account*/
					{
						Adm_OpenExistingAccount();
					}
					else 				/** Admin close System*/
					{
//						Adm_ExitSystem();
						break;
					}
				}
			}
			else
			{
				/** Handle Error Login */
			}
		}
		else if (ch == 2)			 /** User/Client*/
		{
			Clt_ClientOperation();
		}
		else 		/** Close System */
		{
			exit(0);
		}
	}

	return 0;
}
