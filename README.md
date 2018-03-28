# Sapeint Logger  

  Sapeint Logger is a small, but robust and extensible, logging library for usage in C code. 

### _!! WARNING !!_  
This library is _NOT_ thread safe, to the best knoweldge of the authors. However, if you wish to use it make sure you write your own logging function, and handle the threading stuff. Otherwise it is at your own risk.


#### Dependencies  
* GCC (if you wish to use the makefile)
* Doxygen (if you wish to generate the documentation/man files)

#### Installation
_Linux_
1. Run `git clone https://github.com/sapeint/sapeint_logger.git`
2. Run `make && make install`

#### Usage
1. Install it or include logger.c and logger.h in your project tree
2. Include `sapeint_logger.h` if you used `make install`, otherwise include `logger.h`
3. Read through the Docs

## QnA

#### Is this thread safe?  
*NO!* 

#### Really?  
Yes, at least to the knowledge of the author. It is possible that this is thread safe, but it has not been tested or confirmed. If you require thread safety, you will have to write your own log function, use the USER type, and register your own function through the interface.

#### Will you make it thread safe?  
Potentially, however it is not a high priority at this time, nor do I know what I would need to do in order for me to make sure it is thread safe.

#### Why not implement a syslog interface or something?  
This is mainly for those that don't use syslog, and syslog is platform dependent in any case. This is also why you can register your own free and log functions. Just use the USER type.

#### Why do you have a USER type anyway?  
It's to allow for a person to extend the library in a project that might require it. 

#### Doesn't the USER type increase complexity?  
Yes, but not by that much. It only adds in 22 LoC at most, and is only ~18% of the codebase. So removing it only removes a small portion of the code, and the upkeep is extremely negligible, given that most of the code is relatively simple.

## Copyright and Licensing  
All Copyright belongs to their respective owners. 

This code is licensed under the MIT/Expat License, found in LICENSE.
