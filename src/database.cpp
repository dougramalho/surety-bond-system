#include <iostream>
#include <iomanip>
#include "database.h"
#include "business.h"

bool savePolicyholder(const Policyholder& policyholder) {
    // Verifica se já existe um tomador com mesmo documento
    for(size_t i = 0; i < g_policyholders.size(); i++) {
        if(strcmp(g_policyholders[i].documentNumber, policyholder.documentNumber) == 0) {
            setLastError("Document number already exists");
            return false;
        }
    }
    
    g_policyholders.push_back(policyholder);
    return true;
}

bool saveContract(const Contract& contract) {
    // Validações básicas
    if(!validateContractValue(contract.contractValue)) {
        return false;
    }
    
    if(!validateContractDates(contract.startDate, contract.endDate)) {
        return false;
    }
    
    // Verifica se tomador existe
    bool policyholderFound = false;
    for(size_t i = 0; i < g_policyholders.size(); i++) {
        if(g_policyholders[i].id == contract.policyHolderId) {
            policyholderFound = true;
            break;
        }
    }
    
    if(!policyholderFound) {
        setLastError("Policyholder not found");
        return false;
    }
    
    g_contracts.push_back(contract);
    return true;
}

bool saveEndorsement(const Endorsement& endorsement) {
    // Procura o contrato
    Contract* contract = findContract(endorsement.contractNumber);
    if(!contract) {
        setLastError("Contract not found");
        return false;
    }
    
    // Valida o endosso
    if(!validateEndorsement(*contract, endorsement)) {
        return false;
    }
    
    g_endorsements.push_back(endorsement);
    
    // Atualiza o contrato se necessário
    if(endorsement.type == 'I') {  // Increase
        contract->contractValue += endorsement.changeValue;
    } else if(endorsement.type == 'D') {  // Decrease
        contract->contractValue -= endorsement.changeValue;
    } else if(endorsement.type == 'C') {  // Cancel
        contract->active = false;
    }
    
    return true;
}

Policyholder* findPolicyholder(int id) {
    for(size_t i = 0; i < g_policyholders.size(); i++) {
        if(g_policyholders[i].id == id) {
            return &g_policyholders[i];
        }
    }
    return NULL;  // Retorno NULL típico de código legado
}

Contract* findContract(int number) {
    for(size_t i = 0; i < g_contracts.size(); i++) {
        if(g_contracts[i].number == number) {
            return &g_contracts[i];
        }
    }
    return NULL;
}

Coverage* findCoverage(int id) {
    for(size_t i = 0; i < g_coverages.size(); i++) {
        if(g_coverages[i].id == id) {
            return &g_coverages[i];
        }
    }
    return NULL;
}

void listPolicyholders() {
    std::cout << "\n=== Policyholders List ===" << std::endl;
    std::cout << std::setw(5) << "ID" << " | "
              << std::setw(40) << "Name" << " | "
              << std::setw(15) << "Document" << " | "
              << "Status" << std::endl;
    std::cout << std::string(80, '-') << std::endl;
    
    for(size_t i = 0; i < g_policyholders.size(); i++) {
        std::cout << std::setw(5) << g_policyholders[i].id << " | "
                  << std::setw(40) << g_policyholders[i].name << " | "
                  << std::setw(15) << g_policyholders[i].documentNumber << " | "
                  << (g_policyholders[i].active ? "Active" : "Inactive") << std::endl;
    }
}

void listContracts() {
    std::cout << "\n=== Contracts List ===" << std::endl;
    std::cout << std::setw(8) << "Number" << " | "
              << std::setw(15) << "Policy" << " | "
              << std::setw(10) << "Value" << " | "
              << "Status" << std::endl;
    std::cout << std::string(80, '-') << std::endl;
    
    for(size_t i = 0; i < g_contracts.size(); i++) {
        std::cout << std::setw(8) << g_contracts[i].number << " | "
                  << std::setw(15) << g_contracts[i].policyNumber << " | "
                  << std::setw(10) << g_contracts[i].contractValue << " | "
                  << (g_contracts[i].active ? "Active" : "Inactive") << std::endl;
    }
}

void listEndorsements(int contractNumber) {
    std::cout << "\n=== Endorsements for Contract " << contractNumber << " ===" << std::endl;
    std::cout << std::setw(8) << "Number" << " | "
              << std::setw(10) << "Type" << " | "
              << std::setw(10) << "Value" << " | "
              << "Date" << std::endl;
    std::cout << std::string(80, '-') << std::endl;
    
    for(size_t i = 0; i < g_endorsements.size(); i++) {
        if(g_endorsements[i].contractNumber == contractNumber) {
            char typeDesc[20];
            switch(g_endorsements[i].type) {
                case 'I': strcpy(typeDesc, "Increase"); break;
                case 'D': strcpy(typeDesc, "Decrease"); break;
                case 'C': strcpy(typeDesc, "Cancel"); break;
                default: strcpy(typeDesc, "Unknown");
            }
            
            std::cout << std::setw(8) << g_endorsements[i].number << " | "
                      << std::setw(10) << typeDesc << " | "
                      << std::setw(10) << g_endorsements[i].changeValue << " | "
                      << ctime(&g_endorsements[i].endorsementDate);
        }
    }
}