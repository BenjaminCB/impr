- could use getchar function until EOF to make sure that stdin is empty. This way you won't have overflow from the last input over to the next one.
- implement response() from eksamen 2
- still no way to emyty stdin
- scan_data prototype has one parameter in camelCase instead of snake_case
- could just make the varialbe input_size a preproccessor constant then i wouldn't need to use malloc either
- scan_data while loop could be changed to a do while loop, but it wouldn't change much
- you could probably be lazy and check the if the input is valid at the very last moment and gain someting computationally, but i think this makes more sense logically
- the reciprocal function is really not needed
- you could really just yeet out of the program in the validate_data or do_next_op function
- rouding starts once you go over a power of 22 this is probably happening in sscanf, it might happen in lower values as well. scanf will round the input value to the nearest exactly representable floating point value.

### fgets()
fgets() reads in at most one less than size characters from stream
and  stores  them  into the buffer pointed to by s.  Reading stops
after an EOF or a newline.  If a newline is  read,  it  is  stored
into  the  buffer.  A terminating null byte ('\0') is stored after
the last character in the buffer.