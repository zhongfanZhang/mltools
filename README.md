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

## 09 Jan 2022
### Updates today:
- Implemented a combined DataContainer::filter function function that also outputs the associated class labels as strings
- Implemented DataContainer::set_target so that one column can be removed and set as the class labels
- Changed the DecisionTree::write_node function so that it will calculate the class label itself
- Started implementation on DecisionTreeClassifier
### Thoughts on class design
At this point the DataContainer class is beginning to bloat. I am shifting away from my initial design which was for the DataContainer and ML methods classes to interact
similarly to _pandas_ and _sklearn_ from Python for the following reasons.
#### A person using a C++ library will use it very differently as they will python libraries in a Jupyter Notebook:
When I started development on the DataContainer header, my goal was for it to behave similarly to _pandas_, it will read, process, and provide methods for exploratory data analysis. However, one major downside of conducting exploratory data analysis in C++ as opposed to in python (in a Jupyter Notebook) is that one would have to change their code and recompile with every single step of the exploration. However, C++ has other strengths such as performance (if implemented correctly).

One interesting project in this direction could be to write an event driven ml tool in C++ in which the user can load files and input commands.
#### C++ has different strengths to python:
Instead of mimicking a python library, my new direction is to only implement features that are critical to machine learning models and focus my time on optmisation. The DataContainer class won't be a clone of _pandas_ in C++, it will be a C++ container purposed to make it easier to implement the various machine learning models. This will mean that there will be less functions (such as display()) intended for human users.
