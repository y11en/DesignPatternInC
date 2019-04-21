
#include <stdio.h>
#include "Actor.h"

int main(int argc, char **argv)
{
    Actor *actor = Actor_New();

    actor->SetRole(actor, ROLE_ANGLE);
    actor->SetGender(actor, GENDER_WOMAN);
    actor->SetFace(actor, "Beautiful face ^_^");
    actor->SetCostume(actor, "Classic");
    actor->SetHairStyle(actor, "Long hair");

    printf("RoleType: %d\n", actor->GetRole(actor));
    printf("Gender: %s\n", (actor->GetGender(actor) == GENDER_WOMAN ? "woman" : "man"));
    char strFace[100];
    printf("Face: %s\n", actor->GetFace(actor, &strFace[0]));
    char strCostume[100];
    printf("Costume: %s\n", actor->GetCostume(actor, &strCostume[0]));
    char strHairStyle[100];
    printf("HairStyle: %s\n", actor->GetHairStyle(actor, &strHairStyle[0]));

    actor->SayLines();
    actor->Act(actor);

    Actor_Free(&actor);

    return 0;
}