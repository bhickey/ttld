Time-to-Live Daemon (ttld)
==========================
A little tool that scurries around your file system devouring files that have
expired.

Why?
----
Sometimes you end up with files that you want to keep around for a couple of
days. Automated cleanup is nice. Trust me, this is actually useful.

Given a root, ttld walk the directory tree, it looks for time specifiers in
the directory path. It compares the specifier value with file modification
time and deletes files that are old.

How?
----
1. Create directories resembling /ttl=time/
2. Put it in your crontab, aim it at a directory.
3. Done

Times are approximate.
Example specifiers:

* 1y -- one year
* 5M -- five months (150 days)
* 2w -- one week
* 6d -- six days
* 4h -- four hours
* 6m -- six minutes
* 1s -- one second
* 72 -- seventy-two hours

Won't this destroy my computer?
-------------------------------
Probably. ttld will not traverse links.

This isn't deleting files fast enough!
--------------------------------------
Expirations expressed in seconds aren't terribly useful.
The time specifier indicates the earliest a file may be deleted.

But this isn't a daemon at all!
-------------------------------
Initially I had planned to write it as a fancy FUSE model that did precise
tracking of files. Upon realizing that was silly, I wrote this small tool.
Since it works, I didn't get around to daemonizing it. Send me a pull
request if you want to make it fancy.
