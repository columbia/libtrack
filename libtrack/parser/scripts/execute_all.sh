#!/bin/bash
if [ "$1" == "clean" ]
then
    rm *.csv
    rm *.eps
    exit 0
fi

# check args
if [ "$#" -ne 2 ];
then
    echo "Usage: "$0"  IDIR ODIR"
    exit -1
fi
IDIR=$1
ODIR=$2
FULLPATHS="/home/vatlidak/Repos/telesphorus/scripts/fullpaths.py"

# Copy package configuration files
cp ~/Repos/telesphorus/conf/main.conf /etc/telesphorus/main.conf
# Instal package from source code
cd ~/Repos/telesphorus/
sudo python ~/Repos/telesphorus/setup.py install
TELESPHORUS=`which telesphorus`
cd -

if [ ! -d "${IDIR}" ]
then
    echo "Invalid input directory: '${IDIR}'"
    exit 1
fi

echo "Input Directory is there but...I am a strict machine...I expect a certain structure:"
echo "-LOGS"
echo "--CATEGORY1"
echo "----APP1"
echo "----APP2"
echo "----..."
echo "--CATEGORY2"
echo "----APP1"
echo "----APP2"
echo "----..."
echo "--..."
echo -n "Do you follow this structure? [YES|no]"
read ans
if [  "${ans}" != "YES" ]
then
    echo "Then....goodbye"
    exit 1
fi

if [ ! -d "${ODIR}" ]
then
    echo "Creating ouput directory hierarchy: '${ODIR}'"
    mkdir "${ODIR}"
    mkdir "${ODIR}/graphs"
    mkdir "${ODIR}/fullpaths"
    mkdir "${ODIR}/stats"
    ans="YES"
else
    # You really don't want to overwrite results
    echo  "You are going to overwrite last results"
    echo -n "Are you sure it's OK? [YES|N]: "
    read ans
fi

if [  "${ans}" == "YES" ]
then
    echo "I will start a process which takes some time..."
    sleep 1

    $TELESPHORUS "-t" "${IDIR}" "-g" "${ODIR}/graphs/aggregate.txt" >  "${ODIR}/stats/aggregate.txt" &
    $FULLPATHS "-t" "${IDIR}" >  "${ODIR}/fullpaths/aggregate.txt" &
    for categorie in  `ls ${IDIR}`;
    do
        for application in `ls ${IDIR}/${categorie}`
        do
            $TELESPHORUS "-t" "${IDIR}/${categorie}/${application}" "-g" "${ODIR}/graphs/${application}.txt" >  "${ODIR}/stats/${application}.txt" &
            $FULLPATHS "-t" "${IDIR}/${categorie}/${application}" >  "${ODIR}/fullpaths/${application}.txt"
        done
    done
else
    echo "OK, I didn't replace anything :-)"
fi


echo "We are all done :-)"
