# singleton_example


**[tl;dr]** Modern C++ best practices allows an explicit and beautiful implementation of the singleton design pattern.

---

Table of Contents
=================

   * [Motivations](#motivations)
   * [Context](#context)
   * [Related work](#related-work)
      * [Blogs and websites](#blogs-and-websites)
      * [Books](#books)
   * [Introduction](#introduction)
      * [About design patterns](#about-design-patterns)
      * [The singleton pattern](#the-singleton-pattern)
         * [Why using a singleton](#why-using-a-singleton)
         * [How to implement a singleton](#how-to-implement-a-singleton)
   * [The SysInfo class](#the-sysinfo-class)
      * [The SysInfo class declaration](#the-sysinfo-class-declaration)
         * [Constructor and assignment](#constructor-and-assignment)
         * [Copy constructor and assignment](#copy-constructor-and-assignment)
         * [Move constructor and assignment](#move-constructor-and-assignment)
      * [Singleton functionality](#singleton-functionality)
      * [SysInfo functionality](#sysinfo-functionality)
         * [Log level](#log-level)
         * [Print method](#print-method)
         * [Output setting](#output-setting)
         * [Output protection](#output-protection)
         * [SysInfo class final result](#sysinfo-class-final-result)
      * [Test application](#test-application)
         * [Global parameters](#global-parameters)
         * [Test routine](#test-routine)
         * [A small exception](#a-small-exception)
         * [Main function](#main-function)
         * [Test application final result](#test-application-final-result)
   * [Experimentation](#experimentation)
      * [GitHub repository](#github-repository)
      * [Compilation](#compilation)
      * [Execution](#execution)
   * [Conclusion](#conclusion)
      * [Summary](#summary)
      * [Limitations](#limitations)
      * [Future work](#future-work)

---

# Motivations

I want a C++ Class that I can use on the desktop to detect hardware info such as the amount of available RAM, installed graphics card, 
CPU, instruction set support on the CPU and other such things that a desktop application may need to know. 

I want it to be pure C++ so that I can use it anywhere and not have to rely on a framework. 

I want to build it in CMAKE so that I can compile it on Mac and Windows programmatically from the command line and not be beholden 
to an IDE such as Visual Studio on Windows or XCode on MacOS

I want it to be a singleton class and use it as a sort of global utilities tool for making requests about the state of the machine. 

---

# Context
I mainly have worked in graphics applications on the desktop over the past 5 years, I would like a nice class, hardy utility library
for accessing the computer hardware that is well designed and reusable.

---

# Related work

Here is a non-exhaustive list of resources among my favorite blogs and sites, as well as some books I have read, which I find appropriate for this article.

All these resources are much more professional and educational than my work, and I highly recommend them if you want to go further.

&nbsp;

## Blogs and websites

* I copied the much of the structure and design of this singleton from [here](https://github.com/hnrck/singleton_example)
* [C++ Programming: Code patterns design](https://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns)
* [Fluent\{C\+\+\}](https://www.fluentcpp.com/)
* [Andrzej's C++ blog](https://akrzemi1.wordpress.com/)
* [The view from aristeia](http://scottmeyers.blogspot.com/)
* [ISO C++ blog](https://isocpp.org/blog)
* [C++ Core guidelines](https://github.com/isocpp/CppCoreGuidelines)

&nbsp;

## Books

* [The C++ Programming Language](http://www.stroustrup.com/4th.html)
* [Design Patterns: Elements of Reusable Object-Oriented Software](https://www.oreilly.com/library/view/design-patterns-elements/0201633612/)
* [Programmer en langage C++](https://www.editions-eyrolles.com/Livre/9782212673869/programmer-en-langage-c)
* [Effective Modern C++](https://www.oreilly.com/library/view/effective-modern-c/9781491908419/)
* [Safe C++](https://www.oreilly.com/library/view/safe-c/9781449321338/)
* [C++ Concurrency in Action](https://www.manning.com/books/c-plus-plus-concurrency-in-action)

---

# Introduction

## About design patterns

In software engineering, [design patterns](https://en.wikipedia.org/wiki/Software_design_pattern) are software bricks, recognized as good practice, and addressing common design issues.

There exist many design patterns, and most of the time, we think first and foremost of the [GoF design patterns](http://wiki.c2.com/?GangOfFour).

Design patterns can be split into different categories, in simple words:
* Creational patterns - these are the design patterns that deal with the creation of objects, which requires particular control.
* Structural patterns - these are the design patterns that deal with the relationships between software entities.
* Behavioral patterns - these are the design patterns that deal with the communication and behavior of objects.

But we can still hear about concurrency patterns or even anti-patterns.

&nbsp;

## The singleton pattern

The [singleton](https://en.wikipedia.org/wiki/Singleton_pattern) is a member of the creational patterns.

This is one of the most straighforward patterns, and it aims to ensure that there is only one instance of a given class.

### Why using a singleton

The singleton is used when you need to have the same object to perform specific actions.
The singleton is also very often used in the implementation of other design patterns.

Besides, the singleton makes it possible to maintain a global state without going through a global variable and saves time and allocation space.

### How to implement a singleton

The object should only exist in one instance, so the constructor of its class is inaccessible, and an interface is provided.
The interface  builds the object on the first call, and always returns the same instance to those who call it.

The following class diagram illustrates this mechanism:

![singleton class diagram](https://hnrck.io/static/assets/img/blog/cpp/singleton_example/singleton.png "Singleton class diagram")

In this diagram, the instance is a Singleton object belonging to the Singleton class.
The `get_instance` class method allows to build this instance on the first call, via the private constructor, and to return this same singleton every call.

---

# The SysInfo class


&nbsp;

## The SysInfo class declaration

The first step in creating a class in C++, its declaration.

```cpp
class SysInfo final {
};
```

Since C++11, the specifier [`final`](https://en.cppreference.com/w/cpp/language/final) can be added to classes.

This specifier will be useful at the design level.
It explicitly prohibits inheritance from the specified class.

This deletion of the inheritance is entirely relative, an evil developer wishing to inherit from this class will be able to delete the `final` and do what he wants, nevertheless, it allows to make explicit the desire of the initial developer.
It might be tricky to adapt our singleton into an inherited class, and it is easier to redesign if necessary, for instance by using a singleton adapter.
A developer wanting to manipulate this part of the code will see that the original developer has not planned to allow the inheritance of his class, without having to integrate this into comments, and a less experienced developer will be protected at compilation time.

### Constructor and assignment

The necessary elements of a C++ class are [constructors](https://en.cppreference.com/w/cpp/language/initializer_list) and [destructors](https://en.cppreference.com/w/cpp/language/destructor).
By default these are generated by the compiler, and public.

Here we have subtleties that make us want the explicit declarations: we want to hide the constructor.

```cpp
 private: // Private default constructor.
  SysInfo() = default;

 public:

  // Default sysinfo destructor. No need for virtual destructor as the sysinfo
  // class cannot be inherited.
  ~SysInfo() = default;
```

C++11 introduces new mechanisms for declaring constructors and destructors, the [`= default` and `= delete` specifiers](http://www.stroustrup.com/C++11FAQ.html#default).
The first one explicitly generates a default function, will the second delete a function.

In the previous snippet, the constructor, declared by default, is hidden in the private part of the class.
The compiler should have generated a default constructor implicitly, as there is no other constructor in this class, but this one would have been publicly accessible.

The destructor is free to access. 
It's a design choice.
Making it private would have prevented a user from deleting the instance that everyone uses, but some compilers don't know how to handle private destructor.
In this specific case, I trust users more than compilers.

One could also have not make the destructor explicit, the compiler would have generated one, but from my point of view, it is cleaner to express all constructors and destructors in a class whose creation and destruction mechanisms are essential, and this is the case of the singleton which is a creational pattern.

Finally, it is useless to declare the `virtual` destructor since we have defined our `final` class, and none can inherit it.


### Copy constructor and assignment

Singletons must not be copyable, and only the `get_instance` interface must allow access to the instance.
By default, the compiler will generate [copy constructor](https://en.cppreference.com/w/cpp/language/copy_constructor) and [copy assignment](https://en.cppreference.com/w/cpp/language/copy_assignment), so we have to handle their declaration.

```cpp
 public:
  // Deleted copy constructor.
  // Only the get_instance class method is allowed to give a sysinfo.
  SysInfo(const SysInfo &) = delete;

  // Deleted copy assignment.
  // Only the get_instance class method is allowed to give a sysinfo.
  void operator=(const SysInfo &) = delete;
```

In an earlier version of C++, one would have put these constructors and assignments in the `private` part of the class, as we did to the constructor, but C++11 allows a cleaner method to prevent the use of copy.

The `delete' specifier that we have seen in the previous sub-section allows us to remove these functions explicitly.
They are therefore not only inaccessible, they no longer exist, even for the singleton.

### Move constructor and assignment

This part is not mandatory, but as I wrote above, the singleton is a creational pattern, and all its construction, destruction and assignment mechanisms should be made explicit.
We will also make the [move constructors](https://en.cppreference.com/w/cpp/language/move_constructor) and [assignments](https://en.cppreference.com/w/cpp/language/move_assignment) explicit.

There is no need to delete the latter.
Once an instance has been provided to a client, the client can do whatever he wants with it, including transferring the instance.

```cpp
 public:
  // Default move constructor.
  SysInfo(SysInfo &&) noexcept = default;

  // Default move assignment.
  SysInfo &operator=(SysInfo &&) noexcept = default;
```

Just as we did for the destructor, these are `public` and `default`.
Only one subtlety, the presence of the [`noexcept` specifier](https://en.cppreference.com/w/cpp/language/noexcept_spec).

Since C++11, a function can be specified whether it could throw exceptions or not.
Defaulted functions can potentially throw an exception.
By adding the `noexcept` specifier, move constructor and assignment are explicitly non-throwing.

No specifying `noexecpt` is not a problem in our design since STL libraries containers choose copy constructors and assignments instead of move ones, unless they are marked `noexcept` or the copy constructor is not accessible, which is our case.

&nbsp;

## Singleton functionality

The two crucial elements of implementing a singleton are its instance and its interface.

For the interface, we implement a class method that will initialize the instance at the first call, and return this instance at each call.

```cpp
 public:
  // Initialize the SysInfo singleton once, and return it each time this class
  // method is called.
  static SysInfo &get_instance();
```

[`static` is the keyword](https://en.cppreference.com/w/cpp/language/static) used in C++ to declare a class method, and the return type is `SysInfo &`, a reference to the instance.

At the level of the instance implementation, C++ allows to hide it apart from its attributes.
The instance can be linked to the class method `get_instance`:

```cpp
SysInfo &SysInfo::get_instance() {
  // The sysinfo variable is initialized once with a move assignment of a sysinfo
  // object build with the private constructor.
  static auto &&sysinfo = SysInfo();
  return (sysinfo);
}
```

Variables declared with the [`static` specifier](https://en.cppreference.com/w/cpp/language/storage_duration#Static_local_variables) have static storage duration.
They are initialized the first time the execution goes through the declaration.

[`auto` is a variable specifier](https://en.cppreference.com/w/cpp/language/auto) which means that the type of the variable will be deduced from its initializer.

The [`&&` token](https://en.cppreference.com/w/cpp/language/reference) is used to mean an rvalue reference.
An rvalue reference behaves like an lvalue reference, but can be bind to a temporary rvalue.
The initialized object that would have been a temporary object copied can now be moved in our variable.

`SysInfo()` is the SysInfo class private constructor, creating the sysinfo object.

`static auto &&sysinfo = SysInfo();` means that the first time the declaration is executed, a sysinfo object will be created by the private constructor, and moved into the sysinfo variable, which is deducted to be a sysinfo object.

From the compiler's point of view `static auto &&sysinfo = SysInfo();` will be translated into `static SysInfo &&sysinfo = SysInfo();`.
I remain satisfied with the disappearance of the bureaucratic aspect of rewriting the class name several times to declare it, then initialize it with its constructor.

__Note:__

It would also have been possible to call the private constructor directly:

```cpp
  static SysInfo sysinfo;
```

From my point of view, this is a bad practice.
I want a consistent language. 
I like that all my variable declaration are:

```cpp
[static] [const] auto [&[&]] <name> = <initializer>;
```

Language is consistent, it makes it impossible for objects to be uninitialized, and this is way more stylish.

I recommend you this [great article](https://herbsutter.com/2013/08/12/gotw-94-solution-aaa-style-almost-always-auto/) from Herb Sutter.


&nbsp;

## SysInfo functionality

### Log level

C++ inherits from C a straightforward mechanism for a set of constants declaration.

```cpp
 public:
  // The different sysinfo levels.
  enum level : unsigned char {
    INFO,
    WARN,
    ERROR,
  };
};
```

Three unsigned char constants are declared, with respectively 0, 1 and 2 as value.

### Print method

The print method will take one of the enum level constants as entered, as well as a message.
There's nothing particular here.

```cpp
 public:
  // Print a message with a certain sysinfo level on the output.
  void print(enum level level, const std::string &message);
```

This method is implemented as follow:
```cpp
void SysInfo::print(SysInfo::level level, const std::string &message) {
  // Initializing a string stream.
  auto ss = std::stringstream();

  // Buffering the log level in the string stream.
  switch (level) {
    case (INFO):ss << "INFO";
      break;
    case (WARN):ss << "WARN";
      break;
    case (ERROR):ss << "ERROR";
      break;
  }
  // Buffering the message in the string stream.
  ss << ": " << message;

  if (p_output_ != nullptr) {
    // If the output is set, then display the string stream.
    (*p_output_) << ss.rdbuf() << std::endl;
  }

  // In a real application, log might also be saved in file.
}
```


### SysInfo class final result

&nbsp;

## Test application 

WIP 

### Global parameters
wip

```cpp
// An arbitrary maximum number of threads.
#define MAX_NB_THREADS 1000
```

### Test routine


### A small exception



### Main function

All the bricks are now ready for our application.
First, we start the main body, and set the future exit code:

```cpp
int main(int argc, char const *argv[]) {
  // Initializing the program exit code, success by default.
  auto exit_code = int(EXIT_SUCCESS);
```

Then we retrieve the instance of our SysInfo,:


Finally, if everything went well, we can leave the execution of the program.

```cpp
  // Exiting the program with the exit code.
  return (exit_code);
}
```

### Test application final result
wip

---

# Experimentation

## GitHub repository


The GitHub repository is structured as following:
```
.
????????? app
??????? ????????? main.cpp
????????? CMakeLists.txt
????????? include
??????? ????????? SysInfo.h
????????? LICENSE
????????? srcs
    ????????? SysInfo.cpp
```


&nbsp;

## Compilation

```bash
cd singleton_example
mkdir build
cd build
cmake ..
cmake --build . 
```

These commands build the sysinfo library `libsysinfo.so.1.0.0` in `singleton_example/build/usr/lib/` and an executable `main` in `singleton_example/build/usr/bin/`.

*Alternative*

As a huge big fan of clang and ninja, I use the following commands.
In the future, I will try to make an article to explain my tool preferences.

```bash
cd singleton_example
mkdir build
cd build
cmake -G "Ninja" -DCMAKE_CXX_COMPILER=clang++ ..
cmake --build . 
```

&nbsp;

## Execution

From `singleton_example/build/`, the main application can be executed with:

```bash 
usr/bin/main <number of thread> 2> <log file>
```

Where `<number of thread>` is a number from 0 to 1000. Trying to enter incorrect values causes errors, but that is not the point of this article
And `<log file>` is the file where the log will be written

*Note:*

```bash 
usr/bin/main <number of thread>
```

*Will output the logs in the terminal.*

For instance:

```bash 
usr/bin/main 10 2> log.txt
```

returns on the terminal:

```
SysInfo singleton example.
Take a number of thread from first argument (from 0 to 1000), and execute concurrently simple routines.
Setting the sysinfo output to std::cerr, so the log can be extracted and saved in a file.
Creating  and joining 10 threads.
All the threads finished their routines.
Done with success.
```

and `log.txt` contains:

```
WARN: this is the message n?? 1.
INFO: this is the message n?? 0.
ERROR: this is the message n?? 2.
INFO: this is the message n?? 3.
WARN: this is the message n?? 4.
ERROR: this is the message n?? 5.
INFO: this is the message n?? 6.
WARN: this is the message n?? 7.
ERROR: this is the message n?? 8.
INFO: this is the message n?? 9.
```

Video of the demo on [asciinema](https://asciinema.org/a/6FnXYa8zZV1tpdK2RyxAF7Xbm):

[![asciicast](https://asciinema.org/a/6FnXYa8zZV1tpdK2RyxAF7Xbm.svg)](https://asciinema.org/a/6FnXYa8zZV1tpdK2RyxAF7Xbm)
<!-- ![demo](/static/assets/img/blog/cpp/singleton_example/demo.gif "demo") -->
<!-- <p align="center"> -->
<!--   <img src="/static/assets/img/blog/cpp/singleton_example/demo.gif" height="1000" width="968"> -->
<!-- </p> -->

---

# Conclusion

## Summary

I hope you had as much fun reading this article as I did writing it.

Design patterns are essential building blocks of software engineering.
In this article, we presented one of the most simple design patterns, the singleton.

C++ does not have direct support for these design patterns, and recent modernizations do not provide this support.
Nevertheless, modern C++ best practices allow an explicit and beautiful implementation of the singleton design pattern.

&nbsp;

## Limitations

First of all, the singleton I decided to illustrate in this article is often considered as bad practice.

Then, the SysInfo class and main application I built are very simplistic examples. The Internet is full of examples of more interesting applications.

&nbsp;

## Future work

In any order, I would like to write articles about other design patterns implementation, write articles about the C++ tools I used, and write articles about my C++ preferred resources.

---
