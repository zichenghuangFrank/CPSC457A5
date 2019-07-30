/**********************************************
 * Last Name:   <Huang>
 * First Name:  <Zicheng>
 * Student ID:  <30009205>
 * Course:      CPSC 457
 * Tutorial:    <T02>
 * Assignment:  5
 * Question:    Q6
 *
 * File name: pagesim.cpp
 *********************************************/
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <string.h>
#include <vector>

using namespace std;

vector<int>entries;
vector<int>optimalFrame;
vector<int>LRUFrame;
vector<int>clockFrame;



int main(int argc, char **argv){
    // check command line right or not
    if(argc != 2){
        cout << "This program needs 2 command arguments. Usage: ./program num < input.txt." << endl;
        exit(-1);
    }

    int avaFrame = stoi(argv[1]);               //

    int pageRef;
    
     while(1) {
        if( 1 != scanf("%d", &pageRef)) break;
        entries.push_back(pageRef);
    }
    /*
    for(int i = 0; i < entries.size(); i++){
        cout << entries[i] << endl;
    }    
    */
    // Optimal ===========================================================================
    int optimalFrameFault = 0;
    for(int m = 0; m < entries.size(); m++){
        if(entries.size() <= avaFrame){
            optimalFrame.push_back(entries[m]);
            continue;
        }else{

            bool flagExist = false;

            //check if the page is the same as one of them in the frame.
            for(int n = 0; n < optimalFrame.size(); n++){
                if(entries[m] == optimalFrame[n]){
                    flagExist = true;
                    break;
                }
            }
            if(!flagExist){
                optimalFrameFault++;
            }else{
                continue;
            }
            
            if(optimalFrame.size() < avaFrame){
                optimalFrame.push_back(entries[m]);
            }else if(m == entries.size() - 1){
                optimalFrame[0] = entries[m];
            }else{
                int oldIndex = -1;
                int updateIndex = -1;
                for(int i = 0; i < optimalFrame.size(); i++){
                    int tempStore = -1;
                    for(int j = (m + 1); j < entries.size(); j++){
                        if(optimalFrame[i] == entries[j]){
                            tempStore = j;
                            break;
                        }
                    }
                    if(tempStore == -1){
                        updateIndex = i;
                        break;
                    }
                    
                    if(updateIndex < tempStore){
                        oldIndex = tempStore;
                        updateIndex = i;
                    }
                    
                }
                
                optimalFrame[updateIndex] = entries[m];
            }
        }
    }
    cout << "Optimal:" << endl;
    cout << "  - frames: ";
    for(int i = 0; i < optimalFrame.size(); i++){
        cout << optimalFrame[i] << " ";
    }
    cout << endl << "  - page faults: " << optimalFrameFault << endl;
     
    // LRU ===============================================================================
    int LRUFrameFault = 0;
    for(int m = 0; m < entries.size(); m++){
        if(entries.size() <= avaFrame){
            LRUFrame.push_back(entries[m]);
            continue;
        }else{
            
            bool flagExist = false;
            
            //check if the page is the same as one of them in the frame.
            for(int n = 0; n < LRUFrame.size(); n++){
                if(entries[m] == LRUFrame[n]){
                    flagExist = true;
                    break;
                }
            }
            if(!flagExist){
                LRUFrameFault++;
            }else{
                continue;
            }
            
            if(LRUFrame.size() < avaFrame){
                LRUFrame.push_back(entries[m]);
            }else{
                int oldIndex = entries.size();
                int updateIndex = entries.size();
                for(int i = 0; i < LRUFrame.size(); i++){
                    int tempStore = -1;
                    int j = m - 1;
                    while(j >= 0){
                        if(LRUFrame[i] == entries[j]){
                            tempStore = j;
                            break;
                        }
                        j--;
                    }
                    if(oldIndex > tempStore){
                        updateIndex = i;
                        oldIndex = tempStore;
                    }
                }
                LRUFrame[updateIndex] = entries[m];
            }
        }
    }
    cout << "LRU:" << endl;
    cout << "  - frames: ";
    for(int i = 0; i < LRUFrame.size(); i++){
        cout << LRUFrame[i] << " ";
    }
    cout << endl << "  - page faults: " << LRUFrameFault << endl;
    
    // Clock =============================================================================
    int clockFrameFault = 0;
    vector<int>clockFrameTable (avaFrame, 1);
    int pt = 0;
    for(int m = 0; m < entries.size(); m++){
        if(entries.size() <= avaFrame){
            clockFrame.push_back(entries[m]);
            continue;
        }else{
            
            bool flagExist = false;
            
            //check if the page is the same as one of them in the frame.
            for(int n = 0; n < clockFrame.size(); n++){
                if(entries[m] == clockFrame[n]){
                    flagExist = true;
                    break;
                }
            }
            if(!flagExist){
                clockFrameFault++;
            }else{
                continue;
            }
            
            if(clockFrame.size() < avaFrame){
                clockFrame.push_back(entries[m]);
            }else{
                while(clockFrameTable[pt] == 1){
                    clockFrameTable[pt] = 0;
                    pt = (pt + 1) % avaFrame;
                }
                clockFrame[pt] = entries[m];
                clockFrameTable[pt] = 1;
                pt = (pt + 1) % avaFrame;
            }
        }
    }
    cout << "Clock:" << endl;
    cout << "  - frames: ";
    for(int i = 0; i < clockFrame.size(); i++){
        cout << clockFrame[i] << " ";
    }
    cout << endl << "  - page faults: " << clockFrameFault << endl;
    
    // End ===============================================================================
    return 0;
}
