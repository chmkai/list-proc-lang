# LIST PROCESSOR LANGUAGE (LLP) #
## -- NOTICE : APPROVED COLLABORATORS ONLY -- ##



### Syntax Guide ###

The basic building block of LLP (can someone come up with a better name?) are _lists_.
Lists are groups of elements (known as _atoms_)  to be interpreted by LLP. They are represented by strings , delimited by whitespace , bounded by square-brackets , as shown below:

 `[atom0 atom1 atom2]`

Lists in general will hold an array of values.
For example, a list of the first 3 natural numbers would be,

`[0 1 2]`

Statements are to be formed by using the name of a function as the 0th atom, its arguments being the rest, and using parentheses in place of square-brackets:

`(function arg1 arg2 ... argn)`

For example, a function `cat` to concatenate two stings _Hello_ and _World_ would be:

`(cat "Hello " "World")`

Blocks of code would be represented by braces ` {` and `}`.

```
{
    (statement 1)
    (statement 2)
    (statement 3)
        ...
    (statement n)
}
```

 Every statement placed as a list inside of blocks would be run in order from the first to the last one. Blocks from which a value is to be returned would return the output of the last statement in it. For example:

```
(print
    {
        (defun square (a b) (+ (pow a 2) b))
        (square 5)
    }
)
```
would print `25`, leaving the first statement alone.

LLP _atoms_ will have types:

- num (ordinary numbers)
- char (character variables)
- str (array of chars)
- nil (empty list)

Variables can be assigned using `var` as the 0th atom. For example,

`(var x 5)` creates a variable x of default value 5.

Anonymous functions are created with the `lambda` keyword as the the 0th atom, followed by a _list_ of arguments , and a _list_ **OR** _block_ of elements. For example,

`(lambda (x) (x+1))`

would create an incrementing function.

```
(lambda ()
    {
        (var x (in))
        (var return 0)
        (try (return)
            (print (+ x 1))
        )
        [return]
    }
)
```

In order to create a named function, we simply replace `lambda` with `defun`, followed by the name of the function.

`(defun name (arg) { })`

OR
```
(defun name (arg)
    {

    }
)```

#### Control Structure ####

Conditionals, using the `c` keyword are created as an expression containing 3 atoms:

- Left hand side
- Operation ( `=` , `<` `>`)
- Right hand side

Example:- `(c x = 5 )`

the `if` function , carrying 3 lists , executes the 2nd if the first is true; otherwise it eectues the third:

Example:
```
(if (c (% x 2) = 0)
    (print "It is even")
    (print "It is odd")
)
```

Boolean control gates can be used to alter conditional results :

* `and` - AND gate (&&)
* `or` - OR gate (||)
* `not` - NOT gate  (!)
* `xor` - XOR gate (^)

Example:

* `(and (c x = 5) (c y = 2))`
* `(not (x > 5))`

Testing the success of a statement can be done with `try`. This gives `atom1` the value `1` if the execution of the 2nd statement fails
```
(try (x)
    (print "sdaodosj")
)
```


- - - -
