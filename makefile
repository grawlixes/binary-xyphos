# "make" creates the executables
# "make clean" removes the executables and object files

# the compressor

# usage: "./compress <input> <output>" compresses the input file, where
# 	 the input is a text file and output is the name of the output
#	 file that holds the new binary info and header information.
#	 NOTE: the output file will have ".xyp" appended to it to
#	 ensure it is well-formed for the decompressor

compress : compress.o
	gcc -g -Wall compress.o -o compress
compress.o : compress.c
	gcc -c compress.c

# the decompressor
 
# usage: "./decompress <input>" decompresses the input file, where
# 	 the file is a special ".xyp" file made by the compressor


# test

test : test.o
	gcc -g -Wall test.o -o test
test.o : test.c
	gcc -c test.c

# clean
clean2 : clean
	rm -f *.xyp
clean :
	rm -f compress compress.o test test.o

# instructions go here #
