#! /bin/bash

# This script will run a SINGLE RQG grammar file
# and return results to STDOUT.  Make sure to set the
# DB_DIR environment variable via "export DB_DIR=<some path>"
# The DB_DIR is basically where the extraction and test execution
# will occur within the vardir.

if [ -z "$DB_DIR" ]; then
    echo "Need to set DB_DIR"
    exit 1
fi
if [ ! -d "$DB_DIR" ]; then
    echo "Need to create directory DB_DIR"
    exit 1
fi
if [ "$(ls -A $DB_DIR)" ]; then
    echo "$DB_DIR contains files, cannot run script"
    exit 1
fi

# Enter the grammar file (.yy) and
# the data generation (.zz) file names below.

export gendata=
export grammar=

# Enter the source directory (location of the tarball) 
# and name of the tarball (excluding the tar.gz postfix) below.
#
#    Here is an example:
#
#    export SOURCE="/home/bob/tokutek/mysql-releases"
#    export TAR=mysql-5.5.29-linux2.6-x86_64

export SOURCE="/mnt/ssd"
export TAR=

if [ ! -f ${SOURCE}/${TAR}.tar.gz ] ; then
    echo "Unable to locate file ${SOURCE}/${TAR}.tar.gz"
    exit 1
fi

pushd ${DB_DIR}

echo "untarring ${SOURCE}/${TAR}..."
tar xzf ${SOURCE}/${TAR}.tar.gz

popd

export BASEDIR=${DB_DIR}/${TAR}
export VARDIR=${DB_DIR}/vardir1_1

rm -rf ${VARDIR}
mkdir ${VARDIR}

# Create this dummy directory so that "percona-qa/startup.sh 1 man"
# will work in the event that additional tracing might be needed.
mkdir ${DB_DIR}/current1_1

RQG_DIR=/home/joel/github/randgen

export numQueries=100000000
export numThreads=64
export secDuration=300
#export debugSwitch=--debug
export sqlLog1=--mysqld=--general_log
#export sqlTrace=--sqltrace

pushd ${RQG_DIR}

./runall.pl --grammar=conf/temporal/${grammar} --duration=${secDuration} --queries=${numQueries} --threads=${numThreads} --basedir=${BASEDIR} --vardir=${VARDIR} --mask-level=0 --mask=0 --seed=1 ${debugSwitch} ${sqlLog1} ${sqlTrace} > ${DB_DIR}/trial1.log 2>&1 

# This line echoes the actual command to the vardir1_1/command file
# which can be useful to grab it for posterity.

echo "./runall.pl --grammar=conf/temporal/${grammar} --duration=${secDuration} --queries=${numQueries} --threads=${numThreads} --basedir=${BASEDIR} --vardir=${VARDIR} --mask-level=0 --mask=0 --seed=1 ${debugSwitch} ${sqlLog1} ${sqlTrace}" > ${VARDIR}/command

popd

pushd ${DB_DIR}

tar -zhcf vardir1_1.tar.gz ./vardir1_1

popd
