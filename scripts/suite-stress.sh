#! /bin/bash

# This script will dive down and run all the .yy grammar files
# that exist under randgen/conf. This script does have a 
# dependency on rqg-stress which should be present in the same directory.
# All results will be written to a log file.  Make sure to set the
# DB_DIR environment variable via "export DB_DIR=<some path>"
# The DB_DIR is basically where the extraction and test execution
# will occur within the vardir.



# Enter the source directory (location of the tarball) 
# and name of the tarball (excluding the tar.gz postfix) below.
# These variables will be passed to rqg-stress.
#
#
#    Here is an example:
#
#    export SOURCE1="/home/bob/tokutek/mysql-releases"
#    export TAR1=mysql-5.5.29-linux2.6-x86_64

export SOURCE1="/mnt/ssd/"
export TAR1=

export BASEDIR1=${DB_DIR}/${TAR1}
export RQG_DIR=/mnt/ssd/randgen

rm /home/joel/RQG_results/${TAR1}-STRESS-ACTIVE.log

pushd ${RQG_DIR}/conf

for i in $(ls)
do
  export DOMAIN_DIR=$i
  pushd ${DOMAIN_DIR}

  for i in $(ls | grep yy | uniq)
  do
    vardir_name=$(echo $i | sed 's/.\{3\}$//')
    vardir_name+="_vardir"
    export VARDIR1=${DB_DIR}/${vardir_name}


#for i in $(cat /home/joel/mystuff/randgen/randgen-2.2.0/conf/zlist)
#for i in $(ls /home/joel/mystuff/randgen/randgen-2.2.0-bzr/conf/${DOMAIN_DIR} | sed 's/.\{3\}$//' | uniq)


    grammar=$i
    export grammar=$grammar

    gendata=$(echo $i | sed 's/.\{3\}$//')
    gendata+=".zz"

    if [ -a "$RQG_DIR\conf\${DOMAIN_DIR}\$gendata" ]; then
    export gendata=$gendata
    fi

    /home/joel/bin/rqg-stress >> /home/joel/RQG_results/${TAR1}-STRESS-ACTIVE.log 2>&1

    rm -rf ${DB_DIR}/${TAR1}
    rm -rf ${VARDIR1}
  
  done

  popd

done

popd

mv /home/joel/RQG_results/${TAR1}-STRESS-ACTIVE.log /home/joel/RQG_results/${TAR1}-STRESS.log
