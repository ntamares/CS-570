// Nestor Tamares (masc2010) & Alvin Somvilay (masc2006)
// CS 570, Summer 2016
// Guy Leonard
// Assignment #2, Paging
// second_chance.cpp

#include "second_chance.h"

using namespace std;

struct SCVal{
    bool refer;
    int value;
};

int SCReplace(int maxFrames, vector<int> pages)
{
    vector<SCVal> frames;
    int faults = 0;
    bool found;
    bool replaced = false;
    int index = 0;

    //Fill empty frame
    for(int x = 0; frames.size() < maxFrames; x++)
    {
        found = false;
        for(int y = 0; y < frames.size(); y++)
        {
            if(frames[y].value == pages.front())
            {
                found = true;
                break;
            }
        }
        if(!found)
        {
            faults++;
          	SCVal newSC;
        		newSC.refer = false;
        		newSC.value = pages.front();
            frames.push_back(newSC);
        }
        pages.erase(pages.begin());
    }

    //Fill frames with page values until all pages have been referenced
    while(!pages.empty())
    {
        found = false;

        for(int a = 0; a < maxFrames; a++)
        {
            if(frames[a].value == pages.front())
            {
                frames[a].refer = true;
                found = true;
                break;
            }
        }

        if(!found)
        {
            faults++;
            replaced = false;
            while(!replaced)
            {
                if(frames.front().refer)
                {
                    frames.front().refer = false;
                    frames.push_back(frames.front());
                    frames.erase(frames.begin());
                }
                else
                {
                    replaced = true;
                }
            }
            SCVal SCPage;
            SCPage.refer = false;
            SCPage.value = pages.front();
            frames.push_back(SCPage);
            frames.erase(frames.begin());
        }

        //Remove first page after inserting it into the frame or being referenced
        pages.erase(pages.begin());
    }

    return faults;
}
