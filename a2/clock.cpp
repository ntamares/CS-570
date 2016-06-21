// Nestor Tamares (masc2010) & Alvin Somvilay (masc2006)
// CS 570, Summer 2016
// Guy Leonard
// Assignment #2, Paging
// clock.cpp

#include "clock.h"

int clock(int frame_len, vector<int> pages){
    
    int page_len = pages.size();
    int use_bit[page_len];
    int page_no[page_len];
    int faults = 0;
    int ptr = 0; // Pointer (clock hand)
    bool found = false;
    
  
    // Set the values of pages and use bit for each frame to 0
    for(int i = 0; i < page_len; i++) {
        page_no[i] = 0;
	use_bit[i] = 0;
    }
    
    // Iterate through all the pages
    for(int j = 0; j < page_len; j++) {
        while(1) {
	
	    found = false;
	    
	    // If the pointer has reached the end of the array, go back to 0
	    if(ptr == frame_len)
	        ptr =0;
		
	    // Check if page is in the frames
	    for(int k =0; k <  frame_len; k++) {
	        if (page_no[k] == pages[j]) {
		    use_bit[k] = 1;
		    ptr = k;
		    found = true;
		    break;
		}
	    }
	    
	    // If page is found in current frames break and don't update poitner
	    if (found == true)
	        break;
		
	    // If the use bit is 0, add a page fault insert the new page, 
	    // set the use bit to 1, and increment the pointer
	    if (use_bit[ptr] == 0) {
	        faults++;
	        page_no[ptr] = pages[j];
		use_bit[ptr] = 1;
		ptr++;
		break;
	    }
	    // If the use bit is 1, set to 0 and increment the pointer
	    else {
	        use_bit[ptr] = 0;
                ptr++;
	    }
	    
	} 
    } 
    
    return faults;
} 
