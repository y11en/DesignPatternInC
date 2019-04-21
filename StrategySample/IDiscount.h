
#ifndef IDISCOUNT_H
#define IDISCOUNT_H

typedef struct IDiscount IDiscount;

struct IDiscount
{
	void *pImplicit;

	double (* Calculate)(IDiscount *pDiscount, double dblPrice);

	void (* Free)(IDiscount **ppDiscount);
};

#endif // !IDISCOUNT_H
