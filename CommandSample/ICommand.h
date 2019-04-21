
#ifndef ICOMMAND_H
#define ICOMMAND_H

typedef struct ICommand ICommand;

struct ICommand
{
    void *pImplicit;

    void (* Execute)(ICommand *pCommand);

    void (* Free)(ICommand **ppCommand);
};

#endif // !ICOMMAND_H
