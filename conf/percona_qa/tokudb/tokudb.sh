# User settings
WORKDIR=/mnt/ssd/
RQG_DIR=/mnt/ssd/randgen

# Internal settings
MTR_BT=$[$RANDOM % 300 + 1]

# Build Information
# In order to run combinations tests, modify the TOKUDB_VERSION
# first and then change the --basedir and --config-file as arguments
# to the combinations.pl script below.

TOKUDB_VERSION=mysql-5.5.36-tokudb-7.1.5
TOKUDB_DEBUG_DIR=${WORKDIR}${TOKUDB_VERSION}-debug-e-linux-x86_64
TOKUDB_VALGRIND_DIR=${WORKDIR}${TOKUDB_VERSION}-valgrind-e-linux-x86_64
TOKUDB_OPTIMIZED_DIR=${WORKDIR}${TOKUDB_VERSION}-e-linux-x86_64

# If an option was given to the script, use it as part of the workdir name
if [ -z $1 ]; then
  WORKDIRSUB=$(echo $RANDOM$RANDOM$RANDOM | sed 's/..\(......\).*/\1/')
else
  WORKDIRSUB=$1
fi


# Check if random directory already exists & start run if not
if [ -d $WORKDIR/$WORKDIRSUB ]; then
  echo "Directory already exists. Retry.";
else
  mkdir $WORKDIR/$WORKDIRSUB
  mkdir $WORKDIR/$WORKDIRSUB/tmp
  export TMP=$WORKDIR/$WORKDIRSUB/tmp

  # Special preparation: _epoch temporary directory setup
  mkdir $WORKDIR/$WORKDIRSUB/_epoch
  export EPOCH_DIR=$WORKDIR/$WORKDIRSUB/_epoch

  cd $RQG_DIR
  MTR_BUILD_THREAD=$MTR_BT; perl ./combinations.pl \
  --clean \
  --force \
  --parallel=4 \
  --trials=100 \
  --workdir=$WORKDIR/$WORKDIRSUB \
  --basedir=$TOKUDB_DEBUG_DIR \
  --config=$RQG_DIR/conf/percona_qa/tokudb/tokudb_debug.cc
fi
