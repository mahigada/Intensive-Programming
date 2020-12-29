#!/bin/bash
for ((i=0;i<60;i++)); do
    cdate=`date +"%Y_%m_%d_%h_%M_%s"`
    index_page='https://finance.yahoo.com/most-active'
    wget -O yahoo_${cdate}.html $index_page
    python3 hw8_2.py yahoo_${cdate}.html
    sleep 60 
done