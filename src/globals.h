#ifndef GLOBALS_H
#define GLOBALS_H

#include <vector>
#include <string.h>
#include <time.h>

// Constant definitions
#define MAX_NAME_LENGTH 100
#define MAX_DOC_LENGTH 20
#define MAX_COVERAGES 10
#define MIN_CONTRACT_VALUE 1000.0
#define MAX_CONTRACT_VALUE 10000000.0
#define DEFAULT_PREMIUM_RATE 0.02

// Basic structures
struct Address {
    char street[100];
    char number[20];
    char city[50];
    char state[2];
    char zipCode[10];
};

struct Policyholder {
    int id;
    char name[MAX_NAME_LENGTH];
    char documentNumber[MAX_DOC_LENGTH];
    Address address;
    char phone[15];
    bool active;
    time_t registrationDate;
};

struct Coverage {
    int id;
    char name[50];
    char description[200];
    double maxValue;
    double premiumRate;
    bool active;
};

struct Contract {
    int number;
    char policyNumber[20];
    int policyHolderId;
    time_t startDate;
    time_t endDate;
    double contractValue;
    double premium;
    bool active;
    int coverageIds[MAX_COVERAGES];
    int coverageCount;
    time_t issueDate;
};

struct Endorsement {
    int number;
    int contractNumber;
    time_t endorsementDate;
    char type;  // 'I'=Increase, 'D'=Decrease, 'C'=Cancel
    double changeValue;
    char description[200];
};

// Global variables declarations
extern std::vector<Policyholder> g_policyholders;
extern std::vector<Coverage> g_coverages;
extern std::vector<Contract> g_contracts;
extern std::vector<Endorsement> g_endorsements;
extern char g_lastError[200];

#endif