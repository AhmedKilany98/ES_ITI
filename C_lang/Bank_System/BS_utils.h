/*****************************************/
/**  File    : BS_utils.h                */
/**  Author  : Ahmed Kilany              */
/**  Date    : Nov 24, 2022              */
/**  Version : V00                       */
/*****************************************/

#ifndef BS_UTILS_H_
#define BS_UTILS_H_


uint64_t Power(uint32_t base, uint8_t exponent)
{
	uint64_t ret=1;
	while(exponent)
	{
		ret *= base;
		exponent --;
	}
	return ret;
}


void HashFunction(uint8_t *text , uint8_t* rtext)
{
	uint8_t i=0 ;
	uint64_t hash=text[i];
	while(text[i] !='\0')
	{
		hash = ((hash +text[i])* Power(31,i))%(10000000009);
		i++;
	}
	sprintf(rtext,"%llu",hash);

}


#endif /* BS_UTILS_H_ */
