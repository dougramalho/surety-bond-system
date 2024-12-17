#ifndef MENU_H
#define MENU_H

#include "globals.h"

// Menu display functions
void showMainMenu();
void showPolicyholderMenu();
void showContractMenu();
void showEndorsementMenu();

// Menu process functions
void processPolicyholderMenu();
void processContractMenu();
void processEndorsementMenu();
void processReportsMenu();

// Input/Output functions
void inputPolicyholder(Policyholder& policyholder);
void displayPolicyholder(const Policyholder& policyholder);
void inputContract(Contract& contract);
void displayContract(const Contract& contract);
void inputEndorsement(Endorsement& endorsement);
void displayEndorsement(const Endorsement& endorsement);

void showReportsMenu();
void reportActiveContracts();
void reportPremiumByPolicyholder();
void reportEndorsementsHistory();

#endif