prime-counter
====

高速に素数の数を数えるよ

Atkinの篩を用いて1~nまでの素数を列挙し、√n個毎にその個数を数えて標準出力に出力します。

# Required Library/Software

- gcc or clang
- boost
- pthread
- cmake
- make

# build

```
$ cmake .
$ make
```

# run

    $ ./prc 10000000000

# Copyright

Copyright 2015 primenumber (prime@kmc.gr.jp)

# License

This file is part of prime-counter.

prime-counter is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

prime-counter is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with prime-counter.  If not, see <http://www.gnu.org/licenses/>.
