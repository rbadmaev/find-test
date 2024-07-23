# mtfind

mtfind is a program that performs substring search in a text file using a wildcard pattern with multithreading.

## Usage

To run the program, use the following command:
<pre>  
mtfind [file_path] [pattern]  
  
</pre>
- [file_path]: The path of the input file to search in.
- [pattern]: The wildcard pattern to search for. Use "?" to represent any single character.
## Example

Suppose we have an input file named "input.txt" with the following content:
<pre>
I've paid my dues
Time after time.
I've done my sentence
But committed no crime.
And bad mistakes ?
I've made a few.
I've had my share of sand kicked in my face
But I've come through.
</pre>

To search for the pattern "?ad" in the file, we can run the following command:
<pre>
mtfind input.txt "?ad"
</pre>

The expected output would be:
<pre>
3
5 5 bad
6 6 mad
7 6 had
</pre>

This indicates that the pattern was found in line 5 at index 5, line 6 at index 6, and line 7 at index 6.
