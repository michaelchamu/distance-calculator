/*
The solution was reached using the following sites for reference:
http://www.movable-type.co.uk/scripts/latlong.html
http://www.geodatasource.com/developers/javascript
1. The list of locations to search from are obtained from partners.json file, 
2. The file reading process is wrapped in a try{}catch block to 
    enable the program to gracefully exit if there are any extra errors in the program.
3. I added an extra routine so that, If file is found but is empty, or the json in the file is invalid the program can 
search for the data using an http request to 
    https://success.spidergap.com/partners.json?inf_contact_key=03c136b17c618f95ea80462a55165d4d9bb94ec0b9ff1c2d2129031ffdf84a05
4. If the values are still not found, the program will exit with an error message
*/
#include <utility>
#include <nlohmann/json.hpp>
#include <iostream>
#include "DistanceCalculator.h"
using json = nlohmann::json;
using namespace std;

int main(void)
{
    float range;
    char response;
    //ask user for range
    do
    {
        cout
            << "Enter range you want to search: \n";
        cin >> range;
        vector<string> locations;
        ifstream ifs("locations.json");
        json j = json::parse(ifs);
        locations = DistanceCalculator::FindLocationsInRadius(j, range);
        cout << "Printing list not sorted alphabetically\n";
        StringProcessing::print(locations);
        locations = StringProcessing::alphabaticallySort(locations);
        cout << "Printing list sorted alphabetically\n";
        StringProcessing::print(locations);
        cout << "DO YOU WANT TO RUN ANOTHER CALCULATION? Y/N: ";
        cin >> response;
    } while (response == 'Y' || response == 'y');

    return 0;
}
