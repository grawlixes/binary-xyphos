# binary-xyphos
An improved version of "Xyphos," my primitive text file compression algorithm. This algorithm uses "Huffman Coding," an old method of representing binary values, to compress and decompress text files.

# why is it better?
There are several reasons.

    - Efficiency: Huffman Coding, though old, is certainly better than the
      dictionary assignment I used in Xyphos to represent redundancies.
      So, more file space will be saved with binary-xyphos.

	- Time complexity: my old program uses some very primitive string methods
      several times over, making it pretty slow. I expect this one to
      compress in much less time. 

	- Lossless: my old program doesn't conserve the case of letters. This
	  program saves everything.

    - Jack Black: Jack Black is actually a spokesman for Binary Xyphos.
      Sorry, that was a lie.

    - Low-level: Xyphos is written in Python, a high-level interpreted pro-
      gramming language implemented in C. Binary Xyphos is written in pure
      C, so it'll suffer from less overhead.

In fact, these improvements really exist because I am compressing files at 
a lower level. In Xyphos, I tried compressing without considering any
information below text level; in Binary Xyphos, I'm compressing at the
binary level. This showcases both my program's efficiency and my 
top-tier project naming skills.

The only problem I see arising from this new iteration is lack of portability.
I'm not really sure how to address that, but I don't really care - just use C11.

# overhead
To be honest, I actually don't know how much better the overhead will be
for Binary Xyphos vs. original Xyphos. The original Xyphos just placed a lot of
text representing the redundancy dictionary in the top of all files, where Binary Xyphos
will place some bit-level header in all .xyp files. This leads me to believe that
Binary Xyphos will have less overhead in compressed files, but I won't know just
how much until I get a little further.

# info
See this link for more information: https://www2.cs.duke.edu/csed/poop/huff/info/

This program isn't done yet! I just finished the compressor for this program. I ran a 
few test (some automated, some not) to see how efficient and accurate the compression
is, and it looks like the Huffman method worked perfectly. Here's a to-do list.

# to do
COMPRESSOR:

	- Add the total weight of the compressed document so I don't have to
	  deal with a pseudo-EOF character. This will make things a bit easier
	  since I'm trying to support all edge cases and characters.
	- Add more support for Unicode characters. Currently works for ASCII.
	  I haven't tried using Unicode characters yet.
	- Use a Priority Queue to select Huffman nodes while building the tree.
	  This will decrease the time complexity of building the tree from 
	  O(N^2) to O(N lg(N)).
	- Use LZ 77 method on .xyp file compressed data for even more efficiency.
	  I have a plan for this already, but I have a lot to do before I can
	  get started.
DECOMPRESSOR:

	- Start! I'm swamped with exams and homework right now, but I want it
	  to be done (or close to done) before the semester ends. I'm pretty
	  confident that I can finish in this time.
