
/*include*/typedef struct EmployeeFulltime EmployeeFulltime;
/*include*/typedef struct EmployeePartTime EmployeePartTime;

#ifndef IDEPARTMENT_H
#define IDEPARTMENT_H

typedef struct IDepartment IDepartment;

struct IDepartment
{
    void *pImplicit;

    void (* VisitFulltimeEmployee)(IDepartment *pDepart, EmployeeFulltime *pFulltimeEmployee);
    void (* VisitPartTimeEmployee)(IDepartment *pDepart, EmployeePartTime *pPartTimeEmployee);

    void (* Free)(IDepartment **ppDepart);
};

#endif // !IDEPARTMENT_H
