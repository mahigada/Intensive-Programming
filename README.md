# Intensive-Programming

>HW1: 
>>count.sh - builds a table of counters for the commands under /bin in alphabetical order.
>>reverse.sh - reverses the contents of a directory passed as a parameter.
>>filter.sh - prints those files/directories that have the size greater than the average file size of the directory. 
>>insert-sort.sh - sorts a list of command line parameters in ascending order.
---
>HW2:
>>create.sh - creates a directory tree with depth d and breadth b in a programmable depth/breadth-first fashion, where depth-first or breadth-first can be crontrolled by a command line parameter. Depth refers to the level of the directory tree while breadth refers to the number of directories a directory may have. Use d and b between 3 and 5 inclusive for testing purposes. 
---
>HW3:
>>Download the index page manually saving it. Extract the lines that contain the strings with information: titles, user, upload_time, duration, views. Save that lines to clips.txt. Construct a csv table with five columns: titles, user, upload_time, duration, views. Use while, read, expr, cut and paste commands, as discussed in class. First extract titles and save to titles.txt. Do the same for the remaining four fields, save them to four files: users.txt, upload.txt, duration.txt, views.txt. Now you have files each of which containing useful information. titles, user, upload_time, duration, views. Use paste command to construct a CSV table of five columns: titles, user, upload_time, duration, views. Construct a csv table with five columns using grep with look-ahead '(?=)' and look-behind '(?<=)' and '\K.' Create five seperate txt files using five sepereate grep commands. Use paste command to construct a CSV table of five columns. Construct a csv table with five columns using one-liner sed with backreferences, as demonstrated in class.
---
>HW4:
>>Write a C program that prints a memory map.
---
>HW5:
>>Use the CSV file (comma sepearated value file) you created in HW3, where each line consists of titles, user, upload-time, duration, and views. Since titles and users may contain commas, you need to convert those pre-existing commas to something else such as MY_COMMA or something of that sort. Later on you can revert MY_COMMA back to real commas when everything is said and done. Use strtok() function to split a line into five fields with "," as the delimiter. As cautioned above, you need to convert commas to something else which can then be reverted back to commas after you have built a list.
---
>HW6:
>>Write a C program to implement and compare four sorting functions: selection(slowest but simple), merge (moderate), integer radix and float radix sort (fast but simple).
---
>HW7:
>>Design and implement a C program for three search strategies: depth first, breadth first, and intelligent search. For intelligent search, use the heuristic function and values f,g,h, to be disucssed in class.
---
>HW8:
>>Write a Bash script to download the stock web page every minute for an hour. Make sure you do this between 9:30 am and 4 pm when the values change. Your bash script will call a python program.
---
>HW9:
>>Write two C programs for computing dot product that will run on any number of cores or comptuers using MPI. The two versions are: (a) point to point comunication using MPI_Send() and MPI_Recv() and (b) collective communication using MPI_Scatter() and MPI_Gather() as we will discuss in class shortly. Use the following MPI constructs.
