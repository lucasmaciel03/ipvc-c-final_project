#ifndef ROLE_AGENT_H
#define ROLE_AGENT_H

#include "../auth/users/user.h"

typedef enum {
    FINALIZADA, // 0
    AGENDADA, // 1
    NAO_COMPARECEU // 2
} VisitStatus;

typedef enum {
    POR_ANUNCIO,
    POR_CASA_ABERTA
} VisitType;

typedef struct Visit {
    char agentUsername[20];
    char date[11];
    char time[6];
    int propertyId;
    char clientUsername[20];
    VisitStatus status;
    VisitType tipo;
    struct Visit* next;
    struct Visit* prev;
} Visit;

typedef struct VisitList {
    Visit* head;
    Visit* tail;
} VisitList;


void listClientsAlphabetically(const User* user);

void searchClientByNIF(const User* user);
void scheduleVisit(VisitList* visitList, const User* user);
void saveVisitsToFile(VisitList* visitList);
void initVisitList(VisitList* visitList);
void loadVisitsFromFile(VisitList* visitList);
void listVisits(VisitList* visitList, const User* user);
void listVisitsByClient(VisitList* visitList, const User* user);
void listVisitsByPropertyType(VisitList* visitList, const User* user);
void simulateVisit(VisitList* visitList, const User* user);
void listNoShowVisits(VisitList* visitList, const User* user);
void calculateRevenue(VisitList* visitList, const User* user);
void totalVisitsByAgent(VisitList* visitList, const User* user);
void generateFinancialReport(VisitList* visitList, const User* user);
#endif