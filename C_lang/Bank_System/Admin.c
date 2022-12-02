/*****************************************/
/**  File    : Admin.c	                 */
/**  Author  : Ahmed Kilany              */
/**  Date    : Nov 24, 2022              */
/**  Version : V00                       */
/*****************************************/

#include <ctype.h>
#include "Account.h"
#include "Admin.h"


static Admin_t MasterAdmin =
{ .Username = "kilany", .Password = "1998" };


/**----------------------------- Public Admin to Admin APIs -------------------------------------**/

uint8_t Adm_Login(void)
{
//	return 1;
	Admin_t tmpAdmin;
	uint8_t iter = 3, ret = 0;
	do
	{
		printf("\nPlease Enter UserName:");
		setbuf(stdout, NULL);
		scanf(" %s", tmpAdmin.Username);
		fflush(stdin);
		if (strcmp((char*) MasterAdmin.Username, (char*) tmpAdmin.Username)
				!= 0)
		{
			printf("Invalid Input,Please Enter Correct Value.");
		}
		else
		{
			break;
		}
	} while (--iter);
	if (iter == 0)
	{
		printf("\nSorry You Enter An Invalid Value.");
		printf("\n bye bye");
		exit(0);
	}
	else
	{
		iter = 3;
		do
		{
			printf("Please Enter Password:");
			setbuf(stdout, NULL);
			scanf(" %s", tmpAdmin.Password);
			fflush(stdin);
			if (strcmp((char*) MasterAdmin.Password, (char*) tmpAdmin.Password)
					!= 0)
			{
				printf("Invalid Input,Please Enter Correct Value.");
			}
			else
			{
				ret = 1;
				break;
			}
		} while (--iter);
		if (iter == 0)
		{
			printf("\nSorry You Enter An Invalid Value.");
			printf("\n bye bye");
			exit(0);
		}
	}
	return ret;
}

/**----------------------------- Public Admin To Account APIs -------------------------------------**/

/**
 * Adm_CreateNewAccount
 * @return none
 */

void Adm_CreateNewAccount(void)
{
	Account_t* ptrAccount = calloc(1, sizeof(Account_t));
	char name[15] = "";
	char FullName[4][7] =
	{ "First", "Second", "Third", "Four" };
	uint8_t flag = 1;

	if (Adm_Login() == 1)
	{
		/** Get Full Name From User */
		for (uint8_t i = 0; i < 4; i++)
		{
			do
			{
				printf("Please Enter %6s Name :", FullName[i]);
				setbuf(stdout, NULL);
				scanf(" %s", name);
				fflush(stdin);
				for (uint8_t j = 0; j < strlen(name); j++)
				{
					if (isalpha(name[j]) == 0)
					{
						printf("Please Enter Valid Value.\n");
						flag = 0;
						break;
					}
				}
				if (flag == 1)
				{
					break;
				}
				flag = 1;
			} while (1);

			strcat((char*) (ptrAccount->FullName), name);
			if (i + 1 != 4)
				strcat((char*) (ptrAccount->FullName), (char*) " ");
			strcat(name, (char*) "");

		}

		/** Get Full Address from User */
		printf("Please Enter Full Address:");
		setbuf(stdout, NULL);
		scanf(" %[^\n]%*c", ptrAccount->FullAddress);
		fflush(stdin);

		/** Get Age from User */
		while (1)
		{
			printf("Please Enter Age:");
			setbuf(stdout, NULL);
			scanf("%u", (unsigned int*) &(ptrAccount->Age));
			fflush(stdin);
			if (ptrAccount->Age > 120)
			{
				printf("Please Enter Valid Value.\n");
			}
			else if (ptrAccount->Age >= 2 && ptrAccount->Age <= 120)
			{
				break;
			}
		}

		/** Get Guardian Name if Age is less than 21*/
		if ((ptrAccount->Age) < 21)
		{
			for (uint8_t i = 0; i < 2; i++)
			{
				do
				{
					flag = 1;
					printf("Please Enter Guardian %6s Name:",FullName[i]);
					scanf(" %s", name);
					fflush(stdin);
					for (uint8_t j = 0; j < strlen(name); j++)
					{
						if (isalpha(name[j]) == 0 || strlen(name) > 14)
						{
							printf("Please Enter Valid Value.\n");
							flag = 0;
							break;
						}
					}
					if (flag == 1)
					{
						break;
					}
				} while (1);

				strcat((char*) (ptrAccount->GuardianName), name);
				if (i == 0)
					strcat((char*) (ptrAccount->GuardianName), (char*) " ");
				strcat(name, (char*) "");
			}
		}
		/** Get Guardian National Id From User if Age is less than 21*/
		if ((ptrAccount->Age) < 21)
		{
			while (1)
			{
				flag = 1;
				printf("Please Enter Guardian National ID:");
				setbuf(stdout, NULL);
				scanf(" %s", (char*) ptrAccount->GuardianNationalID);
				fflush(stdin);
				for (uint8_t i = 0; i < NationalIDSize; i++)
				{
					if ((isdigit(ptrAccount->GuardianNationalID[i]) == 0)
							|| (strlen((char*) ptrAccount->GuardianNationalID)
									!= NationalIDSize))
					{
						printf("Please Enter Valid Value.\n");
						printf("size:%lu. size must equal 14 char\n",
								strlen((char*) ptrAccount->GuardianNationalID));
						flag = 0;
						break;
					}
				}
				if (flag == 1)
				{
//					strcat((char*) (ptrAccount->GuardianNationalID), name);
					break;
				}
			}
		}

		/** Get National Id From User*/

		while (1)
		{
			flag = 1;
			printf("Please Enter National ID:");
			setbuf(stdout, NULL);
			scanf(" %s", (char*) ptrAccount->NationalID);
			fflush(stdin);
			for (uint8_t i = 0; i < NationalIDSize; i++)
			{
				if ((isdigit(ptrAccount->NationalID[i]) == 0)
						|| (strlen((char*) ptrAccount->NationalID)
								!= NationalIDSize))
				{
					printf("Please Enter Valid Value.\n");
					printf("size:%lu. size must equal 14 char\n",
							strlen((char*) ptrAccount->NationalID));
					flag = 0;
					break;
				}
			}
			if (flag == 1)
			{
				break;
			}
		}

		/** Get Balance From User*/
		while (1)
		{
			flag = 1;
			printf("Please Enter Balance:");
			setbuf(stdout, NULL);
			scanf(" %ld", (long int *) &(ptrAccount->Balance));
			fflush(stdin);
			if (ptrAccount->Balance <= 0)
			{
				printf("Please Enter Valid Value.\n");
				flag = 0;
			}
			if (flag == 1)
			{
				break;
			}
		}

		ptrAccount->AccountStatus = ACTIVE;
		ACC_AddAccount(ptrAccount);
	}

}


/**
 * Adm_OpenExistingAccount
 * @return none
 */
void Adm_OpenExistingAccount(void)
{
	char AccountID[10] =
	{ 0 }, flag = 0;
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
		uint8_t ch = 0;
		while (1)
		{
			printf(
					"--------- Welcome to Existing Account Operation ----------\n");
			printf("1-Make Transaction.\n");
			printf("2-Change Account Status.\n");
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
				ACC_ChangeStatus(ptr_Account);
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
				 break;
//				return;
			}
			else
			{
				printf("Please Enter Valid Choice.\n");
			}
		}
	}
	else
	{
		printf("Sorry Your Account ID not Exist.\n");
	}
}


/**
 * @return none
 */
void Adm_ExitSystem(void)
{
	exit(0);
}


