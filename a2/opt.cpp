// Nestor Tamares (masc2010) & Alvin Somvilay (masc2006)
// CS 570, Summer 2016
// Guy Leonard
// Assignment #2, Paging
// opt.cpp

#include "opt.h"

using namespace std;

/*Search the rest of the oncoming pages and check to see if any pages
in the frames are to be referenced again. If there exists a page in the
frame that is not referenced again, return its index. Else, find the page that is referenced
again last and return its index.*/
int findOPT(vector<int> frameVect, int maxFrames, vector<int> pages)
{
    int index = 0;
    int farPage = 0;
    bool inPageSet = false;

    for(int f = 0; f < maxFrames; f++)
    {
        inPageSet = false;
        for(int v = 0; v < pages.size(); v++)
        {
            if(frameVect[f] == pages[v])
            {
                inPageSet = true;
                if(v > farPage)
                {
                    farPage = v;
                    index = f;
                }
                break;
            }
        }
        if(!inPageSet)
            return f;
    }
    return index;
}


int OPTReplace(int maxFrames, vector<int> pages)
{
    vector<int> frames;
    int replaceIndex = 0;
    int faults = 0;
    bool found;
    int index = 0;

    for(int x = 0; frames.size() < maxFrames; x++)
    {
        found = false;
        for(int y = 0; y < frames.size(); y++)
        {
            if(frames[y] == pages.front())
            {
                found = true;
                break;
            }
        }
        if(!found)
        {
            faults++;
            frames.push_back(pages.front());
        }
        pages.erase(pages.begin());
    }

    //Fill frames with page values until all pages have been referenced
    while(!pages.empty())
    {
        found = false;
        for(int a = 0; a < maxFrames; a++)
        {
            if(frames[a] == pages.front())
            {
                found = true;
                break;
            }
        }

        if(!found)
        {
            faults++;
            replaceIndex = findOPT(frames, maxFrames, pages);
            frames[replaceIndex] = pages.front();
        }

        //Remove first page after inserting it into the frame or being referenced
        pages.erase(pages.begin());

    }

    return faults;
}


