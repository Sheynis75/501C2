Functionality of the implant:
1) Authorize/check in with the c2 server
2) Request tasks from the c2
3) Execute those tasks and send back the response to the c2

Implant's life-cycle:
1. get information about the system it is in. (GUID, Computer name, IP addresses)
2. authorize with the c2 (get session id = symmetric key)
3. while active->request tasks, execute tasks and update the c2
4. can also self-destroy if needed

Implant should have:
1. c2's public encryption key & authorize code (could be different for different compaigns)
2. c2's most recent ip address
3. an agreed prime number and generator with the c2 for key exchange
