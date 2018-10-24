#!/bin/sh

set -e

initdir=$PWD
backupdir=$PWD/../
targetdir=$PWD/../../

echo "Backup/Compressing current release"

cd $targetdir

zip -r $backupdir/release-backup.zip ./bin/*


cd bin

find . -type f ! -name "*.json" | xargs -r rm


echo "Updating to new version"

cd $initdir

mv bin/* $targetdir/bin/

echo "Finished"




