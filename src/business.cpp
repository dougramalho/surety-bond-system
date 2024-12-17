#include <iostream>
#include <string.h>
#include "business.h"

void setLastError(const char* error) {
    strncpy(g_lastError, error, sizeof(g_lastError) - 1);
    g_lastError[sizeof(g_lastError) - 1] = '\0';
}

const char* getLastError() {
    return g_lastError;
}

bool validateDocumentNumber(const char* docNumber) {
    // Validação simplificada de CNPJ
    int len = strlen(docNumber);
    if(len != 14) {
        setLastError("Document number must have 14 digits");
        return false;
    }
    
    // Verifica se são todos números
    for(int i = 0; i < len; i++) {
        if(docNumber[i] < '0' || docNumber[i] > '9') {
            setLastError("Document number must contain only digits");
            return false;
        }
    }
    
    return true;
}

bool validateContractDates(time_t startDate, time_t endDate) {
    // Verifica se a data final é posterior à data inicial
    if(endDate <= startDate) {
        setLastError("End date must be after start date");
        return false;
    }
    
    // Verifica se a data inicial não é passada
    time_t now;
    time(&now);
    if(startDate < now) {
        setLastError("Start date cannot be in the past");
        return false;
    }
    
    return true;
}

bool validateContractValue(double value) {
    if(value <= 0) {
        setLastError("Contract value must be positive");
        return false;
    }
    
    if(value < MIN_CONTRACT_VALUE) {
        setLastError("Contract value below minimum allowed");
        return false;
    }
    
    if(value > MAX_CONTRACT_VALUE) {
        setLastError("Contract value above maximum allowed");
        return false;
    }
    
    return true;
}

bool validateEndorsement(const Contract& contract, const Endorsement& endorsement) {
    if(!contract.active) {
        setLastError("Cannot endorse inactive contract");
        return false;
    }
    
    switch(endorsement.type) {
        case 'I':  // Increase
            if(contract.contractValue + endorsement.changeValue > MAX_CONTRACT_VALUE) {
                setLastError("Endorsement would exceed maximum contract value");
                return false;
            }
            break;
            
        case 'D':  // Decrease
            if(contract.contractValue - endorsement.changeValue < MIN_CONTRACT_VALUE) {
                setLastError("Endorsement would result in contract value below minimum");
                return false;
            }
            break;
            
        case 'C':  // Cancel
            // Sempre permite cancelamento
            break;
            
        default:
            setLastError("Invalid endorsement type");
            return false;
    }
    
    return true;
}

double calculatePremium(const Contract& contract) {
    double totalPremium = 0.0;
    
    // Para cada cobertura no contrato
    for(int i = 0; i < contract.coverageCount; i++) {
        Coverage* coverage = findCoverage(contract.coverageIds[i]);
        if(coverage && coverage->active) {
            // Calcula o prêmio baseado na taxa da cobertura
            totalPremium += contract.contractValue * coverage->premiumRate;
        }
    }
    
    // Aplica desconto por volume se aplicável
    if(contract.contractValue > 1000000.0) {
        totalPremium *= 0.95;  // 5% de desconto
    }
    
    return totalPremium;
}

void generatePolicyNumber(char* policyNumber, int contractNumber) {
    // Formato: ANO-SEQUENCIAL (exemplo: 2024-00001)
    time_t now;
    time(&now);
    struct tm* timeinfo = localtime(&now);
    
    sprintf(policyNumber, "%d-%05d", 
            timeinfo->tm_year + 1900, 
            contractNumber);
}