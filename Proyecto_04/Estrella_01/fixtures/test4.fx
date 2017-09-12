# cargamos grafo
< # 9 15
< graph G {
<   1 -- 2 [label=15];
<   1 -- 3 [label=13];
<   2 -- 5 [label=11];
<   4 -- 9 [label=20];
<   4 -- 6 [label=5];
<   3 -- 4 [label=8];
<   7 -- 9 [label=17];
<   8 -- 9 [label=21];
<   5 -- 1 [label=6];
<   8 -- 3 [label=11];
<   2 -- 7 [label=25];
<   3 -- 6 [label=12];
<   6 -- 9 [label=10];
<   4 -- 8 [label=3];
<   1 -- 9 [label=9];
< }

# chequeamos aristas de salida
> # 9 15
> 7 -- 9 \[label=17\];
> 2 -- 5 \[label=11\];
> 6 -- 9 \[label=10\];
> 1 -- 9 \[label=9\];
> 3 -- 4 \[label=8\];
> 5 -- 1 \[label=6\];
> 4 -- 6 \[label=5\];
> 4 -- 8 \[label=3\];
> 1 -- 2 \[label=15,style=dotted\];
> 1 -- 3 \[label=13,style=dotted\];
> 3 -- 6 \[label=12,style=dotted\];
> 8 -- 3 \[label=11,style=dotted\];
> 4 -- 9 \[label=20,style=dotted\];
> 8 -- 9 \[label=21,style=dotted\];
> 2 -- 7 \[label=25,style=dotted\];

# chequeamos leaks
> All heap blocks were freed -- no leaks are possible
: Hay leaks!
