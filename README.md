ed
==

Event-driven framework<br>
<br>
Generic purpouse - unlimited parallelization of complex modules.<br>
<br>
Example:<br>
Before performing action(delete file) module chould check multiply constraits:<br>
1) Check is device plugged in  (10 ms)<br>
2) Check is path to file exists (10 ms)<br>
3) Check is file exists  (9 ms)<br>
4) Check to valid user permissions (1 ms)<br>
<br>
Sequential execution - 30ms<br>
Rational (1,2,4 -> 1,2 -> 3) - 19ms<br>
<br>
This goal is achieved by notifying about every events/actions that happens.<br>
<br>
0ms USER: SYSTEM, delete file<br>
0ms SYSTEM: Notifing, im going to delete file<br>
0ms (messages to all listening modules: 1, 2, 4)<br>
1ms MODULE_4->SYSTEM: OK<br>
10ms MODULE_1->SYSTEM: OK<br>
(10ms MODULE_2, Path exists)<br>
10ms MODULE_2: MODULE_3, Check file<br>
(10ms message MODULE_3)<br>
19ms MODULE_3->MODULE_2: FAIL<br>
19ms MODULE_2->SYSTEM: FAIL<br>
19ms SYSTEM->USER: Failed cause module 2.<br>
<br>