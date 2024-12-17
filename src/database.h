// database.h
#ifndef DATABASE_H
#define DATABASE_H

#include "globals.h"

// Database operations
bool savePolicyholder(const Policyholder& policyholder);
bool saveContract(const Contract& contract);
bool saveEndorsement(const Endorsement& endorsement);
bool saveCoverage(const Coverage& coverage);

// Retrieval operations
Policyholder* findPolicyholder(int id);
Contract* findContract(int number);
Coverage* findCoverage(int id);

// List operations
void listPolicyholders();
void listContracts();
void listEndorsements(int contractNumber);

#endif