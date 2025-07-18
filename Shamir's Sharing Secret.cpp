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

        thresholdNumber = numberOfShares / 2;

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
            std::cout << "Participant " << (i + 1) << ": Share y = " << share.second << "\n";
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

                std::vector<Share> selectedShares;
                for (int i = 0; i < shareCount; ++i) {
                    int participantIndex;
                    std::cout << " Requesting share from Participant " << (i + 1) << ":";
                    std::cin >> participantIndex;

                    if (participantIndex < 1 || participantIndex > participants.size()) {
                        std::cerr << "Error: Invalid participant index. Must be between 1 and " << participants.size() << "\n";
                        --i;
                        continue;
                    }
                    Share share = participants[participantIndex - 1].provideShare(0);
                    selectedShares.push_back(share);
                }


                SecretReconstruction secretReconstruction(thresholdNumber);
                int reconstructedSecret = secretReconstruction.reconstructSecret(selectedShares);

                if (dealer.verifySecret(reconstructedSecret)) {
                    std::cout << "The secret has been successfully reconstructed!\n";
                    std::cout << "Reconstructed secret: " << reconstructedSecret << "\n";
                } else {
                    std::cout << "Secret reconstruction failed!\n";
                    std::cout << "Reconstructed secret: " << reconstructedSecret << "\n";
                }
            }
        }
    }
    else {
        std::cout << "Secret reconstruction skipped." << std::endl;
    }

    return 0;
}


