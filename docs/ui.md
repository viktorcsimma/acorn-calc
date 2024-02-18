## Application windows

### Main window

The main window consists of three panels.

- The first one is a ListView contains history items:
the expressions/statements evaluated on the left,
and their results on the right.
By clicking on them, one can use the result in a next command.
(This can also be achieved by writing history[0], history[1] etc.
That means the last item, the last but one and so on.)
In the upper right corner, there is a "Clear" button.
- The second one contains the input field;
this is what also displays the result, if any
(but after clicking that, it changes to "Ans").
There is also a smaller label
displaying an error message if the evaluation failed,
or the type of the result if we have one.
And on the right, a progress circle so that
one can see that the calculation is still in progress.
On its place, if we do have a (real) result,
there should be a button that opens the "Precise output" window.
- The last one is the numpad.
It also contains a selection list to choose the underlying representation
(Dyadic or Rational).

### "Precise output" window

This has four elements:

- a large, scrollable label in which the approximation is displayed;
- a spin box which contains the number of digits of precision;
- a "Calculate approximation" button; and
- a progress circle.

The "Precise output" window is a child of the main window
(i.e. while it is open,
the main window cannot be closed or otherwise manipulated).

## Other requirements on behaviour

- The `Ans` variable is always set whenever a result is displayed;
regardless of whether another variable has been assigned a value.
- The button linking to the "Precise output" window is only displayed
if there is a result and it is real.
- There is a separate "=" (assignment operator) and "Enter" button
on the numpad.
- When clicking on the input field after getting a result,
the text changes to `Ans`
and it can be deleted immediately by pressing Backspace only once.
- Results are coloured according to their types:
    - booleans are red,
    - integers are blue,
    - rationals are green and
    - reals are purple.
- On the numpad, real literals or functions with a real output
are displayed with a slightly darker background
and purple text.
Their nature is also indicated by a tooltip.
- The Rational option in the list view
is accompanied by the comment `(legacy)`.
- When switching to the "Precise output" window,
there is a long approximation with a default precision
(e.g. 100 digits);
- The "Calculate approximation" button is only enabled
if there has been a change of precision.
- After clicking it, a progress circle appears
until the result is printed;
meanwhile, the scrollable label is visibly disabled.
Instead of the original button, a "Cancel" button is available.

