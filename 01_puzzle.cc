#include <iostream>
#include <cstdint>
#include <fstream>


#define DATA_SIZE 1000

void mergeSort(uint32_t *array, uint32_t left, uint32_t right);
void merge(uint32_t *array, uint32_t left, uint32_t middle, uint32_t right);
int main() {

    uint32_t group_one[DATA_SIZE];
    uint32_t group_two[DATA_SIZE];
    uint32_t difference_sum = 0;

    std::fstream file("dataset.txt", std::ios::in);

    if (file.is_open()) {

        for(int i = 0;i<1000;i++) {
            file >> group_one[i];
            file >> group_two[i];
        }

    } else {

        std::cout << "unable to open the dataset file" << std::endl;
        exit(EXIT_FAILURE);

    }


    mergeSort(group_one, 0, DATA_SIZE - 1);
    mergeSort(group_two, 0, DATA_SIZE - 1);

    for(int i = 0;i<1000;i++) {

        difference_sum += abs(group_one[i] - group_two[i]);
        
    }

    std::cout << "The difference between two sets are :: " << difference_sum << std::endl;

    return 0;

}


void mergeSort(uint32_t *array, uint32_t left, uint32_t right) {
    
    if(left < right) {

        uint32_t middle = left + (right - left) / 2;
        mergeSort(array, left, middle);
        mergeSort(array, middle + 1, right);
        merge(array, left, middle, right);
    }
}

void merge(uint32_t *array, uint32_t left, uint32_t middle, uint32_t right) {


    uint32_t leftSize = middle - left + 1;
    uint32_t rightSize = right - middle;

    uint32_t leftArray[leftSize];
    uint32_t rightArray[rightSize];

    for(int i = 0;i<leftSize;i++) {
        leftArray[i] = array[left + i];
    }

    for(int i = 0;i<rightSize;i++) {
        rightArray[i] = array[middle + 1 + i];
    }

    uint32_t leftIndex = 0;
    uint32_t rightIndex = 0;
    uint32_t mergedIndex = left;

    while(leftIndex < leftSize && rightIndex < rightSize) { 

        if(leftArray[leftIndex] <= rightArray[rightIndex]) {
            array[mergedIndex] = leftArray[leftIndex];
            leftIndex++;    
        } else {
            array[mergedIndex] = rightArray[rightIndex];
            rightIndex++;
        }

        mergedIndex++;
    }

    while(leftIndex < leftSize) {

        array[mergedIndex] = leftArray[leftIndex];
        leftIndex++;
        mergedIndex++;
    }

    while(rightIndex < rightSize) {

        array[mergedIndex] = rightArray[rightIndex];
        rightIndex++;
        mergedIndex++;
    }

}
