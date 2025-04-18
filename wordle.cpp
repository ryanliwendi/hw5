#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
set<string> set_combine(set<string> s1, set<string> s2);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    set<string> words;
    if (in.find('-') == string::npos)
    {
        if (floating.empty() && dict.find(in) != dict.end())
            words.insert(in);
        return words;
    }
    int count = 0;
    for (char c : in)
        if (c == '-')
            count++;
    if (count < floating.size())
        return words;
    int pos = in.find('-');
    string nextin = in;
    for (int i = 0; i < floating.size(); i++)
    {
        nextin[pos] = floating[i];
        string nextfloat = floating.substr(0, i) + floating.substr(i + 1);
        set<string> temp = wordle(nextin, nextfloat, dict);
        words = set_combine(words, temp);
    }
    for (int i = 0; i < 26; i++)
    {
        char c = 'a' + i;
        if (floating.find(c) != string::npos)
            continue;
        nextin[pos] = c;
        set<string> temp = wordle(nextin, floating, dict);
        words = set_combine(words, temp);
    }
    return words;
}

// Define any helper functions here
set<string> set_combine(set<string> s1, set<string> s2)
{
    set<string> ret = s1;
    for (set<string>::iterator it = s2.begin(); it != s2.end(); ++it)
        ret.insert(*it);
    return ret;
}