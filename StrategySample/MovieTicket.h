
#include <apr_pools.h>
#include "IDiscount.h"


#ifndef MOVIETICKET_H
#define MOVIETICKET_H

typedef struct MovieTicket_Fld MovieTicket_Fld;
typedef struct MovieTicket MovieTicket;

struct MovieTicket
{
	MovieTicket_Fld *pFld;

	void (* SetDiscount)(MovieTicket *pInst, IDiscount *pDiscount);
	double (* GetPrice)(MovieTicket *pInst);
	void (* SetPrice)(MovieTicket *pInst, double dblPrice);
};

MovieTicket *MovieTicket_New(apr_pool_t *pSupPool);
void MovieTicket_Free(MovieTicket **ppInst);

#endif // !MOVIETICKET_H
