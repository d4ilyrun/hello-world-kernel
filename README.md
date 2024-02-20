# My First Kernel

This repository contains the source code shown in the article: [`My First Kernel`](https://blog.gistre.epita.fr/posts/leo.duboin-2023-11-26-my_first_kernel/)
on the GISTRE blog

This kernel should boot correctly and write `Hello, GISTRE!` onto the screen.

## Prerequisites

* i686-gcc
* qemu
* Make

## Building

```bash
$ make iso  # builds an ISO of the kernel
$ make qemu # boots the kernel inside qemu
```
