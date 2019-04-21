
#ifndef ICOMPONENT_H
#define ICOMPONENT_H

typedef struct IComponent IComponent;

struct IComponent
{
    void *pImplicit;

    void (* Display)(IComponent *pComponent);

    void (* Free)(IComponent **ppComponent);
};

#endif // !ICOMPONENT_H
