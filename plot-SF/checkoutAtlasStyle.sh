#!/bin/bash

# Check AtlasStyle packae if the directories do not yet exist:
if [ ! -d "AtlasStyle" ]; then
    svn co svn+ssh://svn.cern.ch/reps/atlasgroups/pubcom/root/atlasstyle/trunk AtlasStyle
fi
