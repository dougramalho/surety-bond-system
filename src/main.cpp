#include <iostream>
#include "globals.h"
#include "menu.h"
#include "business.h"
#include "database.h"

// Inicialização das variáveis globais
std::vector<Policyholder> g_policyholders;
std::vector<Coverage> g_coverages;
std::vector<Contract> g_contracts;
std::vector<Endorsement> g_endorsements;
char g_lastError[200];

void initializeSystem() {
    // Inicializa cobertura padrão (comum em sistemas legados ter dados hard-coded)
    Coverage defaultCoverage;
    defaultCoverage.id = 1;
    strcpy(defaultCoverage.name, "Performance Bond");
    strcpy(defaultCoverage.description, "Default performance bond coverage");
    defaultCoverage.maxValue = 1000000.0;
    defaultCoverage.premiumRate = 0.02;
    defaultCoverage.active = true;
    g_coverages.push_back(defaultCoverage);

    defaultCoverage.id = 2;
    strcpy(defaultCoverage.name, "Bid Bond");
    strcpy(defaultCoverage.description, "Default bid bond coverage");
    defaultCoverage.maxValue = 500000.0;
    defaultCoverage.premiumRate = 0.015;
    defaultCoverage.active = true;
    g_coverages.push_back(defaultCoverage);
}

int main() {
    initializeSystem();
    
    while(1) {
        showMainMenu();
        int choice;
        std::cin >> choice;
        
        switch(choice) {
            case 1:
                processPolicyholderMenu();
                break;
            case 2:
                processContractMenu();
                break;
            case 3:
                processEndorsementMenu();
                break;
            case 4:
                processReportsMenu();
                break;
            case 0:
                std::cout << "Exiting system..." << std::endl;
                return 0;
            default:
                std::cout << "Invalid option!" << std::endl;
        }
    }
    
    return 0;
}