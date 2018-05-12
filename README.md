I am struggling to run with a large number of threads because OS limits.

https://stackoverflow.com/questions/344203/maximum-number-of-threads-per-process-in-linux

`/proc/sys/kernel/threads-max` is part of the answer. Also need to set
the `ulimit` for numprocs so the user can make threads. You may need to
adjust:

    /etc/security/limits.conf

But also in `fork.c` there may be a limitation regarding virtual memory
(or is it the amount of physical memory?) and stack size. Check
`set_max_threads`. Seems to want to use at maximum 1/8th of the total
ram for thread structures. Involves `totalram_pages`, is that physical
or virtual RAM pages? Important distinction?

```
		threads = div64_u64((u64) totalram_pages * (u64) PAGE_SIZE,
				    (u64) THREAD_SIZE * 8UL);
```

You can get page size via `getconf PAGE_SIZE`. It looks like
`THREAD_SIZE` is defined to be 2x the `PAGE_SIZE` (because
`THREAD_ORDER`?)?

Actually, `THREAD_ORDER`, for 64bit linux, is set to `2`, so
`THREAD_SIZE` is 4x the `PAGE_SIZE`.

So looks like it might be 1/16th of the pages can be set aside for
threads?

`vmstat -s` gives you VM stats, like the number of pages?

vmstat gives me the amount of total memory. That's the numerator of the
equation. Then I divide by `8 * THREAD_SIZE = 8 * (2 * PAGE_SIZE)`.
Indeed, dividing by 32 is gives me 7925...

Fuck.

* https://github.com/torvalds/linux/blob/master/kernel/fork.c
  * Where limit is enforced.
* https://github.com/torvalds/linux/blob/master/mm/page_alloc.c
  * Where `totalram_pages` is defined but not helpful :-(
* https://elixir.bootlin.com/linux/v3.1/source/arch/x86/include/asm/page_64_types.h#L5
* https://github.com/torvalds/linux/blob/a5532439ebab93e47784effb96aafa7d7ba4b760/arch/x86/include/asm/page_64_types.h
