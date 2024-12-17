
#include <iostream>
#include <iomanip>
#include "menu.h"
#include "globals.h"
#include "business.h"
#include "database.h"

using namespace std;

void showMainMenu() {
    system("cls"); // Limpa tela (típico em sistemas legados)
    cout << "\n=== SURETY BOND SYSTEM ===" << endl;
    cout << "1. Policyholder Management" << endl;
    cout << "2. Contract Management" << endl;
    cout << "3. Endorsement Management" << endl;
    cout << "4. Reports" << endl;
    cout << "0. Exit" << endl;
    cout << "\nChoice: ";
}

void showPolicyholderMenu() {
    cout << "\n=== POLICYHOLDER MENU ===" << endl;
    cout << "1. New Policyholder" << endl;
    cout << "2. List Policyholders" << endl;
    cout << "3. Find Policyholder" << endl;
    cout << "0. Back to Main Menu" << endl;
    cout << "\nChoice: ";
}

void showContractMenu() {
    cout << "\n=== CONTRACT MENU ===" << endl;
    cout << "1. New Contract" << endl;
    cout << "2. List Contracts" << endl;
    cout << "3. Find Contract" << endl;
    cout << "0. Back to Main Menu" << endl;
    cout << "\nChoice: ";
}

void showEndorsementMenu() {
    cout << "\n=== ENDORSEMENT MENU ===" << endl;
    cout << "1. New Endorsement" << endl;
    cout << "2. List Contract Endorsements" << endl;
    cout << "0. Back to Main Menu" << endl;
    cout << "\nChoice: ";
}

void processPolicyholderMenu() {
    while(1) {
        showPolicyholderMenu();
        int choice;
        cin >> choice;
        
        switch(choice) {
            case 1: {
                Policyholder newPolicyholder;
                inputPolicyholder(newPolicyholder);
                if(savePolicyholder(newPolicyholder)) {
                    cout << "Policyholder saved successfully!" << endl;
                } else {
                    cout << "Error: " << getLastError() << endl;
                }
                break;
            }
            case 2:
                listPolicyholders();
                break;
            case 3: {
                int id;
                cout << "Enter Policyholder ID: ";
                cin >> id;
                Policyholder* found = findPolicyholder(id);
                if(found) {
                    displayPolicyholder(*found);
                } else {
                    cout << "Policyholder not found!" << endl;
                }
                break;
            }
            case 0:
                return;
            default:
                cout << "Invalid option!" << endl;
        }
        
        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
    }
}

void inputPolicyholder(Policyholder& policyholder) {
    policyholder.id = g_policyholders.size() + 1;  // Identificador sequencial
    policyholder.active = true;
    time(&policyholder.registrationDate);

    cin.ignore();
    cout << "Name: ";
    cin.getline(policyholder.name, MAX_NAME_LENGTH);
    
    cout << "Document Number (CNPJ): ";
    cin.getline(policyholder.documentNumber, MAX_DOC_LENGTH);
    
    if(!validateDocumentNumber(policyholder.documentNumber)) {
        setLastError("Invalid document number format");
        return;
    }
    
    cout << "Address:\n";
    cout << "Street: ";
    cin.getline(policyholder.address.street, 100);
    
    cout << "Number: ";
    cin.getline(policyholder.address.number, 20);
    
    cout << "City: ";
    cin.getline(policyholder.address.city, 50);
    
    cout << "State (2 letters): ";
    cin.getline(policyholder.address.state, 3);
    
    cout << "ZIP Code: ";
    cin.getline(policyholder.address.zipCode, 10);
    
    cout << "Phone: ";
    cin.getline(policyholder.phone, 15);
}

void displayPolicyholder(const Policyholder& p) {
    cout << "\n=== Policyholder Details ===" << endl;
    cout << "ID: " << p.id << endl;
    cout << "Name: " << p.name << endl;
    cout << "Document: " << p.documentNumber << endl;
    cout << "Address: " << p.address.street << ", " 
         << p.address.number << endl;
    cout << "City: " << p.address.city << " - " 
         << p.address.state << endl;
    cout << "ZIP: " << p.address.zipCode << endl;
    cout << "Phone: " << p.phone << endl;
    cout << "Status: " << (p.active ? "Active" : "Inactive") << endl;
}

