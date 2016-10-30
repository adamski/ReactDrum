//
//  HelperMethods.h
//  ReactDrum
//
//  Created by Adam Wilson on 30/10/2016.
//
//

#ifndef HelperMethods_h
#define HelperMethods_h

#include "JuceHeader.h"

class HelperMethods
{
public:
    static String getSampleNameFromFilename(String filename)
    {
        String sampleName = filename.upToLastOccurrenceOf("_ogg", false, false);
        sampleName = sampleName.replace("_", " ");
        return sampleName;
    }
};

#endif /* HelperMethods_h */
