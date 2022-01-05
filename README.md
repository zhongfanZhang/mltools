# ml_tools dev log
## 06 Jan 2022
### Thoughts on DataContainer implementation
I think one of the biggest design flaws of the DataContainer class was that I was too eager to
replicate the _pandas_ library from python which has a vast array of features including dealing with string
elements easily etc. My current design direction is for the DataContainer class to act as a method of reading, processing
data from .csv files to be output as a useful format for use in c++.
#### Regarding the use of std::any
I had been interested in creating a data structure in C++ in which values of different types may be stored.
While this was achieved to a limited extent with std::any, in hindsight, there are many drawbacks to using
this library for this purpose. I had initially implemented this with the use of void pointers.

One of the biggest problems of using std::any is its limitations in terms of retrieving values. In order to
retrieve values from the 2 dimensional vectors of std::anys, I had to use std::any_cast conditionally per element
in the vector. This incurs a heavy performance cost as we would have to first navigate the
if statement to check its type, and then any_cast it to retrieve the value. Furthermore, when the std::any_cast
function is called with a non pointer type argument, it also makes a copy of the argument, incurring further
performance costs.

In hindsight, std::any definitely does not seem like the correct choice for this type of
use case. Data sets used in modern machine learning are usually very large and this method
scales terribly with size.

#### An alternative approach to storing data
My initial implementation of a container that could contain many types was to use an array of
void pointers, each pointing to an array of data of differing types. In order to retrieve the value with the correct type
I used another array to store the types of the data, and another array to store the column headers of the data. 

Another method that I had thought would be interesting to test would be to use a std::map container to store values
in pairs of std::string (column headers) and void* (data arrays). Not only are std::map containers iterable, but they also offer
easy access to values by using the column headers.