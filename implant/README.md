Functionality of the implant:
1) Authorize/check in with the c2 server
2) Request tasks from the c2
3) Execute those tasks and send back the response to the c2

Implant's life-cycle:
-get information about the system it is in. (GUID, Computer name, IP addresses)
-authorize with the c2 (get session id = symmetric key)
-while active->request tasks, execute tasks and update the c2
-can also self-destroy if needed
