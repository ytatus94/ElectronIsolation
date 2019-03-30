# Setup DQ2 environments
#source /afs/cern.ch/atlas/offline/external/GRID/ddm/DQ2Clients/setup_testing.sh 
source /afs/cern.ch/atlas/offline/external/GRID/ddm/DQ2Clients/setup.sh
# Initiate the atlas voms-proxy
voms-proxy-init -voms atlas
# Check atlas voms-proxy
#voms-proxy-info -all
