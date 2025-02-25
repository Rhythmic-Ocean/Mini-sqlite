# Mini-SQLite

<h3><a href = "https://youtu.be/RKVKSDsSR4A">VIDEO DEMONSTRATION</a></h3>

To get started, compile the `.c` files to create the output executable. Then, run the following command in the terminal:

`./output table1`

This command will create or open table1.csv, allowing you to create one table (i.e., only one table per .csv file).

The Database Management System (DBMS) interface currently supports the following three functions:

    CREATE tablehead tablehead tablehead... (Creates a table header with the specified table heads)

    INSERT tabledata tabledata tabledata... (Adds the specified table data to the table header in order)

    READ ALL (Displays everything in the table)
    
    EXIT (Commit changes (if in read mode, and exit)'


<h2>Repository Overview</h2>

<p>This repository was submitted as the final project for the CS50x 2025 online course offered by Harvard University. It is essentially a mini SQLite database management interface written in C. The application is designed to store data in table formats in .csv files.</p>

For the libraries, I used the usual stdlib.h, stdio.h, string.h, and a library I created on my own, namely “all_thingies.h.” There, I defined various functions that I will be discussing soon.


<h3>main.c</h3>

Here is where my main function resides. First, it checks if the command line argument is acceptable, and once we pass that, the user is given a choice to read or write. The read functionality is only valid if the file already exists; if it doesn’t, the program will display an error message and terminate. If the file does exist, it will move on to the head_read() function and read() function before closing with fclose.

If the user chooses to write instead, the file is still opened in read mode initially to check if it exists, and it prompts the user that a new file has been created if it doesn’t. If the file existed previously, the head_read() function is invoked again, and it reads everything (while the file is in read mode) before we close it and open it in write mode.

<h3>basics.c</h3>

There are several functions in this file. The most intuitive ones are read and write, which are invoked based on the user’s choice of what they want to do with this program. Both have identical structures and are mostly the same except for the fact that write() executes exec_write() and read() executes exec_read(). Both of them contain the functions line_reader() and arg_reader() inside them, which basically read the user’s input under an infinite loop until the user terminates the program with EXIT.

The line_reader() function has an infinite loop inside it that reads input character by character. This function was probably the one that gave me the most headache and thus has become the most memorable for me. Specifically, this part:

`if(count == 1 && c == '\n')
{
    continue;
}`

Here, if it’s the first character and it’s an <enter>, it ignores it. I figured out that for some reason, getchar() was reading ‘\n’ from previous user input and executing

`if (c == '\n') {
    buffer[p] = '\0';
    return buffer;
}`

prematurely, which ended up causing me constant segmentation faults. I was forced to learn the basics of gdb (a C debugging tool) just due to this.

After that, we have the arg_reader() function, which returns an array of strings, i.e., it basically breaks down the user’s input into tokens using strtok based on spaces. For example, if the string is “Samir Khanal,” arg_reader() will return an array of strings, say str[], where str[0] = “Samir”, str[1] = “Khanal”, and str[2] = NULL. The last one would be useful when we process the user’s arguments into memory in array_memory.c before committing it to the .csv file.

I also tried implementing dynamic memory in line_reader() and arg_reader(), and while the one in line_reader() works quite well as I tested it myself, I don’t know about arg_reader() since I don’t think anyone would be using this to store 250+ different columns of data.

Lastly, we have the commit() function. It works as it sounds; after every EXIT command the user types, the commit() function gets invoked and all the changes made will be committed to the .csv file that was open throughout the program’s duration in typical CSV format (with “,” for columns and “\n” for rows). However, if you only open the file for reading, commit() will not run after you EXIT.


<h3>array_memory.c</h3>

I was initially contemplating making this a hash memory, but since I was working with C and this was my first big project ever, I didn’t want to suffer too much, especially not on the memory side with C. So, although suboptimal, I made it work somehow. This is probably the messiest part of my code, and although I have been trying to fix the memory leaks for days, Valgrind still isn’t satisfied.

So, basically, there are two main parts to this function. The first one is head_reader, which, as the name suggests, reads the header of the table (i.e., the first line of the .csv file), and the second one is body_reader, which reads the rest of the table. master_memory_headers is our variable that will store all headers while the row variable of type struct table_row will be storing the data. I initially wanted to have a unique ID associated with each new row (that’s why there is an id variable of type int in all_thingies.h), but it quickly got convoluted, so I abandoned the idea.

Similar to line_reader() and arg_reader() in basics.c, there is also the provision of dynamic memory allocation based on the size of the CSV file for head_reader() and body_reader().

For head_reader(), we first read the entire first line of the .csv file into a variable, tokenize it using the strtok() function with “,” as our delimiter of choice, and finally have it added into our master_memory_header as an array of strings.

Similarly, for body_reader(), we first read (starting from the second line) line by line of the file; after reading one line, we tokenize it and have it added into our row[].column_data[].


<h3>reading.c</h3>

It is basically the printer that prints the entire table. I initially wanted to make it so that the user can read by rows or columns, but I just settled with printing the table in the end. This is a simple function, so there’s not much to explain here. (Although I will definitely add more functionalities once some holidays come around). As of right now, it only handles the “READ ALL” function.

<h3>writing.c</h3>

This also contains a single function (exec_writer), and is arguably the most complicated function in this program. It handles the “CREATE” and “INSERT NEW” functionalities. Here too, I wanted to have “INSERT OLD ….. WHERE…..” initially but quickly gave up on the idea. The first part of this function would be if(.....”CREATE”...), and this involved first determining if master_memory_header and row are already occupied and freeing them manually. Then we have to fill just the header with whatever arguments were passed in with CREATE.

The second part was the else if (.....”INSERT”...) followed by if(.....”NEW”...). All it does is reallocate some more memory into row and row[].column_data[] and add the data the users want to it. Nothing too fancy, though I will probably try again with the INSERT OLD functionality.

<h2>24<sup>th</sup> Feb 2025:</h2>

<h3>Makefile added for easier compilation</h3>

<p>Just found out about this stuff. Now all you need to do is:

    make final`

and you will have compiled the exe file with the name final which you can just run with

    ./final table

Pretty Cool stuff.</p>
