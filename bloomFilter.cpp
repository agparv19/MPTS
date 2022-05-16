#include <bits/stdc++.h>
using namespace std;

class bloomFilter{
public:
    vector<int> bitArray; //not really a bit array, each entry is a 64-bit integer instead of 1 bit
    int filterSize;
    int currSize;

    bloomFilter(int size){
        filterSize = size;
        currSize = 0;

        for (int i=0; i<filterSize; i++) bitArray.push_back(0);
    }

    bool isMember(int num){

        if (bitArray[h1(num)] > 0 && bitArray[h2(num)] > 0 && bitArray[h3(num)] > 0 && bitArray[h4(num)] > 0) return true;
        return false;
    }


    void insert_val(int num){

        if (isMember(num)) {
            cout<<num<<" is probably already in the set\n";
            return;
        }
        
        bitArray[h1(num)]++;
        bitArray[h2(num)]++;
        bitArray[h3(num)]++;
        bitArray[h4(num)]++;

        currSize++;
    }

    void delete_val(int num){

        if (!isMember(num)) {
            cout<<num<<" is def not in the set, nothing to delete\n";
            return;
        }
        
        bitArray[h1(num)]--;
        bitArray[h2(num)]--;
        bitArray[h3(num)]--;
        bitArray[h4(num)]--;

        currSize--;
    }

    int getSize(){
        return currSize;
    }

    //hash 1
    int h1(int num){
        return num%filterSize;
    }

    //hash2
    int h2(int num){
        double c = 0.618033988;
        return floor(filterSize*(num*c - floor(num*c)));
    }

    //hash3
    int h3(int num){

        unsigned int x = num;

        x = ((x >> 13) ^ x) * 0x45d9f3b;
        x = ((x >> 17) ^ x) * 0x45d9f3b;
        x = (x >> 7) ^ x;

        unsigned int size = filterSize;

        int res = x%filterSize;

        return res;
    }

    //hash4
    int h4(int num){

        int n = 0;

        if (num>0) n += 7*(num%5);

        num = num/5;

        if (num>0) n += 29*(num%13);

        num = num/13;

        if (num>0) n += 71*(num%19);

        return n%filterSize;
    }



};