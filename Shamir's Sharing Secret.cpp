#include <iostream>
#include <vector>
#include "Dealer.hpp"
#include "Participant.hpp"
#include "SecretReconstruction.hpp"

int main() {
    Dealer dealer;

    int secretInput;
    std::cout << "Enter the secret code: ";
    std::cin >> secretInput;

    int numberOfShares, thresholdNumber;
    bool validShares = false;

    while (!validShares) {
        std::cout << "Enter the total number of shares to distribute: ";
        std::cin >> numberOfShares;
        std::cout << "Enter the threshold number of shares required for reconstruction: ";
        std::cin >> thresholdNumber;

        if (numberOfShares < thresholdNumber) {
            std::cout << "The total shares cannot be less than the threshold. Please try again.\n";
        } else {
            validShares = true;
        }
    }

    dealer.generateSecret(secretInput);
    Polynomial poly = dealer.choosePolynomial(thresholdNumber);
    std::vector<Share> shares = dealer.calculateShares(numberOfShares, thresholdNumber);

    std::vector<Participant> participants(numberOfShares);
    for (int i = 0; i < numberOfShares; ++i) {
        dealer.sendShare(participants[i], shares[i]);
    }

    char printShares;
    std::cout << "Do you want to print the list of shares? (y/n): ";
    std::cin >> printShares;
    if (printShares == 'y' || printShares == 'Y') {
        for (int i = 0; i < numberOfShares; ++i) {
            std::pair<int, int> share = shares[i].getShare();
            std::cout << "Participant " << (i + 1) << ": Share y = "
                << share.second << "\n";
        }
    }

    char reconstructChoice;
    std::cout << "Do you want to reconstruct the secret? (y/n): ";
    std::cin >> reconstructChoice;

    if (reconstructChoice == 'y' || reconstructChoice == 'Y') {
        int shareCount;
        bool validReconstruction = false;

        while (!validReconstruction) {
            std::cout << "Enter the number of shares for reconstruction: ";
            std::cin >> shareCount;

            if (shareCount < thresholdNumber) {
                std::cout << "You need at least " << thresholdNumber << " shares. Please try again.\n";
            } else if (shareCount > numberOfShares) {
                std::cout << "You only have " << numberOfShares << " participants. Please enter a smaller number.\n";
            } else {
                validReconstruction = true;

                SecretReconstruction secretReconstruction(thresholdNumber);
                for (int i = 0; i < shareCount; ++i) {
                    std::cout << "Requesting share from participant " << i+1 << std::endl;
                    secretReconstruction.requestShare(participants[i]);
                }

                int reconstructedSecret = secretReconstruction.reconstructSecret();

                if (dealer.verifySecret(reconstructedSecret)) {
                    std::cout << "The secret has been successfully reconstructed!" << std::endl;
                    std::cout << "Reconstructed secret: " << reconstructedSecret << std::endl;
                } else {
                    std::cout << "Secret reconstruction failed!" << std::endl;
                    std::cout << "Reconstructed secret: " << reconstructedSecret << std::endl;
                }
            }
        }
    } else {
        std::cout << "Secret reconstruction skipped." << std::endl;
    }
    return 0;
}
