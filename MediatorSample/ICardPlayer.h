
/*include*/typedef struct Mediator Mediator;


#ifndef ICARDPLAYER_H
#define ICARDPLAYER_H

typedef struct ICardPlayer ICardPlayer;

struct ICardPlayer
{
    void *pImplicit;

    double (* GetMoney)(ICardPlayer *pCardPlayer);
    void (* SetMoney)(ICardPlayer *pCardPlayer, double dblMoney);
    void (* ChangeMoney)(ICardPlayer *pCardPlayer, double dblMoney, Mediator *pMediator);

    void (* Free)(ICardPlayer **ppCardPlayer);
};

#endif // !ICARDPLAYER_H
