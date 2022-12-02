/*****************************************/
/**  File    : Account.h                 */
/**  Author  : Ahmed Kilany              */
/**  Date    : Nov 24, 2022              */
/**  Version : V00                       */
/*****************************************/

#ifndef ACCOUNT_H_
#define ACCOUNT_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/**----------------------------- Account Structure Details -------------------------------**/


#define NumberAccounts	20
#define FullNameSize 60
#define FullAddressSize 50
#define NationalIDSize 14
#define AccountIDSize 10
#define GuardianNameSize 30
#define PasswordSize 15

typedef enum
{
	ACTIVE = 0X11, RESTRICTED = 0x55, CLOSED = 0xAA
} AccountSatus_t;

typedef struct
{
	uint8_t FullName[FullNameSize + 1];
	uint8_t FullAddress[FullAddressSize + 1];
	uint8_t NationalID[NationalIDSize + 1];
	uint8_t AccountID[AccountIDSize + 1];
	uint8_t GuardianName[GuardianNameSize + 1];
	uint8_t GuardianNationalID[NationalIDSize + 1];
	AccountSatus_t AccountStatus;
	uint8_t Password[PasswordSize + 1];
	int32_t Balance;
	uint8_t Age;
} Account_t;

typedef struct Account_t* Accountptr_t;

/**----------------------------- Public Accounts APIs -------------------------------------**/
void ACC_AddAccount(Account_t *ptr_Account);
void ACC_PrintAccount(Account_t *ptr_Account ,uint8_t AdminClientState);
Account_t* ACC_GetAccount(char* ptr_AccountID);

/**----------------------------- Public Account Operation APIs -------------------------------------**/
void ACC_MakeTransaction(Account_t*ptr_Account);
void ACC_GetCash(Account_t *ptr_AccountTx);
void ACC_ChangeStatus(Account_t *ptr_AccountTx);
void ACC_ChangePassword(Account_t *ptr_AccountTx);
void ACC_DepositIn(Account_t *ptr_Account);

/**----------------------------- Private Account_t APIs -------------------------------------**/

//static void ACC_GenAccountID(Account_t *ptr_Account);
static void ACC_GenAccountID(Account_t *ptr_Account);
static void ACC_GenAccountPassword(Account_t *ptr_Account);

#endif /* ACCOUNT_H_ */
