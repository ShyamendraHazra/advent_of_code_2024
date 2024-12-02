#include <iostream>
#include <cstdint>
#include <fstream>


#define DATA_SIZE 1000

void mergeSort(uint32_t* array, uint32_t left, uint32_t right);
void merge(uint32_t* array, uint32_t left, uint32_t middle, uint32_t right);
void populate_location_id_map(uint32_t* grp_one, uint32_t* grp_two, uint32_t location_id_map[2][DATA_SIZE], uint32_t location_id_set[2][DATA_SIZE], uint16_t* location_id_set_offset);
uint16_t get_occurance(uint32_t* array, uint32_t element);
int16_t get_location(uint32_t* array, uint32_t element);
uint8_t has_element(uint32_t* array, uint32_t element);

int main() {

    uint32_t group_one[DATA_SIZE] = {0};
    uint32_t group_two[DATA_SIZE] = {0};
    uint32_t similarity_map[DATA_SIZE] = {0};
    uint32_t location_id_map[2][DATA_SIZE] = {0};
    uint32_t location_id_set[2][DATA_SIZE] = {{0}, {0}};
    uint16_t location_id_set_offset = 0;
    
    uint64_t final_similarity_score = 0;


    std::fstream file("dataset.txt", std::ios::in);

    if (file.is_open()) {

        for(uint16_t i = 0; i < DATA_SIZE; i++) {
            file >> group_one[i];
            file >> group_two[i];
        }

    } else {

        std::cout << "unable to open the dataset file" << std::endl;
        exit(EXIT_FAILURE);

    }


    mergeSort(group_one, 0, DATA_SIZE - 1);
    mergeSort(group_two, 0, DATA_SIZE - 1);

    populate_location_id_map(group_one, group_two, location_id_map, location_id_set, &location_id_set_offset);

    for(uint16_t i = 0; i < DATA_SIZE; i++) {

        final_similarity_score += location_id_map[0][i] * location_id_map[1][i];
        
    }

    std::cout << "The similarity score between two sets are :: " << final_similarity_score << std::endl;

    return 0;

}


void mergeSort(uint32_t* array, uint32_t left, uint32_t right) {
    
    if(left < right) {

        uint32_t middle = left + (right - left) / 2;
        mergeSort(array, left, middle);
        mergeSort(array, middle + 1, right);
        merge(array, left, middle, right);
    }
}

void merge(uint32_t* array, uint32_t left, uint32_t middle, uint32_t right) {


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

void populate_location_id_map(uint32_t* grp_one, uint32_t* grp_two, uint32_t location_id_map[2][DATA_SIZE], uint32_t location_id_set[2][DATA_SIZE], uint16_t* location_id_set_offset) {

    for(uint16_t i = 0; i < DATA_SIZE; i++) {
    
        location_id_map[0][i] = grp_one[i];
        
        if(has_element(location_id_set[0], grp_one[i])) {
            
            location_id_map[1][i] = location_id_set[1][get_location(location_id_set[0], grp_one[i])];
        
        } else {
            location_id_set[0][*location_id_set_offset] = grp_one[i];
            location_id_set[1][*location_id_set_offset] = get_occurance(grp_two, grp_one[i]);
            location_id_map[1][i] = location_id_set[1][*location_id_set_offset];
            (*location_id_set_offset)++;
        }
    }

}



uint16_t get_occurance(uint32_t* array, uint32_t element) {
    
    uint16_t count = 0;
    
    for(uint16_t i = 0; i < DATA_SIZE; i++) {

        if(array[i] == element) {
            count++;
        }

    }

    return count;

}


int16_t get_location(uint32_t* array, uint32_t element) {

    for(uint16_t i = 0; i < DATA_SIZE; i++) {

        if(array[i] == element) {
        
            return i;
        
        }
    }

    return -1;

}

uint8_t has_element(uint32_t* array, uint32_t element) {
    uint8_t flag = 0;
    for(uint16_t i = 0; i < DATA_SIZE; i++) {

        if(array[i] == element) {
        
            flag = 1;
        
        } else {
         
            break;

        }        
    }
    return flag;
}