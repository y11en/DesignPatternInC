
/*include*/typedef struct IDepartment IDepartment;

#ifndef IEMPLOYEE_H
#define IEMPLOYEE_H

typedef struct IEmployee IEmployee;

struct IEmployee
{
    void *pImplicit;

    void (* Accept)(IEmployee *pEmployee, IDepartment *pDepart);

    void (* Free)(IEmployee **ppEmployee);
};

#endif // !IEMPLOYEE_H
