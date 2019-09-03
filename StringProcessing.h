#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;

class StringProcessing
{
public:
    //method to split each string of comma separated coordinates
    // into an array of longitude and latitude values
    static vector<string> explode(string const &s, char delim)
    {
        vector<string> result;
        istringstream iss(s);

        for (string token; getline(iss, token, delim);)
        {
            result.push_back(move(token));
        }

        return result;
    }
    //function to print a rpovided array
    static void print(vector<string> locationsParameter)
    {
        printf("printing........\n");
        printf("\n");
        if (locationsParameter.size() == 0)
        {
            cout << "No locations in provided range" << endl;
        }
        else
        {
            for (int i = 0; i < locationsParameter.size(); i++)
                cout << locationsParameter[i] << endl;
        }
        printf("----------------------------------------");
        printf("\n");
        printf("\n");
    }
    //function to compare two strings
    //returns 1 if string a is alphabetically less than string b
    static bool mycomp(string a, string b)
    {
        return a < b;
    }
    //function to sort a provided string array alphabetically
    static vector<string> alphabaticallySort(vector<string> a)
    {
        int n = a.size();
        sort(a.begin(), a.end(), mycomp);
        return a;
    }
};