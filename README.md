
# path-finder \#\#\# work in progress! \#\#\#

Path-finder is a simple cli game made using ncurses in C that challenges its players to find a designated file path.

There are two gamemodes :\
    - quick fire,\
    - burning steps.




## quick fire

```
dir1
 ├────file1
 │
 ├────file2
 │
 └────dir2
        └────*file3*
```

When prompted such a repertory tree, the user has to compute a route to the file in the shortest amount of time. So in this case, correct input would be :\
`"dir1/dir2/file3"`\
When levels get harder, players can make a wrong step into a directory. The only way of going back is the `"../"` instruction. You cannot delete correct directories from your path input.
## burning steps

```
dir1
 ├────file1
 │
 ├────file2
 │
 ├────dir2
 │      └────file3
 └────dir3
        └────*file4*
```

When prompted such a repertory tree, the user has to compute the quickest route to the file without being able to go back on its track. Each step into a directory locks the users ability to use `"../"`. So in this case, if the player entered :\
 `"dir1/dir2/"`\
he would be stuck inside dir2 and lose.
## how to run

Compile project using :

```bash
  $ make compile
```

Run :

```bash
  $make run
```
or
```bash
  $./bin/path-finder
```
