noipv4
======

Run a program with IPv4 disabled.

It hacks [`bind`](http://linux.die.net/man/2/bind), [`connect`](http://linux.die.net/man/2/bind)
and [`sendto`](http://linux.die.net/man/2/sendto) functions to make them reject IPv4 connections.

This utility is particularly useful in [CERNET](http://www.edu.cn/), where
IPv6 is free and IPv4 is not.
("Free" as in both "free beer" and "freedom". You know what this means LOL)

本工具用于禁止 IPv4 流量。在部分高校, IPv6 免费、IPv4 按流量计费,
当 IPv6 资源充足时, 可使用本工具禁用 IPv4, 以减少下载费用。


HOWTO
=====

Example: Disable IPv4 for [transmission](http://www.transmissionbt.com/).

    $ cd noipv4
    $ make
    $ cp libnoipv4.so ~/
    $ LD_PRELOAD=$HOME/libnoipv4.so transmission
