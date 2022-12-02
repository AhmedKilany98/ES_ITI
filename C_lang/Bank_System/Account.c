/*****************************************/
/**  File    : Account.h                 */
/**  Author  : Ahmed Kilany              */
/**  Date    : Nov 24, 2022              */
/**  Version : V00                       */
/*****************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

#include "Account.h"
#include "BS_utils.h"

static Account_t AccountDB[NumberAccounts + 1];
static uint8_t AccountDBsz = 0;

/**----------------------------- Public Accounts APIs -------------------------------------**/


void ACC_AddAccount(Account_t *ptr_Account)
{
	/** Set Account Full Name */
	strncpy((char*) (AccountDB + AccountDBsz)->FullName,
			(char*) ptr_Account->FullName,
			FullNameSize);

	/** Generate Account ID */
	ACC_GenAccountID(ptr_Account);

	/** Set Account ID*/
	strncpy((char*) (AccountDB + AccountDBsz)->AccountID,
			(char*) ptr_Account->AccountID, AccountIDSize);

	/** Set Account Full Address */
	strncpy((char*) (AccountDB + AccountDBsz)->FullAddress,
			(char*) ptr_Account->FullAddress,
			FullAddressSize);

	/** Set Account National ID */
	strncpy((char*) (AccountDB + AccountDBsz)->NationalID,
			(char*) ptr_Account->NationalID,
			NationalIDSize);

	/** Generate Default Account Password */
	ACC_GenAccountPassword(ptr_Account);

	/** Set Account Password */
	strncpy((char*) (AccountDB + AccountDBsz)->Password,
			(char*) ptr_Account->Password,
			PasswordSize);

	/** Set Account Age */
	(AccountDB + AccountDBsz)->Age = ptr_Account->Age;

	/** Set Account Status */
	(AccountDB + AccountDBsz)->AccountStatus = ptr_Account->AccountStatus;

	/** Set Account Balance */
	(AccountDB + AccountDBsz)->Balance = ptr_Account->Balance;

	if (ptr_Account->Age < 21)
	{
		/** Set Guardian Name*/
		strncpy((char*) (AccountDB + AccountDBsz)->GuardianName,
				(char*) ptr_Account->GuardianName,
				GuardianNameSize);

		/** Set Guardian National ID */
		strncpy((char*) (AccountDB + AccountDBsz)->GuardianNationalID,
				(char*) ptr_Account->GuardianNationalID,
				GuardianNameSize);
	}

	ACC_PrintAccount(AccountDB + AccountDBsz, 1);

	AccountDBsz++;
}


void ACC_PrintAccount(Account_t *ptr_Account, uint8_t AdminClientState)
{
	printf(
			"--------------------- Account Details --------------------------\n");
	printf("Account Full Name           :%s\n", ptr_Account->FullName);
	printf("Account Full Address        :%s\n", ptr_Account->FullAddress);
	printf("Account ID                  :%s\n", ptr_Account->AccountID);

	if (ptr_Account->AccountStatus == ACTIVE)
	{
		printf("Account Status              :ACTIVE\n");
	}
	else if (ptr_Account->AccountStatus == RESTRICTED)
	{
		printf("Account Status              :RESTRICTED\n");
	}
	else
	{
		printf("Account Status              :CLOSED\n");
	}
	printf("Account National ID         :%s\n", ptr_Account->NationalID);

	if (AdminClientState == 1)
	{
		printf("Account Password            :%s\n", ptr_Account->Password);
	}
	else
	{
		printf("Account Password            :");
		for (uint8_t i = 0; i < PasswordSize; i++)
		{
			printf("*");
		}
		printf("\n");
	}

	printf("Account Balance             :%d\n", ptr_Account->Balance);

	printf("Account Age                 :%d\n", ptr_Account->Age);

	if (ptr_Account->Age < 21)
	{
		printf("Account Guardian Name       :%s\n", ptr_Account->GuardianName);
		printf("Account Guardian National ID:%s\n",
				ptr_Account->GuardianNationalID);
	}

	printf("-------------------------------------------------------------\n");
}


Account_t* ACC_GetAccount(char* ptr_AccountID)
{
	int i = 0, flag = 0x0F;
	for (i = 0; i < AccountDBsz; i++)
	{
		if (strcmp(AccountDB[i].AccountID, ptr_AccountID) == 0)
		{
			flag = 0xF0;
			break;
		}
	}
	if (flag == 0x0F)
		return NULL;
	return (AccountDB + i);
}


