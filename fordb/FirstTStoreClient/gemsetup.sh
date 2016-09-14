export XDAQ_ROOT=/opt/xdaq
export XDAQ_DOCUMENT_ROOT=/opt/xdaq/htdocs
export uHALROOT=/opt/cactus

export C_INCLUDE_PATH=${uHALROOT}/include
export CPLUS_INCLUDE_PATH=${uHALROOT}/include

export LD_LIBRARY_PATH=${uHALROOT}/lib:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${XDAQ_ROOT}/lib

export PATH=${PATH}:${XDAQ_ROOT}/bin
export PATH=${uHALROOT}/bin:$PATH
export PATH=${PATH}:/sbin
export PATH=${PATH}:/usr/sbin
export PATH=${PATH}:/usr/local/sbin
export PATH=${PATH}:/opt/PyChips_1_4_3/scripts

export PYTHONPATH=${PYTHONPATH}:/usr/local/lib/python2.7/site-packages
export PYTHONPATH=${PYTHONPATH}:/usr/lib/python2.6/site-packages/
export PYTHONPATH=${PYTHONPATH}:/afs/cern.ch/work/c/castaned/
export AMC13_ADDRESS_TABLE_PATH=/opt/cactus/etc/amc13

export BUILD_HOME=/afs/cern.ch/work/c/castaned/gem-daq-code
export LDQM_STATIC=/afs/cern.ch/work/c/castaned/ldqm-browser/LightDQM/LightDQM/test
export GLIBTEST=/afs/cern.ch/work/c/castaned/gem-daq-code

alias cern="ssh -XY castaned@lxplus.cern.ch"
alias python27="/usr/local/bin/python2.7"
