//
//  Author: Kai Qi
//  Homework 4

#include <iostream>
#include <vector>
using namespace std;
  

// ****************************************************************
// * Method1: Optimal page replacement
// ****************************************************************
// Function to check whether a page exists in a frame or not
bool search_opt(int key, vector<int>& frame)
{
    for (int i = 0; i < frame.size(); i++)
        if (frame[i] == key)
            return true;
    return false;
}
  
// Function to find the frame that will not be used recently in future
int predict_opt(int page[], vector<int>& frame, int page_number, int index)
{
    // Store the index of pages which are going to be used recently in future
    int res = -1, farthest = index;
    for (int i = 0; i < frame.size(); i++)
    {
        int j;
        for (j = index; j < page_number; j++)
        {
            if (frame[i] == page[j])
            {
                if (j > farthest)
                {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }
  
        // If a page is never referenced in future, return it.
        if (j == page_number)
            return i;
    }
  
    // If all of the frames were not in future, just replace the one with index of 0 Otherwise we return res.
    if (res == -1)
        return 0;
    else
        return res;
}
  
void optimal_replace(int page[], int page_number, int frame_number)
{
    // Create an array for given number of frames and initialize it as empty.
    vector<int> frame;
    int num_pagefault = 0;
  
    // Traverse through page reference array and check for page fault
    for (int i = 0; i < page_number; i++) {
  
        // Page found in a frame, no page fault
        if (search_opt(page[i], frame)) {
            continue;
        }
  
        // Page not found, page fault occurs. But there is still space available in frames.
        if (frame.size() < frame_number){
            frame.push_back(page[i]);
            num_pagefault++;
        }
        // Do page relacement
        else {
            int j = predict_opt(page, frame, page_number, i + 1);
            frame[j] = page[i];
            num_pagefault++;
        }
        
        for(int i =0; i < frame.size(); i++ )
            cout << frame[i] << " ";
        cout << endl;
    }
    cout << "When using optimal algorithm, there are " << num_pagefault << " page faults." << endl << endl;
}



// ****************************************************************
// * Method2: Least Recently Used page replacement
// ****************************************************************


// Function to check whether a page exists
// in a frame or not
bool search_lru(int key, vector<int>& frame)
{
    for (int i = 0; i < frame.size(); i++)
        if (frame[i] == key)
            return true;
    return false;
}
  
// Function to find the frame that was least recently used
int lookback_lru(int page[], vector<int>& frame, int page_number, int index)
{
    // Store the index of pages which was least recently used
    int res = -1, farthest = index;
    for (int i = 0; i < frame.size(); i++)
    {
        int j;
        for (j = index; j > 0; j--)
        {
            if (frame[i] == page[j])
            {
                if (j < farthest)
                {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }
    }
  
        return res;
}
  
void lru_replace(int page[], int page_number, int frame_number)
{
    // Create an array for given number of frames and initialize it as empty.
    vector<int> frame;
    int num_pagefault = 0;
  
    // Traverse through page reference string and check for page faults
    for (int i = 0; i < page_number; i++) {
  
        // Page found in a frame
        if (search_lru(page[i], frame)) {
            continue;
        }
  
        // Page not found, there is space
        if (frame.size() < frame_number){
            frame.push_back(page[i]);
            num_pagefault++;
        }
        // Do page replacement
        else {
            int j = lookback_lru(page, frame, page_number, i - 1);
            frame[j] = page[i];
            num_pagefault++;
        }
        
        for(int i =0; i < frame.size(); i++ )
            cout << frame[i] << " ";
        cout << endl;
    }
    cout << "When using LRU algorithm, there are " << num_pagefault << " page faults." << endl << endl;
}

int main(int argc, const char * argv[])
{
    
    int page[20] = {0};

    srand((unsigned)time(NULL));
    page[0] = rand() % 5 + 1;
    for (int i = 1; i < 20; i++)
    {
        page[i] = rand() % 5 + 1;
        if(page[i] == page[i-1])
            page[i] = rand() % 5 + 1;
    }
    
    cout << "The reference string is: ";
    for (int i = 0; i < 20; i++)
        cout << page[i] << " ";
    cout << endl;
        
    cout << "Input the frame number:";
    int num;
    cin >> num;

    optimal_replace(page, 20, num);
    lru_replace(page, 20, num);
   
    // TEST***********
    /*int page[12] = {1,2,3,4,1,2,5,1,2,3,4,5};
    lru_replace(page, 12, 4);
    optimal_replace(page, 12, 4);*/
    
    return 0;
}
