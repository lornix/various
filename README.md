Various
=======

Various little things to test and try out idea and concepts.

* Makefile: A rather generic Makefile, but suffices to compile most anything

* cling.cpp: someone on [StackOverflow][1] was trying to figure out how to remove all references
    to his class.  Weird.

* eniac_sqrt.c: a rather interesting method used by the original [ENIAC][4] computer to perform
    multi-digit precision [square roots][2] using only adds, subtracts, and decimal point shifts
    (*10, ÷ 10 essentially) [PDF][3] available too. [More ENIAC info][5]

* hello_c.c: symlinked to `hello_cpp.cpp` too, to demonstrate the size difference created by
    compiling with `gcc` vs `g++`.  Less of a difference when using `-Wl,--as-needed`, but
    still... sheesh!

* hello_cpp.cpp: symlinked to `hello_c.c`.

* inot.c: Tinkering with `inotify` functions.  `./inot /etc /usr` will show you every access
    within /etc and /usr subdirs.

* pt.c: Some sample code from somewhere showing how to use ptrace to determine where a program is
    looping.  Interesting.

* regex.cpp: Tinkering with __C++11__'s regex class... kinda cool... kinda huge! Have a look at
    the compiled file size! (Even bigger with debugging symbols!)

* sockclient.c: Playing with sockets, connecting to my router.  No, those aren't my passwords.

* [sockserv.c][]: More sockets... this time a server.

* vector.cpp: Some tinkering code (again, from [SO][1]), playing with various array methods,
    looking for which runs faster.  Also some foray's into steady_clock.

* watchpoint.c: Another sample code from the same somewhere, showing how to use ptrace to monitor
    a particular memory address for accesses and changes.

[1]: http://stackoverflow.com
[2]: http://www4.wittenberg.edu/academics/mathcomp/bjsdir/ENIACSquareRoot.htm
[3]: http://www4.wittenberg.edu/academics/mathcomp/bjsdir/HowTheENIACTookASquareRoot011909.pdf
[4]: http://en.wikipedia.org/wiki/ENIAC
[5]: http://ftp.arl.mil/mike/comphist/eniac-story.html