/**----------------------------- Private Account_t APIs -------------------------------------**/

/**
 *
 * @param ptr_Account
 */
static void ACC_GenAccountID(Account_t *ptr_Account)
{
	if (strcmp((char*) ptr_Account->FullName, (char*) "") != 0)
	{
		HashFunction(ptr_Account->FullName, ptr_Account->AccountID);
	}
	else
	{
		printf("Error Account ID: Please Enter Account Name First.");
	}
}

/**
 *
 * @param ptr_Account
 */
static void ACC_GenAccountPassword(Account_t *ptr_Account)
{
	if (strcmp((char*) ptr_Account->NationalID, (char*) "") != 0)
	{
		HashFunction(ptr_Account->NationalID, ptr_Account->Password);
	}
	else
	{
		printf("Error Account Password: Please Enter Account National ID First.");
	}
}

/**----------------------------- Public Account Operations APIs -------------------------------------**/

void ACC_MakeTransaction(Account_t *ptr_AccountTx)
{
	char AccountID[10] =
	{ 0 }, flag = 0;
	Account_t *ptr_AccountRx = NULL;
	uint32_t AmountMoney = 0;
	printf("--------- Welcome to Make Transaction Function ----------\n");

	/** Enter Receive Bank ID */
	if (ptr_AccountTx->AccountStatus == ACTIVE)
	{
		while (1)
		{
			flag = 0x0F;
			printf("Please Enter Receive Account ID: ");
			setbuf(stdout, NULL);
			scanf(" %s", AccountID);
			fflush(stdin);
			/** Handle Size of Account Id */
			if (strlen(AccountID) == AccountIDSize)
			{
				/** Handle to enter no transmit Account Id Again */
				if (strcmp(ptr_AccountTx->AccountID, AccountID) != 0)
				{
					for (uint8_t i = 0; i < AccountIDSize; i++)
					{
						if (isdigit(AccountID[i]) == 0)
						{
							printf("Please Enter Valid Account ID.\n");
							flag = 0xF0;
							break;
						}
					}
				}
				else
				{
					printf("please Enter Different transmit ID\n");
					flag = 0xF0;
				}
			}
			else
			{
				printf(
						"Please Enter valid size:%llu. size must equal 10 char\n",
						strlen(AccountID));
				flag = 0xF0;
			}
			if (flag == 0x0F)
			{
				break;
			}
		}

		/** Get Account info */
		ptr_AccountRx = ACC_GetAccount(AccountID);
		if (ptr_AccountRx != NULL)
		{
			printf("------- Account Transmit Before Changes -------\n");
			ACC_PrintAccount(ptr_AccountTx, 0);
			printf("------ Account Receive Before Changes -----\n");
			ACC_PrintAccount(ptr_AccountRx, 0);

			if (ptr_AccountRx->AccountStatus == ACTIVE)
			{
				/** Get Balance From User*/
				while (1)
				{
					flag = 1;

					printf("Please Enter Amount of Money:");
					setbuf(stdout, NULL);
					scanf(" %ld", &AmountMoney);
					fflush(stdin);
					if (AmountMoney <= 0)
					{
						printf("Please Enter Valid Value.\n");
						flag = 0;
					}
					if (flag == 1)
					{
						break;
					}
				}

				if (ptr_AccountTx->Balance > AmountMoney)
				{
					/** Add Amount of money to Receive Account */
					ptr_AccountRx->Balance += AmountMoney;
					/** subtract Amount of money for Transmit Account */
					ptr_AccountTx->Balance -= AmountMoney;

					printf("------- Account Transmit After Changes -------\n");
					ACC_PrintAccount(ptr_AccountTx, 0);
					printf("------ Account Receive After Changes -----\n");
					ACC_PrintAccount(ptr_AccountRx, 0);
				}
				else
				{
					printf("Sorry Your Transaction Refused\n");
					printf("Your Balance Account is not \"Enough\"\n");
				}
			}
			else
			{
				printf("Sorry Your Transaction Refused\n");
				printf("Your Receive Account State is not \"ACTIVE\"\n");
			}
		}
		else
		{
			printf("Sorry Your Transaction Refused\n");
			printf("Your Account ID is not \"Exist\"\n");
		}
	}
	else
	{
		printf("Sorry Your Transaction Refused\n");
		printf("Your Account State is not \"ACTIVE\"\n");
	}
}


