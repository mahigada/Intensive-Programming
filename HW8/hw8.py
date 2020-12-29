# CS288 Homework 8
# Read the skeleton code carefully and try to follow the structure
# You may modify the code but try to stay within the framework.
import sys
import os
import re
import sys
from collections import defaultdict
import mysql.connector
from xml.dom.minidom import parse, parseString
def get_elms_for_atr_val(tag,atr,val):
    lst=[]
    elms = dom.getElementsByTagName(tag)
    for i in range(len(elms)):
        lst.append(elms[i])
    return lst
# get all text recursively to the bottom
def get_text(e):
    lst=[]
    if e.nodeType in (3,4):
        lst.append(e.data)
    else:
        for elem in e.childNodes:
            lst=lst+get_text(elem)
    return lst
# replace whitespace chars
def replace_white_space(str):
   p = re.compile(r'\s+')
   new = p.sub(' ',str)   # a lot of \n\t\t\t\t\t\t
   return new.strip()
# replace but these chars including ':'
def replace_non_alpha_numeric(s):
   p = re.compile(r'[^a-zA-Z0-9:-]+')
   #   p = re.compile(r'\W+') # replace whitespace chars
   new = p.sub(' ',s)
   return new.strip()
# convert to xhtml
# use: java -jar tagsoup-1.2.jar --files html_file
def html_to_xml(fn):
   xhtml_file = os.system('java -jar tagsoup-1.2.1.jar --files %s' % (fn))
   xhtml_file = fn.replace('.html', '.xhtml')
   return xhtml_file
def extract_values(dm):
    lst = []
    text=[]
    l = get_elms_for_atr_val('tr','class','most_actives')
    for e in l:
        row = get_text(e)
        lst.append(row)
    return lst
def make_dict(lst):
    elements=lst[1:]
    myDictList=[]
    for company in elements:
        myDict={}
        myDict["Symbol"]=company[0]
        myDict["Name"]=company[1]
        myDict["Price"]=company[2]
        myDict["Change"]=company[3]
        myDict["Percent_Change"]=company[4]
        myDict["Volume"]=company[5]
        myDict["Avg_Volume"]=company[6]
        myDict["Market_Cap"]=company[7]
        myDict["PE_Ratio"]=company[8]
        myDictList.append(myDict)
    return myDictList
# mysql> describe most_active;
def connect_to_db(l,tbl):
    mydb = mysql.connector.connect(
        host="localhost",
        user="root",
        password="rootpassword",
        database="stocks"
        )
    mycursor = mydb.cursor()
    s = "CREATE TABLE IF NOT EXISTS `" + tbl + "` (Symbol varchar(10), Name varchar(255), Price float, Chng varchar(80), percentChange varchar(80), Volume varchar(80), avgVolume varchar(80), marketCap varchar(80), peRatio varchar(10));"
    mycursor.execute(s)
    sql = "INSERT INTO `" + tbl + "` (Symbol, Name, Price, Chng, percentChange, Volume, avgVolume, marketCap, peRatio) VALUES (%s, %s, %s, %s, %s, %s, %s, %s, %s)"
    val = []
    for item in l:
        val.append((item["Symbol"], item["Name"], item["Price"] , item["Change"], item["Percent_Change"], item["Volume"], item["Avg_Volume"], item["Market_Cap"], item["PE_Ratio"]))
    mycursor.executemany(sql, val)
    mydb.commit()
    print(mycursor.rowcount, "record(s) inserted.")
    mycursor.execute("SELECT * FROM stocks.`" + tbl + "`;")
    rows = mycursor.fetchall()
    return rows
def main():
    xhtml_fn = sys.argv[1]
    fn = xhtml_fn.replace('.xhtml','')
    xhtml_fn = html_to_xml(xhtml_fn)
    global dom
    dom = parse(xhtml_fn)
    lst = extract_values(dom)
    dict1 = make_dict(lst)
    table = connect_to_db(dict1,fn)
    for row in table:
        print(row)
    xml = table
    return xml
# end of main()
if __name__ == "__main__":
    main()
# end of hw7.py