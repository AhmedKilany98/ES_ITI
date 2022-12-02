/*****************************************/
/**  File    : Client.c	                 */
/**  Author  : Ahmed Kilany              */
/**  Date    : Nov 24, 2022              */
/**  Version : V00                       */
/*****************************************/

#include <ctype.h>
#include "Account.h"
#include "Client.h"

/**---------- Public Client APIs ----------**/
void Clt_ClientOperation(void)
{
	char AccountID[10], password[15], flag = 0;

	printf("--------- Welcome to Client Operation ----------\n");
	/** Enter Account Bank ID */
	while (1)
	{
		flag = 0x0F;
		printf("Please Enter Account ID: ");
		setbuf(stdout, NULL);
		scanf(" %s", AccountID);
		fflush(stdin);
		for (uint8_t i = 0; i < AccountIDSize; i++)
		{
			if ((isdigit(AccountID[i]) == 0)
					|| (strlen(AccountID) != AccountIDSize))
			{
				printf("Please Enter Valid Account ID.\n");
				printf("size:%llu. size must equal 10 char\n",
						strlen(AccountID));
				flag = 0xF0;
				break;
			}
		}
		if (flag == 0x0F)
		{
			break;
		}
	}

	/** Check if Account Exist or not */
	Account_t *ptr_Account = ACC_GetAccount(AccountID);

	if (ptr_Account != NULL)
	{
		if (ptr_Account->AccountStatus == ACTIVE)
		{
			for (uint8_t i = 1; i <= 3; i++)
			{
				/** Validate Password*/
				while (1)
				{
					printf("Please Enter Account Password: ");
					setbuf(stdout, NULL);
					scanf(" %[^\n]%*c", password);
					fflush(stdin);

					if (strlen(password) < 8 && strlen(password) > PasswordSize)
					{
						printf("Please Enter Valid Password.\n");
						printf("size:%llu. size must be [8-15] char\n",
								strlen(password));
						flag = 0xF0;
						break;
					}
					else
					{
						break;
					}
				}

				/** compare between Account Password and entered password*/

				if (strcmp(ptr_Account->Password, password) == 0)
				{
					uint8_t ch = 0;
					while (1)
					{
						printf("1-Make Transaction.\n");
						printf("2-Change Account Password.\n");
						printf("3-Get Cash.\n");
						printf("4-Deposit In Account.\n");
						printf("5-Return to Main Menu.\n");
						printf("Your Choice: ");
						scanf(" %d", &ch);
						fflush(stdin);

						if (ch == 1)
						{
							ACC_MakeTransaction(ptr_Account);
						}
						else if (ch == 2)
						{
							ACC_ChangePassword(ptr_Account);
						}
						else if (ch == 3)
						{
							ACC_GetCash(ptr_Account);
						}
						else if (ch == 4)
						{
							ACC_DepositIn(ptr_Account);
						}
						else if (ch == 5)
						{
//							break;
							return;
						}
						else
						{
							printf("Please Enter Valid Choice.\n");
						}
					}
				}
				else
				{
					printf("Sorry Wrong password.\n");
					printf("you have %d tries before Restricted your Account.\n",
							3 - i);
					if ((3 - i) == 0)
					{
						ptr_Account->AccountStatus = RESTRICTED;
					}
				}
			}
		}
		else
		{
			printf("Sorry You can't do any operation on this account.\n");
			printf("Please Go To Bank Office.\n");
		}
	}
	else
	{
		printf("Sorry Your Account ID not Exist.\n");
	}
}


