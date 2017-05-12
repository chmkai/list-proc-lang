# Implementation Discussion #

## Statement Parsing##

Statements are to be read as whole lists represented by an array, transfered to an object `func`. The 0th atom of the list will become the statement _name_ , with the rest of the arguments transfered to the array `func.argv[]`.

On reaching an opening delimiter (`"(","{","["`), the function `parselist()` is executed recursively for each new delimiter, while incrementing a variable, say `c`, holding the number of levels the current function has gone deep.
When the function ends, `c` is decremented, and reading continues as normal until `c = 0`.

For user-defined functions, we first iterate through a list of _pre-defined functions_. If no match is found, it searches the _function heap_, followed by interpreting it as part of the list.

## Pointers ##

Since ordinary pointers would be too large to fit within the function arguments, we will use  a virtual _heap pointer_ which is added to the address of the 0th byte of the heap, the _base address_, to get the required address in the heap.

Strings and data-lists (_arrays_) will be stored directly as character arrays on the _data heap_, terminated by _null characters_ (`\0`).

## The 'Stack' ##
The _statement execution **call stack**_, or _call stack_ for short, is the thing that keeps track of all the recursive statements currently being evaluated.

A stack acts as a LIFO (_Last in, First out_) list, with the most recently added item to be evaluated first. To add an item to the top, we use `push()` , and to take the top-most item away, we use `pop()`.

To implement the stack, we use an object containing an array of `func` objects

## The 'Heap' ##

The _heap_ will act as a virtual _data store_ in which the varaiables and functions (or pointers to them?) will be stored for easy access while passing arguments in lists. _Newly created variables_ will also be initialized here, until deleted.
