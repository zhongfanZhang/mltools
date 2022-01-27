# ml_tools dev log

## 16 Jan 2022 - Inheritance vs Composition
### Current Design Direction
Currently, the plan is to store data in the DataContainer class in std::map containers, a column key will be mapped to a vector of numeric values. String data will still be supported as the 'label' column, but it will not be supported for learning data. This will improve performance by removing the need to use std::any_cast whenever any data needs to be accessed, this will also provide easier access to columns through the use of column names.

### Concerns with Composition
However, as there will be a training data set, a testing data set, a vector of labels for the training data set as well as for the testing data set, a large amount of access functions will be required if I were to compose, for example the DecisionTreeClassifier class with the DataContainer class. Not only will I have to have access functions for the columns, there will also be a need to get rows and columns are filtering, getting unique values from each row, etc.

This can be solved using the friend keyword in C++, however, this will result in the DataContainer class having a long list of friend classes once more models are implemented. However, the advantage of this is that DataContainer will be able to be used in its own right, which also improves the reusability of the DataContainer class. However, if I were to continue with the current design, the DataContainer class can still be extended to have a class in its own right.

### Concerns with Inheritance
Using an inheritance model is not without its concerns either. After doing some research on the topic, it seems that many programmers recommend the use of composition over inheritance as a rule of thumb. 

My major concern with using multiple inheritance is that classes that represent the machine learning models, through their multiple inheritance will have an extremely large amount of members. While each individual class may not appear to be bloated, the aggregates of these base class will be inheriting members left right and center, if exceptions and bugs are not well captured, it may be even more difficult to debug in the future.

Another major concern is that scalability is not possible with the current design where a machine learning model 'owns' their respective data sets. For example, if I expose the data set to another model through a copy, memory is being wasted, however, if I expose it by reference, then the other model may make unwanted changes to the data, causing the original owner of the data to malfunction - this will be highly dangerous and hard to debug. 

### Decision and Moving Forward - Inheritance and a touch of Composition
I have decided to use inheritance over composition for the following reasons:
- **Data Member Access**: While I can use a friend access modifier to provide easy data access, this will defeat the purpose of encapsulation and potentially create problems when the project is scaled up, therefore, the DataContainer class will be extremely bloated by all the data processing methods, getters and setters that all the models will be requiring
- **Extensibility of DataContainer**: a derived class can be used to create a class purely for data processing manually, once this has been done, the machine learning models can be updated to work with this new class as well.
- **Scalability**: In order to support a machine learning solution architechture that will involve a number of different models sharing the same data, the current plan will be to use a ensemble class. This class will be a composition of machine learning models and will provide methods to facilitate ensemble learning and secure data sharing.
- **Bloat through multiple inheritance**: This is a difficult problem to solve as of now. My current plan is to simply go along with multiple inheritance with preventing code bloat and exception leaks between classes in mind.

## 15 Jan 2022 - The beginning of a new chapter
### Overhaulling class design
Over the last couple of days, I have been conducting experiments with C++ inheritance and polymorphism in order to implement a more C++
like machine learning tool set. Instead of having classes that interact with each other in the manner of the interactions between _pandas_ and _sklearn_, a class that contains similar functions as the DataContainer class will become a base class for machine learning models. To avoid bloating of the base class, multiple inheritance can be used for each individual type of machine learning model. For example, algorithms that use distance metrics such as kmeans, mean shift, and k-nearest-neighbour can inherit from both the DataContainer-like base class as well as a distance metric based algorithms base class.

Comparatively, in the previous model where data and the model is separate, the DataContainer class is becoming increasingly bloated to cater to the needs of various machine learning algorithms. Furthermore, code-reusability is improved significantly as common data wrangling functions will simply be inherited from the base class.

### Overhauling DataContainer design
While std::any is an extremely interesting library that allows the storing of different types in one vector, it costed dearly in terms of performance. I found that it had the following advantages in this use case:
- Allowing the storage of various types within one vector
- Allowing us to keep the data in the format that it was read in without requiring any (pun not intended) additional engineering
However, the advantages are only important if we desired a jupyter-notebook-like end product where we have a persistent global stack that we can use. This is however, not the strength of a C++ application as we would need to re-compile, reload the data, and redo all calculations every single time a change is made to the code. As such, a C++ library would serve a vastly different purpose compared to a library purposed for the jupyter notebook environment. 

As such, the new design of the DataContainer class will no longer involve std::any, this will likely result in significant performance improvements for processing larger datasets as std::any_cast will no longer be needed to access every element.

### The positive impact of the Overhaul
While we take a step backwards from implementing a Jupyter Notebook like C++ application (which was not the original intention anyway), the above changes are expected to improve the following aspects of the mltools codebase:
- **extensibility**: similar machine learning models will be able to be implemented more efficiently by reusing code from their base class of machine learning models
- **maintainability**: reducing code bloat and the scope that the DataContainer class has to cover will also make it easier to pin-point potential bugs 
- **usuability**: removing the need for users to process data and pass the DataContainer to machine learning models means that users are less likely to encounter problems.

### An assessment of the impact of the Overhaul on workload
While I will require time to refactor the codebase, this will require a significantly shorter amount of time compared to the almost certain maintainability and extensibility problems that the current design will cause. Many of the functions in the current code base may still be reused with small tweaks.

### Goals Moving forward
- Refactor the mltools codebase according to the new class design
- Explore documentation generation tools with visual studio 2022 (doxygen plugin & class diagram feature)
- Explore Microsoft Azure DevOps services (Private project already set up with this repository)

## 09 Jan 2022 - a short, critical reflection on class design
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

## 06 Jan 2022 - a reflection on std::any
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