void processContractMenu() {
    while(1) {
        showContractMenu();
        int choice;
        cin >> choice;
        
        switch(choice) {
            case 1: {
                Contract newContract;
                inputContract(newContract);
                if(saveContract(newContract)) {
                    cout << "Contract saved successfully!" << endl;
                } else {
                    cout << "Error: " << getLastError() << endl;
                }
                break;
            }
            case 2:
                listContracts();
                break;
            case 3: {
                int number;
                cout << "Enter Contract Number: ";
                cin >> number;
                Contract* found = findContract(number);
                if(found) {
                    displayContract(*found);
                } else {
                    cout << "Contract not found!" << endl;
                }
                break;
            }
            case 0:
                return;
            default:
                cout << "Invalid option!" << endl;
        }
        
        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
    }
}

void inputContract(Contract& contract) {
    contract.number = g_contracts.size() + 1;
    contract.active = true;
    time(&contract.issueDate);
    contract.coverageCount = 0;

    cout << "\n=== New Contract ===" << endl;
    
    cout << "Policyholder ID: ";
    cin >> contract.policyHolderId;
    
    if(!findPolicyholder(contract.policyHolderId)) {
        setLastError("Invalid policyholder ID");
        return;
    }

    cout << "Contract Value: ";
    cin >> contract.contractValue;
    
    if(!validateContractValue(contract.contractValue)) {
        return;  // Error message already set by validate function
    }

    // Input dates
    int year, month, day;
    cout << "\nStart Date (YYYY MM DD): ";
    cin >> year >> month >> day;
    
    struct tm startTm = {0};
    startTm.tm_year = year - 1900;
    startTm.tm_mon = month - 1;
    startTm.tm_mday = day;
    contract.startDate = mktime(&startTm);
    
    cout << "End Date (YYYY MM DD): ";
    cin >> year >> month >> day;
    
    struct tm endTm = {0};
    endTm.tm_year = year - 1900;
    endTm.tm_mon = month - 1;
    endTm.tm_mday = day;
    contract.endDate = mktime(&endTm);

    if(!validateContractDates(contract.startDate, contract.endDate)) {
        return;  // Error message already set by validate function
    }

    // Input coverages
    cout << "\nAvailable Coverages:" << endl;
    for(const auto& cov : g_coverages) {
        if(cov.active) {
            cout << cov.id << ". " << cov.name 
                 << " (Rate: " << cov.premiumRate * 100 << "%)" << endl;
        }
    }

    cout << "\nHow many coverages to add? ";
    int numCoverages;
    cin >> numCoverages;

    for(int i = 0; i < numCoverages && i < MAX_COVERAGES; i++) {
        cout << "Enter coverage ID " << (i+1) << ": ";
        int covId;
        cin >> covId;
        
        if(findCoverage(covId)) {
            contract.coverageIds[contract.coverageCount++] = covId;
        } else {
            cout << "Invalid coverage ID, skipping..." << endl;
        }
    }

    if(contract.coverageCount == 0) {
        setLastError("Contract must have at least one coverage");
        return;
    }

    // Calculate premium
    contract.premium = calculatePremium(contract);
    
    // Generate policy number
    generatePolicyNumber(contract.policyNumber, contract.number);
}

void displayContract(const Contract& c) {
    cout << "\n=== Contract Details ===" << endl;
    cout << "Number: " << c.number << endl;
    cout << "Policy Number: " << c.policyNumber << endl;
    
    Policyholder* ph = findPolicyholder(c.policyHolderId);
    if(ph) {
        cout << "Policyholder: " << ph->name << endl;
    }
    
    cout << "Value: $" << fixed << setprecision(2) << c.contractValue << endl;
    cout << "Premium: $" << c.premium << endl;
    
    char buffer[26];
    ctime_s(buffer, sizeof(buffer), &c.startDate);
    cout << "Start Date: " << buffer;
    ctime_s(buffer, sizeof(buffer), &c.endDate);
    cout << "End Date: " << buffer;
    
    cout << "Status: " << (c.active ? "Active" : "Inactive") << endl;
    
    cout << "\nCoverages:" << endl;
    for(int i = 0; i < c.coverageCount; i++) {
        Coverage* cov = findCoverage(c.coverageIds[i]);
        if(cov) {
            cout << "- " << cov->name << endl;
        }
    }
}

