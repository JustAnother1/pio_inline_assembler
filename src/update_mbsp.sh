#!/bin/bash

# update the hardware abstraction layer (HAL) from the
# microcontroller board support package (MBSP) service.
# https://mbsp.nomagic.de/

# 'http://localhost:2323/mbsp'

wget --post-file cfg.json \
 --header='Content-Type:application/json' \
 --output-document=mbsp.zip \
 'https://mbsp.nomagic.de:2323/mbsp'

#wget --post-file cfg.json \
# --header='Content-Type:application/json' \
# --output-document=mbsp.zip \
# 'http://localhost:2323/mbsp'

returnCode=$?
echo "res: $returnCode"
if [ $returnCode -eq 0 ]
then
  echo "OK"
else
  echo "Failed !"
  exit 1
fi


unzip -o mbsp.zip

returnCode=$?
echo "res: $returnCode"
if [ $returnCode -eq 0 ]
then
  echo "OK"
else
  echo "Failed !"
  exit 1
fi

rm mbsp.zip
git restore .cproject
git restore .project

echo "Result:"
cat mbsp_report.txt
if grep -q "successful = false" "mbsp_report.txt"; then
    echo "!!!!!!!!!!!!!!!!!!!!!"
    echo "!!!! MBSP failed !!!!"
    echo "!!!!!!!!!!!!!!!!!!!!!"
else
    echo "Done!"
fi
