ed
==

Event-driven framework

Generic purpouse - unlimited parallelization of complex modules.

Example:
Before performing action(delete file) module chould check multiply constraits:
1) Check is device plugged in  (10 ms)
2) Check is path to file exists (10 ms)
3) Check is file exists  (9 ms)
4) Check to valid user permissions (1 ms)

Sequential execution - 30ms
Rational (1,2,4 -> 1,2 -> 3) - 19ms

This goal is achieved by notifying about every events/actions that happens.

0ms USER: SYSTEM, delete file
0ms SYSTEM: Notifing, im going to delete file
0ms (messages to all listening modules: 1, 2, 4)
1ms MODULE_4->SYSTEM: OK
10ms MODULE_1->SYSTEM: OK
(10ms MODULE_2, Path exists)
10ms MODULE_2: MODULE_3, Check file
(10ms message MODULE_3)
19ms MODULE_3->MODULE_2: FAIL
19ms MODULE_2->SYSTEM: FAIL
19ms SYSTEM->USER: Failed cause module 2.
