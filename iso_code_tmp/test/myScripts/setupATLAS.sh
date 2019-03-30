export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase
alias setupATLAS='source ${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh'
setupATLAS
localSetupROOT
localSetupDQ2Client --skipConfirm
localSetupRucioClients
localSetupPandaClient
localSetupFAX --skipConfirm
localSetupPandaClient currentJedi --noAthenaCheck
# Initiate the atlas voms-proxy
voms-proxy-init -voms atlas
