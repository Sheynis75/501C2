# 501C2
Our final project for CS 501 had us build a C2 framework which would be allow us to inject malware into server and control its actions on the victim machine. In order to do so, we needed to create 3 seperate components which make up a framework. These components are as follows:

## C2
The C2, also known as the command or control center, needs to be able to handle connections from multiple operators, and multiple implants. Our C2 was built using flask in python. Once built, we hosted it on a local machine which was then moved to the public DDNS of cs501kai.ddns.net. 
Our C2 has the following features:
-- Uses MySQL database

## Built With
+ [Flask](https://flask.palletsprojects.com/en/2.0.x/)
+ [MySQL](https://docs.oracle.com/cd/E17952_01/mysql-8.0-en/index.html)
+ [Python](https://docs.python.org/3/)
+ [C++](https://docs.microsoft.com/en-us/cpp/?view=msvc-170)
