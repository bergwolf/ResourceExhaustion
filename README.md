# C
## mmap Creation
```
Allocated map: 65514, 0x7f4602757000
mmap: Cannot allocate memory
```

However, the system does not seem to lock like for Java; same user can run another mmap test:
```
cwb@laptop$ (./a.out | tail -1) & (./a.out | tail -1)
mmap: Cannot allocate memory
mmap: Cannot allocate memory
121126: Allocated map: 65514, 0x7f93dae09000
121128: Allocated map: 65514, 0x7fbce487a000
```

## Thread creation
### VM
Very unscientific way to see around which thread (order of magnitude?):
```
cwb@laptop$ $ (./a.out & while true; do pgrep -f ./a.out  >/dev/null || break ; done; echo "No more a.out" > /dev/stderr) 2>&1 | egrep -B1 -A1 "Resource temporarily unavailable|No more a.out"
After Thread 13735
Afterbash: fork: retry: Resource temporarily unavailable
 Thread 13736
--
After Thread 298827
After Threabash: fork: retry: Resource temporarily unavailable
d 298828
--
Boom
No more a.out
```

### Docker:
* Nice explanation of [Containers](https://www.slideshare.net/jpetazzo/anatomy-of-a-container-namespaces-cgroups-some-filesystem-magic-linuxcon)
* Very deep LWN.net explanation of [cgroups](https://lwn.net/Articles/621006/)
* To create:
 - `docker build --tag local:c_docker_test .`
 - `docker run -ti -v /sys/fs/cgroup:/sys/fs/cgroup:ro -v /tmp/$(mktemp -d):/run -it local:c_docker_test`

Error (on main system): `bash: fork: No space left on device`

## Local System
Error: `bash: fork: retry: No child processes`

# Java
Nice walk through of:
* [Java Memory Leaks](https://stackify.com/memory-leaks-java/)
* [Java Heap vs. Stack Space](https://www.journaldev.com/4098/java-heap-space-vs-stack-memory)
* [G1GC Walk-Through](http://www.oracle.com/technetwork/tutorials/tutorials-1876574.html)
* [LinkedIn naarad](https://github.com/linkedin/naarad) - log summarizer

## Memory Leak Examples:
```
java -XX:+UseG1GC -XX:+PrintGCDetails -XX:+PrintGCTimeStamps -XX:+PrintGCDateStamps -XX:+PrintTenuringDistribution -XX:+PrintGCApplicationStoppedTime -Xloggc:log.gc -verbose:gc -Xmx50m JavaMemLeakTest
```

## Testing Per-Thread Stack Size:
`-XX:ThreadStackSize=512`

## Local:
Error: `bash: fork: retry: No child processes`

## Docker:
To create:
`docker build --tag local:java_docker_test .`
`docker run local:java_docker_test'
		
Error (on main system): `bash: fork: No space left on device`

Error (of running program):
```
[Docker local only with -Xmx 1G?]
Thread Count 31559
Exception in thread "main" java.lang.OutOfMemoryError: unable to create new native thread
	at java.lang.Thread.start0(Native Method)
	at java.lang.Thread.start(Thread.java:714)
	at JavaThreadTest.main(JavaThreadTest.java:11)
```

# Docker Controls:
(From [https://success.docker.com/article/how-to-reserve-resource-temporarily-unavailable-errors-due-to-tasksmax-setting])
```
$ sudo systemctl set-property docker.service TasksMax=300
$ sudo systemctl daemon-reload
$ sudo systemctl restart docker
$ systemctl status docker | grep Tasks
           └─50-TasksMax.conf
    Tasks: 33 (limit: 300)
```

Tasks do not seem to increse from C thread test or Java test

# Aside on `ulimit` overrides
To work around your user ulimits temporarily, with root one can run:
```
$ sudo -s
# ulimit -v unlimited
# ulimit -m unlimited 
# ulimit -u unlimited 
# # Does not work for number of open files (ulimit -n)
# sudo -s <user>
$ <command of interest>
```