void ACC_GetCash(Account_t *ptr_AccountTx)
{
	uint32_t AmountMoney = 0, flag = 0;
	printf("--------- Welcome to Get Cash Function ----------\n");

	while (1)
	{
		flag = 1;

		printf("Please Enter The Cash Amount of Money:");
		setbuf(stdout, NULL);
		scanf(" %ld", &AmountMoney);
		fflush(stdin);
		if (AmountMoney <= 0)
		{
			printf("Please Enter Valid Value.\n");
			flag = 0;
		}
		if (flag == 1)
		{
			break;
		}
	}

	ptr_AccountTx->Balance -= AmountMoney;
	printf("------- Account After Changes -------\n");
	ACC_PrintAccount(ptr_AccountTx, 0);
}


void ACC_ChangeStatus(Account_t *ptr_AccountTx)
{
	uint8_t state = 0;
	printf("--------- Welcome to Change Account State ---------------------\n");
	printf("1-Set Account to Active State\n");
	printf("2-Set Account to Restricted State\n");
	printf("3-Set Account to Closed State\n");
	while (1)
	{
		printf("Your Choice: ");
		scanf(" %d", &state);
		fflush(stdin);
		if (state == 1)
		{
			ptr_AccountTx->AccountStatus = ACTIVE;
			break;
		}
		else if (state == 2)
		{
			ptr_AccountTx->AccountStatus = RESTRICTED;
			break;
		}
		else if (state == 3)
		{
			ptr_AccountTx->AccountStatus = CLOSED;
			break;
		}
		else
		{
			printf("Please Enter Valid Choice.\n");
		}
	}
	printf("------------ Account After Changes -------------\n");
	ACC_PrintAccount(ptr_AccountTx, 0);
}


void ACC_DepositIn(Account_t *ptr_AccountTx)
{
	uint8_t flag = 0;
	uint32_t AmountMoney = 0;
	printf("------------ Welcome in Deposit function ------------\n");
	/** Get amount of money to Deposit in Account*/
	while (1)
	{
		flag = 1;

		printf("Please Enter Amount of Money:");
		setbuf(stdout, NULL);
		scanf(" %ld", &AmountMoney);
		fflush(stdin);
		if (AmountMoney <= 0)
		{
			printf("Please Enter Valid Value.\n");
			flag = 0;
		}
		if (flag == 1)
		{
			break;
		}
	}
	/** Add Amount of money to Account */
	ptr_AccountTx->Balance += AmountMoney;

	printf("------------ Account After Changes  -----------\n");
	ACC_PrintAccount(ptr_AccountTx, 0);
}


void ACC_ChangePassword(Account_t *ptr_AccountTx)
{
	char oldPassword[15], newPassword[15], flag = 0;

	printf("------- Welcome to Change Account Password Window ------\n");
	/** Enter Account Old Password */
	while (1)
	{
		printf("Please Enter Old Password: ");
		setbuf(stdout, NULL);
		scanf(" %[^\n]%*c", oldPassword);
		fflush(stdin);

		if (strlen(oldPassword) < 8 && strlen(oldPassword) > PasswordSize)
		{
			printf("Please Enter Valid Password.\n");
			printf("size:%llu. size must be [8-15] char\n",
					strlen(oldPassword));
		}
		else
		{
			break;
		}
	}

	/** check on Old Password is it or not */
	if (strcmp(ptr_AccountTx->Password, oldPassword) == 0)
	{
		while (1)
		{
			printf("Please Enter Account New Password: ");
			setbuf(stdout, NULL);
			scanf(" %[^\n]%*c", newPassword);
			fflush(stdin);

			if (strlen(newPassword) < 8 && strlen(newPassword) > PasswordSize)
			{
				printf("Please Enter Valid Password.\n");
				printf("size:%llu. size must be [8-15] char\n",
						strlen(newPassword));
			}
			else
			{
				break;
			}
		}
		strncpy(ptr_AccountTx->Password, newPassword, PasswordSize);
		printf("------------ Account After Changes -------------\n");
		ACC_PrintAccount(ptr_AccountTx, 1);
	}
	else
	{
		printf("Sorry Your Old password is Wrong.\n");
	}
}

