# Copyright (c) 2012 Oracle and/or its affiliates. All rights reserved.
# Use is subject to license terms.
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; version 2 of the License.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301
# USA

# Certain parts (c) Percona Inc

# Version 2.0: Advanced Combinatorics (for PS, TokuDB: to be done)
# Note that --short_column_names is required for this grammar (see .zz1 for use of 'c1' name)

# Workarounds
# --mysqld=--utility-user-password=test in top block: to avoid assert BUG #

$combinations=
[
 ['
  --seed=random --duration=300 --querytimeout=60 --short_column_names
  --reporter=Shutdown,Backtrace,QueryTimeout,ErrorLog,ErrorLogAlarm
  --mysqld=--log-output=none --mysqld=--sql_mode=ONLY_FULL_GROUP_BY
  --mysqld=--utility-user-password=test
 '],[
  '--grammar=conf/percona_qa/tokudb/tokudb.yy --gendata=conf/percona_qa/tokudb/tokudb.zz1 --threads=15 --no-mask
     --basedir=/TokuDB-Debug',
  '--grammar=conf/percona_qa/tokudb/tokudb.yy --gendata=conf/percona_qa/tokudb/tokudb.zz1 --threads=20 --no-mask
     --basedir=/TokuDB-Valgrind --valgrind --valgrind_options=--soname-synonyms=somalloc=NONE --reporter=ValgrindErrors --validator=MarkErrorLog',
  '--grammar=conf/percona_qa/tokudb/tokudb.yy --gendata=conf/percona_qa/tokudb/tokudb.zz1 --threads=1  --no-mask
     --basedir=/TokuDB-Debug',
  '--grammar=conf/percona_qa/tokudb/tokudb.yy --gendata=conf/percona_qa/tokudb/tokudb.zz1 --threads=17 --mask-level=1 --validator=Transformer
     --basedir=/TokuDB-Debug --mysqld=--enforce-storage-engine=TokuDB',
  '--grammar=conf/percona_qa/tokudb/tokudb.yy --gendata=conf/percona_qa/tokudb/tokudb.zz1 --threads=1  --no-mask
     --basedir=/TokuDB-Valgrind --valgrind --valgrind_options=--soname-synonyms=somalloc=NONE --reporter=ValgrindErrors --validator=MarkErrorLog',
  '--grammar=conf/percona_qa/tokudb/tokudb.yy --gendata=conf/percona_qa/tokudb/tokudb.zz1 --threads=13 --mask-level=1 --validator=Transformer
     --basedir=/TokuDB-Valgrind --valgrind --valgrind_options=--soname-synonyms=somalloc=NONE --reporter=ValgrindErrors --validator=MarkErrorLog',
  '--grammar=conf/percona_qa/tokudb/tokudb.yy --gendata=conf/percona_qa/tokudb/tokudb.zz2 --threads=1  --no-mask
     --basedir=/TokuDB-Debug',
  '--grammar=conf/percona_qa/tokudb/tokudb.yy --gendata=conf/percona_qa/tokudb/tokudb.zz2 --threads=11 --mask-level=1 --validator=Transformer
     --basedir=/TokuDB-Debug',
  '--grammar=conf/percona_qa/tokudb/tokudb.yy --gendata=conf/percona_qa/tokudb/tokudb.zz2 --threads=25 --no-mask
     --basedir=/TokuDB-Valgrind --valgrind --valgrind_options=--soname-synonyms=somalloc=NONE --reporter=ValgrindErrors --validator=MarkErrorLog',
  '--grammar=conf/percona_qa/tokudb/tokudb.yy --gendata=conf/percona_qa/tokudb/tokudb.zz2 --threads=8 --mask-level=1 --validator=Transformer
     --basedir=/TokuDB-Valgrind --valgrind --valgrind_options=--soname-synonyms=somalloc=NONE --reporter=ValgrindErrors --validator=MarkErrorLog',
  '--grammar=conf/percona_qa/tokudb/tokudb.yy --gendata=conf/percona_qa/tokudb/tokudb.zz3 --threads=10 --no-mask
     --basedir=/TokuDB-Debug',
  '--grammar=conf/percona_qa/tokudb/tokudb.yy --gendata=conf/percona_qa/tokudb/tokudb.zz3 --threads=15 --no-mask
     --basedir=/TokuDB-Valgrind --valgrind --valgrind_options=--soname-synonyms=somalloc=NONE --reporter=ValgrindErrors --validator=MarkErrorLog',
  '--grammar=conf/percona_qa/tokudb/tokudb.yy --gendata=conf/percona_qa/tokudb/tokudb.zz2 --threads=15 --mask-level=1 --validator=Transformer
     --basedir=/TokuDB-Optimized',
  '--grammar=conf/percona_qa/tokudb/tokudb.yy --gendata=conf/percona_qa/tokudb/tokudb.zz1 --threads=1  --no-mask
     --basedir=/TokuDB-Optimized'
 ],[ 
  '--mysqld=--loose-tokudb_cache_size=1000000000 --mysqld=--tokudb_directio=ON',
  '--mysqld=--loose-tokudb_cache_size=1000000000 --mysqld=--tokudb_directio=OFF',
  '--mysqld=--loose-tokudb_cache_size=4075133500 --mysqld=--tokudb_directio=ON',
  '--mysqld=--loose-tokudb_cache_size=4075133500 --mysqld=--tokudb_directio=OFF',
  '--mysqld=--loose-tokudb_cache_size=4890160200 --mysqld=--tokudb_directio=ON',
  '--mysqld=--loose-tokudb_cache_size=5705186900 --mysqld=--tokudb_directio=ON',
  '--mysqld=--loose-tokudb_cache_size=6520213600 --mysqld=--tokudb_directio=ON'
 ],[
  '--mysqld=--tokudb_checkpoint_lock=OFF',
  '--mysqld=--tokudb_checkpoint_lock=ON'
 ],[
  '--mysqld=--tokudb_checkpoint_on_flush_logs=OFF',
  '--mysqld=--tokudb_checkpoint_on_flush_logs=ON'
 ],[
  '--mysqld=--tokudb_checkpointing_period=30',
  '--mysqld=--tokudb_checkpointing_period=60',
  '--mysqld=--tokudb_checkpointing_period=90',
  '--mysqld=--tokudb_checkpointing_period=150'
 ],[
  '--mysqld=--tokudb_commit_sync=ON',
  '--mysqld=--tokudb_commit_sync=OFF'
 ],[
  '--mysqld=--tokudb_disable_hot_alter=OFF',
  '--mysqld=--tokudb_disable_hot_alter=ON'
 ],[
  '--mysqld=--tokudb_disable_prefetching=OFF',
  '--mysqld=--tokudb_disable_prefetching=ON'
 ],[
  '--mysqld=--tokudb_load_save_space=ON',
  '--mysqld=--tokudb_load_save_space=OFF'
 ],[
  '--mysqld=--tokudb_loader_memory_size=100000000',
  '--mysqld=--tokudb_loader_memory_size=10000000000'
 ],[
  '--mysqld=--tokudb_max_lock_memory=500000000',
  '--mysqld=--tokudb_max_lock_memory=2086468352'
 ],[
  '--mysqld=--tokudb_pk_insert_mode=0',
  '--mysqld=--tokudb_pk_insert_mode=1',
  '--mysqld=--tokudb_pk_insert_mode=2',
  '--mysqld=--tokudb_pk_insert_mode=3'
 ],[
  '--mysqld=--tokudb_read_block_size=16384',
  '--mysqld=--tokudb_read_block_size=65536',
  '--mysqld=--tokudb_read_block_size=1000000'
 ],[
  '--mysqld=--tokudb_read_buf_size=128000',
  '--mysqld=--tokudb_read_buf_size=131072',
  '--mysqld=--tokudb_read_buf_size=10000000'
 ],[
  '--mysqld=--tokudb_read_status_frequency=10',
  '--mysqld=--tokudb_read_status_frequency=10000',
  '--mysqld=--tokudb_read_status_frequency=1000000'
 ],[
  '--mysqld=--tokudb_row_format=tokudb_default',
  '--mysqld=--tokudb_row_format=tokudb_fast',
  '--mysqld=--tokudb_row_format=tokudb_small',
  '--mysqld=--tokudb_row_format=tokudb_zlib',
  '--mysqld=--tokudb_row_format=tokudb_quicklz',
  '--mysqld=--tokudb_row_format=tokudb_lzma',
  '--mysqld=--tokudb_row_format=tokudb_uncompressed'
 ]
]

