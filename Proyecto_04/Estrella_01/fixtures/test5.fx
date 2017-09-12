# cargamos grafo
< # 7 11
< graph G {
<   1 -- 2 [label=7];
<   1 -- 4 [label=5];
<   2 -- 3 [label=8];
<   2 -- 4 [label=9];
<   2 -- 5 [label=7];
<   3 -- 5 [label=5]
<   4 -- 5 [label=15];
<   4 -- 6 [label=6];
<   5 -- 6 [label=8];
<   5 -- 7 [label=9];
<   6 -- 7 [label=11];
< }

# chequeamos aristas de salida
> # 7 11
> 5 -- 7 \[label=9\];
> 1 -- 2 \[label=7\];
> 2 -- 5 \[label=7\];
> 4 -- 6 \[label=6\];
> 3 -- 5 \[label=5\];
> 1 -- 4 \[label=5\];
> 5 -- 6 \[label=8,style=dotted\];
> 2 -- 3 \[label=8,style=dotted\];
> 2 -- 4 \[label=9,style=dotted\];
> 6 -- 7 \[label=11,style=dotted\];
> 4 -- 5 \[label=15,style=dotted\];

# chequeamos leaks
> All heap blocks were freed -- no leaks are possible
: Hay leaks!