void processEndorsementMenu() {
    while(1) {
        showEndorsementMenu();
        int choice;
        cin >> choice;
        
        switch(choice) {
            case 1: {
                Endorsement newEndorsement;
                inputEndorsement(newEndorsement);
                if(saveEndorsement(newEndorsement)) {
                    cout << "Endorsement saved successfully!" << endl;
                } else {
                    cout << "Error: " << getLastError() << endl;
                }
                break;
            }
            case 2: {
                int contractNumber;
                cout << "Enter Contract Number: ";
                cin >> contractNumber;
                listEndorsements(contractNumber);
                break;
            }
            case 0:
                return;
            default:
                cout << "Invalid option!" << endl;
        }
        
        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
    }
}

void inputEndorsement(Endorsement& endorsement) {
    endorsement.number = g_endorsements.size() + 1;
    time(&endorsement.endorsementDate);

    cout << "\n=== New Endorsement ===" << endl;
    
    cout << "Contract Number: ";
    cin >> endorsement.contractNumber;
    
    Contract* contract = findContract(endorsement.contractNumber);
    if(!contract) {
        setLastError("Contract not found");
        return;
    }
    
    if(!contract->active) {
        setLastError("Cannot endorse inactive contract");
        return;
    }

    cout << "\nCurrent Contract Value: $" << contract->contractValue << endl;
    
    cout << "Endorsement Type (I=Increase, D=Decrease, C=Cancel): ";
    cin >> endorsement.type;
    endorsement.type = toupper(endorsement.type);
    
    if(endorsement.type != 'I' && endorsement.type != 'D' && endorsement.type != 'C') {
        setLastError("Invalid endorsement type");
        return;
    }

    if(endorsement.type != 'C') {
        cout << "Change Value: $";
        cin >> endorsement.changeValue;
    } else {
        endorsement.changeValue = 0;
    }

    cin.ignore();
    cout << "Description: ";
    cin.getline(endorsement.description, sizeof(endorsement.description));
}

void displayEndorsement(const Endorsement& e) {
    cout << "\n=== Endorsement Details ===" << endl;
    cout << "Number: " << e.number << endl;
    cout << "Contract Number: " << e.contractNumber << endl;
    
    char typeDesc[20];
    switch(e.type) {
        case 'I': strcpy(typeDesc, "Increase"); break;
        case 'D': strcpy(typeDesc, "Decrease"); break;
        case 'C': strcpy(typeDesc, "Cancellation"); break;
        default: strcpy(typeDesc, "Unknown");
    }
    
    cout << "Type: " << typeDesc << endl;
    
    if(e.type != 'C') {
        cout << "Change Value: $" << fixed << setprecision(2) << e.changeValue << endl;
    }
    
    char buffer[26];
    ctime_s(buffer, sizeof(buffer), &e.endorsementDate);
    cout << "Date: " << buffer;
    
    cout << "Description: " << e.description << endl;
}

void showReportsMenu() {
    cout << "\n=== REPORTS MENU ===" << endl;
    cout << "1. Active Contracts Summary" << endl;
    cout << "2. Premium by Policyholder" << endl;
    cout << "3. Endorsements History" << endl;
    cout << "0. Back to Main Menu" << endl;
    cout << "\nChoice: ";
}

void processReportsMenu() {
    while(1) {
        showReportsMenu();
        int choice;
        cin >> choice;
        
        switch(choice) {
            case 1:
                reportActiveContracts();
                break;
            case 2:
                reportPremiumByPolicyholder();
                break;
            case 3:
                reportEndorsementsHistory();
                break;
            case 0:
                return;
            default:
                cout << "Invalid option!" << endl;
        }
        
        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
    }
}

