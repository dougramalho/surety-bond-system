#ifndef BUSINESS_H
#define BUSINESS_H

#include "globals.h"

// Error handling functions
void setLastError(const char* error);
const char* getLastError();

// Validation functions
bool validateDocumentNumber(const char* docNumber);
bool validateContractDates(time_t startDate, time_t endDate);
bool validateContractValue(double value);
bool validateEndorsement(const Contract& contract, const Endorsement& endorsement);

// Business logic functions
double calculatePremium(const Contract& contract);
void generatePolicyNumber(char* policyNumber, int contractNumber);

// Database functions declarations needed by business logic
Coverage* findCoverage(int id);

#endif