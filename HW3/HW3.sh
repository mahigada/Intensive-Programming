#!/bin/sh 
#Mahi Gada - CS288 003
grep '</ytd-thumbnail><div' YouTubeIndex.html | 
while read x;
do
    s=`expr "$x" : ".*aria-label=\"\(.*\)\" title=\".*"`
    
    echo ${s} 
done > clips.txt

grep '</ytd-thumbnail><div' YouTubeIndex.html | 
while read x;
do
    s=`expr "$x" : ".*aria-label=\"\(.*\)\" title=\".*"`
    title=`expr "$s" : "\(.*\) by.*"`
    echo ${title} 
done > title.txt

grep '</ytd-thumbnail><div' YouTubeIndex.html | 
while read x;
do
    s=`expr "$x" : ".*aria-label=\"\(.*\)\" title=\".*"`
    user=`expr "$s" : ".* by \(.*\) [0-9].* ago .*"`
    echo ${user} 
done > user.txt

grep '</ytd-thumbnail><div' YouTubeIndex.html | 
while read x;
do
    s=`expr "$x" : ".*aria-label=\"\(.*\)\" title=\".*"`
    upload_time=`expr "$s" : ".* \([0-9].*\) ago .*"`
    echo ${upload_time} 
done > upload_time.txt

grep '</ytd-thumbnail><div' YouTubeIndex.html | 
while read x;
do
    s=`expr "$x" : ".*aria-label=\"\(.*\)\" title=\".*"`
    duration=`expr "$s" : ".* [0-9].* ago \(.* seconds\)"`
    echo ${duration} 
done > duration.txt

grep '</ytd-thumbnail><div' YouTubeIndex.html | 
while read x;
do
    s=`expr "$x" : ".*aria-label=\"\(.*\)\" title=\".*"`
    views=`expr "$s" : ".* seconds \(.*\) views"`
    echo ${views} 
done > views.txt

paste title.txt user.txt upload_time.txt duration.txt views.txt > expr.csv



grep '</ytd-thumbnail><div' YouTubeIndex.html | 
while read x;
do
    s=`expr "$x" : ".*aria-label=\"\(.*\)\" title=\".*"`
    echo ${s} 
done | sed -n 's/\(.*\) by \(.*\) \([0-9].*\) ago \(.*\) \([0-9,].*\) views$/\"\1\",\"\2\",\"\3\",\"\4\",\"\5\"/p' > tb15.csv



grep '</ytd-thumbnail><div' YouTubeIndex.html | 
while read x; 
do 
    s=`expr "$x" : ".*aria-label=\"\(.*\)\" title=\".*"`; 
    echo ${s} | ggrep -P -o '.*(?=by)' 
done > grep-title.txt; 

grep '</ytd-thumbnail><div' YouTubeIndex.html | 
while read x; 
do 
    s=`expr "$x" : ".*aria-label=\"\(.*\)\" title=\".*"`;
    echo ${s} | ggrep -P -o '(?<=by).*(?= [0-9].* ago)' 
done > grep-user.txt; 

grep '</ytd-thumbnail><div' YouTubeIndex.html | 
while read x; 
do 
    s=`expr "$x" : ".*aria-label=\"\(.*\)\" title=\".*"`; 
    echo ${s} | ggrep -P -o '[0-9]+ (week(s?)|month(s?)|year(s?)|day(s?)|hour(s?)|minute(s?)|second(s?))(?= ago)' 
done  > grep-upload_time.txt; 

grep '</ytd-thumbnail><div' YouTubeIndex.html | 
while read x; 
do 
    s=`expr "$x" : ".*aria-label=\"\(.*\)\" title=\".*"`; 
    echo ${s} | ggrep -P -o '(?<=ago).*seconds (?=[0-9].* views)' 
done > grep-duration.txt; 

grep '</ytd-thumbnail><div' YouTubeIndex.html | 
while read x; 
do 
    s=`expr "$x" : ".*aria-label=\"\(.*\)\" title=\".*"`; 
    echo ${s} | ggrep -P -o '(?<=seconds )[0-9].*(?= views)'
done > grep-views.txt; 

paste grep-title.txt grep-user.txt grep-upload_time.txt grep-duration.txt grep-views.txt > expr2.csv