void reportActiveContracts() {
    cout << "\n=== Active Contracts Summary ===" << endl;
    cout << setfill('=') << setw(80) << "=" << setfill(' ') << endl;
    cout << setw(10) << "Number" << " | "
         << setw(15) << "Policy" << " | "
         << setw(15) << "Value" << " | "
         << setw(15) << "Premium" << " | "
         << "Policyholder" << endl;
    cout << setfill('-') << setw(80) << "-" << setfill(' ') << endl;
    
    double totalValue = 0.0;
    double totalPremium = 0.0;
    int activeCount = 0;
    
    for(const auto& contract : g_contracts) {
        if(contract.active) {
            Policyholder* ph = findPolicyholder(contract.policyHolderId);
            cout << setw(10) << contract.number << " | "
                 << setw(15) << contract.policyNumber << " | "
                 << setw(15) << fixed << setprecision(2) << contract.contractValue << " | "
                 << setw(15) << contract.premium << " | "
                 << (ph ? ph->name : "Unknown") << endl;
                 
            totalValue += contract.contractValue;
            totalPremium += contract.premium;
            activeCount++;
        }
    }
    
    cout << setfill('=') << setw(80) << "=" << setfill(' ') << endl;
    cout << "Total Active Contracts: " << activeCount << endl;
    cout << "Total Value: $" << fixed << setprecision(2) << totalValue << endl;
    cout << "Total Premium: $" << totalPremium << endl;
}

void reportPremiumByPolicyholder() {
    cout << "\n=== Premium by Policyholder ===" << endl;
    cout << setfill('=') << setw(80) << "=" << setfill(' ') << endl;
    cout << setw(40) << "Policyholder" << " | "
         << setw(10) << "Contracts" << " | "
         << setw(15) << "Total Value" << " | "
         << "Total Premium" << endl;
    cout << setfill('-') << setw(80) << "-" << setfill(' ') << endl;
    
    for(const auto& ph : g_policyholders) {
        int contractCount = 0;
        double totalValue = 0.0;
        double totalPremium = 0.0;
        
        // Soma contratos do tomador
        for(const auto& contract : g_contracts) {
            if(contract.policyHolderId == ph.id && contract.active) {
                contractCount++;
                totalValue += contract.contractValue;
                totalPremium += contract.premium;
            }
        }
        
        if(contractCount > 0) {
            cout << setw(40) << ph.name << " | "
                 << setw(10) << contractCount << " | "
                 << setw(15) << fixed << setprecision(2) << totalValue << " | "
                 << totalPremium << endl;
        }
    }
}

void reportEndorsementsHistory() {
    cout << "\n=== Endorsements History ===" << endl;
    cout << setfill('=') << setw(80) << "=" << setfill(' ') << endl;
    
    for(const auto& contract : g_contracts) {
        bool hasEndorsements = false;
        
        // Verifica se contrato tem endossos antes de imprimir cabeçalho
        for(const auto& end : g_endorsements) {
            if(end.contractNumber == contract.number) {
                if(!hasEndorsements) {
                    cout << "\nContract: " << contract.number 
                         << " (Policy: " << contract.policyNumber << ")" << endl;
                    cout << setfill('-') << setw(60) << "-" << setfill(' ') << endl;
                    hasEndorsements = true;
                }
                
                char typeDesc[20];
                switch(end.type) {
                    case 'I': strcpy(typeDesc, "Increase"); break;
                    case 'D': strcpy(typeDesc, "Decrease"); break;
                    case 'C': strcpy(typeDesc, "Cancel"); break;
                    default: strcpy(typeDesc, "Unknown");
                }
                
                char dateStr[26];
                ctime_s(dateStr, sizeof(dateStr), &end.endorsementDate);
                dateStr[24] = '\0';  // Remove newline
                
                cout << dateStr << " - " << typeDesc;
                if(end.type != 'C') {
                    cout << " $" << fixed << setprecision(2) << end.changeValue;
                }
                cout << endl;
                cout << "Description: " << end.description << endl;
            }
        }
        
        if(hasEndorsements) {
            cout << setfill('-') << setw(60) << "-" << setfill(' ') << endl;
        }
    }
}