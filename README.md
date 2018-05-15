# C thread creation (not running)
## VM
`-bash: fork: retry: Resource temporarily unavailable`

## Docker:
To create:
`docker build .`
`docker run -ti -v /sys/fs/cgroup:/sys/fs/cgroup:ro -v /tmp/$(mktemp -d):/run -it <image ID>`

Error (on main system): `bash: fork: No space left on device`

## Local System
Error: `bash: fork: retry: No child processes`

# Java
## Local:
Error: `bash: fork: retry: No child processes`

## Docker:
To create:
`docker build .`
`docker run <image ID>`

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
