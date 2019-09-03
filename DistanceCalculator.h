#include <fstream>
#include <cmath>
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <utility>
#include <nlohmann/json.hpp>
#include <sstream>
#include "StringProcessing.h"
using namespace std;
using json = nlohmann::json;

class DistanceCalculator
{
public:
    static vector<string> FindLocationsInRadius(json j, float range)
    {

        vector<string> locations;
        float tempLat, tempLong, radianLatitudeLocation, radianLatitudeLondon, thetaNormal, thetaRadian, distance;
        float London[] = {51.515419, -0.141099};
        string concatinatedLocationName;
        ostringstream tempLocationString;
        for (auto it : j.items())
        {
            for (auto o : it.value()["offices"].items())
            {
                auto v = StringProcessing::explode(o.value()["coordinates"], ',');
                tempLat = stof(v[0]);
                tempLong = stof(v[1]);
                //haversine formula requires coordinate points to be in radians therefore convert all coordinate points to radians
                radianLatitudeLocation = M_PI * tempLat / 180;
                radianLatitudeLondon = M_PI * London[0] / 180;
                thetaNormal = London[1] - tempLong;
                thetaRadian = M_PI * thetaNormal / 180;
                distance = sin(radianLatitudeLondon) * sin(radianLatitudeLocation) + cos(radianLatitudeLondon) * cos(radianLatitudeLocation) * cos(thetaRadian);

                distance = acos(distance);
                distance = distance * 180 / M_PI;
                //we expect the resulting distance in KM's so we convert from minutes to degrees then miles to kilometers
                distance = distance * 60 * 1.1515;
                distance = distance * 1.609344;

                if (distance <= range)
                {
                    //because we want to arrange the result in alphabetical order based on company name, we create an array of all locations
                    //in the provided radius

                    //always ensure string stream is clear before reconstructing a new string
                    tempLocationString.str(string());
                    tempLocationString << it.value()["organization"] << "\n"
                                       << o.value()["address"] << "\n"
                                       << "Distance of location: " << distance << "\n"
                                       << "User provided range: "
                                       << range << " \n";
                    concatinatedLocationName = tempLocationString.str();
                    locations.push_back(concatinatedLocationName);
                }
            }
        }
        return locations;
    }
};