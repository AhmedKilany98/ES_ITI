/*****************************************/
/**  File    : Admin.h	                 */
/**  Author  : Ahmed Kilany              */
/**  Date    : Nov 24, 2022              */
/**  Version : V00                       */
/*****************************************/

#ifndef ADMIN_H_
#define ADMIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "Account.h"

/**----------------------------- Admin Structure Details -------------------------------**/

#define UserNameSize	15
#define PasswordSize	15

typedef struct {
	uint8_t Username[UserNameSize+1];
	uint8_t Password[PasswordSize+1];
}Admin_t;

/**----------------------------- Public Admin to Admin APIs -------------------------------------**/
uint8_t Adm_Login(void);

/**----------------------------- Public Admin To Account APIs -------------------------------------**/
void Adm_CreateNewAccount(void);

void Adm_OpenExistingAccount(void);

void Adm_ExitSystem(void);


#endif /* ADMIN_H_ */
